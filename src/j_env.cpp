#include "j_env.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////

FontStruct_t jEnv::GetFont(){
    TGFontPool *pool = gClient->GetFontPool();
    // family , size (minus value - in pixels, positive value - in points), weight, slant
    //  kFontWeightNormal,  kFontSlantRoman are defined in TGFont.h
    TGFont *font = pool->GetFont("helvetica", 12,  kFontWeightBold,  kFontSlantRoman);
    FontStruct_t ft = TGTextButton::GetDefaultFontStruct();
//     GContext_t gc=TGButton::GetDefaultGC()();
    if(font){
        ft = font->GetFontStruct();
    }
    return ft;
}


jEnv::jEnv() : TGMainFrame(gClient->GetRoot(), 1, 1,kHorizontalFrame),
    fFitPanel(0),fSpecTool(0),addsub(0),DirList(0),SameSave(0),gDrawSame(false),fTabs(0),
    fPixOffX(1),fPixOffY(33),
    fDefaultDirWidth(280),fDefaultDirHeight(400),
    fDefaultTabsWidth(1000),fDefaultTabsHeight(650),
    fDefaultGrabSize(140),Alternator(0)
{

    FontStruct_t ft =GetFont();
    
TVirtualPad* hold=gPad;
	SetWindowName("jEnv");
    
	SetCleanup(kDeepCleanup);

	TGLayoutHints* ExpandX= new TGLayoutHints(kLHintsExpandX,5,5,3,2);

    DirList=new jDirList(this);
    this->AddFrame(DirList,new TGLayoutHints(kLHintsExpandY,4,4,4,4));
    
	TGVerticalFrame* controlframe1 = new TGVerticalFrame(this);
        //// jBrowser show/hide
		TGTextButton* jbrowser = new TGTextButton(controlframe1,"< jBrowser");
        jbrowser->SetFont(ft);
		jbrowser->Connect("Clicked()","jEnv",this,"ShowHideDir()");
		controlframe1->AddFrame(jbrowser,ExpandX);
        
        ////// Click Grab Window
		fCanvas1 = new CCframe(controlframe1, fDefaultGrabSize, fDefaultGrabSize);//Default grab class TH1*
        fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jEnv", 0,"Clipboard(Int_t,Int_t,Int_t,TObject*)");
		controlframe1->AddFrame(fCanvas1);
		
        //// Fit Panel Buttons
        TGHorizontalFrame* drawduelbuttons = new TGHorizontalFrame(controlframe1);            
            TGTextButton* fitter = new TGTextButton(drawduelbuttons,"Fit Panel");
            fitter->SetFont(ft);
            fitter->Connect("Clicked()","jEnv",this,"FitPanel()");	
            drawduelbuttons->AddFrame(fitter,ExpandX);
			TGPictureButton *fPictureBut = new TGPictureButton(drawduelbuttons,gClient->GetPicture("newcanvas.xpm"));
            fPictureBut->SetMinWidth(30);
            fPictureBut->SetWidth(35);
			fPictureBut->Connect("Clicked()","jEnv",this,"FreeFitPanel()");
			drawduelbuttons->AddFrame(fPictureBut,new TGLayoutHints(kLHintsExpandY,0,5,3,2));
		controlframe1->AddFrame(drawduelbuttons,new TGLayoutHints(kLHintsExpandX,0,0,0,0));
        OneOnly.push_back(fitter);

        ///// Spec Tool Buttons
		TGTextButton* Spect = new TGTextButton(controlframe1,"SpecTool");
            Spect->SetFont(ft);
            Spect->Connect("Clicked()","jEnv",this,"Spectrum()");
		controlframe1->AddFrame(Spect,ExpandX);    
        OneOnly.push_back(Spect);
        
        //// Draw Buttons
		drawduelbuttons = new TGHorizontalFrame(controlframe1);
			TGTextButton* Drawer = new TGTextButton(drawduelbuttons," Draw ");
            Drawer->SetFont(ft);
			Drawer->Connect("Clicked()","jEnv",this,"DrawCpyTab()");
			drawduelbuttons->AddFrame(Drawer,ExpandX);
			fPictureBut = new TGPictureButton(drawduelbuttons,gClient->GetPicture("newcanvas.xpm"));
            fPictureBut->SetMinWidth(30);
            fPictureBut->SetWidth(35);
			fPictureBut->Connect("Clicked()","jEnv",this,"DrawCpy()");
			drawduelbuttons->AddFrame(fPictureBut,new TGLayoutHints(kLHintsExpandY,0,5,3,2));
		controlframe1->AddFrame(drawduelbuttons,new TGLayoutHints(kLHintsExpandX,0,0,0,0));
		
        //// Drawsame Button
		TGTextButton* Drawsm = new TGTextButton(controlframe1,"DrawSame");
        Drawsm->SetFont(ft);
		Drawsm->Connect("Clicked()","jEnv",this,"DrawSm()");
		controlframe1->AddFrame(Drawsm,ExpandX);     
        OneOnly.push_back(Drawsm);  
        
        //// Gating tool button
		TGTextButton* gatter = new TGTextButton(controlframe1,"Gate");
        gatter->SetFont(ft);
		gatter->Connect("Clicked()","jEnv",this,"Gatter()");	
		controlframe1->AddFrame(gatter,ExpandX);
        OneNotly.push_back(gatter);

        //// SaveAs Button
		TGTextButton* Saver = new TGTextButton(controlframe1,"SaveAs");
        Saver->SetFont(ft);
		Saver->Connect("Clicked()","jEnv",this,"jSaveAs()");
		controlframe1->AddFrame(Saver,ExpandX);
        
        //// TBrowser Button
		TGTextButton* tbrowser = new TGTextButton(controlframe1,"TBrowser");
        tbrowser->SetFont(ft);
		tbrowser->Connect("Clicked()","jEnv",this,"Browser()");
		controlframe1->AddFrame(tbrowser,ExpandX);
        
        //// Close and Exit Buttons
		TGTextButton* close = new TGTextButton(controlframe1,"Close");
        close->SetFont(ft);
		close->Connect("Clicked()","jEnv",this,"DeleteWindow()");
		controlframe1->AddFrame(close,ExpandX);
// 		TGTextButton* exit = new TGTextButton(controlframe1,"Exit","gApplication->Terminate(0)");
		TGTextButton* exit = new TGTextButton(controlframe1,"Exit");
		exit->Connect("Clicked()","jEnv",this,"Terminate()");
        exit->SetFont(ft);
        controlframe1->AddFrame(exit,ExpandX);
        
    this->AddFrame(controlframe1);
    
	TGTextButton* expandB = new TGTextButton(this,">");
        expandB->Connect("Clicked()","jEnv",this,"ShowHideTabs()");	
	this->AddFrame(expandB,new TGLayoutHints(kLHintsExpandY, 1, 1, 1, 1));

    fTabs = new TGTab(this, fDefaultTabsWidth, fDefaultTabsHeight);  
    fTabs->Connect("CloseTab(Int_t)", "jEnv", this, "CloseTab(Int_t)");
	this->AddFrame(fTabs, new TGLayoutHints(kLHintsExpandY|kLHintsExpandX, 1, 1, 1, 1));
    
    addsub = new jAddSubTool(fCanvas1,fTabs);
    fTabs->AddTab("Add/Sub",addsub);

	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();

	HideTabs();
	HideDir();
    
////////  Not sure why this was needed, seems to be working without it
//     Move(70+fDefaultDirWidth,70);
//     SetWMPosition(70+fDefaultDirWidth, 70);	
    
// #if __APPLE__
// #elif __linux__
//     ////////  Not sure why this was needed, seems to be working without it
//     ///////
//     // An extra small offset due to window bar
//     // There is probably a more sophisticated way of dealing with this 
// //     Window_t wdummy;
// //     gVirtualX->TranslateCoordinates(GetId(),GetParent()->GetId(),0,0,fPixOffX,fPixOffY,wdummy);
// //     if(!fPixOffY)fPixOffY=33;
// #endif

    //// Connect the various TObject grabbing systems
    //// When (jDirList)DirList has a new selection, this is passed to the (CCframe)fCanvas1 to update it's graphics and reference
    //// (CCframe)fCanvas1 will pass to (jEnv)this when it has a VALID new object EITHER from CCframe or from TCanvas
	//// (CCframe)fCanvas1 is set to only accept TH1 Inheriting objects
    //// (jDirList)DirList also passed directly to the (jEnv), to allow for objects types outside the scope of (CCframe)fCanvas1
	//// jEnv::NewDirObject should NOT parse objects directly if they are valid for the current (CCframe)fCanvas1 instance (e.g. histograms)
    DirList->Connect("NewObject(TObject*)","CCframe",fCanvas1,"NonGuiNew(TObject*)");
    DirList->Connect("NewObject(TObject*)","jEnv",this,"NewDirObject(TObject*)");
    fCanvas1->Connect("NewObject(TObject*)","jEnv",this,"NewCanvasObject(TObject*)");
    
// 	Connect("CloseWindow()","jEnv",this,"~jEnv()");
	Connect("CloseWindow()","jEnv",this,"DontCallClose()");

    if(gFile){
        if(((jDirList*)DirList)->FindAndOpen(gFile->GetName()))ShowDir();
    }
    
gPad=hold;
}


// The button to exit the root session is clicked
void jEnv::Terminate(){
    FreeObjects.SetOwner();// Will delete list objects irrespective of kCanDelete
    delete this;
    gApplication->Terminate(0);
}


void jEnv::ClearFreeObjects(){
    // Disconnected signals from FreeObjects
	// Objects in list will be deleted along with jEnv depenendent on individual kCanDelete values
    
    TObject *obj;
    TIter next(&FreeObjects);
    while((obj= next())){
        if(obj->InheritsFrom("TQObject")){
			if (auto qobj = dynamic_cast<TQObject*>(obj)) {
				qobj->Disconnect(0, this, 0);
			}
        }
    }
    
//     FreeObjects.Clear("nodelete");
}

void jEnv::AddFreeObject(TObject* obj,bool CanDelete){

    // The dynamic cast is crucial here apparently 
	if (auto qobj = dynamic_cast<TQObject*>(obj)) {
		qobj->Connect("Closed(TObject*)","jEnv", this,"ClosedObject(TObject*)");
		// This would link ALL of the class
		// TQObject::Connect(qobj->ClassName(),"Closed(TObject*)","jEnv", this,"ClosedObject(TObject*)");
	}
    
    // Sets if it is allowed to be deleted by TLists it is added to
    if(CanDelete)obj->SetBit(kCanDelete,kTRUE);
    else obj->SetBit(kCanDelete,kFALSE);
    
    FreeObjects.Add(obj);
}

void jEnv::Browser(){
	new TBrowser();
	if(fCanvas1->HistogramType()>0&&fCanvas1->HistogramType()<3){
		// Will have moved into the TCanvas of the TBrowser at creation time
		fCanvas1->GetHistogram()->DrawCopy("colz");
	}
}

void jEnv::FitPanel(){
    if(fCanvas1->HistogramType()==1){ //If valid TH1 input
        if(fFitPanel){ //If we already initialised fFitPanel
            fFitPanel->PassNewHist(fCanvas1->GetHistogram());
            for(int i=0;i<fTabs->GetNumberOfTabs();i++){
				if(fFitPanel==fTabs->GetTabContainer(i)){fTabs->SetTab(i,kFALSE);break;}// Switch to the fFitPanel tab, dont "emit"
			}
            if(!IsVisible(fTabs))ShowTabs();// Open the tabs pane if they are minimised
		}else {
            fFitPanel=new UltraFitEnv(fTabs,fCanvas1->GetHistogram(),0,1);
            fTabs->AddTab("FitPanel",fFitPanel);
            fTabs->SetTab(fTabs->GetNumberOfTabs()-1,kFALSE); 
            ShowTabs();
		}
	}
};

void jEnv::FreeFitPanel(){
        if(fCanvas1->HistogramType()==1)AddFreeObject(new UltraFitEnv(fCanvas1->GetHistogram()),true);
		else AddFreeObject(new UltraFitEnv(),true);
}

void jEnv::Spectrum(){
	if(fCanvas1->HistogramType()==1){
		if(fSpecTool){
			fSpecTool->NewInput(fCanvas1->GetHistogram());
//          fSpecTool->RaiseWindow();
            
            for(int i=0;i<fTabs->GetNumberOfTabs();i++)if(fSpecTool==fTabs->GetTabContainer(i)){fTabs->SetTab(i,kFALSE);break;}
            if(!IsVisible(fTabs))ShowTabs();
		}else {
            ////// Old free jSpecTool
//          fSpecTool=;
// 			fSpecTool->Connect("Destroyed()", "jEnv", this,"SpecToolClose()");
            
            fSpecTool=new jSpecTool(fTabs,fCanvas1->GetHistogram());
            fTabs->AddTab("SpecTool",fSpecTool);
            fTabs->SetTab(fTabs->GetNumberOfTabs()-1,kFALSE);
            ShowTabs();
		}
	}
}


void jEnv::Gatter(){
	if(fCanvas1->HistogramType()>1){
        TGMainFrame* gate=jGatingToolSelector(fCanvas1->GetHistogram());
		if(gate)AddFreeObject(gate,false);
    }
};


void jEnv::DrawCpy(){
	DrawCopyCanvas(fCanvas1->GetHistogram());
};

void jEnv::DrawCpyTab(){
	TH1* H=fCanvas1->GetHistogram();
	if(!H)return;
	TCanvas* Can= AddCanvasTab(H->GetName());
	Can->cd();
	DrawCopyHistOpt(H);
	ConnectPeakClickerCanvas(Can);
};

void jEnv::DrawSm(){
	gDrawSame=false;
	if(SameSave){delete SameSave;SameSave=0;}
	TH1* h=fCanvas1->GetHistogram();
	if(fCanvas1->HistogramType()==1&&h){
		SameSave=(TH1*)h->Clone();
		gDrawSame=true;
		TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "jEnv", this,"DrawSmHere(TPad*,TObject*,Int_t)");
	}
};

void jEnv::DrawSmHere(TPad* pad,TObject* obj,Int_t event){
	
	if(SameSave&&gDrawSame){
		TCanvas* sender=(TCanvas*)gTQSender;
		TVirtualPad* hold=gPad;
		pad->cd();
		TH1* H=DrawHistOpt(SameSave,true,true,true);
        H->SetLineColor(2);
		sender->Modified();
		sender->Update();
		gPad=hold;
	}

	gDrawSame=false;
	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "DrawSmHere(TPad*,TObject*,Int_t)");
	if(SameSave){delete SameSave;SameSave=0;}
}


void jEnv::jSaveAs(){
	if(fCanvas1->HistogramType())HistSaveAs(fCanvas1->GetHistogram(),this);
};


void jEnv::ShowHideTabs(){if(!fTabs)return;
	if(IsVisible(fTabs)){
		HideTabs();
	}else{
		ShowTabs();
	}
}

void jEnv::ShowTabs(){
	ShowFrame(fTabs);
	fTabs->Resize(fDefaultTabsWidth, fDefaultTabsHeight);//Needed as the actual space occupied by the elements of fTabs is smaller than we want
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
}

void jEnv::HideTabs(){
	HideFrame(fTabs);
	DirList->Resize(fDefaultDirWidth,fDefaultDirHeight);//Not actually needed because who cares if it stays a bit big
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
}


TGCompositeFrame* jEnv::AddTab(string TabName,bool ShowClose){
    if(TabName.size()<1){
        stringstream ss;
        ss<<"Tab "<<fTabs->GetNumberOfTabs()+1;
        TabName=ss.str();
    }
    TGCompositeFrame *NewTab= fTabs->AddTab(TabName.c_str());
    Int_t ID=fTabs->GetNumberOfTabs()-1;
    if(ShowClose){
        fTabs->GetTabTab(ID)->ShowClose();
    }
    fTabs->SetTab(ID,kFALSE);
	if(!IsVisible(fTabs))ShowTabs();
    return NewTab;
}

TCanvas* jEnv::AddCanvasTab(string TabName){
    TGCompositeFrame *NewTab= AddTab(TabName.c_str(),true);
    TabName+="EmbededCanvas";
	TRootEmbeddedCanvas* Embeded= new TRootEmbeddedCanvas(TabName.c_str(),NewTab,600,400);
	NewTab->AddFrame(Embeded, new TGLayoutHints(kLHintsExpandY|kLHintsExpandX, 1, 1, 1, 1));
    fTabs->MapSubwindows();
    ShowFrame(fTabs);
    
	TCanvas* Can= Embeded->GetCanvas();
	ReMargin(Can);
    return Can;
}

void jEnv::CloseTab(Int_t ID){
//     cout<<endl<<ID<<endl;
    fTabs->RemoveTab(ID);
    if(ID>=fTabs->GetNumberOfTabs())ID--;
    fTabs->SetTab(ID,kFALSE);
}


void jEnv::ShowHideDir(){if(!DirList)return;
	if(IsVisible(DirList)){
		HideDir();
	}else{
		ShowDir();
	}
}

void jEnv::ShowDir(){
    int tW=fTabs->GetWidth(),tH=fTabs->GetHeight();
	ShowFrame(DirList);
	DirList->Resize(fDefaultDirWidth,fDefaultDirHeight);
	fTabs->Resize(tW, tH);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);

///// This moved the left edge so DirList open to the side but it wasnt needed
// #if __linux__
//     int x,y;
//     Window_t wdummy;
//     gVirtualX->TranslateCoordinates(GetId(),GetParent()->GetId(),0,0,x,y,wdummy);
//     Move(x-fDefaultDirWidth-8-fPixOffX,y-fPixOffY);
//     SetWMPosition(x-fDefaultDirWidth-8-fPixOffX,y-fPixOffY);
// #endif
}

void jEnv::HideDir(){
    int tW=fTabs->GetWidth(),tH=fTabs->GetHeight();
	HideFrame(DirList);
	fTabs->Resize(tW, tH);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
    
///// This moved the left edge so DirList open to the side but it wasnt needed
// #if __linux__
//     int x,y;
//     Window_t wdummy;
//     gVirtualX->TranslateCoordinates(GetId(),GetParent()->GetId(),0,0,x,y,wdummy);
//     Move(x+fDefaultDirWidth+8-fPixOffX,y-fPixOffY);
//     SetWMPosition(x+fDefaultDirWidth+8-fPixOffX,y-fPixOffY);
// #endif
}

void jEnv::NewDirObject(TObject* obj){
    // Only for object types outside the scope of CCframe
    
	if(obj->IsA()->InheritsFrom(TGraph::Class())){
        TCanvas* Can=AddCanvasTab(obj->GetName());
        Can->cd();
		gPad->Update();
        DrawCopyGraphOpt((TGraph*)obj,Alternator)->SetMarkerStyle(20);
        Alternator=!Alternator;
        return;
	}	
	    
	if(obj->IsA()==TMultiGraph::Class()){
        TCanvas* Can=AddCanvasTab(obj->GetName());
        Can->cd();
		gPad->Update();
        if(Alternator)((TMultiGraph*)obj)->DrawClone("al");
        else ((TMultiGraph*)obj)->DrawClone("ap");
        Alternator=!Alternator;
        return;
	}	
	
	if(obj->IsA()->InheritsFrom(TF1::Class())){
        TCanvas* Can=AddCanvasTab(obj->GetName());
        Can->cd();
		gPad->Update();
        ((TF1*)obj)->DrawCopy();
        return;
	}		
	
	if(obj->IsA()->InheritsFrom(TCanvas::Class())){
        ((TCanvas*)obj)->Draw();
        return;
	}
	
	if(obj->IsA()->InheritsFrom(TTree::Class())){
        new TTreeViewer((TTree*)obj);
        return;
	}		
	
	if(obj->IsA()->InheritsFrom(THnBase::Class())){
		// I am surprised the conversion to TObject* for the associated key worked,
		// THnBase *h = dynamic_cast<THnBase*>obj  etc wasnt needed at any point
        TGMainFrame* gate=jGatingToolSelector(obj);
		if(gate)AddFreeObject(gate,false);
        return;
	}	
	
}

void jEnv::NewCanvasObject(TObject* obj){
    // Shouldnt actually use that object pointer
	// Functions that interact with histograms will make a new request to CCframe
	// This function just configures jEnv for the fact CCframe has a new histogram of type "c"

    int c=fCanvas1->HistogramType();
    for (auto i : OneOnly){
        if(c==1){
            i->SetEnabled();
        }else{
            i->SetEnabled(kFALSE);
        }
    }
    for (auto i : OneNotly){
        if(c>1){
            i->SetEnabled();
        }else{
            i->SetEnabled(kFALSE);
        }
    }
}

void jEnv::ClosedObject(TObject* obj){
//     cout<<endl<<"A free object has closed. Here is a pointer to where it HAD been located in memory "<<obj<<endl;    
    FreeObjects.Remove(obj);
}



void jEnv::Clipboard(Int_t event,Int_t x,Int_t y,TObject *o){
    if(event == kButton2Up){
        TVirtualPad* hold=gPad;
        int clipstatus= DrawFromClipboard();
        gPad=hold;
        clipstatus++;//just here to supress warning, clipstatus currently unused
    }
}

