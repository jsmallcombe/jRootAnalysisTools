//
//
//	jROOT Tools
//	Tool panel and helper environment for GUI working in root
//	26 Jul 2025
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

#include <TVirtualX.h>
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
#include <TTreeViewer.h>

#include "j_utility.h"
#include "j_ultrafit_env.h"
#include "j_gpad_tools.h"
#include "j_gating_tool.h"
#include "j_gate_subtract.h"
#include "j_hist_formatting.h"
#include "j_spectool.h"
#include "j_elements.h"
#include "j_clipboard_parse.h"


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
    
    vector<TGButton*> OneOnly;
    vector<TGButton*> OneNotly;
    
    bool Alternator;
	
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
	void FreeSpectrum();
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
	void NewCanvasObject(TObject*);
    
    static void Clipboard(Int_t,Int_t,Int_t,TObject*);
    
	TGCompositeFrame* AddTab(string TabName="",bool ShowClose=true);
    TCanvas* AddCanvasTab(string TabName="");
	void CloseTab(Int_t ID);
    
	void ClosedObject(TObject* obj);
    
    static FontStruct_t GetFont();

	ClassDef(jEnv, 3)
};


#endif
