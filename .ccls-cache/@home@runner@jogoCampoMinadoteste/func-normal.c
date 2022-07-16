#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Todo arquivo .c deve incluir o seu correspondente .h
#include "func-normal.h"
#include "func-auto.h"
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

void salvar_bombas(tabuleiro **  mat, int l_entrada, int c_entrada) {
  int i = 0;
  int qtd = BOMBAS;
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;
  srand(time(NULL));
  while(i<qtd) {
    l = rand() % N;
    c = rand() % M;
    if (l==l_entrada && c==c_entrada || mat[l][c].bomba) { //while??
      l = rand() % N;
      c = rand() % M;
    }
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

Bool clicou_todas (tabuleiro ** mat) {
  int N = LINHAS;
  int M = COLUNAS;
  int contador = 0;
  for (int l = 0; l < N; l++) {
    for (int c = 0; c < M; c++) {
      if(mat[l][c].clicado) {
        contador++;
      }
    }  
  }
  if (contador == 198) {
    return true;
  } 
  return false;
}


int menu_rodada () {
  int n;
  while (!(n==1 || n==2 || n==3 || n==4)) {
    printf("Escolha uma das opções abaixo para continuar:\n");
    printf("1 - Clicar!\n");
    printf("2 - Marcar!\n");
    printf("3 - Pedir Ajuda!\n");
    printf("4 - Tempo de jogo!\n");
    scanf("%d", &n);
  }
  return n;
}

void receber_entradas (int * l, int * c) {
  
  int N = LINHAS;
  int M = COLUNAS;
  int l_entrada, c_entrada;
  printf("Digite o campo [x y] a selecionar:\n");
  scanf("%d %d", &l_entrada, &c_entrada);
  while (l_entrada< 1 || l_entrada>N || c_entrada<1 || c_entrada>M) {
    printf("Digite um campo [x y] válido:\n");
    scanf("%d %d", &l_entrada, &c_entrada);
  }
  *l = l_entrada;
  *c = c_entrada;
}

void tempo_decorrido(time_t p_tempo){
  float min, seg;
  time_t s_tempo;

  s_tempo = time(NULL);

  min = (s_tempo-p_tempo)/60;
  seg = ((s_tempo-p_tempo)%60);
  
  printf("\nTempo decorrido: 00:%02.f:%02.f\n\n", min, seg);
}

void processar_jogo (tabuleiro ** mat){
  int N = LINHAS;
  int M = COLUNAS;
  int i = 0;
  time_t p_tempo = time(NULL);
  Bool perdeu = false;
  Bool venceu = false;
  while (!perdeu && !venceu) { //e não venceu
    if (i==0) {
      processar_primeira_rodada(mat, p_tempo);
      imprimir_matriz(mat);
    } else {
      if(processar_rodada(mat, p_tempo)) {
        imprimir_matriz(mat);
        if(clicou_todas(mat)) {
          venceu = true;
        }
      } else {
        game_over();
        perdeu = true;
      }
    }
    i++;
  }
  if(venceu) {
    sobreviveu();
  }
  revelar_matriz(mat);
}

void processar_primeira_rodada(tabuleiro ** mat, time_t p_tempo){
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;
  int decisao = menu_rodada();
  
  receber_entradas(&l, &c);
  salvar_bombas(mat, l, c);
  percorrer_matriz(mat);
  
  if (decisao == clicar) { // clicar
      clicar_vizinhos(l-1, c-1, N, M, mat); // clicar elemento e seus vizinhos
  } else if (decisao == marcar) { // marcar
      mat[l-1][c-1].marcado = true;
  } else if (decisao == ajuda) { // ajuda
      //falta ajuda
  }  else if (decisao == tempo) { // tempo de jogo
      tempo_decorrido(p_tempo);
  }
}

Bool processar_rodada(tabuleiro ** mat, time_t p_tempo){
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;
  int decisao = menu_rodada();
  
  if (decisao == clicar) { // clicar
    receber_entradas(&l, &c);
    if(mat[l-1][c-1].bomba) { //é bomba
      mat[l-1][c-1].clicado = true;
      return false; 
    } else {  //não é bomba
      clicar_vizinhos(l-1, c-1, N, M, mat); // clicar elemento e seus vizinhos
    }
  } else if (decisao == marcar) { // marcar
    receber_entradas(&l, &c);
      mat[l-1][c-1].marcado = true;
  } else if (decisao == ajuda) { // ajuda
      //falta ajuda
  }  else if (decisao == tempo) { // tempo de jogo
      tempo_decorrido(p_tempo);
  }
  return true;
}

void imprimir_intro () {
  printf("Bem vindo ao jogo Campo Minado!\n");
  printf("Digite seu nome: ");
}

int menu_inicial (char nome[]) {
  int n;
  while (!(n==1 || n==2 || n==3 || n==4)) {
    printf("Olá, %s! Escolha uma das opções abaixo para continuar:\n", nome);
    printf("1 - Jogar!\n");
    printf("2 - Jogo automático (O computador irá jogar por você).\n");
    printf("3 - Sair.\n");
    scanf("%d", &n);
  }
  return n;
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

void iniciar_jogo() {
  //Tabuleiro
  //matriz N por M
  int N = LINHAS;
  int M = COLUNAS;
  tabuleiro ** mat = matriz(N, M);
  
  //introdução e nome do usuário
  imprimir_intro();
  char nome[255];
  scanf("%s", nome);
  //imprimir menu
  int opcao = menu_inicial(nome);
  
  //processar jogo
  if (opcao==jogar){
    // começa a contar o tempo
    processar_jogo(mat);
  } else if (opcao==autom) {
    processar_jogo_auto(mat);
  } else if (opcao==sair) {
    printf("Até mais!");
  }
  
  //liberar espaço de memória
  for(int i=0;i<N;i++){
    free(mat[i]);
  }
  free(mat);
}
