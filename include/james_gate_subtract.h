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
#include <TClass.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/////////// Functions gating and subtracting TH2 and TH3   /////////// 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

//3D gating functions


TAxis* hist_gater(TH3*,string&,int);
TAxis* hist_proj(TH3*,string&,int);


//these will nicely overwrite any previously done projection OF THE SAME TYPE
//if you dont want that add a name in string
TH2* hist_gater(double,double,TH3*,int=0,string="");
TH2* hist_gater_bin(int,int,TH3*,int=0,string="");
TH2* hist_gater(double,TH3*,int=0,string="");// gates from input to axis max
TH2* hist_gater_bin(int,TH3*,int=0,string="");
TH2* hist_gater_anti(double,double,TH3*,int=0,string="");//return an anti gated hist
TH2* hist_gater_anti_bin(int,int,TH3*,int=0,string="");

//2D gating functions
//these will nicely overwrite/fill any previously done 2D projection add a name in string
TH1* hist_gater(double,double,TH2*,int=0,string="proj");
TH1* hist_gater_bin(int,int,TH2*,int=0,string="proj");
TH1* hist_gater(double,TH2*,int=0,string="proj");// gates from input to axis max
TH1* hist_gater_bin(int,TH2*,int=0,string="proj");
TH1* hist_gater_anti(double,double,TH2*,int=0,string="proj");//return an anti gated hist
TH1* hist_gater_anti_bin(int,int,TH2*,int=0,string="proj");

//These just forward to the correct above type after checking TH2/3 inheritance 
TH1* hist_gater(double,double,TH1*,int,string);
TH1* hist_gater_bin(int,int,TH1*,int,string);
TH1* hist_gater(double,TH1*,int,string);
TH1* hist_gater_bin(int,TH1*,int,string);
TH1* hist_gater_anti(double,double,TH1*,int,string);
TH1* hist_gater_anti_bin(int,int,TH1*,int,string);


// Project an axis Functions
//these will nicely overwrite/fill any previously done 2D projection add a name in string
TH1* hist_proj(TH1* in,int xyz=0,string name="proj",bool flowless=false);


//addition/subtraction functions 
//Work for th2 and 3 inherited classes
TH1* scaled_back_subtract(TH1*,TH1*,double,double=0,bool scale=true);
TH1* scaled_back_subtract(TH1*,TH1*,double,TH1*,double=0,bool scale=true);

inline TH1* scaled_addition(TH1*h1,TH1*h2,double f,double ff=0,bool scale=true){return scaled_back_subtract(h1,h2,-f,ff,scale);}
inline TH1* scaled_addition(TH1*h1,TH1*h2,double f,TH1*h3,double ff=0,bool scale=true){return scaled_back_subtract(h1,h2,-f,h3,ff,scale);}


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
