//
//
//	jROOT Tools
//	A gating and background subtraction tool for THn histograms with Ndim>3. Beware memory usage, consider TTrees.
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
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
    
    void Closed(TObject* obj){
        Emit("Closed(TObject*)", (Long_t)obj);
    }
    
	ClassDefOverride(jGatingToolTHnMany, 2)
};

#endif
