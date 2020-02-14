#include "j_ultrapeak.h"
#include "TStyle.h"


//////////////////////////////////////////////////////
/////////////// Ultra peak fit //////////////////////
//////////////////////////////////////////////////////


FullFitHolder* Ultrapeak::PeakFit(TH1* fHist,double fLeftUser,double fRightUser,vector< jPeakDat > &fInput,int backmode,int peaktype,bool truecent,string sig,string dec,string sha,TH1* fExHist){
	// This function takes in peak positions as a series of relative positions
	// This creates undue correlation between centroid positions 
	// However this is the best way to fix the distance between pairs (or more)
	// Which is a likely desire if fitting multiple peaks anyway
	// All entries are relative to the previous one, so place them in the correct order for any linked pairs
    
	bool limittail=false;
	bool twogaus=false;
	if(peaktype==1)limittail=true;
	if(peaktype==2)twogaus=true;
	
	// Possible problems:
	// Peak parameters are estimated from an initial fit which assumes peak zero is the furthest left peak 

    bool BackOff=false;
    if(backmode<0){
        BackOff=true;
        backmode=cBackType0;
    }
    
	//Check any shape parameter overrides
	bool SigFree=true,DecFree=true,ShareFree=true;
	double SigmaF,SigmaFE,DecayF,DecayFE,ShareF,ShareFE;
	ExtractError(sig,SigmaF,SigmaFE);if(SigmaF>0)SigFree=false;
	ExtractError(dec,DecayF,DecayFE);if(DecayF>0)DecFree=false;
	if(sha.size()>0){ExtractError(sha,ShareF,ShareFE);if(ShareF<=1)ShareFree=false;}
	
	cout<<endl<<endl<<endl;
	
	int fNp=fInput.size();if(fNp<1)return 0;
	if(fNp>gMaxPeaks)fNp=gMaxPeaks;

	int fLeftBin=fHist->GetXaxis()->FindBin(fLeftUser),fRightBin=fHist->GetXaxis()->FindBin(fRightUser);
	fLeftUser=fHist->GetBinCenter(fLeftBin);
	fRightUser=fHist->GetBinCenter(fRightBin);
	
	//Find the absolute max minimum value in the fit range
	bool hasdata=false;
	double fMinY=fHist->GetBinContent(fHist->GetMaximumBin()), fMaxY=-fMinY;
	for(int i=fLeftBin;i<=fRightBin;i++){
		double m=fHist->GetBinContent(i);
		if(m<fMinY)fMinY=m;
		if(m>fMaxY)fMaxY=m;
		if(m!=0)hasdata=true;
	}
	if(!hasdata)return 0;
	
    
    int smbin=3;//REDUCED FROM 5 TO 3
    if(backmode==cBackType1f){smbin=1;}
	//Takes averages of histogram for the right and left, so not so sensitive.
	double fLeftHeight = bins_smooth(fHist,fLeftBin,smbin);
	double fRightHeight = bins_smooth(fHist,fRightBin,smbin);
	double fLeftVar = 2*sqrt(bins_var(fHist,fLeftBin,smbin));	
	double fRightVar = 2*sqrt(bins_var(fHist,fRightBin,smbin));
	double fLeftError=sqrt(abs(fLeftHeight));
	double fRightError=sqrt(abs(fRightHeight));
	if(fLeftVar>fLeftError)fLeftError=fLeftVar;
	if(fRightVar>fRightError)fRightError=fRightVar;
	
	//
	// Copy the peaks positions (1 position and a load of relative ones)
	// Hang over from old version
	//
	vector <double> fPeaks;
	for(int i=0;i<fNp;i++)fPeaks.push_back(fInput[i].Centroid);
		
	double p0=fPeaks[0];//Because FindLocalMax changes input and have decided I dont want that
	double fHH=FindLocalMax(fHist,p0);
		
	////////////////////////////////////////////////////////////////
	//////////////// CHECK HISTOGRAM STATS /////////////////////////
	////////////////////////////////////////////////////////////////
	
	int statmode=0;//chi squared
	double binsums=0;
	bool nonintergerbins=false;
	for(int i=fLeftBin;i<=fRightBin;i++){
		double n=fHist->GetBinContent(i);
		if(abs(n-(int)n)>1E-6)nonintergerbins=true;
		binsums+=abs(n);
	}
	
	if(binsums<(fRightBin-fLeftBin+1)*10){
		statmode=1;//likelihood
		if(nonintergerbins)statmode=2;//weighted likelihood
	}
	
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////// PERFORM PRELIMINARY FIT FOR PEAK PARAMETERS /////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	
	TF1 fLin("fLin","x*[1]+[0]");
	
	double fParam[48]={0}; //Holder for parameters, initial guess and limits needed for good minimisation 

	fParam[gUltraPol1] = (fRightHeight-fLeftHeight)/(fRightUser-fLeftUser); //grad
	fParam[gUltraPol0] = fRightHeight-fRightUser*fParam[gUltraPol1]; //intercept
	if(BackOff){
        fParam[gUltraPol1] =0;
        fParam[gUltraPol0] =0;
    }
    
	fLin.SetParameters(fParam[gUltraPol0],fParam[gUltraPol1]);
	fParam[gPeakSigma] = 2.5; // Peak sigma
	fParam[gPeakSigmaB] = 1.5; // Peak sigma ratio for 2gaus
	fParam[gPeakSigmaC] = 0.6; // Peak height ratio for 2gaus
	fParam[gPeakDecay] = 3.0; // Decay of tail (beta)
	fParam[gPeakSharing] = 0.95; // Peak/Tail Sharing parameter (0 - 1)
	fParam[gPeakNH(0)] = abs(fHH-fLin.Eval(fPeaks[0]));// First Peak Height
	fParam[gPeakNC(0)] = fPeaks[0];// First Peak Centroid
	
	
	//This little check makes sure the initial shape fit skips any negligible shoulder peaks
	double tCC=fPeaks[0];
	for(int i=1;i<3&&i<fNp;i++){
		tCC+=fPeaks[i];
		double tH=fHist->GetBinContent(fHist->GetXaxis()->FindBin(tCC));
		tH-=fLin.Eval(tCC);
		if(tH>fParam[gPeakNH(0)]*5){
			cout<<endl<<"Skipping peak "<<i-1<<" for shape fit"<<endl;
			fParam[gPeakNH(0)]=tH;
			fParam[gPeakNC(0)] = tCC;
		}
	}
	
	if(!SigFree)fParam[gPeakSigma]=SigmaF;
	if(!DecFree)fParam[gPeakDecay]=DecayF;
	if(!ShareFree)fParam[gPeakSharing]=ShareF;
	
	// Fit the first peak (peak + linear back)
	Ultrapeak fPeakFunc(1,1,1,0,twogaus,truecent);//Control parameters (peaks #,peaks 0/1,background 0/1,steptype 0/1)
	TF1 *fPre = new TF1("fPre",fPeakFunc,fLeftUser,fPeaks[0]+4,NparFromN(1));
	NameParam(fPre,1,cBackType1,twogaus);
	
	fPre->SetParameters(fParam);
	FixUnusedParam(fPre,1,cBackType1,twogaus);
    
	fPre->FixParameter(gUltraPol0, fParam[gUltraPol0]); //background constant
	fPre->FixParameter(gUltraPol1, fParam[gUltraPol1]); //background grad

	fPre->FixParameter(gPeakSigmaB,2.0);
	fPre->FixParameter(gPeakSigmaC,0.6);
// 	if(twogaus){fPre->SetParLimits(gPeakSigmaB,1.01,5);}
// 	else{fPre->FixParameter(gPeakSigmaB,0);}
	
	if(SigFree)fPre->SetParLimits(gPeakSigma, 1.0, 6.0);  // Sigma
	else if(SigmaFE>0){
		if(SigmaFE>SigmaF)fPre->SetParLimits(gPeakSigma,1E-3,SigmaF+SigmaFE);
		fPre->SetParLimits(gPeakSigma,SigmaF-SigmaFE,SigmaF+SigmaFE);
	}else{
		fPre->FixParameter(gPeakSigma,SigmaF);
		fPre->FixParameter(gPeakSigmaB,2.0);
	}
	
	if(DecFree){
		if(limittail)fPre->SetParLimits(gPeakDecay, 1.0, 4.);  // Decay of tail (beta)
		else fPre->SetParLimits(gPeakDecay, 1.0, 60.);  // Decay of tail (beta)
	}else if(DecayFE>0){
		if(DecayFE>DecayF)fPre->SetParLimits(gPeakDecay,1E-3,DecayF+DecayFE);
		fPre->SetParLimits(gPeakDecay,DecayF-DecayFE,DecayF+DecayFE);
	}else fPre->FixParameter(gPeakDecay,DecayF);
		
	if(ShareFree){
		if(limittail)fPre->SetParLimits(gPeakSharing, 0.93, 1.);// Sharing parameter
		else fPre->SetParLimits(gPeakSharing, 0., 1.);    // Sharing parameter
	}else if(ShareFE>0){
		double l=ShareF-ShareFE,u=ShareF+ShareFE;
		if(u>1)u=1;
		if(l<0)l=0;
		fPre->SetParLimits(gPeakSharing,l,u);
	}else fPre->FixParameter(gPeakSharing,ShareF);	

	fPre->SetParLimits(gPeakNH(0), fParam[gPeakNH(0)]*0.5, fParam[gPeakNH(0)]*2);  // Height
	
	if(fInput[0].CentConstrained){//Centroid
		double err=fInput[0].CentError;
		if(err>0){
			fPre->SetParLimits(gPeakNC(0), fParam[gPeakNC(0)]-err, fParam[gPeakNC(0)]+err); 
		}else{
			fPre->FixParameter(gPeakNC(0), fParam[gPeakNC(0)]);
		}
	}else{
		fPre->SetParLimits(gPeakNC(0), fParam[gPeakNC(0)]-3, fParam[gPeakNC(0)]+3); 
	}
	
	
	//////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////// PRE FIT //////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	
	//Use the bin cancelled exclusion histogram if passed
	if(fExHist)fExHist->Fit(fPre, "RMQN"); 
	else fHist->Fit(fPre, "RMQN");
		
	fPre->GetParameters(fParam);
	delete fPre;
	
	//////////////////////////////////////////////////////////////////////////////////////
	///////////////////////// CONFIGURE FULL MULTI PEAK FIT //////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	
	//Reset these after they may have been overwritten to avoid shoulder peaks in first pre-fit
	fParam[gPeakNH(0)] = abs(fHH-fLin.Eval(fPeaks[0]));// First Peak Height
	fParam[gPeakNC(0)] = fPeaks[0];// First Peak Centroid
	

	// "pol0+step",0
	// "pol1 fixed",1
	// "pol1",2
	// "pol1+step",3
	// "pol2",4
	// "pol2+step",5
	
	bool step=Step(backmode);
    
	// If the background clearly has no under-peak scattering step, then we use a simple formula
	if(fLeftHeight<=fRightHeight)step=false;
	
	fPeakFunc.N=fNp;
	fPeakFunc.SetBit(kStep,step);
	fPeakFunc.SetBit(kPol2,Pol2(backmode));
	if(peaktype==2)fPeakFunc.SetBit(k2Gaus,1);
	for(int i=1;i<fNp;i++)
		if(fInput[i].Ratio>0)
			fPeakFunc.SetBit(PBits(i));

		
	TF1 *fFit = new TF1("fFit",fPeakFunc,fLeftUser,fRightUser,NparFromN(fNp));
    NameParam(fFit,fNp,backmode,twogaus);
	
	//////////////////////////////////// SET PARAMETERS ////////////////////////////////
	
	///////// Background parameters	////////
	// "pol0+step",  // pol0 fixed based on RHS and step RHS-LHS diff
	// "pol1 fixed", // Grad fixed from LHS RHS and offset slightly free
	// "pol1",       // Offset fixed at centre point, offset and grad slightly free (pol1 see-saw)
	// "pol1+step",  // Offset pinned at RHS, grad set to half and step RHS-LHS diff (pol1 hinge) 
	// "pol2",	  // Pretty free, initial inputs as pol1
	// "pol2+step",  // Pretty free, initial inputs as pol1
	
    
    int polorder=PolOrder(backmode);
	if(polorder==0){
		fParam[gUltraPol0]=fRightHeight;
	}else if(polorder==1){
        if(step)fParam[gUltraOffsetOrPol2]=fRightUser;
		else fParam[gUltraOffsetOrPol2]=fLeftUser+(fRightUser-fLeftUser)*0.5;        
		fParam[gUltraPol0]=fLin.Eval(fParam[gUltraOffsetOrPol2]);
		fParam[gUltraPol1]=fLin.GetParameter(1);
		if(step)fParam[gUltraPol1]=fParam[gUltraPol1]*0.5;        
	}else{
		fParam[gUltraPol0]=fLin.GetParameter(0);
		fParam[gUltraPol1]=fLin.GetParameter(1);
		fParam[gUltraOffsetOrPol2]=0;
	}
	
	if(step){
		fParam[gUltraStep]=fLeftHeight-fRightHeight;
	}
	
	///////// Shape parameters ////////
	
	if(twogaus){
		fParam[gPeakSigmaB]=2.0;
		fParam[gPeakSigmaC]=0.6;
	}
	
	///////// Additional Peaks ////////
	
	double sPe=fPeaks[0];
	for(int i=1;i<fNp;i++){
		fParam[gPeakNC(i)]=fPeaks[i];
		sPe+=fPeaks[i];
		double lH=fHist->GetBinContent(fHist->GetXaxis()->FindBin(sPe));
		double lB=fLin.Eval(sPe);
		double pH=lH-lB;
		if(pH<=0)pH=abs(lH);
		
		if(fInput[i].Ratio>0){//peak height ratio not actual height
            stringstream ss;
            ss<<i;
			fFit->SetParName(gPeakNH(i),("Ratio "+ss.str()).c_str());
			fParam[gPeakNH(i)]=fInput[i].Ratio;
		}else{
			fParam[gPeakNH(i)]=pH;
		}
	}	
	
	fFit->SetParameters(fParam);
	FixUnusedParam(fFit,fNp,backmode,twogaus);
	
	//////////////////////////////////// SET LIMTS & FIXED ////////////////////////////////
	
	///////// Background parameters	////////
	// "pol0+step",  // pol0 fixed based on RHS and step RHS-LHS diff
	// "pol1 fixed", // Grad fixed from LHS RHS and offset slightly free
	// "pol1",       // Offset fixed at centre point, offset and grad slightly free (pol1 see-saw)
	// "pol1 down",  // Offset free downwards (pol1 see-saw)
	// "pol1+step",  // Offset pinned at RHS, grad set to half and step RHS-LHS diff (pol1 hinge) 
	// "pol2",	  // Pretty free initial inputs as pol1
	// "pol2+step",  // Pretty free initial inputs as pol1

	//////////
	double fBackError=sqrt(fLeftError*fLeftError+fRightError*fRightError);
	if(step){
		fFit->SetParLimits(gUltraStep,0,fParam[gUltraStep]+fBackError*1.5);
    }
	
    if(polorder==0){
        fFit->SetParLimits(gUltraPol0,fParam[gUltraPol0]-fRightError*1.5,fParam[gUltraPol0]+fRightError*0.5);        
    }else if(polorder==1){
		fFit->FixParameter(gUltraOffsetOrPol2,fParam[gUltraOffsetOrPol2]);

        if(backmode==cBackType1f){
            fFit->FixParameter(gUltraPol1,fParam[gUltraPol1]);
        }else if(step){
            fFit->SetParLimits(gUltraPol1,0,fLin.GetParameter(1)*1.0001);
        }else{
            double dgrad=abs(fBackError/((fRightUser-fLeftUser)*0.5));
            fFit->SetParLimits(gUltraPol1,fParam[gUltraPol1]-dgrad,fParam[gUltraPol1]+dgrad);
        }
        
        if(step){
            fFit->SetParLimits(gUltraPol0,fParam[gUltraPol0]-fRightError*1.5,fParam[gUltraPol0]+fRightError*0.5);
        }else{
            fFit->SetParLimits(gUltraPol0,fParam[gUltraPol0]-fBackError*1.5,fParam[gUltraPol0]+fBackError*0.5);
        }
        
    }else{
// 		double a=abs(fRightHeight/(fRightUser*fRightUser));
// 		fFit->SetParLimits(gUltraOffsetOrPol2,-2*a,2*a);
    }
    
	if(BackOff){
        fPre->FixParameter(gUltraPol0,0); 
    }
    
	///////// Shape parameters ////////
	
	if(twogaus){
		fFit->SetParLimits(gPeakSigmaB,1.01,4);
		fFit->SetParLimits(gPeakSigmaC,0.2,0.8);
	}
	
	if(SigFree)fFit->SetParLimits(gPeakSigma, fParam[gPeakSigma]*0.5, fParam[gPeakSigma]*2);// Sigma
	else if(SigmaFE>0){
		if(SigmaFE>SigmaF)fFit->SetParLimits(gPeakSigma,1E-3,SigmaF+SigmaFE);
		else fFit->SetParLimits(gPeakSigma,SigmaF-SigmaFE,SigmaF+SigmaFE);
	}else{
		fFit->FixParameter(gPeakSigma,SigmaF);
		fFit->FixParameter(gPeakSigmaB,2.0);
	}
	
	if(DecFree){// Decay of tail (beta) (or second gaus)
		double nsc=5.0;
		if(limittail)nsc=2.0;
		if(fParam[gPeakDecay]>fParam[gPeakSigma]*nsc){
            fParam[gPeakDecay]=fParam[gPeakSigma]*0.25;
            fFit->SetParameter(gPeakDecay,fParam[gPeakDecay]);
        }
		fFit->SetParLimits(gPeakDecay, fParam[gPeakDecay]*0.5, fParam[gPeakSigma]*nsc);
	// 	if(limittail&&fParam[gPeakSigma]>2)fFit->SetParLimits(gPeakDecay, fParam[gPeakDecay]*0.5, 10.);
	}else if(DecayFE>0){
		if(DecayFE>DecayF)fFit->SetParLimits(gPeakDecay,1E-3,DecayF+DecayFE);
		else fFit->SetParLimits(gPeakDecay,DecayF-DecayFE,DecayF+DecayFE);
	}else fFit->FixParameter(gPeakDecay,DecayF);

	
	if(ShareFree){ // Sharing parameter
		fFit->FixParameter(gPeakSigmaC,fParam[gPeakSigmaC]);//Cannot have both components free, too many DOF
		if(fParam[gPeakSharing]>=0.6667)fFit->SetParLimits(gPeakSharing, fParam[gPeakSharing]*0.5, 1.0);		// Sharing (should never be >1)
		else fFit->SetParLimits(gPeakSharing, fParam[gPeakSharing]*0.5, fParam[gPeakSharing]*1.5);		// Sharing (should never be >1)
		if(limittail)fFit->SetParLimits(gPeakSharing,0.93,1.);
	}else if(ShareFE>0){
		double l=ShareF-ShareFE,u=ShareF+ShareFE;
		if(u>1)u=1;
		if(l<0)l=0;
		fFit->SetParLimits(gPeakSharing,l,u);
	}else fFit->FixParameter(gPeakSharing,ShareF);	


	///////// Peak zero  ////////

	fFit->SetParLimits(gPeakNH(0), fParam[gPeakNH(0)]*0.5, fHist->GetMaximum()*1.5);	// 0 Height
	
	if(fInput[0].CentConstrained){//Centroid
		double err=fInput[0].CentError;
		if(err>0){
			fFit->SetParLimits(gPeakNC(0), fParam[gPeakNC(0)]-err, fParam[gPeakNC(0)]+err); 
		}else{
			fFit->FixParameter(gPeakNC(0), fParam[gPeakNC(0)]);
		}
	}else{
		fFit->SetParLimits(gPeakNC(0), fParam[gPeakNC(0)]-3, fParam[gPeakNC(0)]+3); 
	}
	
	
	///////// Additional Peaks ////////
	
	double fFree=1;
	for(int i=1;i<fNp;i++){
		int h=gPeakNH(i),c=gPeakNC(i);
		if(fInput[i].Ratio>0){// Height/ratio
			double err=fInput[i].RatioError;
			if(err>0){
				fFit->SetParLimits(h, fParam[h]-err, fParam[h]+err);
			}else{
				fFit->FixParameter(h,fParam[h]);
			}
		}else{
			fFit->SetParLimits(h, fParam[h]*0.2, fParam[h]*4);	// Height
		}
		
		if(fInput[i].CentConstrained){//Centroid
			double err=fInput[i].CentError;
			if(err>0){
				fFit->SetParLimits(c, fParam[c]-err, fParam[c]+err);
				fFree+=0.5;
			}else{
				fFit->FixParameter(c,fParam[c]);
			}
		}else{
			fFree+=1;
			fFit->SetParLimits(c, fParam[c]-2*fFree, fParam[c]+2*fFree);
		}
	}
	
	//////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////// FULL FIT //////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
// 	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(9999);
	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(10000);

	
	TH1* fFitHist=fHist;
	if(fExHist)fFitHist=fExHist;//Use the bin cancelled exclusion histogram if passed

	fFitHist->Fit(fFit, "RMNQ");//Get close, then do extra fit with error analysis
	
	TFitResultPtr fResult;
	if(statmode==0)fResult=fFitHist->Fit(fFit, "RMENS");
	if(statmode==1)fResult=fFitHist->Fit(fFit, "RMNSL");
	if(statmode==2)fResult=fFitHist->Fit(fFit, "RENSWL");
	
	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////// POST FIT OUTPUT ///////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	
	
	// Dont print the whole detail every time, just print when error or parameter limit
	for(unsigned int i=0;i<NparFromN(fNp);i++){
		double sU,sD,sP;
		fFit->GetParLimits(i,sD,sU);
		if(sU>sD){
            double sR=abs(sU-sD);
            if(sR==0)continue;
			sP=fFit->GetParameter(i);
			if(abs(sU-sP)/sR<1E-4)cout<<endl<<fFit->GetParName(i)<<" at/near UPPER limit : "<<sU<<endl;
			if(abs(sD-sP)/sR<1E-4)cout<<endl<<fFit->GetParName(i)<<" at/near LOWER limit : "<<sD<<endl;
		}
	}
	
	if(fResult->Status()!=4000){
		cout<<endl<<"FIT FAILURE."<<endl;
// 		return 0;
	}
	
	
	if(statmode>0)cout<<endl<<"Likelihood fit, use 'chi-squared' with caution!"<<flush;
	if(statmode>1)cout<<endl<<"Weighted Likelihood fit, errors can be weird. Recommend using error from integral form."<<flush;
	
	FullFitHolder* fHold = new FullFitHolder(fFit,fResult->GetCovarianceMatrix(),fPeakFunc.cBits);
	
    bool infl=false;
	if(statmode==0){
		cout<<endl<<"Fit Area Errors inflated by sqrt(RedChi)"<<flush;
        infl=true;
	}
    fHold->SetBit(Ultrapeak::kInflate,infl);
    fHold->RedChiInflateErr=infl;
    
	//This form does not calculate the integral if exclusion range overlaps
	Ultrapeak::MakeData(fHold,fHist,fExHist);
	
	return fHold;	
}

FullFitHolder* Ultrapeak::QuickPeakFit(TH1* fHist,double fLeftUser,double fRightUser, bool fExtraOpt){
	if(!fHist)return 0;
	int maxbin=0;
	double maxval=0;
	int fLeftBin=fHist->GetXaxis()->FindBin(fLeftUser),fRightBin=fHist->GetXaxis()->FindBin(fRightUser);
	
	for(int i=fLeftBin;i<=fRightBin;i++){
		double C=fHist->GetBinContent(i);
		if(C>maxval){maxval=C;maxbin=i;}
	}
	
	vector< jPeakDat > P;
	P.push_back(jPeakDat(fHist->GetXaxis()->GetBinCenter(maxbin)));
	
	FullFitHolder* FFH;
    if(fExtraOpt){
        FFH=PeakFit(fHist,fLeftUser,fRightUser,P,cBackType1s,0,0,"5+500","5+500","",0);
    }else{
        FFH=PeakFit(fHist,fLeftUser,fRightUser,P);
    }
    
	if(FFH){
		PrintData(FFH,true,fHist);
		FFH->Draw("same");
	}
	return FFH;
}
