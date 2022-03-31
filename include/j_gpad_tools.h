//
//
//	jROOT Tools
//	Interactive tools for use in-pad in a root environment
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef jamesgpad_h
#define jamesgpad_h

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <TBrowser.h>
#include <TCanvas.h>
#include <TText.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TBox.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TRootCanvas.h>
#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"
#include "TGButtonGroup.h"
#include "TGToolTip.h"
#include "TROOT.h"
#include "TSystem.h"

#include "j_utility.h"
#include "j_hist_formatting.h"


using namespace std;



///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Return a TObject if there is one drawn in the pad
TObject* obj_capture(TClass*,TVirtualPad* =gPad);

// Remove objects drawn on a paf¥d
void obj_removeall(TClass*,TVirtualPad* =gPad);
void obj_remove(TClass*,TVirtualPad* =gPad,bool=0);

// Return a histogram if there is one drawn in the pad
TH1* hist_capture(TVirtualPad* =gPad);

// Basic quick peak fitter for pad click
void ClickPeakDrawConnect(Int_t,Int_t,Int_t,TObject*);

// Connect any canvas to the above quick fitter function "ClickPeakDrawConnect"
inline void ConnectPeakClickerCanvas(TCanvas* Can){
    if(Can){
        TQObject::Connect(Can, "ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ClickPeakDrawConnect(Int_t,Int_t,Int_t,TObject*)");
	}
}

void ToolTipHide();

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Will draw a histogram and then allow root to continue processing while waiting for a click, I think.
// Unsure what this was used for

class HistClickStop{ 
   private:
	bool selected;
	double pickedx,pickedy;
	TCanvas* cCan;
	bool xy;
	
	void DeleteCan(){
		if(cCan){
			cCan->Close();
			delete cCan;
// 			TRootCanvas* c=(TRootCanvas*)cCan->GetCanvasImp();
// 			c->DeleteWindow();
			cCan=0;
		}
	}

   public:
	HistClickStop(TH1* hist=0,string title="Select",bool yaxis=true);
	~HistClickStop(){DeleteCan();};
	
	operator double() const {
		if(xy)
		return pickedy;
		else
		return pickedx;
		
	}
	operator int() const { return double(); }
	operator bool() const {return !selected;}
	
	bool PickedX(){return pickedx;}
	bool PickedY(){return pickedy;}
	bool Picked(){return selected;}
	
	void ClickedCanvas(Int_t event, Int_t px, Int_t py, TObject *selected_ob);
};


double GetHistClickVal(TH1* hist,string title="",bool y=true);



///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// A Window that will display a histogram and a series of text buttons to ClickedCanvas
// Used for human interfacing a list of of histograms i.e. good/bad, type A/B etc

class jhistquestion : public TGMainFrame {
private:
	TRootEmbeddedCanvas *fCanvas1;
	TGButtonGroup	*fBgroup1;
	int answer;
public:
	jhistquestion():fCanvas1(0),fBgroup1(0){};
	jhistquestion(string a,string b="",string c=""):jhistquestion(vector<string>{a,b,c}){};
	jhistquestion(vector<string>,TH1* h=0);
	virtual ~jhistquestion(){};

	TH1*  DrawCopySame(TH1*);
	TCanvas* GetCanvas(){if(fCanvas1)return	fCanvas1->GetCanvas();return 0;}
	
	int WaitAnswer();
	void SetAnswer(int);

	ClassDef(jhistquestion, 1)
};




#endif
