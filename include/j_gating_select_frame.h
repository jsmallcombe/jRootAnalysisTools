//
//
//	jROOT Tools
//	Very rough copy of j_gating_frame for selection only, no actual gating
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef jGatingSelectFrame_h
#define jGatingSelectFrame_h

#include "TROOT.h"
#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"
#include "TGLayout.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGTextEntry.h"
#include "TGSlider.h"
#include "TGTripleSlider.h"
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

extern bool gGlobalAskWindowName;
void SetGlobalAskWindowName(bool set=true);

class jGateSelectFrame : public TGVerticalFrame {

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

	int maxbin;
	int background_mode;
	int backfit_mode;
	int axis_down,axis_up;  
	int gate_down,gate_up;
	int gate_range;
	int fit_down,fit_up;
	int m_back_down,m_back_up;
	Long64_t target_bin;
	double backfrac;
	double backfracfrac;
	bool action_hold; 
	int back_down,back_up;
	bool SubtractGateFromBack;
	
	int set_for_3D;
    int RebinFactor;
	int xyz;

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
	
	static int jgating_iterator;

public:
   jGateSelectFrame();
   jGateSelectFrame(TGWindow* parent, TH1* input=nullptr, int ThreeDee=0);
   virtual ~jGateSelectFrame();
   
   
	static int Iterator(){jgating_iterator++;return jgating_iterator;};
	static TString Iterator(TString in){return in+=Iterator();};
   
   
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
   
   double GateCentre;
   
   void UpdateInput(TH1*);
   void UpdateInput();

   void RebinPlus();
   void RebinMinus();
   
   //Input signals has to be public
   void ChangeProjection(const Int_t);

   void TickClick();
   
   int GetGateBinDown(){int ret=(gate_down-1)*RebinFactor+1;
	   if(ret<0)return 0;
	   return ret;
	}
   int GetGateBinUp(){int ret=gate_up*RebinFactor;
	   if(ret>maxbin)return maxbin+1;
	   return ret;
	}
   int GetBackBinDown(){int ret=(back_down-1)*RebinFactor+1;
	   if(ret<0)return 0;
	   return ret;
	}
   int GetBackBinUp(){int ret=back_up*RebinFactor;
	   if(ret>maxbin)return maxbin+1;
	   return ret;
	}
   int GetXYX(){return xyz;}
   double GetBackFrac(){return backfrac;}
   double GetBackFracFrac(){return backfracfrac;}
   int GetBackMode(){return background_mode;}
   bool SubtractGate(){return SubtractGateFromBack;}
   double* PointGateCentre(){return &GateCentre;}
   
   void HideManBar();
	
   void Update3D(){
	Emit("UpdateClicked()");
   }
   
// signals:
	void OutputReady();
	void RequestProjection(Int_t);
	void UpdateClicked();
	void BackModeChange();
   
   ClassDef(jGateSelectFrame, 2)
};



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// But in a base level class of the gating classes so TH3 and THnSparse classes will both have use of it.
// Could be relocated to >2D class if the they are unified later 

TGTransientFrame* MakeTH3Popup(const TGWindow* window=gClient->GetRoot());

#endif
