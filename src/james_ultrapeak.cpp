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
	fPeakFunc.SetBit(kPeaks,0);//Switch of the peaks for the background line
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

void Ultrapeak::MakeData(FullFitHolder* fHold,double binwidth){
	
	// Prepare by getting all the info
	double fLower,fUpper;
	fHold->GetRange(fLower,fUpper);
	int N=NfromTF1(fHold);//number of peaks
	fHold->CVal(VN,N);
	
	double fParam[48];
	fHold->GetParameters(fParam);

// 	string fName="Bkgd Grad";
// 	if(strcmp(fHold->GetParName(1), fName.c_str())==0)step=0;
	
	// Prepare pour gunctions
	Ultrapeak fPeakFunc(N,fHold->cBits);
	TF1 fInte("fInte",fPeakFunc,fLower,fUpper,fHold->GetNpar());
	fInte.SetParameters(fParam);
	double fIntegral=fInte.Integral(fLower,fUpper);
	fPeakFunc.SetBit(kBack,0);
	TF1 fPeaks("fPeaks",fPeakFunc,fLower,fUpper,fHold->GetNpar());
	fPeaks.SetParameters(fParam);
	double fIntegralPeaks=fPeaks.Integral(fLower,fUpper);
	
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
		fHold->CVal(VPC(i),sCentroid);
		fHold->CVal(VPCe(i),sCentError);
		
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
	fHold->CVal(VBI,(fIntegral-fIntegralPeaks)/binwidth);//The integral of the background over the fit area
}


void Ultrapeak::MakeData(FullFitHolder* fHold,TH1* hist){
	MakeData(fHold,hist->GetXaxis()->GetBinWidth(1));
	
	// Prepare by getting all the info
	double fLower,fUpper;
	fHold->GetRange(fLower,fUpper);
	int N=NfromTF1(fHold);//number of peaks
	fHold->CVal(VN,N);
	
	double fParam[48];
	fHold->GetParameters(fParam);

	// Start calculating and adding things
	int l=hist->FindBin(fLower);
	int u=hist->FindBin(fUpper);
	
	double total=hist->Integral(l+1,u-1);
	total+=(hist->GetBinContent(l)+hist->GetBinContent(u))*0.5;
	double peakcounts=total-fHold->CVal(VBI);
	double peakcerror=sqrt(total)+sqrt(fHold->CVal(VBI));

	for(int i=0;i<N;i++){
		UltrapeakFrac fPeakFrac(N,i,fHold->cBits);
		TF1 fFrac("fFrac",fPeakFrac,-1,1,fHold->GetNpar());
		fFrac.SetParameters(fParam);
		double pF=fFrac.Eval(0);
		double pFE=AnalyticalFullCovError(&fFrac,fHold->GetCov());
		
		double peak=peakcounts*pF;
		double peakerror=(pFE/pF)*(pFE/pF)+(peakcerror/peakcounts)*(peakcerror/peakcounts);	
		peakerror=sqrt(peakerror)*peak;
		// Integral Area Count
	
		fHold->CVal(VPI(i),peak);
		fHold->CVal(VPIe(i),peakerror);
	}
}

void Ultrapeak::PrintTitles(ostream& ofs){
	ofs<<endl<<setw(10)<<"Red.Chi."<<setw(11)<<"Cent."<<setw(11)<<"(True)"<<setw(11)<<"[error]";
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
		ofs<<endl<<setw(10)<<fHold->CVal(VChi);//chi
		ofs<<" "<<setw(10)<<fHold->CVal(VPC(i))<<" "<<setw(10)<<fHold->CVal(VPC(i))+fHold->CVal(VOff)<<" "<<setw(10)<<fHold->CVal(VPCe(i));
		ofs<<" "<<setw(10)<<fHold->CVal(VPA(i))<<" "<<setw(10)<<fHold->CVal(VPAe(i));
		ofs<<" "<<setw(10)<<fHold->CVal(VPI(i))<<" "<<setw(10)<<fHold->CVal(VPIe(i))<<flush;
	}	
}


//////////////////////////////////////////////////////
/////////////// Ultra peak fit //////////////////////
//////////////////////////////////////////////////////


FullFitHolder* Ultrapeak::PeakFit(TH1* fHist,double fLeftUser,double fRightUser,vector< jPeakDat > &fInput,int backmode,bool fixgamma,string sig,string dec,string sha){
	// This function takes in peak positions as a series of relative positions
	// This creates undue correlation between centroid positions 
	// However this is the best way to fix the distance between pairs (or more)
	// Which is a likely desire if fitting multiple peaks anyway
	// All entries are relative to the previous one, so place them in the correct order for any linked pairs
	
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
	
	//Takes averages of histogram for the right and left, so not so sensitive.//REDUCED FROM 5 TO 3
	double fLeftHeight = bins_smooth(fHist,fLeftBin,3);
	double fRightHeight = bins_smooth(fHist,fRightBin,3);
	double fLeftVar = 2*sqrt(bins_var(fHist,fLeftBin,3));	
	double fRightVar = 2*sqrt(bins_var(fHist,fRightBin,3));
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
	Ultrapeak fPeakFunc(1,1,1,0);//Control parameters (peaks #,peaks 0/1,background 0/1,steptype 0/1)
	TF1 *fPre = new TF1("fPre",fPeakFunc,fLeftUser,fPeaks[0]+4,NparFromN(1));
	
	fPre->SetParName(gUltraPol0,"Pol0");
	fPre->SetParName(gUltraPol1,"Pol1");
	fPre->SetParName(gUltraOffsetOrPol2,"NULL");
	fPre->SetParName(gUltraStep,"NULL");
	fPre->SetParName(gPeakSigma,"Sigma");
	fPre->SetParName(gPeakDecay,"Decay");
	fPre->SetParName(gPeakSharing,"Sharing");
	fPre->SetParName(gPeakNH(0),"Height");
	fPre->SetParName(gPeakNC(0),"Centroid");
	
	fPre->SetParameters(fParam);
	fPre->FixParameter(gUltraPol0, fParam[gUltraPol0]); //background constant
	fPre->FixParameter(gUltraPol1, fParam[gUltraPol1]); //background grad
	fPre->FixParameter(gUltraOffsetOrPol2, 0);
	fPre->FixParameter(gUltraStep, 0);
	
	if(SigFree)fPre->SetParLimits(gPeakSigma, 1.0, 5.0);  // Sigma
	else if(SigmaFE>0){
		if(SigmaFE>SigmaF)fPre->SetParLimits(gPeakSigma,1E-3,SigmaF+SigmaFE);
		fPre->SetParLimits(gPeakSigma,SigmaF-SigmaFE,SigmaF+SigmaFE);
	}else fPre->FixParameter(gPeakSigma,SigmaF);
	
	if(DecFree)fPre->SetParLimits(gPeakDecay, 1.0, 60.);  // Decay of tail (beta)
	else if(DecayFE>0){
		if(DecayFE>DecayF)fPre->SetParLimits(gPeakDecay,1E-3,DecayF+DecayFE);
		fPre->SetParLimits(gPeakDecay,DecayF-DecayFE,DecayF+DecayFE);
	}else fPre->FixParameter(gPeakDecay,DecayF);
		
	if(ShareFree)fPre->SetParLimits(gPeakSharing, 0., 1.);    // Sharing parameter
	else if(ShareFE>0){
		double l=ShareF-ShareFE,u=ShareF+ShareFE;
		if(u>1)u=1;if(l<0)l=0;
		fPre->SetParLimits(gPeakSharing,l,u);
	}else fPre->FixParameter(gPeakSharing,ShareF);	

	
	if(fixgamma){
		fPre->SetParLimits(gPeakDecay, 1.0, 4.);  // Decay of tail (beta)
		fPre->SetParLimits(gPeakSharing, 0.93, 1.);// Sharing parameter
	}
	fPre->SetParLimits(gPeakNH(0), fParam[gPeakNH(0)]*0.5, fParam[gPeakNH(0)]*2);  // Height
	fPre->SetParLimits(gPeakNC(0), fParam[gPeakNC(0)]-3, fParam[gPeakNC(0)]+3);  // Centroid
	
	
	//////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////// PRE FIT //////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	
	fHist->Fit(fPre, "RMQN"); 
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
	
	bool step=false;
	if(backmode==0||backmode==3||backmode==5){
		step=true;
	}
	// If the background clearly has no under-peak scattering step, then we use a simple formula
	if(fLeftHeight<=fRightHeight)step=false;
	
	bool pol2=false;
	if(backmode==4||backmode==5){
		pol2=true;
	}
	
	fPeakFunc.N=fNp;
	fPeakFunc.SetBit(kStep,step);
	fPeakFunc.SetBit(kPol2,pol2);
	for(unsigned int i=1;i<fNp;i++)
		if(fInput[i].Ratio>0)
			fPeakFunc.SetBit(PBits(i));

		
	TF1 *fFit = new TF1("fFit",fPeakFunc,fLeftUser,fRightUser,NparFromN(fNp));
	
	//////////////////////////////////// SET PARAMETERS ////////////////////////////////
	
	///////// Background parameters	////////
	// "pol0+step",0  // pol0 fixed based on RHS and step RHS-LHS diff
	// "pol1 fixed",1 // Grad fixed from LHS RHS and offset slightly free
	// "pol1",2       // Offset fixed at centre point, offset and grad slightly free (pol1 see-saw)
	// "pol1+step",3  // Offset pinned at RHS, grad set to half and step RHS-LHS diff (pol1 hinge) 
	// "pol2",4	  // Pretty free initial inputs as pol1
	// "pol2+step",5  // Pretty free initial inputs as pol1
	
	if(pol2){
		fFit->SetParName(gUltraOffsetOrPol2,"Pol2");
		fParam[gUltraOffsetOrPol2]=0;
	}else{
		fFit->SetParName(gUltraOffsetOrPol2,"Pol1Offset");
		if(backmode==3)fParam[gUltraOffsetOrPol2]=fRightUser;
		else fParam[gUltraOffsetOrPol2]=fLeftUser+(fRightUser-fLeftUser)*0.5;
	}
	
	fFit->SetParName(gUltraPol0,"Pol0");
	fFit->SetParName(gUltraPol1,"Pol1");
	if(backmode==0){
		fParam[gUltraPol0]=fRightHeight;
		fParam[gUltraPol1]=0;
	}else if(backmode<4){
		fParam[gUltraPol0]=fLin.Eval(fParam[gUltraOffsetOrPol2]);
		fParam[gUltraPol1]=fLin.GetParameter(1);
		if(backmode==3&&step)fParam[gUltraPol1]=fParam[gUltraPol1]*0.5;
	}else{
		fParam[gUltraPol0]=fLin.GetParameter(0);
		fParam[gUltraPol1]=fLin.GetParameter(1);
	}
	
	fFit->SetParName(gUltraStep,"Bkgd Step");
	if(step){
		fParam[gUltraStep]=fLeftHeight-fRightHeight;
	}else{
		fParam[gUltraStep]=0.0;
	}

	
	///////// Shape parameters ////////
	
	fFit->SetParName(gPeakSigma,"Sigma");
	fFit->SetParName(gPeakDecay,"Decay");
	fFit->SetParName(gPeakSharing,"Sharing");
	
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
	// "pol0+step",0  // pol0 fixed based on RHS and step RHS-LHS diff
	// "pol1 fixed",1 // Grad fixed from LHS RHS and offset slightly free
	// "pol1",2       // Offset fixed at centre point, offset and grad slightly free (pol1 see-saw)
	// "pol1+step",3  // Offset pinned at RHS, grad set to half and step RHS-LHS diff (pol1 hinge) 
	// "pol2",4	  // Pretty free initial inputs as pol1
	// "pol2+step",5  // Pretty free initial inputs as pol1

	//////////
	double fBackError=fLeftError+fRightError;
	
	//pol2 / offset
	if(pol2){
// 		double a=abs(fRightHeight/(fRightUser*fRightUser));
// 		fFit->SetParLimits(gUltraOffsetOrPol2,-2*a,2*a);
	}else{
		fFit->FixParameter(gUltraOffsetOrPol2,fParam[gUltraOffsetOrPol2]);
	}

	//pol 0
	if(backmode==3||backmode==0){
		fFit->SetParLimits(gUltraPol0,fParam[gUltraPol0]-fRightError*1.5,fParam[gUltraPol0]+fRightError*0.5);
	}else if(backmode==1||backmode==2){
		fFit->SetParLimits(gUltraPol0,fParam[gUltraPol0]-fBackError*1.5,fParam[gUltraPol0]+fBackError*0.5);
	}else{	}

	//pol 1
	if(backmode==0)fFit->FixParameter(gUltraPol1,0);
	if(backmode==1)fFit->FixParameter(gUltraPol1,fParam[gUltraPol1]);
	if(backmode==2||backmode==3){
		double dgrad=abs(((fRightError+fLeftError)/2)/((fRightUser-fLeftUser)*0.5));
		fFit->SetParLimits(gUltraPol1,fParam[gUltraPol1]-dgrad,fParam[gUltraPol1]+dgrad);
		if(step)fFit->SetParLimits(gUltraPol1,0,fLin.GetParameter(1)*1.0001);
	}
	if(backmode>3){}
	
	//Step(
	if(step){
		if(backmode==0){
			fFit->SetParLimits(gUltraStep,fParam[gUltraStep]-fBackError*1.5,fParam[gUltraStep]+fBackError*0.5);
		}else{
			fFit->SetParLimits(gUltraStep,0,fParam[gUltraStep]+fBackError*0.5);
		}
	}else{
		fFit->FixParameter(gUltraStep,0);
	}

	///////// Shape parameters ////////


	if(SigFree)fFit->SetParLimits(gPeakSigma, fParam[gPeakSigma]*0.5, fParam[gPeakSigma]*2);// Sigma
	else if(SigmaFE>0){
		if(SigmaFE>SigmaF)fFit->SetParLimits(gPeakSigma,1E-3,SigmaF+SigmaFE);
		fFit->SetParLimits(gPeakSigma,SigmaF-SigmaFE,SigmaF+SigmaFE);
	}else fFit->FixParameter(gPeakSigma,SigmaF);
	
	
	if(DecFree){// Decay of tail (beta)
		double nsc=5.0;
		if(fixgamma)nsc=2.0;
		if(fParam[gPeakDecay]>fParam[gPeakSigma]*nsc){fParam[gPeakDecay]=fParam[gPeakSigma]*0.25;fFit->SetParameter(gPeakDecay,fParam[gPeakDecay]);}
		fFit->SetParLimits(gPeakDecay, fParam[gPeakDecay]*0.5, fParam[gPeakSigma]*nsc);
	// 	if(fixgamma&&fParam[gPeakSigma]>2)fPre->SetParLimits(gPeakDecay, fParam[gPeakDecay]*0.5, 10.);
	}else if(DecayFE>0){
		if(DecayFE>DecayF)fFit->SetParLimits(gPeakDecay,1E-3,DecayF+DecayFE);
		fFit->SetParLimits(gPeakDecay,DecayF-DecayFE,DecayF+DecayFE);
	}else fFit->FixParameter(gPeakDecay,DecayF);

	
	if(ShareFree){ // Sharing parameter
		if(fParam[gPeakSharing]>=0.6667)fFit->SetParLimits(gPeakSharing, fParam[gPeakSharing]*0.5, 1.0);		// Sharing (should never be >1)
		else fFit->SetParLimits(gPeakSharing, fParam[gPeakSharing]*0.5, fParam[gPeakSharing]*1.5);		// Sharing (should never be >1)
		if(fixgamma)fPre->SetParLimits(gPeakSharing,0.93,1.);
	}else if(ShareFE>0){
		double l=ShareF-ShareFE,u=ShareF+ShareFE;
		if(u>1)u=1;if(l<0)l=0;
		fFit->SetParLimits(gPeakSharing,l,u);
	}else fFit->FixParameter(gPeakSharing,ShareF);	


	///////// Peak zero  ////////

	fFit->SetParLimits(gPeakNH(0), fParam[gPeakNH(0)]*0.5, fHist->GetMaximum()*1.5);	// 0 Height
	fFit->SetParLimits(gPeakNC(0), fParam[gPeakNC(0)]-3, fParam[gPeakNC(0)]+3);	// 0 Centroid
	
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

	fHist->Fit(fFit, "RMNQ");//Get close, then do extra fit with error analysis
	
	TFitResultPtr fResult;
	if(statmode==0)fResult=fHist->Fit(fFit, "RMENS");
	if(statmode==1)fResult=fHist->Fit(fFit, "RMENSL");
	if(statmode==2)fResult=fHist->Fit(fFit, "RMENSWL");
	
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
	
	if(statmode>0)cout<<endl<<"Likelihood fit, fit goodness chi-squared is ..."<<endl;
	
	FullFitHolder* fHold = new FullFitHolder(fFit,fResult->GetCovarianceMatrix(),fPeakFunc.cBits);
	
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

	


