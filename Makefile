#
#
#	James Root Analysis Tools Library
#	20 April 2017
#	james.smallcombe@outlook.com
#
#

ROOT_LIBS = `root-config --glibs`
ROOT_GCC_FLAGS = `root-config --cflags`

JAMES_LIB = $(shell pwd)
JAMES_INCLUDE = $(shell pwd)/include

CC = g++
CFLAGS = -std=c++11 -g -fPIC -Wall $(ROOT_GCC_FLAGS) -I$(JAMES_INCLUDE)
#-Xlinker --verbose -std=c++0x -I$(JAMESLIB)/include

LIBRS = -L$(JAMES_INCLUDE) $(ROOT_LIBS)

HEAD = $(wildcard include/james*.h)
OBJECTS = $(patsubst include/%.h,bin/build/%.o,$(HEAD))

TARG = bin/libJanalysistools.so
	
# OBJECTS+= bin/build/yield.o
# OBJECTSEX+= bin/build/yield.o

main: $(TARG)

date:
	bash bin/build/date.sh $(HEAD)
	
$(TARG): $(OBJECTS) bin/DictOutput.cxx
	$(CC) $(CFLAGS) -o $@ -shared bin/DictOutput.cxx $(OBJECTS) -I. $(LIBRS) $(EXTERNAL_LIBS)
	bash bin/build/header.sh
	bash bin/build/make_export.sh

bin/DictOutput.cxx: $(HEAD)
	bash bin/build/link.sh $(HEAD)
	rootcint -f $@ -c -I$(JAMES_INCLUDE) $(HEAD) bin/build/Linkdef.h

bin/build/%.o: src/%.cpp include/%.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LIBRS)

bin/build/%.o: src/*/%.cpp include/%.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LIBRS)

clean:
	rm -f $(JAMES_LIB)/bin/build/*.o
	rm -f $(JAMES_LIB)/bin/build/Linkdef.h
	rm -f $(JAMES_LIB)/bin/*.*
	rm -f $(MINI)
	rm -f $(TARG)
	rm -f $(TARGB)

