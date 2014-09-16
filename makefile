# Makefile do sudoku pra AAA

objs = main.o sudoku.o
exe = resolvedorDeSudoku
CXX = g++
CXXFLAGS = -Wall -O2 -pipe -std=c++11


all : $(objs)
	$(CXX) $(CXXFLAGS) $(objs) -o $(exe)

# make debug adiciona -DDEBUG e chama o all ali encima
debug : CXXFLAGS += -DDEBUG -g
debug : clean
debug : all

main.o : main.cpp sudoku.o
	$(CXX) $(CXXFLAGS) -c $<

sudoku.o : sudoku.cpp sudoku.hpp
	$(CXX) $(CXXFLAGS) -c $<

run :
	@./$(exe)


clean :
	$(RM) *~ *.o $(exe)
