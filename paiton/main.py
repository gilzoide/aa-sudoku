#!/bin/env pypy3
# coding: utf-8

# 1ª linha permite rodar o script direto pelo shell;
# preferência pelo pypy que é mais rápido
# 2ª pro trem saber que aqui é raça utf-8!

# Gil Barbosa Reis - 8532248
# Leonardo Sampaio Ferraz Ribeiro - 8532300
# SCC 0218 - Algoritmos Avançados e Aplicações
# 08/09/2014

import sys
from sudoku import Sudoku

num_testes = int (input ())

# executa cada teste (Sudoku)
for i in range (num_testes):
    # cria um sudoku vazio
    a = Sudoku ()
    # lê valores da stdin
    a.getInput (sys.stdin)
    a.resolve ()

    print ('sudoku ', i + 1, ' \n', a, sep = '')
