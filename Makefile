#
#
#	James Root Analysis Tools Library
#	20 April 2017
#	james.smallcombe@outlook.com
#
#

ROOT_LIBS = $(shell root-config --glibs)
ROOT_GCC_FLAGS = $(shell root-config --cflags)
ROOT_LIBSEXTRA = -lSpectrum 

JAMES_LIB = $(shell pwd)
JAMES_INCLUDE = $(shell pwd)/include

CC = $(shell root-config --cxx)
CFLAGS = -std=c++11 -g -fPIC -Wall $(ROOT_GCC_FLAGS)
#-Xlinker --verbose -std=c++0x -I$(JAMESLIB)/include


HEAD = $(wildcard include/james*.h)
OBJECTS = $(patsubst include/%.h,bin/build/%.o,$(HEAD))

TARG = bin/libJanalysistools.so
	
# OBJECTS+= bin/build/yield.o
# OBJECTSEX+= bin/build/yield.o

main: $(TARG)

date:
	bash bin/build/date.sh $(HEAD)
	
$(TARG): $(OBJECTS) bin/DictOutput.cxx
	$(CC) $(CFLAGS) -o $@ -shared bin/DictOutput.cxx $(OBJECTS) -I. -I$(JAMES_INCLUDE) $(ROOT_LIBS) $(ROOT_LIBSEXTRA)
	bash bin/build/header.sh
	bash bin/build/make_export.sh

bin/DictOutput.cxx: $(HEAD)
	bash bin/build/link.sh $(HEAD)
	rootcint -f $@ -c -I$(JAMES_INCLUDE) $(HEAD) bin/build/Linkdef.h

bin/build/%.o: src/%.cpp include/%.h
	$(CC) $(CFLAGS) -o $@ -c $< -I$(JAMES_INCLUDE)

bin/build/%.o: src/*/%.cpp include/%.h
	$(CC) $(CFLAGS) -o $@ -c $< -I$(JAMES_INCLUDE)

clean:
	rm -f $(JAMES_LIB)/bin/build/*.o
	rm -f $(JAMES_LIB)/bin/build/Linkdef.h
	rm -f $(JAMES_LIB)/bin/*.*
	rm -f $(MINI)
	rm -f $(TARG)
	rm -f $(TARGB)