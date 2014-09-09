# Gil Barbosa Reis - 8532248
# Leonardo Sampaio Ferraz Ribeiro - 8532300
# SCC 0218 - Algoritmos Avançados e Aplicações
# 08/09/2014

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
        # Some backtracks and shit
        self.it = 0
        self.goBacktrack (0, 0)
        print ('Terminado na ', self.it + 1, 'ª atribuição na matriz\n', sep='')

    def goBacktrack (self, linha, coluna):
        """Faz um passo no backtrack

        @return True se completou, False se não deu certo"""
        # bloco try/except trata quando acaba o sudoku (que ele passa pra
        # uma linha após a última): retorna se é solução ou não (ou
        # já deu certo ou deu errado e tem que voltar no backtrack)
        try:
            if not ehJogoValido (self):
                return False
            proxLinha, proxColuna = proximo (linha, coluna)
            # se não for 0, vê se tá legal esse negócio
            if self.matriz[linha][coluna] != 0:
                if ehSolucao (self, linha):
                    return True
                elif ehJogoValido (self):
                    return self.goBacktrack (proxLinha, proxColuna)
                else:
                    return False
                    
            # se for 0, joga um número e tenta; se não deu, tenta próximo número
            for i in range (1, tam_sudoku + 1):
                self.matriz[linha][coluna] = i
                self.it += 1
                if self.goBacktrack (proxLinha, proxColuna):
                    return True
            # se por acaso tentar as possibilidades não tenham dado certo, retorna
            self.matriz[linha][coluna] = 0
            return False

        except Exception:
            return ehSolucao (self)

            





# funções que verificam a validade do sudoku
def proximo (linha, coluna):
    """Função que calcula a próxima linha e coluna a serem verificadas.

    @return proxLinha, proxColuna"""
    coluna += 1
    if (coluna >= tam_sudoku):
        linha += 1
        coluna = 0

    return linha, coluna

def ehSolucao (sud, linha = 0):
    """Verifica se 'sud' é uma solução válida de sudoku.

    @param linha De qual linha começa a verificar os zeros
    @return True se for solução; senão False"""
    # se tem algum zero, não está pronto ainda
    for i in range (linha, tam_sudoku):
        for j in range (tam_sudoku):
            if sud.matriz[i][j] == 0:
                return False
    # se nenhum zero (tabuleiro completo), verifica se é um jogo válido
    return ehJogoValido (sud)

def ehJogoValido (sud):
    """Verifica se 'sud' respeita as regras do sudoku.
    
    @return True se for válido; senão False"""
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
        # pra cada linha/coluna/quadrado
        for j in i:
            # contagem dos números de 1 a tam_sudoku (ignora zeros); 
            # se tiver mais de um de algum deles, não é um jogo válido
            for num in range (tam_sudoku):
                if j.count (num + 1) > 1:
                    return False
    return True
