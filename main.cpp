/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
 *
 * SCC0218 • Algoritmos Avançados e Aplicações
 *
 * Projeto 01 • Backtracking
 * main.cpp
 *
 * Gil Barbosa Reis                     NUSPº 8532248
 * Leonardo Sampaio Ferraz Ribeiro      NUSPº 8532300
 *
 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */

#include "sudoku.hpp"
#include <iostream>

using namespace std;

int main () {
    
	int num_testes;
	cin >> num_testes;

	// laço principal
	for (int i = 0; i < num_testes; i++) {
		Sudoku teste (true);
        teste.solve(true);
		cout << "sudoku " << i + 1 << ":\n" << teste << '\n';
	}

	return 0;
}
