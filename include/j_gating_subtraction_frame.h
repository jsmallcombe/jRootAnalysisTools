//
//
//	jROOT Tools
//	interstitial class between jGateSelectFrame and TH2/TH3/THn gating tools. All projection and subtraction logic is stored here
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
//

#ifndef jGatingSubtractionFrame_h
#define jGatingSubtractionFrame_h

#include <THnBase.h>

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
	TH1* ProjectAxisByBin(T*,int,TString, bool=gGlobalUnderlowBool,bool=gGlobalOverflowBool);

	//
	// Scaled subtraction functions
	// Templated for TH1 and THn types
	//

	double ScaledBackgroundSubtract(THnBase* ,THnBase*  ,double ,double=0);
	double ScaledBackgroundSubtract(TH1* ,TH1*  ,double ,double=0);
		
	// THnBase has a different relationship with Sumw2 ...
	// THnBase doesnt have GetSumw2N()
	// TH1 doesnt have GetCalculateErrors()
	// TH1::GetSumw2() returns a valid TArrayD* either way
	// TH1::GetSumw2()->fN==0 if no weights calculated
	// THnBase::GetSumw2()==-1 if no weights calculated
	bool TestWeightsStatus(TH1* hist){return hist->GetSumw2N();} // =0 if no weights, so casts to false
	bool TestWeightsStatus(THnBase* hist){return hist->GetCalculateErrors();}
	
	// This doesnt actually clear the weights, but it sets the relevant flag
	// So them old weights arent used and new weights are recalculated next time Sumw2() is called
	void ResetWeights(TH1* hist){hist->Sumw2(kFALSE);}
	void ResetWeights(THnBase* hist){hist->CalculateErrors(kFALSE);}
	
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

extern template TH1* jGateSubtractionFrame::ProjectAxisByBin<TH1>(TH1*,int,TString, bool,bool);
extern template TH1* jGateSubtractionFrame::ProjectAxisByBin<THnBase>(THnBase*,int,TString, bool,bool);

extern template TH1* jGateSubtractionFrame::MakeBackWithGateGap<TH1,TH1>(TH1*,TH1*,TH1*);
extern template TH1* jGateSubtractionFrame::MakeBackWithGateGap<THnBase,TH1>(THnBase*,TH1*,TH1*);
extern template THnBase* jGateSubtractionFrame::MakeBackWithGateGap<THnBase,THnBase>(THnBase*,THnBase*,THnBase*);

extern template void jGateSubtractionFrame::UpdateInput<TH1,TH1>(TH1*,TH1*&);
extern template void jGateSubtractionFrame::UpdateInput<THnBase,TH1>(THnBase*,TH1*&);
extern template void jGateSubtractionFrame::UpdateInput<THnBase,THnBase>(THnBase*,THnBase*&);

extern template double jGateSubtractionFrame::DoGateSubtract<TH1,TH1>(TH1*,TH1*&,TH1*&,TH1*&);
extern template double jGateSubtractionFrame::DoGateSubtract<THnBase,TH1>(THnBase*,TH1*&,TH1*&,TH1*&);
extern template double jGateSubtractionFrame::DoGateSubtract<THnBase,THnBase>(THnBase*,THnBase*&,THnBase*&,THnBase*&);


// // template <typename T>
// // void jGateSubtractionFrame::ResetWeights(T* hist){
// // 	if(hist->IsA()->InheritsFrom(THnBase::Class())){
// // 		THnBase* hcast = dynamic_cast<THnBase*>(hist);
// // 	}
// // }



#endif 
