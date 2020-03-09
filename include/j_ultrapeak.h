//
//
//	jROOT Tools
//	Class for fitting of tailed gaussians with step and polynomail background
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef ultrapeak_func_h
#define ultrapeak_func_h

#include "j_utility.h"
#include "j_fitting.h"    

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
#include <TMinuit.h>

#include <cmath>
#include <TMath.h>

#include <iostream>
#include <iomanip>
using namespace std;

// These globals are set to enable the maths functions declared at global scope to use parameters
// lists Ultrapeak without compatibility issues and for future extension of parameter list without
// intense rewrite. However as Parameter lists are subsequently long and contain unused values, 
// care must be taken fix parameters not in use. There are Ultrapeak functions provided to this end.

const short gPeakBackA=0;
const short gPeakBackB=1;
const short gPeakBackC=2;
const short gPeakBackD=3;
const short gPeakDecay=4;
const short gPeakSigma=5;
const short gPeakSigmaB=6;
const short gPeakSigmaC=7;
const short gPeakSharing=8;
inline short gPeakNH(unsigned short i){return i*2+9;}
inline short gPeakNC(unsigned short i){return i*2+10;}

const short gPeakNlimit=10;


// The following peak functions are written in parts to make the maths transparent
/////////////////////////////////////////////////////
//   Basic Gaussian, centred at zero and height 1  //
/////////////////////////////////////////////////////

inline double UniGaus(double& x,double& sig){return exp(-((x*x)/(sig*sig*2)));}

// CFD
inline double UniGausCFD(double& x,double& sig){return 0.5*(1+TMath::Erf(x/(sig*TMath::Sqrt2())));}

// Unit step for background
inline double UniGausStep(double& x,double& sig){return 1-UniGausCFD(x,sig);}

const double Sqrt2Pi = sqrt(2*TMath::Pi());
inline double UniGausArea(double& sig){return sig*Sqrt2Pi;}


////////////////////////////////////////////////////////
//  Exponential starting at zero decaying negatively  //
//      Convolved with Gaussian broadening            //
////////////////////////////////////////////////////////

inline double DecGaus(double& x,double& sig,double& dec){return exp(x/dec)*TMath::Erfc(x/(sig*TMath::Sqrt2()) + sig/(dec*TMath::Sqrt2()));}

inline double DecGausCFD(double& x,double& sig,double& dec){return 0.5*(1 + exp((x/dec) + ((sig*sig)/(2*dec*dec)))*TMath::Erfc(((dec*x) + (sig*sig)) /(dec*sig*TMath::Sqrt2()))+TMath::Erf(x/(sig*TMath::Sqrt2())));}

inline double DecGausStep(double& x,double& sig,double& dec){return 1-DecGausCFD(x,sig,dec);}

inline double DecGausArea(double& sig,double& dec){return 2*dec*exp(-((sig*sig)/(2*dec*dec)));}

// An analytical approach to the X value of decay peak maximum
// Now using a TGraph, more accurate (and negligably faster)
// Valid in the range 10^-4<=(sigma/decay)<=35
double DecGausMaxX(double& sig,double& dec);

double DecMaxCorrPow(double& sig,double& dec);

///////////////////////////////////
//       DecGaus + UniGaus       //
///////////////////////////////////

inline double TrueCentroid(const double& cent,double& sig,double& dec,double& eta){
    //return cent-DecGausMaxX(sig,dec)*(1-eta);
    return cent-DecGausMaxX(sig,dec)*pow(1-eta,DecMaxCorrPow(sig,dec));// This new extra correction isnt *strickly* necessary
}

///////////////////////////////////////////
//      Ultra peak class definition      //
///////////////////////////////////////////

// A class to call to be parsed in a TF1
// Create an Ultrapeak set it internal parameters and then give it to a TF1
class  Ultrapeak{
 public:	
	enum UBits {
		kPeaks	= BIT(0),
		kBack	= BIT(1),
		kStep	= BIT(2),
		kPol0	= BIT(3),
		kPol1	= BIT(4),
		kPol2	= BIT(5),
		kDecOff	= BIT(6),
		k2Gaus	= BIT(7),
		kInflate= BIT(8),
		kCentTrue= BIT(9)
	};
	static int PBits(int i) {return 0x1<<(i+10);}
	
	double para[48]; // Doesnt store parameters permanatly, used in operations
	
	int N;
	TransientBitsClass<long> cBits;
	static short gMaxPeaks;
    
	void SetBit(int i,bool b=true){cBits.SetBit(i,b);}
	bool TestBit(int i){return cBits.TestBit(i);}
 
    ///////////////////////////////////////////////////////////////////
    
	static const short gUltraPol0=gPeakBackA;
	static const short gUltraPol1=gPeakBackB;
	static const short gUltraOffsetOrPol2=gPeakBackC;
	static const short gUltraStep=gPeakBackD;
	static const short gUltraTGWR=gPeakSigmaB;
	static const short gUltraTGHR=gPeakSigmaC;

    //////////////////// FitHoldVals ////////////////////////////////
    
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
	
	///////////////// Background Control /////////////////////////////
	
	static const short cBackTypeN=-2;//null
	static const short cBackType0=0;//pol0
	static const short cBackType0s=1;//pol0+step
	static const short cBackType1=10;//pol1
	static const short cBackType1s=11;//pol1 +step
	static const short cBackType1f=12;//pol1 fixed   // Note : Ultrapeak doesnt know internally if USED parameters are to be fixed
	static const short cBackType2=20;//pol2
	static const short cBackType2s=21;//pol2 +step
	
	static bool Step(short BackType){
        return BackType%2;
    }
	static unsigned short PolOrder(short BackType){
        	return BackType/10;
    }
    // Pol0/Pol1/Pol2 Pol2
	static bool Pol0(short BackType){
            return (PolOrder(BackType)==0);
    }
	static bool Pol1(short BackType){
            return (PolOrder(BackType)==1);
    }
	static bool Pol2(short BackType){
            return (PolOrder(BackType)==2);
    }
    
    void SetBackMode(short bm){
        SetBit(kBack,!(cBackTypeN==bm));
        SetBit(kStep,Step(bm));
        SetBit(kPol0,Pol0(bm));
        SetBit(kPol1,Pol1(bm));
        SetBit(kPol2,Pol2(bm));
    }
    
    //////////////////////// Constructors /////////////////////////////
    
	Ultrapeak(int n=1,bool p=1,int bm=cBackType1s,bool tg=0,bool c=0):N(n){
		SetBit(kPeaks,p);
		SetBackMode(bm);
		SetBit(k2Gaus,tg);
		SetBit(kInflate,0);
		SetBit(kCentTrue,c);
		if(N>gPeakNlimit)N=gPeakNlimit;
	}
	Ultrapeak(int n,TransientBitsClass<long> b):N(n),cBits(b){}
	Ultrapeak(int n,long b):N(n),cBits(b){}	
	
	Ultrapeak(const Ultrapeak& tmp) : N(tmp.N),cBits(tmp.cBits) { }
	Ultrapeak & operator=(const Ultrapeak & rhs) {N=rhs.N;cBits=rhs.cBits; return *this; }
	
	virtual ~Ultrapeak(){};
    
    ///////////////////////// TF1 Functions ///////////////////////////////
    
    static TF1* PrepareTF1(double range1=0,double range2=1000,int n=1,int backmode=0,bool twogaus=0);
    
    void NameParam(TF1* t);
    static void NameParam(TF1* t,int b,bool tg);
    static void NameParam(TF1* t,int n,TransientBitsClass<long>& bits);
    
    void FixUnusedParam(TF1* t);
    static void FixUnusedParam(TF1* t,int b,bool tg);
    static void FixUnusedParam(TF1* t,int n,TransientBitsClass<long>& bits);
    
    bool FitLimitations(TF1* fPeakFunc,const bool& Print);
    
	static unsigned int NfromTF1(TF1* f){int i=0;while(f->GetNpar()>gPeakNC(i))i++;return i;}// Number of peaks if TF1 is an ultra
	static unsigned int NparFromN(int i){return gPeakNC(i)-1;} // Total number of parameters if fn has i peaks
	
    ///////////////////////////////////////////////////////////////////
	
	// "Fix" here means correct not restrain
	static void FixParameters(double* p,double* P,int Np,TransientBitsClass<long>& bits){
// 		for(unsigned int i=0;i<NparFromN(Np);i++)P[i]=p[i];// copy shared shape para and first peak (well everything actually)
		memcpy(P,p,sizeof(double)*NparFromN(Np));
		for(int i=1;i<Np;i++){
			if(bits.TestBit(Ultrapeak::PBits(i))){//heights
				P[gPeakNH(i)]=P[gPeakNH(i-1)]*p[gPeakNH(i)];
			}
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
	
	static void AreaMeanSigma(double& sigD,double *P) {
		sigD=P[gPeakSigma];
        sigD*=(P[gUltraTGHR]+P[gUltraTGWR]*P[gUltraTGWR]*(1-P[gUltraTGHR]));
        sigD/=(P[gUltraTGHR]+P[gUltraTGWR]*(1-P[gUltraTGHR]));
    } 
	
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
	
	double operator() (double *x, double *p) {
        double *P=p;
        double ret=0;
        double X=x[0];
        double X_0=0;
        
        if(N>1){
            FixParameters(p,para,N,cBits);P=para;
            // Functions take arguments of peak height, but input parameters may be ratios. cBits knows which.
        }
        
        // Function may consist of up to 3 peak components
        // Gaussian + Guassian + DecayTailGaussian
        // The maxium of the component sumed peak is always 1
        // 
        // Two parameters control the ratio of the peak components
        // The MUST have range limits from 0-1
        // One parameter, p[gUltraTGHR], is the ratio of 2 gaussians 
        // gaus1_height/(gaus1_height + gaus2_height)
        // The other parameter, p[gPeakSharing], is the ratio of both Gaussian to DecGaus
        // gaus_sum_height/(Gaus_sum_height + DecGaus_height)
        
        // DecGaus is NOT max @ 0 and does NOT have height = 1
        // From p[gPeakSharing]  we calculate a scaling factors such that:
        // y = xeta*UniGaus + zeta*DecGaus
        // Will have a max height ~1
        // Thus height parameters and sharing parameters can be given in terms of simple observable height
        // Much easier for fitting but more complicated in the functions.
        
        // The "centroid" that is fit is actually the Y-max
        // A true centroid is calcuated from sharing and decay parameters.
        // This is useful for initial fit estimations,
        // but problematic for inputing peaks with known true centroids (energy).
        // In such cases the decay/sharing parameters may be fixed,
        // so that the TrueCentroid offset can be calcualted.
        
        bool Gaus=(P[gPeakSharing]>0);
        bool TwoGaus=(P[gUltraTGHR]<1)&&(P[gUltraTGWR]>1)&&TestBit(k2Gaus);
        bool Tail=(P[gPeakSharing]<1)&&!TestBit(kDecOff);

        double& sigA=P[gPeakSigma];
        double sigB=P[gPeakSigma]*P[gUltraTGWR];
        double sigD=P[gPeakSigma];
        double TGFrac=1;
        if(TwoGaus){
            TGFrac=P[gUltraTGHR];
            if(Tail){
                AreaMeanSigma(sigD,P);
                // Area weighted mean sigma used by the decay tail
            }
        }

        if(Tail){
            X_0=-TrueCentroid(0,sigD,P[gPeakDecay],P[gPeakSharing]); // The X value at which combined peak is maximal // A bit imprecise maybe?
            if(!TestBit(kCentTrue)){// Flag to use "True centroid" 
                X+=X_0;
            }
        }            
        
        double xeta=0,yeta=0,zeta=0;
        // Scaling parameters =
        // 0-1 Height sharing fraction / Y value at X_0
        if(Gaus)xeta=P[gPeakSharing]*TGFrac/UniGaus(X_0,sigA); 
        if(TwoGaus)yeta=P[gPeakSharing]*(1-TGFrac)/UniGaus(X_0,sigB);
        if(Tail)zeta=(1-P[gPeakSharing])/DecGaus(X_0,sigD,P[gPeakDecay]);

        if(TestBit(kPeaks)){
            if(Gaus)ret+=xeta*MulitPeakSigma(P,X,sigA,false);
            if(TwoGaus)ret+=yeta*MulitPeakSigma(P,X,sigB,false);
            if(Tail)ret+=zeta*MulitPeakSigma(P,X,sigD,true);
        }
        
        if(TestBit(kBack)){
            ret+=P[gUltraPol0];
            if(TestBit(kPol2))ret+=x[0]*P[gUltraPol1]+x[0]*x[0]*P[gUltraOffsetOrPol2];
            else if(TestBit(kPol1)) ret+=(x[0]-P[gUltraOffsetOrPol2])*P[gUltraPol1];
            
            if(TestBit(kStep)){// Area weighted step
                double a1=0,a2=0,aD=0;
                if(Gaus)a1=UniGausArea(sigA)*xeta;
                if(TwoGaus)a2=UniGausArea(sigB)*yeta;
                if(Tail)aD=DecGausArea(sigD,P[gPeakDecay])*zeta;
                double sm=P[gUltraStep]/(a1+a2+aD);

                if(Gaus)ret+=sm*a1*MulitPeakBackSigma(P,X,sigA,false);
                if(TwoGaus)ret+=sm*a2*MulitPeakBackSigma(P,X,sigB,false);
                if(Tail)ret+=sm*aD*MulitPeakBackSigma(P,X,sigD,true);
            }
        }
        
        return ret;
	}

    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
	
    //////////////////////////////////////
    //          Simplified Sums         //
    //////////////////////////////////////

    // Add together multiple peaks specified by relative distances
    double MulitPeakSigma(double *par,double& x,double& sig,const bool& decay){
        double ret=0, cent=0, a;
        
        for(int i=0;i<N;i++){
            cent+=par[gPeakNC(i)];
            a=x-cent;
            if(decay)ret+=par[gPeakNH(i)]*DecGaus(a,sig,par[gPeakDecay]);
            else ret+=par[gPeakNH(i)]*UniGaus(a,sig);
        }
        return ret;
    }

    // Add together peak background steps specified by relative distances
    // Normalised to total height 1
    double MulitPeakBackSigma(double *par,double& x,double& sig,const bool& decay){
        double ret=0,sum=0,cent=0,a;

        for(int i=0;i<N;i++)sum+=par[gPeakNH(i)];
        
        for(int i=0;i<N;i++){
            cent+=par[gPeakNC(i)];
            a=x-cent;
            if(decay)ret+=(par[gPeakNH(i)]/sum)*DecGausStep(a,sig,par[gPeakDecay]);
            else ret+=(par[gPeakNH(i)]/sum)*UniGausStep(a,sig);
        }
        return ret;
    }
	
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
	
	// Produce the visuals of an Ultra peak individually, together and background, for drawing or saving 
	// Provide a canvas for overlay drawing
	// Provide a histogram it will be drawn first AND have functions saved, interactive use is lost but graphics and parameter info remain.
	static void DrawPeak(FullFitHolder*,TCanvas* =0,TH1* =0);
	// inline void DrawUltraPeak(FullFitHolder* fHold,TCanvas* fCan=0,TH1* fHist=0){DrawUltraPeak(fHold,fCan,fHist);}
	
	// Calculate all the data of the ultra peak and store in the FullFitHolder vector
	static void MakeData(FullFitHolder* fHold,double binwidth=1);
	static void MakeData(FullFitHolder* fHold,TH1* hist,TH1* exclusion=0);

	static void MakeData(vector< FullFitHolder* > in,TH1* hist){for(int i=0;(unsigned)i<in.size();i++)MakeData(in[i],hist);}
	static void MakeData(vector< FullFitHolder* > in,double binwidth=1){for(int i=0;(unsigned)i<in.size();i++)MakeData(in[i],binwidth);}

	// Print data vector of FullFitHolder as defined for an Ultrapeak (calls Ultrapeak::MakeData if not run)
	static void PrintTitles(ostream& =cout);// Print title to terminal
	static void PrintData(FullFitHolder* fHold,bool titles=true,double binwidth=1,ostream& =cout);
	static void PrintData(FullFitHolder* fHold,bool titles,TH1* hist,ostream& =cout);
	static void PrintData(vector< FullFitHolder* > in,TH1* hist,ostream& ofs=cout){
		PrintTitles(ofs);for(int i=0;(unsigned)i<in.size();i++)PrintData(in[i],false,hist,ofs);ofs<<endl;}	
	static void PrintData(vector< FullFitHolder* > in,double binwidth=1,ostream& ofs=cout){
		PrintTitles(ofs);for(int i=0;(unsigned)i<in.size();i++)PrintData(in[i],false,binwidth,ofs);ofs<<endl;}
		
    ///////////////////////////////////////////////////////////////////
    
	// An all singing all dancing function to fit N peaks that are in close enough proximity to assume constant peak parameters
	// int=1 specified to attempt to use step background int=0 uses linear
	// If the fit fails returns 0
	static FullFitHolder* PeakFit(TH1* fHist,TH1* fExHist,double fLeftUser,double fRightUser,vector< jPeakDat > &fInput,int backmode=cBackType0,int peaktype=0,bool truecent=0,string FixPar="");
	
	
	
	static FullFitHolder* PeakFit(TH1* fHist,double fLeftUser,double fRightUser,vector< jPeakDat > &fInput,int backmode=cBackType0,int peaktype=0,bool truecent=0,string sig="",string dec="",string sha="",TH1* fExHist=0){
        return PeakFit
        (fHist,fExHist,fLeftUser,fRightUser,fInput,backmode,peaktype,truecent,sig+'/'+dec+'/'+sha);
    }
	
    
    ///////////////////////////////////////////////////////////////////
    
	// Uses default values for simple single fit
	// If the fit fails returns 0
	
	static FullFitHolder* QuickPeakFit(TH1* fHist,double fLeftUser,double fRightUser, bool fExtraOpt=0);

    // A TGraph used for the numberical solution to the decay peak
	static TGraph DecayXR10;
	static TGraph DecayCorrPow;
    
	static int Ultra_iterator;
    
	ClassDef(Ultrapeak, 2);
};



///////////////////////////////////////////
//       Helper class definition	 //
///////////////////////////////////////////

// Made to be operated with the same parameter list as Ultrapeak as a TF1,
// even though it has no x dependence.
// Give it an incorrect N and it will F U up.
class  UltrapeakArea{
 public:
  
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

		bool TG=cBits.TestBit(Ultrapeak::k2Gaus);
		bool DT=!cBits.TestBit(Ultrapeak::kDecOff);
        
        double sigB=P[gPeakSigma]*P[gPeakSigmaB];
        double sigD=P[gPeakSigma];
        double TGFrac=1;
        if(TG){
            TGFrac=P[gPeakSigmaC];
            if(DT)Ultrapeak::AreaMeanSigma(sigD,P);
        }
        
        double X_0=0;
        if(DT){
            X_0=-TrueCentroid(0,sigD,P[gPeakDecay],P[gPeakSharing]); 
        }

        double ret=0;
        if(P[gPeakSharing]>0){
            ret+=UniGausArea(P[gPeakSigma])*P[gPeakSharing]*TGFrac/UniGaus(X_0,P[gPeakSigma]);
            if(TG)ret+=UniGausArea(sigB)*P[gPeakSharing]*(1-TGFrac)/UniGaus(X_0,sigB);
        }
        if(DT)ret+=DecGausArea(sigD,P[gPeakDecay])*(1-P[gPeakSharing])/DecGaus(X_0,sigD,P[gPeakDecay]);
        
        return P[gPeakNH(N_i)]*ret;
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
        
        return sCentroid;
	}
};


#endif
