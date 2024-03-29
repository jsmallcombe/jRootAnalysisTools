//
//
//	jROOT Tools
//	Formatting tools for TH1/2/3
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef jameshistfor_h
#define jameshistfor_h

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TVirtualPad.h>
#include <TBox.h>
#include <TLatex.h>
#include <TLine.h>
#include <TMarker.h>
#include <TROOT.h>
#include <TPolyLine.h>
#include <TGFileDialog.h>
#include <TGClient.h>
#include <TRootEmbeddedCanvas.h>
#include <TSystem.h>
#include <TFrame.h>
#include <RtypesCore.h>

#include "j_gpad_tools.h"
#include "j_fitting.h"


using namespace std;

extern bool gGlobalNegativeDraw;
extern Color_t gGlobalBackColor;
extern Color_t gGlobalForeColor;

extern Font_t gGlobalMainFont;
extern bool gGlobalDrawMenuBars;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Prepare Canvases for export as svg and subsequent conversion to pdf_latex
// The axis labes/titles alignments tend to be off if left to TAxis
// Should already be in the pad with a drawn histrogram to run these

void QuickReTexAxis(TH1* h,double stepx=0,double stepy=0);

void ReTexAxisLab(TH1* h,double step=0,bool y=false,bool flipY=false,bool noExpt=false);

void ReTexAxisTitle(TH1* h,string title="",bool y=false,double offset=0.01);

void DrawSharedTitle(string title,bool y=false,double offset=0.01);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Invert a histogram about its central bin, useful for certain fitting functions
void invert(TH1*);

//Shift the data in bin units
void transpose_bins(TH1* h, int binshift);

//Shift the axis
void transpose_axis(TH1* h, double minX=0);

//Add axis labels y="Counts/div" automatically if left blank
void axislab(TH1*,string,string="",string="");

//Add most common axis label so automated
void axislabelkev(TH1*);

//My preferred formatting options for a exporting/figure ready histogram
void hformat(TH1*,bool setminzero=1);

//Reformat a histogram into a totally different binning (obviously there is information loss)
TH1* ExtreemRebin(TH1* target,TH1* data);

//Apply chossen margins
void ReMargin(TVirtualPad*);

//Make a Canvas with desired formatting
//Can create multiple layered transparent pads
TCanvas* preapre_canvas(unsigned int n=1,bool heightset=false,bool nobar=(!gGlobalDrawMenuBars));

//Title of hist are replaced with formatted text boxes drawn in current canvas
void draw_corrected_titles(TH1* hist);

//Apply hformat  & preapre_canvas
TCanvas* DrawHformat(TH1* HH,bool setminzero);

//Prepare and draw fn for 2-hist canvases
TCanvas* preapre_canvas_bisect();
TCanvas* preapre_canvas_inset();
TCanvas* draw_hist_inset(TH1* main,TH1* inset,int pixX=-1,int pixY=-1);
TCanvas* draw_hist_bisect(TH1* bottom,TH1* top,int pixX=-1,int pixY=-1);

void AxisYWhiteBox(TVirtualPad* p=gPad,double NDCY=0.55,double NDCX=0.14);

//Draw_hist_bisect with some specific labels added
TCanvas* draw_electron_gamma(TH1* electron,TH1* gamma);

//These functions are a silly thing for linking the zooming of a bisected canvas
void PostUpdateCanvasUpdateCall(Int_t event, Int_t x, Int_t y, TObject *selected);
void RangeChangeBisectCanvasBoth();

//Get the current range of a histogram
void HistDrawnXRange(TH1* h,double& l,double& u);

//Draw a marker arrow and text
//pairpad can be used in the case of layered pads e.g from preapre_canvas 
void AddPeakLabel(double E,bool exact=false,string text="",TVirtualPad* pad=gPad,TH1* hist=0,TVirtualPad* pairpad=0);

void PadNDCtoUser(vector<double>& x,vector<double>& y,TVirtualPad* pad,bool reverse=false);
void PadNDCtoUser(double& x,double& y,TVirtualPad* pad,bool reverse=false);
void PadNDCtoUser(double& x,double& y,double* xy,bool reverse=false);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Draw formatted in a new window
TCanvas* DrawCopyCanvas(TH1* hist,bool HideErrors=true);//opt="hist" hide errors
TCanvas* DrawCanvas(TH1* hist,bool HideErrors=true,bool copy=false);
TCanvas* DrawCopyPeakClickerCanvas(TH1* hist,bool HideErrors=true);
TCanvas* DrawPeakClickerCanvas(TH1* hist,bool HideErrors=true,bool copy=false);

//Draw with or without errors (but with functions) in current pad
TH1* DrawHistOpt(TH1* hist,bool HideErrors=false,bool Copy=false,bool Same=false);
TH1* DrawCopyHistOpt(TH1* hist,bool HideErrors=true);

TGraph* DrawGraphOpt(TGraph* hist,bool Copy=false,bool Same=false,bool Point=false);
TGraph* DrawCopyGraphOpt(TGraph* hist,bool point=false);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TString HistSaveAs(TH1* hist, TGWindow *window=0,TPad* pad=0);
TFile* RootFileLoad(TGWindow *window=0);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CanvasNegativeFull(TVirtualPad* fPad=gPad);
void CanvasNegative(TVirtualPad* fPad=gPad);
void HistogramNegative(TH1* Hist);
void GraphNegative(TGraph* Graph);

void SetGlobalNegative(bool negative=true);


#endif // #ifdef jameshistfor_h
