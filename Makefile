#Makefile

#Variables

CXX = g++
CXXFLAGS = -b

#Targets

xbd: xbd.o
    $(CXX) $(CXXFLAGS) -o xbd main.o

xbd.o: xbd.cpp xbd.hpp
    $(CXX) $(CXXFLAGS) -c xbd.cpp



