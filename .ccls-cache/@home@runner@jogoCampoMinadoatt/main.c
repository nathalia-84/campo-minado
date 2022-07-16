#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "estruturas.h"
#include "func-normal.h"

int main(void) {
  //Tabuleiro
  //matriz N por M
  int N = LINHAS;
  int M = COLUNAS;
  tabuleiro ** mat = matriz(N, M);
  //B bombas
  int B = BOMBAS;
  //LINHA_B COLUNA_B
  salvar_bombas(B, mat);
  //percorrer matriz para verificar qtd de bombas vizinhas
  percorrer_matriz (mat);
  //introdução e nome do usuário
  imprimir_intro();
  char nome[255];
  scanf("%s", nome);
  //imprimir menu
  imprimir_menu(nome);
  int opcao;
  scanf("%d", &opcao);
  //processar jogo
  if (opcao==1)
    // começa a contar o tempo
    processar_jogo(mat);
  //liberar espaço de memória
  for(int i=0;i<N;i++){
    free(mat[i]);
  }
  free(mat);
  
  return 0;
} 