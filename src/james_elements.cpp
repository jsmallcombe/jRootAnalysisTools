#include "james_elements.h"
CCframe::CCframe(const char * name,const TGWindow* p,UInt_t w,UInt_t h,UInt_t options,Pixel_t back):TRootEmbeddedCanvas(name,p,w,h,options,back),current(0),currentpad(0),currentcan(0){TVirtualPad* hold=gPad;
	this->GetCanvas()->SetMargin(0,0,0,0);
	TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "CCframe", this,"TrackCaptureHistogram(TPad*,TObject*,Int_t)");
	gPad=hold;
    fClass=TH1::Class();
    fNamed=TH1::Class()->InheritsFrom("TNamed");
}

CCframe::~CCframe(){
	TQObject::Disconnect(this);
	TQObject::Disconnect("TCanvas", 0, this);
// 	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureCanvas(TPad*,TObject*,Int_t)");
// 	Disconnect(0,this,0);
// 	TQObject::Disconnect((TCanvas*)this);
}


void CCframe::SetClass(TClass* iClass){
    fClass=iClass;
    fNamed=iClass->InheritsFrom("TNamed");
    this->GetCanvas()->Clear();
    current=0;
    currentpad=0;
    currentcan=0;
}


void CCframe::TrackCaptureHistogram(TPad* pad,TObject* obj,Int_t event){
	//Called by ALL TCanvas
	TCanvas* sender=(TCanvas*)gTQSender;
	
	//To make this ignore certain pads
	for(unsigned int i=0;i<CFriends.size();i++){if(pad==CFriends[i])return;}
	
	
	if(1 == event){//Left Click
		if(this->GetCanvas()==pad){
			//cout<<endl<<"self click"<<endl;
			return;
		}

		if(obj){
			TObject* fH=0;
			if(obj->InheritsFrom(fClass))fH=obj;//If click was exactly on a histogram?
			else fH=obj_capture(fClass,pad);//Else find first object this pad has
// 			else fH=hist_capture(pad);//Else find first histogram this pad has
			
			if(fH)SetNewObject(fH,pad,sender);
			return;
		}
	}
}

void CCframe::SetNewObject(TObject* fH,TPad* Pad,TCanvas* Can){
	if(fH!=current){
		current=fH;
		currentpad=Pad;
		currentcan=Can;
        if(fNamed)fName=current->GetName();
		TVirtualPad* hold=gPad;
		this->GetCanvas()->cd();
        
        //Drawing Options
		if(HType(fH)){
            if(HType(fH)==3){
                this->GetCanvas()->Clear();
                TText t;
                t.SetTextAlign(22);
                t.SetTextSize(.6);
                t.DrawTextNDC(.5,.5,"TH3");
            }else{
                TH1* H=((TH1*)fH)->DrawCopy("COL");
                H->GetXaxis()->SetLabelSize(0);
                H->GetYaxis()->SetLabelSize(0);
                H->SetStats(kFALSE);
            }
		}else if(fH->InheritsFrom("TGraph")){
            gPad->Update();
            ((TGraph*)fH)->DrawClone("al");
        }
		this->GetCanvas()->Modified();
		this->GetCanvas()->Update();
		gPad=hold;
        NewObject();
	}
}

void CCframe::NonGuiNew(TObject* obj){
			if(obj->InheritsFrom(fClass)){
                SetNewObject(obj,0,0);
            }
			return;
}


TH1* CCframe::Hist(){
        if(fClass->InheritsFrom("TH1")){
            return (TH1*)Object();
        }
        return 0;
}
    
    
TObject* CCframe::Object(){
	if(current){
        TObject* Ob;
        if(fNamed&&fName.size()){
            Ob = gROOT->FindObject(fName.c_str());
    // 		cout<<endl<<"Checking if histogram pointer "<<current<<" is valid: "<<Ob<<endl;
            if(Ob)if(Ob->InheritsFrom(fClass))return Ob;
            //Often fails because FindObject has limitations in terms of directories and drawn histograms we might have grabbed.
            //If the canvas is still drawn we might still be able to grab the histogram
        }
		
		TPad* Pad=(TPad*)gROOT->GetListOfCanvases()->FindObject(currentpad);
// 		cout<<endl<<"Checking if pad pointer "<<currentpad<<" is in gROOT->GetListOfCanvases() :"<<Pad<<endl;
		if(Pad){
			Ob=Pad->GetListOfPrimitives()->FindObject(current);
			if(Ob)if(Ob->InheritsFrom(fClass))return Ob;
		}
		
		TCanvas* Can=(TCanvas*)gROOT->GetListOfCanvases()->FindObject(currentcan);
// 		cout<<endl<<"Checking if canvas pointer "<<currentcan<<" is in gROOT->GetListOfCanvases() :"<<Can<<endl;
		if(Can){
			Ob=Can->GetListOfPrimitives()->FindObject(current);
			if(Ob)if(Ob->InheritsFrom(fClass))return Ob;
			
			Pad=(TPad*)Can->GetListOfPrimitives()->FindObject(currentpad);
			if(Pad){
				Ob=Pad->GetListOfPrimitives()->FindObject(current);
				if(Ob)if(Ob->InheritsFrom(fClass))return (TH1*)Ob;
			}
		}
	}
	return 0;
}

int CCframe::Type(){
	return HType(Hist());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

int jAddSubTool::SumNameItt = 0;

jAddSubTool::jAddSubTool(CCframe* Frame,const TGWindow * p):TGCompositeFrame(p,600,400,kVerticalFrame),A(0),B(0),result(0),AHist(0),BHist(0),SumHist(0),fGrabFrame(Frame){
	char buf[32];	//A buffer for processing text through to text boxes
	SetCleanup(kDeepCleanup);
	gSubtract=0;
	
	Stop.Start();
    
		TGHorizontalFrame* ABswap= new TGHorizontalFrame(this);
			A= new TRootEmbeddedCanvas("histholdA",ABswap,100,100);
			A->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jAddSubTool", this,"GrabA(Int_t,Int_t,Int_t,TObject*)");
			TGTextButton* swapB = new TGTextButton(ABswap,"<->");
			swapB->Connect("Clicked()","jAddSubTool",this,"Swap()");	
			B= new TRootEmbeddedCanvas("histholdB",ABswap,100,100);
			B->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jAddSubTool", this,"GrabB(Int_t,Int_t,Int_t,TObject*)");
			ABswap->AddFrame(A);
			ABswap->AddFrame(swapB,new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1));
			ABswap->AddFrame(B);
		this->AddFrame(ABswap,new TGLayoutHints(kLHintsCenterX, 1, 1, 1, 1));
		
		TGHorizontalFrame* FracControl= new TGHorizontalFrame(this);
		
			fTeh1 = new TGTextEntry(FracControl, fTbh1 = new TGTextBuffer(5));//Create some text entry boxes 
			fTeh1->SetToolTipText("Subtraction/Addition Fraction");
			fTeh1->SetDefaultSize(50,25);
			fTeh1->SetAlignment (kTextRight);
			fTeh1->Connect("ReturnPressed()", "jAddSubTool", this,"DoText()");//So it doesnt continually do things while typing is occurrings
			fTeh1->Connect("TabPressed()", "jAddSubTool", this,"DoText()");
			sprintf(buf, "%.1f", 0.0);fTbh1->AddText(0, buf);
			FracControl->AddFrame(fTeh1);
			
			addsubclick = new TGTextButton(FracControl,"     Add/Sub     ");
			addsubclick->Connect("Clicked()","jAddSubTool",this,"AddSubButton()");
			FracControl->AddFrame(addsubclick);
			
			fCheck1 = new TGCheckButton(FracControl,"Hide Ers");
			fCheck1->SetState(kButtonDown);
			fCheck1->Connect(" Clicked()", "jAddSubTool", this,"DoSlider()");
			fCheck1->SetToolTipText("Hide Bin Errors on drawn histograms");
			FracControl->AddFrame(fCheck1);
		
		this->AddFrame(FracControl,new TGLayoutHints(kLHintsCenterX, 2, 2, 2, 2));
        
		TGHorizontalFrame* FracSlider= new TGHorizontalFrame(this);
			fHslider1 = new TGHSlider(FracSlider,1000, kSlider2);
			fHslider1->Connect("PositionChanged(Int_t)", "jAddSubTool", this, "DoSlider()");
			fHslider1->SetRange(-500,500);
			fHslider1->SetPosition(0);
			FracSlider->AddFrame(fHslider1,new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 1));
		this->AddFrame(FracSlider,new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 1));
		
		result= new TRootEmbeddedCanvas("histaddres",this,600,400);
		result->GetCanvas()->SetMargin(0.12,0.04,0.12,0.05);
		
		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ClickPeakDrawConnect(Int_t,Int_t,Int_t,TObject*)");
		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ToolTipHide()");//added because this embedded canvas put tooltip at wrong coordinates on screen
		
		this->AddFrame(result,new TGLayoutHints(kLHintsExpandY|kLHintsExpandX, 1, 1, 1, 1));
	
// 	result->Resize(600,400);
// 	MapSubwindows();
// 	Resize(GetDefaultSize());
// 	MapWindow();

	fGrabFrame->CFriends.push_back(A->GetCanvas());
	fGrabFrame->CFriends.push_back(B->GetCanvas());
    
	A->GetCanvas()->SetMargin(0,0,0,0);
	B->GetCanvas()->SetMargin(0,0,0,0);
}


void jAddSubTool::GrabA(Int_t c,Int_t a,Int_t b,TObject* d){if(c==1)Grab(0);}
void jAddSubTool::GrabB(Int_t c,Int_t a,Int_t b,TObject* d){if(c==1)Grab(1);}
void jAddSubTool::Grab(int i){
	TH1** H=&AHist;string S="AddSubHoldHistA";
	if(i){H=&BHist;S="AddSubHoldHistB";}
	if(fGrabFrame->Type()<3){
		if(*H)delete *H;
		*H=(TH1*)fGrabFrame->Hist()->Clone(S.c_str());
		DrawAB(i);
		if(SumHist){delete SumHist;SumHist=0;SumNameItt++;}
		DoSlider();
	}
}

void jAddSubTool::DrawAB(int i){
	TVirtualPad* hold=gPad;
	TH1* H=AHist;TCanvas* Can=A->GetCanvas();
	if(i){
        H=BHist;Can=B->GetCanvas();
    }else{
        Abinwidth=H->GetXaxis()->GetBinWidth(1);
    }
	if(H){
		Can->cd();
		H->GetXaxis()->SetLabelSize(0);
		H->GetYaxis()->SetLabelSize(0);
		H->SetStats(kFALSE);
		H->DrawCopy("histcol");
	}else{
		Can->Clear();
	}
	Can->Modified();
	Can->Update();
	gPad=hold;
}

void jAddSubTool::Swap(){
	TH1* H=AHist;
	AHist=BHist;
	BHist=H;
	DrawAB(0);
	DrawAB(1);
	if(SumHist){delete SumHist;SumHist=0;SumNameItt++;}
	DoSlider();
}


void jAddSubTool::DoSlider(){
    int slidepos=fHslider1->GetPosition();
	double frac=slidepos/500.0;
	double fracfrac=0.03;//Arbitrary summing fraction error 
	
	UpdateText();
	
	if(AHist&&BHist){
		int Type=HType(AHist);
		if(Type==HType(BHist)){
            
			if(Type==2){
                if(gSubtract>1){
                    gSubtract=-1;
                    AddSubButton();
                    return;
                }
                
				if(Stop.RealTime()<4){
// 					cout<<endl<<"NO TIME "<<Stop.CpuTime()<<endl;
					Stop.Start(kFALSE);	
					return;
				}
// 				cout<<endl<<"GOOD TIME"<<endl;
				Stop.Start();
			}
			
			int rmin=1;
			int rmax=-1;
			
			//Check the 2 ranges
			double AXt=AHist->GetXaxis()->GetXmax();
			double AXb=AHist->GetXaxis()->GetXmin();
			double BXt=BHist->GetXaxis()->GetXmax();
			double BXb=BHist->GetXaxis()->GetXmin();
			double ranges=(AXt-AXb)/(BXt-BXb);
			if(AXt<BXb||BXt<AXb)return;
				
			TH1* back=BHist;
			bool backtmp=false;
			
			//Get the B hist in the right form
			if((AHist->GetNbinsX()!=BHist->GetNbinsX())||
			(ranges<0.999)||(ranges>1.001)){
				if(Type==2)return;
				back=(TH1*)AHist->Clone();
				back->Reset();
				ExtreemRebin(back,BHist);
				backtmp=true;
			}
			
			if(Type==2){
				AXt=AHist->GetYaxis()->GetXmax();
				AXb=AHist->GetYaxis()->GetXmin();
				BXt=BHist->GetYaxis()->GetXmax();
				BXb=BHist->GetYaxis()->GetXmin();
				ranges=(AXt-AXb)/(BXt-BXb);
				if((AXt<BXb||BXt<AXb)||(AHist->GetNbinsY()!=BHist->GetNbinsY())||
				(ranges<0.999)||(ranges>1.001)){
					return;
				}
			}
			
			
			//Delete the previous result and get axis info
			if(SumHist){
				rmin=SumHist->GetXaxis()->GetFirst();
				rmax=SumHist->GetXaxis()->GetLast();
				delete SumHist;SumHist=0;
			}
			
			//Do add/subtraction
			
            switch(gSubtract) {
                case 1 :    SumHist=scaled_addition(AHist,back,frac,fracfrac);
                            //SumHist=scaled_back_subtract(AHist,back,frac,-fracfrac);
                            break;
                case 2 :    SumHist=(TH1*)back->Clone();
                            SumHist->Scale((frac+1)*AHist->Integral()/back->Integral());
                            break;
                case 3 :    SumHist=(TH1*)back->Clone();
                            transpose_bins(SumHist,slidepos);
                            break;
                default :   SumHist=(TH1*)AHist->Clone();
                            SumHist->Add(back,frac);   
                            break;
            }
			stringstream ss;ss<<"AddSubResultHist"<<SumNameItt;
			SumHist->SetName(ss.str().c_str());

			if(backtmp)delete back;
			
			//Draw new results with and adjust axis
			TVirtualPad* hold=gPad;
			result->GetCanvas()->cd();
                
                if(gSubtract>1){
                    TH1* H;
                    if(fCheck1->GetState())H=AHist->DrawCopy("hist");else   H=AHist->DrawCopy(""); 
                    hformat(H,0); 
                    if(rmax>rmin)H->GetXaxis()->SetRange(rmin,rmax);
                    if(rmax>rmin)SumHist->GetXaxis()->SetRange(rmin,rmax);
                    
                    SumHist->SetLineColor(2);
                    if(fCheck1->GetState())SumHist->Draw("histsame");else SumHist->Draw("same");
                }else{
                    hformat(SumHist,0);
                    if(rmax>rmin)SumHist->GetXaxis()->SetRange(rmin,rmax);
                    if(fCheck1->GetState())SumHist->Draw("hiscol");else SumHist->Draw("col"); 
                }
                
                
// 			if(rmax>rmin)SumHist->GetXaxis()->SetRange(rmin,rmax);
//             hformat(SumHist,0);
//             if(fCheck1->GetState())SumHist->Draw("hiscol");else SumHist->Draw("col");
//             if(gSubtract>1){
//                 if(fCheck1->GetState())AHist->Draw("histsame");else AHist->Draw("same");  
//                 SumHist->SetLineColor(2);
//             }
            
			result->GetCanvas()->Modified();
			result->GetCanvas()->Update();
			gPad=hold;
		}else{
			result->GetCanvas()->Clear();
		}
	}else{
		result->GetCanvas()->Clear();
	}
}

void jAddSubTool::DoText(){
	double backfrack=atof(fTbh1->GetString());
    
    if(gSubtract==3){
        backfrack/=Abinwidth;
    }else{
        backfrack*=500;
    }
    
	fHslider1->SetPosition(backfrack);
	DoSlider();
}
	
void jAddSubTool::UpdateText(){
	char buf[32];
	//update the text now the sliders have moved
    
    
    if(gSubtract==3){
        int s=floor(log10(Abinwidth)); if(s>0)s=0;
        stringstream format;
        format<<"%."<<abs(s)<<"f";
        sprintf(buf, format.str().c_str(), fHslider1->GetPosition()*Abinwidth);
    }else{
        sprintf(buf, "%.3f", fHslider1->GetPosition()/500.0);
    }  
    
	fTbh1->Clear();	fTbh1->AddText(0, buf);
	fTeh1->SetCursorPosition(fTeh1->GetCursorPosition());fTeh1->Deselect();
	gClient->NeedRedraw(fTeh1);

}

void jAddSubTool::AddSubButton(){
	gSubtract++;
    
	if(gSubtract>3)gSubtract=0;
    
    switch(gSubtract) {
    case 0 : addsubclick->SetText("   Add/Sub   ");
             break;       
    case 1 : addsubclick->SetText("Scale Add/Sub");
             break;
    case 2 : addsubclick->SetText("Scale Compare");
             break;
    case 3 : addsubclick->SetText("Shift Compare");
             break;
    }

	fHslider1->SetPosition(0);
	gClient->NeedRedraw(addsubclick);
	DoSlider();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

jDirList::jDirList(const TGWindow *p, const TGWindow *main,
                         UInt_t w, UInt_t h)
{
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
//                         if(env){
//                             env->NonGuiNew(key->ReadObj());
//                         }
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


