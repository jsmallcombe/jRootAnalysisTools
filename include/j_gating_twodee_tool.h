// //
// //
// //	jROOT Tools
// //	An object that runs a root based gating and background subtraction environment for TH2 and TH3
// //	17 Nov 2019
// //	james.smallcombe@outlook.com
// //
// //
// 
#ifndef jGateToolTwoDee_h
#define jGateToolTwoDee_h

#include "TROOT.h"
#include "TGLayout.h"
#include "TF1.h"
#include "TMath.h"
#include "TH2.h"
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

#include "j_gating_result_frame.h"
#include "j_gating_select_frame.h"
#include "j_gate_subtract.h"

class jGateFrameTwoDee;

class jGateToolTwoDee : public TGMainFrame {

private:
	jGateFrameTwoDee *gJframe1;
   
public:
	jGateToolTwoDee(const char *);
	jGateToolTwoDee(TObject* = hist_capture());
	virtual ~jGateToolTwoDee(){
        Cleanup();
    };

	void UpdateInput(const char *);
	void UpdateInput(TObject* = hist_capture());
    
	ClassDef(jGateToolTwoDee, 2)
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class jGateFrameTwoDee : public TGHorizontalFrame {

private:
    TH1 *fInputStore;
    TH1 *fProj, *fGate, *fResult, *fResFullProj;
    
    bool ThreeDee;
    int xy;
    string suffix;
    
    // For the 3D use-case
	TH1 **fGateTwo, **fResultTwo, **fResFullProjTwo;
	
	jGateSelectFrame *fGateFrame;
	jGateResultFrame *fResFrame;
    
public:
	jGateFrameTwoDee(){};
	jGateFrameTwoDee(TGWindow *, TH1*,bool=false);
	virtual ~jGateFrameTwoDee();
    
    void ChangeProjection(const Int_t);
    void RequestTwoDee(const Bool_t);
    
    void UpdateInput(TH1*);
    void UpdateTypeSwitch();
    void UpdateInput();
    void DoHistogram();

    // For the 3D use-case
    void SetTwoDeePass(TH1 **res,TH1 **gate,TH1 **pro){
        fResultTwo=res;
        fGateTwo=gate;
        fResFullProjTwo=pro;
    }
    
    void Init(){
       fResFrame->HideSave(); 
       fGateFrame->HideManBar();
    }
    
    bool TestThreeDee(){return ThreeDee;}
    
	ClassDef(jGateFrameTwoDee, 2)
};


#endif
