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

#include "james_utility.h"
#include "james_ultrafit_env.h"
#include "james_gpad_tools.h"
#include "james_gating_tool.h"
#include "james_gate_subtract.h"
#include "james_hist_formatting.h"
#include "james_spectool.h"


using namespace std;

//current_capture_frame
class CCframe : public TRootEmbeddedCanvas {
	private:
		TH1* current;//Never owns
		TPad* currentpad;//Never owns
		TCanvas* currentcan;//Never owns
		string histname;
		void SetNewHist(TH1* fH,TPad* Pad,TCanvas* Can);
		bool pause;
	public:
		CCframe(const char * name = 0,const TGWindow * p = 0,UInt_t w = 10,UInt_t h = 10,UInt_t options = kSunkenFrame | kDoubleBorder,Pixel_t 	back = GetDefaultFrameBackground());
		~CCframe();
		
		TH1* Hist();
		
		int Type();

		void TrackCaptureHistogram(TPad*,TObject*,Int_t);
	
		std::vector< TCanvas* > CFriends;
		
	ClassDef(CCframe, 1)
};


class jEnv : public TGMainFrame {

private:
	TStopwatch Stop;
	CCframe *fCanvas1;
	UltraFitEnv* fFitPanel;
	jSpecTool* fSpecTool;
	TGVerticalFrame* addsub;
	TRootEmbeddedCanvas *A,*B,*result;
	TH1* AHist,*BHist,*SumHist,*SameSave;//Always owned and private
	TGHSlider* fHslider1;
	TGTextEntry* fTeh1;
	TGCheckButton* fCheck1;
	TGTextBuffer  *fTbh1;
	int gSubtract;
	TGTextButton* addsubclick;
	static int SumNameItt;
	bool gDrawSame;
	
	void Show();
	void Hide();
	void Grab(int);
	void DrawAB(int);
	void UpdateText();
	
public:
	jEnv();
	virtual ~jEnv(){
		if(fFitPanel){delete fFitPanel;}
		if(fSpecTool){delete fSpecTool;}
		if(AHist){delete AHist;}
		if(BHist){delete BHist;}
		if(SumHist){delete SumHist;}
		if(SameSave){delete SameSave;}
	};
	
	void Swap();
	void FitPanel();
	void FitPanelClose(){fFitPanel=0;}
	void Spectrum();
	void SpecToolClose(){fSpecTool=0;}
	void Browser();
	void Gatter();
	void ShowHide();
	void jSaveAs();
	void DrawCpy();
	void DrawSm();
	void DrawSmHere(TPad*,TObject*,Int_t);
	void GrabA(Int_t,Int_t,Int_t,TObject*);
	void GrabB(Int_t,Int_t,Int_t,TObject*);
	void DoSlider();
	void DoText();
	void AddSubButton();
	

	ClassDef(jEnv, 1)
};

#endif
