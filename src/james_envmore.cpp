#include "james_envmore.h"




jDirList::jDirList(const TGWindow *p, const TGWindow *main,
                         UInt_t w, UInt_t h)
{
    env=0;
   // Create transient frame containing a dirlist widget.

   fMain = new TGTransientFrame(p, main, w, h);
   fMain->Connect("CloseWindow()", "jDirList", this, "CloseWindow()");
   fMain->DontCallClose(); // to avoid double deletions.

   fIcon = gClient->GetPicture("rootdb_t.xpm");
   fIconH1 = gClient->GetPicture("h1_t.xpm");
   fIconH2 = gClient->GetPicture("h2_t.xpm");
   fIconH3 = gClient->GetPicture("h3_t.xpm");
   TGLayoutHints *lo;

   // use hierarchical cleaning
   fMain->SetCleanup(kDeepCleanup);

   TGCanvas* canvas = new TGCanvas(fMain, 500, 300);
   fContents = new TGListTree(canvas, kHorizontalFrame);
   lo = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsBottom);
   fMain->AddFrame(canvas,lo);
   fContents->Connect("DoubleClicked(TGListTreeItem*,Int_t)","jDirList",this,
                      "OnDoubleClick(TGListTreeItem*,Int_t)");
   fContents->Connect("Clicked(TGListTreeItem*,Int_t)","jDirList",this,
                      "OnDoubleClick(TGListTreeItem*,Int_t)");
#ifdef G__WIN32
   fContents->AddItem(0,"c:\\");  // browse the upper directory
#else
   fContents->AddItem(0,"/");  // browse the upper directory
   TGListTreeItem* CurDir=fContents->AddItem(0,gSystem->pwd());  // Add the current directory
   UseItem(CurDir);//Load the current directory
   fContents->OpenItem(CurDir);//Open the current directory
#endif

   // position relative to the parent's window
   fMain->CenterOnParent();

   fMain->SetWindowName("List Dir Test");

   fMain->MapSubwindows();
   fMain->Resize();
   fMain->MapWindow();
}

jDirList::~jDirList()
{
   // Cleanup.

   gClient->FreePicture(fIcon);
   delete fContents;
   fMain->DeleteWindow();  // delete fMain
}

void jDirList::CloseWindow()
{
   delete this;
}

TString jDirList::DirName(TGListTreeItem* item)
{
   // Returns an absolute path.

   TGListTreeItem* parent;
   TString dirname = item->GetText();

   while ((parent=item->GetParent())) {
      dirname = gSystem->ConcatFileName(parent->GetText(),dirname);
      item = parent;
   }

   return dirname;
}

void jDirList::OnDoubleClick(TGListTreeItem* item, Int_t btn){
    
    //GetUserData Set if directory already processed
    if ((btn!=kButton1) || !item || (Bool_t)item->GetUserData()) return;
                 
    UseItem(item);
}


void jDirList::UseItem(TGListTreeItem* item){
   TSystemDirectory dir(item->GetText(),DirName(item));
   TList *files = dir.GetListOfFiles();
   
   // If system dir files will exist
   if (files) {
        ProcessSystemDir(files,item);
        return;
   }

   // Should have dealt with any real system directory
   // So anything beyond here should be TDirectory structure
    ProcessRootFileObject(item);
   
}

void jDirList::ProcessSystemDir(TList *files,TGListTreeItem* item){
    // Show Directory Contents
    if (files) {
      TIter next(files);
      TSystemFile *file;
      TString fname;

      while ((file=(TSystemFile*)next())) {
         fname = file->GetName();
         if (file->IsDirectory()) {
            if ((fname!="..") && (fname!=".")) { // skip it
               fContents->AddItem(item,fname);
            }
         } else if (fname.EndsWith(".root")) {   // add root files
            fContents->AddItem(item,fname,fIcon,fIcon);
         }
      }
      delete files;

        // use UserData to indicate that item was already browsed
        item->SetUserData((void*)1);
   }
   return;
}

    
void jDirList::AddTDir(TGListTreeItem* item, TDirectory* dir){
//     TDirectory *dirsav = gDirectory;
        TIter next(dir->GetListOfKeys());
        TKey *key;
        while ((key = (TKey*)next())) {
            if (key->IsFolder()) {
               fContents->AddItem(item,key->GetName());
               continue;
            }
            
        switch(HistoClassDetect(key->GetClassName())) {
                case 1 :
                    fContents->AddItem(item,key->GetName(),fIconH1,fIconH1);
                    break;
                case 2 :
                    fContents->AddItem(item,key->GetName(),fIconH2,fIconH2);
                    break;
                case 3 :
                    fContents->AddItem(item,key->GetName(),fIconH3,fIconH3);
                    break;
                default :
                    continue;
            }
        }
        
    item->SetUserData((void*)1);
    return;
}
    
void jDirList::ProcessRootFileObject(TGListTreeItem* item){
        //Either TDir or TObject
   
    TString TSitem(item->GetText());

    //If its an unopend root file  (only reached here if unopend)
    if(TSitem.EndsWith(".root")){
            TFile* Rfile=new TFile(DirName(item),"READ");
            if(!Rfile->IsOpen())return;
            
            RootFileList.Add(Rfile);
            AddTDir(item,Rfile);
            
            return;
    }
    
//     cout<<endl<<"Object "<<GetObject(item);
    TKey *key=GetKey(item);
//     cout<<endl<<"key "<<key;
    
    if(key){
            if (key->IsFolder()) {
            AddTDir(item,(TDirectory*)key->ReadObj());
            return;
        }else{
            switch(HistoClassDetect(key->GetClassName())) {
                    case 1 :
                        if(env){
                            env->NonGuiNew(key->ReadObj());
                        }
                        new TCanvas();
                        ((TH1*)key->ReadObj())->Draw();
                        break;
                    case 2 :
//                         new jgating_tool(key->ReadObj());
                        break;
                    case 3 :
//                         new jgating_tool(key->ReadObj());
                        break;
                    default :
                        break;
                }
        }
    }   
}

TFile* jDirList::GetRootFile(TGListTreeItem* item){
    TGListTreeItem* searchitem=item;
    while(searchitem->GetParent()){
        searchitem=searchitem->GetParent();
         TString TSitem(searchitem->GetText());
         if(TSitem.EndsWith(".root")){
             return (TFile*)RootFileList.FindObject(DirName(searchitem));
        }
    }
    return 0;
}


TKey* jDirList::GetKey(TGListTreeItem* item){
    TDirectory* Dir=GetDirectory(item);
    if(Dir){
        return Dir->GetKey(item->GetText());
    }
    
    return 0;
}


TDirectory* jDirList::GetDirectory(TGListTreeItem* item){
    TFile *Rfile=GetRootFile(item);
    if(Rfile){
        vector<TString> folderpath;

        TGListTreeItem* searchitem=item;
        while(searchitem->GetParent()){
            searchitem=searchitem->GetParent();
            TString TSitem(searchitem->GetText());
            if(TSitem.EndsWith(".root")){
                break;
            }
            folderpath.push_back(TSitem);
        }
        
        TDirectory* CurrentDir=(TDirectory*)Rfile;
        
        for(int i=folderpath.size()-1;i>=0;i--){
            TDirectory* next = (TDirectory*)CurrentDir->Get(folderpath[i]);
            if(next){
                CurrentDir=next;
            }else{
                return 0;
            }
        }
        
         // CurrentDir should now be item's parent
         return CurrentDir;
    }
    return 0;
}

TString jDirList::GetInternal(TGListTreeItem* item){
    TFile *Rfile=GetRootFile(item);
    if(Rfile){
            TString filepath=Rfile->GetName();
            TString itemname=DirName(item);
            TString insidepath( itemname(filepath.Length()+1,itemname.Length()) );
            return insidepath;
    }
    return TString();
}

TObject* jDirList::GetObject(TGListTreeItem* item){
    TFile *Rfile=GetRootFile(item);
    if(Rfile){
        return Rfile->Get(GetInternal(item));
    }
    return 0;
}


