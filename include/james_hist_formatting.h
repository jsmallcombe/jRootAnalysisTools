//
//
//	James Root Library
//	Formatting tools for TH1/2/3
//	05 Mar 2017
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

#include "james_gpad_tools.h"
#include "james_fitting.h"

using namespace std;

//Add axis labels y="Counts/div" automatically if left blank
void axislab(TH1*,string,string="",string="");

//Add most common axis label so automated
void axislabelkev(TH1*);

//My preferred formatting options for a exporting/figure ready histogram
void hformat(TH1*,bool setminzero=1);

//Reformat a histogram into a totally different binning (obviously there is information loss)
TH1* ExtreemRebin(TH1* target,TH1* data);

//Make a Canvas with desired formatting
//Can create mutliple layered transparent pads
TCanvas* preapre_canvas(unsigned int n=1);

//Title of hist are replaced with formatted text boxes drawn in current pad
void draw_corrected_titles(TH1* hist);

//Apply hformat preapre_canvas & preapre_canvas
TCanvas* DrawHformat(TH1* HH,bool setminzero);

//Prepare and draw fn for 2-hist canvases
TCanvas* preapre_canvas_bisect();
TCanvas* preapre_canvas_inset();
TCanvas* draw_hist_inset(TH1* main,TH1* inset);
TCanvas* draw_hist_bisect(TH1* bottom,TH1* top);

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


#endif // #ifdef jameshistfor_h
