#include "james_ultrapeak.h"

void Ultrapeak::DrawPeak(FullFitHolder* fFit,TCanvas* pad,TH1* fHist){
	if(pad)pad->cd();

	double fLower,fUpper;
	fFit->GetRange(fLower,fUpper);
	double fPar[48];
	fFit->GetParameters(fPar);
	int N=NfromTF1(fFit);
	
	//This function is purely graphical AND heights are used within this function,
	//so rather than setting Ultrapeak bits we replace the parameters (using the bits)	
	double fParam[48];
	FixParameters(fPar,fParam,N,fFit->cBits);
	//Consequently we need to turn off any pesky ratio bits that were on.
	Ultrapeak fPeakFunc(N,fFit->cBits);
	for(int i=0;i<N;i++)fPeakFunc.SetBit(PBits(i),0);
	
	TF1 *fDraw = new TF1("fDraw",fPeakFunc,fLower,fUpper,fFit->GetNpar());fDraw->SetNpx(1000);
	fPeakFunc.SetBit(kPeaks,0);//Switch off the peaks for the background line
	TF1 *fBack = new TF1("fBack",fPeakFunc,fLower,fUpper,fFit->GetNpar());fBack->SetNpx(1000);
	
	fDraw->SetParameters(fParam);//Copy in those simplified parameters
	fBack->SetParameters(fParam);
	
	if(pad&&fHist)fHist->DrawCopy();
	
	fBack->SetLineColor(1);
	fBack->SetLineStyle(7);	
	if(pad)fBack->DrawCopy("same");
	if(fHist)fHist->GetListOfFunctions()->Add(fBack->Clone());//NOT A TRUE CLONE, IS EMPTY OF COMPUTATION
	
	fDraw->SetLineColor(36);
	fDraw->SetLineStyle(3);
	
	double fStepSum=0;
	for(int i=0;i<N;i++){
		fStepSum+=fParam[gPeakNH(i)];
		fDraw->SetParameter(gPeakNH(i),0);//turn off all peaks
	}
	fStepSum=fParam[gUltraStep]/fStepSum;
	
	if(N>1){
		for(int i=0;i<N;i++){
			fDraw->SetParameter(gPeakNH(i),fParam[gPeakNH(i)]);//turn one peak on
			if(fPeakFunc.TestBit(kStep))fDraw->SetParameter(gUltraStep,fParam[gPeakNH(i)]*fStepSum);//adjust background step
			if(pad)fDraw->DrawCopy("same");
			if(fHist)fHist->GetListOfFunctions()->Add(fDraw->Clone());//NOT A TRUE CLONE, IS EMPTY OF COMPUTATION
			fDraw->SetParameter(gPeakNH(i),0);//turn it back off
		}
	}
	
	//Moved this to last (necessitating resetting line and params) so that it is last in function list of TH1
	fDraw->SetParameters(fParam);
	fDraw->SetLineColor(2);
	fDraw->SetLineStyle(1);
	if(pad)fDraw->DrawCopy("same");
	if(fHist)fHist->GetListOfFunctions()->Add(fDraw->Clone());//NOT A TRUE CLONE, IS EMPTY OF COMPUTATION
	
	delete fDraw;
	delete fBack;	
	
	gPad->Modified();
	gPad->Update();
}

// Calculated the peak error based on fit parameters
// If binwidth!=1 is provided the areas will be accordingly corrected
void Ultrapeak::MakeData(FullFitHolder* fHold,double binwidth){
    
    //As this is the value in CVal, if it is not set, MakeData will be re-called later.
    fHold->CVal(VPIe(NfromTF1(fHold)-1),0);

	// Prepare by getting all the info
	double fLower,fUpper;
	fHold->GetRange(fLower,fUpper);
	int N=NfromTF1(fHold);//number of peaks
	fHold->CVal(VN,N);
	
	double fParam[48];
	fHold->GetParameters(fParam);

// 	string fName="Bkgd Grad";
// 	if(strcmp(fHold->GetParName(1), fName.c_str())==0)step=0;
	
	// Start calculating and adding things
	fHold->CVal(VChi,fHold->ReducedChi());
	
	double sCentroid=0;// Because peaks are relative
	double sCentError=0;
	
	// Dumb little offset from complex new peak thing 
	double fCentOff=TrueCentroid(sCentroid,fParam[gPeakSigma],fParam[gPeakDecay],fParam[gPeakSharing]);
	fHold->CVal(VOff,fCentOff);
	
	for(int i=0;i<N;i++){
		
		// Centroid and Error
		sCentroid+=fParam[gPeakNC(i)];
		sCentError+=fHold->GetParError(gPeakNC(i));
// 		fHold->CVal(VPC(i),sCentroid);
// 		fHold->CVal(VPCe(i),sCentError);
        
		UltrapeakCentroid fPeakCent(i,fHold->cBits);
		TF1 fCent("fCent",fPeakCent,-1,1,fHold->GetNpar());
		fCent.SetParameters(fParam);
		fHold->CVal(VPC(i),fCent.Eval(0));
		fHold->CVal(VPCe(i),AnalyticalFullCovError(&fCent,fHold->GetCov()));
        // Now a full covariant centroid error
		
		// Full Area Count
		UltrapeakArea fPeakArea(i,fHold->cBits);
		TF1 fArea("fArea",fPeakArea,-1,1,fHold->GetNpar());
		fArea.SetParameters(fParam);
		double sA=fArea.Eval(0);
		double sE=AnalyticalFullCovError(&fArea,fHold->GetCov());
		if(sE<sqrt(abs(sA)))sE=sqrt(abs(sA));
		fHold->CVal(VPA(i),sA/binwidth);
		fHold->CVal(VPAe(i),sE/binwidth);
	}
}

// Calculate areas based on fit function and integration
// Requires the histogram that was the target of the fit
void Ultrapeak::MakeData(FullFitHolder* fHold,TH1* hist,bool exclusion){

	//Calculate the area from the peak function
	MakeData(fHold,hist->GetXaxis()->GetBinWidth(1));
	
	//Calculate the area from the histogram integral
	
	double fParam[48];
	fHold->GetParameters(fParam);
	int N=NfromTF1(fHold);//number of peaks	
    
    vector<int> upbin;
    vector<int> downbin;
    vector<vector<int>> ipeak;
    vector<bool> used(N,true);
    
    double sig3=fParam[gPeakSigma]*3;
    if(fHold->TestBit(Ultrapeak::k2Gaus))sig3*=fParam[gPeakSigmaB];
    double tail=3.9*(1-fParam[gPeakSharing])*fParam[gPeakDecay];
    tail+=sig3;
    
    //Find the bin discrete integration limits
	for(int i=0;i<N;i++){
        upbin.push_back(hist->FindBin(fHold->CVal(VPC(i))+sig3));
        downbin.push_back(hist->FindBin(fHold->CVal(VPC(i))-tail));
        ipeak.push_back(vector<int>(1,i));        
    }
    
    int groupsN=N;
    
    //Check for overlap in integration area
	for(int i=N-1;i>=0;i--){
        for(int j=i-1;j>=0;j--){            
            if((upbin[i]>=downbin[j]&&upbin[i]<=upbin[j])||
            (upbin[j]>=downbin[i]&&upbin[j]<=upbin[i])){
                if(upbin[j]<upbin[i])upbin[j]=upbin[i];
                if(downbin[j]>downbin[i])downbin[j]=downbin[i];
                for(unsigned int s=0;s<ipeak[i].size();s++){
                    ipeak[j].push_back(ipeak[i][s]);
                }
                
                used[i]=false;
                groupsN--;
                j=-1;
                break;
            }
        }
    }
    
//     cout<<endl<<endl<<"groupsN "<<groupsN;
    
	for(int i=0;i<N;i++){
        if(!used[i])continue;
        
        // If exclusion ranges were used in the fit, check if any of the ranges interfere
        if(exclusion){
            bool goodrange=true;
            for(int b=downbin[i];b<=upbin[i];b++){
                if(hist->GetBinContent(b)==0){
                    goodrange=false;
                    break;
                }
            }
            if(!goodrange)continue;
        }
        
        // Calculate full integrals
        double fLower=hist->GetXaxis()->GetBinLowEdge(downbin[i]);
        double fUpper=hist->GetXaxis()->GetBinUpEdge(upbin[i]);
        double total=hist->Integral(downbin[i],upbin[i]);
        
        // Prepare our background functions
        Ultrapeak fPeakFunc(N,fHold->cBits);
        fPeakFunc.SetBit(kPeaks,0);
        TF1 fBack("fBack",fPeakFunc,fLower,fUpper,fHold->GetNpar());
        fBack.SetParameters(fParam);
        double fIntegralBack=fBack.Integral(fLower,fUpper)/hist->GetXaxis()->GetBinWidth(1);
        
        // Start calculating and adding things
        double peakcounts=total-fIntegralBack;
        double peakcerror=sqrt(total+fIntegralBack);
        
        if(ipeak[i].size()>1){
            UltrapeakFrac fPeakFrac(ipeak[i],N,0,fHold->cBits);
            for(unsigned int s=0;s<ipeak[i].size();s++){
                int Ni=ipeak[i][s];
                fPeakFrac.N_i=Ni;
                TF1 fFrac("fFrac",fPeakFrac,-1,1,fHold->GetNpar());
                fFrac.SetParameters(fParam);
                double pF=fFrac.Eval(0);
                double pFE=AnalyticalFullCovError(&fFrac,fHold->GetCov());
                
          		double peak=peakcounts*pF;
                double peakerror=pow(pFE/pF,2)+pow(peakcerror/peakcounts,2);	
                peakerror=sqrt(peakerror)*peak;
                // Integral Area Count
            
                fHold->CVal(VPI(Ni),peak);
                fHold->CVal(VPIe(Ni),peakerror);      
            }  
        }else{
            fHold->CVal(VPI(i),peakcounts);
            fHold->CVal(VPIe(i),peakcerror);   
        }
    }
}

void Ultrapeak::InflateError(FullFitHolder* fHold){
	if(fHold->TestBit(Ultrapeak::kInflate))return;
	double RedChi=fHold->ReducedChi();
	if(RedChi>1&&RedChi<1E5){
		RedChi=sqrt(RedChi);
		for(int i=0;i<fHold->CVal(VN);i++){
			double err=RedChi*fHold->CVal(VPAe(i));
			fHold->CVal(VPAe(i),err);
		}
		fHold->SetBit(Ultrapeak::kInflate);
	}
	return;
}

void Ultrapeak::PrintTitles(ostream& ofs){
	ofs<<endl<<setw(10)<<"Red.Chi."<<setw(11)<<"X max."<<setw(11)<<"Cent."<<setw(11)<<"[error]";
	ofs<<setw(11)<<"Area."<<setw(11)<<"[error]";
	ofs<<setw(11)<<"Int."<<setw(11)<<"[error]"<<flush;
}       

void Ultrapeak::PrintData(FullFitHolder* fHold,bool titles,TH1* hist,ostream& ofs){
	if(fHold->CValS()<VPIe(NfromTF1(fHold)-1))MakeData(fHold,hist);
	PrintData(fHold,titles,hist->GetXaxis()->GetBinWidth(1),ofs);
}
void Ultrapeak::PrintData(FullFitHolder* fHold,bool titles,double binwidth,ostream& ofs){
	
	int N=NfromTF1(fHold);//number of peaks
	if(titles) PrintTitles();
		
	if(fHold->CValS()<VPAe(N-1))MakeData(fHold,binwidth);

	for(int i=0;i<N;i++){
		//New error check
		double delta_A=fHold->CVal(VPA(i))-fHold->CVal(VPI(i));
		double sumerr=fHold->CVal(VPAe(i))+fHold->CVal(VPIe(i));
		bool fiterr=(abs(delta_A)>sumerr);
		
		ofs<<endl<<setw(10)<<fHold->CVal(VChi);//chi
		ofs<<" "<<setw(10)<<fHold->CVal(VPC(i))-fHold->CVal(VOff)<<" "<<setw(10)<<fHold->CVal(VPC(i))<<" "<<setw(10)<<fHold->CVal(VPCe(i));
		ofs<<" "<<setw(10)<<fHold->CVal(VPA(i))<<" "<<setw(10)<<fHold->CVal(VPAe(i));
		if(fHold->CVal(VPI(i))>0){
			ofs<<" "<<setw(10)<<fHold->CVal(VPI(i))<<" "<<setw(10)<<fHold->CVal(VPIe(i))<<flush;
			if(fiterr)ofs<<" Err."<<flush;
		}else{
			ofs<<" "<<setw(10)<<" -"<<" "<<setw(10)<<" -"<<flush;
		}
	}	
}


//////////////////////////////////////////////////////
/////////////// Ultra peak fit //////////////////////
//////////////////////////////////////////////////////


FullFitHolder* Ultrapeak::PeakFit(TH1* fHist,double fLeftUser,double fRightUser,vector< jPeakDat > &fInput,int backmode,int peaktype,string sig,string dec,string sha,TH1* fExHist){
	// This function takes in peak positions as a series of relative positions
	// This creates undue correlation between centroid positions 
	// However this is the best way to fix the distance between pairs (or more)
	// Which is a likely desire if fitting multiple peaks anyway
	// All entries are relative to the previous one, so place them in the correct order for any linked pairs
    
	bool fixgamma=false;
	bool twogaus=false;
	if(peaktype==1)fixgamma=true;
	if(peaktype==2)twogaus=true;
	
	// Possible problems:
	// Peak parameters are estimated from an initial fit which assumes peak zero is the furthest left peak 

	//Check any shape parameter overrides
	bool SigFree=true,DecFree=true,ShareFree=true;
	double SigmaF,SigmaFE,DecayF,DecayFE,ShareF,ShareFE;
	ExtractError(sig,SigmaF,SigmaFE);if(SigmaF>0)SigFree=false;
	ExtractError(dec,DecayF,DecayFE);if(DecayF>0)DecFree=false;
	if(sha.size()>0){ExtractError(sha,ShareF,ShareFE);if(ShareF<=1)ShareFree=false;}
	
	cout<<endl<<endl<<endl<<endl;
	
	unsigned int fNp=fInput.size();if(fNp<1)return 0;
	if(fNp>10)fNp=10;

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
	for(unsigned int i=0;i<fNp;i++)fPeaks.push_back(fInput[i].Centroid);
		
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
	
	double fParam[48]={48,0}; //Holder for parameters, initial guess and limits needed for good minimisation 

	fParam[gUltraPol1] = (fRightHeight-fLeftHeight)/(fRightUser-fLeftUser); //grad
	fParam[gUltraPol0] = fRightHeight-fRightUser*fParam[gUltraPol1]; //intercept
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
	for(unsigned int i=1;i<3&&i<fNp;i++){
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
	Ultrapeak fPeakFunc(1,1,1,0,twogaus);//Control parameters (peaks #,peaks 0/1,background 0/1,steptype 0/1)
	TF1 *fPre = new TF1("fPre",fPeakFunc,fLeftUser,fPeaks[0]+4,NparFromN(1));
	
	fPre->SetParName(gUltraPol0,"Pol0");
	fPre->SetParName(gUltraPol1,"Pol1");
	fPre->SetParName(gUltraOffsetOrPol2,"NULL");
	fPre->SetParName(gUltraStep,"NULL");
	fPre->SetParName(gPeakSigma,"Sigma");
	fPre->SetParName(gPeakDecay,"Decay");
	if(twogaus){
		fPre->SetParName(gPeakSigmaB,"SigmaRatio");
		fPre->SetParName(gPeakSigmaC,"TGHRatio");
	}else{
		fPre->SetParName(gPeakSigmaB,"na");
		fPre->SetParName(gPeakSigmaC,"na");
	}
	
	fPre->SetParName(gPeakSharing,"Sharing");
	fPre->SetParName(gPeakNH(0),"Height");
	fPre->SetParName(gPeakNC(0),"Centroid");
	
	fPre->SetParameters(fParam);
	fPre->FixParameter(gUltraPol0, fParam[gUltraPol0]); //background constant
	fPre->FixParameter(gUltraPol1, fParam[gUltraPol1]); //background grad
	fPre->FixParameter(gUltraOffsetOrPol2, 0);
	fPre->FixParameter(gUltraStep, 0);
	
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
		if(fixgamma)fPre->SetParLimits(gPeakDecay, 1.0, 4.);  // Decay of tail (beta)
		else fPre->SetParLimits(gPeakDecay, 1.0, 60.);  // Decay of tail (beta)
	}else if(DecayFE>0){
		if(DecayFE>DecayF)fPre->SetParLimits(gPeakDecay,1E-3,DecayF+DecayFE);
		fPre->SetParLimits(gPeakDecay,DecayF-DecayFE,DecayF+DecayFE);
	}else fPre->FixParameter(gPeakDecay,DecayF);
		
	if(ShareFree){
		if(fixgamma)fPre->SetParLimits(gPeakSharing, 0.93, 1.);// Sharing parameter
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
	for(unsigned int i=1;i<fNp;i++)
		if(fInput[i].Ratio>0)
			fPeakFunc.SetBit(PBits(i));

		
	TF1 *fFit = new TF1("fFit",fPeakFunc,fLeftUser,fRightUser,NparFromN(fNp));
	
	//////////////////////////////////// SET PARAMETERS ////////////////////////////////
	
	///////// Background parameters	////////
	// "pol0+step",  // pol0 fixed based on RHS and step RHS-LHS diff
	// "pol1 fixed", // Grad fixed from LHS RHS and offset slightly free
	// "pol1",       // Offset fixed at centre point, offset and grad slightly free (pol1 see-saw)
	// "pol1+step",  // Offset pinned at RHS, grad set to half and step RHS-LHS diff (pol1 hinge) 
	// "pol2",	  // Pretty free, initial inputs as pol1
	// "pol2+step",  // Pretty free, initial inputs as pol1
	
	fFit->SetParName(gUltraPol0,"Pol0");
	fFit->SetParName(gUltraPol1,"Pol1");
    fFit->SetParName(gUltraOffsetOrPol2,"Pol2");
    
    int polorder=PolOrder(backmode);
	if(polorder==0){
        fFit->SetParName(gUltraPol1,"na");
        fFit->SetParName(gUltraOffsetOrPol2,"na");
		fParam[gUltraPol0]=fRightHeight;
		fParam[gUltraPol1]=0;
		fParam[gUltraOffsetOrPol2]=0;
	}else if(polorder==1){
		fFit->SetParName(gUltraOffsetOrPol2,"Pol1Offset");
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
        fFit->SetParName(gUltraStep,"Bkgd Step");
		fParam[gUltraStep]=fLeftHeight-fRightHeight;
	}else{
        fFit->SetParName(gUltraStep,"na");
		fParam[gUltraStep]=0.0;
	}

	
	///////// Shape parameters ////////
	
	fFit->SetParName(gPeakSigma,"Sigma");
	fFit->SetParName(gPeakDecay,"Decay");
	fFit->SetParName(gPeakSharing,"Sharing");
	
	if(twogaus){
		fFit->SetParName(gPeakSigmaB,"SigmaRatio");
		fFit->SetParName(gPeakSigmaC,"TGHRatio");
		fParam[gPeakSigmaB]=2.0;
		fParam[gPeakSigmaC]=0.6;
	}else{
		fFit->SetParName(gPeakSigmaB,"na");
		fFit->SetParName(gPeakSigmaC,"na");
		fParam[gPeakSigmaB]=0.0;
		fParam[gPeakSigmaC]=0.0;
	}
	
	///////// Peak zero  ////////

	fFit->SetParName(gPeakNH(0),"Height 0");
	fFit->SetParName(gPeakNC(0),"Peak 0");
	
	///////// Additional Peaks ////////
	
	double sPe=fPeaks[0];
	for(unsigned int i=1;i<fNp;i++){
		stringstream ss;
		ss<<i;
		fFit->SetParName(gPeakNC(i),("Peak "+ss.str()).c_str());
		fParam[gPeakNC(i)]=fPeaks[i];
		sPe+=fPeaks[i];
		double lH=fHist->GetBinContent(fHist->GetXaxis()->FindBin(sPe));
		double lB=fLin.Eval(sPe);
		double pH=lH-lB;
		if(pH<=0)pH=abs(lH);
		
		if(fInput[i].Ratio>0){//peak height ratio not actual height
			fFit->SetParName(gPeakNH(i),("Ratio "+ss.str()).c_str());
			fParam[gPeakNH(i)]=fInput[i].Ratio;
		}else{
			fFit->SetParName(gPeakNH(i),("Height "+ss.str()).c_str());
			fParam[gPeakNH(i)]=pH;
		}
	}	
	
	fFit->SetParameters(fParam);
	
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
    }else{
        fFit->FixParameter(gUltraStep,0);
    }
	
    if(polorder==0){
        fFit->FixParameter(gUltraPol1,0);
		fFit->FixParameter(gUltraOffsetOrPol2,0);
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
    

	///////// Shape parameters ////////
	
	if(twogaus){
		fFit->SetParLimits(gPeakSigmaB,1.01,5);
		fFit->SetParLimits(gPeakSigmaC,0.01,0.99);
	}else{
		fFit->FixParameter(gPeakSigmaB,0.0);
		fFit->FixParameter(gPeakSigmaC,0.0);
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
		if(fixgamma)nsc=2.0;
		if(fParam[gPeakDecay]>fParam[gPeakSigma]*nsc){fParam[gPeakDecay]=fParam[gPeakSigma]*0.25;fFit->SetParameter(gPeakDecay,fParam[gPeakDecay]);}
		fFit->SetParLimits(gPeakDecay, fParam[gPeakDecay]*0.5, fParam[gPeakSigma]*nsc);
	// 	if(fixgamma&&fParam[gPeakSigma]>2)fFit->SetParLimits(gPeakDecay, fParam[gPeakDecay]*0.5, 10.);
	}else if(DecayFE>0){
		if(DecayFE>DecayF)fFit->SetParLimits(gPeakDecay,1E-3,DecayF+DecayFE);
		else fFit->SetParLimits(gPeakDecay,DecayF-DecayFE,DecayF+DecayFE);
	}else fFit->FixParameter(gPeakDecay,DecayF);

	
	if(ShareFree){ // Sharing parameter
		fFit->FixParameter(gPeakSigmaC,fParam[gPeakSigmaC]);//Cannot have both components free, too many dof
		if(fParam[gPeakSharing]>=0.6667)fFit->SetParLimits(gPeakSharing, fParam[gPeakSharing]*0.5, 1.0);		// Sharing (should never be >1)
		else fFit->SetParLimits(gPeakSharing, fParam[gPeakSharing]*0.5, fParam[gPeakSharing]*1.5);		// Sharing (should never be >1)
		if(fixgamma)fFit->SetParLimits(gPeakSharing,0.93,1.);
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
	for(unsigned int i=1;i<fNp;i++){
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
			sP=fFit->GetParameter(i);
			if(abs(sU-sP)<1E-6)cout<<endl<<fFit->GetParName(i)<<" at/near UPPER limit : "<<sU<<endl;
			if(abs(sD-sP)<1E-6)cout<<endl<<fFit->GetParName(i)<<" at/near LOWER limit : "<<sD<<endl;
		}
	}
	
	if(fResult->Status()!=4000||fParam[0]<=0){
		cout<<endl<<"FIT FAILURE."<<endl;
// 		return 0;
	}
	
	
	if(statmode>0)cout<<endl<<"Likelihood fit, use 'chi-squared' with caution!"<<flush;
	if(statmode>1)cout<<endl<<"Weighted Likelihood fit, errors can be weird. Recommend using error from integral form."<<flush;
	
	FullFitHolder* fHold = new FullFitHolder(fFit,fResult->GetCovarianceMatrix(),fPeakFunc.cBits);
	
	if(fExHist){
		//This form does not calculate the integral answers because an exclusion histogram was used
        //Ultrapeak::MakeData(fHold,fHist->GetXaxis()->GetBinWidth(1));
        
        //This form does not calculate the integral if exclusion range overlaps
        Ultrapeak::MakeData(fHold,fExHist,true);
	}else{
		Ultrapeak::MakeData(fHold,fHist);
	}
    
	
	if(statmode==0){
		Ultrapeak::InflateError(fHold);
		cout<<endl<<"Fit Areas Errors inflated by sqrt(RedChi)"<<flush;
	}
	
	return fHold;	
}

FullFitHolder* Ultrapeak::QuickPeakFit(TH1* fHist,double fLeftUser,double fRightUser){
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
	
	FullFitHolder* FFH=PeakFit(fHist,fLeftUser,fRightUser,P);
	if(FFH){
		MakeData(FFH,fHist);
		FFH->Draw("same");
	}
	return FFH;
}



	
Double_t _fx1[348] = {-4,-3.984,-3.968,-3.952,-3.936,-3.92,-3.904,-3.888,-3.872,-3.856,-3.84,-3.824,-3.808,-3.792,-3.776,-3.76,-3.744,-3.728,-3.712,-3.696,-3.68,-3.664,-3.648,-3.632,-3.616,-3.6,-3.584,-3.568,-3.552,-3.536,-3.52,-3.504,-3.488,-3.472,-3.456,-3.44,-3.424,-3.408,-3.392,-3.376,-3.36,-3.344,-3.328,-3.312,-3.296,-3.28,-3.264,-3.248,-3.232,-3.216,-3.2,-3.184,-3.168,-3.152,-3.136,-3.12,-3.104,-3.088,-3.072,-3.056,-3.04,-3.024,-3.008,-2.992,-2.976,-2.96,-2.944,-2.928,-2.912,-2.896,-2.88,-2.864,-2.848,-2.832,-2.816,-2.8,-2.784,-2.768,-2.752,-2.736,-2.72,-2.704,-2.688,-2.672,-2.656,-2.64,-2.624,-2.608,-2.592,-2.576,-2.56,-2.544,-2.528,-2.512,-2.496,-2.48,-2.464,-2.448,-2.432,-2.416,-2.4,-2.384,-2.368,-2.352,-2.336,-2.32,-2.304,-2.288,-2.272,-2.256,-2.24,-2.224,-2.208,-2.192,-2.176,-2.16,-2.144,-2.128,-2.112,-2.096,-2.08,-2.064,-2.048,-2.032,-2.016,-2,-1.984,-1.968,-1.952,-1.936,-1.92,-1.904,-1.888,-1.872,-1.856,-1.84,-1.824,-1.808,-1.792,-1.776,-1.76,-1.744,-1.728,-1.712,-1.696,-1.68,-1.664,-1.648,-1.632,-1.616,-1.6,-1.584,-1.568,-1.552,-1.536,-1.52,-1.504,-1.488,-1.472,-1.456,-1.44,-1.424,-1.408,-1.392,-1.376,-1.36,-1.344,-1.328,-1.312,-1.296,-1.28,-1.264,-1.248,-1.232,-1.216,-1.2,-1.184,-1.168,-1.152,-1.136,-1.12,-1.104,-1.088,-1.072,-1.056,-1.04,-1.024,-1.008,-0.992,-0.976,-0.96,-0.944,-0.928,-0.912,-0.896,-0.88,-0.864,-0.848,-0.832,-0.816,-0.8,-0.784,-0.768,-0.752,-0.736,-0.72,-0.704,-0.688,-0.672,-0.656,-0.64,-0.624,-0.608,-0.592,-0.576,-0.56,-0.544,-0.528,-0.512,-0.496,-0.48,-0.464,-0.448,-0.432,-0.416,-0.4,-0.384,-0.368,-0.352,-0.336,-0.32,-0.304,-0.288,-0.272,-0.256,-0.24,-0.224,-0.208,-0.192,-0.176,-0.16,-0.144,-0.128,-0.112,-0.096,-0.08,-0.064,-0.048,-0.032,-0.016,0,0.016,0.032,0.048,0.064,0.08,0.096,0.112,0.128,0.144,0.16,0.176,0.192,0.208,0.224,0.24,0.256,0.272,0.288,0.304,0.32,0.336,0.352,0.368,0.384,0.4,0.416,0.432,0.448,0.464,0.48,0.496,0.512,0.528,0.544,0.56,0.576,0.592,0.608,0.624,0.64,0.656,0.672,0.688,0.704,0.72,0.736,0.752,0.768,0.784,0.8,0.816,0.832,0.848,0.864,0.88,0.896,0.912,0.928,0.944,0.96,0.976,0.992,1.008,1.024,1.04,1.056,1.072,1.088,1.104,1.12,1.136,1.152,1.168,1.184,1.2,1.216,1.232,1.248,1.264,1.28,1.296,1.312,1.328,1.344,1.36,1.376,1.392,1.408,1.424,1.44,1.456,1.472,1.488,1.504,1.52,1.536,1.552};Double_t _fy1[348] = {-40.7231,-40.6326,-40.5418,-40.4509,-40.3598,-40.2684,-40.1769,-40.0851,-39.9931,-39.901,-39.8086,-39.716,-39.6232,-39.5301,-39.4369,-39.3434,-39.2497,-39.1558,-39.0617,-38.9673,-38.8728,-38.7779,-38.6829,-38.5876,-38.4921,-38.3964,-38.3004,-38.2042,-38.1077,-38.0111,-37.9141,-37.8169,-37.7195,-37.6218,-37.5239,-37.4257,-37.3273,-37.2286,-37.1297,-37.0305,-36.931,-36.8313,-36.7313,-36.631,-36.5305,-36.4297,-36.3286,-36.2273,-36.1256,-36.0237,-35.9215,-35.8191,-35.7163,-35.6133,-35.5099,-35.4063,-35.3024,-35.1982,-35.0936,-34.9888,-34.8837,-34.7783,-34.6725,-34.5665,-34.4601,-34.3534,-34.2464,-34.1391,-34.0315,-33.9235,-33.8152,-33.7066,-33.5976,-33.4883,-33.3787,-33.2687,-33.1584,-33.0477,-32.9367,-32.8253,-32.7135,-32.6014,-32.489,-32.3762,-32.263,-32.1494,-32.0355,-31.9212,-31.8065,-31.6914,-31.5759,-31.4601,-31.3438,-31.2272,-31.1101,-30.9927,-30.8748,-30.7565,-30.6379,-30.5188,-30.3993,-30.2793,-30.159,-30.0382,-29.9169,-29.7953,-29.6732,-29.5506,-29.4276,-29.3042,-29.1803,-29.0559,-28.9311,-28.8058,-28.68,-28.5538,-28.4271,-28.2999,-28.1722,-28.044,-27.9153,-27.7862,-27.6565,-27.5264,-27.3957,-27.2645,-27.1328,-27.0006,-26.8678,-26.7346,-26.6008,-26.4664,-26.3316,-26.1961,-26.0602,-25.9237,-25.7866,-25.649,-25.5108,-25.372,-25.2327,-25.0928,-24.9524,-24.8113,-24.6697,-24.5275,-24.3847,-24.2413,-24.0973,-23.9527,-23.8075,-23.6617,-23.5153,-23.3683,-23.2207,-23.0724,-22.9236,-22.7741,-22.624,-22.4732,-22.3219,-22.1699,-22.0173,-21.864,-21.7102,-21.5556,-21.4005,-21.2447,-21.0883,-20.9312,-20.7735,-20.6152,-20.4562,-20.2966,-20.1364,-19.9755,-19.814,-19.6519,-19.4891,-19.3257,-19.1617,-18.9971,-18.8319,-18.666,-18.4995,-18.3325,-18.1648,-17.9966,-17.8277,-17.6583,-17.4883,-17.3178,-17.1467,-16.975,-16.8028,-16.6301,-16.4569,-16.2832,-16.109,-15.9343,-15.7591,-15.5835,-15.4075,-15.231,-15.0541,-14.8769,-14.6992,-14.5213,-14.343,-14.1644,-13.9855,-13.8063,-13.6269,-13.4473,-13.2675,-13.0875,-12.9075,-12.7273,-12.547,-12.3667,-12.1863,-12.006,-11.8258,-11.6456,-11.4656,-11.2857,-11.106,-10.9266,-10.7475,-10.5687,-10.3902,-10.2122,-10.0346,-9.8575,-9.681,-9.5051,-9.3298,-9.1553,-8.9815,-8.8085,-8.6363,-8.4651,-8.2948,-8.1255,-7.9573,-7.7902,-7.6243,-7.4597,-7.2963,-7.1343,-6.9737,-6.8146,-6.657,-6.5009,-6.3465,-6.1938,-6.0428,-5.8935,-5.7461,-5.6006,-5.457,-5.3154,-5.1758,-5.0383,-4.9029,-4.7696,-4.6385,-4.5096,-4.3829,-4.2586,-4.1365,-4.0167,-3.8993,-3.7842,-3.6715,-3.5611,-3.4532,-3.3476,-3.2445,-3.1437,-3.0453,-2.9493,-2.8557,-2.7644,-2.6755,-2.5889,-2.5046,-2.4225,-2.3427,-2.2651,-2.1898,-2.1165,-2.0454,-1.9764,-1.9094,-1.8445,-1.7815,-1.7205,-1.6613,-1.6041,-1.5486,-1.4949,-1.4429,-1.3926,-1.3439,-1.2968,-1.2513,-1.2073,-1.1648,-1.1237,-1.0839,-1.0456,-1.0085,-0.9727,-0.9381,-0.9047,-0.8725,-0.8414,-0.8113,-0.7823,-0.7544,-0.7274,-0.7013,-0.6762,-0.6519,-0.6285,-0.606,-0.5842,-0.5632,-0.543,-0.5234,-0.5046,-0.4864,-0.4689,-0.452,-0.4357,-0.42,-0.4049,-0.3903,-0.3762,-0.3627,-0.3496,-0.337,-0.3248,-0.3131,-0.3018,-0.2909,-0.2804};

TGraph Ultrapeak::DecayXR10(348,_fx1,_fy1);

double DecGausMaxX(double& sig,double& dec){
  return Ultrapeak::DecayXR10.Eval(log10(sig/dec))*(sig/10.);
}
