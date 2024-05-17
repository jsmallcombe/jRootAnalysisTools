{ 
//    UltraFitEnv* bob=new UltraFitEnv(C);
   jCompCanvas* bob=new jCompCanvas(sili);
   C->Draw("same");
   
    bob->Connect("Closed(TObject*)", "TApplication", gApplication, "Terminate()");
}
