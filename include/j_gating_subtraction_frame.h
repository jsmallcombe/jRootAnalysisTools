//
//
//	jROOT Tools
//	Functions for handling root TH2/TH3 projection/gating in desired way
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef jGatingSubtractionFrame_h
#define jGatingSubtractionFrame_h

#include <iostream>
#include <cmath>

#include <TAxis.h>
#include <THnBase.h>
#include <THnSparse.h>
#include <TH3.h>
#include <TH2.h>
#include <TH1.h>
#include <TClass.h>

#include "j_gating_select_frame.h"


//Created this class to save on extra maths waste adjusting large histograms
//via the limited public functions
class TH1ErrorErrorAdj : public TH1{
public:
	using TH1::TH1; // inherit constructors (only if TH1 has suitable ones)

	TH1ErrorErrorAdj()=default;
	~TH1ErrorErrorAdj()=default;
	void AdjustError(const TH1* back,double frac);
	
	ClassDef(TH1ErrorErrorAdj, 1)	
};

///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/////////// Functions gating and subtracting TH2 and TH3   /////////// 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// class jGateSubtractionFrame {
class jGateSubtractionFrame : public jGateSelectFrame {

private:
	
	Int_t THnAxisHolder[256];
	
	// Unsures projections have unique names from any other simaltanious instances of gater class
	TString IterSuffix;
	
	// Helper functions to ensure overflow is included when we want it
	void SetRangeAxis(TAxis* ax,int=0,int=0);
	void ResetRanges(TH1*,bool=gGlobalUnderlowBool,bool=gGlobalOverflowBool);
	void ResetRanges(THnBase*,bool=gGlobalUnderlowBool,bool=gGlobalOverflowBool);
	
	// THn gating functions
	TObject* GateByBin(THnBase*,int=0,int=0,int=-1);
	
	//3D gating functions
	// these will nicely overwrite any previously done projection OF THE SAME TYPE
	// if you dont want that add a name in string
	TH1* GateByBin(TH3*,int=0,int=0,int=-1,TString="");

	// 2D gating functions
	// these will nicely overwrite/fill any previously done 2D projection add a name in string
	TH1* GateByBin(TH2*,int=0,int=0,int=-1,TString="");
	
	
	// Resets the ranges and forward to the correct above type after checking TH2/3 inheritance 
	TH1* GateAxisByBin(TH1*,int=0,int=0,int=-1,TString="");
	TObject* GateAxisByBin(THnBase*,int=0,int=0,int=-1,TString="");
	
	//
	// Projection functions
	//

	// Template to allow use with TH1* or THn* without casting up to TObject* 
	template <typename T>
	TH1* ProjectAxisByBin(T* input,int xyz,TString name, bool UnderFlow=gGlobalUnderlowBool,bool OverFlow=gGlobalOverflowBool){
		xyz++;
		return (TH1*)GateAxisByBin(input,-xyz,!UnderFlow,-1*OverFlow,name); // Use globals
		// For THn* input, GateAxisByBin can return THn* OR TH1* types, so it returns TObject* in general, and must be cast as we know it is TH1* here.
	}

	//
	// Scaled subtraction functions
	// Templated for TH1 and THn types
	//

	double ScaledBackgroundSubtract(THnBase* ,THnBase*  ,double ,double=0);
	double ScaledBackgroundSubtract(TH1* ,TH1*  ,double ,double=0);

public:
   jGateSubtractionFrame();
   jGateSubtractionFrame(TGWindow* parent, int ThreeDee=0);
   virtual ~jGateSubtractionFrame(){};

// 	double ScaledBackgroundSubtract(TH1*,TH1*,double,double=0);
	
	template <typename U,typename T>
	void UpdateInput(U*, T*&);  
	
	template <typename U,typename T>
	double DoGateSubtract(U*, T*&, T*&, T*&);
	
   ClassDef(jGateSubtractionFrame, 3)
};

///////////////////////////////////////////////////
////////////// Template parts ////////////////////
///////////////////////////////////////////////////

template <typename U,typename T>
void jGateSubtractionFrame::UpdateInput(U*fInput, T*&fResFullProj){
    
	fResFullProj=(T*)GateAxisByBin(fInput,xyz,1,-1,"ResFullProj"+IterSuffix);
// 	fResFullProj->SetStats(0);	//Doesnt work with THnBase template, if need for drawing add in jGatingToolTH3
	fResFullProj->SetTitle("");
	
	TH1* proj=ProjectAxisByBin(fInput,xyz,"proj"+IterSuffix);
    jGateSelectFrame::UpdateInput(proj);// call base class version
	delete proj; //Cloned inside jGateSelectFrame::UpdateInput()
}
    

template <typename U,typename T>
double jGateSubtractionFrame::DoGateSubtract(U*fInput, T*&fResult, T*&fBack, T*&fResFullProj){
        
//     // Testing the name-based histogram recycling functions as intended
// 	cout<<endl;
//     if(fResFullProj)cout<<" "<<fResFullProj->GetName()<<" ";
// 	if(fBack)cout<<fBack->GetName()<<" ";
// 	if(fResult)cout<<fResult->GetName()<<" ";
//     cout<<endl<<" "<<fResFullProj<<" "<<fBack<<" "<<fResult<<" ";
    
	// GateAxisByBin *should* nicely fill the histogram matching the name if the TH1 exists
	// so we dont need to delete pointers except for when changing axis, handled by UpdateInput
	fResult=(T*)GateAxisByBin(fInput,xyz,GetGateBinDown(),GetGateBinUp(),"Gated"+IterSuffix);
	fResult->SetTitle("");

    // Note: The projection "fResFullProj" used to make "full" and "anti" background options
    // include the overflow bins, but excludes the underflow bin.
    // This is an intentional choice, as often intentionally zeroed data may be sorted into the underflow bin
    // The underflow bin can be selected with manual sliders

    T* fBackTidy=fBack;
	switch (GetBackMode()) {
		case 1://full
                fBack=fResFullProj;
			break;
		case 2://compton
                fBack=(T*)GateAxisByBin(fInput,xyz,GetBackBinDown(),-1,"Back"+IterSuffix);
			break;
		case 3://anti gate
			{
				fBack=(T*)fResFullProj->Clone(TString(fResFullProj->GetName()).ReplaceAll("ResFullProj", "Back"));
				fBack->Add(fResult,-1);
				// Doesnt work for THnBase, which has a different relationship with Sumw2 ...
 				//fBack->Sumw2(kFALSE);//Important as the Add is *not* an arithmetic subtraction, but an exact data removal
			}
			break;
		case 4://none
			{
                fBack=fResult;
			}
			break;
		default:  //manual 
			{
				fBack=(T*)GateAxisByBin(fInput,xyz,GetBackBinDown(),GetBackBinUp(),"Back"+IterSuffix);
                if(GetGateBinDown()>GetBackBinDown()&&GetGateBinUp()<GetBackBinUp()){
                    fBack->Add(fResult,-1);//In special case remove the gated part
//                     fBack->Sumw2(kFALSE);// See case 3
                }				
			}
			break;
	}
	
	double fBackFrac=1;
	if(fResult!=fBack)fBackFrac=ScaledBackgroundSubtract(fResult,fBack,GetBackFrac(),GetBackFracFrac());
    
    
//    The method GateAxisByBin, used for fResult, and for the backgrounds Compton & manual
//    will reuse the exiting histogram in memory, the other options do not.
//    So we catch those and delete the abandoned fBack histgram
    if(fBackTidy&&fBack!=fBackTidy){
        if(fBackTidy!=fResult&&fBackTidy!=fResFullProj) delete fBackTidy;
    }
    
    // Testing the name-based histogram recycling functions as intended
//     cout<<endl<<" "<<fResFullProj<<" "<<fBack<<" "<<fResult<<" ";
//     cout<<endl<<" "<<fResFullProj->GetName()<<" "<<fBack->GetName()<<" "<<fResult->GetName()<<endl;

    return fBackFrac;
}


#endif 
