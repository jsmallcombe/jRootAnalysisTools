//
//
//	James Root Library
//	A root GUI panel for TH2/TH3 gating & subtraction, designed to be built/packages into other tools/applets 
//	06 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef j_gating_frame_h
#define j_gating_frame_h


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


#include <iostream>
#include <iomanip> 
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#include "james_gate_subtract.h"
#include "james_fitting.h"

enum commandidentifiersjgatingtool {
   HId1,
   HId2,
   HId3,
   HCId1,
   HCId2,

   HSId1,
   HSId2,
   HSId3,
   HSId4,
};

class j_gating_frame : public TGVerticalFrame {

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
	TGButtonGroup	*fBgroup1,*fBgroup2;
	TGRadioButton	*fRButton1,*fRButton2,*fRButton3,*fRButton4,*fRButton5,*fRButton6,*fRButton7,*fRButton8,*fRButton9,*fRButtonz;
	TGTextButton		*fTButton1;
	
	TH1 *raw_input; 
	TH1 *proj,*proj_flow,*selected,*b_man;
	
	TText* peaknumremove;
	
	//	CONTROL VALUES

	int background_mode;
	int xyz;  
	int axis_down,axis_up;  
	int gate_down,gate_up;
	int gate_range;
	int fit_down,fit_up;
	int m_back_down,m_back_up;
	int target_bin;
	double backfrack;
	double backfrackfrac;
	bool action_hold; 
	bool set_for_3D;

	double manual_frac_store,storef1,storef2;
	
	TGToolTip *fTip;

	//Internal methods
	void NewAxisDrawn();
	void ValidateValues();
	void FetchSliderValues() ;
	void ValuesToSliders();
	void FetchTextValues();
	void ValuesToText();

	void DoAutoFit();
	void DoHistogram();
	
	string suffix;

public:
   j_gating_frame();
   j_gating_frame(TGWindow*,TH1*,string="");
   virtual ~j_gating_frame();
   
   TGVerticalFrame   *fHframe4;
   
   bool hidebinerrors;

   //Functions connected to GUI "slot"
//    void CloseWindow();
	void UpdateCanvas();
   void DoText();
   void DoSlider();
   void SliderRelease();
   void DoSlidePoint();
   void HandleButtons();
   void ChangeProjection(const Int_t);
   void ChangeBackMode(const Int_t);
   void ReDrawOne();
   void ClickedCanvasOne(Int_t,Int_t,Int_t,TObject*);
   void ShowFullProj();
   void HideFullProj();
      
   TH1 *output_hist_point;
   TH1 *gate_hist,*full,*free_hist;
   
   double GateCentre;
   
   void UpdateInput(TH1*);
   void UpdateInput();


   //signals has to be public
   void OutputReady(){};  
   
   ClassDef(j_gating_frame, 2)
};

#endif
