#
#
#	 Root Analysis Tools Library
#	17 Nov 2019
#	.smallcombe@outlook.com
#
#

ROOT_LIBS = $(shell root-config --glibs)
ROOT_GCC_FLAGS = $(shell root-config --cflags)
ROOT_LIBSEXTRA = -lSpectrum -lMinuit -lTreeViewer -lROOTTreeViewer
### library will compile an work 99.9% without TreeViewer ROOTTreeViewer
# -lX11

J_LIB = $(shell pwd)
J_INCLUDE = $(shell pwd)/include

CC = $(shell root-config --cxx)
CFLAGS = -std=c++11 -g -fPIC -Wall $(ROOT_GCC_FLAGS)
#-Xlinker --verbose -std=c++0x -I$(LIB)/include


HEAD = $(wildcard include/j_*.h)
OBJECTS = $(patsubst include/%.h,bin/build/%.o,$(HEAD))

TARG = bin/libJanalysistools.so
	
# OBJECTS+= bin/build/yield.o
# OBJECTSEX+= bin/build/yield.o

main: $(TARG) bin/BuildInfo

date:
	bash bin/build/date.sh $(HEAD)

bin/BuildInfo:
	bash bin/build/buildinfo.sh
	
$(TARG): $(OBJECTS) bin/DictOutput.cxx
	$(CC) $(CFLAGS) -o $@ -shared bin/DictOutput.cxx $(OBJECTS) -I. -I$(J_INCLUDE) $(ROOT_LIBS) $(ROOT_LIBSEXTRA)
	bash bin/build/header.sh
	bash bin/build/make_export.sh

bin/DictOutput.cxx: $(HEAD)
	bash bin/build/link.sh $(HEAD)
	rootcint -f $@ -c -I$(J_INCLUDE) $(HEAD) bin/build/Linkdef.h

bin/build/%.o: src/%.cpp include/%.h
	$(CC) $(CFLAGS) -o $@ -c $< -I$(J_INCLUDE)

bin/build/%.o: src/*/%.cpp include/%.h
	$(CC) $(CFLAGS) -o $@ -c $< -I$(J_INCLUDE)

clean:
	rm -f $(J_LIB)/bin/build/*.o
	rm -f $(J_LIB)/bin/build/Linkdef.h
	rm -f $(J_LIB)/bin/*.*
	rm -f $(J_LIB)/bin/BuildInfo
	rm -f $(J_LIB)/include/jlibmaster.h
	rm -f $(MINI)
	rm -f $(TARG)
	rm -f $(TARGB)
