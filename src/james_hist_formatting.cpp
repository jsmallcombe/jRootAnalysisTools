#include "james_hist_formatting.h"


void axislab(TH1* HH,string x,string y,string z){
	HH->GetXaxis()->SetTitle(x.c_str());
	if(y==""){
		stringstream ss;
		ss<<"Counts/"<<HH->GetBinWidth(1);
		HH->GetYaxis()->SetTitle(ss.str().c_str());
	}else{
		HH->GetYaxis()->SetTitle(y.c_str());	
	}
	if(z!=""){
		HH->GetZaxis()->SetTitle(z.c_str());	
	}	
}

//Add most common axis label so automated
void axislabelkev(TH1* HH){
	stringstream ss;
	double c=HH->GetXaxis()->GetBinWidth(1);
	ss<<"Counts/";
	if(c!=1)ss<<c<<" ";
	ss<<"keV";	
	axislab(HH,"Energy (KeV)",ss.str());
}

void hformat(TH1* HH,bool setminzero){
	TAxis* ax[3]={HH->GetXaxis(),HH->GetYaxis(),HH->GetZaxis()};
	for(int i=0;i<3;i++){
		ax[i]->SetTicks("+-");
		ax[i]->SetLabelFont(22);
		ax[i]->SetLabelSize(0.045);
		ax[i]->SetTitleFont(22);
		ax[i]->SetTitleSize(0.06);
		ax[i]->SetTitleOffset(0.7);
		ax[i]->SetTickLength(0.015);
		ax[i]->CenterTitle(true);
	}
	ax[1]->SetTitleOffset(-0.7);
	
	HH->SetLineColor(1);
	HH->SetStats(false);
	HH->SetTitle("");
	if(!(HH->InheritsFrom(TH2::Class()))){
		if(setminzero)HH->SetMinimum(0);
	}
}

TCanvas* DrawHformat(TH1* HH,bool setminzero){
	TCanvas* canv=preapre_canvas();
	canv->SetTitle(HH->GetTitle());
	hformat(HH,setminzero);
	draw_corrected_titles(HH);
	return canv;
}



TH1* ExtreemRebin(TH1* target,TH1* data){
	TAxis* tAx=target->GetXaxis();
	TAxis* dAx=data->GetXaxis();

	int j=1;
	for(int i=1;i<=data->GetNbinsX();++i){
		double dBinLower=dAx->GetBinLowEdge(i);
		double dBinUpper=dAx->GetBinUpEdge(i);
		
		double content=data->GetBinContent(i);
		vector<int> overlapedbins;
		
		while(tAx->GetBinLowEdge(j)<=dBinUpper){
			if(j>=target->GetNbinsX())break;
			if(tAx->GetBinUpEdge(j)>=dBinLower)overlapedbins.push_back(j);
			if(tAx->GetBinUpEdge(j)<dBinUpper)j++;else break;
		}
		if(overlapedbins.size()==0)continue;
		
		vector<double> overlaparea;
		double overlapareatotal=0;
		
		for(unsigned int k=0;k<overlapedbins.size();++k){
			int bin=overlapedbins[k];
			double tBinLower=tAx->GetBinLowEdge(bin);
			double tBinUpper=tAx->GetBinUpEdge(bin);
			
			if(tBinLower<dBinLower)tBinLower=dBinLower;
			if(tBinUpper>dBinUpper)tBinUpper=dBinUpper;

			double binarea=tBinUpper-tBinLower;
			overlaparea.push_back(binarea);
			overlapareatotal+=binarea;
		}
		
		if(!(overlapareatotal>0))continue;
		
		for(unsigned int k=0;k<overlapedbins.size();++k){
			int bin=overlapedbins[k];
			double binC=content*overlaparea[k]/overlapareatotal;
			binC+=target->GetBinContent(bin);
			target->SetBinContent(bin,binC);
		}
	}

	return target;
}

static unsigned int global_canvas_iterator=0;
TCanvas* preapre_canvas(unsigned int n){
	TCanvas *canv = new TCanvas(("AutoCan"+to_string(global_canvas_iterator)).c_str(), "AutoCan",100,100,900,600);
	global_canvas_iterator++;
	canv->Divide(n);
	for(unsigned int i=1;i<=n;i++){
		TVirtualPad* p=canv->cd(i);
		p->SetPad(0,0,1,1);
		p->SetFrameBorderMode(0);
		p->SetFillStyle(4000);
		p->SetBottomMargin(0.15);
		p->SetTopMargin(0.05);
		p->SetRightMargin(0.05);
		p->SetLeftMargin(0.15);
		p->SetFrameLineWidth(2);
	}
	return canv;
}

void draw_corrected_titles(TH1* hist){
	
	hist->GetXaxis()->SetTitleSize(0);
	hist->GetYaxis()->SetTitleSize(0);	
	
	TLatex *latex= new TLatex();
	latex->SetTextSize(0.06);
	latex->SetTextFont(22);
	latex->SetTextAlign(22);
	latex->SetTextAngle(90);
	latex->DrawLatexNDC(0.05,0.55,hist->GetYaxis()->GetTitle());
	latex->SetTextAngle(0);
	latex->DrawLatexNDC(0.55,0.05,hist->GetXaxis()->GetTitle());
	delete latex;
}


TCanvas* preapre_canvas_bisect(){
	TCanvas *canv = preapre_canvas(2);
	canv->SetTitle("BisectCanvas");
	TVirtualPad* p=canv->cd(1);
	p->SetTopMargin(0.45);
	p=canv->cd(2);
	p->SetBottomMargin(0.55);
	return canv;
}

TCanvas* preapre_canvas_inset(){
	TCanvas *canv = preapre_canvas(2);
	canv->SetTitle("InsetCanvas");
	TVirtualPad* p=canv->cd(2);
	p->SetBottomMargin(0.55);
	p->SetTopMargin(0.07);
	p->SetRightMargin(0.07);
	p->SetLeftMargin(0.55);
	return canv;
}


TCanvas* draw_hist_inset(TH1* main,TH1* inset){
	TCanvas *canv = preapre_canvas_inset();
	canv->SetTitle(main->GetTitle());
	hformat(main);hformat(inset);
	
	TAxis* ax[2]={inset->GetXaxis(),inset->GetYaxis()};
	for(int i=0;i<2;i++){
		ax[i]->SetNdivisions(4,5,0);
		ax[i]->SetLabelSize(0.03);
		ax[i]->SetTitleSize(0.04);
		ax[i]->SetTitleOffset(0.5);
		ax[i]->SetTickLength(0.02);
	}
	
	canv->cd(1);main->Draw();
	draw_corrected_titles(main);

	canv->cd(2);inset->Draw();
	
	return canv;
}

TCanvas* draw_hist_bisect(TH1* bottom,TH1* top){
	TCanvas *canv = preapre_canvas_bisect();
	canv->SetTitle(bottom->GetTitle());
	hformat(bottom);hformat(top);
	
	top->GetXaxis()->SetLabelSize(0);
	
	top->GetXaxis()->SetTitleSize(0);
	top->GetYaxis()->SetTitleSize(0);
	bottom->GetXaxis()->SetTitleSize(0);
	bottom->GetYaxis()->SetTitleSize(0);
	
	top->GetYaxis()->SetNdivisions(5,5,0);
	bottom->GetYaxis()->SetNdivisions(5,5,0);
	
	TPad* p=(TPad*)canv->cd(1);bottom->Draw();
	
	//Whitebox covering top number
	TBox *box = new TBox();
	box->SetFillColor(0);
	p->Update();//To load in the new coords properly
	box->DrawBox(p->PixeltoX(p->UtoPixel(0)),
	p->AbsPixeltoY(abs(p->VtoPixel(0.5))),
	p->PixeltoX(p->UtoPixel(0.14)),
	p->AbsPixeltoY(abs(p->VtoPixel(0.7))));

	p=(TPad*)canv->cd(2);
	top->Draw();
	draw_corrected_titles(top);
	TQObject::Connect(p, "RangeChanged()", 0, 0,"RangeChangeBisectCanvasBoth()");
	TQObject::Connect(canv, "ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0, 0,"PostUpdateCanvasUpdateCall(Int_t,Int_t,Int_t,TObject*)");
	
	return canv;	
}


TCanvas* draw_electron_gamma(TH1* electron,TH1* gamma){
	axislabelkev(gamma);
	axislabelkev(electron);
	TCanvas *canv = draw_hist_bisect(electron,gamma);
	electron->SetMinimum((int)-1111);//undo the zero minimum set
	
	canv->cd(2);
	
	TLatex *latex= new TLatex();
	latex->SetTextSize(0.05);
	latex->SetTextFont(22);
	latex->SetTextAngle(0);
	latex->SetTextAlign(32);
	latex->DrawLatexNDC(0.93,0.9,"#gamma rays");
	latex->DrawLatexNDC(0.93,0.5,"Electrons");

	return canv;
	
	
}

//This function is added to sidestep interrupting update events
static bool PostUpdateCanvasUpdateCallbool=false;
void PostUpdateCanvasUpdateCall(Int_t event, Int_t x, Int_t y, TObject *selected){
	if(!gTQSender)return;
	if(PostUpdateCanvasUpdateCallbool&&((TObject*)gTQSender)->IsA() == TCanvas::Class()){
		PostUpdateCanvasUpdateCallbool=false;
		((TCanvas*)gTQSender)->Update();
	}
}


void RangeChangeBisectCanvasBoth(){
	cout<<endl<<"Pad 2->1 Range Change Start. "<<flush;

	//If gTQSender isnt a TObject pointer, this will crash
	if(!gTQSender)return;
	if (!(((TObject*)gTQSender)->IsA() == TPad::Class()))return;
	TPad* s=(TPad*)gTQSender;
	if(!(s->GetMother()->IsA() == TCanvas::Class()))return;
	TPad* p=(TPad*)s->GetMother()->cd(1);
	if(p==s)return;
	
	double l=1,u=-1;
	
	TH1* h=hist_capture(s);
	if(!h)return;
	HistDrawnXRange(h,l,u);//Use this rather than canvas GetRangeAxis/GetUxmin/GetUxmax because this fn is called mid-update and those dont work right
	
	cout<<l<<" "<<u;
	if(u<l)return;
	
	h=hist_capture(p);
	if(!h)return;
	h->GetXaxis()->SetRangeUser(l,u);
	
	double min=h->GetMaximum();
	double max=0;
	for(int i=h->GetXaxis()->GetFirst();i<=h->GetXaxis()->GetLast();i++){
		double y=h->GetBinContent(i);
		if(y<min)min=y;
		if(y>max)max=y;
	}
	h->SetMinimum(min);
	h->SetMaximum(min+(max-min)*1.2);

	cout<<" Range Change Finished."<<endl;
	
	//Because this function is called part way though a canvas update we cant force update of other canvas here
	p->Modified();
	PostUpdateCanvasUpdateCallbool=true;

	//We must change back to this canvas to allow the canvas update this function was called during to complete correctly
	s->cd();
}

void HistDrawnXRange(TH1* h,double &l,double &u){
	TAxis* a=h->GetXaxis();
	l=a->GetBinLowEdge(a->GetFirst());
	u=a->GetBinUpEdge(a->GetLast());
}


void AddPeakLabel(double E,bool exact,string text,TVirtualPad* pad,TH1* hist,TVirtualPad* pairpad){
	pad->cd();
	gPad->Update();//These lines seem to be quite important for range functions to work properly
	
	stringstream label;
	label<<" "<<E<<" "<<text;
	
	if(!hist)hist=hist_capture(pad);
	if(!hist)return;
	
	//Find y
	double y;
	if(exact)y=hist->GetBinContent(hist->GetXaxis()->FindBin(E));
	else y=FindLocalMax(hist,E);
	
	double yb=pad->GetUymin();
	double yt=pad->GetUymax();
	
	//Slight y offset
	double y5=0.05*(yt-yb);
	y+=y5;
	if(y>yt-y5)y=yt-y5;
	double yL=y+y5;
	double EL=E;
	
	//range of the drawn x-axis
	double xb=pad->GetUxmin();
	double xt=pad->GetUxmax();

// 	cout<<endl<<xb<<" "<<yb<<" "<<xt<<" "<<yt<<endl<<E<<" "<<y;	
	
	if(!(E>xb&&E<xt))return;
	
	if(pairpad){
		//convert to NDC and back
		PadNDCtoUser(E,y,pad,true);
		PadNDCtoUser(EL,yL,pad,true);
		PadNDCtoUser(E,y,pairpad);
		PadNDCtoUser(EL,yL,pairpad);
	}
	
	//By drawing in pad rather than NDC markers mover when x-axis changed
	//Also had all kinds of trouble with marker draw NDC
	
	TLatex* latex=new TLatex();
	latex->SetTextSize(0.045);
	latex->SetTextFont(22);
	latex->SetTextAlign(12);

	TMarker mark;
	mark.SetMarkerStyle(23);
	mark.DrawMarker(E,y);
	latex->DrawLatex(E,yL,label.str().c_str());
//TH1* backless SmoothOffBack(TH1*);	
}

void PadNDCtoUser(vector<double>& x,vector<double>& y,TVirtualPad* pad,bool reverse){
	double xy[4];
	pad->cd();gPad->Update();
	pad->GetRange(xy[0],xy[1],xy[2],xy[3]);

	for(unsigned int i=0;i<x.size()&&i<y.size();i++){
		PadNDCtoUser(x[i],y[i],xy,reverse);
	}
}

void PadNDCtoUser(double& x,double& y,TVirtualPad* pad,bool reverse){
	double xy[4];
	pad->cd();gPad->Update();
	pad->GetRange(xy[0],xy[1],xy[2],xy[3]);
	PadNDCtoUser(x,y,xy,reverse);
}

void PadNDCtoUser(double& x,double& y,double* xy,bool reverse){
	if(reverse){
			x=((x-xy[0])/(xy[2]-xy[0]));
			y=((y-xy[1])/(xy[3]-xy[1]));
	}else{
		x=(x*(xy[2]-xy[0]))+xy[0];
		y=(y*(xy[3]-xy[1]))+xy[1];
	}
}


void HistDrawCopy(TH1* hist){
	if(hist){
		TVirtualPad* hold=gPad;
		string name=hist->GetName();
		name+="DrawCopyCan";
		TCanvas* Can=new TCanvas(name.c_str());
		Can->cd();
		hist->DrawCopy("histcolz");
		//Convoluted but allows change format of just the drawcopy without cloning
		TH1* H=hist_capture(Can);
		if(H)hformat(H,0);
		Can->Modified();
		Can->Update();
		gPad=hold;
	}
}

TH1* DrawCopyHistOpt(TH1* hist){
	if(!hist)return 0;
		TH1* h=hist->DrawCopy("histcolz");
		TObject *obj;TIter next(hist->GetListOfFunctions());
		while ((obj = next()))((TF1*)obj)->DrawCopy("same");//Needed because of "Hist option turns off the functions"
	return h;	
}


//Mostly stolen from TRootCanvas.cxx
static const char *HistSaveAsTypes[] = { "PDF",          "*.pdf",
                                      "ROOT macros",  "*.C",
                                      "ROOT files",   "*.root",
                                      "PNG",          "*.png",
                                      "All files",    "*",
                                      0,              0 };
void HistSaveAs(TH1* hist, TGWindow *window){
if(hist){
		//Save the stuff for the next loop;
		static TString dir(".");
		static Int_t typeidx = 2;
		static Bool_t overwr = kFALSE;
		
		TGFileInfo fi;//Root class for containing save/open file info
		
		//initialise fi			
		TString workdir = gSystem->WorkingDirectory();
		fi.fFileTypes   = HistSaveAsTypes;
		fi.fIniDir      = StrDup(dir);
		fi.fFileTypeIdx = typeidx;
		fi.fOverwrite = overwr;
		
		//This appears to halt the process until close
		new TGFileDialog(gClient->GetRoot(), window, kFDSave, &fi);
// 		new TGFileDialog(fClient->GetDefaultRoot(), this, kFDSave, &fi);

		gSystem->ChangeDirectory(workdir.Data());
		
		if (!fi.fFilename) return;
		
		TString fn = fi.fFilename;
		TString ft = fi.fFileTypes[fi.fFileTypeIdx+1];
		
		dir     = fi.fIniDir;
		typeidx = fi.fFileTypeIdx;
		overwr  = fi.fOverwrite;
		
		Bool_t  appendedType = kFALSE;
again:
		if (fn.EndsWith(".root") ||
			fn.EndsWith(".C") ){
			hist->SaveAs(fn);
		}else if(fn.EndsWith(".pdf") ||
			fn.EndsWith(".png") ){
			TCanvas fCan;
			fCan.cd();
			DrawCopyHistOpt(hist);
			fCan.SaveAs(fn);
		}else {//check if the type has been added to string or nor
			if (!appendedType) {
			if (ft.Index(".") != kNPOS) {
				fn += ft(ft.Index("."), ft.Length());
				appendedType = kTRUE;
				goto again;//I didnt write this
			}
			}
			Warning("ProcessMessage", "file %s cannot be saved with this extension", fi.fFilename);
		}
		
		//Save the file type for the next loop;
		for (int i=1;HistSaveAsTypes[i];i+=2) {
			TString ftype = HistSaveAsTypes[i];
			ftype.ReplaceAll("*.", ".");
			if (fn.EndsWith(ftype.Data())) {
			typeidx = i-1;
			break;
			}
		}
	}

}
