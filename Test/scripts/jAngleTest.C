{ 
//     SetGlobalNegative();
//     TCanvas* C1=new TCanvas();
//     dedx->Draw("col");    
    
    gROOT->cd();
    
    new jAngleAngel(dedx);
    
//     C1->SetWindowPosition(1000,200);
//     C1->Modified();
//     C1->Update();
}
