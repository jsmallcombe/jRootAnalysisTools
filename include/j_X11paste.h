//
//
//	jROOT Tools
//	Code for interacting with the clipboard on an X11 windows system
//	17 Nov 2019
//	james.smallcombe@outlook.com
//
//

#ifndef JX11Paste
#define JX11Paste

#include <sstream>
#include <iostream>

using namespace std;


int ReadX11CopyBufferAsText(stringstream &ss, bool clip=true);

#endif
