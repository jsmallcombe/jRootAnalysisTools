//
//
//	jROOT Tools
//	GUI tool for fitting and saving with ultrapeak fuction
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef jultrafit_env
#define jultrafit_env

// Prefix:
//  gGlobal - Defined globally such as functions
//  fFunction - Defined within a function
//  sScope - Defined in a smaller scope e.g. while loop

// ROOT
#include <TStyle.h>
#include <TCanvas.h>
#include <TRootCanvas.h>
#include <TPad.h>
#include <TH1.h>
#include <TF1.h>
#include <TAxis.h>
#include <TMath.h>
#include <TLine.h>
#include <TLegend.h>
#include <TString.h>
#include <TGraphErrors.h>
#include <TGButton.h>
#include <TControlBar.h>
#include <TGFrame.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TGTextEntry.h>
#include <TGLabel.h>
#include <TQObject.h>
#include <TRootHelpDialog.h>
#include <TGFileDialog.h>
#include <TGClient.h>
#include <TRootEmbeddedCanvas.h>
#include <TBrowser.h>
#include <TText.h>
#include <TLatex.h>
#include <TBox.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGComboBox.h>
#include <TStopwatch.h>

// #include "Math/GSLIntegrator.h"
// #include "Math/WrappedTF1.h"


#include "j_utility.h"
#include "j_gpad_tools.h"
#include "j_ultrapeak.h"
#include "j_hist_formatting.h"

// C++
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

class UltraFitEnv : public TGCompositeFrame
{ 
    public:       
	////////////// Public Access Environment variables ///////////////////   
	FullFitHolder cLastFit;
	
	///////// Constructors copy etc //////////////
	
	UltraFitEnv(TH1* =0,TCanvas* =0);
	UltraFitEnv(const TGWindow * p,TH1* =0,TCanvas* =0,int=0);
	virtual ~UltraFitEnv();
	
	//These need to be implemented properly, what with all the pointers etc
	UltraFitEnv( const UltraFitEnv &obj)= default;//copy constructor
	UltraFitEnv& operator=(const UltraFitEnv&)= default;//assignment operator
	UltraFitEnv(UltraFitEnv&&) = default;                    // Move constructor
	UltraFitEnv& operator=(UltraFitEnv&&) & = default;       // Move assignment operator

	
	///////////////////////////////////////////////////////////////////////////
	//////// Methods for General Use including Command Line ////////
	///////////////////////////////////////////////////////////////////////////
	
	// Never give out access to ACTUAL gHist
// 	TH1F* gHistGet(){return (TH1F*)gHist->Clone();}
	void SaveFit();
	void PrintFits();
	void ExportFits();
	void ExportFitsMan(string);
	void SetSep(unsigned int fN,double fS,double fSe=-1);
	void ImportPeaks(string file);
	void LoadSession(string file);

	///////////////////////////////////////////////////////////////////////////
	//////// Methods For The Graphical Interface ////////
	///////////////////////////////////////////////////////////////////////////
	
// 	void MakeCanvas();
	void ClickedCanvas(Int_t, Int_t, Int_t, TObject *);
// 	void test(){cout<<endl<<endl<<"Test success"<<endl<<endl;}	
	void PointMe(){cout<<endl<<this<<endl;}// For recovering command line access when working in root interpretive mode	
	void TextToSep();
	void SetN();
	void AddTextBox();
	void RemoveTextBox();
	void FitGUIPeak();
	void SetCapture(int);
	void CaptureHistogram(TPad*,TObject*,Int_t);
	void CaptureCanvas(TPad*,TObject*,Int_t);
   
	void SetNewHist(TH1*,bool=true);
	void ConnectNewCanvas(TVirtualPad*);
	void ReDrawgHist();
	void DrawSaveLabels();
	void DrawgHist();
	void ClearFits();
	void ClearFitsD();
	
	void LoadSession();
    
    void ChangeCentMode();
	
	void HideSubShapes();
	void HideShape();
	
	void Help();
	void jSaveAs();
	
	void PassNewHist(TH1*);
	
	void ClearExclusion();
	
    void Closed(TObject* obj){
        Emit("Closed(TObject*)", (Long_t)obj);
    }
	void KillCan();
    
    private:	    
	    
    TGMainFrame* MainFrame; //null unless selfowned mainframe
    
	// Members
	TGHorizontalFrame* mainhold;
	TGVerticalFrame* cFrame,*cShapePane,*cTailParPane,*cTwinParPane;
	TRootEmbeddedCanvas *cPan; 
	string can_name;
	TCanvas *cCan;
	TH1 *gHist;//always 0 if deleted, never give access/use directly
	TH1 *gHistDrawn;
	string gHistDrawnName;
	bool cShift,cCtrl,cAlt,cGoodFit,cSaveConf,cClearConf;
	vector< double > cClicker,cRClicker,cExClicker;
	vector< FullFitHolder* > cFitList;
	vector< TText > cPeakLabels;
	vector< TText > cSaveLabels;
	TStopwatch Stop;
	
	TGComboBox *fCombo;
	bool fFitFinished;
	
	TGTextEntry* cShapeTsig,*cShapeTdecay,*cShapeTshare,*cShapeTtwinwidth,*cShapeTtwinshare;
	
	TGLabel* decaysigmablabel;
	
	// Peak controls
	TGCheckButton* fCheckLabels,*fCheckLimit,*fCheckNoTail,*fCheckTwin;
	vector< TGHorizontalFrame* > cTframe;//row holder
	vector< TGTextEntry* > cTbox;//peak separation
	vector< TGTextEntry* > cPTbox;//peak selected/fit centroids
	vector< TGTextEntry* > cRTbox;//peak ratio
	TGTextEntry* cNpd;
	TGTextEntry* cZc;//zeroth peak centroid
	
	TGTextEntry* fZERO;//zeroth peak centroid override
	TGTextButton* cTrueCentButton;
    bool cTrueCent;
	
	unsigned int cNfit;//Keeps track of the current number of peaks, heavily trusted in terms of the above vectors
	unsigned int cNfree;
	
	// Internal Methods, not called directly or by GUI
	void BuildDialogBox(int opt=0);
	TObject* FindCan();
	TCanvas* GetCan();
	void ExternalHistUpdateCheck();
	void DisconnectCanvasSignals();
	void HideCanvas();
	void ShowCanvas();
	void ReDrawFrames();
	void LoadSession(TFile* file);
	void ImportPeaks(TFile* file);
    
    void ExportSession(TString FileName="peakinfo.root");
	
	vector< double > GetClicks(int=3);
	void RemoveLines();
	void UpdateLines();
	void UltraFitAfter(FullFitHolder*);
	vector< jPeakDat > MakePeakList();
	vector< jPeakDat > MakeBoundryPeakList(double& bound_l,double& bound_u);
	vector< double > MakeBoundryPeakListAbs();

	static int UltraFitEnv_iterator;
	ClassDef(UltraFitEnv, 3);
    
    public: 
    double GetFitVal(unsigned int f,unsigned int v);
    
    // Because list of peaks may be spread over several multipeak fits
    double GetPeakVal(unsigned int f,unsigned int v);
    
};

// inline UltraFitEnv* gStart(double fSep=-1){
// 	UltraFitEnv* gEnv = new UltraFitEnv(0,fSep);
// 	return gEnv;
// }

inline UltraFitEnv* FitUltra(TVirtualPad* fPad=gPad){if(!fPad)return 0;
	TCanvas* fCan=fPad->GetCanvas();
	if(fCan){
		return new UltraFitEnv(0,fCan);
	}
	return 0;
}


#endif
