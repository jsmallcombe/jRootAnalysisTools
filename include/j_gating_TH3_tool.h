// //
// //
// //	jROOT Tools
// //	An object that runs a root based gating and background subtraction environment for TH2 and TH3
// //	17 Nov 2019
// //	james.smallcombe@outlook.com
// //
// //
// 
#ifndef jGatingToolTH3_h
#define jGatingToolTH3_h

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

#include "j_gating_TH2_tool.h"

class jGatingFrameTH3;

class jGatingToolTH3 : public TGMainFrame {

private:
	jGatingFrameTH3 *gJframe1;
   
public:
	jGatingToolTH3(const char *);
	jGatingToolTH3(TObject* = hist_capture());
	virtual ~jGatingToolTH3(){
        Cleanup();
    };

	void UpdateInput(const char *);
	void UpdateInput(TObject* = hist_capture());
    
	ClassDef(jGatingToolTH3, 1)
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class jGatingFrameTH3 : public TGHorizontalFrame {

private:
    TH1 *fInputStore;
    TH1 *fProj, *fBack, *fResult, *fResFullProj;
    double fBackFrac;
    
    int xyz;
    string suffix;
	
	jGateSubtractionFrame *fGateFrame;
	jGatingFrameTH2 *fResFrame;
    
    bool UpdateLock;
    
public:
	jGatingFrameTH3(){};
	jGatingFrameTH3(TGWindow *, TH1*);
	virtual ~jGatingFrameTH3();
    
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
	ClassDefOverride(jGatingFrameTH3, 3)
};


#endif
