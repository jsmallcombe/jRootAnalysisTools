//
//
//	jROOT Tools
//	Components of jEnv Toolbar
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
//

#ifndef jameselements_h
#define jameselements_h


#include <TTree.h>
#include <TStopwatch.h>
#include <TGListTree.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>

#include "j_gating_subtraction_frame.h"



//current_capture_frame
class CCframe : public TRootEmbeddedCanvas {
	private:
		static int CCframeIterator;
		
        vector<TClass*> fClass;
        bool fNamed;
		std::vector< TCanvas* > CFriends;
		
		TObject* currentob;//Never owns
		TPad* currentpad;//Never owns
		TCanvas* currentcan;//Never owns
		bool currenttrust;
		TString fName;
		
		void SetNewObject(TObject* fH,TPad* Pad=0,TCanvas* Can=0,bool Trust=0);
		void PrintMessageInternal(TString,TString);
        bool IsA(TObject*);
        TObject* GetA(TPad*);
		
	public:
		CCframe(const TGWindow * p = 0,UInt_t w = 10,UInt_t h = 10,TClass* iClass=TH1::Class());
		~CCframe();
        void SetClass(TClass*);
        void AddClass(TClass*);
		void AddFriend(TCanvas* can){
			if(can)CFriends.push_back(can);
		}
        
		TObject* Object();
		
		TH1* GetHistogram();
		int HistogramType();

		void TrackCaptureHistogram(TPad*,TObject*,Int_t);
        
        void NonGuiNew(TObject*);
		
		void PrintMessage(TString,TString);
	
        void NewObject(){
            Emit("NewObject()");
        }
        void NewObject(TObject* obj){
            Emit("NewObject(TObject*)", (Long_t)obj);
        }
		
	ClassDef(CCframe, 4)
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
   const TGPicture  *fIconTHn;
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
