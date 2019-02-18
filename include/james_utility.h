//
//
//	James Root Library
//	Utility functions and classes for Vectors, TF1s etc
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef JUtility
#define JUtility

#include <TMatrixD.h>
#include <TMatrixDSym.h>
#include <vector>
#include <utility>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TClass.h>
#include <TGraph.h>
#include <TArray.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TGraphErrors.h>
#include <TFitResult.h>

using namespace std;

inline int HType(TObject* H){
	if(H){
		if(H->InheritsFrom("TH3"))return 3;
		if(H->InheritsFrom("TH2"))return 2;
		if(H->InheritsFrom("TH1"))return 1;
	}
	return 0;
}


inline int HistoClassDetect(TClass* tclass){
    if(tclass->InheritsFrom(TH3::Class()))return 3;
    if(tclass->InheritsFrom(TH2::Class()))return 2;
    if(tclass->InheritsFrom(TH1::Class()))return 1;
    return 0;
}

inline int HistoClassDetect(TString classname){
    return HistoClassDetect(gROOT->GetClass(classname));
}


inline bool GraphClassDetect(TClass* tclass){
    return tclass->InheritsFrom(TGraph::Class());
}

inline bool GraphClassDetect(TString classname){
    return GraphClassDetect(gROOT->GetClass(classname));
}

//////////////////////////////////////////////////
//	FUNCTIONS FOR EQUATION EVALUATION	//
//////////////////////////////////////////////////

//
// Provide a TF1 the full error with variance and covariance in the matrix is calculated at X (or leave =0 for no X dependence)
//
double AnalyticalFullCovError(TF1*,TMatrixD*,double=0);


//////////////////////////////////
//	VECTOR SORT FUNCTIONS	//
//////////////////////////////////

//Basic function to sort a vector of doubles, bool=true ascending
void vector_d_sort(vector< double >&,bool);

//
// Returns a a list of the indices of the input vector sorted based on their values, bool=true ascending
//
vector< int > vector_order_gen(vector< double >& fValues, bool fUp=true);

//
//	These are used in the evaluation of order
//
template<typename T>
bool PairCompareDown(const pair<double, T>& firstElem, const pair<double, T>& secondElem) {return firstElem.first > secondElem.first;}
template<typename T>
bool PairCompareUp(const pair<double, T>& firstElem, const pair<double, T>& secondElem) {  return firstElem.first < secondElem.first;}


//
//	Sort a second vector based on the first vector
//	first bool=true ascending
//	second bool=true sort the first vector aswell
//
template<typename T>
void vector_dd_sort(vector< double >& fValues,vector< T >& fValuesT, bool fUp=true,bool both=false){
	double fN=fValues.size();
	vector<pair<double,T>> fPair;
	for(int i=0;i<fN;i++)fPair.push_back(pair<double,T>(fValues[i],fValuesT[i]));	
	
	if(fUp)std::sort(fPair.begin(), fPair.end(), PairCompareUp<T>);
	else std::sort(fPair.begin(), fPair.end(), PairCompareDown<T>);

	for(int i=0;i<fN;i++){
		if(both)fValues[i]=fPair[i].first;
		fValuesT[i]=fPair[i].second;
	}
}

//
//	Sort three vectors based on the first vector, bool=true ascending
//
template<typename T,typename TT>
void vector_ddd_sort(vector< double >& fValues,vector< T >& fValuesT,vector< TT >& fValuesTT, bool fUp){
	vector_dd_sort<T>(fValues,fValuesT,fUp,false);
	vector_dd_sort<TT>(fValues,fValuesTT,fUp,true);
}

//////////////////////////
//	BIT  CLASS	//
//////////////////////////

//Modified from grsisort
template<typename T>
class TransientBitsClass {
  public:
    TransientBitsClass() : fBits(0) { }
    TransientBitsClass(const T& tmp) : fBits(tmp) { }
    TransientBitsClass(const TransientBitsClass<T>& tmp) : fBits(tmp.fBits) { }
    ~TransientBitsClass() { } 

    void SetBit(Int_t f, Bool_t flag) { flag ? SetBit(f) : ClearBit(f); } 
    void SetBit(Int_t f) { fBits |= f; }
    void ClearBit(Int_t f) { fBits &= ~f; } 
    Bool_t TestBit(Int_t f) const { return fBits & f; }

    TransientBitsClass & operator=(const T & rhs) { fBits = rhs; return *this; }
    TransientBitsClass & operator=(const TransientBitsClass & rhs) { fBits = rhs.fBits; return *this; }

    void Clear(){ fBits = 0; }
    void Print() const { std::cout << std::hex << fBits << std::endl; }
    void Print(T bits) const {
		for(T i=0;i<bits;i++){
			if((0x1<<i)&fBits)std::cout<<"1";
			else std::cout<<"0";
		}
		std::cout << std::endl;
    }

    T fBits;
};


//////////////////////////////////////////////////////////
//	Function to separate value+error strings	//
//////////////////////////////////////////////////////////

void ExtractError(string str,double& value,double& error);

void ExtractErrorTest(string str);


void ExtractAsymError(string str,double& value,double& errorup,double& errordwn);

void ExtractAsymErrorTest(string str);

//////////////////////////////////////////////////////////
//		mini maths functions			//
//////////////////////////////////////////////////////////


inline void swap_jd(double &a,double &b){double x=a;a=b;b=x;}
inline void higher_jd(double &low,double &high){if(low>high)swap_jd(low,high);}

inline double jsigfig(double in,int sf){
  if(in==0)return 0;
  int sfis=floor(log10(abs(in)));

  double fac=pow(10,sfis-sf+1);

  return round(in/fac)*fac;
}



//////////////////////////////////////////////////////////
//		efficiency fill histogram		//
//////////////////////////////////////////////////////////

//
// A helper class for filling a TH1D based on efficiency
// Acts primarily as a TH1D except data on efficiency and efficiency uncertainty are stored
// And hence filling is overridden,
// Correlated efficiency uncertainty is tallied once filling is completed.
// Call FillFinish() (called automatically on Write)
//

class TH1Efficiency : public TH1D {
  public:
	TH1Efficiency(){};
	TH1Efficiency(const char *name,const char *title,Int_t nbins,Double_t xlow,Double_t xup,TGraph *Eff,TGraph *Err=0):TH1D(name,title,nbins,xlow,xup){
// 		fEstore.Set(TH1D::GetNcells());
		fEstore.Set(fNcells);
		fEff=(*Eff);
		fDoErr=(Err);
		FillFin=false;
		if(fDoErr){
			fErr=(*Err);
		}
	}
	virtual ~TH1Efficiency(){}
	

	TH1Efficiency( const TH1Efficiency &obj){obj.Copy(*this);}//copy constructor
	TH1Efficiency& operator=(const TH1Efficiency& obj){//assignment operator
		obj.Copy(*this);
		return *this;
	}
	void Copy(TObject &rhs) const {
		TH1D::Copy(rhs);
		static_cast<TH1Efficiency&>(rhs).fEff=fEff;
		static_cast<TH1Efficiency&>(rhs).fErr=fErr;
		static_cast<TH1Efficiency&>(rhs).fDoErr=fDoErr;
		static_cast<TH1Efficiency&>(rhs).fEstore=fEstore;
		return;                                      
	}
	
	
	Int_t Fill(double X){return Fill(X,X);}
	Int_t Fill(double X,double eX){
		if(FillFin)return 1;
		double D=fEff.Eval(eX);
		if(D>1E-6){
			Int_t N=TH1D::Fill(X,1/D);//Will correctly increment sumw2 by 1/D^2
			if(N<0) return -1;
			if(fDoErr){
				double d=fErr.Eval(eX);
				if(d>0&&d<D){
					fEstore.fArray[N]+=d/pow(D,2);
				}
			}
			return N;
		}
		return -1;
	}
	// Could include Eff Err into sumw2 at fill time.
	// However the end result is actually an overall smaller error (this ignores correlations between the efficiency in each fill)

	
  	void FillFinish(){
		if(fDoErr&&fSumw2.fN == fNcells){
			for (Int_t bin = 0; bin < fNcells; ++bin){
				fSumw2.fArray[bin] += pow(fEstore.fArray[bin],2);
				fEstore.fArray[bin]=0;
			}
			FillFin=true;
		}
	}
	
	Int_t Write(const char *name = 0,Int_t 	option = 0,Int_t bufsize = 0){
		FillFinish();
// 		return TObject::Write(name,option,bufsize);
		
		TH1D copy;
		TH1D::Copy(copy);
		return copy.Write(name,option,bufsize);
	}
	
  private:
	TGraph fEff;
	TGraph fErr;
	TArrayD fEstore;
	bool fDoErr,FillFin;
   private:
	ClassDef(TH1Efficiency,2);
};


class TH2Efficiency : public TH2D {
  public:
	bool asymmetric; 
	TH2Efficiency(){};
	TH2Efficiency(const char *name,const char *title,Int_t nbins,Double_t xlow,Double_t xup,Int_t nbinsy,Double_t ylow,Double_t yup,double ggfracin,TGraph *Eff,TGraph *Err=0):TH2D(name,title,nbins,xlow,xup,nbinsy,ylow,yup){
// 		fEstore.Set(TH1D::GetNcells());
		fEstore.Set(fNcells);
		fEstore2.Set(fNcells);
		fEff=(*Eff);
		fDoErr=(Err);
		FillFin=false;
		ggfrac=ggfracin;
		if(fDoErr){
			fErr=(*Err);
		}
		asymmetric=false;
	}
	virtual ~TH2Efficiency(){}
	
	
	// While this class is primarily for gamma gamma histograms,
	// this option sets only the x axis to be efficiency corrected
	// the is free to be a normal counter/variable 
	void SetAsymmetric(){
		asymmetric=true;
	}
	

	TH2Efficiency( const TH2Efficiency &obj){obj.Copy(*this);}//copy constructor
	TH2Efficiency& operator=(const TH2Efficiency& obj){//assignment operator
		obj.Copy(*this);
		return *this;
	}
	void Copy(TObject &rhs) const {
		TH2D::Copy(rhs);
		static_cast<TH2Efficiency&>(rhs).fEff=fEff;
		static_cast<TH2Efficiency&>(rhs).fErr=fErr;
		static_cast<TH2Efficiency&>(rhs).fDoErr=fDoErr;
		static_cast<TH2Efficiency&>(rhs).fEstore=fEstore;
		static_cast<TH2Efficiency&>(rhs).fEstore2=fEstore2;
		return;                                      
	}
	
	
	Int_t Fill(double X,double Y){return Fill(X,X,Y,Y);}
	Int_t Fill(double X,double eX,double Y){return Fill(X,eX,Y,Y);}
	Int_t Fill(double X,double eX,double Y,double eY){
		if(FillFin)return 1;
		double D=fEff.Eval(eX);
		double D2=fEff.Eval(eY);
		if(asymmetric)D2=1;
		if(D>1E-4&&D2>1E-4){
			double scale=D*D2*ggfrac;
			Int_t N=TH2D::Fill(X,Y,1/scale);
			if(N<0) return -1;
			if(fDoErr){
				double d=fErr.Eval(eX);
				double d2=fErr.Eval(eY);
				if(d>0&&d<D&&d2>0&&d2<D2){
					fEstore.fArray[N]+=d/(D*scale);
					if(!asymmetric)fEstore2.fArray[N]+=d2/(D2*scale);
				}
			}
			return N;
		}
		return -1;
	}
	Int_t FillSymt(double X,double eX,double Y,double eY){Fill(Y,eY,X,eX);return Fill(X,eX,Y,eY);}
	
  	void FillFinish(){
		if(fDoErr&&fSumw2.fN == fNcells){
			for (Int_t bin = 0; bin < fNcells; ++bin){
				fSumw2.fArray[bin] += pow(fEstore.fArray[bin],2);
				fSumw2.fArray[bin] += pow(fEstore2.fArray[bin],2);
				
				fSumw2.fArray[bin] += pow(fArray[bin]*0.05,2);//Assumed 5% error ggfrac
				
				fEstore.fArray[bin]=0;
				fEstore2.fArray[bin]=0;
			}
			FillFin=true;
		}
	}
	
	Int_t Write(const char *name = 0,Int_t 	option = 0,Int_t bufsize = 0){
		FillFinish();
// 		return TObject::Write(name,option,bufsize);
		
		TH2D copy;
		TH2D::Copy(copy);
		return copy.Write(name,option,bufsize);
	}
	
  private:
	TGraph fEff;
	TGraph fErr;
	TArrayD fEstore,fEstore2;
	bool fDoErr,FillFin;
	double ggfrac;
   private:
	ClassDef(TH2Efficiency,1);
};





#endif
