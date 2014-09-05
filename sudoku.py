# Gil Barbosa Reis - 8532248
# SCC 0218 - Algoritmos Avançados e Aplicações
# 31/08/2014

from collections import Counter

altura_bloco = 3
largura_bloco = 3
tam_sudoku = altura_bloco * largura_bloco

class Sudoku:
    """TAD do sudoku, representado em uma matriz 'tam_sudoku x tam_sudoku'.
nota: valores igual a zero são valores não preenchidos no sudoku."""
    def __init__ (self):
        self.matriz = []
        for i in range (tam_sudoku):
            # inicializa cada linha com tam_sudoku zeros: uma matriz nula
            self.matriz.append ([0] for i in range (tam_sudoku))

    def __str__ (self):
        """Representação visual do sudoku em linhas e colunas com os respectivos valores"""
        s = ''
        for i in self.matriz:
            for j in i:
                s += str (j) + ' '
            s += '\n'

        return s[:-1]   # retorna string sem o último '\n'

    def getInput (self, stream):
        """Lê cada valor numérico do sudoku, primeiro por linha, sem o '\\n' e separado pelos espaços"""
        for i in range (tam_sudoku):
            s = ''
            # descarta linhas vazias
            while not s: 
                s = stream.readline ().strip ('\n')
            self.matriz[i] = s.split (' ')
        # transforma as string em int
        for i in range (tam_sudoku):
            for j in range (tam_sudoku):
                self.matriz[i][j] = int (self.matriz[i][j])

    def resolve (self):
        """Mágica! Resolve o tal do sudoku xD"""
        if ehSolucao (self):
            print ('É solução!')
        else:
            print ('Não é solução =/')


# funções que verificam a validade sudoku
def ehSolucao (sud):
    """Verifica se 'sud' é uma solução válida de sudoku. Retorno booleano"""
    # se tem algum zero, não está pronto ainda
    for i in sud.matriz:
        for j in i:
            if j == 0:
                return False
    # se nenhum zero (tabuleiro completo), verifica se é um jogo válido
    return ehJogoValido (sud)

def ehJogoValido (sud):
    """Verifica se 'sud' desrespeita as regras do sudoku. Retorno booleano."""
    # inicializa as listas de verificação
    linhas = [[] for i in range (tam_sudoku)]
    colunas = [[] for i in range (tam_sudoku)]
    quadrados = [[] for i in range (tam_sudoku)]
    # preenche as listas de verificação
    for i in range (tam_sudoku):
        linhas[i] = sud.matriz[i]
        for j in range (tam_sudoku):
            quadrados[altura_bloco * (i//altura_bloco) + j//largura_bloco].append (sud.matriz[i][j])
            colunas[j].append (linhas[i][j])
    # verifica repetições de números nas linhas, colunas e quadrados
    for i in linhas, colunas, quadrados:
        for j in i:
            # pega o contador mais comum em 'j'; se der 2 ou mais, não é jogo válido
            # nota: most_common retorna uma lista com uma tupla com o valor mais
            #  comum e sua contagem, por isso pegamos o valor diretamente com [0][1]
            count = Counter (j).most_common(1)[0][1]
            if count > 1:
                return False
    return True
