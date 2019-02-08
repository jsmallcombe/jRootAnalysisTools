Double_t decaypeak(Double_t *x, Double_t *par)
{
    return DecGaus(x[0],par[0],par[1]);
}

void SkewTest(){
    
      
    TF1 *f1 = new TF1("myfunc",decaypeak,-500,500,2);
 
    new TCanvas();
    gPad->Update();
    TGraph R2;
    TGraph R1;
    int steps=500;
    for(int i=0;i<=steps;i++){
            double R10=-4+8.0*i/steps;
            double r=pow(10,R10);
            f1->SetParameters(10.,10./r);
            double Y=0;
            for(int x=-10;x<=100;x++){
                 if(f1->Derivative(-x)>0){
                        for(int c=1;c<=10000;c++){
                            double X=-((x-1)+c*0.0001);

                         if(f1->Derivative(X,0,0.00001)>0){
                                if(f1->Eval(X)>Y){
                                    R2.SetPoint(R2.GetN(),R10,X);
                                    if(i%10==0){
                                        R1.SetPoint(R1.GetN(),R10,X);
                                    }
                                }
                                break;
                            }
                        }
                     break;
                }
                Y=f1->Eval(-x);
            }
    }
    R2.DrawClone("al");
    R1.SetLineColor(2); 
    R1.DrawClone("samel");
    
 
    new TCanvas();
    gPad->Update();
    f1->SetParameters(10.,10000);
    f1->Draw();
            
    TStopwatch stop;
    stop.Start();
    new TCanvas();
    gPad->Update();
    TGraph2D G;
    for(int i=1;i<=10000;i++){
        double sigma=i/1000.;
        for(int j=1;j<=1000;j++){
            double decay=j/10.;
            double R=sigma/decay;
            double X=R2.Eval(log10(R))*(sigma/10.);
            double x=DecGausMaxX(sigma,decay);
//             G.SetPoint(G.GetN(),sigma,decay,X/x);
        }
    }
    
    cout<<endl<<stop.RealTime()<<endl;
    stop.Start();

    for(int i=1;i<=10000;i++){
        double sigma=i/1000.;
        for(int j=1;j<=1000;j++){
            double decay=j/10.;
            NewDecGausMaxX(sigma,decay);
        }
    }
    
    cout<<endl<<stop.RealTime()<<endl;
    
}
