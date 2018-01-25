//
//
//	James Root Library
//	Class for fitting of tailed gaussians with step and polynomail background
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef ultrapeak_func_h
#define ultrapeak_func_h

#include "james_utility.h"
#include "james_fitting.h"

#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH3.h>
#include <TH2.h>
#include <TH1.h>
#include <TMatrixDSym.h>
#include <TFitResult.h>
#include <TList.h>

#include <cmath>
#include <TMath.h>

#include <iostream>
using namespace std;

// The following peak functions are written in many parts to make the maths transparent

////////////////////////////////////////////////////
// Basic Gaussian centred at zero and height 1    //
////////////////////////////////////////////////////

const short gPeakBackA=0;
const short gPeakBackB=1;
const short gPeakBackC=2;
const short gPeakBackD=3;
const short gPeakSigma=4;
const short gPeakDecay=5;
const short gPeakSigmaB=gPeakDecay;
const short gPeakSharing=6;
inline short gPeakNH(unsigned short i){return i*2+7;}
inline short gPeakNC(unsigned short i){return i*2+8;}


inline double UniGaus(double& x,double& sig){return exp(-((x*x)/(sig*sig*2)));}

// CFD
inline double UniGausCFD(double& x,double& sig){return 0.5*(1+TMath::Erf(x/(sig*sqrt(2))));}

// Unit step for background
inline double UniGausStep(double& x,double& sig){return 1-UniGausCFD(x,sig);}

inline double UniGausArea(double& sig){return sig*sqrt(2*TMath::Pi());}

///////////////////////////////////////////////////////
// Exponential starting at zero decaying negatively  //
// Convolved with Gaussian broadening 		     //
///////////////////////////////////////////////////////

inline double DecGaus(double& x,double& sig,double& dec){return exp(x/dec)*TMath::Erfc(x/(sig*sqrt(2)) + sig/(dec*sqrt(2)));}

inline double DecGausCFD(double& x,double& sig,double& dec){return 0.5*(1 + exp((x/dec) + ((sig*sig)/(2*dec*dec)))*TMath::Erfc(((dec*x) + (sig*sig)) /(dec*sig*sqrt(2)))+TMath::Erf(x/(sig*sqrt(2))));}

inline double DecGausStep(double& x,double& sig,double& dec){return 1-DecGausCFD(x,sig,dec);}

inline double DecGausArea(double& sig,double& dec){return 2*dec*exp(-((sig*sig)/(2*dec*dec)));}

//An analytical approach to the X value of peak maximum, valid in the range sigma 0.1-10 decay 1-100
inline double DecGausMaxX(double& sig,double& dec){
	double a=1.39065*pow(dec,0.785742);
	a+=dec*-0.429206;
	a+=dec*dec*0.000356727;
	a+=dec*dec*dec*-3.08765e-8;
	
	double b=1.93679*pow(dec,0.920522);
	b+=dec*-0.819016;
	b+=dec*dec*-0.00515282;
	b+=dec*dec*dec*4.87915e-05;
	b+=dec*dec*dec*dec*-1.77445e-07;
	
	return (exp(-sig/a)-1)*b;
}

///////////////////////////////////////
//    Combining the two peaks	     //
///////////////////////////////////////

// Returns the two peaks in their nominal form summed
inline double CombRDpeak(double& x,double& sig,double& dec,double& eta){return UniGaus(x,sig)*eta+DecGaus(x,sig,dec)*(1-eta);}

// Returns the two peak steps in their nominal form summed
// A single sharing parameter from 0-1
inline double CombRDstep(double& x,double& sig,double& dec,double& b1){return UniGausStep(x,sig)*b1+DecGausStep(x,sig,dec)*(1-b1);}

// Given the usual 0-1 sharing parameter returns the area of the combined peak
// Simply multiply by h_a
inline double CombArea(double& sig,double& dec,double& eta){
	double decX_0=DecGausMaxX(sig,dec)*(1-eta);  
	double xeta=eta/UniGaus(decX_0,sig);//should be -X_0, but its symmetric
	double zeta=(1-eta)/DecGaus(decX_0,sig,dec);
	return UniGausArea(sig)*xeta + DecGausArea(sig,dec)*zeta;
}
inline double OldCombArea(double& sig,double& dec,double& eta){return UniGausArea(sig)*eta + DecGausArea(sig,dec)*(1-eta);}

inline double TrueCentroid(double& cent,double& sig,double& dec,double& eta){return cent-DecGausMaxX(sig,dec)*(1-eta);}
	
///////////////////////////
//    TF1 functions      //
///////////////////////////

// This function parses the TF1 parameter list and the additional sharing
// parameters to add together multiple peaks specified by relative distances
inline double MulitPeak(double *par,int Np,double& x,double& yeta){
	double ret=0;
	double cent=0;
	double a;
	for(int i=0;i<Np;i++){cent+=par[gPeakNC(i)];
		a=x-cent;
		ret+=par[gPeakNH(i)]*CombRDpeak(a,par[gPeakSigma],par[gPeakDecay],yeta);}
	return ret;
}

// This function parses the TF1 parameter list and the additional sharing
// parameters to add together peak background specified by relative distances
inline double MulitPeakBackUni(double *par,int Np,double& x,double& yeta){
	double ret=0;
	double sum=0;
	double cent=0;
	double a;
	
	double a1 = UniGausArea(par[gPeakSigma]);
	double a2 = DecGausArea(par[gPeakSigma],par[gPeakDecay]);
	double b1 = a1*yeta/(a1*yeta+a2*(1-yeta));
	
	for(int i=0;i<Np;i++)sum+=par[gPeakNH(i)];
	for(int i=0;i<Np;i++){cent+=par[gPeakNC(i)];
		a=x-cent;
		ret+=(par[gPeakNH(i)]/sum)*CombRDstep(a, par[gPeakSigma],par[gPeakDecay],b1);}
	return ret;//*par[gPeakBackB]+par[gPeakBackA];
}

inline double MulitPeakBack(double *par,int Np,double& x,double& yeta){
	return MulitPeakBackUni(par,Np,x,yeta)*par[gPeakBackB]+par[gPeakBackA];
}

// Simple linear background alternative
inline double StepMulitPeak(double *par,int Np,double& x,double& hach,double& yeta){return hach*MulitPeak(par,Np,x,yeta)+MulitPeakBack(par,Np,x,yeta);}
inline double LinearMulitPeak(double *par,int Np,double& x,double& hach,double& yeta){return hach*MulitPeak(par,Np,x,yeta)+x*par[gPeakBackB]+par[gPeakBackA];}



///////////////////////////////////////////
//    New/Old Two Gaus Rather than Exp	 //
///////////////////////////////////////////

// parameters to add together peak background specified by relative distances
inline double MulitPeakBackUni2Gaus(double *par,int Np,double& x,double& yeta){
	double ret=0,sum=0,cent=0;
	for(int i=0;i<Np;i++)sum+=par[gPeakNH(i)];
	for(int i=0;i<Np;i++){cent+=par[gPeakNC(i)];
		double a=x-cent;
		ret+=(par[gPeakNH(i)]/sum)*(UniGausStep(a,par[gPeakSigma])*yeta+UniGausStep(a,par[gPeakSigmaB])*(1-yeta));
	}
	return ret;
}

inline double MulitPeak2Gaus(double *par,int Np,double& x,double& yeta){
	double ret=0,cent=0;
	for(int i=0;i<Np;i++){cent+=par[gPeakNC(i)];
		double a=x-cent;
		ret+=par[gPeakNH(i)]*(UniGaus(a,par[gPeakSigma])*yeta+UniGaus(a,par[gPeakSigmaB])*(1-yeta));
	}
	return ret;
}

inline double CombArea2Gaus(double& sig,double& sigB,double& yeta){
	return UniGausArea(sig)*yeta + UniGausArea(sigB)*(1-yeta);
}

///////////////////////////////////////////
//    Ultra peal class definition	 //
///////////////////////////////////////////


// A class to call to be parsed in a TF1
// Create an Ultrapeak set it internal parameters and then give it to a TF1
// const vector<short> UltraBasicParaIndex={gPeakBackA,gPeakBackB,gPeakBackC,gPeakBackD,gPeakSigma,gPeakDecay,gPeakSharing,gPeakNH(0),gPeakNC(0)};
class  Ultrapeak{
 public:	
	enum UBits {
		kPeaks	= BIT(0),
		kBack	= BIT(1),
		kStep	= BIT(2),
		kPol2	= BIT(3),
		k2Gaus	= BIT(4)
	};
	static int PBits(int i) {return 0x1<<(i+6);}
	
	double para[48];
	
	int N;
	TransientBitsClass<long> cBits;
	
	static const short gUltraPol0=gPeakBackA;
	static const short gUltraPol1=gPeakBackB;
	static const short gUltraOffsetOrPol2=gPeakBackC;
	static const short gUltraStep=gPeakBackD;
	
	static const short VN=0;
	static const short VBI=VN+1;
	static const short VChi=VBI+1;
	static const short VOff=VChi+1;
	static short VPC(int i=0){return i*6+VOff+1;}
	static short VPCe(int i=0){return i*6+VOff+2;}
	static short VPA(int i=0){return i*6+VOff+3;}
	static short VPAe(int i=0){return i*6+VOff+4;}
	static short VPI(int i=0){return i*6+VOff+5;}
	static short VPIe(int i=0){return i*6+VOff+6;}
	
	
	
	void SetBit(int i,bool b=true){cBits.SetBit(i,b);}
	bool TestBit(int i){return cBits.TestBit(i);}
 
	Ultrapeak(int n=1,bool p=1,bool b=1,bool s=1,bool g=0):N(n){
		SetBit(kPeaks,p);
		SetBit(kBack,b);
		SetBit(kStep,s);
		SetBit(k2Gaus,g);
		if(N>10)N=10;
	}
	Ultrapeak(int n,TransientBitsClass<long> b):N(n),cBits(b){}
	Ultrapeak(int n,long b):N(n),cBits(b){}	
	
	Ultrapeak(const Ultrapeak& tmp) : N(tmp.N),cBits(tmp.cBits) { }
	Ultrapeak & operator=(const Ultrapeak & rhs) {N=rhs.N;cBits=rhs.cBits; return *this; }
	
	~Ultrapeak(){};
	
	static unsigned int NfromTF1(TF1* f){int i=0;while(f->GetNpar()>gPeakNC(i))i++;return i;}//Number of peaks if TF1 is an ultra
	static unsigned int NparFromN(int i){return gPeakNC(i)-1;}//Total number of parameters if fn has i peaks
	
	//Fix here means correct not restrain
	static void FixParameters(double* p,double* P,int Np,TransientBitsClass<long>& bits){
		for(unsigned int i=0;i<NparFromN(Np);i++)P[i]=p[i];//copy shared shape para and first peak (well everything actually)
		for(int i=1;i<Np;i++){
// 			P[gPeakNC(i)]=p[gPeakNC(i)];//centroid
			if(bits.TestBit(Ultrapeak::PBits(i))){//heights
				P[gPeakNH(i)]=P[gPeakNH(i-1)]*p[gPeakNH(i)];
			}//else{
			//	P[gPeakNH(i)]=p[gPeakNH(i)];
			//}
		}
	}
	
	static double GetFixedNH(double* p,TransientBitsClass<long>& bits,unsigned short i){//i=index not N
		double ret=p[gPeakNH(0)];
		for(int j=1;j<=i;j++){
			if(bits.TestBit(Ultrapeak::PBits(j))){//heights
				ret=ret*p[gPeakNH(j)];
			}else{
				ret=p[gPeakNH(j)];
			}
		}
		return ret;
	}
	
	
	double operator() (double *x, double *p) {

		// Complex sharing parameters for the decay peak are calculated here to save multiplication of effort
		double a=DecGausMaxX(p[gPeakSigma],p[gPeakDecay])*(1-p[gPeakSharing]); 
		double X=x[0]+a;  
		double xeta=p[gPeakSharing]/UniGaus(a,p[gPeakSigma]);
		double zeta=(1-p[gPeakSharing])/DecGaus(a,p[gPeakSigma],p[gPeakDecay]);
		double yeta=xeta/(xeta+zeta);
		double hach=xeta+zeta;
		
		// NOTE the following line removes
		// complex sharing parameter normalisation behaviour 
		// Use OldCombArea and ignore "TrueCentroid"
		//yeta=p[gPeakSharing];hach=1;X=x[0];
		
		// The latter functions take peak height but now peak height inputs may be ratio
		// So first we convert.
		double *P=p;
		if(N>1){FixParameters(p,para,N,cBits);P=para;}

		double ret=0;
		if(TestBit(kPeaks)){
			if(TestBit(k2Gaus))ret+=MulitPeak2Gaus(P,N,x[0],p[gPeakSharing]);
			else ret+=hach*MulitPeak(P,N,X,yeta);
		}
		
			
		if(TestBit(kBack)){
			ret+=P[gUltraPol0];
			if(TestBit(kStep)){
				if(TestBit(k2Gaus))ret+=P[gUltraStep]*MulitPeakBackUni2Gaus(P,N,x[0],p[gPeakSharing]);
				else ret+=P[gUltraStep]*MulitPeakBackUni(P,N,X,yeta);
			}
			if(TestBit(kPol2))ret+=x[0]*P[gUltraPol1]+x[0]*x[0]*P[gUltraOffsetOrPol2];
			else ret+=(x[0]-P[gUltraOffsetOrPol2])*P[gUltraPol1];
		}

		return ret;
	}

	
	// Produce the visuals of an Ultra peak individually, together and background, for drawing or saving 
	// Provide a canvas for overlay drawing
	// Provide a histogram it will be drawn first AND have functions saved, interactive use is lost but graphics and parameter info remain.
	static void DrawPeak(FullFitHolder*,TCanvas* =0,TH1* =0);
	// inline void DrawUltraPeak(FullFitHolder* fHold,TCanvas* fCan=0,TH1* fHist=0){DrawUltraPeak(fHold,fCan,fHist);}
	
	// Calculate all the data of the ultra peak and store in the FullFitHolder vector
	static void MakeData(FullFitHolder* fHold,double binwidth=1);
	static void MakeData(FullFitHolder* fHold,TH1* hist);

	static void MakeData(vector< FullFitHolder* > in,TH1* hist){for(int i=0;(unsigned)i<in.size();i++)MakeData(in[i],hist);}
	static void MakeData(vector< FullFitHolder* > in,double binwidth=1){for(int i=0;(unsigned)i<in.size();i++)MakeData(in[i],binwidth);}

	// Print data vector of FullFitHolder as defined for an Ultrapeak (calls Ultrapeak::MakeData if not run)
	static void PrintTitles(ostream& =cout);// Print title to terminal
	static void PrintData(FullFitHolder* fHold,bool titles=true,double binwidth=1,ostream& =cout);
	static void PrintData(FullFitHolder* fHold,bool titles,TH1* hist,ostream& =cout);
	static void PrintData(vector< FullFitHolder* > in,TH1* hist,ostream& ofs=cout){
		PrintTitles(ofs);for(int i=0;(unsigned)i<in.size();i++)PrintData(in[i],false,hist,ofs);}	
	static void PrintData(vector< FullFitHolder* > in,double binwidth=1,ostream& ofs=cout){
		PrintTitles(ofs);for(int i=0;(unsigned)i<in.size();i++)PrintData(in[i],false,binwidth,ofs);}
		
	// An all singing all dancing function to fit N peaks that are in close enough proximity to assume constant peak parameters
	// int=1 specified to attempt to use step background int=0 uses linear
	static FullFitHolder* PeakFit(TH1* fHist,double fLeftUser,double fRightUser,vector< jPeakDat > &fInput,int backmode=0,int peaktype=0,string sig="",string dec="",string sha="",TH1* fExHist=0);
	// If the fit fails returns 0
	
	// Uses default values for simple single fit
	// If the fit fails returns 0
	
	static FullFitHolder* QuickPeakFit(TH1* fHist,double fLeftUser,double fRightUser);

};




///////////////////////////////////////////
//       Helper class definition	 //
///////////////////////////////////////////


// Made to be operated with the same parameter list as Ultrapeak as a TF1,
// even though it has no x dependence.
// Give it an incorrect N and it will F U up.
class  UltrapeakArea{
 public:
 
  static double UltraPeakAreaFn(unsigned int& Np, double *p){return p[gPeakNH(Np)]*CombArea(p[gPeakSigma],p[gPeakDecay],p[gPeakSharing]);}
  
  static double UltraPeakAreaFn2Gaus(unsigned int& Np, double *p){return p[gPeakNH(Np)]*CombArea2Gaus(p[gPeakSigma],p[gPeakSigmaB],p[gPeakSharing]);}
  
	unsigned int N_i;//Target peak 0-(N-1), not total number
	TransientBitsClass<long> cBits;
	double para[48];
	
	UltrapeakArea(int n,TransientBitsClass<long> bits):N_i(n),cBits(bits){if(N_i>9)N_i=9;}
	UltrapeakArea(int n,long bits):UltrapeakArea(n,TransientBitsClass<long>(bits)){}
	UltrapeakArea(int n=0):UltrapeakArea(n,3){}
	~UltrapeakArea(){};
	
	double operator() (double *x, double *p) {
		double *P=p;
		if(N_i>0){Ultrapeak::FixParameters(p,para,N_i+1,cBits);P=para;}
		if(cBits.TestBit(Ultrapeak::k2Gaus))return UltraPeakAreaFn2Gaus(N_i,P);
		else return UltraPeakAreaFn(N_i,P);
	}
};

// Made to be operated with the same parameter list as Ultrapeak as a TF1,
// even though it has no x dependence.
// Give it an incorrect N and it will F U up.
class  UltrapeakFrac{
 public:
 
	static double UltrapeakFracFn(unsigned int& Np, unsigned int& i,double *p){
		double sum=0;
		for(unsigned int j=0;j<Np;j++)sum+=p[gPeakNH(j)];
		return p[gPeakNH(i)]/sum;
	}
 
	unsigned int N;//total number
	unsigned int N_i;//Target peak 0-(N-1), not total number
	TransientBitsClass<long> cBits;
	double para[48];
	
	UltrapeakFrac(int n,int i,TransientBitsClass<long> bits):N(n),N_i(i),cBits(bits){if(N>10)N=10;}
	UltrapeakFrac(int n,int i,long bits):UltrapeakFrac(n,i,TransientBitsClass<long>(bits)){}
	UltrapeakFrac(){};
	~UltrapeakFrac(){};
	
	double operator() (double *x, double *p) {
		double *P=p;
		if(N>0){Ultrapeak::FixParameters(p,para,N+1,cBits);P=para;}
		if(N>N_i)return UltrapeakFracFn(N,N_i,P);
		return 0;
	}

};


#endif