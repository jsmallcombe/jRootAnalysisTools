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

#include <TGInputDialog.h>

#include "j_gating_THn_tool.h"

/////////////////////////////////////////////////////////////////////////////////////

// THIS IS THE MAIN FUNCTION TO BE USED BY GUI ETC FOR LAUNCHING ANY GATER
TGMainFrame* jGatingToolSelector(const char *);
TGMainFrame* jGatingToolSelector(TObject*);

/////////////////////////////////////////////////////////////////////////////////////

TGTransientFrame* MakeTH3Popup();

/////////////////////////////////////////////////////////////////////////////////////

#endif
