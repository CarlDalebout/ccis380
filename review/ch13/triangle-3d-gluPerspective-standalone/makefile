# Makefile for mygllib
# Y. Liow
#------------------------------------------------------------------------------
# Macros
#------------------------------------------------------------------------------
CXX       = g++
CXXFLAGS  = -g -Wall
LINK      = g++
LINKFLAGS = -lGL -lGLU -lglut
#OBJS      = config.o View.o Reshape.o SingletonView.o Keyboard.o
OBJS      = main.o 
EXE       = main.exe

#------------------------------------------------------------------------------
# Executable
#------------------------------------------------------------------------------
$(EXE):	*.cpp *.h
	$(CXX) *.cpp $(LINKFLAGS) -o $(EXE)

#------------------------------------------------------------------------------
# Build all obj codes
#------------------------------------------------------------------------------
#all:	$(OBJS)
#	$(NOOP)
#------------------------------------------------------------------------------
# Object files
#------------------------------------------------------------------------------
#config.o: config.h config.cpp
#	$(CXX) $(CXXFLAGS) config.cpp -c -o config.o
#
#View.o: View.h View.cpp
#	$(CXX) $(CXXFLAGS) View.cpp -c -o View.o
#
#SingletonView.o: SingletonView.h SingletonView.cpp
#	$(CXX) $(CXXFLAGS) SingletonView.cpp -c -o SingletonView.o
#
#Reshape.o: Reshape.h Reshape.cpp
#	$(CXX) $(CXXFLAGS) Reshape.cpp -c -o Reshape.o
#
#Keyboard.o: Keyboard.h Keyboard.cpp
#	$(CXX) $(CXXFLAGS) Keyboard.cpp -c -o Keyboard.o

#------------------------------------------------------------------------------
# Utilities
#------------------------------------------------------------------------------
run:
	./$(EXE)
r:
	./$(EXE)
clean:
	rm -f $(OBJS) $(EXE)
c:
	rm -f $(OBJS) $(EXE)
