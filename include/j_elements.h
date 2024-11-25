//
//
//	jROOT Tools
//	Tool panel and helper enviroment for GUI working in root
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef jameselements_h
#define jameselements_h

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
#include <TStopwatch.h>
#include <TGListTree.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>
#include <TGSlider.h>
#include <TGTextEntry.h>
#include <TKey.h>


#include "j_utility.h"
#include "j_gpad_tools.h"
#include "j_hist_formatting.h"
#include "j_gate_subtract.h"

using namespace std;

//current_capture_frame
class CCframe : public TRootEmbeddedCanvas {
	private:
		TObject* current;//Never owns
		TPad* currentpad;//Never owns
		TCanvas* currentcan;//Never owns
		
		bool currenttrust;
		string fName;
		void SetNewObject(TObject* fH,TPad* Pad=0,TCanvas* Can=0,bool Trust=0);
		bool pause;
        TClass *fClass;
        bool fNamed;
        
	public:
		CCframe(const char * name = 0,const TGWindow * p = 0,UInt_t w = 10,UInt_t h = 10,UInt_t options = kSunkenFrame | kDoubleBorder,Pixel_t 	back = GetDefaultFrameBackground());
		~CCframe();
        void SetClass(TClass*);
        
		TH1* Hist();
		TObject* Object();
		
		int Type();

		void TrackCaptureHistogram(TPad*,TObject*,Int_t);
        
        void NonGuiNew(TObject* obj);
	
		std::vector< TCanvas* > CFriends;
        
        void NewObject(){
            Emit("NewObject()");
        }
        void NewObject(TObject* obj){
            Emit("NewObject(TObject*)", (Long_t)obj);
        }
		
	ClassDef(CCframe, 2)
};

////////////////////////////////////////////////////////////////

class jHistCapButton : public TGTextButton {

public:
	jHistCapButton(const TGWindow *p, const char *s, const char *cmd, Int_t id=-1, GContext_t norm=GetDefaultGC()(), FontStruct_t font=GetDefaultFontStruct(), UInt_t option=kRaisedFrame|kDoubleBorder):
	TGTextButton(p,s,cmd,id,norm,font,option){};
 
 	jHistCapButton(const TGWindow *p, TGHotString *s, Int_t id=-1, GContext_t norm=GetDefaultGC()(), FontStruct_t font=GetDefaultFontStruct(), UInt_t option=kRaisedFrame|kDoubleBorder):
	TGTextButton(p,s,id,norm,font,option){};

 	jHistCapButton(const TGWindow *p=0, const char *s=0, Int_t id=-1, GContext_t norm=GetDefaultGC()(), FontStruct_t font=GetDefaultFontStruct(), UInt_t option=kRaisedFrame|kDoubleBorder):
	TGTextButton(p,s,id,norm,font,option){};
    
    ~jHistCapButton(){TQObject::Disconnect(this);};
    
public:
    
    void Clicked();
    void CaptureHistogram(TPad* pad,TObject* obj,Int_t event);
    void NewHist(TH1* h){
            Emit("NewHist(TH1*)", (Long_t)h);
    }
    
	ClassDef(jHistCapButton, 0)
};


////////////////////////////////////////////////////////////////

//My little add sub tool
class jAddSubTool : public TGCompositeFrame {
	private:
	TStopwatch Stop;
	TRootEmbeddedCanvas *A,*B,*result;
	TH1* AHist,*BHist,*BSet,*SumHist,*DrawHist;//Always owned and private
	bool TempB;
	TGHSlider* fHslider1;
	TGTextEntry* fTeh1;
	TGCheckButton* fCheck1;
	TGTextBuffer  *fTbh1;
	int gSubtract;
	TGTextButton* addsubclick;
	static int SumNameItt;
    CCframe* fGrabFrame;
	
	void Grab(int);
	void DrawAB(int);
	void PrepareB();
	void UpdateText();
    double Abinwidth;
    
public:
		jAddSubTool(CCframe* Frame,const TGWindow * p = 0, UInt_t w=600, UInt_t h=400, UInt_t options=kVerticalFrame);
        
		~jAddSubTool(){
            DrawHist=0;
            if(AHist){delete AHist;}
            if(BHist){delete BHist;}
            if(BSet&&TempB){delete BSet;}
            if(SumHist){delete SumHist;}
        };
        
	void Swap();
	void GrabA(Int_t,Int_t,Int_t,TObject*);
	void GrabB(Int_t,Int_t,Int_t,TObject*);
	void DoSlider();
	void DoText();
	void AddSubButton();
		
	ClassDef(jAddSubTool,1)
};



class jDirList: public TGCompositeFrame {
    
    // Modified from example guitest.C
    
   //RQ_OBJECT("jDirList")
   // if jDirList not inherited from TQObject, allows class to use signal/slot communication
    
protected:
   TGListTree       *fContents;
   const TGPicture  *fIcon;
   const TGPicture  *fIconH1;
   const TGPicture  *fIconH2;
   const TGPicture  *fIconH3;
   const TGPicture  *fIconGr;
   const TGPicture  *fIconMGr;
   const TGPicture  *fIconTF;
   const TGPicture  *fIconCan;
   const TGPicture  *fIconTree;
   TList RootFileList;
   
   TString DirName(TGListTreeItem* item);

public:
   jDirList(const TGWindow* p, UInt_t w=200, UInt_t h=400, UInt_t options=kVerticalFrame);
   virtual ~jDirList();

   // slots
   void OnDoubleClick(TGListTreeItem* item, Int_t btn);
   void CloseWindow();
   void NewObject(TObject*);
   
    void Closed(TObject* obj){
        Emit("Closed(TObject*)", (Long_t)obj);
    }
   
    bool FindAndOpen(TString fname);
    
private:
    void OpenClose(TGListTreeItem* item);
    void UseItem(TGListTreeItem* item);
    void ProcessSystemDir(TList *files,TGListTreeItem* item);
    TFile* GetRootFile(TGListTreeItem*);
    TKey* GetKey(TGListTreeItem*);
    TDirectory* GetDirectory(TGListTreeItem*);
    TString GetInternal(TGListTreeItem*);
    TObject* GetObject(TGListTreeItem*);
    void AddTDir(TGListTreeItem* item, TDirectory* dir);
    void ProcessRootFileObject(TGListTreeItem* item);
    
public:
	ClassDef(jDirList, 1)
    
};

#endif
