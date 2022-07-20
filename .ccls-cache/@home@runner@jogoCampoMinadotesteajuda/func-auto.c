#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "func-ajuda.h"
#include "func-normal.h"
#include "estruturas.h"

void clicar_auto(tabuleiro ** mat){

  int l, c;
  int *r = pedir_ajuda(mat);
  l = r[0];
  c = r[1];

  mat[l][c].clicado = true;
  //typedef enum { perdeu = 1, continua = 2, parou = 3, ganhou = 4} Processamento;
}

void processar_jogo_AUTO(tabuleiro ** mat){

  int N = LINHAS;
  int M = COLUNAS;
  int i = 0;
  //time_t p_tempo = time(NULL);
  int estado;
  Bool perdeu_jogo = false;
  Bool venceu_jogo = false;

  
  

  clicar_auto(mat);

  //continuar
  //perder
  //ganhar

  
  
}