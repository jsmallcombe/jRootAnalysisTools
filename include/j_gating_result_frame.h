//
//
//	jROOT Tools
//	Very rough copy of j_gating_frame for selection only, no actual gating
//	17 Nov 2025
//	james.smallcombe@outlook.com
//
//

#ifndef j_gating_result_frame_h
#define j_gating_result_frame_h


#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"
#include "TGLayout.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGTextEntry.h"
#include "TGSlider.h"
#include "TGTripleSlider.h"
#include "TH2F.h"
#include "TGButtonGroup.h"
#include "TGButton.h"
#include "THashList.h"
#include "TClass.h"
#include "TText.h"
#include "TGToolTip.h"
#include "TGLabel.h"
#include "TSpectrum.h"
#include "TGComboBox.h"

#include <iostream>
#include <iomanip> 
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#include "j_fitting.h"
#include "j_hist_formatting.h"
#include "j_ultrafit_env.h"


class j_gating_result_frame : public TGHorizontalFrame {
private:
	bool ThreeDee;
	bool RangeUpdateHold;
	
	TRootEmbeddedCanvas *fCanvas1;
	TGVerticalFrame     *resultframe,*saveframe;
	TGButtonGroup	*fBgroup1,*savebuttons;
	TGRadioButton	*fRButton1,*fRButton2,*fRButton3;
	TGCheckButton   *fCheck0,*fCheck1;
	TGHSlider    	*fHslider1;
    
    TGTextEntry *RebinText;
    
    TGHorizontalFrame* MainPanels;
    
    TGTextButton* ftbutton;
	
	TF1 *fFitFcn; 
	TText* fPeakNumText;   

	TGToolTip *fTip;
	UltraFitEnv* fFitPanel;
    
    vector< TH1* > savehists;
	vector< TGCheckButton* > savechecks;
	vector< TGTextButton* > savebutton;
	
	TH1 **fInput, **fGate, **fProj;
	double *fCentroid;
    
    double x1,x2,y1,y2;
    
	void ClearSaved();
	void ClearSavedButtons();
	
	// Have to manually specify nanoseconds, or trunacte manaully to microseconds elsewhere, or mac wont compile due the system clock prevision not matching that which is assumed
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> clicktime;
	
public:
   j_gating_result_frame();
   j_gating_result_frame(TGWindow* parent, TH1** input=nullptr, TH1** back=nullptr, TH1** proj=nullptr,double* cent=nullptr,bool threedee=false);
   virtual ~j_gating_result_frame();
   
   
   	void DoCheckbox2D();
	void ClickedFinalCanvas(Int_t,Int_t,Int_t,TObject*);
	void SavePanel();
	void FitPanel();
	void jSaveAs();
	void AddStoreHistogram();
	void CSaveButton();
	void StoreHistograms(Int_t);
	void DrawSaved();
	void NewAxisDrawn();
	
	void DrawHist();	 // Call for any update in the conditions
	void InputUpdated(); // A totally new input
    
	void ResetRange();
    void ButtonGroupDoUpdate(Int_t i);
   
	void HideSave();
   
   ClassDef(j_gating_result_frame, 1)
};



#endif
