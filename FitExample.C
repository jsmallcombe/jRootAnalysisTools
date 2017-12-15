{
	TCanvas *C1 = new TCanvas();
	
	TH1D *histim = new TH1D("hist","hist",1000,0,1000);//replace this with an actual histogram
	
	TH1 *hist = (TH1*)histin; //assign pointer to be parent class
	//We use no fucntions of TH1D,TH1F,TH1I directly, so all code aims to be generic using TH1D
	
	//Different ways of getting the input
	double XX=800; //peak energy
	//double XX=hist->GetXaxis()->GetBinCenter(hist->GetMaximumBin())
	//double XX=GetHistClickVal(hist,"Select Peak",false);//Getting a click
	
	//Give the fitting data of the one peak
	jPeakDat peak;
	peak.Centroid=XX;
	peak.CentConstrained=false;
	peak.CentError=-1;// <=0 fixed param
	peak.Ratio=-1;// <=0 unused
	peak.RatioError=-1;// <=0 fixed param
		
	//jPeakDat peak(xx,false,-1,-1,-1):
	
	//Fitting function takes a vector list of peaks each relative to the previous one
	vector< jPeakDat > fInput;
	fInput.push_back(peak);
	
// 	static FullFitHolder* PeakFit(TH1* fHist,double fLeftUser,double fRightUser,vector< jPeakDat > &fInput,int backmode=0,int peaktype=0,string sig="",string dec="",string sha="");
	
	double FitRangeStart=XX-25;
	double FitRangeEnd=XX-25;
	int BackgroundMode=0;
	int PeakType=0
	
	//Defauly parameters should be fine
	string SigmaParameter="";
	//string SigmaParameter="10+5"; //Fit peaks with a sigma of 10 +- 5
	string DecayParameter="";
	string SharingParameter="";
	
	// You dont actually need to give all the arguments if we want the defaults
	FullFitHolder* fitA = Ultrapeak::PeakFit(hist,FitRangeStart,FitRangeEnd,fInput,BackgroundMode,PeakType,SigmaParameter,DecayParameter,SharingParameter);
	//= Ultrapeak::PeakFit(hist,FitRangeStart,FitRangeEnd,fInput);

	//PeakFit returns zero to the FullFitHolder pointer if the fit fails.
	//We do not want to try and use a pointer that is zero
	if(fitA){
		C1->cd();
		gPad->Update();//This is a line you sometimes need after chaging pads when drawing in script
		
		hist->DrawCopy();
		fitA->DrawCopy("same");
		
		C1->WaitPrimitive(); //Root functions that will wait for you to look at canvas (close or double click it)
		
		//If we are done with fitA, delete it and zero the pointer.
		delete fitA;fitA=0;
	}	
}
