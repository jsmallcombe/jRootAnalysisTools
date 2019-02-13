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

//Pick a script by commenting
// dir+="/scripts/EfficiencyCurves.C";
// // dir+="/scripts/GateTest.C";
  dir+="/scripts/UltraFitTest.C";
//  dir+="/scripts/Massage.C";
//  dir+="/scripts/gPadTest.C";
//dir+="/scripts/jEnvTest.C";

//Run that script
gROOT->ProcessLine(dir.c_str());
}
