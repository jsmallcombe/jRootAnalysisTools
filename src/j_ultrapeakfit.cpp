#include "j_ultrapeak.h"
#include "TStyle.h"


//////////////////////////////////////////////////////
/////////////// Ultra peak fit //////////////////////
//////////////////////////////////////////////////////

FullFitHolder* Ultrapeak::PeakFit(TH1* fHist,TH1* fExHist,double fLeftUser,double fRightUser,vector< jPeakDat > &fInput,int backmode,int peaktype,bool truecent,string FixParStr){
    
	// This function takes in peak positions as a series of relative positions, this creates undue correlation between centroid positions.
	// However, this is the best way to fix the distance between pairs (or more), which is a likely desire if fitting multiple peaks.
	// All entries are relative to the previous one, so place them in the correct order for any linked pairs
    
	// Possible problems:
	// Peak parameters are estimated from an initial fit which assumes peak zero is the furthest left peak 
    
	cout<<endl<<"--------------------------------------------------"<<endl<<endl;
	
	//////////////////////////////////////////////////////
	/////////// PROCESS PEAK TYPE/SHAPE INPUTS ///////////
	//////////////////////////////////////////////////////

	bool tailon=(peaktype%2);
	bool twogaus=((int)(peaktype/10)%2);    
    
    // Parse the '/' seperated parameter limit strings
    string sig, dec, sha,TGWRstr,TGHRstr;
    vector<string*> dp={&sig,&dec,&sha,&TGWRstr,&TGHRstr};
    for(unsigned int l=0;l<dp.size();l++){
        unsigned int dash=FixParStr.find('/');
        if(dash<FixParStr.size()){
            *dp[l]=FixParStr.substr(0,dash);
            FixParStr=FixParStr.substr(dash+1,FixParStr.size());
        }else{
            *dp[l]=FixParStr;
            break;
        }
    }
    
	// Check any shape parameter overrides
	// If the following xFree bools are true, the values of xF xFE are never used 
	double SigmaF,SigmaFE,DecayF,DecayFE,ShareF,ShareFE,TGWRF,TGWRFE,TGHRF,TGHRFE;
	ExtractError(sig,SigmaF,SigmaFE); // Return SigmaF=0 in the case of no input. 
    bool SigFree=!(SigmaF>0); // Safe guard against negative values!
	ExtractError(dec,DecayF,DecayFE);
    bool DecFree=!(DecayF>0);
    ExtractError(sha,ShareF,ShareFE);
    bool ShareFree=!((ShareF>=0&&ShareF<=1)&&sha.size()>0);
    // Extra check to distinquish between an actual input of zero (which is allowed) and a zero due to no input
    
    ExtractError(TGWRstr,TGWRF,TGWRFE);
    bool TGWRFree=!(TGWRF>=1);
    ExtractError(TGHRstr,TGHRF,TGHRFE);
    bool TGHRFree=!((TGHRF>=0&&TGHRF<=1)&&TGHRstr.size()>0);
	
	int fNp=fInput.size();if(fNp<1)return 0;
	if(fNp>gMaxPeaks)fNp=gMaxPeaks; // If a user tries to fit too many peaks, the latter inputs are ignored
	
	// Copy the peaks positions (1 absolute position and N-1 relative positions)
	vector <double> fPeaks;
	for(int i=0;i<fNp;i++)fPeaks.push_back(fInput[i].Centroid);
		
	//////////////////////////////////////////////////////
	//////////////// GET HISTOGRAM DATA //////////////////
	//////////////////////////////////////////////////////	

	// Fine the bins of the chossen range and amend the range to reflect the limits of those bins
	int fLeftBin=fHist->GetXaxis()->FindBin(fLeftUser),fRightBin=fHist->GetXaxis()->FindBin(fRightUser);
	fLeftUser=fHist->GetBinCenter(fLeftBin);
	fRightUser=fHist->GetBinCenter(fRightBin);
	
	// Find the absolute max minimum value in the fit range
	bool hasdata=false;
	double fMinY=fHist->GetBinContent(fHist->GetMaximumBin()), fMaxY=-fMinY;
	for(int i=fLeftBin;i<=fRightBin;i++){
		double m=fHist->GetBinContent(i);
		if(m<fMinY)fMinY=m;
		if(m>fMaxY)fMaxY=m;
		if(m!=0)hasdata=true;
	}
	if(!hasdata)return 0;
	
    int smbin=3;// REDUCED FROM 5 TO 3
    if(backmode==cBackType1f){smbin=1;}
	// Takes a short average of histogram bins for the right and left edges of the fit range.
	double fLeftHeight = bins_smooth(fHist,fLeftBin,smbin);
	double fRightHeight = bins_smooth(fHist,fRightBin,smbin);
	double fLeftVar = 2*sqrt(bins_var(fHist,fLeftBin,smbin));	
	double fRightVar = 2*sqrt(bins_var(fHist,fRightBin,smbin));
	double fLeftError=sqrt(abs(fLeftHeight));
	double fRightError=sqrt(abs(fRightHeight));
	if(fLeftVar>fLeftError)fLeftError=fLeftVar;
	if(fRightVar>fRightError)fRightError=fRightVar;

	double p0=fPeaks[0];
	double fHH=FindLocalMax(fHist,p0); // FindLocalMax changes input p0 to local maximum bin centroid and returns bin content
		
	/////////////////////////////////////////////////////////
	//////////////// CHECK HISTOGRAM STATS //////////////////
	/////////////////////////////////////////////////////////
	
	int statmode=0;// Chi Squared
	double binsums=0;
	bool nonintergerbins=false;
	for(int i=fLeftBin;i<=fRightBin;i++){
		double n=fHist->GetBinContent(i);
		if(abs(n-(int)n)>1E-6)nonintergerbins=true;
		binsums+=abs(n);
	}
	
	// If average bin content<10 definitely use Log Likelihood
	if(binsums<(fRightBin-fLeftBin+1)*10){
		statmode=1;//likelihood
		if(nonintergerbins)statmode=2;//weighted likelihood
		
		if(fExHist){
            fExHist=0;
            cout<<"  Low stats Likelihood fitting incompatible with exclusion zones! "<<endl;
        }
	}
	// If background is fully subtracted ~0 and large peaks are present, likelihood will not be used.
	// If background is still being fit in this case it will likely be overestimated.
	

	//// log likelihood (particularly weighted) fitting hasnt been working very well
	//// In the case bin errors have been inflated over poisson then using chi should fine/best
	if(fHist->GetSumw2N()){
		for(int i=fLeftBin;i<=fRightBin;i++){
			double n=fHist->GetBinContent(i);
			double e=fHist->GetBinError(i);
			if(abs(e)-sqrt(abs(n))>1E-6){
				statmode=0;
			}
			
			if(n<0&&e<abs(n))fHist->SetBinError(i,abs(n));
			// Error inflating for over subtraction issues.
			// Not totally justified
		}
	}
	
	//////////////////////////////////////////////////////////////////////////////
	//////////////// PERFORM PRELIMINARY FIT FOR PEAK PARAMETERS /////////////////
	//////////////////////////////////////////////////////////////////////////////
	// Good Initial guesses and limits needed for good minimisation
	
	TF1 fLin("fLin","x*[1]+[0]"); // Always uses pol1 for intial fit, irrespective of input
	
	double fParam[48]={0}; // Holder for parameters

	fParam[gUltraPol1] = (fRightHeight-fLeftHeight)/(fRightUser-fLeftUser); // Background pol1 gradient
	fParam[gUltraPol0] = fRightHeight-fRightUser*fParam[gUltraPol1]; // Background pol1 intercept
	fLin.SetParameters(fParam[gUltraPol0],fParam[gUltraPol1]);
    
	fParam[gPeakSigma] = 2.5; // Peak sigma
	fParam[gUltraTGWR] = 1.5; // Peak sigma ratio for 2gaus
	fParam[gUltraTGHR] = 0.6; // Peak height ratio for 2gaus
	fParam[gPeakDecay] = 3.0; // Decay of tail (beta)
	fParam[gPeakSharing] = 0.95; // Gaus/Tail Sharing parameter (0 - 1)
	fParam[gPeakNH(0)] = abs(fHH-fLin.Eval(fPeaks[0])); // First Peak Height (fn is height=1 normalised, not area normalised)
	fParam[gPeakNC(0)] = fPeaks[0]; // First Peak Centroid
	
	// Ideally the first peak in the input list vector< jPeakDat > &fInput should be the large, to the left, and isolated,
	// in order to enable the best peak shape estimates. However this is not always the case
	// This check skips up to 2 negligible initial peaks
	double tCC=fPeaks[0];
	for(int i=1;i<3&&i<fNp;i++){
		tCC+=fPeaks[i];
		double tH=fHist->GetBinContent(fHist->GetXaxis()->FindBin(tCC));
		tH-=fLin.Eval(tCC);
		if(tH>fParam[gPeakNH(0)]*5){
			cout<<"Skipping peak "<<i-1<<" for shape fit"<<endl;
			fParam[gPeakNH(0)]=tH;
			fParam[gPeakNC(0)]=tCC;
		}
	}
	
	// If manual inputs were given, use those
	if(!SigFree)fParam[gPeakSigma]=SigmaF;
	if(!DecFree)fParam[gPeakDecay]=DecayF;
	if(!ShareFree)fParam[gPeakSharing]=ShareF;
	
    // Define the Ultrapeak instance that will be used in the initial and final fits to control the TF1
	// Initially the function is defined as a single peak (of the chossen type) + a pol1 background
	Ultrapeak fPeakFunc(1,1,cBackType1,twogaus,truecent);// Control parameters (peaks #,peaks 0/1,background type,step 0/1)
	fPeakFunc.SetBit(kDecOff,!tailon);
    
    // Decalare the TF1 that will perform the initial shape parameter fit
	TF1 *fPre = new TF1("fPre",fPeakFunc,fLeftUser,fPeaks[0]+4,NparFromN(1));
	fPre->SetParameters(fParam);
	fPeakFunc.NameParam(fPre);
    
    // Do not fit the background during this intial fit
	fPre->FixParameter(gUltraPol0, fParam[gUltraPol0]); // Background constant
	fPre->FixParameter(gUltraPol1, fParam[gUltraPol1]); // Background grad
	fPre->FixParameter(gUltraOffsetOrPol2, 0);          // Background offset
	
    // Sigma limits if left "free" or manually constrained 
	if(SigFree){ // No constraints given, use default
        fPre->SetParLimits(gPeakSigma, 1.0, 6.0);  
    }else if(SigmaFE>0){ // Range given, but check must always be greater than zero.
		if(SigmaFE>SigmaF)fPre->SetParLimits(gPeakSigma,1E-3,SigmaF+SigmaFE);
		else fPre->SetParLimits(gPeakSigma,SigmaF-SigmaFE,SigmaF+SigmaFE);
	}else{ // Fixed value specified 
		fPre->FixParameter(gPeakSigma,SigmaF);
	}
	
	if(tailon){ // If not in use parameters will be fixed by FixUnusedParam();
        
        // Decay tail limits if left "free" or manually constrained 
        if(DecFree){
            fPre->SetParLimits(gPeakDecay, 1.0, 60.);
        }else if(DecayFE>0){
            if(DecayFE>DecayF)fPre->SetParLimits(gPeakDecay,1E-3,DecayF+DecayFE);
            else fPre->SetParLimits(gPeakDecay,DecayF-DecayFE,DecayF+DecayFE);
        }else{
            fPre->FixParameter(gPeakDecay,DecayF);
        }
            
        // Gaus/Tail Sharing parameter limits
        if(ShareFree){
            fPre->SetParLimits(gPeakSharing, 0., 1.);
        }else if(ShareFE>0){
            double l=ShareF-ShareFE,u=ShareF+ShareFE;
            if(u>1)u=1;
            if(l<0)l=0;
            fPre->SetParLimits(gPeakSharing,l,u);
        }else{
            fPre->FixParameter(gPeakSharing,ShareF);
        }
        
    }
    
    if(twogaus){// If not in use parameters will be fixed by FixUnusedParam();
        // Limits for the twin gaus parameters 
        fPre->SetParLimits(gUltraTGWR,1.01,4);
        fPre->SetParLimits(gUltraTGHR,0.0,1.0);
    }
        
	// Peak Centroid
	if(!fInput[0].CentConstrained){ 
		fPre->SetParLimits(gPeakNC(0), fParam[gPeakNC(0)]-3, fParam[gPeakNC(0)]+3); 
    }else if(fInput[0].CentError>0){
        double err=fInput[0].CentError;
        fPre->SetParLimits(gPeakNC(0), fParam[gPeakNC(0)]-err, fParam[gPeakNC(0)]+err); 
    }else{
        fPre->FixParameter(gPeakNC(0), fParam[gPeakNC(0)]);
    }
	
    // Peak Height
	fPre->SetParLimits(gPeakNH(0), fParam[gPeakNH(0)]*0.5, fParam[gPeakNH(0)]*2);  // Should be wide enough range unless background really weird
    
    
    // Any unused parameters in the TF1 are fixed based on the option bits of Ultrapeak fPeakFunc
	fPeakFunc.FixUnusedParam(fPre);
    
	/////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////// PRE FIT ///////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	
	
	TH1* fFitHist=fHist;
	if(fExHist)fFitHist=fExHist; // Use the bin cancelled exclusion histogram if passed
	
	// The new default to minuit2 caused and issue with fixed parameters in the middle of lists 
	// Temporary fix, should probably fully embrace minuit2
	ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit");
	
	// Use the bin cancelled exclusion histogram if passed
    TFitResultPtr fPreResult=fFitHist->Fit(fPre, "SRQN");
    
    Int_t FitPreStatus = fPreResult;
    if(FitPreStatus){
        cout<<endl<<"  Initial shape fit failed! TFitResultPtr Status = "<<FitPreStatus<<", Limits = "<<AnyParAtLimit(fPre)<<endl;
		// Accessing some of these things during a bad fit results caused crashes
//         cout<<endl<<"  Initial shape fit failed! TFitResultPtr Status = "<<FitPreStatus<<", gMinuit status = "<<gMinuit->fCstatu<<", CovarianceMatrix = "<<CovDiag(fPreResult)<<", Limits = "<<AnyParAtLimit(fPre)<<endl;
        return 0;
    }else{
        // If the git was good, get the parameters from the fit
        fPre->GetParameters(fParam);
    }
    
	delete fPre; // Done with that TF1
	
	////////////////////////////////////////////////////////////////////////////////
	///////////////////////// CONFIGURE FULL MULTI PEAK FIT ////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	
	// Change the settings of Ultrapeak fPeakFunc to reflect the settings for the full fit
	fPeakFunc.N=fNp;
	for(int i=1;i<fNp;i++){
		if(fInput[i].Ratio>0){
			fPeakFunc.SetBit(PBits(i));
        }
    }
	fPeakFunc.SetBackMode(backmode);
	// Now we use the selected background mode, not the default pol0;
	// However, if the background has no clear under-peak step, it is disabled
	if(fLeftHeight<=fRightHeight){
        fPeakFunc.SetBit(kStep,false);
    }
	
	int Npar=NparFromN(fNp);
	TF1 *fFit = new TF1("fFit",fPeakFunc,fLeftUser,fRightUser,Npar);
    fPeakFunc.NameParam(fFit);
	
	/////////////////////////////////////////////////////////////////////////
	//////////////////////////// SET PARAMETERS /////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	
	///////// Background parameters	////////
	// "pol0+step",  // pol0 fixed based on RHS and step RHS-LHS diff
	// "pol1 fixed", // Grad fixed from LHS RHS and offset slightly free
	// "pol1",       // Offset fixed at centre point, offset and grad slightly free (pol1 see-saw)
	// "pol1+step",  // Offset pinned at RHS, grad set to half and step RHS-LHS diff (pol1 hinge) 
	// "pol2",	  // Pretty free, initial inputs as pol1
	// "pol2+step",  // Pretty free, initial inputs as pol1
	
    // Calculate the parameters for selected background type (not used in the prefit).
    
	bool step=fPeakFunc.TestBit(kStep);
    int polorder=PolOrder(backmode);
	if(polorder==0){ // If only constant background (with or without step) use RHS (as step could be on left)
		fParam[gUltraPol0]=fRightHeight;
	}else if(polorder==1){ // If linear background
        // Estimate from the linear background function made during prefit
		fParam[gUltraPol1]=fLin.GetParameter(1);
        if(step){ // If using a step the background offset is fixed at RHS
            fParam[gUltraOffsetOrPol2]=fRightUser;
            fParam[gUltraPol1]=fParam[gUltraPol1]*0.5;
            // If instructed to include a step, set the gradient lower to allow room for step
        }else{  // Else it is fixed in the middle of the fit range
            fParam[gUltraOffsetOrPol2]=fLeftUser+(fRightUser-fLeftUser)*0.5;     
        }
		fParam[gUltraPol0]=fLin.Eval(fParam[gUltraOffsetOrPol2]);
	}else{// Polynomial order 2
		fParam[gUltraPol0]=fLin.GetParameter(0);
		fParam[gUltraPol1]=fLin.GetParameter(1);
		fParam[gUltraOffsetOrPol2]=0;
	}
	
	if(step){
		fParam[gUltraStep]=fLeftHeight-fRightHeight;
	}
	
	///////// Peak  0 ////////

	fParam[gPeakNH(0)] = abs(fHH-fLin.Eval(fPeaks[0]));// First Peak Height
	fParam[gPeakNC(0)] = fPeaks[0];// First Peak Centroid
	
	///////// Additional Peaks ////////
	
	double sPe=fPeaks[0];
	for(int i=1;i<fNp;i++){
		fParam[gPeakNC(i)]=fPeaks[i];
		sPe+=fPeaks[i];
		
		if(fInput[i].Ratio>0){ // peak height ratio not actual height
			fParam[gPeakNH(i)]=fInput[i].Ratio;
		}else{
            double lH=fHist->GetBinContent(fHist->GetXaxis()->FindBin(sPe));
            double lB=fLin.Eval(sPe);
            double pH=lH-lB;
            if(pH<=0)pH=abs(lH);
			fParam[gPeakNH(i)]=pH;
		}
	}	
	
	// Actually set in the TF1
	fFit->SetParameters(fParam);
	
	/////////////////////////////////////////////////////////////////////////
	//////////////////////// LIMTS & FIXED PARAMETERS ///////////////////////
	/////////////////////////////////////////////////////////////////////////
	
	///////// Limits Background ////////
    
    // An estimate of the background fluctuations based on the earlier averaging
	double fBackError=sqrt(fLeftError*fLeftError+fRightError*fRightError)*1.5;
	if(step){
        // Step limits always set to a full range
		fFit->SetParLimits(gUltraStep,0,fParam[gUltraStep]+fBackError);
    }
	
    if(polorder==0){
        fFit->SetParLimits(gUltraPol0,fParam[gUltraPol0]-fBackError,fParam[gUltraPol0]+fBackError*0.5);        
    }else if(polorder==1){
		fFit->FixParameter(gUltraOffsetOrPol2,fParam[gUltraOffsetOrPol2]);
        // Offset always fixed when used. It has no physical meaning, but makes estimating and constraining other parameters easier
        
        if(step){
            fFit->SetParLimits(gUltraPol1,0,fLin.GetParameter(1)*1.0001);
            fFit->SetParLimits(gUltraPol0,fParam[gUltraPol0]-fRightError,fParam[gUltraPol0]+fRightError*0.5);// Slightly stricter 
        }else{
            double dgrad=abs(fBackError/((fRightUser-fLeftUser)*0.5));
            fFit->SetParLimits(gUltraPol1,fParam[gUltraPol1]-dgrad,fParam[gUltraPol1]+dgrad);
            fFit->SetParLimits(gUltraPol0,fParam[gUltraPol0]-fBackError,fParam[gUltraPol0]+fBackError*0.5);
        }
        
        if(backmode==cBackType1f){ // This is the "pol1 fixed" option which fixed the gradient
            fFit->FixParameter(gUltraPol1,fParam[gUltraPol1]);
        }
        
    }else{
        // Pol2 constraints
    }

	//////// Limits Shape parameters ////////
	
	if(SigFree){// Sigma
        fFit->SetParLimits(gPeakSigma, fParam[gPeakSigma]*0.5, fParam[gPeakSigma]*2);
    }else if(SigmaFE>0){
		if(SigmaFE>SigmaF)fFit->SetParLimits(gPeakSigma,1E-3,SigmaF+SigmaFE);
		else fFit->SetParLimits(gPeakSigma,SigmaF-SigmaFE,SigmaF+SigmaFE);
	}else{
		fFit->FixParameter(gPeakSigma,SigmaF);
	}
	
	if(tailon){
        if(DecFree){// Decay tail 
            double nsc=5.0;
            if(fParam[gPeakDecay]>fParam[gPeakSigma]*nsc){ // If not manually set limit based on sigma
                fParam[gPeakDecay]=fParam[gPeakSigma];
                fFit->SetParameter(gPeakDecay,fParam[gPeakDecay]);
            }
            fFit->SetParLimits(gPeakDecay, fParam[gPeakDecay]*0.5, fParam[gPeakSigma]*nsc);
        }else if(DecayFE>0){
            if(DecayFE>DecayF)fFit->SetParLimits(gPeakDecay,1E-3,DecayF+DecayFE);
            else fFit->SetParLimits(gPeakDecay,DecayF-DecayFE,DecayF+DecayFE);
        }else{
            fFit->FixParameter(gPeakDecay,DecayF);
        }

        if(ShareFree){ // Sharing parameter
            double UL=fParam[gPeakSharing]*1.5;
            if(UL>1)UL=1.0; // Sharing (should never be >1)
            fFit->SetParLimits(gPeakSharing, fParam[gPeakSharing]*0.5,UL);
        }else if(ShareFE>0){
            double l=ShareF-ShareFE,u=ShareF+ShareFE;
            if(u>1)u=1;
            if(l<0)l=0;
            fFit->SetParLimits(gPeakSharing,l,u);
        }else{
            fFit->FixParameter(gPeakSharing,ShareF);
        }
    }
    
    	
	if(twogaus){
        
        // Twin Gaus Width Ratio. Must be > 1
        if(TGWRFree){
            fFit->SetParLimits(gUltraTGWR,1.01,4);
        }else if(TGWRFE>0){
            if(TGWRFE>TGWRF-1){
                fFit->SetParLimits(gUltraTGWR,1,TGWRF+TGWRFE);
            }else{
                fFit->SetParLimits(gUltraTGWR,TGWRF-TGWRFE,TGWRF+TGWRFE);
            }
        }else{
            fFit->FixParameter(gUltraTGWR,TGWRF);
        }
        
        // Twin Gaus Height Ratio. Must be 0-1
        if(TGHRFree){
            fFit->SetParLimits(gUltraTGHR,0.0,1.0);
        }else if(TGHRFE>0){
            double l=TGHRF-TGHRFE,u=TGHRF+TGHRFE;
            if(u>1)u=1;
            if(l<0)l=0;
            fFit->SetParLimits(gUltraTGHR,l,u);
        }else{
            fFit->FixParameter(gUltraTGHR,TGHRF);
        }
             
	}
    

	//////// Limits Peaks ////////
	///////// Peak zero //////////
	double fFree=0; // Count the number of free peaks to help set limits on centroids

	fFit->SetParLimits(gPeakNH(0), fParam[gPeakNH(0)]*0.5, fHist->GetMaximum()*1.5); // Peak 0 Height
	
    // Peak 0 Centroid 
	if(!fInput[0].CentConstrained){ // Free
        fFree=1;
		fFit->SetParLimits(gPeakNC(0), fParam[gPeakNC(0)]-3, fParam[gPeakNC(0)]+3); 
    }else if(fInput[0].CentError>0){ // Constrained
        fFree=0.5;
        double err=fInput[0].CentError;
        fFit->SetParLimits(gPeakNC(0), fParam[gPeakNC(0)]-err, fParam[gPeakNC(0)]+err); 
    }else{ // Fixed
        fFit->FixParameter(gPeakNC(0), fParam[gPeakNC(0)]);
    }
	
	/////// Additional Peaks ///////
	
	for(int i=1;i<fNp;i++){
		int h=gPeakNH(i),c=gPeakNC(i);
        
        // Height/ratio
		if(fInput[i].Ratio>0){ // Ratio
			double err=fInput[i].RatioError;
            // Ratios never have default values as they are only used manually
			if(err>0){
				fFit->SetParLimits(h, fParam[h]-err, fParam[h]+err);
			}else{
				fFit->FixParameter(h,fParam[h]);
			}
		}else{ // Absolute height
			fFit->SetParLimits(h, fParam[h]*0.2, fParam[h]*4); // Heights have very wide limits 
		}
		
		// Centroids
		if(!fInput[i].CentConstrained){ // Free
			fFree+=1;
			fFit->SetParLimits(c, fParam[c]-2*fFree, fParam[c]+2*fFree);
        }else if(fInput[i].CentError>0){ // Constrained
            fFree+=0.5;
            double err=fInput[i].CentError;
            fFit->SetParLimits(c, fParam[c]-err, fParam[c]+err);
        }else{ // Fixed
            fFit->FixParameter(c,fParam[c]);
        }
	}
	
    // Any unused parameters in the TF1 are fixed based on the option bits of Ultrapeak fPeakFunc
	fPeakFunc.FixUnusedParam(fFit);
	
	//////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////// FULL FIT ZONE //////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	
// 	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(9999);
	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(10000);

    string MasterFitOpt="RSNQ";
    // R - use Range
    // S - return full TFitResultPtr
    // N - do not adda anything to histogram or draw
    // Q - quiet no text output
    
    // First fit
	// Get close, with basic fit options
 	TFitResultPtr fResult=fFitHist->Fit(fFit,MasterFitOpt.c_str());
    
    // TFitResultPtr is a "smart pointer" has an automatic conversion to an integer, the value of which corresponds to the fit status
    Int_t FitStatus = fResult;
    // Currently using TMinuit minimiser:
    // FitStatus = migradResult + 10*minosResult + 100*hesseResult + 1000*improveResult ( 0 no error, 4 if error )
    // FitStatus < 0 if error not connected with the minimizer
    
    if(FitStatus){
        cout<<endl<<"  BASIC FIT FAILED! TFitResultPtr Status = "<<FitStatus<<", gMinuit status = "<<gMinuit->fCstatu<<", CovarianceMatrix = "<<CovDiag(fResult)<<", Limits = "<<AnyParAtLimit(fFit)<<endl;
        // fResult->GetCovarianceMatrix().Print();
        // fResult->Print("V");
        return 0;
    }else{
        // cout<<"Initial fit status = "<<FitStatus<<", CovM "<<CovDiag(fResult)<<", Lim = "<<AnyParAtLimit(fFit)<<endl;
    }
    
    // Fix parameters for tail/twogaus/sharing if close to limits to avoid problems
    fPeakFunc.FitLimitations(fFit,true);
    
    // L - use logliklihood not chisquared (because low stats)
    // WL - use weighted logliklihood because non-integer bings (i.e. subtraction)
	if(statmode==1)MasterFitOpt+="L";
	if(statmode==2)MasterFitOpt+="WL";
    
    // Do a second fit with statoptions and option M
    // M option is supposed to find improved minimum, but seems to ALWAYS return error code 4000
    fResult=fFitHist->Fit(fFit,(MasterFitOpt+"M").c_str());
    FitStatus = fResult;
    bool Mfit=(CovDiag(fResult)&&!FitStatus);
    // cout<<"M fit status = "<<FitStatus<<", CovM "<<CovDiag(fResult)<<", Lim = "<<AnyParAtLimit(fFit)<<endl;
    
    // Set last few impovement options for a final fit 
    
    double binwidth=fFitHist->GetBinWidth(1);
    if(binwidth>=fFit->GetParameter(gPeakSigma)){
        MasterFitOpt+="I";
        // I - use integral of function instead of value in bin center.
        // Much slower but needed if bin width is wide relative to peaks
    }
    
    if(statmode!=2){ // WL incompatible with E
        // E - better errors estimation by using Minos technique
        MasterFitOpt+="E";
    }

    // Opt M should be the last thing on the string so it is the first removed, due to usually being troublesome
    if(Mfit){
        MasterFitOpt+="M";
    }
    
    // This loop will do a final fit with all options
    // If full options fit is imperfect remove options in order of least importance (right to left) and retry    
    while(MasterFitOpt.length()>3){
    
        fResult=fFitHist->Fit(fFit,MasterFitOpt.c_str());
        FitStatus = fResult;
		
        if(fPeakFunc.FitLimitations(fFit,true)){continue;}
        if(!FitStatus&&CovDiag(fResult)){break;}
        
        cout<<"  "<<MasterFitOpt<<" fit status = "<<FitStatus<<", CovM "<<CovDiag(fResult)<<", Lim = "<<AnyParAtLimit(fFit)<<", Failed."<<endl;
        MasterFitOpt=MasterFitOpt.substr(0,MasterFitOpt.length()-1);
    }
    // *should* now have a good fit as the above loop reduced back to the original options until a good fit
    // And if the original fit options failed then function terminated there
    
//////// Debugging ////////
//    fFitHist->Fit(fFit,"RSNE");
//     fResult->Print("V");    
//////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////// POST FIT OUTPUT ///////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

//fResult->Print("V");

    // Switched to a manual output due to a strange error with opt "E"
    // which caused the values of some parameters to be changed between terminal output and fit result
    
    cout<<endl<<"     FIT STATUS : "<<gMinuit->fCstatu;
	for(int i=0;i<Npar;i++){
        string pname=fFit->GetParName(i);
        double val=fFit->GetParameter(i);
        double err=fFit->GetParError(i);
        
        if(!pname.compare("na"))continue;
        cout.precision(5);
        
        //////////// Identical to normal TF1 fit output ////////////
        // cout<<endl<<setw(4)<<right<<i<<"  "<<left<<setw(10)<<pname<<setw(14)<<right<<scientific<<val<<setw(14)<<err<<flush;
        ////////////////////////////////////////////////////////////    

        cout<<endl<<setw(3)<<right<<i<<"  ";
        cout<<left<<setw(10)<<pname<<right<<setw(12);
        
        if(IsParFixed(fFit,i)){
                cout<<val<<"       fixed";
        }else if(ParAtLimit(fFit,i)){
                cout<<val<<"      Warning!   Parameter At ";
                if(ParAtLimit(fFit,i,0))cout<<"Lower";
                else cout<<"Upper";
                cout<<" Limit. Errors Invalid.";;
        }else{
            ScientificErrorPrint(val,err,2,true,true);
            if(abs(err/val)>0.1){
                cout.precision(3);
                cout<<"  Warning!   "<<abs(100*err/val)<<"% Error";
            }
        }
        cout<<flush;
    }
    cout<<endl;
    cout<<resetiosflags(cout.flags()); // clears all flags
    
    if(fResult->Status()){
        cout<<endl<<"       WARNING FIT FAILURE!";
        cout<<endl<<"  Fit Status code : "<<fResult->Status();
        cout<<endl<<"  Fit Status word : "<<gMinuit->fCstatu;
        cout<<endl;
		return 0;
	}
	
	// Actually populate the return value
	FullFitHolder* fHold = new FullFitHolder(fFit,fResult->GetCovarianceMatrix(),fPeakFunc.cBits);
	
    bool infl=(statmode==0);
    fHold->SetBit(Ultrapeak::kInflate,infl);
    fHold->RedChiInflateErr=infl;
    
    // Calculate all data (area etc) and stores in fHold's vector
	MakeData(fHold,fHist,fExHist);
    
	// PrintData can call MakeData internally, but doesnt handel exclusion ranges so the above direct call is added 
    PrintData(fHold,true,binwidth);
    
    if(fHold->InflateChi()>1)cout<<endl<<"  Fit area errors inflated by sqrt(RedChi)."<<flush;
	if(statmode>0)cout<<endl<<"  Likelihood fit, use 'chi-squared' with caution."<<flush;
	if(statmode>1)cout<<endl<<"  Weighted Likelihood fit. Use error from integral form."<<flush;  
    cout<<endl;
	
	if(!CovDiag(fResult)||AnyParAtLimit(fFit)){
        cout<<endl<<"     Warning, Uncertainty Problems!";
        if(!CovDiag(fResult))cout<<endl<<"     Covariance Matrix Incomplete.";
        if(AnyParAtLimit(fFit))cout<<endl<<"        Parameters at Limits.";
        cout<<endl;
    }

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
