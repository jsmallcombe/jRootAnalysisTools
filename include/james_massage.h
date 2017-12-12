//
//
//	James Root Library
//	An object that runs a root based gating and background subtraction environment for TH2 and TH3
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef jamesfunc_massage
#define jamesfunc_massage

#include "TROOT.h"
#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"
#include "TGLayout.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGTextEntry.h"
#include "TGSlider.h"
#include "TGLabel.h"
//#include "TGTripleSlider.h"
#include "TH2F.h"
#include "TGButtonGroup.h"
#include "TGButton.h"
#include "THashList.h"
#include "TStyle.h"
#include "TSpectrum.h"

#include <iostream>
#include <iomanip> 

#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


class jmassage : public TGMainFrame {

private:
	TRootEmbeddedCanvas *fCanvas1;
	TH1	*histin,*histsub,*specback;
	TGCheckButton   *fCheck0,*fCheck1,*fCheck2,*fCheck3;
	TGHSlider    	*fHslider1,*fHslider2,*fHslider3;
	TGTextEntry *fTeh1,*fTeh2;
	static int jmassage_iterator;
	static vector<string> BackOpt;
	string make_iterator();
	unsigned int N;
	string StrOpt;

public:
	jmassage(TObject* = 0);
	virtual ~jmassage();

	void DoUpdate();
	void UpdateSpecBack();
	void RemovalProcess(TH1*);
	void ReMakeSpecBack(TH1*);
	
	ClassDef(jmassage, 1)
};



#endif
