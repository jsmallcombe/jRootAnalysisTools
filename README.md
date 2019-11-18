
Please refer to the provided pdf manual for detailed operating instructions.

Users are recommended to use the latest release and not the master branch
https://github.com/jsmallcombe/jRootAnalysisTools/releases/latest
Please report any issues on the github issues page.

Please cite using doi:
[![DOI](https://zenodo.org/badge/88855371.svg)](https://zenodo.org/badge/latestdoi/88855371)
J. Smallcombe, jROOT Tools.

This package contains an add-on library for CERN's root analysis package.
The primary tools are:
-jEnv : A graphical session manager
-UltraFitEnv: A graphical fitting environment to for TH1 histograms. A help file is included in the tool.
-jgating_tool: A graphical slicer and background subtraction tool for TH2 and TH3 histograms.

Various histogram formatting and automated fitting macros are also included and may be documented later.

The library has been written with root 6.
Requires a C++11 compiler and will not work with root 5.
Compatibility has been tested on various linux distributions (debian and RHEL based) and macOS.
Last tested on root version 6.14 (exact sub-version not required for use).

Instructions for use:
1. Source "thisroot.sh" from your root installation
2. Run "make" in this directory
3. Add "source bin/thisjlib.sh" to your bashrc
4. Run "root -l bin/root_start.C" or
   OR
   Add "gSystem->Load("libJanalysistools.so")" to your ROOT start up script.
5. When running a root interactive session type "new jEnv();"
   to open the interactive toolbar to access analysis tools.

