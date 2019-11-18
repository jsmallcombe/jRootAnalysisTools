//
//
//	James Root Library
//	Fit Holder Class, for storing full error matrix
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef FullFitHold
#define FullFitHold

#include <TMatrixD.h>
#include <TMatrixDSym.h>
#include <vector>
#include <utility>
#include <TF1.h>
#include <TMath.h>
#include <TH1.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TFitResult.h>


#include "james_utility.h"

using namespace std;

//////////////////////////////////////////
//	FIT FUNCTION HOLDER CLASS	//
//////////////////////////////////////////

//
// A simple class to hold all data from a fit generic
// Designed to be populated after fit completion
// The user is responsible for populating vector<double> cVal externally
// NO FUNCTION SPECIFIC elements should be added to this class.
//
class FullFitHolder: public TF1
{ 
	// Members   
    private:
	vector< double > cVal;
    public: 
	bool RedChiInflateErr;
	    
	//TMatrixDSym cCov has issue with = assignment because of dimensions
	TMatrixD cCov;
	TransientBitsClass<long> cBits;
	   
	// Constructors copy etc
	FullFitHolder(TF1* sFit,TMatrixDSym sCov,TransientBitsClass<long> bits=0x0):FullFitHolder(sFit,(TMatrixD)sCov,bits){}
	FullFitHolder(TF1* sFit=new TF1(),TMatrixD sCov=TMatrixD(),TransientBitsClass<long> bits=0x0):TF1(*sFit),RedChiInflateErr(1),cCov(sCov),cBits(bits){
		fNpx=1000;
	}

	virtual ~FullFitHolder(){};

	FullFitHolder( const FullFitHolder &obj){obj.Copy(*this);}//copy constructor
	FullFitHolder& operator=(const FullFitHolder& obj){//assignment operator
		obj.Copy(*this);
		return *this;
	}
	void Copy(TObject &rhs) const {
		TF1::Copy(rhs);
		static_cast<FullFitHolder&>(rhs).cVal= cVal;
		static_cast<FullFitHolder&>(rhs).cCov.ResizeTo(cCov);
		static_cast<FullFitHolder&>(rhs).cCov=cCov;
		static_cast<FullFitHolder&>(rhs).cBits=cBits;
		return;                                      
	} 
	
	TMatrixD* GetCov(){return &cCov;}
// 	FullFitHolder(FullFitHolder&&) = default;                    // Move constructor
// 	FullFitHolder& operator=(FullFitHolder&&) & = default;       // Move assignment operator
	
	// Methods
	double ReducedChi(){if(GetNDF()>0)return GetChisquare()/GetNDF();else return 1E8;}
	double InflateChi(){
        if(RedChiInflateErr){
            double RedChi=ReducedChi();
			if(RedChi>1&&RedChi<1E5){
                return RedChi;
            }
        }
        return 1;
    }
    
// 	double Eval(double X=0){return cFit.Eval(X);}
	double EvalError(double X=0){
		return AnalyticalFullCovError(this,&cCov,X)*sqrt(InflateChi());
        //TMath::StudentQuantile(0.5 + 0.67/2, GetNDF())*TMath::Sqrt(ReducedChi());
	}
	
// 	operator TF1() { return cFit; }
// 	operator TF1*() { return this; }
	operator TMatrixD() { return cCov; }
	operator TMatrixD*() { return &cCov; }
	
	FullFitHolder & operator= (const TMatrixD & Trans){
		Mcopy(Trans);
		return *this;
	}	
	
	void Mcopy(const TMatrixD & Trans){
		cCov.ResizeTo(Trans.GetNrows(),Trans.GetNcols());
		cCov=Trans;
	}
	
// 	void Draw(){cFit.Draw();}
// 	void DrawCopy(){cFit.DrawCopy();}

	
	vector<TGraph*> DrawCopyBands(Option_t * option="",bool BOnly=false){
		double xa,xb;GetRange(xa,xb);
		TGraph A,B;

		for(int i=1;i<2000;i++){
			double x=xa+(xb-xa)*i/2000;
			double y=Eval(x);
			double ey=EvalError(x);
			A.SetPoint(i-1,x,y+ey);
			B.SetPoint(i-1,x,y-ey);
		}
		if(!BOnly)DrawCopy(option);
		
		vector<TGraph*> ret;
		ret.push_back((TGraph*)A.DrawClone("samel"));
		ret.push_back((TGraph*)B.DrawClone("samel"));
		
		return ret;
	}
	
	int Fit(TH1* in,string opt="RBMSE+"){return FitOb(in,opt);}
	int Fit(TGraph* in,string opt="RBMSE+"){return FitOb(in,opt);}
	int Fit(TMultiGraph* in,string opt="RBMSE+"){return FitOb(in,opt);}
	
	template<typename T>
	int FitOb(T* in,string opt){
		opt+="S";
		TFitResultPtr fResult=in->Fit(this,opt.c_str());
		Mcopy(fResult->GetCovarianceMatrix());
		return fResult->Status();
	}
	
	void Refresh(TF1* FreshFit){//Make this FFH functional in a session when loaded from file 
		double xa,xb;
		GetRange(xa,xb);
		FreshFit->SetRange(xa,xb);
		FreshFit->SetParameters(GetParameters());
		FreshFit->SetParErrors(GetParErrors());
		FreshFit->SetName(GetName());
		TF1::operator=(*FreshFit);
// 		FreshFit->Copy((TObject*)this);
	// 	cFit=*FreshFit;
	}
	
	void Refresh(double(*fcn)(double *, double *)){
		TF1 fre("tmp",fcn,0,1,GetNpar());
		Refresh(&fre);
	}
	
	template <typename Func>
	void Refresh(Func f){
		TF1 fre("tmp",f,0,1,GetNpar());
		Refresh(&fre);
	}
	
	void CVal(unsigned int i,double v){
		while(i>=cVal.size())cVal.push_back(0.);
		cVal[i]=v;
	}
	
	double CVal(unsigned int i){
		if(i<cVal.size())return cVal[i];
		return 0;
	}
	
	unsigned short CValS(){return cVal.size();}
	
// 	void Write(string name=""){
// 		cFit.Write((name+"cFit").c_str());
// 		cCov.Write((name+"cCov").c_str());
// 	}	
	
	void SetBit(int bit,bool opt=true){cBits.SetBit(bit,opt);}
	bool TestBit(int bit){return cBits.TestBit(bit);}

   private:
	
	ClassDef(FullFitHolder,4);
};

//
// Sorts a vector of FullFitHolder pointers in order of reduced chi squared
// The optional value will discard (delete from memory) any above a specified limit
//
void SortFullFitByRedChi(vector<FullFitHolder*>&,double=-1);

//
// Sorts a vector of FullFitHolder pointers based on data the user has stored in vector<double> cVal
// The int is the element of the vector, any without a cVal[int] element are deleted from memory
// Optional bool switches to ascending rather than descending
//
void SortFullFitByVal(vector<FullFitHolder*>&,unsigned int,bool=false);

#endif
