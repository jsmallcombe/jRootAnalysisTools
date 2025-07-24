// //
// //
// //	jROOT Tools
// //	An object that runs a root based gating and background subtraction environment for TH2 and TH3
// //	17 Nov 2019
// //	james.smallcombe@outlook.com
// //
// //
// 
#ifndef jGatingToolMaster_h
#define jGatingToolMaster_h

#include "TROOT.h"
#include "TBuffer.h"
#include "TGLayout.h"
#include "TF1.h"
#include "TMath.h"
#include "TH2.h"
#include "TH3.h"
#include "THnBase.h"
#include "TGInputDialog.h"
#include "TGFrame.h"

#include <RQ_OBJECT.h>

#include <iostream>
#include <iomanip> 
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include "j_gating_TH3_tool.h"

class jGatingToolTHnMany : public TGMainFrame {

private:
//     static inline const int DummyBins[256] = {1}; 
//     static inline const double DummyLow[256] = {0.0}; 
//     static inline const double DummyHigh[256] = {1.0}; 
    
    THnBase *fInputStore;
    THnBase *fBack, *fResult, *fResFullProj;
    double fBackFrac;
    TString ChildName;
	
	jGateSubtractionFrame *fGateFrame;
	jGatingToolTHnMany *fResFrameTHn;
	jGatingToolTH3 *fResFrameTH3;
	TGMainFrame *child;
    int Ndim;
    
    void CleanResHist();
    
public:
	jGatingToolTHnMany(THnBase* input,TString OverrideName="");
	virtual ~jGatingToolTHnMany();
    
    
	void UpdateInput(THnBase* input, TString OverrideName="");
    void UpdateInput();
    void DoHistogram();
    

    void Init(){
       fGateFrame->HideManBar();
    }
    
	ClassDef(jGatingToolTHnMany, 1)
};

#endif
