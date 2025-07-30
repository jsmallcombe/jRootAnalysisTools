//
//
//	jROOT Tools
//	Gamma Efficiency Curve Functions
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
//
#ifndef eff_func_h
#define eff_func_h

#include <TGraphErrors.h>

#include "Math/MinimizerOptions.h"

#include "j_fitting_fitholder.h"



// Fit all of the below functions
vector<TF1*> MegaEffAuto(TGraphErrors * graph);
vector<FullFitHolder*> MegaEffAutoFH(TGraphErrors * graph);

//
// These function do all the needed pre work 
// take the output fn and do a final fit to get the error matrix 
// "E" option gives better errors (recommended)
// TFitResultPtr fResult=graph->Fit(TF!,"RSE+");
// TMatrixD matrix =fResult->GetCovarianceMatrix()
//

//Return a "scaleradeff" fit to the data.
TF1* auto_radeff_scaled(TGraphErrors * graph,bool byparts=false);// USE THIS ONE

//Return a "scaleradeff" OR "radeff" fit by parts
TF1* radeff_by_parts(TGraphErrors * graph,bool scaled);
//scaleradeff scale parameter is returned fixed

//Returns a "stefeff" fit to data
TF1* prepare_stefeff(TGraphErrors * graph);

//Returns a "GosiaWoodsac" fit to data
TF1* prepare_gosiaA(TGraphErrors * graph);

//Returns a "GosiaAdhoc" fit to data
TF1* prepare_gosiaB(TGraphErrors * graph);


//
// Under the hood functions
//

extern double radeffscadef[7];
TF1* rad_eff_scaled(TGraphErrors * graph);//Return a "scaleradeff" with some default values.
TF1* rad_eff();//Return a "radeff" with some default values.

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
////////////////// FUNCTION DEFINITIONS ////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

//The 7 parameter radware gamma effciency function for TF1 use
inline Double_t radeff(Double_t *x, Double_t *par){
	
	if(x[0]<1)return 0;
	
        double xx=log(x[0]/100.);
        double yy=log(x[0]/1000.);
	
	double AA=(par[0]+xx*par[1]);
        double BB=(par[2]+yy*par[3]+yy*yy*par[4]);

	double a=0,b=0,c=0,d=0;
	double G=abs(par[5])+2;//dont let it be less than ^2
	
	if(AA>0)a=1/pow(AA,G);
	if(BB>0)b=1/pow(BB,G);	
	c=a+b;
	if(c>0)d=1./pow(c,1./G);
	
	if((AA<log(1000)&&abs(AA)>0)||d<log(1000))return 0;
	
	double ret=(exp(d)/1000.0)-1;//Because function only works in stupid range
// 	if(ret<0)return 0;
	return ret;
	
}

//A 7 parameter scaled radware gamma efficiency function for TF1 use
inline Double_t scaleradeff(Double_t *x, Double_t *par){
	double ret=radeff(x,par)*abs(par[6]);
// 	if(ret<0)ret=0;
	return ret;
	
}

//A 4 parameter simple gamma efficiency function for TF1 use
inline Double_t stefeff(Double_t *x, Double_t *par){
	
	if(x[0]<1)return 0;
	
        double xx=x[0];
        double yy=log10(x[0]);
	
	double a=par[0]*yy+par[1]*yy*yy+par[2]/(xx*xx);
	
	double d=pow(10,a);
	
	if(d<0)return 0;

	return d*par[3];
}

//A 5 parameter simple gamma efficiency function for TF1 use
inline Double_t stefeffwonky(Double_t *x, Double_t *par){
	
	if(x[0]<1)return 0;
	
        double xx=x[0];
        double yy=log10(x[0]);
	
	double a=par[0]*yy+par[1]*yy*yy+par[2]/(xx*xx);
	
	double d=pow(10,a);
	
	if(d<0)return 0;

	return d*(par[3]+par[4]*x[0]);
}


//A 3 parameter high energy gamma efficiency function from gosia gremlin
inline Double_t GosiaHigh(Double_t *x, Double_t *par){
	if(x[0]<1)return 0;
        double xx=log(x[0]/50.);
	double ret=0;
	for(int i=0;i<4;i++){
		ret+=par[i]*pow(xx,i);
	}
	return exp(ret);
}

//A 5 parameter gamma efficiency function from gosia gremlin
inline Double_t GosiaAdhoc(Double_t *x, Double_t *par){
	if(x[0]<1)return 0;
	double xx=log(x[0]/50.);
	return GosiaHigh(x,par)*exp(-abs(par[4])/pow(xx,abs(par[5])+1));
}

//A 5 parameter gamma efficiency function from gosia gremlin
inline Double_t GosiaWoodsac(Double_t *x, Double_t *par){
	return GosiaHigh(x,par)/(1.0+exp((abs(par[4])-x[0])/abs(par[5])));
}

#endif
