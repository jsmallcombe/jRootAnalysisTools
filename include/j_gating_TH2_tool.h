// //
// //
// //	jROOT Tools
// //	An object that runs a root based gating and background subtraction environment for TH2 and TH3
// //	17 Nov 2019
// //	james.smallcombe@outlook.com
// //
// //
// 
#ifndef jGatingToolTH2_h
#define jGatingToolTH2_h

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
#include "j_gating_subtraction_frame.h"

class jGatingFrameTH2;

class jGatingToolTH2 : public TGMainFrame {

private:
	jGatingFrameTH2 *gJframe1;
   
public:
	jGatingToolTH2(const char *);
	jGatingToolTH2(TObject* = hist_capture());
	virtual ~jGatingToolTH2(){
        Cleanup();
    };

	void UpdateInput(const char *);
	void UpdateInput(TObject* = hist_capture());
    
	ClassDef(jGatingToolTH2, 2)
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class jGatingFrameTH2 : public TGHorizontalFrame {

private:
    TH1 *fInputStore;
    TH1 *fProj, *fBack, *fResult, *fResFullProj;
    double fBackFrac;
    
    bool ThreeDee;
    int xy;
    TString suffix;
    
    // For the 3D use-case
	TH1 **fBackTwo, **fResultTwo, **fResFullProjTwo;
	double *fBackFracTwo;
	
	jGateSubtractionFrame *fGateFrame;
	jGateResultFrame *fResFrame;
    
public:
	jGatingFrameTH2(){};
	jGatingFrameTH2(TGWindow *, TH1*,bool=false);
	virtual ~jGatingFrameTH2();
    
    void ChangeProjection(const Int_t);
    void RequestTwoDee(const Bool_t);
    
    void UpdateInput(TH1*);
    void UpdateTypeSwitch();
    void UpdateInput();
    void DoHistogram();

    // For the 3D use-case
    void SetTwoDeePass(TH1 **res,TH1 **gate,TH1 **pro,double *bfr){
        fResultTwo=res;
        fBackTwo=gate;
        fResFullProjTwo=pro;
        fBackFracTwo=bfr;
    }
    
    void Init(){
       fResFrame->HideSave(); 
       fGateFrame->HideManBar();
    }
    
    bool TestThreeDee(){return ThreeDee;}
    
	ClassDef(jGatingFrameTH2, 2)
};


#endif
