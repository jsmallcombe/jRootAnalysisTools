{
    
    // A script to look at how wrong the estimate of the maximum of a combined decay + gaus peaks is
    
    TGraph *range=new TGraph;
    range->SetPoint(0,0,1);
    range->SetPoint(1,0.1,1.005);
    range->SetPoint(2,0.5,1.1);
    range->SetPoint(3,1,1.3);
    range->SetPoint(4,10,2.3);
    range->SetPoint(5,30,3.4);
    range->SetPoint(6,100,4.2);
    range->SetPoint(7,300,5.4);
    range->SetPoint(8,1000,6);
    range->SetPoint(9,10000,8);
    range->SetLineColor(2);
    
    TGraph *r1=new TGraph;
    TGraph *r2=new TGraph;
    r1->SetLineColor(2);
    r2->SetLineColor(2);
    
    TGraph *ErrOrg=new TGraph;
    TGraph *ErrImpr=new TGraph;
    
    TGraph *gr=new TGraph;
    gr->SetPoint(0,0.0001,1);
    
    TGraph *GR=new TGraph;
    GR->SetPoint(0,1000,1);
    
    
    double sigma=1;

    for(double d=-1.5;d<=4.1;d+=0.1){
        double decay=pow(10,d);
        cout<<"."<<flush;
        
        double Pbest=1;
        double ErrorSumBest=1E14;
        
        double prange=range->Eval(decay);
        double plims=((prange-1)*0.5/abs(d+2))+0.01;
        
        r1->SetPoint(r1->GetN(),decay,prange-plims);
        r2->SetPoint(r2->GetN(),decay,prange+plims);
        
        double ErrorSumOrig=0;
        for(double PP=prange-plims;PP<=prange+plims;PP+=plims*0.1){

            double ErrorO=0;
            double ErrorSum=0;
            for(double sharing=0.1;sharing<1;sharing+=0.05){
            
                double x_0=DecGausMaxX(sigma,decay)*(1-sharing);
                double xe=sharing/UniGaus(x_0,sigma); 
                double ze=(1-sharing)/DecGaus(x_0,sigma,decay);
                
                double X_0=DecGausMaxX(sigma,decay)*pow(1-sharing,PP);
                double xeta=sharing/UniGaus(X_0,sigma); 
                double zeta=(1-sharing)/DecGaus(X_0,sigma,decay);
                
                double ymax=0;
                double xopt=X_0;
                
                double ym=0;
                double xo=x_0;               
                
                for(double x=1.5*X_0;x<0.5*X_0;x+=0.0001){
                    double y=xeta*UniGaus(x,sigma)+zeta*DecGaus(x,sigma,decay);
                    if(y>ymax){xopt=x;ymax=y;}
                    
                    y=xe*UniGaus(x,sigma)+ze*DecGaus(x,sigma,decay);
                    if(y>ym){xo=x;ym=y;}
                    
                }
                ErrorSum+=xopt-X_0;
                ErrorO+=xo-x_0;
            }
            if(abs(ErrorSum)<ErrorSumBest){
                ErrorSumBest=abs(ErrorSum);
                Pbest=PP;
            }
            
            ErrorSumOrig=abs(ErrorO);
        }
        
        ErrOrg->SetPoint(ErrOrg->GetN(),decay,ErrorSumOrig);
        ErrImpr->SetPoint(ErrImpr->GetN(),decay,ErrorSumBest);
    
        gr->SetPoint(gr->GetN(),decay,Pbest);
        GR->SetPoint(GR->GetN(),sigma/decay,Pbest);
    }
    TCanvas* C1=new TCanvas();
    C1->Divide(3);
    C1->cd(1);
    gPad->Update();
    gr->Draw("al");
    range->Draw("samel");
    r1->Draw("samel");
    r2->Draw("samel");
    gPad->SetLogx();
    gr->GetHistogram()->SetTitle("X_0 Correction Power;decay/sigma;power");
    
    C1->cd(2);
    gPad->Update();
    GR->Draw("al");
    gPad->SetLogx();
    GR->GetHistogram()->SetTitle("X_0 Correction Power;sigma/decay;power");
    
    cout<<endl;
    GR->Print();
    cout<<endl;
    
    C1->cd(3);
    gPad->Update();
    ErrOrg->Draw("al");
    ErrImpr->SetLineColor(2);
    ErrImpr->Draw("samel");
    gPad->SetLogx();
    gPad->SetLogy();
    ErrOrg->GetHistogram()->SetTitle("X_0 Total Error Power;decay/sigma;Error [arb]");
    
    
    vector<double> testpoints{0.1,1,10,100};
    TCanvas* C2=new TCanvas();
    C2->Divide(testpoints.size());
    
    for(unsigned int i=0;i<testpoints.size();i++){
        C2->cd(i+1);
        gPad->Update();
        
        TGraph* old=new TGraph();
        TGraph* nw=new TGraph();
        nw->SetLineColor(2);
        
        double decay=testpoints[i]*sigma;
        double PP=gr->Eval(testpoints[i]);
        

        for(double sharing=0;sharing<1;sharing+=0.01){

            double x_0=DecGausMaxX(sigma,decay)*(1-sharing);
            double xe=sharing/UniGaus(x_0,sigma); 
            double ze=(1-sharing)/DecGaus(x_0,sigma,decay);
            
            double X_0=DecGausMaxX(sigma,decay)*pow(1-sharing,PP);
            double xeta=sharing/UniGaus(X_0,sigma); 
            double zeta=(1-sharing)/DecGaus(X_0,sigma,decay);
            
            double ymax=0;
            double xopt=X_0;
            
            double ym=0;
            double xo=x_0;               
            
            for(double x=1.5*X_0;x<0.5*X_0;x+=0.0001){
                double y=xeta*UniGaus(x,sigma)+zeta*DecGaus(x,sigma,decay);
                if(y>ymax){xopt=x;ymax=y;}
                
                y=xe*UniGaus(x,sigma)+ze*DecGaus(x,sigma,decay);
                if(y>ym){xo=x;ym=y;}
                
            }
            old->SetPoint(old->GetN(),sharing,xo-x_0);
            nw->SetPoint(nw->GetN(),sharing,xopt-X_0);
        }
        
        old->SetPoint(old->GetN(),1,-TMath::MaxElement(old->GetN(),old->GetY()));
        old->Draw("al");
        nw->Draw("samel");
    
    }
    
    
}
