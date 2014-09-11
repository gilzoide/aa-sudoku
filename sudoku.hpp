#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iostream>

class Sudoku {
    
	friend std::ostream& operator<< (std::ostream& os, const Sudoku& sud);
    friend std::istream& operator>> (std::istream& is, const Sudoku& sud);

public:
	const static int altura_bloco = 3;
	const static int largura_bloco = 3;
	const static int tam_sudoku = altura_bloco * largura_bloco;

    /**
     * Construtor Default
     * sem argumentos
     */
	Sudoku ();
    
	/**
     * Construtor que lê matriz de entradas
     * do usuário e constrói o jogo de Sudoku
     *
     * @param pega_da_stdin
     * Flag paraindicar se a leitura de input deve
     * ser realizada ou não
     *
     */
	Sudoku (bool pega_da_stdin);
    
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
     * Encontra a próxima casa
     * do jogo que deve ser trabalhada
     *
     * @return 
     * posição da próxima casa em um pair<x, y>
     */
    std::pair<int, int> proxima_casa();
    
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
};

#endif
