{
	TCanvas *C1 = new TCanvas();
	
	TH1D *histin = new TH1D("hist","hist",1000,0,1000);//// Replace this with an actual histogram you wish to fit
    TF1 test("testf1","TMath::Gaus(x,500,3.0)+0.2",0,10000);
	histin->FillRandom("testf1",100000);

	TH1 *hist = (TH1*)histin; //// Cast pointer to be parent class
	//// We use no fucntions of TH1D,TH1F,TH1I directly, so all code aims to be generic using TH1
	
	//// Different ways of getting the input
// 	double XX=500; //// peak energy
	double XX=hist->GetXaxis()->GetBinCenter(hist->GetMaximumBin());
// 	double XX=GetHistClickVal(hist,"Select Peak",false); //// Getting a click
	
	//// Give the fitting data of the one peak
	jPeakDat peak(XX);
	peak.CentConstrained=false; //// CentError ignored
	peak.CentError=-1;//// <=0 fixed param
	peak.Ratio=-1;//// <=0 unused
	peak.RatioError=-1;//// <=0 fixed param
		
	//jPeakDat peak(XX,false,-1,-1,-1): //// Direct constructor
	
	//// Fitting function takes a vector list of peaks each relative to the previous one
	vector< jPeakDat > fInput;
	fInput.push_back(peak);
	
	double FitRangeStart=XX-35;
	double FitRangeEnd=XX+35;
	int BackgroundMode=10;
	int PeakType=0;
	
	//Defauly parameters should be fine
	string SigmaParameter="";
	//string SigmaParameter="10+5"; //// Fit peaks with a sigma of 10 +- 5
	string DecayParameter="";
	string SharingParameter="1"; //// Fix no exponential tail on peak
	
    //// The auto fit function of Ultrapeak is declared as follows:
    //// static FullFitHolder* PeakFit(TH1* fHist,double fLeftUser,double fRightUser,vector< jPeakDat > &fInput,int backmode=0,int peaktype=0,bool truecent=0,string sig="",string dec="",string sha="",TH1* fExHist=0));
	//// You dont need to give all arguments if we want the defaults
    
	FullFitHolder* fitA = Ultrapeak::PeakFit(hist,FitRangeStart,FitRangeEnd,fInput,BackgroundMode,PeakType,0,SigmaParameter,DecayParameter,SharingParameter);
	//= Ultrapeak::PeakFit(hist,FitRangeStart,FitRangeEnd,fInput);

	//// PeakFit returns zero to the FullFitHolder pointer if the fit fails.
	//// We do not want to try and use a pointer that is zero
	if(fitA){
		C1->cd();
		gPad->Update();//// This is a line you sometimes need (mostly for graphs) after chaging pads when drawing in script
		
		hist->DrawCopy();
		fitA->DrawCopy("same");
        Ultrapeak::PrintData(fitA,true,hist);
        cout<<endl;
		
		// C1->WaitPrimitive(); //// Root functions that will wait for you to look at canvas before carrying on with a loop etc		
        
		//// If we are done with fitA, delete it and zero the pointer.
		delete fitA;fitA=0;
	}

}
