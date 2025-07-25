//
//
//	jROOT Tools
//	A gating and background subtraction tool for TH3 histograms and THn histograms with Ndim=3
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
//

#ifndef jGatingToolTH3_h
#define jGatingToolTH3_h

#include "j_gating_TH2_tool.h"

class jGatingToolTH3 : public TGMainFrame {


private:
    TObject *fInputStore;
    TH1 *fProj, *fBack, *fResult, *fResFullProj;
    double fBackFrac;
	
	jGateSubtractionFrame *fGateFrame;
	jGatingFrameTH2 *fResFrame;
    
    bool UpdateLock;
    
    bool THnBaseType;
    
    bool DetachedHead;
    
    void CleanResHist();
    
//     TGMainFrame* child;
    TGTransientFrame* child;
    
public:
	jGatingToolTH3(TObject* = hist_capture(),int=-1);
	jGatingToolTH3(const char *,int=-1);
	virtual ~jGatingToolTH3();
    
    void SetWindowName(const char* name) override;
    
    void ChangeProjection(const Int_t);
    void RequestTwoDee(Bool_t){};
    
	void UpdateInput(const char *);
	void UpdateInput(TObject*);
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
	ClassDefOverride(jGatingToolTH3, 5)
};

#endif
