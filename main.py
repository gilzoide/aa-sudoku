#!/bin/env python
# Linha acima permite rodar o script direto pelo shell

# Gil Barbosa Reis - 8532248
# SCC 0218 - Algoritmos Avançados e Aplicações
# 31/08/2014

import sys
from sudoku import Sudoku

a = Sudoku ()

num_testes = int (input ())

a.getInput (sys.stdin)
print (a)
