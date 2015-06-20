# Makefile for DX layer Pan-STARRS

# *****************************************************
# Parameters to control Makefile operation

CXX = gcc
CXXFLAGS =

# ****************************************************
# Entries to bring the executable up to date

CXXFLAGS_BASIC = -g -I. 
CXXFLAGS_LIBXML = -I/usr/include/libxml2

#Use of GNU libxml
LDFLAGS_LIBXML = -lxml2 -lz -lm

LDFLAGS = ${LDFLAGS_LIBXML} 
CXXFLAGS = ${CXXFLAGS_BASIC} ${CXXFLAGS_LIBXML}


PROGRAMS = main

all: main.c validateJobManifest.c
	$(CXX) -o main $(CXXFLAGS) main.c validateJobManifest.c ${LDFLAGS}

#gcc -o main -I/usr/include/libxml2 main.c validateJobManifest.c -lxml2 -lz -lm

clean:
	-rm -f ${PROGRAMS}

