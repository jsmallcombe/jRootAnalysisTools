//
//
//	jROOT Tools
//	Histogram Y Graph manipulation gui tools
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef jamesextragui_h
#define jamesextragui_h

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <TBrowser.h>
#include <TCanvas.h>
#include <TText.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TBox.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TStopwatch.h>
#include <TApplication.h>
#include <TGTab.h>

#include "j_utility.h"
#include "j_ultrafit_env.h"
#include "j_gpad_tools.h"
#include "j_gating_tool.h"
#include "j_gate_subtract.h"
#include "j_hist_formatting.h"
#include "j_spectool.h"
#include "j_elements.h"
#include "j_clipboard_parse.h"
#include "j_env.h"


using namespace std;

// RQ_OBJECT("MyClass") inside the MyClass body (IF MyClass not inherited from TQObject) allow class to use signal/slot communication

class jScale : public TGMainFrame {

private:
	CCframe *fCanvas1,*fCanvas2;
	TRootEmbeddedCanvas *result;
    TGraph *gg;
    TGTextButton* lockbutton;
    bool IsLocked;
    
public:
	jScale();
	virtual ~jScale(){
        if(gg)delete gg;
    };
    
	void NewInput();
    void Lock();

	ClassDef(jScale, 2)
};


class jEval : public TGMainFrame {

private:
	CCframe *fCanvas1;
    TGraph *gg,*GG;
    TGTextButton* lockbutton;
    bool IsLocked;
    TGTextEntry *fTeh1,*fTeh2;
    
public:
	jEval();
	virtual ~jEval(){
        if(gg)delete gg;
        if(GG)delete GG;
    };
    
	void NewInput();
    void Lock();
    void Eval(char*);

	ClassDef(jEval, 1)
};


class jAngleAngel : public TGMainFrame {

private:
	TRootEmbeddedCanvas *fCanvas1;
	TH2* fHistHigh;
	TH2* fHistLow;
	TH2* fHist;//doesnt exist;
	TGHSlider* fHslider;
	TLine fLine;
	int Nl;
	bool lock;
	int sliderpos;
	TStopwatch Stop;
	void DoLines();
    
public:
	jAngleAngel(TH1* fH=0);
	virtual ~jAngleAngel();
    
	void SetCapture();
	void SetNewHist(TH1 *fH);
	void CaptureHistogram(TPad* pad,TObject* obj,Int_t event);
	void SliderChange();
	void SliderRelease();
	void NewRange();
	
	void MakeHist(double=0);
	void MakeHist90(){MakeHist(TMath::Pi()*0.5);};
    
	ClassDef(jAngleAngel, 2)
};



#endif
