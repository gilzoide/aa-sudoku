#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iostream>

using namespace std;

class Sudoku {
	friend ostream& operator<< (ostream& os, const Sudoku& sud);
public:
	const static int altura_bloco = 3;
	const static int largura_bloco = 3;
	const static int tam_sudoku = altura_bloco * largura_bloco;

	// Ctor
	Sudoku ();
	// Ctor que já pega valores de 'input'
	Sudoku (bool pega_da_stdin);



private:
	int matriz[tam_sudoku][tam_sudoku];
	int cont;
};

#endif
