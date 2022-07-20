#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "func-ajuda.h"
#include "func-normal.h"
#include "estruturas.h"

// Todo arquivo .c deve incluir o seu correspondente .h

int contar_marcacao_ia(int l, int c, int N, int M, tabuleiro ** mat){
  int count=0;

  for(int i=-1 ; i<=1 ; i++){
    for(int j=-1 ; j<=1 ; j++){
      if (celula_valida(l+i, c+j, N, M) && mat[l+i][c+j].ia_marca) count++;
    }
  }
  return count;
}

int contar_nao_clicados(int l, int c, int N, int M, tabuleiro ** mat){
  int count=0;

  for(int i=-1 ; i<=1 ; i++){
    for(int j=-1 ; j<=1 ; j++){
      if (celula_valida(l+i, c+j, N, M) && !mat[l+i][c+j].clicado) count++;
    }
  }
  
  return count;
}

void marcacao_ia(tabuleiro ** mat){

  /*  a função ira verificar todas as celulas que foram clicadas e possuem uma quantidade de bombas adjacentes >= 0. as células que tiverem o numero de bombas iguais ao numero de celulas não clicadas são marcadas pela i.a como tendo uma bomba, sem utilização de informações da struct sobre o posicionamento das bombas */

  int N = LINHAS;
  int M = COLUNAS;
  int a=0, b=0, l=0, c=0;

  for (l=0 ; l < N ; l++){
    for (c=0 ; c < M ; c++){
      
      a = mat[l][c].qtd_bombas;
      b = contar_nao_clicados(l, c, N, M, mat);
      
      if (a == b && a!=0 && b!=0){
        
        for(int i=(-1) ; i<=1 ; i++){
          for(int j=(-1); j<=1 ; j++){
            
            if (celula_valida(l+i, c+j, N, M)){
              
              if (!mat[l+i][c+j].clicado){
                mat[l+i][c+j].ia_marca = true;
              }
            }
          }
        }
      }
    }
  }
}

int *pedir_ajuda(tabuleiro ** mat){
  
  /* 
    para cada célula já clicada, a função irá armazenar 3 valores: a quantidade de bombas atual, quantas células adjacentes não foram clicadas e quantas células adjacentes foram marcadas pela função anterior. Em seguida, escolherá como celula principal que tenha a menor quantidade de bombas em relação a quantidade de celulas não clicadas e celulas marcadas. Em seguida, irá imprimir, dentre as celulas adjacentes, qual deve ser clicada que não foi marcada e não foi clicada.
  */

  marcacao_ia(mat);

  int N = LINHAS;
  int M = COLUNAS;
  int resultado[2];
  int *r= resultado;

  int l=0, c=0, x=0, y=0, z=0;

  int ctrl = 1; 
  while(ctrl < 8){
    
    for (l=0 ; l < N ; l++){
      for (c=0 ; c < M ; c++){
            
        if (mat[l][c].clicado && mat[l][c].qtd_bombas <= ctrl){
  
          x = mat[l][c].qtd_bombas;
          y = contar_nao_clicados(l,c,N,M,mat);
          z = contar_marcacao_ia(l,c,N,M,mat);
  
          //printf("x: %d, y: %d, z:%d\n", x, y, z);
          
          if (x>0 && y>z && z>0){
  
            for(int i=-1 ; i<=1 ; i++){
              for(int j=-1 ; j<=1 ; j++){
  
                if(celula_valida(l+i, c+j, N, M)){
                  if(!mat[l+i][c+j].clicado && !mat[l+i][c+j].ia_marca){
                    printf("Selecione a opção e escolha as coordenadas [%d : %d]\n", (l+i)+1, (c+j)+1);
                    resultado[0] = l+i;
                    resultado[1] = c+j;
                    return r;
                  }
                }
              }
            }
          }
        }
      }
    }
    
    ctrl++;
  }

  return 0;
}