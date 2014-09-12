/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
 *
 * SCC0218 • Algoritmos Avançados e Aplicações
 *
 * Projeto 01 • Backtracking
 * sudoku.cpp
 *
 * Gil Barbosa Reis                     NUSPº 8532248
 * Leonardo Sampaio Ferraz Ribeiro      NUSPº 8532300
 *
 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */

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
    
    // executa cálculos necessários para diferentes otimizações
    if (verificacao_adiante || verificacao_adiante_e_MVR)
        prepara_verificacao_adiante();
    if (verificacao_adiante_e_MVR)
        prepara_MVR();
    
    // da início a recursão do algoritmo de backtracking
    backtracking_recursivo();
}

bool Sudoku::backtracking_recursivo() {
    
    // auxiliares
    int valor_possivel;
    
    // checa se uma solução válida foi encontrada
    if (eh_uma_solucao() && eh_um_jogo_valido())
        return true;
    
    // seleciona posição que será trabalhada neste passo
    pair<int, int> posicao_atual = proxima_casa();
    
    // para cada valor possível
    while ((valor_possivel = valor_possivel_para_esta_posicao(posicao_atual)) != NENHUM) {
        
        // checa se a jogada é válida
        if (eh_uma_jogada_valida(posicao_atual, valor_possivel)) {
            
            // faz a atribuição e incrementa o contador
            faz_atribuicao(posicao_atual, valor_possivel);
            
            // recursivamente parte para próxima casa
            if (backtracking_recursivo()) {
                return true;
            }
            
            // desiste deste valor, desfaz atribuição
            desfaz_atribuicao(posicao_atual);
        }
    }
    
    // não há solução válida nesta configuração
    return false;
}

std::pair<int, int> Sudoku::proxima_casa() {
    
    // checa se deve aplicar a heurística MVR
    if (verificacao_adiante_e_MVR) {
        return posicao_com_MVR();
    }
    
    // percorre todas as posições
    for (int y = 0; y < tam_sudoku; y++) {
        for (int x = 0; x < tam_sudoku; x++) {
            
            // e encontra uma que ainda não tem atribuição
            if (solucao[x][y] == 0)
                return pair<int, int>(x, y);
        }
    }
    
    return pair<int, int>(0, 0);
}

int Sudoku::valor_possivel_para_esta_posicao(pair<int, int> posicao) {
    
    // percorre lista de valores possíveis
    for (int i = 0; i < tam_sudoku; i++) {
        
        // e encontra valor possível
        if (valores_remanescentes[posicao.first][posicao.second][i] == 1) {
            return i+1;
        }
        
    }
    
    // erro! sem valores possíveis
    return NENHUM;
}

void Sudoku::faz_atribuicao(std::pair<int, int> posicao, int valor) {
    
    // faz a atribuição
    solucao[posicao.first][posicao.second] = valor;
    
    // se usar verificação adiante, atualiza as listas de
    // valores possíveis
    if (verificacao_adiante || verificacao_adiante_e_MVR)
        atualiza_listas_de_valores_remanescentes(posicao, 0, valor);
}

void Sudoku::desfaz_atribuicao(std::pair<int, int> posicao) {
    
    // salva valor antigo
    int valor_antigo = solucao[posicao.first][posicao.second];
    
    // faz a atribuição
    solucao[posicao.first][posicao.second] = 0;
    
    // se usar verificação adiante, atualiza as listas de
    // valores possíveis
    if (verificacao_adiante || verificacao_adiante_e_MVR)
        atualiza_listas_de_valores_remanescentes(posicao, valor_antigo, 0);
}

void Sudoku::atualiza_listas_de_valores_remanescentes(std::pair<int, int> posicao, int valor_antigo, int valor_novo) {
    // TODO: Your code here!
}

bool Sudoku::eh_um_jogo_valido() {
    
    // auxiliares
    int contadores_linhas[tam_sudoku][tam_sudoku];
    int contadores_colunas[tam_sudoku][tam_sudoku];
    int contadores_quadrados[tam_sudoku][tam_sudoku];
    
    // inicializa os contadores;
    for (int i = 0; i < tam_sudoku; i++) {
        for (int j = 0; j < tam_sudoku; j++) {
            contadores_linhas[i][j] = contadores_colunas[i][j] = contadores_quadrados[i][j] = 0;
        }
    }
    
    // para cada coluna/linha/quadrado
    for (int i = 0; i < tam_sudoku; i++) {
        
        // para cada posição na determinada linha/coluna/quadrado
        for (int j = 0; j < tam_sudoku; j++) {
            
            // encontra posição no quadrado
            pair<int, int> posicao_no_quadrado = posicao_j_no_quadrado_i(j, i);
            
            // checa se houve alguma repetição
            if ((contadores_linhas[i][solucao[j][i]]++ > 1)
            || (contadores_colunas[i][solucao[i][j]]++ > 1)
            || (contadores_quadrados[i][solucao[posicao_no_quadrado.first][posicao_no_quadrado.second]]++ > 1)) return false;
        }
    }
    
    // jogo válido :D
    return true;
}

bool Sudoku::eh_uma_solucao() {
    
    // percorre o tabuleiro
    for (int y = 0; y < tam_sudoku; y++) {
        for (int x = 0; x < tam_sudoku; x++) {
            
            // se encontrar uma posição sem atribuição,
            // o jogo não está completo
            if (solucao[x][y] == 0)
                return false;
            
        }
    }
    
    // jogo completo, só testar a validade! :D
    return true;
}

bool Sudoku::eh_uma_jogada_valida(std::pair<int, int> posicao, int valor) {
    // TODO: Your code here!
    return false;
}

std::pair<int, int> Sudoku::posicao_com_MVR() {
    // TODO: Your code here!
    return pair<int, int> (1, 1);
}

bool Sudoku::passa_na_verificacao_adiante() {
    // TODO: Your code here!
    return false;
}

void Sudoku::prepara_verificacao_adiante() {
    // TODO: Your code here!
}

void Sudoku::prepara_MVR() {
    // TODO: Your code here!
}

pair<int, int> Sudoku::posicao_j_no_quadrado_i(int j, int i) {
    return pair<int, int>(j%altura_bloco + (altura_bloco*i)%tam_sudoku, j/altura_bloco);
}







