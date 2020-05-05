#include "j_utility.h"

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


double AnalyticalFullCovError(TF1* fFunc,double fX){
	int fNpar=fFunc->GetNpar();
    TMatrixD TempMatrix(fNpar,fNpar);
	for(int i=0;i<fNpar;i++){
        TempMatrix[i][i]=pow(fFunc->GetParError(i),2);
    }
	return AnalyticalFullCovError(fFunc,&TempMatrix,fX);
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


string ScientificErrorPrint(double val,double abserr, unsigned short sigfig, bool sigfigerror, bool print){
    abserr=abs(abserr);
    if(!sigfig)return "";
    sigfig--;
    if(!val)return "";
    
    // Find the decimal place of val
    int ten=-50;
    while(ten<50){
        if(abs((int)(val*pow(10,ten)))>0)break;
        ten++;
    }
    int dp=-ten;
    
	if(sigfigerror){
	
		int errten=-50;
		while(errten<50){
			if(abs((int)(abserr*pow(10,errten)))>0)break;
			errten++;
		}
		if(errten>ten){
			sigfig+=(errten-ten);
		}
		
	}
	
    double power=pow(10,ten+sigfig);
    val=round(val*power)/power;
    abserr=round(abserr*power);
    if(!abserr)abserr=1;
    
    stringstream ss;
    if(abs(dp)>4){
        ss<<std::fixed;
        ss<<std::setprecision(sigfig);
        ss<<std::scientific;
    }else{
        if(dp<sigfig){
            ss<<std::fixed;
            ss<<std::setprecision(abs(dp-sigfig));
        }
        if(dp>sigfig){
            abserr/=power;
        }
    }
    
    ss<<val;
    if(print){
        cout<<ss.str()<<"("<<(int)abserr<<")"<<flush;
    }
    ss<<"("<<(int)abserr<<")";
    return ss.str();
}


/////////////////////////////////////////////////////////////////////////////////////

ClassImp(TH1Efficiency);
ClassImp(TH2Efficiency);


template<typename T>
T csv_Tconv(string input){
    std::stringstream ss; 
    ss<<input;
    T t;
    ss>>t;
    return t;
}
template <> string csv_Tconv<string>(string input){
    return input;
}
    
template<typename T>
vector< vector<T>> csv_process(string file){
    vector< vector<T> > ret;
    ifstream infile(file.c_str());
    if(!infile.good()) return ret;

    T blank;
    string line;
    int columns=0;
    int row=0;
    while(getline(infile,line)){
        for(int i=0;i<columns;i++)ret[i].push_back(blank);
        
        line=line+',';
        int f=0,l=0,L=line.length();
        int i=0;
        while(l<=L){
            if(line[l]==','){
                if(i>=columns){
                    columns++;
                    ret.push_back(vector<T>(row+1,blank));
                }
                if(l>f){
                    ret[i][row]=csv_Tconv<T>(line.substr(f,l-f));
                }
                f=l+1;
                i++;
            }
            l++;
        }
        row++;
    }
    infile.close();

    return ret;
}
template vector< vector<int>> csv_process<int>(string);
template vector< vector<float>> csv_process<float>(string);
template vector< vector<double>> csv_process<double>(string);
template vector< vector<string>> csv_process<string>(string);


TObject* ReadFirstObject(TFile* File,TClass* Class){
	TKey *key;
	TIter next(File->GetListOfKeys());
	while ((key = (TKey*)next())){
		TClass *cl = gROOT->GetClass(key->GetClassName());
		if (cl->InheritsFrom(Class)){
            TObject* Ob=key->ReadObj();
            string Na=Ob->GetName();
            return Ob->Clone((Na+"Cln").c_str());
		}
	}
	return 0;
}

TObject* ReadFirstObject(string File,TClass* Class){
    TFile tmp(File.c_str(),"READ");
    gROOT->cd();
    if(!tmp.IsOpen()){
        cout<<endl<<"NO FILE OPENED :"<<File<<flush;
        return 0;
    }
    TObject* Ob=ReadFirstObject(&tmp,Class);
    tmp.Close();
    return Ob;
}
    
    
TH1* ReadFirstHist(TFile* File){
	return (TH1*) ReadFirstObject(File,TH1::Class());
}
TH1* ReadFirstHist(string File){
	return (TH1*) ReadFirstObject(File,TH1::Class());
}



////////////////////////////////////////////////////////////////////////////////
///////////////////////  Modified Popup Class   ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

ClassImp(jRootMultiPurposePopup);

#include <TGIcon.h>
jRootMultiPurposePopup::jRootMultiPurposePopup(vector<string> lines):
TGTransientFrame(gClient->GetRoot(), gClient->GetRoot(), 400, 200, kHorizontalFrame){
	TGTransientFrame *popup=this;
    popup->SetWindowName("LOADING");
	
//    fClient->GetPicture("mb_exclamation_s.xpm");
//    fClient->GetPicture("mb_asterisk_s.xpm");
    fL1 = new TGLayoutHints(kLHintsCenterY | kLHintsExpandX, 5, 20, 0, 0);

    TGIcon *fIcon = new TGIcon(popup, fClient->GetPicture("mb_stop_s.xpm"),100, 100);
    popup->AddFrame(fIcon,new TGLayoutHints(kLHintsCenterY, 20, 15, 20, 20));

    fLabelFrame = new TGVerticalFrame(popup, 60, 20);
    popup->AddFrame(fLabelFrame,fL1);
	
	DefaultLine="";
	for(unsigned short c=0;c<WC;c++){DefaultLine+=DefaultChar;}
	
	for(unsigned int l=0;l<lines.size();l++){
		if(lines[l].size()){
			// Calling ExpandLines manually to avoid UpdateLine calling ReMap multiple times
			ExpandLines(l+1+DefaultPaddingRules*2); 
			UpdateLine(lines[l],l+DefaultPaddingRules);
		}
	}
	
	ReMap();
	SmallWait();
        
// 	popup->Connect("CloseWindow()","TGTransientFrame",popup,"DontCallClose()");
    popup->DontCallClose();
//  CenterOnParent();// position relative to the parent's window
	
    SetCleanup(kDeepCleanup); // On deletion delete all subframes automatically
}

bool jRootMultiPurposePopup::ExpandLines(unsigned short lines){
	bool NOLChanged=false;
	while(fLabelLines.size()<lines){
		TGLabel *label = new TGLabel(fLabelFrame,DefaultLine.c_str());
		fLabelLines.push_back(label);
//        label->SetTextJustify(text_align);
		fLabelFrame->AddFrame(label, fL1);
		NOLChanged=true;
	}
	return NOLChanged;
}

void jRootMultiPurposePopup::SmallWait(unsigned short reps){
    int waitc=0;
    while(waitc<reps){
        gSystem->ProcessEvents();//gSystem->InnerLoop();
        gSystem->Sleep(5); // 5 milisecond
        waitc++;
		// Little loop to buy Xsystem time to perform draw actionsbox before code moves on
    }
}

void jRootMultiPurposePopup::ReMap(){
    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();
    gClient->NeedRedraw(this,kTRUE);
}

void jRootMultiPurposePopup::UpdateLine(string input,unsigned int line){
	if(input.size()>WC){
		input=input.substr(0,WC-1);
	}else if(input.size()+4<WC && DefaultPaddingRules){
		input=' '+input+' ';
		while(input.size()<WC){
			input=DefaultChar+input;
			if(input.size()<WC)input+=DefaultChar;
		}
	}
	
	bool NOLChanged=ExpandLines(line+1);
	fLabelLines[line]->SetText(input.c_str());
	if(NOLChanged){ReMap();}
	SmallWait(1);
}

void jRootMultiPurposePopup::UpdatePercentage(double percent,unsigned int line){
	stringstream ss;
	ss<<setw(4)<<std::setprecision(3) << percent << " %."; 
	UpdateLine(ss.str(),line);
};

