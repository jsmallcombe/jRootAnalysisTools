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
			error=error*pow(10,floor(log10(abs(value)))-sf+1);
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


void ExtractAsymError(string str,double& value,double& errorup,double& errordwn){
	value=0;	
	errorup=-1;
	errordwn=-1;	

	unsigned int l=str.size();
	if(l<1)return;
	
	char symb[6]={'+','-',' ','(',')','\t'};
	vector<unsigned int> type;
	vector<string> substr;
	unsigned int lasttype=100;
	unsigned int count=0;
	for(unsigned int i=0;i<l;++i){
		bool special=0;
		int thistype=-1;
		for(int j=0;j<6;++j){
			if(symb[j]==str[i]){
				//exception for exponents
				if(i>0){
					if(j<2&&(str[i-1]=='e'||str[i-1]=='E')){
						continue;
					}
				}
				special=1;
				thistype=j;	
			}
		}
		
		//If this character is special
		if(special){
			if(count){//There was any length of non special (i.e. a number)
				substr.push_back(str.substr(i-count,count));
				type.push_back(lasttype);
			}
			lasttype=thistype;
			count=0;
		}else{
			count++;
			if(i==(l-1)){//If its the end of string
				substr.push_back(str.substr(l-count,count));
				type.push_back(lasttype);
			}
		}
	}
	
	unsigned int s=substr.size();
	if(s<1)return;
	value=std::atof(substr[0].c_str());
	if(type[0]==1)value=-abs(value);//Because we took off any signs
	
	if(s<2)return;
	
	// Calculate the scale applied to significant figure errors //
	
	unsigned int digits=substr[0].size();
	unsigned int exp=substr[0].find("e");
	unsigned int EXP=substr[0].find("E");
	if(exp<digits)digits=exp;
	if(EXP<digits)digits=EXP;
	unsigned int sf=digits;
	for(unsigned int i=0;i<digits;i++)
		if(substr[0][i]=='0')sf--;
		else if(substr[0][i]!='.')break;

	if((unsigned)substr[0].find(".")<digits)sf--;
	double scale=pow(10,floor(log10(abs(value)))-sf+1);
	
	//////
	
	double err=std::atof(substr[1].c_str());
	if(type[1]==3){//If bracketed significant figure error
		//If error value is <1 or non-integer, it isn't a sf error
			if(!(err<1||int(err)<err))err*=scale;
	}
	
	if(type[1]==1)errordwn=abs(err);//abs should be unnecessary is char part works right 
	else errorup=abs(err);
	
	if(s>2){
		err=std::atof(substr[2].c_str());
		if(type[2]==3){//If bracketed significant figure error
			//If error value is <1 or non-integer, it isn't a sf error
				if(!(err<1||int(err)<err))err*=scale;
		}
	}
	
	if(errordwn<0)errordwn=abs(err);
	if(errorup<0)errorup=abs(err);
	
	return;
}

void ExtractAsymErrorTest(string str){
	double v,u,d;
	ExtractAsymError(str,v,u,d);
	cout<<endl<<v<<" + "<<u<<" - "<<d<<endl;
}


ClassImp(TH1Efficiency);
