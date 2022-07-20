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

int marcacao_ia_limpo(tabuleiro ** mat){

  int count=0;
  /*
  A função irá verificar todas as celulas que foram clicadas e possuem uma     quantidade de bombas adjacentes >= 0. As células que tiverem o número de bombas iguais ao número de celulas não clicadas são marcadas pela IA como tendo uma bomba, sem utilização de informações da struct sobre o posicionamento das bomba.
  */

  int N = LINHAS;
  int M = COLUNAS;
  int x=0, y=0, z=0, l=0, c=0;

  // percorre as 8 casas ao redor da casa mat[l][c]
  for (l=0 ; l < N ; l++){     
    for (c=0 ; c < M ; c++){
      
      x = mat[l][c].qtd_bombas;
      y = contar_nao_clicados(l,c,N,M,mat);
      z = contar_marcacao_ia(l,c,N,M,mat);
      
      // condição para verificar 1ª regra de jogo da IA
      // verifica se a quantidade de bobas ao redor da casa mat[l][c]
      // é igual à quantidade de casas não clicadas ao redor de mat[l][c]
      if (x > 0 && x == z){   

        // percorre as 8 casas ao redor da casa mat[l][c]
        for(int i=(-1) ; i<=1 ; i++){
          for(int j=(-1); j<=1 ; j++){
            
            // verifica se a casa está dentro do tabuleiro
            if (celula_valida(l+i, c+j, N, M)){
              
              // as casas que ainda não foram clicadas e que não foram marcadas como bomba
              if (!mat[l+i][c+j].clicado && !mat[l+i][c+j].ia_marca){
                mat[l+i][c+j].ia_limpo = true;
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

int * clicar_primeira_casa(int l, int c, int*r, tabuleiro ** mat){
  // essa função retorna a primeira celula adjascente que não tiver sido clicada
  
  int N = LINHAS;
  int M = COLUNAS;
  for(int i=-1 ; i<=1 ; i++){
    for(int j=-1 ; j<=1 ; j++){
      if(celula_valida(l+i, c+j, N, M)){
        if(!mat[l+i][c+j].clicado){
          printf("As coordenadas [%d, %d] ", (l+i)+1, (c+j)+1);
          printf("tem baixas chances de ser uma bomba\n");
          r[0] = l+i;
          r[1] = c+j;
          return r;
        }
      }
    }
  }
}

int * nenhuma_celula_marcada(tabuleiro ** mat, int * r){

  int N = LINHAS;
  int M = COLUNAS;

  int l=0, c=0, x=0, y=0, z=0;

  float ctrl_prct = 1;
    while (ctrl_prct<100){

    for (l=0 ; l < N ; l++){
      for (c=0 ; c < M ; c++){

        float dif=1;
        if (mat[l][c].clicado){
          x = mat[l][c].qtd_bombas;
          y = contar_nao_clicados(l,c,N,M,mat);
          dif = (x/y)*10;
          if (dif <= ctrl_prct){
          r = clicar_primeira_casa(l, c, r, mat);
          return r;
          }
        } 
        }
      }
    }
    ctrl_prct++;
}

int * clicar_limpas(tabuleiro ** mat, int * r){

  int N = LINHAS;
  int M = COLUNAS;

  int l=0, c=0;

  for (l=0 ; l < N ; l++){
      for (c=0 ; c < M ; c++){

        if (mat[l][c].ia_limpo && !mat[l][c].clicado){ 
          printf("As coordenadas [%d, %d] ", (l)+1, (c)+1);
          printf("tem baixas chances de ser uma bomba\n");
          r[0] = l;
          r[1] = c;
          return r;
        }
      }
    }
}



int *pedir_ajuda(tabuleiro ** mat){
  /*
    A função pedir_ajuda irá utilizar duas informações do tabuleiro: quais células foram clicadas e qual a quantidade de bombas ao redor dela. Com elas, irá definir e calcular duas regras: Qual célula adjascente tem 100% de chance de ser uma bomba e qual célula tem 100% de chance de não ser uma bomba. Dessa forma, primeiramente, percorrerá todas as casas do tabuleiro, marcando e clicando as respectivas células adjascentes.
  */

  int qtd_marcados = marcacao_ia_bomba(mat);
  int qtd_limpos = marcacao_ia_limpo(mat);

  int N = LINHAS;
  int M = COLUNAS;
  int *r = malloc(sizeof(int)*2);

  int l=0, c=0, x=0, y=0, z=0;

  
  if (qtd_marcados == 0){

    /* caso o tabuleiro não permita fazer marções exatas, escolherá a primeira célula que tenha a menor chance de ter uma bomba ao redor, vendo a relação entre a quantidade de bombas e a quantidade de casas adjascentes não clicadas, retornará a primeira célula adjascente não clicada*/

    r = nenhuma_celula_marcada(mat, r);
    return r;
  }

  if (qtd_limpos > 0){
    /* Retornará a primeira posição que tiver sido marcada como limpa e não clicada*/
    r = clicar_limpas(mat, r);
    return r;
  }

  int ctrl_qtd = 1;
    /* o primeiro ctrl serve para que a célula escolhida seja sempre a com a menor quantidade de bombas ao redor possível */
  while(ctrl_qtd < 8){
    int ctrl_dif = 1;
        /* o segundo ctrl serve para que a diferença entre a quantidade de casas adjascentes marcadas e nao clicadas seja a menor possível*/
    while(ctrl_dif < 10){
      for (l=0 ; l < N ; l++){
        for (c=0 ; c < M ; c++){
  
          if (mat[l][c].clicado && mat[l][c].qtd_bombas == ctrl_qtd){ 
    
            x = mat[l][c].qtd_bombas;
            y = contar_nao_clicados(l,c,N,M,mat);
            z = contar_marcacao_ia(l,c,N,M,mat);
            int dif = (x-z)/(y-z);
            
            //printf("x:%d, y:%d, z:%d, dif:%f\n ",x,y,z, dif);
            
            if (y>z && z!=0 && dif <= ctrl_dif){
              for(int i=-1 ; i<=1 ; i++){
                for(int j=-1 ; j<=1 ; j++){
    
                  if(celula_valida(l+i, c+j, N, M)){
                    
                    if(!mat[l+i][c+j].clicado && !mat[l+i][c+j].ia_marca){
                      printf("As coordenadas [%d, %d] ", (l+i)+1, (c+j)+1);
                      printf("tem baixas chances de ser uma bomba\n");
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
    ctrl_dif++;
  }
    ctrl_qtd++;
  }
}