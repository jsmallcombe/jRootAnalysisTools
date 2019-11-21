#include "j_gate_subtract.h"

TAxis* hist_gater(TH3* in,string& pro,int xyz){
	switch (xyz) { 
		case 0: pro="yz"; return in->GetXaxis();  break;
		case 1: pro="xz"; return in->GetYaxis();  break;
		default: pro="xy"; return in->GetZaxis();  break;
	}
}

TAxis* hist_proj(TH3* in,string& pro,int xyz){
	switch (xyz) { 
		case 0: pro="x"; return in->GetXaxis();  break;
		case 1: pro="y"; return in->GetYaxis();  break;
		default: pro="z"; return in->GetZaxis();  break;
	}
}

	//	
	// 3D gating functions
	//

TH2* hist_gater(double lower,double upper,TH3* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRangeUser(lower,upper);
	TH2* ret=(TH2*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}

TH2* hist_gater_bin(int lower,int upper,TH3* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRange(lower,upper);
	TH2* ret=(TH2*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}

TH2* hist_gater(double lower,TH3* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRange(ax->FindFixBin(lower),ax->GetNbins()+1);
	TH2* ret=(TH2*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}

TH2* hist_gater_bin(int lower,TH3* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRange(lower,ax->GetNbins()+1);
	TH2* ret=(TH2*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}


 //NOTE 1: The generated histogram is named th3name + option


	//
	//2D gating functions
	//
	
TH1* hist_gater(double lower,double upper,TH2* in,int xyz,string name){
	if(xyz==1) return (TH1*)in->ProjectionX(name.c_str(),in->GetYaxis()->FindFixBin(lower),in->GetYaxis()->FindFixBin(upper));
	else  return (TH1*)in->ProjectionY(name.c_str(),in->GetXaxis()->FindFixBin(lower),in->GetXaxis()->FindFixBin(upper));
}
TH1* hist_gater_bin(int lower,int upper,TH2* in,int xyz,string name){
	if(xyz==1) return (TH1*)in->ProjectionX(name.c_str(),lower,upper);
	else  return (TH1*)in->ProjectionY(name.c_str(),lower,upper);
}
TH1* hist_gater(double lower,TH2* in,int xyz,string name){
	if(xyz==1) return (TH1*)in->ProjectionX(name.c_str(),in->GetYaxis()->FindFixBin(lower),in->GetYaxis()->GetNbins()+1);
	else  return (TH1*)in->ProjectionY(name.c_str(),in->GetXaxis()->FindFixBin(lower),in->GetXaxis()->GetNbins()+1);
}
TH1* hist_gater_bin(int lower,TH2* in,int xyz,string name){
	if(xyz==1) return (TH1*)in->ProjectionX(name.c_str(),lower,in->GetYaxis()->GetNbins()+1);
	else  return (TH1*)in->ProjectionY(name.c_str(),lower,in->GetXaxis()->GetNbins()+1);
}


///////

TH1* hist_gater(double a,double b,TH1* c,int d,string e){
	if(c->IsA()->InheritsFrom(TH3::Class()))return hist_gater(a,b,(TH3*)c,d,e);
	if(c->IsA()->InheritsFrom(TH2::Class()))return hist_gater(a,b,(TH2*)c,d,e);
	return 0;
}
TH1* hist_gater_bin(int a,int b,TH1* c,int d,string e){
	if(c->IsA()->InheritsFrom(TH3::Class()))return hist_gater_bin(a,b,(TH3*)c,d,e);
	if(c->IsA()->InheritsFrom(TH2::Class()))return hist_gater_bin(a,b,(TH2*)c,d,e);
	return 0;
}
TH1* hist_gater(double a,TH1* c,int d,string e){
	if(c->IsA()->InheritsFrom(TH3::Class()))return hist_gater(a,(TH3*)c,d,e);
	if(c->IsA()->InheritsFrom(TH2::Class()))return hist_gater(a,(TH2*)c,d,e);
	return 0;
}
TH1* hist_gater_bin(int a,TH1* c,int d,string e){
	if(c->IsA()->InheritsFrom(TH3::Class()))return hist_gater_bin(a,(TH3*)c,d,e);
	if(c->IsA()->InheritsFrom(TH2::Class()))return hist_gater_bin(a,(TH2*)c,d,e);
	return 0;
}

	//
	// Projection functions
	//

TH1* hist_proj(TH1* input,int xyz,string name,bool flowless){
	if(input->IsA()->InheritsFrom(TH3::Class())){
		TH3* in=(TH3*)input;
		if(flowless){
			switch (xyz) { 
				case 0: return (TH1*)in->ProjectionX(name.c_str(),1,in->GetYaxis()->GetNbins(),1,in->GetZaxis()->GetNbins());  break;
				case 1: return (TH1*)in->ProjectionY(name.c_str(),1,in->GetXaxis()->GetNbins(),1,in->GetZaxis()->GetNbins());  break;
				default: return (TH1*)in->ProjectionZ(name.c_str(),1,in->GetXaxis()->GetNbins(),1,in->GetYaxis()->GetNbins());  break;
			}			
		}else{
			switch (xyz) { 
				case 0: return (TH1*)in->ProjectionX(name.c_str());  break;
				case 1: return (TH1*)in->ProjectionY(name.c_str());  break;
				default: return (TH1*)in->ProjectionZ(name.c_str());  break;
			}			
		}
	}
	if(input->IsA()->InheritsFrom(TH2::Class())){
		TH2* in=(TH2*)input;
		if(flowless){
			if(xyz==0)return (TH1*)in->ProjectionX(name.c_str(),1,in->GetYaxis()->GetNbins());
			else return (TH1*)in->ProjectionY(name.c_str(),1,in->GetXaxis()->GetNbins());			
		}else{
			if(xyz==0)return (TH1*)in->ProjectionX(name.c_str());
			else return (TH1*)in->ProjectionY(name.c_str());			
		}
	}	
	return 0;	
}


	//
	//subtraction functions
	//
TH1* scaled_back_subtract(TH1* gate,TH1* back ,double backfrack,double uncertainfrac,bool scale){
	TH1* pass=(TH1*)gate->Clone();
	return scaled_back_subtract(gate,back ,backfrack,pass,uncertainfrac,scale);
}

TH1* scaled_back_subtract(TH1* gate,TH1* back ,double backfrack,TH1* pass,double uncertainfrac,bool scale){
    
    if(scale){
        double backcount=back->Integral();
        double forecount=gate->Integral();
        backfrack*=forecount/backcount;
    }
	
	if(!back->GetSumw2N())back->Sumw2();
	if(!gate->GetSumw2N())gate->Sumw2();
	
	pass->Add(gate,back,1.0,-backfrack);
	
	if(uncertainfrac){static_cast< TH1ErrorAdj* > (pass)->AdjustError(back,backfrack*uncertainfrac);}
	return pass;
}

//Doing it this way allows direct access to BinErrorSq so saves on wasteful squaring and rooting
void TH1ErrorAdj::AdjustError(const TH1* back,double frac){
	if(!fSumw2.fN)Sumw2();
	double v;
	for (Int_t bin = 0; bin < fNcells; ++bin) {
		v=back->GetBinContent(bin);
		fSumw2.fArray[bin] += v*v*frac*frac;
	}
}


void TH3axisreseter(TH3* hist){
	hist->GetXaxis()->SetRange();
	hist->GetYaxis()->SetRange();
	hist->GetZaxis()->SetRange();
}


