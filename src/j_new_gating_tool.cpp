// //
// //
// //	James gating GUI tool 1.2
// // 	27/10/16		16/10/2015
// //	james.smallcombe@outlook.com
// //
// //
// 
// #include "j_gating_tool.h" // Currently included just for gGlobalAskWindowName
// #include "j_gpad_tools.h"
#include "j_new_gating_tool.h"
#include "j_gating_tool.h"
// 
// 
// ClassImp(jnewgating_tool);
// 
// int jnewgating_tool::jnewgating_tool_iterator = 0;
// 
// jnewgating_tool::jnewgating_tool(const char * input) : jnewgating_tool(gROOT->FindObject(input)){}
// 
// jnewgating_tool::jnewgating_tool(TObject* input,bool Owner) : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame) ,gJframe1(0),fCheck0(0),fCheck1(0),fFitFcn(0),peaknumremove(0),fTip(0),fFitPanel(0),fInputStore(0),x1(1),x2(-1),y1(1),y2(-1),RangeUpdateHold(1){
// TVirtualPad* hold=gPad;
//     ResetRange();
// 
// 	if(!input){
// //      delete this;
//         return;
//     }
//     
// 	bool Bthree=input->IsA()->InheritsFrom("TH3");
//     
//     if(!(Bthree||input->IsA()->InheritsFrom("TH2"))){
//         return;
//     }
//     
// 	TGTransientFrame* PopUp=0;
// 	if(Bthree){
//         PopUp=MakeTH3Popup();
// 		cout<<endl<<endl<<" ============== Beginning Loading of TH3 ============ "<<endl<<" ====== Please be patient until window appears ====== "<<endl<<endl;
// 	}
// 		
// 	char* FrameReNamChar=new char[128];
//     string FrameReNamStr;
// 	if(gGlobalAskWindowName){
//         new TGInputDialog(gClient->GetRoot(),gClient->GetRoot(),"Rename Gate Tool Window",input->GetName(),FrameReNamChar);
//         FrameReNamStr=FrameReNamChar;
//     }
//     
// 	if(FrameReNamStr.size()){
// 		SetWindowName(FrameReNamStr.c_str());	
// 	}else{
// 		SetWindowName(input->GetName());	
// 	}
// 	
//     TH1* pass=(TH1*)input;
// 
//     if(!Bthree){
//         // Make a local copy of TH2
//         // Still too intensive to do it for TH3 though.
//         stringstream ss;
//         ss<<"GateStoreCopy"<<make_iterator();
//         fInputStore=(TH1*)pass->Clone(ss.str().c_str());
//         pass=fInputStore;
//     }
// 
// 
//     //
//     //   FINISHED INPUT START BUILDING THE FRAMES
//     //
//     
//     SetCleanup(kDeepCleanup);	
//     
//     //    //--- layout for the frame:
//     TGLayoutHints* ffExpandLeft = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0);
//     TGLayoutHints* ffExpand = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0);
//     TGLayoutHints* ffExpandRight = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsRight, 0, 0, 0, 0);
// //     TGLayoutHints* ffExpandY = new TGLayoutHints(kLHintsExpandY, 0, 0, 0, 0);
//     TGLayoutHints* ffExpandYRight = new TGLayoutHints(kLHintsExpandY | kLHintsRight, 0, 0, 0, 0);
//     TGLayoutHints* ffExpandYLeft = new TGLayoutHints(kLHintsExpandY | kLHintsLeft, 0, 0, 0, 0);
//     TGLayoutHints* ffExpandXpad = new TGLayoutHints(kLHintsExpandX, 3, 3, 3, 3);
//     TGLayoutHints* ffCenX = new TGLayoutHints(kLHintsCenterX, 3, 3, 3, 3);
//     TGLayoutHints* ffCenY = new TGLayoutHints(kLHintsCenterY, 3, 3, 3, 3);
//     TGLayoutHints* ffCenTop = new TGLayoutHints(kLHintsTop | kLHintsCenterX, 3, 3, 3, 3);
//     TGLayoutHints* ffSpeBuf = new TGLayoutHints(kLHintsTop | kLHintsCenterX, 0, 0,10,10);
//     
//     //
//     //   BUILD HISTOGRAM SAVING FRAME
//     //
//     
//     savehists.clear();
//     savechecks.clear();
//     savebutton.clear();
//     
//     TGTextButton* spbutton = new TGTextButton(this,">");
//     spbutton->Connect("Clicked()","jnewgating_tool",this,"SavePanel()");
//     spbutton->SetToolTipText("Show Save Panel\n Open side-panel for holding gating results\n  in memory to enable on-the-fly summing.");
//     
//     saveframe= new TGVerticalFrame(this, 0, 0, 0); 
// // 		TGButtonGroup* savecontrolbut = new TGButtonGroup(saveframe,1,2);
//     TGTextButton* plushist = new TGTextButton(saveframe,"DrawSum");
//     plushist->Connect("Clicked()","jnewgating_tool",this,"DrawSaved()");
//     plushist->SetToolTipText("Draw a sum of currently\n selected saved Histograms.");
//     saveframe->AddFrame(plushist,ffSpeBuf);//
//     
//     plushist = new TGTextButton(saveframe,"DeleteAll");
//     plushist->Connect("Clicked()","jnewgating_tool",this,"CSaveButton()");
//     plushist->SetToolTipText("Clear all locally saved\n gated histograms.");
//     saveframe->AddFrame(plushist,ffSpeBuf);//
//     
//     TGLabel *label = new TGLabel(saveframe, "Saved Gated\n Histograms.\n Check box\n   to sum.");
// // 		TGHorizontalFrame* inbetw= new TGHorizontalFrame(saveframe, 0, 0, 0);
// // 		savebuttons = new TGButtonGroup(inbetw,"",kVerticalFrame);
//     savebuttons = new TGButtonGroup(saveframe,15,2);
//     savebuttons->Connect(" Clicked(Int_t)", "jnewgating_tool", this,"StoreHistograms(Int_t)");//Link test signal to its	
//     AddStoreHistogram();
//     
//     saveframe->AddFrame(label,ffSpeBuf);//
//     saveframe->AddFrame(savebuttons,ffCenTop);//
//     
//     //
//     //   BUILD RESULT FRAME
//     //
//     
//     MainPanels = new TGHorizontalFrame(this, 0, 0, 0); 
// 
//     resultframe = new TGVerticalFrame(MainPanels, 0, 0, 0);
//     TGHorizontalFrame* buttonframe = new TGHorizontalFrame(resultframe, 0, 0, 0); 
//     fBgroup1 = new TGButtonGroup(buttonframe,"Show Extra",kChildFrame);// Another button group
//         fRButton1 = new TGRadioButton(fBgroup1,"    ");
//         fRButton1->SetToolTipText("Normal View Mode");
//         fRButton2 = new TGRadioButton(fBgroup1,"Projection ");
//         fRButton2->SetToolTipText("Show Projection\n Show a scaled version of the fResFullProj\n un-gated projection for this axis.");
//         fRButton3 = new TGRadioButton(fBgroup1,"Background ");
//         fRButton3->SetToolTipText("Show Background\n Show the background spectrum currently\n being subtracted (actual size).");
//     fRButton1->SetState(kButtonDown);
//     fBgroup1->Show();
//     fBgroup1->Connect(" Clicked(Int_t)", "jnewgating_tool", this,"ButtonGroupDoUpdate(Int_t)");
//     
//     if(Bthree){
//         fCheck0 = new TGCheckButton(buttonframe,"2D ");
//         fCheck0->SetState(kButtonUp);
//         fCheck0->Connect(" Clicked()", "jnewgating_tool", this,"DoCheckbox2D()");
//         fCheck0->SetToolTipText("2D Only\n Do not perform the second axis subtraction.\n Instead view TH2 matrix results from the first.");
//     }
//     
//     fCanvas1 = new TRootEmbeddedCanvas(("Embedded"+make_iterator()).c_str(), resultframe, 600, 400);
//     fCanvas1->GetCanvas()->SetName(("ResultCan"+make_iterator()).c_str());
//     
//     fCanvas1->GetCanvas()->SetFillColor(33);
//     fCanvas1->GetCanvas()->SetBorderMode(0);
//     fCanvas1->GetCanvas()->SetFrameFillColor(10);
// 
//     fCanvas1->GetCanvas()->SetMargin(0.01,0.005,0.08,0.005);	
//     fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jnewgating_tool", this,"ClickedFinalCanvas(Int_t,Int_t,Int_t,TObject*)");
//     fCanvas1->GetCanvas()->Connect("RangeChanged()", "jnewgating_tool", this, "NewAxisDrawn()");
//     
//     // rebin bar
//     
//     TGHorizontalFrame* rebinframe = new TGHorizontalFrame(resultframe, 0, 0, 0);
//         TGLabel *reblabel = new TGLabel(rebinframe, "Binning ");
//         rebinframe->AddFrame(reblabel,ffCenY);
//         
//         fHslider1 = new TGHSlider(rebinframe, 9, kSlider2);
//         fHslider1->SetPosition(0);
//         fHslider1->Connect("PositionChanged(Int_t)", "jnewgating_tool", this, "DoUpdate()");
//         rebinframe->AddFrame(fHslider1, ffExpandXpad);
//         
//         RebinText = new TGTextEntry(rebinframe, new TGTextBuffer(4));
//         RebinText->SetDefaultSize(40,25);
//         RebinText->SetAlignment(kTextCenterX);
//         RebinText->SetEnabled(kFALSE);
//         rebinframe->AddFrame(RebinText,ffCenY);
//     
//     ftbutton = new TGTextButton(buttonframe,"Fit Panel");
//     ftbutton->Connect("Clicked()","jnewgating_tool",this,"FitPanel()");
//     ftbutton->SetToolTipText("Open Fit Tool\n Open an instance of J-fit panel,\n initially connected to result canvas.");
// 
//     TGTextButton* SAbutton = new TGTextButton(buttonframe,"SaveAs");
//     SAbutton->Connect("Clicked()","jnewgating_tool",this,"jSaveAs()");
//     SAbutton->SetToolTipText("Save the currently drawn histogram.");
//     
//     fCheck1 = new TGCheckButton(buttonframe,"Hide Ers");
//     fCheck1->SetState(kButtonDown);
//     fCheck1->Connect(" Clicked()", "jnewgating_tool", this,"DoUpdate()");
//     fCheck1->SetToolTipText("Hide Bin Errors on drawn histograms");
// 
//     buttonframe->AddFrame(fBgroup1, ffCenX);
//     if(Bthree)buttonframe->AddFrame(fCheck0, ffCenY);
//     buttonframe->AddFrame(ftbutton, ffCenY);
//     buttonframe->AddFrame(SAbutton, ffCenY);
//     buttonframe->AddFrame(fCheck1, ffCenY);
//     resultframe->AddFrame(buttonframe, ffCenX);
//     resultframe->AddFrame(fCanvas1, ffExpand);
//     resultframe->AddFrame(rebinframe, ffExpandXpad);  
//     
//     //
//     //   BUILD j_gating_frame FRAMES
//     //
//     
//     //If TH3 extra gate panel
//     if(Bthree){
//         gJframe1 = new j_gating_frame(MainPanels,pass,make_iterator());
//         gJframe1->Connect("InputChange()", "jnewgating_tool", this,"ResetRange()");
//         gJframe1->Connect("OutputReady()", "jnewgating_tool", this,"DoUpdate2D()");
//         pass=(TH1*)gJframe1->fResult;
//     }
//     
//     //TH2 gate panel
//     gJframe2 = new j_gating_frame(MainPanels,pass,make_iterator());
//     gJframe2->Connect("InputChange()", "jnewgating_tool", this,"ResetRange()");
//     gJframe2->Connect("OutputReady()", "jnewgating_tool", this,"DoUpdate()");
//     
//     
//     //
//     //   Add Frames to the main layout
//     //
//     
//     AddFrame(MainPanels, ffExpandLeft);
//     AddFrame(saveframe,ffExpandYRight);
//     AddFrame(spbutton,ffExpandYRight);
//     
//     
//     if(Bthree){
//         gJframe1->ChangeOptions(kFixedWidth);
//         MainPanels->AddFrame(gJframe1,ffExpandYLeft);
//         TGVSplitter* splitter = new TGVSplitter(MainPanels);
//         splitter->SetFrame(gJframe1, kTRUE);
//         MainPanels->AddFrame(splitter,ffExpandYLeft);
//     }
//     
//     gJframe2->ChangeOptions(kFixedWidth);
//     MainPanels->AddFrame(gJframe2,ffExpandYLeft);
//     splitterB = new TGVSplitter(MainPanels);   
//     splitterB->SetFrame(gJframe2, kTRUE);
//     MainPanels->AddFrame(splitterB,ffExpandYLeft);
//     MainPanels->AddFrame(resultframe,ffExpandRight);
//     
//     Connect("ProcessedConfigure(Event_t*)","jnewgating_tool", this,"ProcessedConfigure(Event_t*)");
//     
//     // create the tooltip with a timeout of 250 ms
//     fTip = new TGToolTip(gClient->GetRoot(), fCanvas1, "", 250);
// 
//     MapSubwindows();
//     Resize(GetDefaultSize());
//     MapWindow();
// 
//     HideFrame(saveframe);
//     gJframe2->HideFrame(gJframe2->fHframe4);
//     if(Bthree)gJframe1->HideFrame(gJframe1->fHframe4);
//     
//     ShareMainPanels();
//     
//     DoUpdate();
//     if(PopUp){PopUp->CloseWindow();}
// 	
// gPad=hold;
// }
// 
// //______________________________________________________________________________
// jnewgating_tool::~jnewgating_tool()
// {
//     ClearSaved();//delete any saved result histograms
//     
// // 	if(fTip){fTip->Hide();delete fTip;} // Seems have created many crashes recently 
// 	if(fInputStore){delete fInputStore;}
// 	
// 	Closed(this);
//     
//    // Clean up
//     Cleanup();
// }
// 
// //______________________________________________________________________________
// // void jnewgating_tool::DoClose()
// // {
// //    // Called when window is closed via the window manager
// //    
// //    cout<<endl<<"DOO0000000OM"<<endl;
// //    delete this;
// // }
// 
// 
// void jnewgating_tool::ProcessedConfigure(Event_t*){
// //     cout<<endl<<"Processed "<<in<<flush;
//     ShareMainPanels();
// }
// 
// 
// void jnewgating_tool::ShareMainPanels(){
//     double width = MainPanels->GetWidth();
//     if(gJframe1){
//         if(MainPanels->IsVisible(gJframe2)){
//             gJframe1->SetWidth(width*0.333);
//             gJframe2->SetWidth(width*0.333);
//         }else{
//             gJframe1->SetWidth(width*0.5);
//         }
//     }else{
//         gJframe2->SetWidth(width*0.5);
//     }
//     MainPanels->Layout();//This was the only way I could get for the above SetWidth to happen NOW
// }
// 
// //Just reset the viewing range of thefinal canvas
// void jnewgating_tool::ResetRange(){
// //     cout<<endl<<"RESETTING RANGE"<<endl;
//     // usual -1 +1 actually doesnt work if they are in the same bin
//     x1=1E20;
//     x2=-1E20;
//     y1=1E20;
//     y2=-1E20;
// }
// 
// 
// void jnewgating_tool::DoCheckbox2D(){
//     if(fCheck0)if(fCheck0->GetState()&&fFitPanel){
//         ftbutton->SetState(kButtonUp);
//         HideFrame(fFitPanel);
//     }
//     
//     ResetRange();
// 	CSaveButton();
// 	DoUpdate2D();
// }
// 
// 
// void jnewgating_tool::ButtonGroupDoUpdate(Int_t i){
//     if(i==1){
//         ResetRange();
//     }
//     DoUpdate();
// }
// 
// 
// 
// void jnewgating_tool::DoUpdate2D(){TVirtualPad* hold=gPad;
//     RangeUpdateHold=true;
// 	if(!gJframe1)return;
// 	gJframe1->hidebinerrors=fCheck1->GetState();
// 	if(fCheck0->GetState()){
// 		MainPanels->HideFrame(gJframe2);
// 		MainPanels->HideFrame(splitterB);
// 		fCanvas1->GetCanvas()->cd();
// 		if(fRButton2->GetState()){
//             
// 			TH1* H=DrawCopyHistOpt(gJframe1->fResFullProj);
//             H->GetXaxis()->SetRangeUser(x1,x2);
//             H->GetYaxis()->SetRangeUser(y1,y2);
// 		}else if(fRButton3->GetState()){
// 			gJframe1->free_hist->Add(gJframe1->fGate,gJframe1->fResult,1,-1);
// 			TH1* H=DrawCopyHistOpt(gJframe1->free_hist);
//             H->GetXaxis()->SetRangeUser(x1,x2);
//             H->GetYaxis()->SetRangeUser(y1,y2);
// 		}else{
// 			TH1* H=gJframe1->fResult;
//             DrawHistOpt(H);
//             H->GetXaxis()->SetRangeUser(x1,x2);
//             H->GetYaxis()->SetRangeUser(y1,y2);
// 		}
// 
// 		fCanvas1->GetCanvas()->Modified();
// 		fCanvas1->GetCanvas()->Update();
// 	}else{
// 		gJframe2->hidebinerrors=fCheck1->GetState();
// 		MainPanels->ShowFrame(gJframe2);
// 		MainPanels->ShowFrame(splitterB);
// 		gJframe2->UpdateInput(gJframe1->fResult);
// 	}
// 	ShareMainPanels();
// RangeUpdateHold=false;
// gPad=hold;
// }
// 
// 
// void jnewgating_tool::DoUpdate(){
//     TVirtualPad* hold=gPad;
//     RangeUpdateHold=true;
//     
// 	gJframe2->hidebinerrors=fCheck1->GetState();
// 
// 	if(fCheck0){
// 		if(fCheck0->GetState()){//Dangerously close to awful loop behaviour
// 			DoUpdate2D();
// 			return;
// 		}
// 	}
// 
// 	ShowFrame(gJframe2);
// 	
// 	unsigned short rebin=fHslider1->GetPosition()+1;
// 	
// 	TH1* H;
// 	fCanvas1->GetCanvas()->cd();
//     
// 	H=DrawCopyHistOpt(gJframe2->fResult,fCheck1->GetState());
// 	if(rebin>1)H->Rebin(rebin);		
//     H->GetXaxis()->SetRangeUser(x1,x2);
//     
//     char buf[32];
//     sprintf(buf, "%.1f", H->GetXaxis()->GetBinWidth(1));
//     TGTextBuffer* fTbh2=RebinText->GetBuffer();
//     fTbh2->Clear();	fTbh2->AddText(0, buf);
//     RebinText->SetCursorPosition(RebinText->GetCursorPosition());
//     RebinText->Deselect();
//     gClient->NeedRedraw(RebinText);
//     
// //     H->GetXaxis()->SetLabelSize(0.03);
// //     H->GetXaxis()->SetTicks("+");
// //     H->GetXaxis()->SetLabelFont(42);
//     H->GetYaxis()->SetNdivisions(8);
//     H->GetYaxis()->SetTickLength(0.03);
//     
// 	if(fRButton2->GetState()){
// 		gJframe2->free_hist->Reset();
// 		gJframe2->free_hist->Add(gJframe2->fResFullProj,gJframe2->fResult->Integral()/gJframe2->fResFullProj->Integral());
// 	}
// 	if(fRButton3->GetState()){
// 		gJframe2->free_hist->Add(gJframe2->fGate,gJframe2->fResult,1,-1);
// 	}
// 	if(!fRButton1->GetState()){
// 		gJframe2->free_hist->Sumw2(kFALSE);
// 		TH1* h=gJframe2->free_hist->DrawCopy("same");
// 		if(rebin>1)h->Rebin(rebin);		
// 	}
// 	
// 	fCanvas1->GetCanvas()->Modified();
// 	fCanvas1->GetCanvas()->Update();
// 	
// RangeUpdateHold=false;
// gPad=hold;
// }
// 
// 
// string jnewgating_tool::make_iterator(){
// 	stringstream ss;
// 	ss << jnewgating_tool_iterator;
// 	jnewgating_tool_iterator++;
// 	return ss.str();
// }
// 
// 
// // Just a basic little no frills, minimal input peak fitter for standard size y/e peaks
// // Added it in to help with quick peak identification
// void jnewgating_tool::ClickedFinalCanvas(Int_t event, Int_t px, Int_t py, TObject *selected_ob)
// {TVirtualPad* hold=gPad;
// 	if (event == kMouseLeave){fTip->Hide(); return;}
// 	
// 	//Click is given in pixel coordinates
// 	double x =fCanvas1->GetCanvas()->PixeltoX(px);
// 	
// 	//Update the tooltip
// 	fTip->Hide();
// 	fTip->SetText(TString::Format("%.1f",x));
// 	fTip->SetPosition(px+15, py-15);
// 	fTip->Reset();
// 	
// 	if ( event == kButton1Double) {
//         if(gJframe1){
//             if(fCheck0->GetState())return;
//             //Dont try to fit in 2D mode
//         }
//         
// 		fCanvas1->GetCanvas()->cd();
// 	
// 		TH1* h=hist_capture(fCanvas1->GetCanvas());
// 		if(!h)h=gJframe2->fResult;
// 		
// 		TF1* Quick=UserQuickSingleGausAutoFitE(h,x,x-20,x+20,1);//Free & linear back
// 
// 		if(fFitFcn)fCanvas1->GetCanvas()->GetListOfPrimitives()->Remove(fFitFcn);
// 		fFitFcn=Quick->DrawCopy("same");
// 
// 		// Print the text on the canvas
// 		double cent=Quick->GetParameter(1);
// 		stringstream ss;
// 		ss<<round(cent*10)/10;
// 		
// 		delete Quick;
// 		
// 		TText peaknum;
// 		peaknum.SetTextAlign(22);
// 		peaknum.SetTextSize(0.035);
// 		
// 		double shif=(h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetLast())-h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetFirst()))*0.05;
// 		//GetXmin() doesnt account for zooming
// 		
// 		if(peaknumremove)fCanvas1->GetCanvas()->GetListOfPrimitives()->Remove(peaknumremove);//Remove if its there else ignored
// 		peaknumremove=peaknum.DrawText(cent+shif,h->GetBinContent(h->FindBin(cent))*0.95,ss.str().c_str());
// 
// 		fCanvas1->GetCanvas()->Modified();
// 		fCanvas1->GetCanvas()->Update();
// 	}
// 	
// gPad=hold;
// }
// 
// void jnewgating_tool::SavePanel(){
// 	if(IsVisible(saveframe)){
// 		HideFrame(saveframe);
// 	}else{
// 		ShowFrame(saveframe);
// 	}
// 	ShareMainPanels();
// }
// 
// void jnewgating_tool::FitPanel(){
// 	if(fCheck0)if(fCheck0->GetState())return;
//     
//     if(!fFitPanel){
// 		fFitPanel=new UltraFitEnv(this,0,fCanvas1->GetCanvas(),2);
//         AddFrame(fFitPanel,new TGLayoutHints(kLHintsExpandY, 1, 1, 1, 1));
//         Resize(GetDefaultSize());
//         HideFrame(fFitPanel);
//     }
//     
// 	if(IsVisible(fFitPanel)){
//         ftbutton->SetState(kButtonUp);
//         HideFrame(fFitPanel);
//         fFitPanel->KillCan();
//         DoUpdate();
//     }else{
//         ftbutton->SetState(kButtonDown);
//         ShowFrame(fFitPanel);
//         fFitPanel->ConnectNewCanvas(fCanvas1->GetCanvas());
// 	}
// 	ShareMainPanels();
// }
// 
// void jnewgating_tool::jSaveAs(){
// 	TH1* h=hist_capture(fCanvas1->GetCanvas());
// 	if(!h)h=gJframe2->fResult;
// 	HistSaveAs(h,this,fCanvas1->GetCanvas());
// }
// 
// void jnewgating_tool::AddStoreHistogram(){
// 	if(savehists.size()<15){
// 		savebutton.push_back(new TGTextButton(savebuttons,"  [save]  "));
// 		
// 		savebutton[savebutton.size()-1]->SetToolTipText("Save current gating\n result histogram.");
// 		savechecks.push_back(new TGCheckButton(savebuttons,""));
// 		savechecks[savechecks.size()-1]->SetEnabled(false);
// 		savechecks[savechecks.size()-1]->SetToolTipText("Include this saved histogram\n when drawing sum.");
// 		savehists.push_back(0);
// 		savebuttons->Show();
// 		saveframe->MapSubwindows();saveframe->Resize(saveframe->GetDefaultSize());saveframe->MapWindow();
// 	}
// }
// 
// 
// void jnewgating_tool::StoreHistograms(Int_t i){
// 	if(i%2){
// 		uint select=i/2;
// 	// 	cout<<endl<<endl<<i<<endl<<endl;
// 		if(select<savehists.size()){
// 			if(savehists[select]){delete savehists[select];}savehists[select]=0;
// 
// // 			savehists[select]=new TH1F();
// // 			gJframe2->fResult->Copy(*savehists[select]);
// // 			savehists[select]->SetName(("savedhist"+make_iterator()).c_str());
// 			
// 			TH1* targ=gJframe2->fResult;;
// 			if(fCheck0)if(fCheck0->GetState()) targ=gJframe1->fResult;
// 			
// 			savehists[select]=(TH1*)targ->Clone(("savedhist"+make_iterator()).c_str());
// 			savehists[select]->GetListOfFunctions()->Clear();
// 			
// 			if(!savechecks[select]->IsEnabled())savechecks[select]->SetEnabled();
// 			
// 			stringstream ss;ss<<" "<<gJframe2->GateCentre<<" ";
// 			if(fCheck0)if(fCheck0->GetState()){ss.clear(); ss.str("");ss<<" "<<gJframe1->GateCentre<<" ";}
// 			
// 			savebutton[select]->SetText(ss.str().c_str());
//             
//             if(select==savebutton.size()-1)AddStoreHistogram();
// 		}
// 	}
// }
// 
// void jnewgating_tool::DrawSaved(){
// 	TH1* saveadd=0;
// 	for(uint i=0;i<savehists.size();i++){
// 		if(savehists[i]&&savechecks[i]->GetState()==EButtonState::kButtonDown){
// 			if(saveadd){
// 				if(saveadd->GetNbinsX()==savehists[i]->GetNbinsX())
// 					saveadd->Add(savehists[i]);
// 			}else{
// 				saveadd=(TH1*)savehists[i]->Clone(("savedhist"+make_iterator()).c_str());
// 			}
// 		}
// 	}
// 	if(saveadd){
// 		unsigned short rebin=fHslider1->GetPosition()+1;
// 		if(rebin>1)saveadd->Rebin(rebin);
//         DrawPeakClickerCanvas(saveadd);
//         saveadd->SetDirectory(0);
//         saveadd->SetBit(kCanDelete);
//         //Could have done drawcopy but this saves one copy if a big TH2
// 	}
// }
// 
// void jnewgating_tool::ClearSaved(){
// 	for(uint i=0;i<savehists.size();i++){
//         if(savehists[i]){
//             delete savehists[i];
//             savehists[i]=0;
//         }
//     }
// }
// 
// 
// //Doesnt actually clear anything, you just cant select them
// void jnewgating_tool::CSaveButton(){
//     
//     std::chrono::duration<double> diff= std::chrono::system_clock::now()-clicktime;
//     if(abs(diff.count())<2){
//         for(uint i=0;i<savehists.size();i++){
//             savechecks[i]->SetState(kButtonUp);
//             savechecks[i]->SetState(kButtonDisabled);
//             savebutton[i]->SetText("[Empty]");
//         }
//         ClearSaved();
//         
// //         cout<<endl<<"Saved results cleared."<<endl;
//     }else{
//         cout<<"Click twice to clear."<<endl;
//     }
//     
//     clicktime=std::chrono::system_clock::now();
// }
// 
// 
// 
// void jnewgating_tool::NewAxisDrawn() //adjust sliders and control values for new axis
// {
// 	if(fFitFcn&&fCanvas1->GetCanvas()->GetListOfPrimitives()->FindObject(peaknumremove)){
// 		
// 		TH1* h=hist_capture(fCanvas1->GetCanvas());
// 		if(!h)h=gJframe2->fResult;
// 		double cent=fFitFcn->GetParameter(1);
// 		double shif=(h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetLast())-h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetFirst()))*0.05;
// 		peaknumremove->SetX(cent+shif);
// 		fCanvas1->GetCanvas()->Modified();
// 		fCanvas1->GetCanvas()->Update();
// 	}
// 	
// 	if(!RangeUpdateHold){
// 		TH1* h=hist_capture(fCanvas1->GetCanvas());
//         if(h){
// //             cout<<endl<<"GRABBING NEW RANGE"<<endl;
//             TAxis* x=h->GetXaxis();
//             x1=x->GetBinLowEdge(x->GetFirst());
//             x2=x->GetBinUpEdge(x->GetLast());
//             
//             if(fCheck0){if(fCheck0->GetState()){
//                 TAxis* y=h->GetXaxis();
//                 y1=y->GetBinLowEdge(y->GetFirst());
//                 y2=y->GetBinUpEdge(y->GetLast());
//             }}
//         }
//     }
// 	
// }
// 
// #include <TGIcon.h>
// TGTransientFrame* jnewgating_tool::MakeTH3Popup(){
//     TGTransientFrame* popup=new TGTransientFrame(gClient->GetRoot(), gClient->GetRoot(), 400, 200, kHorizontalFrame);
// 
// //    fClient->GetPicture("mb_exclamation_s.xpm");
// //    fClient->GetPicture("mb_asterisk_s.xpm");
//     TGLayoutHints *fL1 = new TGLayoutHints(kLHintsCenterY | kLHintsExpandX, 5, 20, 0, 0);
// 
//     TGIcon *fIcon = new TGIcon(popup, fClient->GetPicture("mb_stop_s.xpm"),100, 100);
//     popup->AddFrame(fIcon,new TGLayoutHints(kLHintsCenterY, 20, 15, 20, 20));
// 
//     TGVerticalFrame* fLabelFrame = new TGVerticalFrame(popup, 60, 20);
//     popup->AddFrame(fLabelFrame,fL1);
//    
//     TGLabel *label1 = new TGLabel(fLabelFrame,"====================================================");
//     TGLabel *label2 = new TGLabel(fLabelFrame,"============= Beginning Loading of TH3 =============");
//     TGLabel *label3 = new TGLabel(fLabelFrame,"====== Please be patient until window appears ======");
//     TGLabel *label4 = new TGLabel(fLabelFrame,"====================================================");
// //        label->SetTextJustify(text_align);
//     fLabelFrame->AddFrame(label1, fL1);    
//     fLabelFrame->AddFrame(label2, fL1);    
//     fLabelFrame->AddFrame(label3, fL1);    
//     fLabelFrame->AddFrame(label4, fL1);    
//         
//     popup->SetWindowName("LOADING");
// 
//     popup->MapSubwindows();
//     popup->Resize(popup->GetDefaultSize());
//     popup->MapWindow();
//     gClient->NeedRedraw(popup,kTRUE);
// 
//     int waitc=0;
//     while(waitc<20){
//         gSystem->ProcessEvents();//gSystem->InnerLoop();
//         gSystem->Sleep(5);
//         waitc++;
//     // Little loop to buy Xsystem time to draw the box before code moves on
//     }
// //     gClient->WaitFor(popup);
//         
// // 	popup->Connect("CloseWindow()","TGTransientFrame",popup,"DontCallClose()");
//     popup->DontCallClose();
//     
// //     CenterOnParent();// position relative to the parent's window
//     
//     return popup;
// }
// 


ClassImp(j_gating_frametwodee);


j_gating_frametwodee::j_gating_frametwodee(TGWindow *parent,TH1* input,bool ThreeDee) : TGHorizontalFrame(parent, 100, 100),
    fInputStore(nullptr),fProj(nullptr), fGate(nullptr), fBack(nullptr), fResult(nullptr), fResFullProj(nullptr),
    GateCentralValue(0), xy(0), suffix(jgating_tool::Iterator("")),
    fGateFrame(new j_gating_select_frame(this, fProj,(((int)ThreeDee)+1)*2)),
    fResFrame(new j_gating_result_frame(this, &fResult, &fBack, &fResFullProj, &GateCentralValue, ThreeDee)){
// It may be better to initilise the frames after the histograms so they dont try to do their first draw with empty histograms
   
	UpdateInput(input);  
}
    
j_gating_frametwodee::~j_gating_frametwodee(){
	Cleanup(); 
}

void j_gating_frametwodee::ChangeProjection(const Int_t id)
{  
	xy=id-1;
	UpdateInput();
}

//______________________________________________________________________________
void j_gating_frametwodee::UpdateInput(TH1* input){ 
	fInputStore=(TH1*)input->Clone(jgating_tool::Iterator("GateStoreCopy"));
	UpdateInput();
}

//______________________________________________________________________________

// Replace histograms and pass new projection to gatingframe
// Subsequently gatingframe will "emit" and this frame will do the gate
// Called for new input histogram or change axis
void j_gating_frametwodee::UpdateInput()
{       
//     Emit("InputChange()");///// Not sure if this is needed in this new version yet
    
TVirtualPad* hold=gPad;

	if(fProj)delete fProj;

	fProj=hist_proj(fInputStore,xy,"proj"+suffix,true);
    // We decided to get rid of the overflow histgram view proj_flow from old class
    
    //May not be needed
	fProj->SetStats(0);
	fProj->SetTitle("");
	fProj->SetLineColor(1);

	if(fResFullProj)delete fResFullProj;
	fResFullProj=hist_gater_bin(1,fInputStore,xy,"fResFullProj"+suffix);
	fResFullProj->SetStats(0);	
	fResFullProj->SetTitle("");
	
	if(fResult)delete fResult;
	fResult=(TH1*)fResFullProj->Clone(("outputhist"+suffix).c_str());
	fResult->SetLineColor(1);
	fResult->GetXaxis()->SetTitleOffset(1.0);//Fixed a problem from other lib with Yaxis title

    fGateFrame->UpdateInput(fProj);
        
gPad=hold;
}

// The main gating function, which is called when daugter select_frame says so
void j_gating_frametwodee::DoHistogram(){
	
    // Some of these could have been set by j_gating_select_frame emits
    // Or by having DoHistogram takes these as inputs and connecting though the signals
    double backfrack=fGateFrame->GetBackFrac();
    double backfrackfrac=fGateFrame->GetBackFracFrac();
    int gate_down=fGateFrame->GetGateBinDown(), gate_up=fGateFrame->GetGateBinUp();
    int background_mode=fGateFrame->GetBackMode();
    int back_down=fGateFrame->GetBackBinDown(), back_up=fGateFrame->GetBackBinUp();
    
	// hist_gater_bin *should* nicely fill the histogram matching the name if the TH1 exists
	// so we dont need to delete pointer fGate
	fGate=hist_gater_bin(gate_down,gate_up,fInputStore,xy,"fGate"+suffix);
    fGate->SetLineColor(1);
	fGate->GetXaxis()->SetTitleOffset(1.0);//Fixed a problem from other lib with Yaxis title
	
    // Note the "fResFullProj" projection used to make full and anti includes the overflow, but excludes the underflow bin
    // This is an intentional choice as often intentionally zeroed data may be sorted into the underflow bin
    // The underflow bin can be selected with manual sliders
    
	switch (background_mode) {
		case 1://full
            scaled_back_subtract(fGate,fResFullProj,backfrack,fResult,backfrackfrac);
			break;
		case 2://compton
            {
                TH1* compton_hist=hist_gater_bin(back_down,fInputStore,xy,"c_gate");
                scaled_back_subtract(fGate,compton_hist,backfrack,fResult,backfrackfrac);
                delete compton_hist;
            }
			break;
		case 3://anti gate
			{
				TH1* anti_hist=(TH1*)fResFullProj->Clone("antiback");
				anti_hist->Add(fGate,-1);
				anti_hist->Sumw2(kFALSE);
				scaled_back_subtract(fGate,anti_hist,backfrack,fResult,backfrackfrac);
				delete anti_hist;
			}
			break;
		case 4://none
			{
                
			}
			break;
		default://manual // Compton // Antiate
			{
				TH1* manb_hist=hist_gater_bin(back_down,back_up,fInputStore,xy,"m_gate_2d");
                if(gate_down>back_down&&gate_up<back_up)manb_hist->Add(fGate,-1);//In special case remove the gated part
				manb_hist->Sumw2(kFALSE);
				scaled_back_subtract(fGate,manb_hist,backfrack,fResult,backfrackfrac);
				delete manb_hist;				
			}
			break;
	}
	
	fResult->SetTitle("");

	Emit("OutputReady()");// Or call the result frame directly
}







