#------------------------------------------------------------------------------
# Makefile for main.exe
# Y. Liow
#------------------------------------------------------------------------------
# Macros
#------------------------------------------------------------------------------
CXX 		= g++
CXXFLAGS 	= -g -Wall
LINK 		= g++
LINKFLAGS 	= -lGL -lGLU -lglut -lGLEW
OBJS 		= ../mygllib/config.o \
		  	  ../mygllib/View.o \
		  	  main.o
EXE 		= main.exe

#------------------------------------------------------------------------------
# Executable
#------------------------------------------------------------------------------
$(EXE): 	$(OBJS)
	$(LINK) $(OBJS) -o $(EXE) $(LINKFLAGS)

#------------------------------------------------------------------------------
# Object files
#------------------------------------------------------------------------------
main.o: main.cpp gl2d.h
	$(CXX) $(CXXFLAGS) main.cpp -c -o main.o -I ../mygllib/
config.o: config.cpp config.h
	$(CXX) $(CXXFLAGS) config.cpp -c -o config.o -I ../mygllib/
View.o: View.cpp View.h
	$(CXX) $(CXXFLAGS) View.clean -c -o View.o -I ../mygllib
#------------------------------------------------------------------------------
# Utilities
#------------------------------------------------------------------------------
clean:
	rm -f $(EXE) main.o 
c:
	rm -f $(EXE) main.o 
run:
	./$(EXE)
r:
	./$(EXE)