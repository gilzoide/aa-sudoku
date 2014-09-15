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
    bool checado[tam_sudoku];
    
    // inicializa lista de valores checados
    for (int i = 0; i < tam_sudoku; i++) checado[i] = false;
        
    // checa se uma solução válida foi encontrada
    if (eh_uma_solucao() && eh_um_jogo_valido())
        return true;
    
    // seleciona posição que será trabalhada neste passo
    pair<int, int> posicao_atual = proxima_casa();
    
    // para cada valor possível
    while ((valor_possivel = valor_possivel_para_esta_posicao(posicao_atual)) != NENHUM) {
        
        // checa se a jogada é válida
        if (eh_uma_jogada_valida(posicao_atual, valor_possivel) && !checado[valor_possivel-1]) {
            
            // marca o valor como checado
            checado[valor_possivel-1] = true;
            
            // faz a atribuição e incrementa o contador
            faz_atribuicao(posicao_atual, valor_possivel);
            
#warning debug code running
            system("clear");
            cout <<  *this;
            
            // verificação adiante
            if ((verificacao_adiante || verificacao_adiante_e_MVR)
            && (!passa_na_verificacao_adiante())) {
                desfaz_atribuicao(posicao_atual);
                continue;
            }
            
            // recursivamente parte para próxima casa
            if (backtracking_recursivo()) {
                return true;
            }
            
            // desiste deste valor, desfaz atribuição
            desfaz_atribuicao(posicao_atual);
        }
        
        retira_lista_de_valores_remanescentes(posicao_atual, valor_possivel, -2);
    }
    
    // restaura valores possíveis para esta posição
    for (int i = 0; i < tam_sudoku; i++)
        if (valores_remanescentes[posicao_atual.first][posicao_atual.second][i] == -2) {
            valores_remanescentes[posicao_atual.first][posicao_atual.second][i-1] = 1;
            valores_remanescentes[posicao_atual.first][posicao_atual.second][tam_sudoku]++;
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
    
    //if (valor_antigo > tam_sudoku)
        //return;
    
    atualiza_listas_de_valores_remanescentes(posicao, valor_antigo, 0);
}

void Sudoku::atualiza_listas_de_valores_remanescentes(std::pair<int, int> posicao, int valor_antigo, int valor_novo) {
    
    // se usar verificação adiante
    if (verificacao_adiante || verificacao_adiante_e_MVR) {
        
        // identifica o quadrado
        int quadrado = posicao.first/altura_bloco + (posicao.second/altura_bloco)*altura_bloco;
        
        // percorre a linha/coluna/quadrado da posição modificada
        for (int i = 0; i < tam_sudoku; i++) {
            
            // encontra posição no quadrado
            pair<int, int> posicao_quadrado = posicao_j_no_quadrado_i(i, quadrado);
            
            pair<int, int> linha(i, posicao.second);
            pair<int, int> coluna(posicao.first, i);
            pair<int, int> quadrado(posicao_quadrado.first, posicao_quadrado.second);
            
            // atualiza listas dos valores afetados
            if (valor_novo > 0) {
                retira_lista_de_valores_remanescentes(linha, valor_novo);
                retira_lista_de_valores_remanescentes(coluna, valor_novo);
                retira_lista_de_valores_remanescentes(quadrado, valor_novo);
            }
            else {
                adiciona_lista_de_valores_remanescentes(linha, valor_antigo);
                adiciona_lista_de_valores_remanescentes(coluna, valor_antigo);
                adiciona_lista_de_valores_remanescentes(quadrado, valor_antigo);
            }
        }
        
        //if (valor_novo == 0)
          //  retira_lista_de_valores_remanescentes(posicao, valor_antigo);
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
            if (((solucao[j][i] > 0)
                 && (++contadores_linhas[i][solucao[j][i]-1] > 1))
            || (((solucao[i][j] > 0)
                 && (++contadores_colunas[i][solucao[i][j]-1] > 1)))
            || (((solucao[posicao_quadrado.first][posicao_quadrado.second] > 0)
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
    if (verificacao_adiante || verificacao_adiante_e_MVR) {
        return true;
    }
    
    // identifica o quadrado (uso do arredondamento de ints (.../altura_bloco)*altura_bloco)
    int quadrado = posicao.first/altura_bloco + (posicao.second/altura_bloco)*altura_bloco;
    
    // verifica todos os valores afetados
    for (int i = 0; i < tam_sudoku; i++) {
        
        // encontra posição no quadrado
        pair<int, int> posicao_quadrado = posicao_j_no_quadrado_i(i, quadrado);
        
        if ((solucao[posicao.first][i] == valor)
        || (solucao[i][posicao.second] == valor)
        || (solucao[posicao_quadrado.first][posicao_quadrado.second] == valor)) {
            
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
    
    // percorre lista ordenada pelo número de valores remanescentes
    std::vector<std::pair<std::pair<int, int>, char*> >::iterator it;
    for (it = nro_de_valores_remanescentes.begin(); it != nro_de_valores_remanescentes.end();
         ++it) {
        
        // checa se um valor não possui atribuição e valores remanescentes
        if ((*(it->second) == 0)
        && (solucao[it->first.first][it->first.second] == 0)) {
            return false;
        }
        
        // se estivermos usando MVR, a lista está ordenada,
        // e qualquer valor > 0 indica que não existem mais valores
        if (verificacao_adiante_e_MVR && *(it->second) > 0) {
            break;
        }
        
    }
    
    // passou! vá ser feliz!
    return true;
}

void Sudoku::prepara_verificacao_adiante() {
    
    // para cada posição no tabuleiro
    for (int y = 0; y < Sudoku::tam_sudoku; y++) {
        for (int x = 0; x < Sudoku::tam_sudoku; x++) {
            
            // identifica o quadrado
            int quadrado = x/altura_bloco + (y/altura_bloco)*altura_bloco;
            pair<int, int> posicao(x, y);
            
            // para cada posição na linha/coluna/quadrado pertencente a este
            for (int i = 0; i < tam_sudoku; i++) {
                
                // encontra posição no quadrado
                pair<int, int> posicao_quadrado = posicao_j_no_quadrado_i(i, quadrado);
                
                if (matriz[i][y] > 0) {
                    retira_lista_de_valores_remanescentes(posicao, matriz[i][y], -1);
                }
                if (matriz[x][i] > 0) {
                    retira_lista_de_valores_remanescentes(posicao, matriz[x][i], -1);
                }
                if (matriz[posicao_quadrado.first][posicao_quadrado.second] > 0) {
                    retira_lista_de_valores_remanescentes(posicao, matriz[posicao_quadrado.first][posicao_quadrado.second], -1);
                }
            }
            
            // adiciona a posição e um ponteiro para o tamanho para o vetor de
            // número de valores remanescentes
            nro_de_valores_remanescentes.push_back(pair<pair<int, int>, char*>(posicao, &valores_remanescentes[x][y][tam_sudoku]));
        }
    }
}

void Sudoku::prepara_MVR() {
    // TODO: Your code here!
}

void Sudoku::prepara_listas_de_valores_remanescentes() {
    
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
    
    // preparação diferenciada para diferentes heurísticas
    if (verificacao_adiante || verificacao_adiante_e_MVR) {
        prepara_verificacao_adiante();
        if (verificacao_adiante_e_MVR)
            prepara_MVR();
    }
    
}

pair<int, int> Sudoku::posicao_j_no_quadrado_i(int j, int i) {
    return pair<int, int>(j%altura_bloco + (altura_bloco*i)%tam_sudoku, j/altura_bloco + (i/altura_bloco)*altura_bloco);
}

void Sudoku::adiciona_lista_de_valores_remanescentes(std::pair<int, int> posicao, int valor) {
    if (valores_remanescentes[posicao.first][posicao.second][valor-1] < 1) {
        valores_remanescentes[posicao.first][posicao.second][valor-1] = 1;
        valores_remanescentes[posicao.first][posicao.second][tam_sudoku]++;
    }
    
}
void Sudoku::retira_lista_de_valores_remanescentes(std::pair<int, int> posicao, int valor, int estado) {
    if (valores_remanescentes[posicao.first][posicao.second][valor-1] == 1) {
        valores_remanescentes[posicao.first][posicao.second][valor-1] = estado;
        valores_remanescentes[posicao.first][posicao.second][tam_sudoku]--;
    }
}





