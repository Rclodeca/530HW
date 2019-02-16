#Ryan Clode, Michael Kemper  
#cssc0431, cssc0446  
#CS 530 Spring 2019    
#Assignment #1, XBD  
#Makefile



#Makefile

#Variables

CXX = g++

#Targets

xbd: xbd.o
	$(CXX) -o xbd xbd.o

xbd.o: xbd.cpp xbd.hpp
	$(CXX) -c xbd.cpp



