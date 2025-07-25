//
//
//	jROOT Tools
//	Code for interacting with the clipboard on an X11 windows system
//	26 Jul 2025
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
