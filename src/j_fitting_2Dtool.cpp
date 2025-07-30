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
		
	Resize(800,850);
    }

jFittingTool2D::~jFittingTool2D() {
	// Properly delete child widgets
	Cleanup();
}


////////////////////////////////////////////////////////////////

jFittingFrame2D::jFittingFrame2D(TGWindow * parent,TH2* fH,double sigx,double sigy) : TGVerticalFrame(parent, 100, 100),
	fHist(new TH2I()),sigmaX(sigx),sigmaY(sigy),rangeX(1.0),rangeY(1.0), TextSlideBlock(false), Nslide(1600)
{
// TVirtualPad* hold=gPad;


	fCanvas1 = new TRootEmbeddedCanvas("fit2Dcanvas1",this,600,400);
    fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jFittingFrame2D", this,"Fit2DPeak(Int_t,Int_t,Int_t,TObject*)");
	fCanvas1->GetCanvas()->SetMargin(0.14,0.02,0.14,0.02);
	
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
		
		fCheckRes = new TGCheckButton(buttons);// A tick box with hover text belonging to a parent frame
		fCheckRes->SetState(kButtonUp);
		fCheckRes->SetToolTipText("Draw Fit-Residuals in a new window.");

        buttons->AddFrame(fCheckRes);
    
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
		fCheckY->SetToolTipText("Enable separate Y resolution.");
		fCheckY->Connect("Clicked()","jFittingFrame2D",this,"EnableSigmaY()");//Link it signal to its slot
		
		SlideY->AddFrame(SlideYlab,CentY);
		SlideY->AddFrame(fTextEntry2,CentY);
		SlideY->AddFrame(fHslider2, ExpX);
		SlideY->AddFrame(fCheckY,CentY);
		
	AddFrame(SlideY, ExpX);

	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
	
    gf2 = new TF2("gf2","[5]+[0]*exp(-0.5*pow((x-[1])/[3],2))*exp(-0.5*pow((y-[2])/[4],2))");
    gf2->SetParNames("Height","X0","Y0","Xsig","Ysig","Pol0");
    gf2->SetContour(15);
	
	//Only one sigma, dont forget to fix par 4=0;
    gf1 = new TF2("gf1","[5]+[0]*exp(-0.5*pow((x-[1])/[3],2))*exp(-0.5*pow((y-[2])/[3],2))+[4]");
    gf1->SetParNames("Height","X0","Y0","Sigma","NULL","Pol0");
    gf1->SetContour(15);

	gf=gf2;
	
	SetNewHist(fH);
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
		
		rangeX=0.1*(fH->GetXaxis()->GetXmax()-fH->GetXaxis()->GetXmin());
		rangeY=0.1*(fH->GetYaxis()->GetXmax()-fH->GetYaxis()->GetXmin());
		TextSlideBlock=true;
		
		double SSX=0.1*rangeX;
		double SSY=0.1*rangeY;
		if(sigmaX)SSX=sigmaX;
		if(sigmaY)SSY=sigmaY;
		
		fHslider1->SetPosition(Nslide*SSX/rangeX);
		fHslider2->SetPosition(Nslide*SSY/rangeY);
		
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
	
	if (event == kButton1Double){
		TCanvas* Can=(TCanvas*)fCanvas1->GetCanvas();
		
		//Click is given in pixel coordinates
		double x =Can->AbsPixeltoX(px);
		double y =Can->AbsPixeltoY(py);
		
		
		// Get the user input sigmas from sliders
		sigmaX=rangeX*fHslider1->GetPosition()/Nslide;
		sigmaY=rangeY*fHslider2->GetPosition()/Nslide;
		gf=gf2;
		if(!fCheckY->GetState()){
			sigmaY=sigmaX;
			gf=gf1;
		}
		
		if(!sigmaX)sigmaX=1;
		if(!sigmaY)sigmaY=1;

		
		Fit2DGaus(x,y);
	}
}


void jFittingFrame2D::DrawHelpers(double x, double y){
	fCanvas1->GetCanvas()->cd();
	gPad->Update();
	
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
	fCanvas1->GetCanvas()->cd();
	gPad->Update();
	
	// sigmaX are inputs taken from sliders 
	
	double h=FindLocalMax(fHist,x,y);
	
	gf->SetRange(x-sigmaX*2,y-sigmaY*2,x+sigmaX*2,y+sigmaY*2);
	gf->SetParameters(h,x,y,sigmaX,sigmaY,h*0.01);
	gf->SetParLimits(0,h*0.3,h*1.2);
	gf->SetParLimits(1,x-sigmaX,x+sigmaY);
	gf->SetParLimits(2,y-sigmaX,y+sigmaY);
	gf->SetParLimits(3,sigmaX*0.2,sigmaY*2);
	gf->SetParLimits(4,sigmaX*0.2,sigmaY*2);
	gf->SetParLimits(5,0,h*0.5);
	
	if(gf==gf1){
		gf->FixParameter(4,0);
	}

// 	fHist->Fit(gf,"RQ");
	fHist->Fit(gf,"R");
	
	double X=gf->GetParameter(1);
	double Y=gf->GetParameter(2);
	
	cout<<endl<<"Local Max  x,y = "<<x<<", "<<y<<endl;
	cout<<"Fit Result x,y = "<<X<<", "<<Y<<endl;

	DrawHelpers(x,y);
	
	gPad->Update();
	
	if(fCheckRes->GetState()){
		DrawResidual(x, y);
	}

}

void jFittingFrame2D::DrawResidual(double x, double y){
	if(!fHist){return;}
	
	double BWx=fHist->GetXaxis()->GetBinWidth(1);
	double BWy=fHist->GetYaxis()->GetBinWidth(1);
	int Bx=fHist->GetXaxis()->FindBin(x);
	int By=fHist->GetYaxis()->FindBin(y);
	int Wx=sigmaX*2/BWx;
	int Wy=sigmaY*2/BWy;
	int gap=3;
	int Of=gap+1+Wy*2;
	double pol0=gf->GetParameter(5);
	
	TH2D* Residuals=new TH2D("Fit2DGausResiduals","Fit2DGausResiduals",1+Wx*2,0,1,Wy*4+2+gap,0,2+(gap*0.5/Wy));
	
	for(int ix=1;ix-1<=Wx*2;ix++){
		int BX=ix+Bx-Wx-1;; 
			
		double xLow  = fHist->GetXaxis()->GetBinLowEdge(BX);
		double xHigh = fHist->GetXaxis()->GetBinUpEdge(BX);
		
		for(int iy=1;iy-1<=Wy*2;iy++){
			int BY=iy+By-Wy-1;
			double bc=fHist->GetBinContent(BX,BY);
			Residuals->SetBinContent(ix,iy+Of,bc);
			
			
			double yLow  = fHist->GetYaxis()->GetBinLowEdge(BY);
			double yHigh = fHist->GetYaxis()->GetBinUpEdge(BY);

			double FunctionIntengral = gf->Integral(xLow, xHigh, yLow, yHigh) /
                         ((xHigh - xLow) * (yHigh - yLow));
			
			Residuals->SetBinContent(ix,iy,bc-FunctionIntengral+pol0);
		}
	}
	
	new TCanvas("","Fit2DGausResiduals",900,1000);
	gPad->Update();
	Residuals->DrawCopy("LEGO2");
// 	Residuals->Draw("SURF1");
	delete Residuals;
}



