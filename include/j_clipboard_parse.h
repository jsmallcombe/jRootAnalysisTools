//
//
//	jROOT Tools
//	Utility functions and classes for Vectors, TF1s etc
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef JParseClip
#define JParseClip

#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <TClass.h>
#include <TH1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TCanvas.h>

#include "j_X11paste.h"

using namespace std;

// Trys TMultiGraph, then TH1, then TGraph
// Most selective input to least
TObject* CopyBufferHistOrGraph(bool clip=true);

// If there is a valid object in the plain text clipboard build and draw it
int DrawFromClipboard();
int DrawFromClipboard(bool clip);

#endif
