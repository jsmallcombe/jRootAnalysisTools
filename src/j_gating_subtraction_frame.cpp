#include "j_gating_subtraction_frame.h"

ClassImp(jGateSubtractionFrame);

//______________________________________________________________________________

jGateSubtractionFrame::jGateSubtractionFrame() : jGateSelectFrame(){}

jGateSubtractionFrame::jGateSubtractionFrame(TGWindow * parent,int ThreeDee) : 
		jGateSelectFrame(parent, nullptr,ThreeDee),IterSuffix(Iterator(""))
		{}
		
void jGateSubtractionFrame::SetRangeAxis(TAxis* ax,int lower,int upper){
	if(ax){//Check for nullptr, such as if GetZaxis() called on TH2
		if(lower>upper){
			if(upper==0) upper=ax->GetNbins();  	 // We pass upper=0 for "end of range" 
			else 		 upper=ax->GetNbins()+1;    //  and any other value "include overflow" e.g. -1
		} 
		ax->SetRange(lower,upper);
	}
}
// 	TAxis::SetRange(), defaults to 0,0 which sets excluding OverUnderFlow, but ONLY if BOTH are zero
// 	Attemtping to set UNDERflow ON and OVERflow OFF here is problematic,
//  it can be achieved by manually passing upper=n, but not with automated flags.
// Function inputs for full range settings 
// 	1,0  exclude underoverflow
// 	0,-1 include underoverflow
// 	1,-1 include overflow

void jGateSubtractionFrame::ResetRanges(TH1* hist, bool UnderFlow,bool OverFlow) {
	SetRangeAxis(hist->GetXaxis(),!UnderFlow,-1*OverFlow);
	SetRangeAxis(hist->GetYaxis(),!UnderFlow,-1*OverFlow);
	SetRangeAxis(hist->GetZaxis(),!UnderFlow,-1*OverFlow);
}

void jGateSubtractionFrame::ResetRanges(THnBase* hist, bool UnderFlow,bool OverFlow) {
// 	for()GetNdimensions()
// 		hist->GetAxis(i)
	for(auto* obj : *hist->GetListOfAxes()){
			SetRangeAxis((TAxis*)obj,!UnderFlow,-1*OverFlow);
	}
}

//////////////////////////////////////////

// All ranges are reset by the master GateAxisByBin, so only gating range needs setting 
TObject* jGateSubtractionFrame::GateByBin(THnBase* in,int xyz,int lower,int upper){

	// If negative a 1D projection is requested 
	if(xyz<0){// Return a TH1
		return (TObject*)in->Projection(abs(xyz+1));
	}
	
	int N=in->GetNdimensions();
	if(N<=xyz)return nullptr;
	
	SetRangeAxis(in->GetAxis(xyz),lower,upper);

	if(N==3){ // Return a TH2
		return (TObject*)in->Projection((xyz+1)%3,(xyz+2)%3);
	}
	
	// Fill the array of axis to project with all axis but xyz
	int i=0;
	for(int a=0;a<N;a++){
		if(a==xyz)continue;
		THnAxisHolder[i]=a;
		i++;
	}
	
	return in->ProjectionND(N-1,THnAxisHolder); //Return an THn
}


// All ranges are reset by the master GateAxisByBin, so only gating range needs setting 
TH1* jGateSubtractionFrame::GateByBin(TH3* in,int xyz,int lower,int upper,TString name){
	TString is[6]={"yz","zx","xy","x","y","z"};
	//Note "xz" not "zx" was used previously, so there will be some orientation differences
	
	// negative values used to request 1D projection, rather than 2D slice 
	if(xyz<0){
		xyz=abs(xyz)+2;
	}else{
		switch (xyz%3) { 
			case 0: SetRangeAxis(in->GetXaxis(),lower,upper);  break;
			case 1: SetRangeAxis(in->GetYaxis(),lower,upper);  break;
			default: SetRangeAxis(in->GetZaxis(),lower,upper);  break;
		}
	}
	
	TString Opt=is[xyz%6];
// 	if(name.Length())Opt=name+"_"+Opt;
// // Officially Project3D supports adding extra name portion
// // Had problems combining this with filling-existing-histograms-by-name functionality
// // Ended up with some overwrites that should have been possible resulting in deletions and segfaults
// // This work around works	
	TString Holdname=in->GetName();
	in->SetName(name);
	TH1* ret=in->Project3D(Opt);
	in->SetName(Holdname);
	
	return ret;
}
 //NOTE 1: The generated histogram is named th3name + option
 
// // ProjectionX/Y/Z are not in TH1 only TH2/TH3
// // Project3D is only in TH3, but can also function as ProjectionX/Y/Z
	
TH1* jGateSubtractionFrame::GateByBin(TH2* in,int xyz,int lower,int upper,TString name){
	
	if(abs(xyz)%2==1){
		SetRangeAxis(in->GetYaxis(),lower,upper);
		return (TH1*)in->ProjectionX(name);
	}
	
	SetRangeAxis(in->GetXaxis(),lower,upper);
	return (TH1*)in->ProjectionY(name,lower,upper);
}


///////
TH1* jGateSubtractionFrame::GateAxisByBin(TH1* in,int xyz,int lower,int upper,TString name){
	ResetRanges(in); // Using gGlobalUnderlowBool/gGlobalOverflowBool to include/exclude under/overflows
	if(in->IsA()->InheritsFrom(TH3::Class()))return GateByBin((TH3*)in,xyz,lower,upper,name);
	if(in->IsA()->InheritsFrom(TH2::Class()))return GateByBin((TH2*)in,xyz,lower,upper,name);
	return nullptr;
}

TObject* jGateSubtractionFrame::GateAxisByBin(THnBase* in,int xyz,int lower,int upper,TString name){
	ResetRanges(in); // Using gGlobalUnderlowBool/gGlobalOverflowBool to include/exclude under/overflows
	TNamed* ob=(TNamed*)GateByBin(in,xyz,lower,upper);
// 	ob->SetName(jGateSelectFrame::Iterator("THnProj"));
	ob->SetName(name);
	return (TObject*)ob;
}





double jGateSubtractionFrame::ScaledBackgroundSubtract(THnBase* gate,THnBase* back ,double backfrack,double uncertainfrac){
	
	// Integral is not in THnBase, but not sure ComputeIntegral gives the same results for overunderflow
	double backcount=back->ComputeIntegral();
	double forecount=gate->ComputeIntegral();
	
	backfrack*=forecount/backcount;
	
	if(!back->GetSumw2())back->Sumw2();
	if(!gate->GetSumw2())gate->Sumw2();
	
	gate->Add(back,-backfrack);
	
	return backfrack;
}

double jGateSubtractionFrame::ScaledBackgroundSubtract(TH1* gate,TH1* back ,double backfrack,double uncertainfrac){
	
	double backcount=back->Integral();
	double forecount=gate->Integral();
	// ComputeIntegral for TH1 and THnBase have very different behaviour/return values
	
	backfrack*=forecount/backcount;
	
	if(!back->GetSumw2())back->Sumw2();
	if(!gate->GetSumw2())gate->Sumw2();
	
	gate->Add(back,-backfrack);
	
	if(uncertainfrac>0){
		static_cast< TH1ErrorErrorAdj* > (gate)->AdjustError(back,backfrack*uncertainfrac);
	}
	
	return backfrack;
}


///////////////////////////////////////////////////////////////////////////////////
////////////// Template specialisation, only seen by this file ////////////////////
///////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////



// Doing it this way allows direct access to BinErrorSq so saves on wasteful squaring and rooting
void TH1ErrorErrorAdj::AdjustError(const TH1* back,double frac){
    if (!back || back->GetNcells() != fNcells) {
        Error("AdjustError", "Incompatible histogram bin structure");
        return;
    }
	
	if(!fSumw2.fN)Sumw2();
	double v;
	for (Int_t bin = 0; bin < fNcells; ++bin) {
		v=back->GetBinContent(bin);
		fSumw2.fArray[bin] += v*v*frac*frac;
	}
}
// NOTE: This relies on fSumw2 being protected in TH1 (ROOT). If ROOT changes this to private, this will break.



