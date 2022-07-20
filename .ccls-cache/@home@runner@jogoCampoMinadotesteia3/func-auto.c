#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "func-ajuda.h"
#include "func-normal.h"
#include "estruturas.h"

void processar_primeira_rodada_AUTO(tabuleiro ** mat){
  
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;

  srand(time(NULL));
  
  l = rand() % N; // retorna um número aleatório de 0 a N
  c = rand() % M; // retorna um número aleatório de 0 a M
  
  salvar_bombas(mat, l, c);
  percorrer_matriz(mat);
  clicar_vizinhos(l, c, N, M, mat); // clicar elemento e seus vizinhos
  marcacao_ia_bomba(mat);

}

Processamento processar_rodada_AUTO(tabuleiro ** mat){
  
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;
  int *res = pedir_ajuda(mat);

  l = res[0];
  c = res[1];

  if(mat[l][c].bomba) { //é bomba
    mat[l][c].clicado = true;
    free(res);
    return perdeu; 
  } else {  //não é bomba
    clicar_vizinhos(l, c, N, M, mat); // clicar elemento e seus vizinhos
    free(res);
  }
  return continua;
  free(res);
}

void processar_jogo_AUTO(tabuleiro ** mat){

  char c;
  
  int N = LINHAS;
  int M = COLUNAS;
  int i = 0;
  int estado;
  int rodada = 1;
  Bool perdeu_jogo = false;
  Bool venceu_jogo = false;

  processar_primeira_rodada_AUTO(mat);
  
  while (!perdeu_jogo && !venceu_jogo) { //enquanto não perdeu e não venceu
    if (i==0) {
      
      imprimir_matriz(mat);

      if(clicou_todas(mat)) {
        sobreviveu();
        revelar_matriz(mat);
        venceu_jogo = true;
      }
    } else {
      estado = processar_rodada_AUTO(mat);
      if(estado == continua) {
        imprimir_matriz(mat);
        rodada++;
        if(clicou_todas(mat)) {
          sobreviveu();
          revelar_matriz(mat);
          venceu_jogo = true;
        }
      }
      
      if (estado == perdeu) {
        game_over();
        printf("Foram jogadas %d rodadas\n", rodada);
        revelar_matriz(mat);
        perdeu_jogo = true;
      } 
    }
    i++;
  }
  
}