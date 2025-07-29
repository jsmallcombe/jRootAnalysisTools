//
//
//	jROOT Tools
//	Functions for use in automated peak fitting
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
//

#ifndef j_fitting_2D_h
#define j_fitting_2D_h

#include "j_env_extratools.h"

using namespace std;


/////////////////////////


class jFittingFrame2D : public TGVerticalFrame {
private:
	TRootEmbeddedCanvas *fCanvas1;
	TH2* fHist;
    double sigmaX,sigmaY;
    double rangeX,rangeY;
    vector<double> saveX,saveY;
    TF2 *g2;
	bool TextSlideBlock;
	int Nslide;
	
	TGHSlider *fHslider1, *fHslider2;
	TGTextEntry *fTextEntry1, *fTextEntry2;
	TGCheckButton* fCheckY;
	
	void Fit2DGaus(double x, double y);
	void DrawHelpers(double x, double y);
	
public:
	jFittingFrame2D(TGWindow * parent=0, TH2* fH=0,double sigx=0,double sigy=0);
	virtual ~jFittingFrame2D();
    
	void SetNewHist(TH2 *fH);
	
    void Fit2DPeak(Int_t,Int_t,Int_t,TObject*);
	
    void SaveXY(){
//         saveX.push_back(X);
//         saveY.push_back(Y);
    };
    void Reset(){
		SetNewHist(fHist);
    }

	void SetSliderX(const char*);
	void SetSliderY(const char*);
	void SetText();
	void EnableSigmaY();
    
	ClassDef(jFittingFrame2D, 0)
};

/////////////////////////

class jFittingTool2D : public TGMainFrame {
	private:
	jFittingFrame2D *fFrame;

public:
	jFittingTool2D(TH2* fH=0,double sigx=0,double sigy=0);
	virtual ~jFittingTool2D();
	
	void NewInput(TH2* h){
		fFrame->SetNewHist(h);
	}
	
	ClassDef(jFittingTool2D, 0)
};

#endif 
