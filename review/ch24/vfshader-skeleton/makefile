# Makefile for main
# Y. Liow
#------------------------------------------------------------------------------
# Macros
#------------------------------------------------------------------------------
CXX       = g++
CXXFLAGS  = -g -Wall
LINK      = g++
LINKFLAGS = -lGL -lGLU -lglut -lGLEW
OBJS1     = ../mygllib/config.o ../mygllib/View.o
OBJS2     = main.o
EXE       = main.exe

#------------------------------------------------------------------------------
# Executable
#------------------------------------------------------------------------------
$(EXE):	*.cpp
	$(LINK) $(LINKFLAGS) *.cpp -o $(EXE) -DGL_GLEXT_PROTOTYPES

#------------------------------------------------------------------------------
# Object files
#------------------------------------------------------------------------------
main.o:	main.cpp 
	$(CXX) $(CXXFLAGS) main.cpp -c -o main.o -I../mygllib -DGL_GLEXT_PROTOTYPES

#------------------------------------------------------------------------------
# Utilities
#------------------------------------------------------------------------------
clean:
	rm $(OBJS2) $(EXE)
c:
	rm $(OBJS2) $(EXE)

run:
	./$(EXE)
r:
	./$(EXE)

main.jpg: $(EXE)
	xcapture --program=main.exe --filename=main.jpg
