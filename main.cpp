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

int main (int argc, char *argv[]) {
	// otimização a ser usada para resolver: vem como argumento
	Otimizacoes opt = NENHUMA;
	string arg;
	if (argc > 1) {
		arg = argv[1];
		// verificação adiante
		if (arg == "-f" || arg == "--fc") {
			opt = FC;
		}
		// mínimos valores remanescentes
		else if (arg == "-m" || arg == "--mvr") {
			opt = MVR;
		}
		// mostra ajuda (como usar esse belo programa), e não executa
		else if (arg == "-h" || arg == "--help") {
			cout <<
"Resolvedor de sudokus.\n\
Uso: resolvedorDeSudoku [OPÇÃO]\n\
Opções aceitas:\n\
\t-f ou --fc: resolver usando verificação adiante\n\
\t-m ou --mvr: resolver usando verificação adiante e heurística de mínimos \
valores remanescentes\n";
			return 0;
		}
	}
    
	int num_testes;
	cin >> num_testes;

	// laço principal
	for (int i = 0; i < num_testes; i++) {
		Sudoku teste (true);
		teste.solve (opt);
		cout << "sudoku " << i + 1 << ":\n" << teste << '\n';
	}

	return 0;
}
