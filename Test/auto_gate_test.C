
//     auto_gate inputs
//     TH2* raw_input          Histogram to be gated
//     int xyz=0               The gating axis
//     int itr=25              The number of interations for TSpectrum Background
//     Option_t *specopt=""    TSpectrum Background options
//     double sigma=1.5        Typical peak sigma
//     double thresh=0.05      The size of the smallest peak to be considered, as a fraction of the largest
//     double Rd=1             Lower gating range (TSpectrum rarely does the whole spectrum with one setting)
//     double Ru=1             Upper gating range
// 
//     Gating Tool Default TSpectrum Background Settings
//     High     = 25,""
//     Medium   = 10,""
//     Lower    = 30,"kBackOrder4"
// 

vector<TH1*> auto_gate(TH2* raw_input, int xyz=0, int itr=25, Option_t *specopt="",double sigma=1.5,double thresh=0.05,double Rd=1,double Ru=-1){
    vector<TH1*> ret;
    
	TH1* proj=hist_proj(raw_input,xyz,"projraw",true);
	TH1* projsub=(TH1*)proj->Clone("projsub");
    TH1* specback=TSpectrum::StaticBackground(proj,itr,specopt);
    projsub->Add(specback,-1);
    
    TAxis* ax=proj->GetXaxis();
    int Nb=proj->GetNbinsX();
//     double w=ax->GetBinWidth(1);
    
    TSpectrum *s = new TSpectrum(200);
    Int_t nfound = s->Search(projsub,sigma,"",thresh);
    Double_t *xpeaks;
    xpeaks = s->GetPositionX();
    
    if(Rd>Ru){
        Rd=ax->GetBinLowEdge(1);
        Ru=ax->GetBinLowEdge(Nb+1);
    }
    
    for(int p=0;p<nfound;p++) {
        Double_t xp = xpeaks[p];
        if(xp<Rd||xp>Ru)continue;
        
        int b1=ax->FindBin(xp-sigma*2);
        int b2=ax->FindBin(xp+sigma*2);
        int b3=ax->FindBin(xp+sigma*3);
        
        double ingatecount=proj->Integral(b1,b2);
        double background=specback->Integral(b1,b2);
        double backfrack= background/ingatecount;
        
        TH1* gate_hist=hist_gater_bin(b1,b2,raw_input,xyz,"gate_hist");

        TH1* compton_hist=hist_gater_bin(b3,raw_input,xyz,"c_gate");
        TH1* output_hist=scaled_back_subtract(gate_hist,compton_hist,backfrack,0.04);
        delete compton_hist;
        delete gate_hist;
        
        stringstream ss;
        ss<<"GateOn"<<xp;
        output_hist->SetName(ss.str().c_str());
        ret.push_back(output_hist);
    }

    return ret;
}


void auto_gate_test(){
    
	TFile* MyFile= new TFile("Test/data/2Ddata.root","READ");
	gROOT->cd();
	TH2* hist=(TH2F*)MyFile->Get("yy")->Clone("yyClone");
	MyFile->Close();
    
    vector<TH1*> ret=auto_gate(hist,0,25,"",1.5,0.1,200,1500);
    
    TFile out("out.root","RECREATE");
    out.cd();
    for(auto h : ret){
        h->Write();
    }
    out.Close();
}
