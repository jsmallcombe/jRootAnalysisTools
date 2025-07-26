//
//
//	jROOT Tools
//	Tool for parsing TH1, TGraph & TGraphErrors data from the system clipboard via jEnv middle-click
//	26 Jul 2025
//	james.smallcombe@outlook.com
//
//

#ifndef JParseClip
#define JParseClip

#include <TClass.h>
#include <TH1.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TCanvas.h>

#include "j_env_clipboard_X11paste.h"

// Trys TMultiGraph, then TH1, then TGraph
// Most selective input to least
TObject* CopyBufferHistOrGraph(bool clip=true);

// If there is a valid object in the plain text clipboard build and draw it
int DrawFromClipboard();
int DrawFromClipboard(bool clip);

#endif
