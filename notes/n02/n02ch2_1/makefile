#==========================================================
# Makefile for main.exe
# Carl Dalebout
#==========================================================

#==========================================================
# Macros
#==========================================================
CXX 			= g++
CXXFLAGS	= -g -Wall
LINK			= g++
LINKFLAGS	= -lGL -lGLU -lglut -lGLEW
OBJS			= main.o
EXE				= main.exe

#==========================================================
# Executable
#==========================================================
$(EXE):		$(OBJS)
	$(LINK) $(OBJS) -o $(EXE) $(LINKFLAGS)

#==========================================================
# Object files
#==========================================================
main.o: 	main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -c -o main.o

#==========================================================
# Utilities
#==========================================================
clean:
	rm -f $(EXE) main.o
c:
	rm -f $(EXE) main.o
run:
	./$(EXE)
r:
	./$(EXE)
	
push:
	git add .
	git commit
	git push origin master
p:
	git add .
	git commit
	git push origin master