#include "j_fitting_2Dtool.h"

////////////////////////////////////////////////////////////////

jFittingTool2D::jFittingTool2D(TH2* fH,double sigx,double sigy): 
	TGMainFrame(gClient->GetRoot(),800,600)
    {
		SetCleanup(kDeepCleanup);
		
        // Create the vertical frame
        fFrame = new jFittingFrame2D(this, fH,sigx,sigy);
        
        // Add it to the main frame with expand X and Y options
        AddFrame(fFrame, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

        // Set window name and map it
        SetWindowName("jFittingTool2D");
        MapSubwindows();
        Resize(GetDefaultSize());
        MapWindow();
    }

jFittingTool2D::~jFittingTool2D() {
	// Properly delete child widgets
	Cleanup();
}


////////////////////////////////////////////////////////////////

jFittingFrame2D::jFittingFrame2D(TGWindow * parent,TH2* fH,double sigx,double sigy) : TGVerticalFrame(parent, 100, 100),
	fHist(new TH2I()),sigmaX(1.0),sigmaY(1.0),rangeX(1.0),rangeY(1.0), TextSlideBlock(false), Nslide(1000)
{
// TVirtualPad* hold=gPad;


	fCanvas1 = new TRootEmbeddedCanvas("fit2Dcanvas1",this,600,400);
    fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jFittingFrame2D", this,"Fit2DPeak(Int_t,Int_t,Int_t,TObject*)");
	fCanvas1->GetCanvas()->SetMargin(0.12,0.04,0.12,0.05);
	
    AddFrame(fCanvas1,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY, 1, 1, 1, 1));
    
    TGHorizontalFrame* buttons = new TGHorizontalFrame(this);       
    
        jHistCapButton *CaptureButton = new jHistCapButton(buttons,"    Capture Hist    ");
        CaptureButton->Connect("NewHist(TH1*)","jFittingFrame2D",this,"SetNewHist(TH2*)");	
        buttons->AddFrame(CaptureButton);

        TGTextButton *MakeButton = new TGTextButton(buttons,"       SaveXY       ");
        MakeButton->Connect("Clicked()","jFittingFrame2D",this,"SaveXY()");	
        buttons->AddFrame(MakeButton);
        
        MakeButton = new TGTextButton(buttons,"   Reset   ");
        MakeButton->Connect("Clicked()","jFittingFrame2D",this,"Reset()");	
        buttons->AddFrame(MakeButton);
    
    AddFrame(buttons,new TGLayoutHints(kLHintsCenterX, 1, 1, 1, 1));
	
	TGLayoutHints* CentY = new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1);
	TGLayoutHints* ExpX = new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 1);
	
	TGHorizontalFrame* SlideX = new TGHorizontalFrame(this); 
		TGLabel* SlideXlab = new TGLabel(SlideX, "Sigma X");
		fTextEntry1 =  new TGTextEntry(SlideX, "0000.0000");
		fTextEntry1->SetAlignment(kTextCenterX);
		fTextEntry1->Connect("TextChanged(const char*)", "jFittingFrame2D", this, "SetSliderX(const char*)");

		fHslider1 = new TGHSlider(SlideX, Nslide, kSlider2);
		fHslider1->Connect("PositionChanged(Int_t)", "jFittingFrame2D", this, "SetText()");
		SlideX->AddFrame(SlideXlab,CentY);
		SlideX->AddFrame(fTextEntry1,CentY);
		SlideX->AddFrame(fHslider1, ExpX);
	AddFrame(SlideX, ExpX);
	
	TGHorizontalFrame* SlideY = new TGHorizontalFrame(this); 
		TGLabel* SlideYlab = new TGLabel(SlideY, "Sigma Y");
		fTextEntry2 =  new TGTextEntry(SlideY, "0000.0000");
		fTextEntry2->SetAlignment(kTextCenterX);
		fTextEntry2->Connect("TextChanged(const char*)", "jFittingFrame2D", this, "SetSliderY(const char*)");
		fTextEntry2->SetEnabled(kFALSE);

		fHslider2 = new TGHSlider(SlideY, Nslide, kSlider2);
		fHslider2->Connect("PositionChanged(Int_t)", "jFittingFrame2D", this, "SetText()");
		fHslider2->SetEnabled(kFALSE);
		
		fCheckY = new TGCheckButton(SlideY);// A tick box with hover text belonging to a parent frame
		fCheckY->SetState(kButtonUp);
		fCheckY->Connect("Clicked()","jFittingFrame2D",this,"EnableSigmaY()");//Link it signal to its slot
		
		SlideY->AddFrame(SlideYlab,CentY);
		SlideY->AddFrame(fTextEntry2,CentY);
		SlideY->AddFrame(fHslider2, ExpX);
		SlideY->AddFrame(fCheckY,CentY);
		
	AddFrame(SlideY, ExpX);

	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
	
	
    g2 = new TF2("g2","[5]+[0]*exp(-0.5*pow((x-[1])/[3],2))*exp(-0.5*pow((y-[2])/[4],2))");
    g2->SetParNames("Height","X0","Y0","Xsig","Ysig","Pol0");
    g2->SetContour(15);

    
	SetNewHist(fH);
	
	if(sigx){
		fHslider1->SetPosition(Nslide*sigx/rangeX);
	}
	if(sigy){
		fHslider2->SetPosition(Nslide*sigy/rangeX);
	}
	SetText();
}
	
// 
jFittingFrame2D::~jFittingFrame2D(){
    TQObject::Disconnect(this);//Because of the histogram grabbing functionality
}

void jFittingFrame2D::SetSliderX(const char* txt){
	if(TextSlideBlock)return;
	TextSlideBlock=true;
	std::stringstream ss(txt);
    double val;
    ss >> val;
// 	fHslider1->SetRange(0,10000);// Integers 
	fHslider1->SetPosition(Nslide*val/rangeX);
	TextSlideBlock=false;
}
void jFittingFrame2D::SetSliderY(const char* txt){
	if(TextSlideBlock)return;
	TextSlideBlock=true;
	std::stringstream ss(txt);
    double val;
    ss >> val;
	fHslider2->SetPosition(Nslide*val/rangeY);
	TextSlideBlock=false;
}
void jFittingFrame2D::SetText(){
	if(TextSlideBlock)return;
	TextSlideBlock=true;
	double X=fHslider1->GetPosition();
	double Y=fHslider2->GetPosition();
	
    fTextEntry1->SetText(Form("%.6g", rangeX*X/Nslide));
    fTextEntry2->SetText(Form("%.6g", rangeY*Y/Nslide));
	TextSlideBlock=false;
}

void jFittingFrame2D::EnableSigmaY(){
	if(fCheckY->GetState()){
		fTextEntry2->SetEnabled(kTRUE);
		fHslider2->SetEnabled(kTRUE);
	}else{
		fTextEntry2->SetEnabled(kFALSE);
		fHslider2->SetEnabled(kFALSE);
	}
}

void jFittingFrame2D::SetNewHist(TH2 *fH){
	if(!fH)return;
    
	if(fHist!=fH){
		if(fHist)delete fHist;
		fHist=(TH2*)fH->Clone("fHist2Dfit");
		hformat(fHist);
		
		rangeX=0.2*(fH->GetXaxis()->GetXmax()-fH->GetXaxis()->GetXmin());
		rangeY=0.2*(fH->GetYaxis()->GetXmax()-fH->GetYaxis()->GetXmin());
		TextSlideBlock=true;
		fHslider1->SetPosition(100);
		fHslider2->SetPosition(100);
		TextSlideBlock=false;
		SetText();
	}
	
	// Mostly included for Reset of same histogram
	// Using Fit option "N" followed by TF2::Draw("same") cause issues
	// TF2 was drawn dashed and graphical zooming became limited.
	fHist->GetListOfFunctions()->Clear();
	
	fHist->GetXaxis()->SetRange();
	fHist->GetYaxis()->SetRange();
	
	fCanvas1->GetCanvas()->cd();
	fHist->Draw("col");
	gPad->Update();
	
}

void jFittingFrame2D::Fit2DPeak(Int_t event, Int_t px, Int_t py, TObject *selected_ob){
	if(!fHist){return;}
	if(event == kMouseLeave){return;}
	
	TCanvas* Can=(TCanvas*)fCanvas1->GetCanvas();
	
	//Click is given in pixel coordinates
	double x =Can->AbsPixeltoX(px);
	double y =Can->AbsPixeltoY(py);
	
	// Get the user input sigmas from sliders
	sigmaX=rangeX*fHslider1->GetPosition()/Nslide;
	sigmaY=rangeY*fHslider2->GetPosition()/Nslide;
	if(!fCheckY->GetState())sigmaY=sigmaX;

	if (event == kButton1Double){
		Fit2DGaus(x,y);
	}
}


void jFittingFrame2D::DrawHelpers(double x, double y){
	
	fCanvas1->GetCanvas()->cd();
	TIter next(gPad->GetListOfPrimitives());
	TObject* obj;
	while ((obj = next())) {
		if (obj->InheritsFrom(TBox::Class()) || 
			obj->InheritsFrom(TLine::Class()) || 
			obj->InheritsFrom(TMarker::Class())) {
			gPad->GetListOfPrimitives()->Remove(obj);
			delete obj;  // Optional: also delete to free memory
		}
	}
	gPad->Modified();
	gPad->Update();
	
	TMarker* mark = new TMarker(x, y, kFullCross);  // kFullCross = cross style
	mark->SetMarkerSize(2.0);  // Adjust size as needed
	mark->SetMarkerColor(kGreen);
	mark->Draw("SAME");

	TBox* box = new TBox(x-sigmaX*2,y-sigmaY*2,x+sigmaX*2,y+sigmaY*2);
	box->SetFillStyle(0);       // No fill
	box->SetLineColor(kGreen);    // Red border
	box->SetLineStyle(3);       // Dotted line
	box->Draw("SAME");
	
	gPad->Modified();
	gPad->Update();
}

void jFittingFrame2D::Fit2DGaus(double x, double y){
	if(!fHist){return;}
	
	double h=FindLocalMax(fHist,x,y);
	
	g2->SetRange(x-sigmaX*2,y-sigmaY*2,x+sigmaX*2,y+sigmaY*2);
	g2->SetParameters(h,x,y,sigmaX,sigmaY,h*0.01);
	g2->SetParLimits(0,h*0.3,h*1.2);
	g2->SetParLimits(1,x-sigmaX,x+sigmaY);
	g2->SetParLimits(2,y-sigmaX,y+sigmaY);
	g2->SetParLimits(3,sigmaX*0.2,sigmaY*2);
	g2->SetParLimits(4,sigmaX*0.2,sigmaY*2);
	g2->SetParLimits(5,0,h*0.5);

// 	fHist->Fit(g2,"RQ");
	fHist->Fit(g2,"R");
	
	double X=g2->GetParameter(1);
	double Y=g2->GetParameter(2);
	
	cout<<endl<<"Local Max  x,y = "<<x<<", "<<y<<endl;
	cout<<"Fit Result x,y = "<<X<<", "<<Y<<endl;

	DrawHelpers(x,y);
	
	gPad->Update();
}



