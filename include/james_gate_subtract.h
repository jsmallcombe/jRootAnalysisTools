//
//
//	James Root Library
//	Functions for handling root TH2/TH3 projection/gating in desired way
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef james_gate_n_subtract
#define james_gate_n_subtract

#include <iostream>
#include <cmath>
#include <vector>

#include <TAxis.h>
#include <TH3.h>
#include <TH2.h>
#include <TH1.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/////////// Functions gating and subtracting TH2 and TH3   /////////// 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

//3D gating functions


TAxis* hist_gater(TH3F*,string&,int);
TAxis* hist_proj(TH3F*,string&,int);


//these will nicely overwrite any previously done projection OF THE SAME TYPE
//if you dont want that add a name in string
TH2F* hist_gater(double,double,TH3F*,int=0,string="");
TH2F* hist_gater_bin(int,int,TH3F*,int=0,string="");
TH2F* hist_gater(double,TH3F*,int=0,string="");// gates from input to axis max
TH2F* hist_gater_bin(int,TH3F*,int=0,string="");
TH2F* hist_gater_anti(double,double,TH3F*,int=0,string="");//return an anti gated hist
TH2F* hist_gater_anti_bin(int,int,TH3F*,int=0,string="");

//2D gating functions
//these will nicely overwrite/fill any previously done 2D projection add a name in string
TH1F* hist_gater(double,double,TH2F*,int=0,string="proj");
TH1F* hist_gater_bin(int,int,TH2F*,int=0,string="proj");
TH1F* hist_gater(double,TH2F*,int=0,string="proj");// gates from input to axis max
TH1F* hist_gater_bin(int,TH2F*,int=0,string="proj");
TH1F* hist_gater_anti(double,double,TH2F*,int=0,string="proj");//return an anti gated hist
TH1F* hist_gater_anti_bin(int,int,TH2F*,int=0,string="proj");

// Project an axis Functions
//these will nicely overwrite/fill any previously done 2D projection add a name in string
TH1F* hist_proj(TH3F*,int=0,string="proj");
TH1F* hist_proj(TH2F*,int=0,string="proj");
TH1F* hist_proj_flowless(TH3F*,int=0,string="proj");
TH1F* hist_proj_flowless(TH2F*,int=0,string="proj");



//addition/subtraction functions 
//Work for th2 and 3 inherited classes
TH1* scaled_back_subtract(TH1*,TH1*,double,double=0);
TH1* scaled_back_subtract(TH1*,TH1*,double,TH1*,double=0);

inline TH1* scaled_addition(TH1*h1,TH1*h2,double f,double ff=0){return scaled_back_subtract(h1,h2,-f,ff);}
inline TH1* scaled_addition(TH1*h1,TH1*h2,double f,TH1*h3,double ff=0){return scaled_back_subtract(h1,h2,-f,h3,ff);}


void TH3axisreseter(TH3*);


//Created this class to save on extra maths waste adjusting large histograms
//via the limited public functions
class TH1ErrorAdj : public TH1{
public:
	TH1ErrorAdj():TH1(){};
	~TH1ErrorAdj(){};
	void AdjustError(const TH1* back,double frac);
	ClassDef(TH1ErrorAdj, 1)	
};
#endif 