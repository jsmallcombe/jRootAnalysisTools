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
#include <TKey.h>

#include <cmath>
#include <TMath.h>

#include <iostream>
#include <iomanip>
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
const short gPeakSigmaB=6;
const short gPeakSigmaC=7;
const short gPeakSharing=8;
inline short gPeakNH(unsigned short i){return i*2+9;}
inline short gPeakNC(unsigned short i){return i*2+10;}

const short gPeakNlimit=10;

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
inline double OldDecGausMaxX(double& sig,double& dec){
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

//An analytical approach to the X value of decay peak maximum
// Switched to a TGraph, more accurate (and negligably faster)
// Valid in the range 10^-4<=(sigma/decay)<=35
double DecGausMaxX(double& sig,double& dec);

///////////////////////////////////////
//    DecGaus + UniGaus  	     //
///////////////////////////////////////

// Returns the two peaks in their nominal form summed
inline double CombRDpeak(double& x,double& sig,double& dec,double& eta){return UniGaus(x,sig)*eta+DecGaus(x,sig,dec)*(1-eta);}

// Returns the two peak steps in their nominal form summed
// A single sharing parameter from 0-1
inline double CombRDstep(double& x,double& sig,double& dec,double& b1){return UniGausStep(x,sig)*b1+DecGausStep(x,sig,dec)*(1-b1);}

// Given the usual 0-1 sharing parameter returns the area of the combined peak
// Simply multiply by h_a
inline double CombArea(double& sig,double& dec,double& eta){
	double decX_0=DecGausMaxX(sig,dec)*(1-eta);//The X value at which DecGaus is maximal 
	double yuni=UniGaus(decX_0,sig);//The Y value of UniGaus at that point
	double xeta=eta/yuni;//UniGaus sharing fraction / UniGaus Y value
	double zeta=(1-eta)/DecGaus(decX_0,sig,dec);// DecGaus sharing fraction / DecGaus Y value
	return UniGausArea(sig)*xeta + DecGausArea(sig,dec)*zeta;
	// Peak is defined such that the height at decX_0 == 1
	
	//Old Version UniGausArea(sig)*eta + DecGausArea(sig,dec)*(1-eta)
}

inline double TrueCentroid(double& cent,double& sig,double& dec,double& eta){return cent-DecGausMaxX(sig,dec)*(1-eta);}
	
/////////////////////////////////////////////
//    TF1 functions DecGaus + UniGaus      //
/////////////////////////////////////////////

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


////////////////////////////////////
//     DecGaus + TwoUniGaus       //
////////////////////////////////////


inline double CombRDpeakTwo(double& x,double& sig1,double& sig2,double& TwoGausFrac,double& dec,double& eta){
	double sigd=sig1*TwoGausFrac+sig2*(1-TwoGausFrac);
	return (UniGaus(x,sig1)*TwoGausFrac+UniGaus(x,sig2)*(1-TwoGausFrac))*eta+DecGaus(x,sigd,dec)*(1-eta);
}

inline double CombRDstepTwo(double& x,double& sig1,double& sig2,double& TwoGausFrac,double& dec,double& b1){
	double sigd=sig1*TwoGausFrac+sig2*(1-TwoGausFrac);
	return (UniGausStep(x,sig1)*TwoGausFrac+UniGausStep(x,sig2)*(1-TwoGausFrac))*b1+DecGausStep(x,sigd,dec)*(1-b1);
}


inline double CombAreaTwo(double& sig1,double& sig2,double& TwoGausFrac,double& dec,double& eta){
	double sigd=sig1*TwoGausFrac+sig2*(1-TwoGausFrac);
	double decX_0=DecGausMaxX(sigd,dec)*(1-eta);
	double xeta=eta/(UniGaus(decX_0,sig1)*TwoGausFrac+UniGaus(decX_0,sig2)*(1-TwoGausFrac));
	double zeta=(1-eta)/DecGaus(decX_0,sigd,dec);
	return (UniGausArea(sig1)*TwoGausFrac+UniGausArea(sig2)*(1-TwoGausFrac))*xeta + DecGausArea(sigd,dec)*zeta;
}

	
/////////////////////////////////////////////
//    TF1 functions DecGaus + TwoUniGaus   //
/////////////////////////////////////////////

// This function parses the TF1 parameter list and the additional sharing
// parameters to add together multiple peaks specified by relative distances
inline double MulitPeakTwo(double *par,int Np,double& x,double& yeta){
	double ret=0;
	double cent=0;
	double a;
	double sB=par[gPeakSigma]*par[gPeakSigmaB];
	for(int i=0;i<Np;i++){cent+=par[gPeakNC(i)];
		a=x-cent;
		ret+=par[gPeakNH(i)]*CombRDpeakTwo(a,par[gPeakSigma],sB,par[gPeakSigmaC],par[gPeakDecay],yeta);}
	return ret;
}
	
// This function parses the TF1 parameter list and the additional sharing
// parameters to add together peak background specified by relative distances
inline double MulitPeakBackUniTwo(double *par,int Np,double& x,double& yeta){
	double ret=0;
	double sum=0;
	double cent=0;
	double a;
	double sB=par[gPeakSigma]*par[gPeakSigmaB];
	double TwoGausFrac=par[gPeakSigmaC];
	
	double a1 = UniGausArea(par[gPeakSigma])*TwoGausFrac+UniGausArea(sB)*(1-TwoGausFrac);
	double a2 = DecGausArea(par[gPeakSigma],par[gPeakDecay]);
	double b1 = a1*yeta/(a1*yeta+a2*(1-yeta));
	
	for(int i=0;i<Np;i++)sum+=par[gPeakNH(i)];
	for(int i=0;i<Np;i++){cent+=par[gPeakNC(i)];
		a=x-cent;
		ret+=(par[gPeakNH(i)]/sum)*CombRDstepTwo(a,par[gPeakSigma],sB,TwoGausFrac,par[gPeakDecay],b1);}
	return ret;
}

inline double MulitPeakBackTwo(double *par,int Np,double& x,double& yeta){
	return MulitPeakBackUniTwo(par,Np,x,yeta)*par[gPeakBackB]+par[gPeakBackA];
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
		k2Gaus	= BIT(4),
		kInflate= BIT(5),
		kCentTrue= BIT(6)
	};
	static int PBits(int i) {return 0x1<<(i+7);}
	
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
	
	
	static const short cBackType0=0;//pol0
	static const short cBackType0s=1;//pol0+step
	static const short cBackType1=10;//pol1
	static const short cBackType1s=11;//pol1 +step
	static const short cBackType1f=12;//pol1 fixed
	static const short cBackType2=20;//pol2
	static const short cBackType2s=21;//pol2 +step
	
	static bool Step(int BackType){
        return BackType%2;
    }
	static int PolOrder(int BackType){
        	return BackType/10;
    }
	static bool Pol2(int BackType){
            return PolOrder(BackType)/2;
    }
	
	void SetBit(int i,bool b=true){cBits.SetBit(i,b);}
	bool TestBit(int i){return cBits.TestBit(i);}
 
	Ultrapeak(int n=1,bool p=1,bool b=1,bool s=1,bool g=0,bool c=0):N(n){
		SetBit(kPeaks,p);
		SetBit(kBack,b);
		SetBit(kStep,s);
		SetBit(k2Gaus,g);
		SetBit(kInflate,0);
		SetBit(kCentTrue,c);
		if(N>gPeakNlimit)N=gPeakNlimit;
	}
	Ultrapeak(int n,TransientBitsClass<long> b):N(n),cBits(b){}
	Ultrapeak(int n,long b):N(n),cBits(b){}	
	
	Ultrapeak(const Ultrapeak& tmp) : N(tmp.N),cBits(tmp.cBits) { }
	Ultrapeak & operator=(const Ultrapeak & rhs) {N=rhs.N;cBits=rhs.cBits; return *this; }
	
	virtual ~Ultrapeak(){};
	
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

		// DecGaus is not max @ 0 and does not have height = 1
		// User p[gPeakSharing] specifies the fraction of the height that is UniGaus
		// From this we calculate a new sharing parameter yeta & scaling factor hach such that:
		// y = hach * ( yeta*UniGaus + (1-yeta)*DecGaus)
		// Will have a max height ~1
		// Thus height parameters and sharing parameters can be given in terms of simple observable height
		// Much easier for fitting but more complicated in the functions.
        
        // The "centroid" that is fit is actually the Y-max
        // A true centroid is calcuated from sharing and decay parameters.
        // This is useful for initial fit estimations,
        // but problematic for inputing peaks with known true centroids (energy).
        // In such cases the decay/sharing parameters may be fixed,
        // so that the TrueCentroid offset can be calcualted.
		
		// Complex sharing parameters for the decay peak are calculated here to save multiplication of effort

		
		double TwoGausFrac=p[gPeakSigmaC];
		double sigd=p[gPeakSigma];
		if(TestBit(k2Gaus))sigd*=(TwoGausFrac+p[gPeakSigmaB]*(1-TwoGausFrac));
	
		double a=DecGausMaxX(sigd,p[gPeakDecay])*(1-p[gPeakSharing]); 
		double X=x[0]+a;  
		double xeta;
		if(TestBit(k2Gaus)){
			double sB=p[gPeakSigma]*p[gPeakSigmaB];
			xeta=p[gPeakSharing]/(UniGaus(a,p[gPeakSigma])*TwoGausFrac+UniGaus(a,sB)*(1-TwoGausFrac));
		}else xeta=p[gPeakSharing]/UniGaus(a,p[gPeakSigma]);
		double zeta=(1-p[gPeakSharing])/DecGaus(a,sigd,p[gPeakDecay]);
		double yeta=xeta/(xeta+zeta);
		double hach=xeta+zeta;

		// NOTE the following line removes
		// complex sharing parameter normalisation behaviour 
		// Use OldCombArea and ignore "TrueCentroid"
		//yeta=p[gPeakSharing];hach=1;X=x[0];
        
        if(TestBit(kCentTrue)){//New flag to use "True centroid" while still keeping yeta/hach
            X=x[0];
        }
		
		// The latter functions take peak height but now peak height inputs may be ratio
		// So first we convert.
		double *P=p;
		if(N>1){FixParameters(p,para,N,cBits);P=para;}

		double ret=0;
		if(TestBit(kPeaks)){
			if(TestBit(k2Gaus))ret+=hach*MulitPeakTwo(P,N,X,yeta);
			else ret+=hach*MulitPeak(P,N,X,yeta);
		}
		//With new function it is possible to fix par[gPeakSigmaB]==1 and use MulitPeakTwo instead of MulitPeak
		
			
		if(TestBit(kBack)){
			ret+=P[gUltraPol0];
			if(TestBit(kStep)){
				if(TestBit(k2Gaus))ret+=P[gUltraStep]*MulitPeakBackUniTwo(P,N,X,yeta);
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
	static void MakeData(FullFitHolder* fHold,TH1* hist,TH1* exclusion=0);
	static void InflateError(FullFitHolder* fHold);
	

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
	static FullFitHolder* PeakFit(TH1* fHist,double fLeftUser,double fRightUser,vector< jPeakDat > &fInput,int backmode=cBackType0,int peaktype=0,bool truecent=0,string sig="",string dec="",string sha="",TH1* fExHist=0);
	// If the fit fails returns 0
	
	// Uses default values for simple single fit
	// If the fit fails returns 0
	
	static FullFitHolder* QuickPeakFit(TH1* fHist,double fLeftUser,double fRightUser, bool fExtraOpt=0);

    
    //A TGraph used for the numberical solution to the decay peak
	static TGraph DecayXR10;
    
	ClassDef(Ultrapeak, 1);
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

	static double UltraPeakAreaFnTwo(unsigned int& Np, double *p){
		double sB=p[gPeakSigma]*p[gPeakSigmaB];
		return p[gPeakNH(Np)]*CombAreaTwo(p[gPeakSigma],sB,p[gPeakSigmaC],p[gPeakDecay],p[gPeakSharing]);
	}
  
	unsigned int N_i;//Target peak 0-(N-1), not total number
	TransientBitsClass<long> cBits;
	double para[48];
	
	UltrapeakArea(int n,TransientBitsClass<long> bits):N_i(n),cBits(bits){if(N_i>gPeakNlimit)N_i=gPeakNlimit;}
	UltrapeakArea(int n,long bits):UltrapeakArea(n,TransientBitsClass<long>(bits)){}
	UltrapeakArea(int n=0):UltrapeakArea(n,3){}
	~UltrapeakArea(){};
	
	double operator() (double *x, double *p) {
		double *P=p;
		if(N_i>0){Ultrapeak::FixParameters(p,para,N_i+1,cBits);P=para;}
		if(cBits.TestBit(Ultrapeak::k2Gaus))return UltraPeakAreaFnTwo(N_i,P);
		else return UltraPeakAreaFn(N_i,P);
	}
};

// Made to be operated with the same parameter list as Ultrapeak as a TF1,
// even though it has no x dependence.
// Give it an incorrect N and it will F U up.
class  UltrapeakFrac{
 public:
 
    vector<int> S;
	unsigned int N;//total number
	unsigned int N_i;//Target peak 0-(N-1), not total number
	TransientBitsClass<long> cBits;
	double para[48];
	
	UltrapeakFrac(vector<int> s,int n,int i,TransientBitsClass<long> bits):S(s),N(n),N_i(i),cBits(bits){if(N>gPeakNlimit)N=gPeakNlimit;}
	UltrapeakFrac(vector<int> s,int n,int i,long bits):UltrapeakFrac(s,n,i,TransientBitsClass<long>(bits)){}
	UltrapeakFrac(){};
	~UltrapeakFrac(){};
	
	double operator() (double *x, double *p) {
		double *P=p;
		if(N>0){Ultrapeak::FixParameters(p,para,N+1,cBits);P=para;}
		if(N>N_i){
            double sum=0;
            for(unsigned int s=0;s<S.size();s++)sum+=P[gPeakNH(S[s])];
            return P[gPeakNH(N_i)]/sum;
        }
		return 0;
	}

};


// Made to be operated with the same parameter list as Ultrapeak as a TF1,
// even though it has no x dependence.
// Give it an incorrect N and it will F U up.
class  UltrapeakCentroid{
 public:
  
	unsigned int N_i;//Target peak 0-(N-1), not total number
	TransientBitsClass<long> cBits;
	double para[48];
	
	UltrapeakCentroid(int n,TransientBitsClass<long> bits):N_i(n),cBits(bits){if(N_i>gPeakNlimit)N_i=gPeakNlimit;}
	UltrapeakCentroid(int n,long bits):UltrapeakCentroid(n,TransientBitsClass<long>(bits)){}
	UltrapeakCentroid(int n=0):UltrapeakCentroid(n,3){}
	~UltrapeakCentroid(){};
	
	double operator() (double *x, double *p) {
        double sCentroid=0;
        for(unsigned int i=0;i<=N_i;i++){
            sCentroid+=p[gPeakNC(i)];
        }
        return TrueCentroid(sCentroid,p[gPeakSigma],p[gPeakDecay],p[gPeakSharing]);
	}
};


#endif
