//
//
//	jROOT Tools
//	Depreciated - functions for handling projection, gating and background subtractions of TH2/TH3
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
//

#ifndef j_gating_depreciated
#define j_gating_depreciated

#include <TChain.h>
#include <TGSplitter.h>
#include <TTreeReader.h>

#include <j_gating_select_frame.h>
#include <j_ultrapeak_env.h>

using namespace std;			


///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/////////// Functions gating and subtracting TH2 and TH3   /////////// 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

//3D gating functions


TAxis* hist_gater(TH3*,string&,int);
TAxis* hist_proj(TH3*,string&,int);


//these will nicely overwrite any previously done projection OF THE SAME TYPE
//if you dont want that add a name in string
TH2* hist_gater(double,double,TH3*,int=0,string="");
TH2* hist_gater_bin(int,int,TH3*,int=0,string="");
TH2* hist_gater(double,TH3*,int=0,string="");// gates from input to axis max
TH2* hist_gater_bin(int,TH3*,int=0,string="");

//2D gating functions
//these will nicely overwrite/fill any previously done 2D projection add a name in string
TH1* hist_gater(double,double,TH2*,int=0,string="proj");
TH1* hist_gater_bin(int,int,TH2*,int=0,string="proj");
TH1* hist_gater(double,TH2*,int=0,string="proj");// gates from input to axis max
TH1* hist_gater_bin(int,TH2*,int=0,string="proj");

//These just forward to the correct above type after checking TH2/3 inheritance 
TH1* hist_gater(double,double,TH1*,int,string);
TH1* hist_gater_bin(int,int,TH1*,int,string);
TH1* hist_gater(double,TH1*,int,string);
TH1* hist_gater_bin(int,TH1*,int,string);


// Project an axis Functions
//these will nicely overwrite/fill any previously done 2D projection add a name in string
TH1* hist_proj(TH1* in,int xyz=0,string name="proj",bool flowless=false);


//addition/subtraction functions 
//Work for th2 and 3 inherited classes
TH1* scaled_back_subtract(TH1*,TH1*,double,double=0,bool scale=true);
TH1* scaled_back_subtract(TH1*,TH1*,double,TH1*,double=0,bool scale=true);

inline TH1* scaled_addition(TH1*h1,TH1*h2,double f,double ff=0,bool scale=true){return scaled_back_subtract(h1,h2,-f,ff,scale);}
inline TH1* scaled_addition(TH1*h1,TH1*h2,double f,TH1*h3,double ff=0,bool scale=true){return scaled_back_subtract(h1,h2,-f,h3,ff,scale);}


void TH3axisreseter(TH3*);


//Created this class to save on extra maths waste adjusting large histograms
//via the limited public functions
class TH1ErrorAdj : public TH1{
public:
	TH1ErrorAdj():TH1(){};
	~TH1ErrorAdj(){};
	void AdjustError(const TH1* back,double frac);
	ClassDef(TH1ErrorAdj, 1)	
};



enum commandidentifiersjgatingtool {
   HId1,
   HId2,
   HId3,
   HCId1,
   HCId2,

   HSId1,
   HSId2,
   HSId3,
   HSId4,
};

class j_gating_frame : public TGVerticalFrame {

private:
	TGLayoutHints* fBly;
	TRootEmbeddedCanvas *fCanvas1;
	TF1                 *fFitFcn;
	TGHorizontalFrame   *fHframe0, *fHframe1, *fHframe2, *fHframe3;
	TGTripleHSlider	*fHslider1;
	TGHSlider    	*fHslider2,*fHslider3;
	TGDoubleHSlider	*fHslider4;
	TGTextEntry         *fTeh1, *fTeh2, *fTeh3;
	TGTextBuffer        *fTbh1, *fTbh2, *fTbh3;
	TGCheckButton       *fCheck2,*fCheck1,*fCheck0;
	TGButtonGroup	*fBgroup1,*fBgroup2,*fBgroup3;
	TGRadioButton	*fRButton1,*fRButton2,*fRButton3,*fRButton4,*fRButton5,*fRButton6,*fRButton7,*fRButton8,*fRButton9,*fRButtonz;
	TGTextButton		*fTButton1;
	TGComboBox *BackModeDrop;
	
	TH1 *raw_input; 
	TH1 *proj,*proj_flow,*selected,*b_man,*specback;
	TH1 *projraw,*proj_flowraw;
	
	TText* peaknumremove;
	
// 	TSpectrum spec;
	
	//	CONTROL VALUES

	int background_mode;
	int backfit_mode;
	int xyz;  
	int axis_down,axis_up;  
	int gate_down,gate_up;
	int gate_range;
	int fit_down,fit_up;
	int m_back_down,m_back_up;
	Long64_t target_bin;
	double backfrack;
	double backfrackfrac;
	bool action_hold; 
	bool set_for_3D;
    int RebinFactor;

	double storef1,storef2;
	
	TGToolTip *fTip;

	//Internal methods
	void NewAxisDrawn();
	void ValidateValues();
	void FetchSliderValues() ;
	void ValuesToSliders();
	void FetchTextValues();
	void ValuesToText();
	void UpdateSpecBack();

	void DoAutoFit();
	void UpdateDraw(bool overlay=false);
	
	string suffix;

    
public:
   j_gating_frame();
   j_gating_frame(TGWindow*,TH1*,string="");
   virtual ~j_gating_frame();
   
   TGVerticalFrame   *fHframe4;
   
   bool hidebinerrors;

   //Functions connected to GUI "slot"
//    void CloseWindow();
	void UpdateCanvas();
   void DoText();
   void DoSlider();
   void SliderRelease();
   void DoSlidePoint();
//    void HandleButtons();
   void ChangeProjection(const Int_t);
   void ChangeBackMode(const Int_t);
   void ChangeBackFit(const Int_t);
   void ReDrawOne();
   void ClickedCanvasOne(Int_t,Int_t,Int_t,TObject*);
   void ShowFullProj();
   void HideFullProj();
   void DoHistogram();
   void TickClick();
      
   TH1 *output_hist_point;
   TH1 *gate_hist,*full,*free_hist;
   
   double GateCentre;
   
   void UpdateInput(TH1*);
   void UpdateInput();
   void UpdateProj(bool=true);
   
   void RebinPlus();
   void RebinMinus();


   //signals has to be public
   void OutputReady(){};  
   void InputChange(){};  
   
   ClassDef(j_gating_frame, 3)
};


class jgating_tool : public TGMainFrame {

private:
	TRootEmbeddedCanvas *fCanvas1;
	j_gating_frame      *gJframe1,*gJframe2;
	TGVerticalFrame     *resultframe,*saveframe;
	TGButtonGroup	*fBgroup1,*savebuttons;
	TGRadioButton	*fRButton1,*fRButton2,*fRButton3;
	TGCheckButton   *fCheck0,*fCheck1;
	TGHSlider    	*fHslider1;
    
    TGTextEntry *RebinText;
    
    TGHorizontalFrame* MainPanels;
    TGVSplitter* splitterB;
    
    TGTextButton* ftbutton;
	
	TF1 *fFitFcn; 
	TText* peaknumremove;   

	static int jgating_tool_iterator;
	string make_iterator();
	TGToolTip *fTip;
	UltraFitEnv* fFitPanel;
    
    TGTransientFrame* MakeTH3Popup();
	
    vector< TH1* > savehists;
	vector< TGCheckButton* > savechecks;
	vector< TGTextButton* > savebutton;
	
	TH1* fInputStore;
    
    double x1,x2,y1,y2;
    
    bool RangeUpdateHold;
    
	void ClearSaved();
	// Have to manually specify nanoseconds, or trunacte manaully to microseconds elsewhere, or mac wont compile due the system clock prevision not matching that which is assumed
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> clicktime;
   
public:
	jgating_tool(const char *);
	jgating_tool(TObject* = hist_capture(),bool=0);
	virtual ~jgating_tool();

	void DoCheckbox2D();
	void DoUpdate2D();
	void DoUpdate();
	void ClickedFinalCanvas(Int_t,Int_t,Int_t,TObject*);
	void SavePanel();
	void FitPanel();
	void jSaveAs();
	void AddStoreHistogram();
	void CSaveButton();
	void StoreHistograms(Int_t);
	void DrawSaved();
	void NewAxisDrawn();
    
    void ProcessedConfigure(Event_t*);
    void ShareMainPanels();
    
	void ResetRange();
    void ButtonGroupDoUpdate(Int_t i);
    
    void Closed(TObject* obj){
        Emit("Closed(TObject*)", (Long_t)obj);
    }

    //Move to the new class asap
	static int Iterator(){jgating_tool_iterator++;return jgating_tool_iterator;};
	static TString Iterator(TString in){return in+=Iterator();};
    
	ClassDef(jgating_tool, 2)
};






class jRootTreeCube : public TGMainFrame {
private:
	jRootMultiPurposePopup *Popup;
	TChain *DataChain;
	unsigned short Symmetrisation;
	TH1* Hist[3];
	vector<TH1*> HistList;
	jGateSelectFrame *SelectFrame;
	TGButtonGroup *fBgroup1;
	int XYZ;
	TH2 *Gate,*Back;
	int gd,gu,bd,bu;
	
	TDataType* SelectedLeafType;
	vector<string> BranchAddresses;
	vector<string> LeafAddresses;
	
	bool TestFileExists(string InputFile);
    void SetBranches();
	void ClearHistList();
	void SymmetriseTH2(TH2* hist);
	void ResetTH1fEntries(TH1* hist);
	void ArrangeInputHistograms();
	
	static int jRootTreeCube_iterator;
	
	template <class T>
	int TypedTTreeSortTTreeReader(TH2* FillHist,unsigned short GateAxis,double GateDown,double GateUp);
		
	template <class T>
	int UnsignedTypedTTreeSortBranchLoop(TH2* FillHist,unsigned short GateAxis,unsigned int GateDown,unsigned int GateUp);

	EDataType GetEDataType(string typestring);
	
	string FillHistNum(){
		stringstream ss;
		ss<<"FillHist"<<jRootTreeCube_iterator;
		jRootTreeCube_iterator++;
		return ss.str();
	}
	
public:	
	jRootTreeCube();
	jRootTreeCube(string InputFile):jRootTreeCube(){
		SetNewInput(InputFile);
	}
	
	~jRootTreeCube(){
		if(DataChain)delete DataChain;
		if(Popup)delete Popup;
		if(Gate)delete Gate;
		if(Back)delete Back;
		ClearHistList();
		Cleanup();
	};
	
    void SetNewInput(string InputFile);
    void AddFile(string InputFile);
	
	void SetSymmetry(bool X,bool Y,bool Z){
		Symmetrisation=0;
		if(X)Symmetrisation+=1;
		if(Y)Symmetrisation+=2;
		if(Z)Symmetrisation+=4;
		
		if(Symmetrisation==1||Symmetrisation==2||Symmetrisation==4){
			cout<<endl<<"Error : Cannot have 1 symmetric axis."<<endl;
			Symmetrisation=0;
		}
	}
	
	void ChangeProjection(Int_t);
	
	TH2* PerformGate(unsigned short GateAxis,int GateDown,int GateUp);
	
	TH1* DoGates();
	void DoGatesDraw();
	void DoGatesGate();
	
	ClassDef(jRootTreeCube, 1)	
};

#endif 
