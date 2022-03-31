{ 
//     SetGlobalNegative();
//     TCanvas* C1=new TCanvas();
//     dedx->Draw("col");    
    
    gROOT->cd();
    
    new j2DPeakFit(ydots,11);
    
//     C1->SetWindowPosition(1000,200);
//     C1->Modified();
//     C1->Update();
}
