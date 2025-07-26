//
//
//	jROOT Tools
//	Independent panel for determining background subtraction requirements from 1D projections, designed to be built into other tools using various signal-slots. Various gating globals live here.
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
//

#ifndef jGatingSelectFrame_h
#define jGatingSelectFrame_h

#include "TGTextEntry.h"
#include "TGSlider.h"
#include "TGTripleSlider.h"
#include "TSpectrum.h"
#include "TGComboBox.h"

#include "j_fitting.h"
#include "j_hist_formatting.h"

extern bool gGlobalAskGateWindowName;
void SetGlobalAskWindowName(bool set=true);

extern bool gGlobalTH3UpdateLock;
void SetGlobalTH3UpdateLock(bool set=true);

extern bool gGlobalTH3UseHead;
void SetGlobalTH3UseHead(bool set=true);

extern bool gGlobalOverflowBool;
void SetGlobalOverflowInclude(bool set=true);

extern bool gGlobalUnderlowBool;
extern unsigned short gGlobalLowestBin;
void SetGlobalUnderflowInclude(bool set=true);

extern double gGlobalSubtractionFractionError;
void SetGlobalSubtractionFractionError(double set=0.04);


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
	TGTextEntry* NdimText;
	
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
	
	int Ndim;
	int NdimSel;		
    int RebinFactor;

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
	void DoNdimText();

	void DoAutoFit();
	void UpdateDraw(bool overlay=false);
	
	static int jgating_iterator;
	
protected:
	int xyz;

public:
   jGateSelectFrame();
   jGateSelectFrame(TGWindow* parent, TH1* input=nullptr, int Ndim=0);
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
   void NdimPlus();
   void NdimMinus();
   
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




#endif
