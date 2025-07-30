{ 
//  SetGlobalNegative();
    TCanvas* C1=new TCanvas();
    C1->Divide(2,3);
    C1->cd(1);
    A->Draw("col");
    C1->cd(2);
    B->Draw("col");
    CanvasNegative(C1->cd(2));
    C1->cd(3);
    C->Draw("col");
    C1->cd(4);
    D->Draw("col");
    CanvasNegative(C1->cd(4));
    C1->cd(5);
    gPad->Update();
    G1->DrawClone("al");
    C1->cd(6);
    gPad->Update();
    G2->DrawClone("al");
    CanvasNegative(C1->cd(6));
    gPad->Update();
    
    
    gROOT->cd();
    gSystem->cd("./Test/data/");
    
    new jEnv();
    
    
    C1->SetWindowPosition(1000,200);
    C1->Modified();
    C1->Update();
	
	new jSpecTool(oversub);
	new jAngleAngel(dedx);
// 	new j2DAlphaCalibrator(ydots,11);
	new jCompCanvas(sili);C->Draw("same");
	new jScale();
	new jEval();
    new jFittingTool2D((TH2*)ydots);
    
//     jhistquestion* jHQ= new jhistquestion("Yes","No","Maybe");
//     jHQ->Resize(900,900);
//     jHQ->GetCanvas()->cd();
//     C->DrawCopy();
//     jHQ->WaitAnswer();
}
