#include "james_utility.h"

//////////////////////////////////////////////////
//	FUNCTIONS FOR EQUATION EVALUATION	//
//////////////////////////////////////////////////

double AnalyticalFullCovError(TF1* fFunc,TMatrixD* fMatrix,double fX){
	vector<double> fGrad;
	int fNpar=fFunc->GetNpar();
	//cout<<endl<<endl;
	for(int i=0;i<fNpar;i++){fGrad.push_back(fFunc->GradientPar(i,&fX,0.01));}//cout<<fGrad[i]<<" ";}
	
	//cout<<endl<<endl;
	
	double fRet=0;
	if(fMatrix->GetNrows()>=fNpar){
		for(int i=0;i<fNpar;i++){
			for(int j=0;j<fNpar;j++){
				//cout<<fGrad[j]*fGrad[i]*((*fMatrix)[i][j])<<" ";
				fRet+=fGrad[j]*fGrad[i]*((*fMatrix)[i][j]);
			}
			//cout<<endl;
// 			fRet+=fGrad[i]*fGrad[i]*((*fMatrix)[i][i]);
		}
	}
	return sqrt(abs(fRet));
}


//////////////////////////////////
//	VECTOR SORT FUNCTIONS	//
//////////////////////////////////

void vector_d_sort(vector< double >& fValues, bool fUp){
	std::sort(fValues.begin(),fValues.end());
	if(!fUp)std::reverse(fValues.begin(),fValues.end());
}

vector< int > vector_order_gen(vector< double >& fValues, bool fUp){
	double fN=fValues.size();
	vector<pair<double,int>> fPair;
	for(int i=0;i<fN;i++)fPair.push_back(pair<double,int>(fValues[i],i));	
	
	if(fUp)std::sort(fPair.begin(), fPair.end(), PairCompareUp<int>);
	else std::sort(fPair.begin(), fPair.end(), PairCompareDown<int>);
	
	vector< int > fReturn;
	for(int i=0;i<fN;i++)fReturn.push_back(fPair[i].second);
	return fReturn;
}




//////////////////////////////////////////
//	ERRROR EXTRACT FUNCTIONS	//
//////////////////////////////////////////


void ExtractError(string str,double& value,double& error){
	value=0;	
	error=-1;	

	unsigned int l=str.size();
	if(l<1)return;
	
	string symb[5]={"+","-"," ","(",")"};
	unsigned int pos[5];
	for(int i=0;i<5;++i)
		pos[i]=str.substr(1,l-1).find(symb[i])+1;

	//dealing with exponents
	for(int i=0;i<2;++i)if(pos[i]<l&&pos[i]>0)
		while(str[pos[i]-1]=='E'||str[pos[i]-1]=='e'){
			unsigned int j=str.substr(pos[i]+1,l-1).find(symb[i]);
			if(j<l-1){pos[i]+=j+1;}else{pos[i]=l;break;}
		}

	//If +- or other gibberish rather than one symbol or space
	unsigned int errHigh=0,errLow=l;
	for(int i=0;i<4;++i)if(pos[i]<l&&pos[i]>0){
		if(pos[i]>errHigh)errHigh=pos[i];
		if(pos[i]<errLow)errLow=pos[i];
	}
	
	string strval;
	if(errLow<l&&errLow>0){
		strval=str.substr(0,errLow);
		value=std::atof(strval.c_str());
	}else{
		value=std::atof(str.c_str());
		return;
	}
	
	if(errHigh<l-1){
		error=std::atof(str.substr(errHigh+1,l-1).c_str());
		if(pos[4]<l&&pos[4]>pos[3]+1&&pos[3]==errHigh){//is it in brackets
			
			//If error value is <1 or non-integer, it isn't a sf error
			if(error<1||int(error)<error)return;
			
			unsigned int digits=strval.size();
			
			unsigned int exp=strval.find("e");
			unsigned int EXP=strval.find("E");
			if(exp<digits)digits=exp;
			if(EXP<digits)digits=EXP;
			
			unsigned int sf=digits;
			for(unsigned int i=0;i<digits;i++)
				if(strval[i]=='0')sf--;
				else if(strval[i]!='.')
					break;

			if((unsigned)strval.find(".")<digits)sf--;
			error=error*pow(10,floor(log10(value))-sf+1);
// 			cout<<endl<<error<<endl;
		}
	}
	return;
}

void ExtractErrorTest(string str){
	double v,e;
	ExtractError(str,v,e);
	cout<<endl<<v<<" +- "<<e<<endl;
}
