#include "j_extra_guitools.h"

////////////////////////////////////////////////////////////////

jScale::jScale() : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),gg(0),IsLocked(0){
TVirtualPad* hold=gPad;
	SetWindowName("jScale");
	SetCleanup(kDeepCleanup);
	
    FontStruct_t ft =jEnv::GetFont();

	TGLayoutHints* ExpandX= new TGLayoutHints(kLHintsExpandX,5,5,3,2);
	
	TGHorizontalFrame* inputframe = new TGHorizontalFrame(this);
		fCanvas1 = new CCframe("Embedded1", inputframe, 100, 100);
        fCanvas1->Connect("NewObject()","jScale",this,"NewInput()");
		inputframe->AddFrame(fCanvas1);
		fCanvas2 = new CCframe("Embedded2", inputframe, 100, 100);
        fCanvas2->SetClass(TGraph::Class());
        fCanvas2->Connect("NewObject()","jScale",this,"NewInput()");
		inputframe->AddFrame(fCanvas2);
            
        lockbutton = new TGTextButton(inputframe,"  Lock  ");
        lockbutton->SetFont(ft);
        lockbutton->Connect("Clicked()","jScale",this,"Lock()");	
		inputframe->AddFrame(lockbutton,new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1));
        
	this->AddFrame(inputframe,ExpandX);
	
    
    result= new TRootEmbeddedCanvas("scaledhistcan",this,600,400);
		result->GetCanvas()->SetMargin(0.12,0.04,0.12,0.05);
// 		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ClickPeakDrawConnect(Int_t,Int_t,Int_t,TObject*)");
// 		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ToolTipHide()");//added because this embedded canvas put tooltip at wrong coordinates on screen

	this->AddFrame(result,ExpandX);
    
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
    
    
    
	fCanvas1->CFriends.push_back(fCanvas2->GetCanvas());
	fCanvas1->CFriends.push_back(result->GetCanvas());
	fCanvas2->CFriends.push_back(fCanvas1->GetCanvas());
	fCanvas2->CFriends.push_back(result->GetCanvas());
	
gPad=hold;
}


void jScale::NewInput(){
    TH1* H=fCanvas1->Hist();
    TGraph* G=(TGraph*)fCanvas2->Object();
    
    if(G){
        if(gg)delete gg;
        gg=(TGraph*)G->Clone();
    }
    
    if(IsLocked) return;
    
//     cout<<endl<<H<<endl<<gg<<endl;
    if(HType(H)&&gg&&HType(H)<3){
        stringstream nn;
        nn<<H->GetName()<<"x"<<gg->GetName();
        TH1* scaled=(TH1*)H->Clone(nn.str().c_str());
        scaled->Reset();
        bool Y=(HType(H)==2);
        int NX=H->GetNbinsX();
        int ny=0;
        int NY=0;
        if(Y){
            ny=1;
            NY=H->GetNbinsY();
        }
        
        for(int x=1;x<=NX;x++){
            double efX=gg->Eval(H->GetXaxis()->GetBinCenter(x));
            
            for(int y=ny;y<=NY;y++){
                int bin=H->GetBin(x,y);
                double n=H->GetBinContent(bin);
                double e=H->GetBinError(bin);
                double efY=1;
                if(Y){
                    efY=gg->Eval(H->GetYaxis()->GetBinCenter(y));
                }
                double scale=1/(efY*efX);
                scaled->SetBinContent(bin,n*scale);
                scaled->SetBinError(bin,e*scale);
            }
        }
        
//         Draw new results with and adjust axis
        TVirtualPad* hold=gPad;
        result->GetCanvas()->cd();
            hformat(scaled,0);
            scaled->DrawCopy("hiscol");
            delete scaled;
//             gPad->Update();
//             G->DrawClone("al");
        result->GetCanvas()->Modified();
        result->GetCanvas()->Update();
        gPad=hold;
        stringstream ss;
        ss<<"jScale : "<<H->GetName()<<" x "<<gg->GetName();
        SetWindowName(ss.str().c_str());
    }
}


void jScale::Lock(){
    IsLocked=!IsLocked;
    if(IsLocked){
        lockbutton->SetText("Unlock");
        lockbutton->SetTextColor(2);
        lockbutton->SetState(kButtonDown);
    }else{
        lockbutton->SetText("  Lock  ");
        lockbutton->SetTextColor(1);
        lockbutton->SetState(kButtonUp);
        NewInput();
    }
}


////////////////////////////////////////////////////////////////

jEval::jEval() : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),gg(0),GG(0),IsLocked(0){
TVirtualPad* hold=gPad;
    SetWindowName("jEval");
    SetCleanup(kDeepCleanup);

    FontStruct_t ft =jEnv::GetFont();


    fCanvas1 = new CCframe("Embedded1", this, 100, 100);
    fCanvas1->SetClass(TGraph::Class());
    fCanvas1->Connect("NewObject()","jEval",this,"NewInput()");
    this->AddFrame(fCanvas1);
        
    lockbutton = new TGTextButton(this,"  Lock  ");
    lockbutton->SetFont(ft);
    lockbutton->Connect("Clicked()","jEval",this,"Lock()");	
    this->AddFrame(lockbutton,new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1));

    fTeh1 = new TGTextEntry(this, new TGTextBuffer(4));
    fTeh1->SetDefaultSize(50,25);
    fTeh1->SetAlignment (kTextRight);
//     fTeh1->Connect("ReturnPressed()", "jEval", this,"Eval()");
//     fTeh1->Connect("TabPressed()", "jEval", this,"Eval()");
    fTeh1->Connect("TextChanged(char*)", "jEval", this,"Eval(char*)");
    this->AddFrame(fTeh1,new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1));
    
    fTeh2 = new TGTextEntry(this,new TGTextBuffer(6));
    fTeh2->SetDefaultSize(100,25);
    fTeh2->SetAlignment (kTextRight);
    this->AddFrame(fTeh2,new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1));
    
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
    
gPad=hold;
}


void jEval::NewInput(){
    TGraph* G=(TGraph*)fCanvas1->Object();
    
    if(G){
        if(gg)delete gg;
        gg=(TGraph*)G->Clone();
    }
    
    if(IsLocked) return;
    
    if(gg){
        if(GG)delete GG;
        GG=(TGraph*)gg->Clone();
        stringstream ss;
        ss<<"jEval : "<<gg->GetName();
        SetWindowName(ss.str().c_str());
    }
}


void jEval::Lock(){
    IsLocked=!IsLocked;
    if(IsLocked){
        lockbutton->SetText("Unlock");
        lockbutton->SetTextColor(2);
        lockbutton->SetState(kButtonDown);
    }else{
        lockbutton->SetText("  Lock  ");
        lockbutton->SetTextColor(1);
        lockbutton->SetState(kButtonUp);
        NewInput();
    }
}

void jEval:: Eval(char* cha){
    stringstream in;
    in<<cha;
    double input;
    in>>input;
    if(GG){
        double Y=GG->Eval(input);
        char buf[32];
        sprintf(buf, "%.5f", Y);
        TGTextBuffer* fTbh2=fTeh2->GetBuffer();
        fTbh2->Clear();	fTbh2->AddText(0, buf);
        fTeh2->SetCursorPosition(fTeh2->GetCursorPosition());
        fTeh2->Deselect();
        gClient->NeedRedraw(fTeh2);
        cout<<endl<<GG->GetName()<<" Eval at "<<input<<" = "<<Y<<flush;
    }
}



////////////////////////////////////////////////////////////////

jAngleAngel::jAngleAngel(TH1* fH) : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),fHistHigh(0),fHistLow(0),fHist(0),fCurrentCutG(nullptr), fCutSetting(false),fCutActive(false){
TVirtualPad* hold=gPad;

    SetWindowName("jAngleAngel");
    SetCleanup(kDeepCleanup);
	Stop.Start();
	
	TGHorizontalFrame* topbuttons = new TGHorizontalFrame(this);            

		jHistCapButton *CaptureButton = new jHistCapButton(topbuttons," Capture Hist ");
		CaptureButton->Connect("NewHist(TH1*)","jAngleAngel",this,"SetCapture(TH1*)");	
		topbuttons->AddFrame(CaptureButton);
	// 	AddFrame(CaptureButton);
		
		fButton = new TGTextButton(topbuttons, "Set Cut");
		topbuttons->AddFrame(fButton);
		fButton->Connect("Clicked()", "jAngleAngel", this, "StartCutButtonPressed()");

		fButtonEnd = new TGTextButton(topbuttons, "Finish Cut");
		topbuttons->AddFrame(fButtonEnd);
		fButtonEnd->Connect("Clicked()", "jAngleAngel", this, "FinaliseCut()");
		fButtonEnd->SetState(kButtonDisabled);
		
		fButtonUnuse = new TGTextButton(topbuttons, "Remove Cut");
		topbuttons->AddFrame(fButtonUnuse);
		fButtonUnuse->Connect("Clicked()", "jAngleAngel", this, "UnUseCut()");
		fButtonUnuse->SetState(kButtonDisabled);
		
	AddFrame(topbuttons,new TGLayoutHints(kLHintsCenterX, 1, 1, 1, 1));
	
	// Create a button and add it to the main frame
	
	fCanvas1 = new TRootEmbeddedCanvas("anglecan1",this,600,400);
    AddFrame(fCanvas1,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY, 1, 1, 1, 1));
	
    
//     fCanvas1->ToggleEventStatus(); // Show event info on screen apparently, not tested, could be useful
    fCanvas1->GetCanvas()->Connect("RangeChanged()", "jAngleAngel", this, "NewRange()");
	fCanvas1->GetCanvas()->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)");

    fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jAngleAngel", this,
                    "HandleEvent(Int_t,Int_t,Int_t,TObject*)");
	
	fHslider = new TGHSlider(this, 360, kSlider2);
	fHslider->Connect("PositionChanged(Int_t)", "jAngleAngel", this, "SliderChange()");
	fHslider->Connect("Released()", "jAngleAngel", this, "SliderRelease()");
    AddFrame(fHslider,new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));

	TGHorizontalFrame* buttons = new TGHorizontalFrame(this);            

		TGTextButton *MakeButton = new TGTextButton(buttons," Make Hist ");
		MakeButton->Connect("Clicked()","jAngleAngel",this,"MakeHist()");	
		buttons->AddFrame(MakeButton);
		
		MakeButton = new TGTextButton(buttons," Make Hist90 ");
		MakeButton->Connect("Clicked()","jAngleAngel",this,"MakeHist90()");	
		buttons->AddFrame(MakeButton);
	AddFrame(buttons,new TGLayoutHints(kLHintsCenterX, 1, 1, 1, 1));
	
    
	fLine.SetLineColor(2);
	Nl=20;
    
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
	
	SetNewHist(fH);
	
	lock=false;
	sliderpos=-1;
    
    gPad=hold;
}

jAngleAngel::~jAngleAngel(){
    TQObject::Disconnect(this);
}
void jAngleAngel::SetNewHist(TH1 *fH){
	if(!fH)return;
	if(!fH->InheritsFrom("TH2"))return;
	
    if(fHistLow&&fHistHigh!=fHistLow){delete fHistLow;fHistLow=0;}
    if(fHistHigh){delete fHistLow;fHistLow=0;}
    
	fHistHigh=(TH2*)fH->Clone("fHistHigh");
	hformat(fHistHigh);
    
    if(fHistHigh->GetNcells()>1048584){//1024^2 + 8 overflows
        fHistLow=fHistHigh->Rebin2D(floor(fHistHigh->GetNbinsX()/500.),floor(fHistHigh->GetNbinsY()/500.),"fHistLow");
    }else{
        fHistLow=fHistHigh;
    }
    
    fHist=fHistHigh;
	
	fCanvas1->GetCanvas()->cd();
	fHist->Draw("col");
// 	hformat(fHist);
	gPad->Update();
	DoLines();	
}


void jAngleAngel::NewRange(){
	if(!fHist||lock)return;
	DoLines();
}


void jAngleAngel::SetCapture(TH1* fH){
	if(fHist==fH)return;
    lock=true;
    SetNewHist(fH);
    lock=false;
};

// Lots of checks to try and slow the thing down
void jAngleAngel::SliderChange(){

	if(!fHist||sliderpos==fHslider->GetPosition()||lock)return;
	if(Stop.RealTime()<0.2){
		Stop.Start(kFALSE);	
		return;
	}
	Stop.Start();
	lock=true;
	
	if(fHist==fHistHigh&&fHistLow!=fHistHigh){
        TAxis *X=fHist->GetXaxis();
        TAxis *Y=fHist->GetYaxis();
		fHist=fHistLow;
        TAxis *x=fHist->GetXaxis();
        TAxis *y=fHist->GetYaxis();
    
        x->SetRange(x->FindBin(X->GetBinCenter(X->GetFirst())),x->FindBin(X->GetBinCenter(X->GetLast())));
        y->SetRange(y->FindBin(Y->GetBinCenter(Y->GetFirst())),y->FindBin(Y->GetBinCenter(Y->GetLast())));         
        
		fCanvas1->GetCanvas()->cd();
		fHist->Draw("col");
	}
	DoLines();

	lock=false;
};

void jAngleAngel::SliderRelease(){
	if(fHist==fHistLow&&fHistLow!=fHistHigh){
		fHist=fHistHigh;
		fCanvas1->GetCanvas()->cd();
        lock=true;
		fHist->Draw("col");
        lock=false;
	}
	DoLines();
};

// No checks just do
void jAngleAngel::DoLines(){

	sliderpos=fHslider->GetPosition();

	TCanvas *can=fCanvas1->GetCanvas();
	can->cd();
	obj_removeall(TLine::Class(),can);
// 	obj_removeall(TMarker::Class(),can);
	
	double Angle=TMath::Pi()*fHslider->GetPosition()/360.0;
	
	TAxis *X=fHist->GetXaxis();
	TAxis *Y=fHist->GetYaxis();
	
	// The currently drawn limits 
	double y0=Y->GetBinLowEdge(Y->GetFirst());
	double y1=Y->GetBinLowEdge(Y->GetLast()+1);
	double x0=X->GetBinLowEdge(X->GetFirst());
	double x1=X->GetBinLowEdge(X->GetLast()+1);
	double xr=(x1-x0);
// 	double yr=(y1-y0);
	
	// The midpoint
	double yn=(y0+y1)*0.5;
	double xn=(x0+x1)*0.5;
	
	// Gradient y/x;
// 	double g=yr/xr;
	double g=Y->GetBinWidth(1)/X->GetBinWidth(1);
	
	double wg=(double)fCanvas1->GetWidth()/fCanvas1->GetHeight();
	// The extra wg factor is for nice spacing when drawing, but not actually used in the angle ratio
	
	// Division for line spacing in x
	double dx=xr/Nl;
	double nl=0.5;

	double sn=sin(Angle);
	double cs=cos(Angle);
	double tn=tan(Angle);
	
// 	TMarker mark;
// 	mark.SetMarkerStyle(20);
	
// 	cout<<"."<<flush;
	while(nl<Nl){
		double YY=nl*dx*cs*g*wg;
		double XX=nl*dx*sn;
		YY+=yn;
		XX+=xn;
// 		mark.DrawMarker(XX,YY);
		
		double xb=x1;
		double yb=YY-(xb-XX)*g*tn;
		if(tn>0&&yb<y0){
			yb=y0;
			xb=XX-(yb-YY)/(g*tn);
		}else if(tn<0&&yb>y1){
			yb=y1;
			xb=XX-(yb-YY)/(g*tn);
		}
		if(yb>y1||yb<y0){
			break;
		}
// 		mark.DrawMarker(xb,yb);
		
		double xt=x0;
		double yt=YY-(xt-XX)*g*tn;	
		if(tn>0&&yt>y1){
			yt=y1;
			xt=XX-(yt-YY)/(g*tn);
		}else if(tn<0&&yt<y0){
			yt=y0;
			xt=XX-(yt-YY)/(g*tn);
		}
// 		mark.DrawMarker(xt,yt);
		
		fLine.DrawLine(xb,yb,xt,yt);
		if(nl<0){
			nl--;
		}
		nl=-nl;
	}
	can->Update();
};


// No checks just do
void jAngleAngel::MakeHist(double offset){
    if(!fHistHigh)return;
    
	double Angle=TMath::Pi()*fHslider->GetPosition()/360.0;
	Angle+=offset;
	
	TAxis *X=fHistHigh->GetXaxis();
	TAxis *Y=fHistHigh->GetYaxis();
	
	// The currently drawn limits 
	double y0=Y->GetBinLowEdge(Y->GetFirst());
	double y1=Y->GetBinLowEdge(Y->GetLast()+1);
	double x0=X->GetBinLowEdge(X->GetFirst());
	double x1=X->GetBinLowEdge(X->GetLast()+1);
	double yr=(y1-y0);

	
	// Gradient y/x;
// 	double g=yr/xr;
	double g=Y->GetBinWidth(1)/X->GetBinWidth(1);
	
	
	double tn=tan(Angle);	

	double xlow=x0+yr/(tn*g);
	double xhigh=x1;
	if(tn>0){
		xlow=x0;
		xhigh=x1+yr/(tn*g);
	}

	// A whole lot of guff to calculate spreading the counts over bins
	double w=X->GetBinWidth(1);
	double range=1;
	TGraph grh;
	double t=1/abs(tn);
	if(t>1){t=1/t;
		double dx=(1-t)/t;
		range=w*(0.5*dx+1);
		grh.SetPoint(1,-range,0);
		grh.SetPoint(2,w*(-0.5*dx),(1-t)/(dx*w));
		grh.SetPoint(3,w*(0.5*dx),(1-t)/(dx*w));
		grh.SetPoint(4,range,0);
	}else{
		range=w*(0.5*(1-t)+t);
		grh.SetPoint(1,-range,0);
		grh.SetPoint(2,w*(-0.5*(1-t)),1/w);
		grh.SetPoint(3,w*(0.5*(1-t)),1/w);
		grh.SetPoint(4,range,0);
	}
	grh.SetPoint(0,-range*10,0);
	grh.SetPoint(5,range*10,0);
	
	TH1D smth("smth","smth",100,-range,range);
	for(int b=1;b<=smth.GetNbinsX();b++){
		smth.SetBinContent(b,grh.Eval(smth.GetBinCenter(b)));
	}
	smth.Scale(1.0/smth.Integral());
	TAxis *sax=smth.GetXaxis();
	double smwdth=sax->GetBinWidth(1);
	
	
	TH1D ret("jAngleAngelRet","jAngleAngelRet",fHistHigh->GetNbinsX()*2,xlow,xhigh);
	TAxis *ax=ret.GetXaxis();
	
	int brange=ceil(range/ret.GetBinWidth(1));

	for(int x=1;x<=fHistHigh->GetNbinsX();x++){
		for(int y=1;y<=fHistHigh->GetNbinsY();y++){
			
			double XX=X->GetBinCenter(x);
			double YY=Y->GetBinCenter(y);
			
			if(fCutActive){
				if(fCurrentCutG){
					if(!fCurrentCutG->IsInside(XX,YY))continue;
				}
			}
			
			double A=XX+(YY-y0)/(g*tn);
// 			ret.Fill(A,fHistHigh->GetBinContent(x,y));	
			
			double C=fHistHigh->GetBinContent(x,y);
			int B=ax->FindBin(A);
			for(int b=B-brange;b<=B+brange;b++){
				double smin=ax->GetBinLowEdge(b)-A;				
				double smax=ax->GetBinLowEdge(b+1)-A;	
				int bmin = sax->FindBin(smin);		
				int bmax = sax->FindBin(smax);		
				double frc = smth.Integral(bmin,bmax);
				//// These corrections dont actuall make the individual frc values more accurate
				//// They just stop the sum being greater than 1
				frc -= smth.GetBinContent(bmin)*(smin-sax->GetBinLowEdge(bmin))/smwdth;
				frc -= smth.GetBinContent(bmax)*(sax->GetBinUpEdge(bmax)-smax)/smwdth;

				ret.Fill(ax->GetBinCenter(b),C*frc);
			}
		}
	}
	
	new TCanvas();
	gPad->Update();
	ret.DrawCopy("hist");
}



void jAngleAngel::HandleEvent(Int_t event, Int_t px, Int_t py, TObject *selected) {
	
	if (!fCutSetting) return;
	
    TCanvas *canvas = fCanvas1->GetCanvas();
	
	if (!fCurrentCutG) {
		fCurrentCutG = new TGraph();
		fCurrentCutG->SetName("TRUEGRAPH");	
	}
	TGraph *cut=fCurrentCutG;
	
	switch (event) {
	case kButton1Down:
		{
			cut->SetPoint(cut->GetN(), gPad->AbsPixeltoX(px), gPad->AbsPixeltoY(py));
			gPad->Modified();
			gPad->Update();
			break;
		}
	case kButton1Up:
		{
			if ( cut->GetN() == 1) {
				canvas->cd();
				cut->Draw("L");
			}
			canvas->Update();	
			break;
		}
// 	case kButton1Double:  // Never got doubleclick working, it finished the TGraph/TCut but some other TCanvas function then changes the graph as it "owns" them, couldnt track it down
	case kKeyPress:
		{
			if(py!=kKey_Space) break;
			FinaliseCut();
			break;
		}
	}
}

void jAngleAngel::StartCutButtonPressed() {
    // Reset the TCutG and enable cut modifications
	if (fCurrentCutG) {
		RemoveGraphs();
			fCurrentCutG = nullptr;
    }
    fCutSetting = true;
	fButton->SetState(kButtonDisabled);
	fButtonEnd->SetState(kButtonUp);
	fButtonUnuse->SetState(kButtonUp);
}


void jAngleAngel::RemoveGraphs() {
    TCanvas *canvas = fCanvas1->GetCanvas();
	TIter next(canvas->GetListOfPrimitives());
	TObject *obj;
	while ((obj = next())) {
		if (obj->InheritsFrom(TGraph::Class())) {
			canvas->GetListOfPrimitives()->Remove(obj);
			delete obj;
		}
	}
	fCutActive=false;
	canvas->Modified();
	canvas->Update();
	fButtonUnuse->SetState(kButtonDisabled);
}

void jAngleAngel::FinaliseCut() {

	if(fCurrentCutG){
		TCanvas *canvas = fCanvas1->GetCanvas();
		if ( fCurrentCutG->GetN() > 2) {
			double X,Y;
			fCurrentCutG->GetPoint(0,X,Y);
			fCurrentCutG->SetPoint(fCurrentCutG->GetN(), X,Y);
			fCutActive=true;
		}else{RemoveGraphs();}
		canvas->Update();
	}
		
	// Finalize the cut creation
	fCutSetting = false;
	fButton->SetState(kButtonUp);
	fButtonEnd->SetState(kButtonDisabled);
}

void jAngleAngel::UnUseCut() {
	RemoveGraphs();
	fCutActive=false;
	fCutSetting = false;
	
	fButton->SetState(kButtonUp);
	fButtonEnd->SetState(kButtonDisabled);
}

////////////////////////////////////////////////////////////////

j2DPeakFit::j2DPeakFit(TH1* fH,double sig) : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),fHist(0),sigma(sig){
// TVirtualPad* hold=gPad;
    SetWindowName("j2DPeakFit");
    SetCleanup(kDeepCleanup);


	fCanvas1 = new TRootEmbeddedCanvas("fit2can1",this,600,400);
    AddFrame(fCanvas1,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY, 1, 1, 1, 1));
    
    fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "j2DPeakFit", this,"Fit2DPeak(Int_t,Int_t,Int_t,TObject*)");

    
    TGHorizontalFrame* buttons = new TGHorizontalFrame(this);       
    
        jHistCapButton *CaptureButton = new jHistCapButton(buttons,"    Capture Hist    ");
        CaptureButton->Connect("NewHist(TH1*)","j2DPeakFit",this,"SetNewHist(TH1*)");	
        buttons->AddFrame(CaptureButton);

        TGTextButton *MakeButton = new TGTextButton(buttons,"       SaveXY       ");
        MakeButton->Connect("Clicked()","j2DPeakFit",this,"SaveXY()");	
        buttons->AddFrame(MakeButton);

        MakeButton = new TGTextButton(buttons,"   CalibrateAlpha   ");
        MakeButton->Connect("Clicked()","j2DPeakFit",this,"CalibrateAlpha()");	
        buttons->AddFrame(MakeButton);
        
        MakeButton = new TGTextButton(buttons,"   Reset   ");
        MakeButton->Connect("Clicked()","j2DPeakFit",this,"Reset()");	
        buttons->AddFrame(MakeButton);
    
    AddFrame(buttons,new TGLayoutHints(kLHintsCenterX, 1, 1, 1, 1));
    
    g2 = new TF2("g2","[0]*exp(-0.5*pow((x-[1])/[3],2))*exp(-0.5*pow((y-[2])/[4],2))");
    g2->SetParNames("Height","X0","Y0","Xsig","Ysig");
    g2->SetContour(10);
    
    lincal = new TF1("lincal","(5485.56-x*[0])/[1]");
    lincal->SetParNames("CalX","CalY");
    lincal->SetParameters(4,4);
    
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
    
	SetNewHist(fH);
}
// 
j2DPeakFit::~j2DPeakFit(){
    TQObject::Disconnect(this);
}

void j2DPeakFit::SetNewHist(TH1 *fH){
	if(!fH)return;
	if(!fH->InheritsFrom("TH2"))return;
    
    if(fHist)delete fHist;
	fHist=(TH2*)fH->Clone("fHist2Dfit");
	hformat(fHist);

    
	fCanvas1->GetCanvas()->cd();
	fHist->Draw("col");
	gPad->Update();
}

void j2DPeakFit::Fit2DPeak(Int_t event, Int_t px, Int_t py, TObject *selected_ob){

	if(!fHist){return;}
	if(event == kMouseLeave){return;}
	TCanvas* Can=(TCanvas*)fCanvas1->GetCanvas();
	
	//Click is given in pixel coordinates
	double x =Can->AbsPixeltoX(px);
	double y =Can->AbsPixeltoY(py);

	if (event == kButton1Double){
//         cout<<endl<<x<<" "<<y<<endl;
// 		TH1* fHist=hist_capture(Can);
		if(!fHist) return;
        if(HType(fHist)!=2) return;
		
        double h=fHist->GetBinContent(fHist->GetXaxis()->FindBin(x),fHist->GetXaxis()->FindBin(y));
        g2->SetRange(x-sigma*2,y-sigma*2,x+sigma*2,y+sigma*2);
        g2->SetParameters(h,x,y,sigma,sigma);
		g2->SetParLimits(0,h*0.5,h*1.5);
		g2->SetParLimits(1,x-sigma,x+sigma);
		g2->SetParLimits(2,y-sigma,y+sigma);
		g2->SetParLimits(3,sigma*0.5,sigma*2);
		g2->SetParLimits(4,sigma*0.5,sigma*2);

        fHist->Fit(g2,"RQ");
        
		X=g2->GetParameter(1);
		Y=g2->GetParameter(2);
		
// 		Can->GetCanvas()->Modified();
// 		Can->GetCanvas()->Update();
	}
}

void j2DPeakFit::CalibrateAlpha(){
    TGraph tmp(saveX.size(),&saveX[0],&saveY[0]);
    ((TGraph*)tmp.DrawClone("al"))->Fit(lincal);
//     tmp.Fit(lincal);
};

////////////////////////////////////////////////////////////////

jIntegrator::jIntegrator(TH1* fH) : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),fHist(0),first(true){
// TVirtualPad* hold=gPad;
    SetWindowName("jIntegrator");
    SetCleanup(kDeepCleanup);

	fCanvas1 = new TRootEmbeddedCanvas("fit2can1",this,600,400);
    AddFrame(fCanvas1,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY, 1, 1, 1, 1));
    
    fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jIntegrator", this,"Integrate(Int_t,Int_t,Int_t,TObject*)");

	jHistCapButton *CaptureButton = new jHistCapButton(this,"    Capture Hist    ");
	CaptureButton->Connect("NewHist(TH1*)","jIntegrator",this,"SetNewHist(TH1*)");	
	AddFrame(CaptureButton);

	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
    
	SetNewHist(fH);
}
// 
jIntegrator::~jIntegrator(){
    TQObject::Disconnect(this);
}

void jIntegrator::SetNewHist(TH1 *fH){
	if(!fH)return;
	if(!fH->InheritsFrom("TH1"))return;
    
    if(fHist)delete fHist;
	fHist=(TH1*)fH->Clone("fHistInt");
	hformat(fHist);

	fCanvas1->GetCanvas()->cd();
	fHist->Draw("col");
	gPad->Update();
}


void jIntegrator::Integrate(Int_t event, Int_t px, Int_t py, TObject *selected_ob){

	if(!fHist){return;}
	if(event == kMouseLeave){return;}
	TCanvas* Can=(TCanvas*)fCanvas1->GetCanvas();
	
	//Click is given in pixel coordinates
	double x =Can->AbsPixeltoX(px);

	if (event == 1){// Left click
		if(!fHist) return;
        if(HType(fHist)!=1) return;
		
		if(first){
			X1=fHist->GetXaxis()->FindBin(x);
			x1=x;
			first=false;
			return;
		}else{
			X2=fHist->GetXaxis()->FindBin(x);
			x2=x;
			first=true;
			cout<<"Integral from "<<x1<<" ("<<X1<<") to "<<x2<<" ("<<X2<<") = "<<fHist->Integral(X1,X2)<<endl;
		}
	}
}


////////////////////////////////////////////////////////////////

jCompCanvas::jCompCanvas(TH1 *fH, Option_t * option ):TCanvas(),ReCol(0),ReColI(0),ColInit(0),CurrentPad(this){
	if(fH){
		this->cd();
		fH->Draw(option);
	}
	this->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jCompCanvas",this,"MouseEvent(Int_t,Int_t,Int_t,TObject*)");
		
};
	
	
jCompCanvas::~jCompCanvas(){
	TQObject::Disconnect(this);
}


void jCompCanvas::MouseEvent(Int_t e,Int_t x,Int_t y,TObject* ob){

// 		cout<<e<<"  "<<x<<"  "<<y<<"  "<<ob<<endl;
// 	cout<<ob->ClassName()<<endl;
	
	if(ob->InheritsFrom(TPad::Class())){
		if(CurrentPad!=ob)CurrentPad=(TPad*)ob;
		
		if(e==kButton1){
			ResetView();
			CurrentPad->Modified();
			CurrentPad->Update();
		}
	}else if(ob->InheritsFrom(TH1::Class())){
		
// 	cout<<ob->ClassName()<<endl;
		
		TH1* h=(TH1*)ob;
		if(e==kButton1Up){
			h->SetLineColor(this->Colour());
		}
		HighlightHist(h);
		CurrentPad->Modified();
		CurrentPad->Update();
	}if(ob->InheritsFrom(TGraph::Class())){
		
// 	cout<<ob->ClassName()<<endl;
		
		TGraph* g=(TGraph*)ob;
// 		if(ob->InheritsFrom(TGraph::Class()))h=((TGraph*)ob)->GetHistogram();
	
		HighlightGraph(g);
		CurrentPad->Modified();
		CurrentPad->Update();
	}
};
	
void jCompCanvas::ResetView(){
// 	cout<<endl<<"RESET"<<endl;
	
	SetTitle("");
	
	TObjLink *lnk = CurrentPad->GetListOfPrimitives()->FirstLink();
	while (lnk) {
		if(lnk->GetObject()->InheritsFrom(TH1::Class())){
			TH1* h=(TH1*)lnk->GetObject();
			h->SetLineWidth(1);
			h->SetFillStyle(0);
			if(!ColInit){h->SetLineColor(this->Colour());}  // Initial colouring, so not needed before drawing (doesnt work for multipad canvas)
		}
		if(lnk->GetObject()->InheritsFrom(TGraph::Class())){
			TGraph* h=(TGraph*)lnk->GetObject();
			h->SetLineWidth(1);
			h->SetFillStyle(0);
			if(!ColInit){h->SetLineColor(this->Colour());}
		}
		lnk = lnk->Next();
	}
	ColInit=true;
}

UShort_t jCompCanvas::ColBase[6]={kRed,kBlue,kGreen,kMagenta,kCyan,kYellow};

UShort_t jCompCanvas::Colour(UShort_t Col){
	if(!Col){ // if given an input its just a filter for the worst colors i.e. dont have white lines
		Col=ColBase[ReColI]+ReCol;
		ReColI++;
		if(ReColI==6){ReColI=0;ReCol++;}
	}
	if(Col==0||Col==10||Col==19)Col++;
	return Col;
}

void jCompCanvas::HighlightHist(TH1* h){
// 	cout<<endl<<"HIGHLIGHT"<<endl;
	ResetView();
	
	SetTitle(h->GetTitle());
	
	h->SetLineColor(this->Colour(h->GetLineColor())); // Filter the colors
	h->SetLineWidth(4);
	h->SetFillColor(h->GetLineColor());
	h->SetFillStyle(3244);
}
void jCompCanvas::HighlightGraph(TGraph* g){ // Filter the colors
// 	cout<<endl<<"HIGHLIGHT"<<endl;
	ResetView();
	
	SetTitle(g->GetTitle());
	
	g->SetLineColor(this->Colour(g->GetLineColor()));
	g->SetLineWidth(4);
	g->SetFillColor(g->GetLineColor());
	g->SetFillStyle(3244);
}

