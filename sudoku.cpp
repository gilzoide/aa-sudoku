#include "sudoku.hpp"

using namespace std;

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

istream& operator>> (istream& is, const Sudoku& sud) {
    for (int i = 0; i < sud.tam_sudoku; i++) {
        for (int j = 0; j < sud.tam_sudoku; j++) {
            is >> sud.matriz[i][j];
        }
    }
    
    return is;
}

void Sudoku::solve(bool verificacao_adiante, bool verificacao_adiante_e_MVR) {
    
    // atribui os parametros de otimizações aos parâmetros do objeto
    this->verificacao_adiante = verificacao_adiante;
    this->verificacao_adiante_e_MVR = verificacao_adiante_e_MVR;
    
    // da início a recursão do algoritmo de backtracking
    backtracking_recursivo();
}

bool Sudoku::backtracking_recursivo() {
    
    // checa se uma solução válida foi encontrada
    if (eh_uma_solucao() && eh_um_jogo_valido())
        return true;
    
    // seleciona posição que será trabalhada neste passo
    pair<int, int> posicao_atual = proxima_casa();
    
    // para cada valor possível
    for (int i = 1; i < (tam_sudoku+1); i++) {
        
        // checa se a jogada é válida
        if (eh_uma_jogada_valida(posicao_atual, i)) {
            
            // faz a atribuição e incrementa o contador
            solucao[posicao_atual.first][posicao_atual.second] = i;
            
            // recursivamente parte para próxima casa
            if (backtracking_recursivo()) {
                return true;
            }
            
            // desiste deste valor, desfaz atribuição
            solucao[posicao_atual.first][posicao_atual.second] = 0;
        }
    }
    
    // não há solução válida nesta configuração
    return false;
}

std::pair<int, int> Sudoku::proxima_casa() {
    return pair<int, int> (1, 1);
}

bool Sudoku::eh_um_jogo_valido() {
    return false;
}

bool Sudoku::eh_uma_solucao() {
    return false;
}

bool Sudoku::eh_uma_jogada_valida(std::pair<int, int> posicao, int valor) {
    return false;
}


