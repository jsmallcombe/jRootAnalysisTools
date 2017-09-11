{ 
	TFile* MyFile= new TFile("Test/data/2Ddata.root","READ");
	gROOT->cd();
	TH2F* ret=(TH2F*)MyFile->Get("ey")->Clone();

	HistClickStop* bob=new HistClickStop(ret,"test");
	
	while(*bob){
		gSystem->ProcessEvents();
		cout<<"."<<flush;
	}
	delete bob;
	
// 	HistClickStop(TH1* hist=0,string title="Select",bool yaxis=true):selectedval(0),picked(0),cCan(0),xy(yaxis){
}
