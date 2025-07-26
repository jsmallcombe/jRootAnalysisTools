{ 
	UltraFitEnv* bob=new UltraFitEnv(C); // Gammas
// 	UltraFitEnv* bob=new UltraFitEnv(sili);
// 	UltraFitEnv* bob=new UltraFitEnv(sililow);
	bob->Connect("Closed(TObject*)", "TApplication", gApplication, "Terminate()");
}
