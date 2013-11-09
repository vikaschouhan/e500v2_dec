# Makefile for demo test
#
CXX            := g++
EXES           := e500v2_dec_main
SRC_ROOT       := .

HOST_CXXFLAGS  := -I$(SRC_ROOT) -std=c++0x -Wno-narrowing

all: e500v2_dec_main

e500v2_dec_main: main.cpp ppc_dis.h
	$(CXX) $(HOST_CXXFLAGS) -o $@ $<

clean:
	rm -rf $(EXES)

distclean: clean
	echo "Done"

again: clean all
	echo "Built"
