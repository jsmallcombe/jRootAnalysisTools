//
//
//	jROOT Tools
//	An object that runs a root based gating and background subtraction environment for TH2 and TH3
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef jamesfunc_spectool
#define jamesfunc_spectool

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


class jSpecTool : public TGCompositeFrame {

private:
    TGMainFrame *ParentWindow;
	TRootEmbeddedCanvas *fCanvas1;
	TH1	*histin,*histsub,*histzero,*specback;
	TGCheckButton   *fCheck0,*fCheck1,*fCheck2,*fCheck3,*fCheck4;
	TGHSlider    	*fHslider1,*fHslider2,*fHslider3;
	TGTextEntry *fTeh1,*fTeh2;
	static int spectool_iterator;
	static vector<string> BackOpt;
	string make_iterator();
	unsigned int N,gStart;
	string StrOpt;
		
	void RemovalPrep(TH1*);
	int RemovalStart(TH1*);
	void RemovalPrivate(TH1*);

public:    
	jSpecTool(TH1* = 0);
	jSpecTool(const TGWindow * p,TH1* = 0);
	virtual ~jSpecTool();

	void DoUpdate(bool=true);
	void DoUpdateF(){DoUpdate(false);}
	void UpdateSpecBack();
	void ReMakeSpecBack(TH1*);
	void RemovalPublic(TH1*,bool=true);
	void RemovalProcess(TH1*,int);
	void NewInput(TH1*);
    void Invert();

    void Closed(TObject* obj){
        Emit("Closed(TObject*)", (Long_t)obj);
    }
		
	ClassDef(jSpecTool, 1)
};


#endif
