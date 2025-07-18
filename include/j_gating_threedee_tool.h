// //
// //
// //	jROOT Tools
// //	An object that runs a root based gating and background subtraction environment for TH2 and TH3
// //	17 Nov 2019
// //	james.smallcombe@outlook.com
// //
// //
// 
#ifndef jGateToolThreeDee_h
#define jGateToolThreeDee_h

#include "TROOT.h"
#include "TBuffer.h"
#include "TGLayout.h"
#include "TF1.h"
#include "TMath.h"
#include "TH2.h"
#include "TH3.h"
#include "TGInputDialog.h"

#include <RQ_OBJECT.h>

#include <iostream>
#include <iomanip> 
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include "j_gating_twodee_tool.h"
#include "j_gating_select_frame.h"
#include "j_gate_subtract.h"

class jGateFrameThreeDee;

class jGateToolThreeDee : public TGMainFrame {

private:
	jGateFrameThreeDee *gJframe1;
   
public:
	jGateToolThreeDee(const char *);
	jGateToolThreeDee(TObject* = hist_capture());
	virtual ~jGateToolThreeDee(){
        Cleanup();
    };

	void UpdateInput(const char *);
	void UpdateInput(TObject* = hist_capture());
    
	ClassDef(jGateToolThreeDee, 1)
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class jGateFrameThreeDee : public TGHorizontalFrame {

private:
    TH1 *fInputStore;
    TH1 *fProj, *fGate, *fResult, *fResFullProj;
    
    int xyz;
    string suffix;
	
	jGateSelectFrame *fGateFrame;
	jGateFrameTwoDee *fResFrame;
    
    bool UpdateLock;
    
public:
	jGateFrameThreeDee(){};
	jGateFrameThreeDee(TGWindow *, TH1*);
	virtual ~jGateFrameThreeDee();
    
    void ChangeProjection(const Int_t);
    void RequestTwoDee(Bool_t){};
    
    void UpdateInput(TH1*);
    void UpdateInput();
    void DoHistogram();
    
    void CallDoHistogram();

    void Init(){
       fResFrame->Init(); 
       fGateFrame->HideManBar();
    }
    
    void Layout() override;
    
    bool UpdateLockSetting;
    
    //Using instead of ClassDef because the above override was causing issues with "Steamer"
	ClassDefOverride(jGateFrameThreeDee, 3)
};


#endif
