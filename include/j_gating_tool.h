//
//
//	jROOT Tools
//	An object that runs a root based gating and background subtraction environment for TH2 and TH3
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef jamesfunc_gating_tool
#define jamesfunc_gating_tool

#include "TROOT.h"
#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"
#include "TGLayout.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGTextEntry.h"
#include "TGSlider.h"
//#include "TGTripleSlider.h"
#include "TH2F.h"
#include "TGButtonGroup.h"
#include "TGButton.h"
#include "THashList.h"
#include "TStyle.h"
#include "TGSplitter.h"
#include "TGInputDialog.h"

#include <iostream>
#include <iomanip> 
#include <RQ_OBJECT.h>

#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <ctime>    
using namespace std;

#include "j_ultrafit_env.h"
#include "j_gating_frame.h"

extern bool gGlobalAskWindowName;
void SetGlobalAskWindowName(bool set=true);

class jgating_tool : public TGMainFrame {

private:
	TRootEmbeddedCanvas *fCanvas1;
	j_gating_frame      *gJframe1,*gJframe2;
	TGVerticalFrame     *resultframe,*saveframe;
	TGButtonGroup	*fBgroup1,*savebuttons;
	TGRadioButton	*fRButton1,*fRButton2,*fRButton3;
	TGCheckButton   *fCheck0,*fCheck1;
	TGHSlider    	*fHslider1;
    
    TGTextEntry *RebinText;
    
    TGHorizontalFrame* MainPanels;
    TGVSplitter* splitterB;
    
    TGTextButton* ftbutton;
	
	TF1 *fFitFcn; 
	TText* peaknumremove;   

	static int jgating_tool_iterator;
	string make_iterator();
	TGToolTip *fTip;
	UltraFitEnv* fFitPanel;
    
    TGTransientFrame* MakeTH3Popup();
	
    vector< TH1* > savehists;
	vector< TGCheckButton* > savechecks;
	vector< TGTextButton* > savebutton;
	
	TH1* fInputStore;
    
    double x1,x2,y1,y2;
    
    bool RangeUpdateHold;
    
	void ClearSaved();
	// Have to manually specify nanoseconds, or trunacte manaully to microseconds elsewhere, or mac wont compile due the system clock prevision not matching that which is assumed
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> clicktime;
   
public:
	jgating_tool(const char *);
	jgating_tool(TObject* = hist_capture(),bool=0);
	virtual ~jgating_tool();

	void DoCheckbox2D();
	void DoUpdate2D();
	void DoUpdate();
	void ClickedFinalCanvas(Int_t,Int_t,Int_t,TObject*);
	void SavePanel();
	void FitPanel();
	void jSaveAs();
	void AddStoreHistogram();
	void CSaveButton();
	void StoreHistograms(Int_t);
	void DrawSaved();
	void NewAxisDrawn();
    
    void ProcessedConfigure(Event_t*);
    void ShareMainPanels();
    
	void ResetRange();
    void ButtonGroupDoUpdate(Int_t i);
    
    void Closed(TObject* obj){
        Emit("Closed(TObject*)", (Long_t)obj);
    }

    //Move to the new class asap
	static int Iterator(){jgating_tool_iterator++;return jgating_tool_iterator;};
	static TString Iterator(TString in){return in+=Iterator();};
    
	ClassDef(jgating_tool, 2)
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  MINIMALIST TH3 SLICER  /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////



class minimalist_th3slice : public TGMainFrame {
private:
	TRootEmbeddedCanvas *fCanvas1,*fCanvas2;
	TGLayoutHints       *fLcan,*fBly, *fBfly1, *fBfly2, *fBfly3, *fBfly4;
	TGVerticalFrame     *miniframe,*miniframe1;
	TGHorizontalFrame   *fHframe0;
	TGButtonGroup	*fBgroup1;
	TGRadioButton	*fRButton1,*fRButton2,*fRButton3;
	TGCheckButton	*fCheck0;

	TH3 *raw_3d;
	TH2 *slice;
	TH1 *proj;
	
	static int minimalist_th3slice_iterator;
	string make_iterator();
	string iterator;
	//	CONTROL VALUES
	int xyz;     
	int bin;
	
	void initialise(); //the core of the two constructors
public:
   minimalist_th3slice();
   minimalist_th3slice(TH3*);
   virtual ~minimalist_th3slice();
   minimalist_th3slice& operator= (TH3*);   
   minimalist_th3slice& operator() (TH3*); 
   void set(TH3F* in){*this=in;}
   
   

    void ChangeProjection(Int_t);
    void DoUpdate(Int_t,Int_t,Int_t,TObject*);
    
   ClassDef(minimalist_th3slice, 2)
};

#endif
