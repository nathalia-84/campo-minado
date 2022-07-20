#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "func-normal.h"
#include "estruturas.h"
#include "func-auto.h"

// Todo arquivo .c deve incluir o seu correspondente .h
#include "func-ajuda.h"



int contar_marcacao_ia(int l, int c, int N, int M, tabuleiro ** mat){
  /*
  A função irá contar a quantidade de casas ao redor da casa mat[l][c] que foram marcadas como bomba pela IA.
  */
  
  int count=0;

  // percorre as 8 casas ao redor da casa mat[l][c]
  for(int i=-1 ; i<=1 ; i++){ 
    for(int j=-1 ; j<=1 ; j++){
      if (celula_valida(l+i, c+j, N, M) && mat[l+i][c+j].ia_marca) count++;
    }
  }
  return count;
}

int contar_nao_clicados(int l, int c, int N, int M, tabuleiro ** mat){
  /*
  A função irá contar a quantidade de casas ao redor da casa mat[l][c] que ainda não foram clicadas.
  */
  
  int count=0;

  // percorre as 8 casas ao redor da casa mat[l][c]
  for(int i=-1 ; i<=1 ; i++){  
    for(int j=-1 ; j<=1 ; j++){
      if (celula_valida(l+i, c+j, N, M) && !mat[l+i][c+j].clicado) count++;
    }
  }
  
  return count;
}

int marcacao_ia_bomba(tabuleiro ** mat){
  int count=0;
  /*
  A função irá verificar todas as celulas que foram clicadas e possuem uma     quantidade de bombas adjacentes >= 0. As células que tiverem o número de bombas iguais ao número de celulas não clicadas são marcadas pela IA como tendo uma bomba, sem utilização de informações da struct sobre o posicionamento das bomba.
  */

  int N = LINHAS;
  int M = COLUNAS;
  int a=0, b=0, l=0, c=0;

  // percorre as 8 casas ao redor da casa mat[l][c]
  for (l=0 ; l < N ; l++){     
    for (c=0 ; c < M ; c++){
      
      // variável para armazenar a quantidade de bombas ao redor de mat[l][c]
      a = mat[l][c].qtd_bombas; 
      
      // variável para contar quantas casas ao redor de mat[l][c] não foram clicadas
      b = contar_nao_clicados(l, c, N, M, mat); 
      
      // condição para verificar 1ª regra de jogo da IA
      // verifica se a quantidade de bobas ao redor da casa mat[l][c]
      // é igual à quantidade de casas não clicadas ao redor de mat[l][c]
      if (a == b && a!=0 && b!=0){    

        // percorre as 8 casas ao redor da casa mat[l][c]
        for(int i=(-1) ; i<=1 ; i++){
          for(int j=(-1); j<=1 ; j++){
            
            // verifica se a casa está dentro do tabuleiro
            if (celula_valida(l+i, c+j, N, M)){
              
              // as casas que ainda não foram clicadas serão marcadas como bomba
              if (!mat[l+i][c+j].clicado){
                mat[l+i][c+j].ia_marca = true;
                count++;
              }
            }
          }
        }
      }
    }
  }
  // retorna a quantidade de bombas marcadas pela IA
  return count;
}

Bool verificar_vizinhos (tabuleiro ** mat, int l, int c) {
  /*
  A função irá verificar se uma determinada casa mat[l][c] tem mais de um vizinho clicado e com bombas ao redor dela.
  */

  int N = LINHAS;
  int M = COLUNAS;
  Bool tem_mais_de_um_vizinho_clicado = false;
  int count=0;

  // percorre as 8 casas ao redor da casa mat[l][c]
  for(int i=-1 ; i<=1 ; i++){ 
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

  

int *pedir_ajuda(tabuleiro ** mat){
  /* 
    para cada célula já clicada, a função pedir_ajuda irá armazenar 3 valores: a quantidade de bombas atual, quantas células adjacentes não foram clicadas e quantas células adjacentes foram marcadas pela função anterior. Em seguida, escolherá como celula principal que tenha a menor quantidade de bombas em relação a quantidade de celulas não clicadas e celulas marcadas. Em seguida, irá imprimir, dentre as celulas adjacentes, qual deve ser clicada que não foi marcada e não foi clicada.
  */

  int qtd_marcados = marcacao_ia_bomba(mat);
   

  int N = LINHAS;
  int M = COLUNAS;
  int *r = malloc(sizeof(int)*2);

  int l=0, c=0, x=0, y=0, z=0;

  /* caso a quantidade marcações da IA seja igual a zero, escolher uma casa que tenha a menor chance de ter uma bomba ao redor, ou seja, que tenha o menor*/
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

    for (l=0 ; l < N ; l++){
      for (c=0 ; c < M ; c++){

        if (mat[l][c].clicado){ 
  
          x = mat[l][c].qtd_bombas;
          y = contar_nao_clicados(l,c,N,M,mat);
          z = contar_marcacao_ia(l,c,N,M,mat);
          
          if (x==0) {
            r = clicar_primeira_casa(l, c, r, mat);
          }

          //printf("x:%d, y:%d, z:%d, dif:%f\n ",x,y,z, dif);
          
          if (y>z && z!=0){
          
    
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
        }
      }
    }
}