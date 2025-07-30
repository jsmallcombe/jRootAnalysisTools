//
//
//	jROOT Tools
//	Selection of independent graphical tools for analysing/manipulating/viewing histograms
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
//

#ifndef jamesextragui_h
#define jamesextragui_h

#include <TF2.h>

#include "j_hist_formatting.h"
#include "j_env.h"


// RQ_OBJECT("MyClass") inside the MyClass body (IF MyClass not inherited from TQObject) allow class to use signal/slot communication

// Tool for automatically scaling a TH1/TH2 based on a TGraph/TF1
class jScale : public TGMainFrame {

private:
	CCframe *fCanvas1,*fCanvas2;
	TRootEmbeddedCanvas *result;
    TGraph *gg;
    TF1 *ff;
    TH1 *hh;
    TString gfname;
    TGTextButton* lockbutton;
    TGTextButton* invertbutton;
    TGTextButton* normbutton;
    bool IsLocked;
    bool IsInvert;
    bool IsNorm;
		
	Pixel_t red, black;
    
public:
	jScale();
	virtual ~jScale(){
        if(gg)delete gg;
        if(ff)delete ff;
        if(hh)delete hh;
    };
    
	void NewFunc(TObject*);
	void NewHist(TObject*);
	double Eval(double x);
	void NewInput();
    void Lock();
    void Invert();
    void Norm();
	
	static void GlobalNewScale(){new jScale;}

	ClassDef(jScale, 3)
};

// Graphical tool for running TGraph::Eval and TF1::Eval
// example use case, extracting multiple efficiency values from a curve
class jEval : public TGMainFrame {

private:
	CCframe *fCanvas1;
    TGraph *gg;
	TF1* ff;
    TGTextButton* lockbutton;
    bool IsLocked;
    TGTextEntry *fTeh1,*fTeh2;
    double Xin;
	
    void Eval();
	
public:
	jEval();
	virtual ~jEval(){
        if(gg)delete gg;
        if(ff)delete ff;
    };
    
	void NewInput(TObject*);
    void Lock();
    void Input(char*);
	
	static void GlobalNewEval(){new jEval;}

	ClassDef(jEval, 2)
};


// Tool for projecting TH2s at arbitrary angles, graphical cuts can be included
class jAngleAngel : public TGMainFrame {

private:
	TRootEmbeddedCanvas *fCanvas1;
	TH2* fHistHigh;
	TH2* fHistLow;
	TH2* fHist;//doesnt exist;
	TGHSlider* fHslider;
	TLine fLine;
	int Nl;
	bool lock;
	int sliderpos;
	TStopwatch Stop;
	void DoLines();
	
    TGTextButton *fButton;
    TGTextButton *fButtonEnd;
    TGTextButton *fButtonUnuse;
    TGraph *fCurrentCutG; // Pointer to store the current TCutG
    bool fCutSetting; // Flag to indicate if the setting cut is active
    bool fCutActive; // Flag to indicate if the setting cut is active
    
    void RemoveGraphs();
    
public:
	jAngleAngel(TH1* fH=0);
	virtual ~jAngleAngel();
    
	void SetCapture(TH1 *fH);
	void SetNewHist(TH1 *fH);
	void SliderChange();
	void SliderRelease();
	void NewRange();
	
	void MakeHist(double=0);
	void MakeHist90(){MakeHist(TMath::Pi()*0.5);};
    
	
    void HandleEvent(Int_t event, Int_t px, Int_t py, TObject *selected);
    void StartCutButtonPressed();

    void FinaliseCut();
    void UnUseCut();
	
    TGraph* GetCut() const {
        return fCurrentCutG;
    }
    
	static void GlobalNewAngleAngel(){new jAngleAngel;}
    
	ClassDef(jAngleAngel, 2)
};


// 2D Gaussian semi-automated fitter, written for a very specific alpha calibration, in need of generalisation
class j2DAlphaCalibrator : public TGMainFrame {

private:
	TRootEmbeddedCanvas *fCanvas1;
	TH2* fHist;
    double X,Y;
    vector<double> saveX,saveY;
    TF2 *g2;
    TF1 *lincal;
public:
	j2DAlphaCalibrator(TH1* fH=0,double sig=11);
	virtual ~j2DAlphaCalibrator();
    
	void SetNewHist(TH1 *fH);
    void Fit2DPeak(Int_t,Int_t,Int_t,TObject*);
    void SaveXY(){
        saveX.push_back(X);
        saveY.push_back(Y);
    };
    void Reset(){
        saveX.clear();
        saveY.clear();
    }
    void CalibrateAlpha();

    double sigma;
    
	ClassDef(j2DAlphaCalibrator, 0)
};

// Quick integrator by mouse click TH1
class jIntegrator : public TGMainFrame {

private:
	TRootEmbeddedCanvas *fCanvas1;
	TH1* fHist;
    int X1,X2;
    double x1,x2;
	bool first;
public:
	jIntegrator(TH1* fH=0);
	virtual ~jIntegrator();
    
	void SetNewHist(TH1 *fH);
    void Integrate(Int_t,Int_t,Int_t,TObject*);
	
	static void GlobalNewIntegrator(){new jIntegrator;}

	ClassDef(jIntegrator,1)
};

// TCanvas that automatically highlights Histograms on mouse-over
// Useful for viewing multiple overlaid histograms 
class jCompCanvas : public TCanvas {
	
private:
	Short_t ReCol;
	UShort_t ReColI;
	static UShort_t ColBase[6];
	bool ColInit;
	void ResetView();
	UShort_t Colour(UShort_t Col=0);
	void ChangeHistColour(TH1*);
	void HighlightHist(TH1*);
	void HighlightGraph(TGraph*);
	TPad* CurrentPad;
	
public:
	jCompCanvas(TH1 *fH=nullptr,Option_t * option = "");
    virtual ~jCompCanvas();
	
	void MouseEvent(Int_t e,Int_t x,Int_t y,TObject* ob);
	
		
	ClassDef(jCompCanvas,1)
};


#endif
