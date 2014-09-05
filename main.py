#!/bin/env python
# Linha acima permite rodar o script direto pelo shell

# Gil Barbosa Reis - 8532248
# SCC 0218 - Algoritmos Avançados e Aplicações
# 31/08/2014

import sys
from sudoku import *

num_testes = int (input ())

# executa cada teste (Sudoku)
for i in range (num_testes):
    # cria um sudoku vazio
    a = Sudoku ()
    # lê valores da stdin
    a.getInput (sys.stdin)
    a.resolve ()

    print ('sudoku ', i + 1, ' \n', a, sep = '')
