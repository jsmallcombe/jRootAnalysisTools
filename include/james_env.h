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
#include <TApplication.h>
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
    
	TGTab* fTabs;
	
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
    void AddFreeObject(TObject* obj,bool CanDelete=true);
	
public:
	jEnv();
	virtual ~jEnv(){
		if(SameSave){delete SameSave;}
		ClearFreeObjects();
	};
    
    void Terminate();

	void FitPanel();
	void FreeFitPanel();
	void FitPanelClose(){fFitPanel=0;}
	void Spectrum();
	void SpecToolClose(){fSpecTool=0;}
	void Browser();
	void Gatter();
	void ShowHideTabs();
	void ShowHideDir();
	void jSaveAs();
	void DrawCpy();
	void DrawCpyTab();
	
	void DrawSm();
	void DrawSmHere(TPad*,TObject*,Int_t);	
	void NewDirObject(TObject*);
    
	TGCompositeFrame* AddTab(string TabName="",bool ShowClose=true);
    TCanvas* AddCanvasTab(string TabName="");
	void CloseTab(Int_t ID);
    
	void ClosedObject(TObject* obj);
    
    static FontStruct_t GetFont();

	ClassDef(jEnv, 3)
};



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

#endif
