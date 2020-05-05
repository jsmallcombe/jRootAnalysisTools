//
//
//	jROOT Tools
//	An object that runs a root based gating and background subtraction environment for TH2 and TH3
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef j_treetup_tool_h
#define j_treetup_tool_h

#include<TH1.h>
#include<TH2.h>
#include<TH3.h>
#include<TTree.h>
#include<TChain.h>
#include<TTreeReader.h>
#include<TFile.h>
#include<TROOT.h>
#include<TCanvas.h>
#include<TGLabel.h>
#include<TGFrame.h>
#include<TROOT.h> 
#include<TSystem.h> 
using namespace std;

#include "j_gating_select_frame.h"
#include "j_gate_subtract.h"
#include "j_gating_tool.h"

class jRootTreeCube : public TGMainFrame {
private:
	jRootMultiPurposePopup *Popup;
	TChain *DataChain;
	unsigned short Symmetrisation;
	TH1* Hist[3];
	vector<TH1*> HistList;
	j_gating_select_frame *SelectFrame;
	TGButtonGroup *fBgroup1;
	int XYZ;
	TH2 *Gate,*Back;
	int gd,gu,bd,bu;
	
	TDataType* SelectedLeafType;
	vector<string> BranchAddresses;
	vector<string> LeafAddresses;
	
	bool TestFileExists(string InputFile);
    void SetBranches();
	void ClearHistList();
	void SymmetriseTH2(TH2* hist);
	void ResetTH1fEntries(TH1* hist);
	void ArrangeInputHistograms();
	
	static int jRootTreeCube_iterator;
	
	template <class T>
	int TypedTTreeSortTTreeReader(TH2* FillHist,unsigned short GateAxis,double GateDown,double GateUp);
		
	template <class T>
	int UnsignedTypedTTreeSortBranchLoop(TH2* FillHist,unsigned short GateAxis,unsigned int GateDown,unsigned int GateUp);

	EDataType GetEDataType(string typestring);
	
	const char* FillHistNum(){
		stringstream ss;
		ss<<"FillHist"<<jRootTreeCube_iterator;
		jRootTreeCube_iterator++;
		return ss.str().c_str();
	}
	
public:	
	jRootTreeCube();
	jRootTreeCube(string InputFile):jRootTreeCube(){
		SetNewInput(InputFile);
	}
	
	~jRootTreeCube(){
		if(DataChain)delete DataChain;
		if(Popup)delete Popup;
		if(Gate)delete Gate;
		if(Back)delete Back;
		ClearHistList();
		Cleanup();
	};
	
    void SetNewInput(string InputFile);
    void AddFile(string InputFile);
	
	void SetSymmetry(bool X,bool Y,bool Z){
		Symmetrisation=0;
		if(X)Symmetrisation+=1;
		if(Y)Symmetrisation+=2;
		if(Z)Symmetrisation+=4;
		
		if(Symmetrisation==1||Symmetrisation==2||Symmetrisation==4){
			cout<<endl<<"Error : Cannot have 1 symmetric axis."<<endl;
			Symmetrisation=0;
		}
	}
	
	void ChangeProjection(Int_t);
	
	TH2* PerformGate(unsigned short GateAxis,int GateDown,int GateUp);
	
	TH1* DoGates();
	void DoGatesDraw();
	void DoGatesGate();
	
	ClassDef(jRootTreeCube, 1)	
};


#endif
