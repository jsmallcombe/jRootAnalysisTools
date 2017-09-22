#include "james_fitholder.h"

ClassImp(FullFitHolder);

//////////////////////////////////////////
//	FIT FUNCTION HOLDER CLASS	//
//////////////////////////////////////////

void SortFullFitByRedChi(vector<FullFitHolder*>& fPass,double fLimit){
	vector<FullFitHolder*> fHold;
	vector<double> fChiV;
	
	int fN=fPass.size();
	
	//Load chi squared values Throw out those over limit
	for(int i=0;i<fN;i++){
		double sChi=fPass[i]->ReducedChi();
		if(sChi<=fLimit||fLimit<0){
			fHold.push_back(fPass[i]);
			fChiV.push_back(sChi);
		}else{
			delete fPass[i];
		}
	}
	
	vector<int> fOrder = vector_order_gen(fChiV);
	
	fN=fOrder.size();
	fPass.resize(fN);
	
	//Sort
	for(int i=0;i<fN;i++)fPass[i]=fHold[fOrder[i]];
}

void SortFullFitByVal(vector<FullFitHolder*>& fPass,unsigned int fVar,bool fUp){
	vector<FullFitHolder*> fHold;
	vector<double> fVal;
	int fN=fPass.size();
	for(int i=0;i<fN;i++){
		if(fPass[i]->CValS()>fVar){
			fHold.push_back(fPass[i]);
			fVal.push_back(fPass[i]->CVal(fVar));
		}else{
			delete fPass[i];
		}
	}
	vector<int> fOrder = vector_order_gen(fVal,fUp);
	fN=fOrder.size();
	fPass.resize(fN);
	for(int i=0;i<fN;i++)fPass[i]=fHold[fOrder[i]];
}