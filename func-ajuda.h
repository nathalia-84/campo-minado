#include <time.h>
#include "estruturas.h"

#ifndef FUNCOESAJUDA_H_
#define FUNCOESAJUDA_H_

//declaração das funções

int contar_nao_clicados(int l, int c, int N, int M, tabuleiro ** mat);

int marcacao_ia_bomba(tabuleiro ** mat);

int marcacao_ia_limpo(tabuleiro ** mat);

int contar_marcacao_ia(int l, int c, int N, int M, tabuleiro ** mat);

int * nenhuma_celula_marcada(tabuleiro ** mat, int * r);

int * clicar_limpas(tabuleiro ** mat, int * r);

int *pedir_ajuda(tabuleiro ** mat);

#endif
