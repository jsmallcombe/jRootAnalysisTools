{

	int a=3;

	
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
		
		
		// Define binning THnSparse
		const Int_t nbins[3] = {20, 20, 20};
		const Double_t xmin[3] = {0, 0, 0};
		const Double_t xmax[3] = {20, 20, 20};
		THnSparseI* sparse = new THnSparseI("sparse", "sparse", 3, nbins, xmin, xmax);
		
		TH3I* three=new TH3I("three","three",20,0,20,20,0,20,20,0,20);
		
		
		TRandom r;
		TF1 fn("bob","1+sin(x*3.14159/10.)",0,20);
		
		Double_t coords[3];
		
		for(int i=0;i<20000;i++){
			int a=r.Gaus(10,3);
			int b=fn.GetRandom();
			int c=r.Uniform()*20;
			
			// Put some gaps in the data to check the THnSparse bins are being selected correctly 
			if(b==12)continue;
			if(c==7)continue;
			
			// Turn off underoverflow
// 			if(abs(a-10)>9)continue;
// 			if(abs(b-10)>9)continue;
// 			if(abs(c-10)>9)continue;
			
			three->Fill(a,b,c);
			
			coords[0] = a;
			coords[1] = b;
			coords[2] = c;
			sparse->Fill(coords);
		}
		reta=three;
		
		
// 	cout<<endl<<"IS IT STATS "<<three->GetName()<<" "<<three->GetSumw2().fN<<endl;
// 		b = new jgating_tool(reta);
		
// 		new jGatingToolTH3(sparse);
		
// 		new jGatingToolTH3(retb);
		new jGatingToolTH3(three);
// 		new jgating_tool(three);
		
// 		new jGatingToolTH3("");
		
// 		jGatingToolTH3 *bill=new jGatingToolTH3("");
// 		bill->UpdateInput(reta);
		
// 		bill->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
		
		
		
// Set slice condition on Z (axis 2)
// sparse->GetAxis(2)->SetRange(sparse->GetAxis(2)->FindBin(5.0), sparse->GetAxis(2)->FindBin(10.0));

// sparse->GetAxis(0)->SetRange(1,4);
// sparse->GetAxis(1)->SetRange(1,4);
// 		new TCanvas();
// 		gPad->Update();
// 		sparse->Projection(0)->DrawCopy();
// 		new TCanvas();
// 		gPad->Update();
// 		sparse->Projection(1)->DrawCopy();
// 		new TCanvas();
// 		gPad->Update();
// 		sparse->Projection(2)->DrawCopy();

		
		
		
		
	}
	
	
	
	
		new jEnv;
// 		new TBrowser;
}
