#include "sudoku.hpp"

Sudoku::Sudoku () : cont (0) {}

Sudoku::Sudoku (bool pega_da_stdin) {
	Sudoku ();
	if (pega_da_stdin) {
        cin >> this;
	}
}

ostream& operator<< (ostream& os, const Sudoku& sud) {
	for (int i = 0; i < Sudoku::tam_sudoku; i++) {
		for (int j = 0; j < Sudoku::tam_sudoku; j++) {
			os << sud.matriz[i][j] << ' ';
		}
		os << '\n';
	}

	return os;
}

istream& operator>> (istream& is, Sudoku& sud) {
    for (int i = 0; i < tam_sudoku; i++) {
        for (int j = 0; j < tam_sudoku; j++) {
            is >> sud.matriz[i][j];
        }
    }
}
