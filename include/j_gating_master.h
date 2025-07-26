//
//
//	jROOT Tools
//	Master function for starting the new TH2/TH3/THn gating tools
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
//

#ifndef jGatingToolMaster_h
#define jGatingToolMaster_h

#include <TGInputDialog.h>

#include "j_gating_THn_tool.h"

/////////////////////////////////////////////////////////////////////////////////////

// THIS IS THE MAIN FUNCTION TO BE USED BY GUI ETC FOR LAUNCHING ANY GATER
TGMainFrame* jGatingToolSelector(const char *);
TGMainFrame* jGatingToolSelector(TObject* = (TObject*)hist_capture());

/////////////////////////////////////////////////////////////////////////////////////

TGTransientFrame* MakeTH3Popup();

/////////////////////////////////////////////////////////////////////////////////////

#endif
