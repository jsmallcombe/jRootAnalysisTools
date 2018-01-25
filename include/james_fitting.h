//
//
//	James Root Library
//	Functions automated peak fitting
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef james_fitting_h
#define james_fitting_h

// C++

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <sstream>

#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH3.h>
#include <TH2.h>
#include <TH1.h>
#include <TMatrixDSym.h>
#include <TFitResult.h>
#include <TList.h>

#include "Math/MinimizerOptions.h"

#include "james_utility.h"
#include "james_fitholder.h"
#include "Math/MinimizerOptions.h"

using namespace std;

//Using user coordinates
//hist,centroid,user range left,user range right
//Range is absolute, not relative
TF1* UserQuickSingleGausAutoFit(TH1*,double,double=0,double=0,int=0);//Fixed & linear back
TF1* UserQuickSingleGausAutoFitE(TH1*,double,double=0,double=0,int=0);//Free & linear back
TF1* UserQuickSingleGausAutoFitEE(TH1*,double,double=0,double=0,int=0);//Free & pol2 background

//Using bin number
//hist,bin centroid, bin range left,bin range right
//Range is absolute, not relative
TF1* QuickSingleGausAutoFit(TH1*,int,int,int,int=0);//Fixed & linear back
TF1* QuickSingleGausAutoFitE(TH1*,int,int,int,int=0);//Free & linear back
TF1* QuickSingleGausAutoFitEE(TH1*,int,int,int,int=0);//Free & pol2 background


///////////////////////////////////////////////////////
////////////////// Ultra peak fit /////////////////////
///////////////////////////////////////////////////////

typedef struct jPeakDat{
	double Centroid;// seperation
	bool CentConstrained;// false, error ignored
	double CentError;// <=0 fixed param
	double Ratio;// <=0 unused
	double RatioError;// <=0 fixed param
	jPeakDat(double c,bool cb=0,double ce=0,double r=0,double re=0):
	Centroid(c),CentConstrained(cb),CentError(ce),Ratio(r),RatioError(re){}// default Constructor
} jPeakDat;



//////////////////////////////////////////////////
//	FUNCTIONS COMPLEMENTARY TO PEAK FITTING	//
//////////////////////////////////////////////////

//
// Finds the local maximum bin of a histogram and returns its value (for lazy peak selection)
// Climbs from input, stops at any decrease (so bad in grassy spectra)
// Returns the height at the max
//
double FindLocalMax(TH1* fHist,double& fPeak);//This version is in user coordinates
double FindLocalMax(TH1* fHist,int& fPeak,int fLeft,int fRight);//This version is in bin number
// Range is absolute, not relative
	
//Absolute max in +-range
double FindBinRangeMaxD(TH1* fHist,double& fPeak,double range);
double FindBinRangeMax(TH1* fHist,int& fPeak,int range);

//
// Given peak bin, fit bins down, fit bins up: optimises those values for peak fitting
// Finds peak bin local maximum
// Reduces fitting range where there is a large rise near peak.
//
// // Internally does a background subtraction of Hist for better results, input hist unchanged
// Maybe too intensive to use in loops
//
// Uses FindLocalMax, returns the same.
//
// Range is absolute, not relative
double FitPositionOptimisation(TH1*,int&,int&,int&);

// Quick function to get a average around a bin of a histogram
// Useful when quantifying backgrounds
double bins_smooth(TH1*,double);//user coordinates 
double bins_smooth(TH1*,int,int);//bin #, # bins to sample

//The variance on the value from the above bins_smooth function
double bins_var(TH1*,int,int);//bin #, # bins to sample

//Adds errors to zero bins so they are fit normally
void ZeroBinsFitFix(TH1*);

//
// Does a quick background subtraction (very smooth) input unchanged
//
TH1* SmoothOffBack(TH1*);

//
// Automated fitting loop for functions that dont converge easily
//
template<typename T>
bool fitrep(T* HG,TF1* fit,string opts="QRB0NM", int reps=10){
	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(10000);
	for(int i=0;i<reps;i++){
		int status=(int)HG->Fit(fit,opts.c_str());
		if(0==status||4000==status)return true;
	}
	cout<<" Failed fit"<<endl;
	return false;
}




#endif 
