/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
 *
 * SCC0218 • Algoritmos Avançados e Aplicações
 *
 * Projeto 01 • Backtracking
 * sudoku.hpp
 *
 * Gil Barbosa Reis                     NUSPº 8532248
 * Leonardo Sampaio Ferraz Ribeiro      NUSPº 8532300
 *
 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */

#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iostream>
#include <vector>

#define NENHUM -1

class Sudoku {
    
	friend std::ostream& operator<< (std::ostream& os, const Sudoku& sud);
    friend std::istream& operator>> (std::istream& is, const Sudoku& sud);

public:
    
    /// constantes do jogo
	const static int altura_bloco = 3;
	const static int largura_bloco = 3;
	const static int tam_sudoku = altura_bloco * largura_bloco;
    
	/**
     * Construtor que lê matriz de entradas
     * do usuário e constrói o jogo de Sudoku
     *
     * @param pega_da_stdin
     * Flag paraindicar se a leitura de input deve
     * ser realizada ou não
     *
     */
	Sudoku (bool pega_da_stdin = true);
    
    /**
     * Resolve um jogo de Sudoku utilizando 
     * um algoritmo de backtracking com diversas
     * modificações voltadas a um melhor desempenho
     *
     * @param verificacao_adiante
     * flag: backtracking com verificação adiante. backtracking
     * é realizado quando uma variável fica sem nenhum valor
     * disponível;
     *
     * @param verificacao_adiante_e_MVR
     * flag: backtracking com verificação adiante e mínimos 
     * valores remanescentes. Idem ao anterior com a adição da
     * heurística MVR para decidir a próxima variável.
     */
    void solve(bool verificacao_adiante = false, bool verificacao_adiante_e_MVR = false);
    

private:
	
    /// matriz original do jogo
    int matriz[tam_sudoku][tam_sudoku];
    
    /// matriz com possível solução
    int solucao[tam_sudoku][tam_sudoku];
    
    /** 
     * Matriz de Valores Remanescentes
     * cada posição possui o valor 0 ou 1 indicando se x pode
     * ser utlizado ou não, a última posição contem a quantidade
     * de valores remanescentes
     */
    char valores_remanescentes[tam_sudoku][tam_sudoku][tam_sudoku+1];
    
    /**
     * Vetor de Número Valores Remanescentes
     * cada posição no vetor contém um pair contendo a 
     * posição desta variável e o número de valores
     * remanescentes (um ponteiro para parte da estrutura
     * valores_remanescentes declarada acima)
     *
     * deve ser mantido ordenado por número de valores
     * remanescentes
     */
    std::vector<std::pair<std::pair<int, int>, char*> > nro_de_valores_remanescentes;
    
    /// contador de atribuições
	int cont = 0;
    
    /// flag, indica se o jogo foi resolvido
    bool resolvido = false;
    
    /// flags, indicam otimizações no algorítmo
    bool verificacao_adiante, verificacao_adiante_e_MVR;
    
    /**
     * Executa um algoritmo recursivo do tipo
     * backtracking para resolver o jogo de Sudoku
     *
     * @return
     * retorna verdadeiro para solução encontrada
     * falsa no caso contrário
     */
    bool backtracking_recursivo();
    
    /**
     * Busca posição no tabuleiro usando
     * a heurística de [mínimos valores remanescentes]
     *
     * @return
     * posição que possui o mínimo de valores remanescentes
     */
    std::pair<int, int> posicao_com_MVR();
    
    /**
     * Executa a verificação adiante para identificar 
     * se um determinado movimento vai render um futuro
     * jogo válido
     *
     * @return
     * verdadeiro se possível jogo válido no futuro, 
     * falso no caso contrário
     */
    bool passa_na_verificacao_adiante();
    
    /**
     * Prepara os atributos necessários para 
     * realizar a verificação adiante
     */
    void prepara_verificacao_adiante();
    
    /**
     * Prepara os atributos necessários para
     * utlizar a heurística MVR
     */
    void prepara_MVR();
    
    /**
     * Prepara as listas de valores remanescentes
     */
    void prepara_listas_de_valores_remanescentes();
    
    /**
     * Encontra a próxima casa
     * do jogo que deve ser trabalhada
     *
     * @return 
     * posição da próxima casa em um pair<x, y>
     */
    std::pair<int, int> proxima_casa();
    
    /**
     * Faz a atribuição na posição desejada
     * caso faça o uso da verificação adiante, atualiza
     * a lista de valores possíveis
     *
     * @param posicao
     * posição onde será feita atribuição
     *
     * @param valor
     * valor que será atribuído
     */
    void faz_atribuicao(std::pair<int, int> posicao, int valor);
    
    /**
     * Desfaz a atribuição na posição desejada
     * caso faça o uso da verificação adiante, atualiza
     * a lista de valores possíveis
     *
     * @param posicao
     * posição onde será desfeita a atribuição
     */
    void desfaz_atribuicao(std::pair<int, int> posicao);
    
    /**
     * atualiza as lista de valores remanescentes
     *
     * @param posicao
     * posição onde será feita atribuição
     *
     * @param valor_antigo
     * valor que existia anteriormente
     *
     * @param valor_novo
     * valor que foi atribuído
     */
    void atualiza_listas_de_valores_remanescentes(std::pair<int, int> posicao, int valor_antigo, int valor_novo);
    
    /** 
     * auxiliares para retirar ou adicionar um valor a
     * lista de valores remanescentes
     */
    void adiciona_lista_de_valores_remanescentes(std::pair<int, int> posicao, int valor);
    void retira_lista_de_valores_remanescentes(std::pair<int, int> posicao, int valor, int estado = 0);
    
    /**
     * Verifica se o jogo é válido, se respeita as regras
     *
     * @return 
     * verdadeiro para jogo válido, falso caso contrário
     */
    bool eh_um_jogo_valido();
    
    /**
     * Verifica se o jogo é uma solução
     * (não possui nenhuma casa com 0's)
     * Não checa a validade do jogo
     *
     * @return
     * verdadeiro para solução, falso caso contrário
     */
    bool eh_uma_solucao();
    
    /**
     * Verifica se a jogada em questão é válida
     *
     * @param posicao
     * posição na qual se deseja fazer a jogada
     *
     * @param valor
     * valor que deseja atribuir
     *
     * @return
     * verdadeiro para jogada válida, falso caso contrário
     */
    bool eh_uma_jogada_valida(std::pair<int, int> posicao, int valor);
    
    /**
     * Retorna uma posição em relação a sua posição 
     * em determinado quadrado
     */
    std::pair<int, int> posicao_j_no_quadrado_i(int j, int i);
    
};

#endif
