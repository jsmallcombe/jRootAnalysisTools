//
//
//	James Root Library
//	Tool panel and helper enviroment for GUI working in root
//	05 Feb 2019
//	james.smallcombe@outlook.com
//
//

#ifndef jamesenvmore_h
#define jamesenvmore_h

#include <iostream>

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TGListTree.h"
#include "TSystemFile.h"
#include "TSystemDirectory.h"

#include "james_env.h"
#include "james_utility.h"

using namespace std;


class jDirList {
    
    // Modified from example guitest.C
    
protected:
   TGTransientFrame *fMain;
   TGListTree       *fContents;
   const TGPicture  *fIcon;
   const TGPicture  *fIconH1;
   const TGPicture  *fIconH2;
   const TGPicture  *fIconH3;
   TList RootFileList;
   
   TString DirName(TGListTreeItem* item);

public:
   jDirList(const TGWindow *p, const TGWindow *main, UInt_t w, UInt_t h);
   virtual ~jDirList();

   // slots
   void OnDoubleClick(TGListTreeItem* item, Int_t btn);
   void CloseWindow();
   
   jEnv* env;
   
private:
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
