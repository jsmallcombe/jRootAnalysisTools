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
	
	template <typename T>
	bool TestWeightsStatus(T*);
	
	template <typename T>
	void ResetWeights(T*);
	
	template <typename U,typename T>
	T* MakeBackWithGateGap(U*, T* =nullptr, T* =nullptr);

public:
   jGateSubtractionFrame();
   jGateSubtractionFrame(TGWindow* parent, int ThreeDee=0);
   virtual ~jGateSubtractionFrame(){};

// 	double ScaledBackgroundSubtract(TH1*,TH1*,double,double=0);
	
	template <typename U,typename T>
	void UpdateInput(U*, T*&);  
	
	template <typename U,typename T>
	double DoGateSubtract(U*, T*&, T*&, T*&);
	
   ClassDef(jGateSubtractionFrame, 4)
};

///////////////////////////////////////////////////
////////////// Template parts ////////////////////
///////////////////////////////////////////////////

template <typename U,typename T>
void jGateSubtractionFrame::UpdateInput(U*fInput, T*&fResFullProj){
	// fResFullProj expected to be nullptr as fResFullProj is only created on input/axis change
	// Hence expect fResFullProj do have changed binning etc, so it is *always* deleted, and not making use name-based overwritting.
    
	fResFullProj=(T*)GateAxisByBin(fInput,xyz,gGlobalLowestBin,-1*gGlobalOverflowBool,"ResFullProj"+IterSuffix);
// 	fResFullProj->SetStats(0);	// No support for THnBase template. If need for drawing reason, add in jGatingToolTH3
	fResFullProj->SetTitle("");
	
	TH1* proj=ProjectAxisByBin(fInput,xyz,"proj"+IterSuffix);
    jGateSelectFrame::UpdateInput(proj);// call base class version
	delete proj; //Cloned inside jGateSelectFrame::UpdateInput()
}
    

template <typename U,typename T>
double jGateSubtractionFrame::DoGateSubtract(U*fInput, T*&fResult, T*&fBack, T*&fResFullProj){
	
	// In the case of TH2::ProjectionX()/TH3::Project3D efficiently re-using in-memory histogram of same name
	// There is an issue whereby the sumw2 is not reset, so if fInput does NOT have weights,
	// The resultant projections, which should not have weights set, will have weights set that are incorrect!
	// The reset is called on the previous histogram if it exists, before it is overwritten, to avoid removing weights if fInput DOES have weights 
	if(fResult)ResetWeights(fResult);
	if(fBack)ResetWeights(fBack);
    
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
				// In gated part from the full projection
				fBack=MakeBackWithGateGap(fInput,fResult,fResFullProj);
			}
			break;
		case 4://none
			{
                fBack=fResult;
			}
			break;
		default:  //manual 
			{
                if(SubtractGate()){
					// In special case remove the gated part
					fBack=MakeBackWithGateGap(fInput,fResult);
				}else{
					fBack=(T*)GateAxisByBin(fInput,xyz,GetBackBinDown(),GetBackBinUp(),"Back"+IterSuffix);
				}		
			}
			break;
	}
	
//    The method GateAxisByBin, used for fResult, and for the backgrounds Compton & manual
//    will reuse the exiting histogram in memory, the other options do not.
//    So we catch those and delete the abandoned fBack histgram
    if(fBackTidy&&fBack!=fBackTidy){
        if(fBackTidy!=fResult&&fBackTidy!=fResFullProj) delete fBackTidy;
    }
	
	// The gated "histogram" fResult* and a background "histogram" fBack* are now clearly defined
	// Do the actual subtraction and propagate errors 
	
	double fBackFrac=1;
	if(fResult!=fBack)fBackFrac=ScaledBackgroundSubtract(fResult,fBack,GetBackFrac(),GetBackFracFrac());
    

    return fBackFrac;
}

template <typename T>
bool jGateSubtractionFrame::TestWeightsStatus(T* hist){
	
		//  THnBase has a different relationship with Sumw2 ...
		// THnBase doesnt have GetSumw2N()
		// TH1 doesnt have GetCalculateErrors()
		// TH1::GetSumw2() returns a valid TArrayD* either way
		// TH1::GetSumw2()->fN==0 if no weights calculated
		// THnBase::GetSumw2()==-1 if no weights calculated
		if(hist->IsA()->InheritsFrom(TH1::Class())){
			TH1* hcast = dynamic_cast<TH1*>(hist);
			if(hcast)return hcast->GetSumw2N();//zero if no weights, so casts to false
		}else if(hist->IsA()->InheritsFrom(THnBase::Class())){
			THnBase* hcast = dynamic_cast<THnBase*>(hist);
			if(hcast)return hcast->GetCalculateErrors();
		}
		return false;
}


template <typename T>
void jGateSubtractionFrame::ResetWeights(T* hist){
	if(hist->IsA()->InheritsFrom(TH1::Class())){
		TH1* hcast = dynamic_cast<TH1*>(hist);
		if(hcast)return hcast->Sumw2(kFALSE);
	}else if(hist->IsA()->InheritsFrom(THnBase::Class())){
		THnBase* hcast = dynamic_cast<THnBase*>(hist);
		if(hcast)return hcast->CalculateErrors(kFALSE);
	}
}
// This doesnt actually clear the weights, but it sets the relevant flag so they arent used/are recalculated

template <typename U,typename T>
T* jGateSubtractionFrame::MakeBackWithGateGap(U*fInput, T*fResult, T*fResFullProj){

	T* fBack=nullptr;
	
	// First test if fInput has not had its stats set. Then we can do a quick subtraction
	if(!TestWeightsStatus(fInput)&&fResult){
		// Important as the Add is *not* an arithmetic subtraction, but an exact data removal.
		// If the statistics have already been set due to previous hisogram arithmatic, then a simple subtraction cant work
		if(fResFullProj){
			fBack=(T*)fResFullProj->Clone(TString(fResFullProj->GetName()).ReplaceAll("ResFullProj", "Back"));
		}else{
			fBack=(T*)GateAxisByBin(fInput,xyz,GetBackBinDown(),GetBackBinUp(),"Back"+IterSuffix);
		}
		
		fBack->Add(fResult,-1);

// // // Not used anymore
// // // This removed the additional errors from THIS subtraction, but also deletes any previously present >sqrt(N) errors
// // // ResetWeights(fBack)
		
	}else{ // We must do the slower option of 2 gates, 1 above and 1 below, to preserve statistics
		
		// Test if we are at the very edge of the range and so can do 1 gate
		// This test has actually already been done for manual-type at jGateSelectFrame::DoHistogram(), but not for anti-type
		if(GetGateBinDown()<=GetBackBinDown()){
			fBack=(T*)GateAxisByBin(fInput,xyz,GetGateBinUp()+1,GetBackBinUp(),"Back"+IterSuffix);
		}else if(GetGateBinUp()>=GetBackBinUp()){
			fBack=(T*)GateAxisByBin(fInput,xyz,GetBackBinDown(),GetBackBinDown()-1,"Back"+IterSuffix);
		}else{
			fBack=(T*)GateAxisByBin(fInput,xyz,GetGateBinUp()+1,GetBackBinUp(),"Back"+IterSuffix);
			T* fBackTwo=(T*)GateAxisByBin(fInput,xyz,GetBackBinDown(),GetBackBinDown()-1,"BackTwo"+IterSuffix);
			if(fBack&&fBackTwo){
				fBack->Add(fBackTwo);
				delete fBackTwo;
			}
		}
	}
	return fBack;
}

#endif 
