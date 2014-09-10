/*
 * Resolvedor de Sudoku, pra AAA
 */

#include "sudoku.hpp"
#include <iostream>

using namespace std;

int main () {
	int num_testes;
	cin >> num_testes;

	// laço principal
	for (int i = 0; i < num_testes; i++) {
		Sudoku teste (true);
		cout << "sudoku " << i + 1 << ":\n" << teste << '\n';
	}

	return 0;
}
