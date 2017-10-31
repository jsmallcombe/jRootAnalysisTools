//
//
//	James Root Library
//	Interactive tools for use in-pad in a root environment
//	05 Mar 2017
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

#include "james_utility.h"


using namespace std;



///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

TObject* obj_capture(TClass*,TVirtualPad* =gPad);
void obj_removeall(TClass*,TVirtualPad* =gPad);
void obj_remove(TClass*,TVirtualPad* =gPad,bool=0);
TH1* hist_capture(TVirtualPad* =gPad);

void ClickPeakDrawConnect(Int_t,Int_t,Int_t,TObject*);
	
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////



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
