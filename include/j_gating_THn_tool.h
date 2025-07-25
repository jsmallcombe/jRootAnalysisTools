// //
// //
// //	jROOT Tools
// //	An object that runs a root based gating and background subtraction environment for TH2 and TH3
// //	17 Nov 2019
// //	james.smallcombe@outlook.com
// //
// //
// 
#ifndef jGatingToolTHn_h
#define jGatingToolTHn_h

#include "j_gating_TH3_tool.h"

class jGatingToolTHnMany : public TGMainFrame {

private:
//     static inline const int DummyBins[256] = {1}; 
//     static inline const double DummyLow[256] = {0.0}; 
//     static inline const double DummyHigh[256] = {1.0}; 
    
    THnBase *fInputStore;
    THnBase *fBack, *fResult, *fResFullProj;
    double fBackFrac;
	
	jGateSubtractionFrame *fGateFrame;
	jGatingToolTHnMany *fResFrameTHn;
	jGatingToolTH3 *fResFrameTH3;
	TGMainFrame *child;
    int Ndim;
    
    void CleanResHist();
    
public:
	jGatingToolTHnMany(THnBase* input);
	virtual ~jGatingToolTHnMany();
    
    void SetWindowName(const char* name) override;
    
	void UpdateInput(THnBase* input);
    void UpdateInput();
    void DoHistogram();
    

    void Init(){
       fGateFrame->HideManBar();
    }
    
	ClassDefOverride(jGatingToolTHnMany, 2)
};

#endif
