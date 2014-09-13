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

Sudoku::Sudoku (bool pega_da_stdin) {
	if (pega_da_stdin) {
        for (int y = 0; y < this->tam_sudoku; y++) {
            for (int x = 0; x < this->tam_sudoku; x++) {
                cin >> this->matriz[x][y];
                this->solucao[x][y] = matriz[x][y];
            }
        }
	}
}

ostream& operator<< (ostream& os, const Sudoku& sud) {
    for (int y = 0; y < Sudoku::tam_sudoku; y++) {
        for (int x = 0; x < Sudoku::tam_sudoku; x++) {
			os << sud.solucao[x][y] << ' ';
		}
		os << '\n';
	}

	return os;
}

void Sudoku::solve(bool verificacao_adiante, bool verificacao_adiante_e_MVR) {
    
    // atribui os parâmetros de otimizações aos parâmetros do objeto
    this->verificacao_adiante = verificacao_adiante;
    this->verificacao_adiante_e_MVR = verificacao_adiante_e_MVR;
    
    // prepara_listas_de_valores_remanescentes (!!!)
    prepara_listas_de_valores_remanescentes();
    
    // da início a recursão do algoritmo de backtracking
    if (!backtracking_recursivo()) {
        cout << "Não foi possível encontrar uma solução!" << endl;
    }
    
    // imprime o contador de atribuições
    cout << "\nNúmero de Atribuições: " << this->cont << endl;
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
            
            // verificação adiante
            if ((verificacao_adiante || verificacao_adiante_e_MVR)
            && (!passa_na_verificacao_adiante())) {
                desfaz_atribuicao(posicao_atual);
                continue;
            }
            
#warning debug code running
            //system("clear");
            //cout <<  *this;
            
            // recursivamente parte para próxima casa
            if (backtracking_recursivo()) {
                return true;
            }
            
            // desiste deste valor, desfaz atribuição
            desfaz_atribuicao(posicao_atual);
        }
    }
    
    // se não usar verificação adiante,
    // restaura valores possíveis para esta posição
    if (!(verificacao_adiante || verificacao_adiante_e_MVR)) {
        for (int i = 0; i < tam_sudoku; i++)
            valores_remanescentes[posicao_atual.first][posicao_atual.second][i] = 1;
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

void Sudoku::faz_atribuicao(pair<int, int> posicao, int valor) {
    
    // faz a atribuição
    solucao[posicao.first][posicao.second] = valor;
    
    atualiza_listas_de_valores_remanescentes(posicao, 0, valor);
    
    this->cont++;
}

void Sudoku::desfaz_atribuicao(pair<int, int> posicao) {
    
    // salva valor antigo
    int valor_antigo = solucao[posicao.first][posicao.second];
    
    // faz a atribuição
    solucao[posicao.first][posicao.second] = 0;
    
    atualiza_listas_de_valores_remanescentes(posicao, valor_antigo, 0);
}

void Sudoku::atualiza_listas_de_valores_remanescentes(std::pair<int, int> posicao, int valor_antigo, int valor_novo) {
    
    // atualiza lista da posição modificada
    if (valor_novo != 0) {
        retira_lista_de_valores_remanescentes(posicao, valor_novo);
    }
    
    // se usar verificação adiante
    if (verificacao_adiante || verificacao_adiante_e_MVR) {
        
        // identifica o quadrado
        int quadrado = posicao.first/3 + (posicao.second/3)*3;
        
        // percorre a linha/coluna/quadrado da posição modificada
        for (int i; i < tam_sudoku; i++) {
            
            // encontra posição no quadrado
            pair<int, int> posicao_quadrado = posicao_j_no_quadrado_i(i, quadrado);
            
            // atualiza listas dos valores afetados
            if (valor_novo != 0) {
                retira_lista_de_valores_remanescentes(std::pair<int, int>(i, posicao.second), valor_novo);
                retira_lista_de_valores_remanescentes(std::pair<int, int>(posicao.first, i), valor_novo);
                retira_lista_de_valores_remanescentes(std::pair<int, int>(posicao_quadrado.first, posicao_quadrado.second), valor_novo);
            }
            else {
                adiciona_lista_de_valores_remanescentes(std::pair<int, int>(i, posicao.second), valor_antigo);
                adiciona_lista_de_valores_remanescentes(std::pair<int, int>(posicao.first, i), valor_antigo);
                adiciona_lista_de_valores_remanescentes(std::pair<int, int>(posicao_quadrado.first, posicao_quadrado.second), valor_antigo);
            }
        }
    }
        
        // re-ordena lista com número de valores remanescentes
#warning operação de ordenação aqui!!
    
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
            pair<int, int> posicao_quadrado = posicao_j_no_quadrado_i(j, i);
            
            // checa se houve alguma repetição
            if (((solucao[j][i] != 0)
                 && (++contadores_linhas[i][solucao[j][i]-1] > 1))
            || (((solucao[i][j] != 0)
                 && (++contadores_colunas[i][solucao[i][j]-1] > 1)))
            || (((solucao[posicao_quadrado.first][posicao_quadrado.second] != 0)
                 && (++contadores_quadrados[i][solucao[posicao_quadrado.first][posicao_quadrado.second]-1] > 1)))) return false;
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

bool Sudoku::eh_uma_jogada_valida(pair<int, int> posicao, int valor) {
    
    // se estiver usando verificação adiante,
    // a validade da jogada está garantida pelas listas de
    // valores remanescentes
    if (verificacao_adiante)
        return true;
    
    // identifica o quadrado (uso do arredondamento de ints (.../3)*3)
    int quadrado = posicao.first/3 + (posicao.second/3)*3;
    
    // verifica todos os valores afetados
    for (int i = 0; i < tam_sudoku; i++) {
        
        // encontra posição no quadrado
        pair<int, int> posicao_quadrado = posicao_j_no_quadrado_i(i, quadrado);
        
        if ((solucao[posicao.first][i] == valor)
        || (solucao[i][posicao.second] == valor)
        || (solucao[posicao_quadrado.first][posicao_quadrado.second] == valor)) {
            
            // se não usar otimizações, atualiza lista de valores remanescentes
            if (!(verificacao_adiante_e_MVR || verificacao_adiante))
                retira_lista_de_valores_remanescentes(posicao, valor);
            
            return false;
        }
    }
    
    // Sucesso! :D
    return true;
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
    
    // para cada posição no tabuleiro
    for (int y = 0; y < Sudoku::tam_sudoku; y++) {
        for (int x = 0; x < Sudoku::tam_sudoku; x++) {
            
            // identifica o quadrado
            int quadrado = x/3 + (y/3)*3;
            
            // para cada posição na linha/coluna/quadrado pertencente a este
            for (int i = 0; i < tam_sudoku; i++) {
                
                // encontra posição no quadrado
                pair<int, int> posicao_quadrado = posicao_j_no_quadrado_i(i, quadrado);
                
                // TODO: A LOOOOT!
        
            }
        }
    }
}

void Sudoku::prepara_MVR() {
    // TODO: Your code here!
}

void Sudoku::prepara_listas_de_valores_remanescentes() {
    
    // preparação diferenciada para diferentes heurísticas
    if (verificacao_adiante || verificacao_adiante_e_MVR) {
        prepara_verificacao_adiante();
        if (verificacao_adiante_e_MVR)
            prepara_MVR();
        return;
    }
    
    // percorre todas as posições
    for (int y = 0; y < tam_sudoku; y++) {
        for (int x = 0; x < tam_sudoku; x++) {
            
            // preenche as listas com todos os valores possíveis
            for (int i = 0; i < tam_sudoku; i++) {
                valores_remanescentes[x][y][i] = 1;
            }
            
            valores_remanescentes[x][y][tam_sudoku] = tam_sudoku;
        }
    }
}

pair<int, int> Sudoku::posicao_j_no_quadrado_i(int j, int i) {
    return pair<int, int>(j%altura_bloco + (altura_bloco*i)%tam_sudoku, j/altura_bloco + (i/3)*3);
}







