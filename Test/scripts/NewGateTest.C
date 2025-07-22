{

	int a=2;

	
	TH1 *reta,*retb;
	if(a==2){
		TFile* MyFile= new TFile("Test/data/2Ddata.root","READ");
		gROOT->cd();
		reta=(TH2F*)MyFile->Get("yy")->Clone();
		retb=(TH2F*)MyFile->Get("ey")->Clone();
		MyFile->Close();
			
		
// // removing overflow underflow for comparison with old methods
// 		int X=retb->GetNbinsX();
// 		int Y=retb->GetNbinsY();
// 		for(int y=0;y<Y+1;y++){
// 			retb->SetBinContent(0,y,0.0);
// 			retb->SetBinContent(X+1,y,0.0);
// 		}
// 		for(int y=0;y<X+1;y++){
// 			retb->SetBinContent(y,0,0.0);
// 			retb->SetBinContent(y,Y+1,0.0);
// 		}
		
		
		
		new jGatingToolTH2(retb);
		new jgating_tool(retb);
		
// 		new jGatingToolTH2("");
// 		jGatingToolTH2 *bob=new jGatingToolTH2("");
// 		bob->UpdateInput(reta);
		
	}else{

		TFile* MyFile= new TFile("Test/data/3Ddata.root","READ");
		gROOT->cd();
		retb=(TH3F*)MyFile->Get("Mult_alphaprotons_gamma");
		
		TH3I* three=new TH3I("three","three",20,0,20,20,0,20,20,0,20);
		TRandom r;
		TF1 bob("bob","1+sin(x*3.14159/10.)",0,20);
		for(int i=0;i<20000;i++){
			three->Fill(r.Gaus(10,3),bob.GetRandom(),r.Uniform()*20);
		}
		reta=three;
		
// 		b = new jgating_tool(reta);
		
		
// 		new jGatingToolTH3(retb);
// 		new jgating_tool(retb);
		
// 		new jGatingToolTH3("");
		
		jGatingToolTH3 *bill=new jGatingToolTH3("");
		bill->UpdateInput(reta);
		
		
	}
	
	
	
	
		new jEnv;
// 		new TBrowser;
}
