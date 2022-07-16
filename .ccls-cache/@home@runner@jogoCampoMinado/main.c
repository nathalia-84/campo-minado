#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "estruturas.h"

tabuleiro ** matriz(int N, int M){
  tabuleiro ** mat = (tabuleiro**) malloc((N)*sizeof(tabuleiro*)); // n linhas
  for(int i=0;i<N;i++){
    mat[i] = (tabuleiro*) malloc((M)*sizeof(tabuleiro)); // n colunas
  }
  return mat;
}

Bool celula_valida(int l, int c, int N, int M)
{
    // Retorna true se a linha e coluna são válidas
    if (l >= 0 && l < N && c >= 0 && c < M) {
      return true;
    } else {
      return false;
    }
}


int contar_bombas_vizinhas(int l, int c, int N, int M, tabuleiro ** mat) {
  int cont = 0;
  if (celula_valida(l-1, c, N, M) && mat[l-1][c].bomba){
    cont++;
  }
  if (celula_valida(l+1, c, N, M) && mat[l+1][c].bomba){
    cont++;
  }
  if (celula_valida(l, c-1, N, M) && mat[l][c-1].bomba){ 
    cont++;
  }
  if (celula_valida(l, c+1, N, M) && mat[l][c+1].bomba){ 
    cont++;
  }
  if (celula_valida(l-1, c+1, N, M) && mat[l-1][c+1].bomba){ 
    cont++;
  }
  if (celula_valida(l+1, c-1, N, M) && mat[l+1][c-1].bomba){ 
    cont++;
  }
  if (celula_valida(l+1, c+1, N, M) && mat[l+1][c+1].bomba){ 
    cont++;
  }
  if (celula_valida(l-1, c-1, N, M) && mat[l-1][c-1].bomba){
    cont++;
  }
  return cont;
}


void percorrer_matriz (tabuleiro ** mat) {
  int N = LINHAS;
  int M = COLUNAS;
  for (int l = 0; l < N; l++) {
    for (int c = 0; c < M; c++) {
      if(!(mat[l][c].bomba)) {
        mat[l][c].qtd_bombas = contar_bombas_vizinhas(l, c, N, M, mat);
      }
    }  
  }
}

void salvar_bombas(int qtd, tabuleiro **  mat) {
  int i = 0;
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;
  srand(time(NULL));
  while(i<qtd) {
    l = rand() % N;
    c = rand() % M;
    mat[l][c].bomba = true;
    i++;
  }
}

int tamanho(int n, char str[n]) {
  int cont=0;
  while(cont<n && str[cont]!='\0')
    cont = cont + 1;
  return cont;
}

char minusculo(char c) {
  if(c >=65 && c <=90)
    c +=32;
  return c;
}

Bool comparar(int n_a, char a[], int n_b, char b[]) {
  Bool cmp = false;
  int tamanho_a = tamanho(n_a, a);
  int tamanho_b = tamanho(n_b, b);
  if (tamanho_a == tamanho_b) {
    cmp = true;
    for (int i=0; i<tamanho_a; i++) {
      if (minusculo(a[i]) != minusculo(b[i])) {
        cmp = false;
      }
    }
  }
  return cmp;
}

void game_over () {
  printf("CABUUUUM!\n");
  printf("Game Over....\n");
}

void sobreviveu () {
  printf("Você sobreviveu!\n");
}

void clicar_vizinhos (int l, int c, int N, int M, tabuleiro **  mat) {
  if (celula_valida(l, c, N, M) && !mat[l][c].clicado) {
    mat[l][c].clicado = true;
    if (mat[l][c].qtd_bombas==0) {
      clicar_vizinhos(l-1, c, N, M, mat);
      clicar_vizinhos(l, c+1, N, M, mat);
      clicar_vizinhos(l, c-1, N, M, mat);
      clicar_vizinhos(l+1, c+1, N, M, mat);
      clicar_vizinhos(l-1, c-1, N, M, mat);
      clicar_vizinhos(l+1, c-1, N, M, mat);
      clicar_vizinhos(l-1, c+1, N, M, mat);
    }
  } 
}

Bool processar_rodada(tabuleiro **  mat) {
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;
  int rodada = 0;
  char buffer[6];
  char clicar[] = "Clica";
  char marcar[] = "Marca";

  printf("Digite a opção [Clica] ou [Marca] e o campo [x y] a selecionar:\n");
  scanf("%s", buffer);
  scanf("%d %d", &l, &c);
  while (!comparar(6, buffer, 6, clicar) && !comparar(6, buffer, 6, marcar)) {
    printf("Digite a opção [Clica] ou [Marca] e o campo [x y] a selecionar:\n");
    scanf("%s", buffer);
    scanf("%d %d", &l, &c);
  }
  if (comparar(6, buffer, 6, clicar)) {
    if(mat[l-1][c-1].bomba) { //é bomba
      mat[l-1][c-1].clicado = true;
      return false; 
    } else {  //não é bomba
      clicar_vizinhos(l-1, c-1, N, M, mat); // clicar elemento e seus vizinhos
      return true;
    }
  } else if (comparar(6, buffer, 6, marcar)) {
      mat[l-1][c-1].marcado = true;
      return true;
  } 
}

void imprimir_barra (int n) {
  int i = 0;
  printf("\t");
  while (i<n) {
    printf("----");
    i++;
  }
  printf("\n");
  
}

void imprimir_matriz (tabuleiro ** mat) {
  int N = LINHAS;
  int M = COLUNAS;
  for (int c=0; c<M; c++) 
    printf("\t%d ", c+1);
  printf("\n");
  
  for (int l = 0; l < N; l++) {
    imprimir_barra(M);
    if (l==N-1) {
      printf("%d", l+1);
      printf(" |");
    } else {
      printf("%d", l+1);
      printf("  |");
    }
    for (int c = 0; c < M; c++) {
      if (mat[l][c].clicado) {
        if (mat[l][c].bomba) {
          printf(" X ");
        } else {
          printf(" %d ", mat[l][c].qtd_bombas);
        }
      } else if (mat[l][c].marcado && mat[l][c].bomba) {
        printf(" B ");
      }  else {
        printf(" * ");
      }
      printf("|");
    }  
    printf("\n");
  }
  imprimir_barra(M);
}

void revelar_matriz (tabuleiro ** mat) {
  int N = LINHAS;
  int M = COLUNAS;
  for (int c=0; c<M; c++) 
    printf("\t%d ", c+1);
  printf("\n");
  
  for (int l = 0; l < N; l++) {
    imprimir_barra(M);
    if (l==N-1) {
      printf("%d", l+1);
      printf(" |");
    } else {
      printf("%d", l+1);
      printf("  |");
    }
    for (int c = 0; c < M; c++) {
      if (mat[l][c].clicado && mat[l][c].bomba) {
          printf(" X ");
      } else if (mat[l][c].bomba) {
        printf(" B ");
      }  else {
        printf(" %d ", mat[l][c].qtd_bombas);
      }
      printf("|");
    }  
    printf("\n");
  }
  imprimir_barra(M);
}

void processar_jogo (tabuleiro ** mat){
  int N = LINHAS;
  int M = COLUNAS;
  int i = 0;
  Bool perdeu = false;
  while (!perdeu) {
    if(processar_rodada(mat)) {
      imprimir_matriz(mat);
    } else {
      game_over();
      perdeu = true;
    }
    i++;
  }
  if(!perdeu) {
    sobreviveu();
  }
  revelar_matriz(mat);
}

void imprimir_intro () {
  printf("Bem vindo ao jogo Campo Minado!\n");
  printf("Digite seu nome: ");
}

void imprimir_menu (char nome[]) {
  printf("Olá, %s! Escolha uma das opções abaixo para continuar:\n", nome);
  printf("1 - Jogar!\n");
  printf("2 - Jogo automático (O computador irá jogar por você).\n");
  printf("3 - Sair.\n");
}

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
    processar_jogo(mat);
  //liberar espaço de memória
  for(int i=0;i<N;i++){
    free(mat[i]);
  }
  free(mat);
  
  return 0;
}