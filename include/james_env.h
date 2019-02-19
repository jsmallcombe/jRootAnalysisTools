//
//
//	James Root Library
//	Tool panel and helper enviroment for GUI working in root
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef jamesenv_h
#define jamesenv_h

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
#include <TGTab.h>

#include "james_utility.h"
#include "james_ultrafit_env.h"
#include "james_gpad_tools.h"
#include "james_gating_tool.h"
#include "james_gate_subtract.h"
#include "james_hist_formatting.h"
#include "james_spectool.h"
#include "james_elements.h"

using namespace std;

// RQ_OBJECT("MyClass") inside the MyClass body (IF MyClass not inherited from TQObject) allow class to use signal/slot communication


class jEnv : public TGMainFrame {

private:
	CCframe *fCanvas1;
	UltraFitEnv* fFitPanel;
	jSpecTool* fSpecTool;
	TGCompositeFrame* addsub;
	TGCompositeFrame* DirList;
	TH1* SameSave;
	bool gDrawSame;
    
	TGTab* fTab;
	vector<TGCompositeFrame*> fTabs;
	
	void ShowTabs();
	void HideTabs();
	void ShowDir();
	void HideDir();
    double Abinwidth;
    
    int fPixOffX;
    int fPixOffY;
    int fDefaultDirWidth;
    int fDefaultDirHeight;
    int fDefaultTabsWidth;
    int fDefaultTabsHeight;
    int fDefaultGrabSize;
    
    TList FreeObjects;
    
    void ClearFreeObjects();
	
public:
	jEnv();
	virtual ~jEnv(){
		if(fFitPanel){delete fFitPanel;}
		if(fSpecTool){delete fSpecTool;}
		if(SameSave){delete SameSave;}
		ClearFreeObjects();
	};
	
	void FitPanel();
	void FitPanelClose(){fFitPanel=0;}
	void Spectrum();
	void SpecToolClose(){fSpecTool=0;}
	void Browser();
	void Gatter();
	void ShowHideTabs();
	void ShowHideDir();
	void jSaveAs();
	void DrawCpy();
	void DrawSm();
	void DrawSmHere(TPad*,TObject*,Int_t);	
	void NewDirObject(TObject*);
    
	void AddTab();
	void CloseTab(Int_t ID);
    
	void ClosedObject(TObject* obj);

	ClassDef(jEnv, 2)
};



class jScale : public TGMainFrame {

private:
	CCframe *fCanvas1,*fCanvas2;
	TRootEmbeddedCanvas *result;
    TGraph *gg;

public:
	jScale();
	virtual ~jScale(){
        if(gg)delete gg;
    };
    
	void NewInput();

	ClassDef(jScale, 1)
};

#endif
