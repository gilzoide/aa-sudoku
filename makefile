# Makefile do sudoku pra AAA

objs = main.o sudoku.o
exe = resolvedorDeSudoku
CXX = g++
CXXFLAGS = -g -Wall -O2 -pipe -std=c++11


all : $(objs)
	$(CXX) $(CXXFLAGS) $(objs) -o $(exe)

main.o : main.cpp sudoku.o
	$(CXX) $(CXXFLAGS) -c $<

sudoku.o : sudoku.cpp sudoku.hpp
	$(CXX) $(CXXFLAGS) -c $<

run :
	@./$(exe)


clean :
	$(RM) *~ *.o $(exe)
