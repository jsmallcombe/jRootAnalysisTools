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
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TGraphErrors.h>
#include <TFitResult.h>

using namespace std;

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
//	Function to sepearte value+error strings	//
//////////////////////////////////////////////////////////

void ExtractError(string str,double& value,double& error);

void ExtractErrorTest(string str);


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

#endif
