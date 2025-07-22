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

using namespace std;

///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/////////// Functions gating and subtracting TH2 and TH3   /////////// 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// class jGateSubtractionFrame {
class jGateSubtractionFrame : public jGateSelectFrame {

private:

	// Helper functions to ensure overflow is included when we want it
	void SetRangeAxis(TAxis* ax,int=0,int=0);
	void ResetRanges(TH1*,bool=false);
	
	//3D gating functions
	// these will nicely overwrite any previously done projection OF THE SAME TYPE
	// if you dont want that add a name in string
	TH1* GateByBin(TH3*,int=0,int=0,int=-1,TString="");

	// 2D gating functions
	// these will nicely overwrite/fill any previously done 2D projection add a name in string
	TH1* GateByBin(TH2*,int=0,int=0,int=-1,TString="proj");


public:
   jGateSubtractionFrame();
   jGateSubtractionFrame(TGWindow* parent, TH1* input=nullptr, int ThreeDee=0);
   virtual ~jGateSubtractionFrame(){};
   
   
	// This just forward to the correct above type after checking TH2/3 inheritance 
	TH1* GateAxisByBin(TH1*,int=0,int=0,int=-1,TString="proj");
	
	// Project an axis Functions
	// these will nicely overwrite/fill any previously done 2D projection add a name in string
	TH1* ProjectAxisByBin(TH1* in,int xyz=0,string name="proj");

	//addition/subtraction functions 
	//Work for th2 and 3 inherited classes
	TH1* scaled_back_subtract(TH1*,TH1*,double,double=0,bool scale=true);
	TH1* scaled_back_subtract(TH1*,TH1*,double,TH1*,double=0,bool scale=true);

	
   ClassDef(jGateSubtractionFrame, 1)
};


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
#endif 
