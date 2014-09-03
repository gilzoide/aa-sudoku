# Gil Barbosa Reis - 8532248
# SCC 0218 - Algoritmos Avançados e Aplicações
# 31/08/2014

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
            self.matriz.append ([0] * (tam_sudoku))

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
        for i in range (len (self.matriz)):
            s = ''
            # descarta linhas vazias
            while not s: 
                s = stream.readline ().strip ('\n')
            self.matriz[i] = s.split (' ')
