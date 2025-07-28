{
string dir=gSystem->pwd();	
string load=dir+"/bin/libJanalysistools.so";
dir=".x "+dir+"/Test";

//load the library	
gROOT->ProcessLine(".include ./include");
gSystem->Load(load.c_str());

//load some 1D histograms
gROOT->ProcessLine((dir+"/data/1Dhist.C").c_str());
gROOT->ProcessLine((dir+"/data/1Dhistlow.C").c_str());
gROOT->ProcessLine((dir+"/data/1Doversub.C").c_str());
gROOT->ProcessLine((dir+"/data/LoadFiles.C").c_str());


// Pick a script by commenting
// dir+="/scripts/jEnvTest.C";    // Test jEnv and gui tools
// dir+="/scripts/UltraFitTest.C"; // Test Ultrapeak fitting environment
dir+="/scripts/NewGateTest.C"; // Test gating tool
// dir+="/scripts/THnTest.C"; // Gating THnSparse test
// dir+="/scripts/EfficiencyCurves.C"; // Test automated gamma efficiency curve functions 


//Run that script
gROOT->ProcessLine(dir.c_str());
}
