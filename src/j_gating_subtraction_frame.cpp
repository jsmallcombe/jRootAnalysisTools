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
	
	if(!back->GetCalculateErrors())back->Sumw2();// Or CalculateErrors()()
	if(!gate->GetCalculateErrors())gate->Sumw2();
	
	gate->Add(back,-backfrack);
	
	return backfrack;
}

double jGateSubtractionFrame::ScaledBackgroundSubtract(TH1* gate,TH1* back ,double backfrack,double uncertainfrac){
	
	double backcount=back->Integral();
	double forecount=gate->Integral();
	// ComputeIntegral for TH1 and THnBase have very different behaviour/return values
	
	backfrack*=forecount/backcount;
	
	if(!back->GetSumw2N())back->Sumw2();
	if(!gate->GetSumw2N())gate->Sumw2();
	
	gate->Add(back,-backfrack);
	
	if(uncertainfrac>0){
		static_cast< TH1ErrorErrorAdj* > (gate)->AdjustError(back,backfrack*uncertainfrac);
	}
	
	return backfrack;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////// Template with explicit declaration of limited types, so can appear in .cpp not .h ///////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Template to allow use with TH1* or THn* without casting up to TObject* 
template <typename T>
TH1* jGateSubtractionFrame::ProjectAxisByBin(T* input,int xyz,TString name, bool UnderFlow,bool OverFlow){
	xyz++;
	return (TH1*)GateAxisByBin(input,-xyz,!UnderFlow,-1*OverFlow,name); // Use globals
	// For THn* input, GateAxisByBin can return THn* OR TH1* types, so it returns TObject* in general, and must be cast as we know it is TH1* here.
}

template TH1* jGateSubtractionFrame::ProjectAxisByBin<TH1>(TH1*,int,TString, bool,bool);
template TH1* jGateSubtractionFrame::ProjectAxisByBin<THnBase>(THnBase*,int,TString, bool,bool);


template <typename U,typename T>
T* jGateSubtractionFrame::MakeBackWithGateGap(U*fInput, T*fResult, T*fResFullProj){

	T* fBack=nullptr;
	
	// First test if fInput has not had its stats set. Then we can do a quick subtraction
	if(!TestWeightsStatus(fInput)&&fResult){
		// Important as the Add is *not* an arithmetic subtraction, but an exact data removal.
		// If the statistics have already been set due to previous hisogram arithmatic, then a simple subtraction cant work
		if(fResFullProj){
			fBack=(T*)fResFullProj->Clone(TString(fResFullProj->GetName()).ReplaceAll("ResFullProj", "Back"));
		}else{
			fBack=(T*)GateAxisByBin(fInput,xyz,GetBackBinDown(),GetBackBinUp(),"Back"+IterSuffix);
		}
		
		fBack->Add(fResult,-1);

// // // Not used anymore
// // // This removed the additional errors from THIS subtraction, but also deletes any previously present >sqrt(N) errors
// // // ResetWeights(fBack)
		
	}else{ // We must do the slower option of 2 gates, 1 above and 1 below, to preserve statistics
		
		// Test if we are at the very edge of the range and so can do 1 gate
		// This test has actually already been done for manual-type at jGateSelectFrame::DoHistogram(), but not for anti-type
		if(GetGateBinDown()<=GetBackBinDown()){
			fBack=(T*)GateAxisByBin(fInput,xyz,GetGateBinUp()+1,GetBackBinUp(),"Back"+IterSuffix);
		}else if(GetGateBinUp()>=GetBackBinUp()){
			fBack=(T*)GateAxisByBin(fInput,xyz,GetBackBinDown(),GetBackBinDown()-1,"Back"+IterSuffix);
		}else{
			fBack=(T*)GateAxisByBin(fInput,xyz,GetGateBinUp()+1,GetBackBinUp(),"Back"+IterSuffix);
			T* fBackTwo=(T*)GateAxisByBin(fInput,xyz,GetBackBinDown(),GetBackBinDown()-1,"BackTwo"+IterSuffix);
			if(fBack&&fBackTwo){
				fBack->Add(fBackTwo);
				delete fBackTwo;
			}
		}
	}
	return fBack;
}

template TH1* jGateSubtractionFrame::MakeBackWithGateGap<TH1,TH1>(TH1*,TH1*,TH1*);
template TH1* jGateSubtractionFrame::MakeBackWithGateGap<THnBase,TH1>(THnBase*,TH1*,TH1*);
template THnBase* jGateSubtractionFrame::MakeBackWithGateGap<THnBase,THnBase>(THnBase*,THnBase*,THnBase*);



template <typename U,typename T>
void jGateSubtractionFrame::UpdateInput(U*fInput, T*&fResFullProj){
	// fResFullProj expected to be nullptr as fResFullProj is only created on input/axis change
	// Hence expect fResFullProj do have changed binning etc, so it is *always* deleted, and not making use name-based overwritting.
    
	fResFullProj=(T*)GateAxisByBin(fInput,xyz,gGlobalLowestBin,-1*gGlobalOverflowBool,"ResFullProj"+IterSuffix);
// 	fResFullProj->SetStats(0);	// No support for THnBase template. If need for drawing reason, add in jGatingToolTH3
	fResFullProj->SetTitle("");
	
	TH1* proj=ProjectAxisByBin(fInput,xyz,"proj"+IterSuffix);
    jGateSelectFrame::UpdateInput(proj);// call base class version
	delete proj; //Cloned inside jGateSelectFrame::UpdateInput()
}

template void jGateSubtractionFrame::UpdateInput<TH1,TH1>(TH1*,TH1*&);
template void jGateSubtractionFrame::UpdateInput<THnBase,TH1>(THnBase*,TH1*&);
template void jGateSubtractionFrame::UpdateInput<THnBase,THnBase>(THnBase*,THnBase*&);

    
template <typename U,typename T>
double jGateSubtractionFrame::DoGateSubtract(U*fInput, T*&fResult, T*&fBack, T*&fResFullProj){
	
	// In the case of TH2::ProjectionX()/TH3::Project3D efficiently re-using in-memory histogram of same name
	// There is an issue whereby the sumw2 is not reset, so if fInput does NOT have weights,
	// The resultant projections, which should not have weights set, will have weights set that are incorrect!
	// The reset is called on the previous histogram if it exists, before it is overwritten, to avoid removing weights if fInput DOES have weights 
	if(fResult)ResetWeights(fResult);
	if(fBack)ResetWeights(fBack);
    
	// GateAxisByBin *should* nicely fill the histogram matching the name if the TH1 exists
	// so we dont need to delete pointers except for when changing axis, handled by UpdateInput
	fResult=(T*)GateAxisByBin(fInput,xyz,GetGateBinDown(),GetGateBinUp(),"Gated"+IterSuffix);
	fResult->SetTitle("");

    // Note: The projection "fResFullProj" used to make "full" and "anti" background options
    // include the overflow bins, but excludes the underflow bin.
    // This is an intentional choice, as often intentionally zeroed data may be sorted into the underflow bin
    // The underflow bin can be selected with manual sliders

	
    T* fBackTidy=fBack;
	switch (GetBackMode()) {
		case 1://full
                fBack=fResFullProj;
			break;
		case 2://compton
                fBack=(T*)GateAxisByBin(fInput,xyz,GetBackBinDown(),-1,"Back"+IterSuffix);
			break;
		case 3://anti gate
			{
				// In gated part from the full projection
				fBack=MakeBackWithGateGap(fInput,fResult,fResFullProj);
			}
			break;
		case 4://none
			{
                fBack=fResult;
			}
			break;
		default:  //manual 
			{
                if(SubtractGate()){
					// In special case remove the gated part
					fBack=MakeBackWithGateGap(fInput,fResult);
				}else{
					fBack=(T*)GateAxisByBin(fInput,xyz,GetBackBinDown(),GetBackBinUp(),"Back"+IterSuffix);
				}		
			}
			break;
	}
	
//    The method GateAxisByBin, used for fResult, and for the backgrounds Compton & manual
//    will reuse the exiting histogram in memory, the other options do not.
//    So we catch those and delete the abandoned fBack histgram
    if(fBackTidy&&fBack!=fBackTidy){
        if(fBackTidy!=fResult&&fBackTidy!=fResFullProj) delete fBackTidy;
    }
	
	// The gated "histogram" fResult* and a background "histogram" fBack* are now clearly defined
	// Do the actual subtraction and propagate errors 
	
	double fBackFrac=1;
	if(fResult!=fBack)fBackFrac=ScaledBackgroundSubtract(fResult,fBack,GetBackFrac(),GetBackFracFrac());
    

    return fBackFrac;
}

template double jGateSubtractionFrame::DoGateSubtract<TH1,TH1>(TH1*,TH1*&,TH1*&,TH1*&);
template double jGateSubtractionFrame::DoGateSubtract<THnBase,TH1>(THnBase*,TH1*&,TH1*&,TH1*&);
template double jGateSubtractionFrame::DoGateSubtract<THnBase,THnBase>(THnBase*,THnBase*&,THnBase*&,THnBase*&);


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
