// //
// //
// //	jROOT Tools
// //	An object that runs a root based gating and background subtraction environment for TH2 and TH3
// //	17 Nov 2019
// //	james.smallcombe@outlook.com
// //
// //
// 
#ifndef jGatingToolMaster_h
#define jGatingToolMaster_h

#include "TROOT.h"
#include "TBuffer.h"
#include "TGLayout.h"
#include "TF1.h"
#include "TMath.h"
#include "TH2.h"
#include "TH3.h"
#include "THnBase.h"
#include "TGInputDialog.h"
#include "TGFrame.h"

#include <RQ_OBJECT.h>

#include <iostream>
#include <iomanip> 
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// // header Over important due to inheretance 
#include "j_gating_select_frame.h"
#include "j_gating_subtraction_frame.h"
#include "j_gating_result_frame.h"
#include "j_gating_TH2_tool.h"
#include "j_gating_TH3_tool.h"
#include "j_gating_THn_tool.h"

/////////////////////////////////////////////////////////////////////////////////////

// THIS IS THE MAIN FUNCTION TO BE USED BY GUI ETC FOR LAUNCHING ANY GATER
TGMainFrame* jGatingToolSelector(const char *);
TGMainFrame* jGatingToolSelector(TObject*);

/////////////////////////////////////////////////////////////////////////////////////

TGTransientFrame* MakeTH3Popup();

/////////////////////////////////////////////////////////////////////////////////////

#endif
