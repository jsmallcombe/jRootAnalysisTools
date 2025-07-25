//
//
//	jROOT Tools
//	A gating and background subtraction tool for TH2 histograms, based on a sub-frame which can be co-opted by higher order gating tools
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
//

#ifndef jGatingToolTH2_h
#define jGatingToolTH2_h

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
    TH1 *fBack, *fResult, *fResFullProj;
    double fBackFrac;
    
    bool ThreeDee;
    
    // For the 3D-parent use-case
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
    
	ClassDef(jGatingFrameTH2, 3)
};


#endif
