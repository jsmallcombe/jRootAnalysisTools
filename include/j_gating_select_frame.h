//
//
//	jROOT Tools
//	Very rough copy of j_gating_frame for selection only, no actual gating
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef j_gating_select_frame_h
#define j_gating_select_frame_h


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

class j_gating_select_frame : public TGVerticalFrame {

private:
	TGLayoutHints* fBly;
	TRootEmbeddedCanvas *fCanvas1;
	TF1                 *fFitFcn;
	TGHorizontalFrame   *fHframe0, *fHframe1, *fHframe2, *fHframe3;
	TGTripleHSlider	*fHslider1;
	TGHSlider    	*fHslider2,*fHslider3;
	TGDoubleHSlider	*fHslider4;
	TGTextEntry         *fTeh1, *fTeh2, *fTeh3;
	TGTextBuffer        *fTbh1, *fTbh2, *fTbh3;
	TGCheckButton       *fCheck2,*fCheck1,*fCheck0;
	TGButtonGroup	*fBgroup2;
	TGRadioButton *fRButton4,*fRButton5,*fRButton6,*fRButton7,*fRButton8,*fRButton9;
	TGComboBox *BackModeDrop;
	
	TH1 *raw_input; 
	TH1 *proj,*selected,*b_man,*specback;
	
	TText* peaknumremove;
	
// 	TSpectrum spec;
	
	//	CONTROL VALUES

	int background_mode;
	int backfit_mode;
	int axis_down,axis_up;  
	int gate_down,gate_up;
	int gate_range;
	int fit_down,fit_up;
	int m_back_down,m_back_up;
	Long64_t target_bin;
	double backfrack;
	double backfrackfrac;
	bool action_hold; 
	int back_down,back_up;
	bool SubtractGateFromBack;

	double storef1,storef2;
	
	TGToolTip *fTip;

	//Internal methods
	void NewAxisDrawn();
	void ValidateValues();
	void FetchSliderValues() ;
	void ValuesToSliders();
	void FetchTextValues();
	void ValuesToText();
	void UpdateSpecBack();

	void DoAutoFit();
	void UpdateDraw(bool overlay=false);
	
	string suffix;

public:
   j_gating_select_frame();
   j_gating_select_frame(TGWindow* parent, TH1* input=0);
   virtual ~j_gating_select_frame();
   
   TGVerticalFrame   *fHframe4;

   //Functions connected to GUI "slot"
//    void CloseWindow();
	void UpdateCanvas();
   void DoText();
   void DoSlider();
   void DoSlidePoint();
   void ChangeBackMode(const Int_t);
   void ChangeBackFit(const Int_t);
   void ReDrawOne();
   void ClickedCanvasOne(Int_t,Int_t,Int_t,TObject*);
   void DoHistogram();
      
   TH1 *output_hist_point;
   TH1 *gate_hist,*full,*free_hist;
   
   double GateCentre;
   
   void UpdateInput(TH1*);
   void UpdateInput();


   //signals has to be public
   void OutputReady(){};  
   void InputChange(){}; 
   
   void TickClick();
   
   int GetGateBinDown(){return gate_down;}
   int GetGateBinUp(){return gate_up;}
   int GetBackBinDown(){return back_down;}
   int GetBackBinUp(){return back_up;}
   double GetBackFrac(){return backfrack;}
   bool SubtractGate(){return SubtractGateFromBack;}

   
   ClassDef(j_gating_select_frame, 1)
};

#endif
