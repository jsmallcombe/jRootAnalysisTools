//
//
//	James functions for auto fitting and such 1.0
// 	02/03/2019
//	james.smallcombe@outlook.com
//
//

#include "j_fitting.h"

// No easy way to get if par fixed, TF1 doesnt actually store this info.
// Part copied from TF1::GetNumberFreeParameters()
bool IsParFixed(TF1* func,unsigned int par){
    if(!func) return false;
    if(par>=(unsigned)func->GetNpar())return false;
    Double_t al, bl;
    func->GetParLimits(par,al,bl);
    return (al * bl != 0 && al >= bl);
}

// Check for diagonal matrix elements, should be non zero if error estimation was good
bool CovDiag(TFitResultPtr fResult){
    TMatrixDSym cov=fResult->GetCovarianceMatrix();
    double OffDiag=0;
    for(int i=0;i<cov.GetNcols();i++)for(int j=0;j<i;j++)OffDiag+=abs(cov[i][j]);
    return (OffDiag);
}


bool ParAtLimit(TF1* func,unsigned int par,bool Upper){
    if(IsParFixed(func,par))return false;
    Double_t al, bl;
    func->GetParLimits(par,al,bl);
    double p=func->GetParameter(par);
    double range=abs(bl-al);
    if(Upper)al=bl;
    
    return (abs(p-al)/range<1E-9);
}

bool ParAtLimit(TF1* func,unsigned int par){
    return (ParAtLimit(func,par,0)||ParAtLimit(func,par,1));
}

bool AnyParAtLimit(TF1* func){
    for(int i=0;i<func->GetNpar();i++){
        if(ParAtLimit(func,i))return true;
    }
    return false;
    // gMinuit->fLimset if immediate
}

void FixLimitPushers(TF1* func){
    for(int i=0;i<func->GetNpar();i++){
        Double_t al, bl;
        func->GetParLimits(i,al,bl);
        if(ParAtLimit(func,i,0)){
            func->FixParameter(i,al);
        }else if(ParAtLimit(func,i,1)){
            func->FixParameter(i,bl);
        }
    }
}


TF1* UserQuickSingleGausAutoFit(TH1* h,double c,double a,double b,int autoR){
	TAxis* x=h->GetXaxis();if(a==0&&b==0){a=c-20;b=c+20;}
	return QuickSingleGausAutoFit(h,x->FindBin(c),x->FindBin(a),x->FindBin(b),autoR);
}
TF1* UserQuickSingleGausAutoFitE(TH1* h,double c,double a,double b,int autoR){
	TAxis* x=h->GetXaxis();if(a==0&&b==0){a=c-20;b=c+20;}
	return QuickSingleGausAutoFitE(h,x->FindBin(c),x->FindBin(a),x->FindBin(b),autoR);
}
TF1* UserQuickSingleGausAutoFitEE(TH1* h,double c,double a,double b,int autoR){
	TAxis* x=h->GetXaxis();if(a==0&&b==0){a=c-20;b=c+20;}
	return QuickSingleGausAutoFitEE(h,x->FindBin(c),x->FindBin(a),x->FindBin(b),autoR);
}

TF1* QuickSingleGausAutoFit(TH1* hist,int x,int rb,int rt,int autoR){	
	if(rb>rt){int a=rb;rb=rt;rt=a;}
	if(rb<1){rb=1;}
	if(rt>hist->GetNbinsX()){rt=hist->GetNbinsX();}
	 
	//Find the local maximum from the given peak
	double N;
	if(autoR)N=FitPositionOptimisation(hist,x,rb,rt);
	else N=FindLocalMax(hist,x,rb,rt);
	
	double RB=hist->GetBinLowEdge(rb),RT=hist->GetBinLowEdge(rt+1);
	
	double X=hist->GetBinCenter(x);
	N-=((hist->GetBinContent(rb)+hist->GetBinContent(rt))/2);
	
	TF1 *fa1 = new TF1("quickgaus","gaus(0)+pol2(3)",RB,RT);

	fa1->SetRange(RB,RT);
	fa1->SetParameter(0,abs(N));
	fa1->SetParLimits(0,0.0,abs(N)*100);
	fa1->SetParameter(1,X);
	fa1->SetParameter(2,2.0);
	

	double m=(bins_smooth(hist,rt,3)-bins_smooth(hist,rb,3))/(RT-RB);
	double c=bins_smooth(hist,rb,3)-(RB*m);
	fa1->FixParameter(3,c);
	fa1->FixParameter(4,m);
	fa1->FixParameter(5,0.0);
		
	hist->Fit(fa1,"QRBNO");

	return fa1;	
}

TF1* QuickSingleGausAutoFitE(TH1* hist,int cc,int rb,int rt,int autoR){
	TF1* pass=QuickSingleGausAutoFit(hist,cc,rb,rt,autoR);
	pass->SetParLimits(3,1,0);
	pass->SetParLimits(4,1,0);
	hist->Fit(pass,"QRBNO");
	return pass;
}

TF1* QuickSingleGausAutoFitEE(TH1* hist,int cc,int rb,int rt,int autoR){
	TF1* pass=QuickSingleGausAutoFitE(hist,cc,rb,rt,autoR);
	pass->SetParLimits(0,0.0,pass->GetParameter(0)*100);
	pass->SetParLimits(5,1,0);
	hist->Fit(pass,"QRBNO");
	return pass;
}



//////////////////////////////////////////////////
//	FUNCTIONS COMPLEMENTARY TO PEAK FITTING	//
//////////////////////////////////////////////////


double FindLocalMax(TH1* fHist,double& fPeak){
	int x=fHist->GetXaxis()->FindBin(fPeak);
	int x0=x;
	double H=FindLocalMax(fHist,x,1,fHist->GetNbinsX());
	if(x0!=x)fPeak=fHist->GetXaxis()->GetBinCenter(x);
	return H;	
}	
	
double FindLocalMax(TH1* fHist,int& fPeak,int fLeft,int fRight){
	double fRetL=fHist->GetBinContent(fPeak);
	double fRet=fHist->GetBinContent(fPeak);
	int fPos=fPeak;
	for(int i=fPos+1;i<=fRight;i++){
		double sHh=fHist->GetBinContent(i);
		if(sHh>fRet){fRet=sHh;fPeak=i;}else break;
	}
	for(int i=fPos-1;i>=fLeft;i--){
		double sHh=fHist->GetBinContent(i);
		if(sHh>fRetL){
			fRetL=sHh;
			if(sHh>fRet){fRet=sHh;fPeak=i;}
		}else break;
	}	
	return fRet;
}

double FindBinRangeMaxD(TH1* fHist,double& fPeak,double range){
	TAxis* x =fHist->GetXaxis();
	int X=x->FindBin(fPeak);
	double Y =FindBinRangeMax(fHist,X,range/x->GetBinWidth(1));
	fPeak=x->GetBinCenter(X);
	return Y;
}
	
double FindBinRangeMax(TH1* fHist,int& fPeak,int range){
	double m=0;
	int x=0;
	for(int i=-range;i<=range;i++){
		double y=fHist->GetBinContent(fPeak+i);
		if(y>m){m=y;x=fPeak+i;}
	}
	fPeak=x;
	return m;
}
	


//Gets better results if fHist is background subtracted, but should be ok without
double FitPositionOptimisation(TH1* fHistIn,int& fPeak,int& fLeft,int& fRight){
	//Determine a good fitting range near the suggested fLeft and fRight
	
	//Find the local maximum from the given peak
	double fHH=FindLocalMax(fHistIn,fPeak,fLeft,fRight);	
	
	TH1* fHist=SmoothOffBack(fHistIn);

	double fMaxY=fHH*5;
	
	double fMin=fMaxY;
	for(int j=fLeft;j<=fRight;j++)if(fHist->GetBinContent(j)<fMin)fMin=fHist->GetBinContent(j);
	fMin*=5;

	//Go along taking an average and when it starts to go back up, kill the progression		
	double fMinR=fMaxY*2;
	for(int j=fPeak+5;j<=fRight;j++){
		double sAverage=0;
		for(int l=0;l<5;l++)sAverage+=abs(fHist->GetBinContent(j+l));
		if(sAverage<fMinR){fMinR=sAverage;}
		if(sAverage>fMinR+(fMaxY-fMin)*0.05){fRight=j;}				
	}
		
	double fMinL=fMaxY*2;
	for(int j=fPeak-5;j>=fLeft;j--){
		double sAverage=0;
		for(int l=0;l<5;l++)sAverage+=abs(fHist->GetBinContent(j-l));
		if(sAverage<fMinL){fMinL=sAverage;}
		if(sAverage>fMinL+(fMaxY-fMin)*0.05){fLeft=j;}				
	}
	delete fHist;
	return fHH;
}

double bins_smooth(TH1* fHist,double fMid){
	int fM=fHist->GetXaxis()->FindBin(fMid);
	return bins_smooth(fHist,fM,5);
}

double bins_smooth(TH1* fHist,int fM,int fN){
	fN=(fN-1)/2;double ret=0;
	for(int i=-fN;i<=fN;i++)ret+=fHist->GetBinContent(fM+i);
	return ret/((fN*2)+1);
}

double bins_var(TH1* fHist,int fM,int fN){
	double mean=bins_smooth(fHist,fM,fN);
	fN=(fN-1)/2;double ret=0;
	
	for(int i=-fN;i<=fN;i++)ret+=pow(fHist->GetBinContent(fM+i)-mean,2);
	return ret/(fN*2+1);
}

void ZeroBinsFitFix(TH1* hist){
	for(int i=1;i<=hist->GetNbinsX();i++){
		if(hist->GetBinContent(i)==0){
			hist->SetBinError(i,1);
		}
	}
}


TH1* SmoothOffBack(TH1* fHist){
	//Calc a very smoothed background
	TH1* fBack=fHist->ShowBackground(30,"BackSmoothing9");
	fBack->Add(fBack,fHist,-1,1);
	return fBack;
}

