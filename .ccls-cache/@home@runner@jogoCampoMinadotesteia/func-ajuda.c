#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "func-normal.h"
#include "estruturas.h"
#include "func-ajuda.h"
#include "func-auto.h"

// Todo arquivo .c deve incluir o seu correspondente .h

int contar_marcacao_ia(int l, int c, int N, int M, tabuleiro ** mat){
  int count=0;

  for(int i=-1 ; i<=1 ; i++){ // percorrer as 8 casas ao redor da casa l, c
    for(int j=-1 ; j<=1 ; j++){
      if (celula_valida(l+i, c+j, N, M) && mat[l+i][c+j].ia_marca) count++;
    }
  }
  return count;
}

int contar_nao_clicados(int l, int c, int N, int M, tabuleiro ** mat){
  int count=0;

  for(int i=-1 ; i<=1 ; i++){  // percorrer as 8 casas ao redor da casa l, c
    for(int j=-1 ; j<=1 ; j++){
      if (celula_valida(l+i, c+j, N, M) && !mat[l+i][c+j].clicado) count++;
    }
  }
  
  return count;
}

int marcacao_ia_bomba(tabuleiro ** mat){
  int count=0;
  /*  a função ira verificar todas as celulas que foram clicadas e possuem uma quantidade de bombas adjacentes >= 0. as células que tiverem o numero de bombas iguais ao numero de celulas não clicadas são marcadas pela i.a como tendo uma bomba, sem utilização de informações da struct sobre o posicionamento das bombas */

  int N = LINHAS;
  int M = COLUNAS;
  int a=0, b=0, l=0, c=0;

  for (l=0 ; l < N ; l++){     // percorrer todas as casas do tabuleiro
    for (c=0 ; c < M ; c++){
      
      a = mat[l][c].qtd_bombas;      
      // variavel para arm qtd de bombas
      b = contar_nao_clicados(l, c, N, M, mat); 
      // variavel para contar quantas casas ao redor dessa casa não foram clicadas
      
      if (a == b && a!=0 && b!=0){    
        
        for(int i=(-1) ; i<=1 ; i++){
          for(int j=(-1); j<=1 ; j++){
            // // percorrer as 8 casas ao redor da casa[l][c]
            
            if (celula_valida(l+i, c+j, N, M)){
              // verifica se a casa está dentro do tabuleiro
              
              if (!mat[l+i][c+j].clicado){
                // o que não foi clicado será marcado como bomba
                mat[l+i][c+j].ia_marca = true;
                count++;
              }
            }
          }
        }
      }
    }
  }
  return count;
}

Bool verificar_vizinhos (tabuleiro ** mat, int l, int c) {

  int N = LINHAS;
  int M = COLUNAS;
  Bool tem_mais_de_um_vizinho_clicado = false;
  int count=0;
  
  for(int i=-1 ; i<=1 ; i++){ // percorrer as 8 casas ao redor da casa[l][c]
    for(int j=-1 ; j<=1 ; j++){
      if (celula_valida(l+i, c+j, N, M) && mat[l+i][c+j].clicado && mat[l+i][c+j].qtd_bombas>0) {
        count++;
        if (count>1) {
          tem_mais_de_um_vizinho_clicado = true;
          return tem_mais_de_um_vizinho_clicado;
        }
      }
    }
  }
  return tem_mais_de_um_vizinho_clicado;
}

int * clicar_primeira_casa(int l, int c, int*r, tabuleiro ** mat){

  int N = LINHAS;
  int M = COLUNAS;

  for(int i=-1 ; i<=1 ; i++){
    for(int j=-1 ; j<=1 ; j++){
      if(celula_valida(l+i, c+j, N, M)){
        if(!mat[l+i][c+j].clicado){
          printf("As coordenadas [%d : %d] ", (l+i)+1, (c+j)+1);
          printf("tem baixas chances de ser uma bomba\n");
          r[0] = l+i;
          r[1] = c+j;
          return r;
        }
      }
    }
  }
}

  /* 
    para cada célula já clicada, a função pedir_ajuda irá armazenar 3 valores: a quantidade de bombas atual, quantas células adjacentes não foram clicadas e quantas células adjacentes foram marcadas pela função anterior. Em seguida, escolherá como celula principal que tenha a menor quantidade de bombas em relação a quantidade de celulas não clicadas e celulas marcadas. Em seguida, irá imprimir, dentre as celulas adjacentes, qual deve ser clicada que não foi marcada e não foi clicada.
  */

int *pedir_ajuda(tabuleiro ** mat){

  int qtd_marcados = marcacao_ia_bomba(mat);
  /* caso a quantidade marcações da i.a seja igual a zero, escolher uma casa que tenha a menor chance de ter uma bomba ao redor, ou seja, que tenha o menor*/ 

  int N = LINHAS;
  int M = COLUNAS;
  int *r = malloc(sizeof(int)*2);

  int l=0, c=0, x=0, y=0, z=0;

  if (qtd_marcados == 0){

    int ctrl_prct = 1;
    
    while (ctrl_prct<100){

    for (l=0 ; l < N ; l++){
      for (c=0 ; c < M ; c++){

        float dif=0;
        
        if (mat[l][c].clicado){
          x = mat[l][c].qtd_bombas;
          y = contar_nao_clicados(l,c,N,M,mat);
          dif = (x/y)*10;
        }
        if (dif <= ctrl_prct){
          r = clicar_primeira_casa(l, c, r, mat);
          }
        }
      }
    }
    ctrl_prct++;
    }

  int ctrl_qtd = 1;
    /* o primeiro ctrl serve para que a casa escolhida seja sempre a com a menor quantidade de bombas ao redor possível */
  while(ctrl_qtd < 8){ 
    int ctrl_dif = 1;
        /* o segundo ctrl serve para que a diferença entre a quantidade de casas adjascentes marcadas e nao clicadas seja a menor possível*/
    while(ctrl_dif < 8){
    
    for (l=0 ; l < N ; l++){
      for (c=0 ; c < M ; c++){

        if (mat[l][c].clicado && mat[l][c].qtd_bombas == ctrl_qtd){ 
  
          x = mat[l][c].qtd_bombas;
          y = contar_nao_clicados(l,c,N,M,mat);
          z = contar_marcacao_ia(l,c,N,M,mat);
          
          if (x==0) {
            r = clicar_primeira_casa(l, c, r, mat);
          }

          //printf("x:%d, y:%d, z:%d, dif:%f\n ",x,y,z, dif);
          
          if (y>z && z!=0 && x-z <= ctrl_dif){
          
    
            for(int i=-1 ; i<=1 ; i++){
              for(int j=-1 ; j<=1 ; j++){
  
                if(celula_valida(l+i, c+j, N, M)){
                  
                  if(!mat[l+i][c+j].clicado && !mat[l+i][c+j].ia_marca){
                    printf("Selecione a opção e escolha as coordenadas [%d : %d]\n", (l+i)+1, (c+j)+1); 
                    r[0] = l+i;
                    r[1] = c+j;
                    return r;
                  }
                }
              }
            }
          }
          //
        }
      }
    }
    ctrl_dif++;
    }
    ctrl_qtd++;
  }/*

  // só irá gerar um valor aleatório se não retornar nenhum valor com base nas regras do jogo da IA
  srand(time(NULL));
  r[0] = rand() % N;
  r[1] = rand() % M;
  printf("Puxando um aleatório [%d][%d] \n", r[0], r[1]);
    while (!celula_valida(r[0], r[1], N, M) || mat[r[0]][r[1]].clicado) {
      r[0] = rand() % N;
      r[1] = rand() % M;
    }
  return r;*/
}