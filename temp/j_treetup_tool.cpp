
#include "j_treetup_tool.h"

ClassImp(jRootTreeCube);

int jRootTreeCube::jRootTreeCube_iterator = 0;


jRootTreeCube::jRootTreeCube():
	TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),
	Popup(0),DataChain(0),Symmetrisation(0),Hist{0,0,0},XYZ(0),
	Gate(0),Back(0),gd(-1),gu(-1),bd(-1),bu(-1){
    
    SetCleanup(kDeepCleanup);	
    
    
    TGLayoutHints* ffExpandY = new TGLayoutHints(kLHintsExpandY | kLHintsCenterY, 0, 0, 0, 0);
    TGLayoutHints* ffExpand = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0);

	TGVerticalFrame *ControlFrame = new TGVerticalFrame(this, 0, 0, 0); 

		fBgroup1 = new TGButtonGroup(ControlFrame,"Projection",kChildFrame);
		TGRadioButton *fRButton = new TGRadioButton(fBgroup1,"X ");
		fRButton->SetState(kButtonDown);
		fRButton = new TGRadioButton(fBgroup1,"Y ");
		fRButton = new TGRadioButton(fBgroup1,"Z");
		fBgroup1->Show();
		fBgroup1->Connect(" Clicked(Int_t)", "jRootTreeCube", this,"ChangeProjection(Int_t)");//Link test signal to its    int gate_down,gate_up;
	ControlFrame->AddFrame(fBgroup1);
	
		TGTextButton *fTButton1 = new TGTextButton(ControlFrame,"DoGates");
		fTButton1->Connect("Clicked()","jRootTreeCube",this,"DoGatesDraw()");
	ControlFrame->AddFrame(fTButton1);
		TGTextButton *fTButton2 = new TGTextButton(ControlFrame,"GateGates");
		fTButton2->Connect("Clicked()","jRootTreeCube",this,"DoGatesGate()");
	ControlFrame->AddFrame(fTButton2);
	
	
    AddFrame(ControlFrame,ffExpandY);

	SelectFrame = new jGateSelectFrame(this);
    AddFrame(SelectFrame,ffExpand);

    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();
}

void jRootTreeCube::ChangeProjection(Int_t xyz){
	fBgroup1->SetButton(xyz);
	XYZ=xyz-1;
	SelectFrame->UpdateInput(Hist[XYZ]);
}


// If using the quick AddBinContent it doesnt incriment fEntries properly, which can cause issues down the line
void jRootTreeCube::ResetTH1fEntries(TH1* hist){
	double fEntriesCount=0;
	int N=hist->GetNcells();
	for(int b=0;b<N;b++){
		fEntriesCount+=hist->GetBinContent(b);
	}
	hist->SetEntries(fEntriesCount);
}

// If using the quick AddBinContent it doesnt incriment fEntries properly, which can cause issues down the line
void jRootTreeCube::SymmetriseTH2(TH2* hist){
	double fEntriesCount=0;
	for (int x=0;x<=hist->GetNbinsX()+1;x++){
		for (int y=0;y<=x;y++){
			double D=hist->GetBinContent(x,y)+hist->GetBinContent(y,x);
			hist->SetBinContent(x,y,D);
			hist->SetBinContent(y,x,D);
			fEntriesCount+=2*D;
		}
	}
	hist->SetEntries(fEntriesCount);
}


bool jRootTreeCube::TestFileExists(string InputFile){
	TFile InFile(InputFile.c_str(),"READ");
	gROOT->cd();	
	if(!InFile.IsOpen()){
		cout<<endl<<"No File Named "<<InputFile<<endl;
		return false;
	}
	InFile.Close();
	return true;
}

void jRootTreeCube::ClearHistList(){
	for(auto h:HistList)delete h;
	HistList.clear();
}

void jRootTreeCube::SetNewInput(string InputFile){
	
	if(!TestFileExists(InputFile))return;
	TFile InFile(InputFile.c_str(),"READ");
	gROOT->cd();	
	
	string TTreeName="";
	ClearHistList();
	
	TKey *key;
	TIter next(InFile.GetListOfKeys());
	while ((key = (TKey*)next())){
		TClass *cl = gROOT->GetClass(key->GetClassName());
		if(cl->InheritsFrom(TTree::Class())&&!TTreeName.size()){
            TTreeName=key->GetName();
		}
		if(cl->InheritsFrom(TH1::Class())
		&& !cl->InheritsFrom(TH2::Class())
		&& !cl->InheritsFrom(TH3::Class())){
			// Only find and clone 1D
            HistList.push_back((TH1*)key->ReadObj()->Clone());
			HistList[HistList.size()-1]->Reset(); // Empty them because we will sum the first file
		}
	}
	InFile.Close();
	
	if(!HistList.size()){
		cout<<endl<<"No Projections Histograms Located in file "<<InputFile<<endl;
	}
	
	ArrangeInputHistograms();
	
	if(!TTreeName.size()){
		cout<<endl<<"No TTree Located in file "<<InputFile<<endl;
		return;
	}
	
	if(DataChain)delete DataChain;
	DataChain=new TChain(TTreeName.c_str());
	
	AddFile(InputFile);
	
	SetBranches();

	return;
}

void jRootTreeCube::AddFile(string InputFile){
	
	if(!DataChain){
		SetNewInput(InputFile);
		return;
	}
		
	if(!TestFileExists(InputFile))return;

	TFile InFile(InputFile.c_str(),"READ");
	gROOT->cd();
	for(auto h:HistList){
		TH1* H=(TH1*) InFile.Get(h->GetName());
		if(H)h->Add(H);
	}	
	InFile.Close();
	
	DataChain->Add(InputFile.c_str());
	
	ChangeProjection(1);
	
	cout<<"Added File : "<<InputFile<<endl;
}


void jRootTreeCube::SetBranches(){
	if(!DataChain)return;
	
	SelectedLeafType= nullptr;
	BranchAddresses.clear();
	LeafAddresses.clear();

	auto obarray=DataChain->GetListOfBranches();
	
	for(int b=0;b<DataChain->GetNbranches();b++){
		if(obarray->At(b)->IsA()->InheritsFrom("TBranch")){
			TBranch* branch=(TBranch*)obarray->At(b);
			TClass *expectedClass=0;
			EDataType expectedType;
			if(!branch->GetExpectedType(expectedClass,expectedType)){ //returns 0 when no error
				if(!expectedClass){ // Not a TClass
					TDataType* LeafType=TDataType::GetDataType(expectedType);
// 					cout<<"  Type "<<TDataType::GetTypeName(expectedType);
					if(SelectedLeafType==nullptr)SelectedLeafType=LeafType;
					if(LeafType==SelectedLeafType)BranchAddresses.push_back((string)branch->GetName());	
				}
			}
			
			auto leafarray=branch->GetListOfLeaves();
			for(int l=0;l<branch->GetNleaves();l++){
				if(leafarray->At(l)->IsA()->InheritsFrom("TLeaf")){
					TLeaf* leaf=(TLeaf*)leafarray->At(l);
					TDataType* LeafType=TDataType::GetDataType(GetEDataType(leaf->GetTypeName()));
			
					if(SelectedLeafType==nullptr)SelectedLeafType=LeafType;
					
					if(LeafType==SelectedLeafType){
						string BrNm=branch->GetName();
						BrNm+="."+(string)leaf->GetName();
						LeafAddresses.push_back(BrNm);
					}
				}
			}
		}
	}
	/// If using the TTreeReader method, even when a branch is a basic data type
	/// If it was "created using a leaf list" it will have a leaf that must be addressed directly

	if(SelectedLeafType==nullptr){
		cout<<endl<<"No Valid Leaf Types Found"<<endl;
		return;
	}
}


void jRootTreeCube::ArrangeInputHistograms(){
	
	if(!HistList.size()){
		return;
	}
	
	Hist[0]=HistList[0];
	Hist[1]=HistList[0];
	Hist[2]=HistList[0];
	if(HistList.size()>1){
		Hist[1]=HistList[1];
		Hist[2]=HistList[1];
	}
	if(HistList.size()>2){
		Hist[2]=HistList[2];
	}
	for(auto h:HistList){
		string name=h->GetName();
		if(name.find("X")<name.size())Hist[0]=h;
		if(name.find("Y")<name.size())Hist[1]=h;
		if(name.find("Z")<name.size())Hist[2]=h;
	}
	
	
	bool x=(Hist[0]==Hist[1])||(Hist[0]==Hist[2]);
	bool y=(Hist[1]==Hist[0])||(Hist[1]==Hist[2]);
	bool z=(Hist[2]==Hist[0])||(Hist[1]==Hist[2]);
	SetSymmetry(x,y,z);
	
}

TH2* jRootTreeCube::PerformGate(unsigned short GateAxis,int GateDown,int GateUp){

	if(!DataChain){
		return 0;
	}
		
	bool BrcN=(BranchAddresses.size()>2);
	bool LfN=(BranchAddresses.size()>2);
	if(!(BrcN||LfN)){
		return 0;
	}
	
	///////////////////////////////////////////
	// Preapre the TH2 Histogram For Filling //
	///////////////////////////////////////////

	int Ny=Hist[(GateAxis+1)%3]->GetNbinsX();
	double Zeroy=Hist[(GateAxis+1)%3]->GetBinLowEdge(1);
	double Widthy=Hist[(GateAxis+1)%3]->GetBinWidth(1);
	int Nz=Hist[(GateAxis+2)%3]->GetNbinsX();
	double Zeroz=Hist[(GateAxis+2)%3]->GetBinLowEdge(1);
	double Widthz=Hist[(GateAxis+2)%3]->GetBinWidth(1);

	TH2F* FillHist=new TH2F(FillHistNum().c_str(),"FillHist",Ny,Zeroy,Zeroy+Ny*Widthy,Nz,Zeroz,Zeroz+Nz*Widthz);
/*	
	unsigned int GBd=Hist[GateAxis%3]->GetXaxis()->FindBin(GateDown);
	unsigned int GBu=Hist[GateAxis%3]->GetXaxis()->FindBin(GateUp);*/
	unsigned int GBd=GateDown;
	unsigned int GBu=GateUp;	
	
	
	// A popup message window, as this can be a very slow process
	if(!Popup)Popup=new jRootMultiPurposePopup();
	string title="Running TChain sort for class : "+(string)SelectedLeafType->GetFullTypeName();
// 	string title="Running TChain sort for class : "+(string)typeid(T).name();
	Popup->UpdateLine(title,1);
	Popup->UpdateLine("Starting",2);

	
	TStopwatch stopw;
	stopw.Start();//Defauly behaviour clears
	
	switch (SelectedLeafType->GetType()) {
		case  EDataType::kUShort_t:
			if(BrcN)UnsignedTypedTTreeSortBranchLoop<UShort_t>(FillHist,GateAxis,GBd,GBu); // This is the case that we expect
			else TypedTTreeSortTTreeReader<UShort_t>(FillHist,GateAxis,GateDown,GateUp);
			break;
		case  EDataType::kUInt_t:
			if(BrcN)UnsignedTypedTTreeSortBranchLoop<UInt_t>(FillHist,GateAxis,GBd,GBu);
			else TypedTTreeSortTTreeReader<UInt_t>(FillHist,GateAxis,GateDown,GateUp);
			break;
		case  EDataType::kULong64_t:
			if(BrcN)UnsignedTypedTTreeSortBranchLoop<ULong64_t>(FillHist,GateAxis,GBd,GBu);
			else TypedTTreeSortTTreeReader<ULong64_t>(FillHist,GateAxis,GateDown,GateUp);
			break;
		case  EDataType::kULong_t:
			if(BrcN)UnsignedTypedTTreeSortBranchLoop<ULong_t>(FillHist,GateAxis,GBd,GBu);
			else TypedTTreeSortTTreeReader<ULong_t>(FillHist,GateAxis,GateDown,GateUp);
			break;
// 		case  EDataType::kShort_t: if(LfN)TypedTTreeSortTTreeReader<Short_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kInt_t: if(LfN)TypedTTreeSortTTreeReader<Int_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kLong_t: if(LfN)TypedTTreeSortTTreeReader<Long_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kLong64_t: if(LfN)TypedTTreeSortTTreeReader<Long64_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kFloat_t: if(LfN)TypedTTreeSortTTreeReader<Float_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kFloat16_t: if(LfN)TypedTTreeSortTTreeReader<Float16_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kDouble_t: if(LfN)TypedTTreeSortTTreeReader<Double_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kDouble32_t: if(LfN)TypedTTreeSortTTreeReader<Double32_t>(FillHist,GateAxis,GateDown,GateUp); break;
		default: break;
	}
	
	double CpuTime=stopw.CpuTime(); // and stops
	cout<<endl<<CpuTime<<" s"<<endl;

	return FillHist;
}
	
	
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
int jRootTreeCube::TypedTTreeSortTTreeReader(TH2* FillHist,
											 unsigned short GateAxis,
											 double GateDown,
											 double GateUp){	
	// Inputs are in tree's leaf order. Rearrange cyclically setting gate to 0.
	string LeafAddress[3]={LeafAddresses[GateAxis%3],LeafAddresses[(GateAxis+1)%3],LeafAddresses[(GateAxis+2)%3]};
	bool SymBools[3]={(bool)(Symmetrisation&(1<<(GateAxis%3))),(bool)(Symmetrisation&(1<<((GateAxis+1)%3))),(bool)(Symmetrisation&(1<<((GateAxis+2)%3)))};
	
	unsigned long nevent = DataChain->GetEntries();
	unsigned long e = 0;
	
	DataChain->ResetBranchAddresses();
	TTreeReader myReader(DataChain);
	myReader.Restart();
	
	TTreeReaderValue<T> ReadVal1(myReader,LeafAddress[0].c_str());
	TTreeReaderValue<T> ReadVal2(myReader,LeafAddress[1].c_str());
	TTreeReaderValue<T> ReadVal3(myReader,LeafAddress[2].c_str());
	double val[3];
	
	while(myReader.Next()){
		val[0]=*ReadVal1;
		val[1]=*ReadVal2;
		val[2]=*ReadVal3;	
		
		if(val[0]>=GateDown && val[0]<GateUp)FillHist->Fill(val[1],val[2]);
		
		if(SymBools[0]&&SymBools[1]){
			if(val[1]>=GateDown && val[1]<GateUp)FillHist->Fill(val[0],val[2]);
		}
		
		if(SymBools[0]&&SymBools[2]){
			if(val[2]>=GateDown && val[2]<GateUp)FillHist->Fill(val[1],val[0]);
		}
		
		if(!(e&0x3FFFFF)){ // Update the popup about every 4 million events.
			Popup->UpdatePercentage(100.0*e/nevent,2);
		}
		e++;
	}
	
	if(SymBools[1]&&SymBools[2]){
		Popup->UpdateLine("Finisihed sort, symmetrisating histogram.",2);
		SymmetriseTH2(FillHist);
	}
	
	return 0;
}

template <class T>
int jRootTreeCube::UnsignedTypedTTreeSortBranchLoop(TH2* FillHist,
										unsigned short GateAxis,
										unsigned int GateDown,
										unsigned int GateUp){
	
	// Inputs are in tree's leaf order. Rearrange cyclically setting gate to 0.
	string BranchAddress[3]={BranchAddresses[GateAxis%3],BranchAddresses[(GateAxis+1)%3],BranchAddresses[(GateAxis+2)%3]};
	bool SymBools[3]={(bool)(Symmetrisation&(1<<(GateAxis%3))),(bool)(Symmetrisation&(1<<((GateAxis+1)%3))),(bool)(Symmetrisation&(1<<((GateAxis+2)%3)))};
// 	bool SymBools[3];
	
	bool AllAxisSym=SymBools[0]&&SymBools[1]&&SymBools[2];
	bool GateAxisSym=SymBools[0];
	bool HistSym=SymBools[1]&&SymBools[2];

	unsigned int OvX=FillHist->GetNbinsX()+1;
	unsigned int OvY=FillHist->GetNbinsY()+1;
	unsigned int NBX=OvX+1;
	
	if(HistSym&&(OvX!=OvY)){
		cout<<endl<<"Error : Asymmetric histogram provided when requesting symmetric fill."<<endl;
		return -1;
	}
	
	unsigned long nevent = DataChain->GetEntries();
	T val[3]; // Holder array for branch values
	DataChain->ResetBranchAddresses();
	DataChain->SetBranchAddress(BranchAddress[0].c_str(),&val[0]);
	DataChain->SetBranchAddress(BranchAddress[1].c_str(),&val[1]);
	DataChain->SetBranchAddress(BranchAddress[2].c_str(),&val[2]);
	
	if(AllAxisSym){
		for (unsigned long e=0;e<nevent;e++) {
			DataChain->GetEvent(e);
			
			//// This fuction is for unsigned, so only have to check if bin number is past the overflow
			if(val[0]>OvX)val[0]=OvX;
			if(val[1]>OvX)val[1]=OvX;
			if(val[2]>OvX)val[2]=OvX;
			
////////  Fractionally faster to not have to do [(i+2)%3] address lookup for every event //////
////////  So write out the 3 cases explicity rather than the nice neat loop below        //////
			if(val[0]>=GateDown && val[0]<=GateUp)FillHist->AddBinContent(val[1]+NBX*val[2]);
			if(val[1]>=GateDown && val[1]<=GateUp)FillHist->AddBinContent(val[2]+NBX*val[0]);
			if(val[2]>=GateDown && val[2]<=GateUp)FillHist->AddBinContent(val[0]+NBX*val[1]);
			
// // 				for(int i=0;i<3;i++){
// // 					if(val[i]>=GateDown && val[i]<=GateUp) {
// // 						FillHist->AddBinContent(val[(i+1)%3]+NBX*val[(i+2)%3]);
// // 					}
// // 				}
			
			if(!(e&0x3FFFFF)){ // Update the popup about every 4 million events.
				Popup->UpdatePercentage(100.0*e/nevent,2);
			}
		}
	}else if(GateAxisSym){
		// In this case 2 of the three axis are the gating axis
		for (unsigned long e=0;e<nevent;e++) {
			DataChain->GetEvent(e);
			if(val[1]>OvX)val[1]=OvX;
			if(val[2]>OvY)val[2]=OvY;

			// Histogram are defined X-axis == (GateAxis+1)%3, Y-axis == (GateAxis+2)%3
			// Filling here they are NOT symetric
			if(val[0]>=GateDown && val[0]<=GateUp){
// 				cout<<","<<flush;
				FillHist->AddBinContent(val[1]+NBX*val[2]);
			}
			if(SymBools[1])if(val[1]>=GateDown && val[1]<=GateUp){
// 				cout<<"."<<flush;
				if(val[0]>OvX)val[0]=OvX;
				FillHist->AddBinContent(val[0]+NBX*val[2]);
			}
			if(SymBools[2])if(val[2]>=GateDown && val[2]<=GateUp){
				cout<<"'"<<flush;
				if(val[0]>OvY)val[0]=OvY;
				FillHist->AddBinContent(val[1]+NBX*val[0]);
			}
			
			if(!(e&0x3FFFFF)){ // Update the popup about every 4 million events.
				Popup->UpdatePercentage(100.0*e/nevent,2);
			}
		}	
	}else{
		// When only gating on one branch then it is much faster to initially load only that branch.
		auto br=DataChain->GetBranch(BranchAddress[0].c_str()); 
		for (unsigned long e=0;e<nevent;e++) {
			br->GetEvent(e);
			if(val[0]>=GateDown && val[0]<=GateUp) {
				DataChain->GetEvent(e);
				if(val[1]>OvX)val[1]=OvX;
				if(val[2]>OvX)val[2]=OvX;
				FillHist->AddBinContent(val[1]+NBX*val[2]);
			}
			
			if(!(e&0x3FFFFF)){ // Update the popup about every 4 million events.
				Popup->UpdatePercentage(100.0*e/nevent,2);
			}
		}
		
		// Alteratively one may use the TTree draw command. This is slower than a basic loop.
// // 			string DrawCmd=BranchAddress[2]+":"+BranchAddress[1]+">>+"+FillHist->GetName(); // Note X/Y in TTree::Draw command flipped
// // 			stringstream ss; ss<<BranchAddress[0]<<">="<<GateDown<<"&&"<<BranchAddress[0]<<"<"<<GateUp;
// // 			DataChain->Draw(DrawCmd.c_str(),ss.str().c_str(),"goff");
		
	}

	
	///// Make the output histogram symetric if it should be
	///// The treatmet of diagonal being double filled is correct.
	if(HistSym){
		Popup->UpdateLine("Finisihed sort, symmetrisating histogram.",2);
		SymmetriseTH2(FillHist);
	}else{
		ResetTH1fEntries(FillHist);// Result of using AddBinContent
	}
	
	return 0;
}


// For some reason I can only find getting leaf type names by hardcoded output in 
// inherited classes TLeafD, TLeafS etc, and in these they use the "UShort_t" typename 
// TDataType will return these names, but I can find no function to TAKE these names
EDataType jRootTreeCube::GetEDataType(string typestring){
	if (!typestring.compare("Char_t"))return EDataType::kChar_t;
	if (!typestring.compare("Short_t"))return EDataType::kShort_t;
	if (!typestring.compare("Int_t"))return EDataType::kInt_t;
	if (!typestring.compare("Long_t"))return EDataType::kLong_t;
	if (!typestring.compare("Float_t"))return EDataType::kFloat_t;
	if (!typestring.compare("char*"))return EDataType::kCharStar;
	if (!typestring.compare("Double_t"))return EDataType::kDouble_t;
	if (!typestring.compare("Double32_t"))return EDataType::kDouble32_t;
	if (!typestring.compare("UChar_t"))return EDataType::kUChar_t;
	if (!typestring.compare("UShort_t"))return EDataType::kUShort_t;
	if (!typestring.compare("UInt_t"))return EDataType::kUInt_t;
	if (!typestring.compare("ULong_t"))return EDataType::kULong_t;
	if (!typestring.compare("Long64_t"))return EDataType::kLong64_t;
	if (!typestring.compare("ULong64_t"))return EDataType::kULong64_t;
	if (!typestring.compare("Bool_t"))return EDataType::kBool_t;
	if (!typestring.compare("Float16_t"))return EDataType::kFloat16_t;
	return EDataType::kVoid_t;
}



TH1* jRootTreeCube::DoGates(){
	
	if(!Popup)Popup=new jRootMultiPurposePopup();
	
	if(SelectFrame->GetGateBinDown()!=gd||SelectFrame->GetGateBinUp()!=gu){
		Popup->UpdateLine("Performing New Gate",0);
		gd=SelectFrame->GetGateBinDown();
		gu=SelectFrame->GetGateBinUp();
		if(Gate)delete Gate;
		
		Gate=PerformGate(XYZ,gd,gu);
		/// DO THE GATE
	}
	
	if(!Gate)return 0;
	
	if(SelectFrame->GetBackBinDown()!=bd||SelectFrame->GetBackBinUp()!=bu){
		Popup->UpdateLine("Performing New Background Gate",0);
		bd=SelectFrame->GetBackBinDown();
		bu=SelectFrame->GetBackBinUp();
		if(Back)delete Back;
		Back=0;
		
		if(bu>bd){
		/// DO THE GATE
			Back=PerformGate(XYZ,bd,bu);
		}
	}	
	double Frac=SelectFrame->GetBackFrac();
	
	TH1* RetHist;
	
	if(Frac>0 && Back){// If do background subtraction
		Popup->UpdateLine("Performing Background Subtraction",0);
		
		if(SelectFrame->SubtractGate()){// If special case gate overlaps
			Back->Add(Gate,-1);
		}
		
		RetHist=scaled_back_subtract(Gate,Back,Frac,0.04,true);
	}else{
		RetHist=(TH1*)Gate->Clone();
	}
	
	if(Popup){
		delete Popup;
		Popup=0;
	}

	return RetHist;
}

void jRootTreeCube::DoGatesDraw(){
	TH1* HistRet=DoGates();
	if(HistRet){
		TCanvas *C1=new TCanvas();
		C1->cd();
		gPad->Update();
		HistRet->SetDirectory(0);
		HistRet->AppendPad("col");
	}
	
}

void jRootTreeCube::DoGatesGate(){
	TH1* HistRet=DoGates();
	if(HistRet){
		new jgating_tool(HistRet,true);
	}
}
