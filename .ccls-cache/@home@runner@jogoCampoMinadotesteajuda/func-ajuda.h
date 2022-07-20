#include <time.h>
#include "estruturas.h"

#ifndef FUNCOESAJUDA_H_
#define FUNCOESAJUDA_H_

//declaração das funções

int contar_nao_clicados(int l, int c, int N, int M, tabuleiro ** mat);

void marcacao_ia(tabuleiro ** mat);

int contar_marcacao_ia(int l, int c, int N, int M, tabuleiro ** mat);

int *pedir_ajuda(tabuleiro ** mat);

#endif
