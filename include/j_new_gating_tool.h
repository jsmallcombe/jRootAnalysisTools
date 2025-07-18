// //
// //
// //	jROOT Tools
// //	An object that runs a root based gating and background subtraction environment for TH2 and TH3
// //	17 Nov 2019
// //	james.smallcombe@outlook.com
// //
// //
// 
#ifndef jamesfuncnew_gating_tool
#define jamesfuncnew_gating_tool

#include "TROOT.h"
#include "TGLayout.h"
#include "TF1.h"
#include "TMath.h"
#include "TH2.h"

#include <RQ_OBJECT.h>

#include <iostream>
#include <iomanip> 
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include "j_gating_select_frame.h"
#include "j_gating_result_frame.h"
#include "j_gate_subtract.h"

class j_gating_frametwodee;

class jnewgating_tool : public TGMainFrame {

private:
	j_gating_frametwodee *gJframe1;
   
public:
	jnewgating_tool(const char *);
	jnewgating_tool(TObject* = hist_capture());
	virtual ~jnewgating_tool(){
        Cleanup();
    };

	void UpdateInput(const char *);
	void UpdateInput(TObject* = hist_capture());
    
	ClassDef(jnewgating_tool, 2)
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class j_gating_frametwodee : public TGHorizontalFrame {

private:
    TH1 *fInputStore;
    TH1 *fProj, *fGate, *fResult, *fResFullProj;
    
    int xy;
    string suffix;
	
	j_gating_select_frame *fGateFrame;
	j_gating_result_frame *fResFrame;
    
public:
	j_gating_frametwodee(){};
	j_gating_frametwodee(TGWindow *, TH1*,bool=false);
	virtual ~j_gating_frametwodee();
    
    void ChangeProjection(const Int_t);
    void RequestTwoDee(Bool_t){};
    
    void UpdateInput(TH1*);
    void UpdateInput();
    void DoHistogram();

    void Init(){
       fResFrame->HideSave(); 
       fGateFrame->HideManBar();
    }
    
	ClassDef(j_gating_frametwodee, 2)
};


#endif
