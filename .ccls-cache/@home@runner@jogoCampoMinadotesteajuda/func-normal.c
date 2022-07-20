#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Todo arquivo .c deve incluir o seu correspondente .h
#include "func-normal.h"
#include "func-ajuda.h"
#include "estruturas.h"

tabuleiro ** matriz(int N, int M){
  tabuleiro ** mat = (tabuleiro**) malloc((N)*sizeof(tabuleiro*)); // n linhas
  for(int i=0;i<N;i++){
    mat[i] = (tabuleiro*) malloc((M)*sizeof(tabuleiro)); // n colunas
  }
  return mat;
}

Bool celula_valida(int l, int c, int N, int M){
    // Retorna true se a linha e coluna são válidas
    if (l >= 0 && l < N && c >= 0 && c < M ){
      return true;
    } 
    return false;
}

int contar_bombas_vizinhas(int l, int c, int N, int M, tabuleiro ** mat) {
  int count = 0;

  for(int i=(-1) ; i<=1 ; i++){
    for(int j=(-1) ; j<=1 ; j++){
      if (celula_valida(l+i, c+j, N, M) && mat[l+i][c+j].bomba) count++;
    }
  }

  return count;
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

Bool area_invalida(tabuleiro ** mat, int l, int c, int l_entrada, int c_entrada){
  // Retorna true se for uma bomba, se for a primeira coordenada ou se for até duas posições adjacentes
  
  if (mat[l][c].bomba) return true;
  if (l == l_entrada && c == c_entrada) return true;

  int N = LINHAS;
  int M = COLUNAS;

  for(int i=(-1) ; i<=1 ; i++){
      for(int j=(-1); j<=1 ; j++){
        if (celula_valida(l_entrada+i, c_entrada+j, N, M)){
          if (l_entrada+i == l && c_entrada+j == c) return true;
        }
      }
    }
  
  return false;
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
    while (area_invalida(mat, l, c, l_entrada, c_entrada)) {
      l = rand() % N;
      c = rand() % M;
    }
    mat[l][c].bomba = true;
    i++;
  }
}

int tamanho(int n, char str[n]) {
  int cont=0;
  while(cont<n && str[cont]!='\0') cont++;
  return cont;
}

char minusculo(char c) {
  if(c >=65 && c <=90) c +=32;
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
  int casas_sem_bombas = N*M - BOMBAS;
  int contador = 0;
  for (int l = 0; l < N; l++) {
    for (int c = 0; c < M; c++) {
      if(mat[l][c].clicado) {
        contador++;
      }
    }  
  }
  if (contador == casas_sem_bombas) {
    return true;
  } 
  return false;
}

int menu_primeira_rodada () {
  int n;
  while (!(n==1 || n==2 || n==3 || n==4)) {
    printf("Escolha uma das opções abaixo para continuar:\n");
    printf("1 - Clicar!\n");
    //printf("2 - Marcar!\n");
    //printf("3 - Pedir Ajuda!\n");
    //printf("4 - Tempo de jogo!\n");
    scanf("%d", &n);
  }
  return n;
}

int menu_rodada () {
  int n;
  while (!(n==1 || n==2 || n==3 || n==4 || n==5)) {
    printf("Escolha uma das opções abaixo para continuar:\n");
    printf("1 - Clicar!\n");
    printf("2 - Marcar!\n");
    printf("3 - Pedir Ajuda!\n");
    printf("4 - Tempo de jogo!\n");
    printf("5 - Parar jogo!\n");
    scanf("%d", &n);
  }
  return n;
}

void receber_entradas (int * l, int * c) {
  int N = LINHAS;
  int M = COLUNAS;
  int l_entrada, c_entrada;
  printf("Digite a linha a selecionar:\n");
  scanf("%d", &l_entrada);
  printf("Digite a coluna a selecionar:\n");
  scanf("%d", &c_entrada);
  while (l_entrada< 1 || l_entrada>N || c_entrada<1 || c_entrada>M) {
    printf("Digite uma linha válida a selecionar:\n");
    scanf("%d", &l_entrada);
    printf("Digite a coluna válida a selecionar:\n");
    scanf("%d", &c_entrada);
  }
  *l = l_entrada;
  *c = c_entrada;
}

void tempo_decorrido(time_t p_tempo){

  printf("Entrou tempo\n");
  float min, seg, hor;
  time_t s_tempo;

  s_tempo = time(NULL);

  hor = ((s_tempo-p_tempo)/60)/60;
  min = (s_tempo-p_tempo)/60;
  seg = ((s_tempo-p_tempo)%60);
  
  printf("\nTempo decorrido: %02.f:%02.f:%02.f\n\n", hor, min, seg);
}

void processar_jogo (tabuleiro ** mat, Bool jogo_existente){
  int N = LINHAS;
  int M = COLUNAS;
  int i = 0;
  time_t p_tempo = time(NULL);
  int estado;
  Bool perdeu_jogo = false;
  Bool venceu_jogo = false;
  Bool parou_jogo = false;
  while (!perdeu_jogo && !venceu_jogo && !parou_jogo) { //enquanto não perdeu e não venceu
    if (i==0 && jogo_existente==false) {
      processar_primeira_rodada(mat, p_tempo);
      imprimir_matriz(mat);
      if(clicou_todas(mat)) {
        sobreviveu();
        revelar_matriz(mat);
        venceu_jogo = true;
      }
    } else {
      estado = processar_rodada(mat, p_tempo);
      if(estado == continua) {
        imprimir_matriz(mat);
        if(clicou_todas(mat)) {
          sobreviveu();
          revelar_matriz(mat);
          venceu_jogo = true;
        }
      } else if (estado == perdeu) {
        game_over();
        revelar_matriz(mat);
        perdeu_jogo = true;
      } else if (estado == parou) {
        printf("Paramos seu jogo e o salvamos para uma próxima rodada!\n");
        salvar_matriz(mat);
        parou_jogo = true;
      }
    }
    i++;
  }
  if (perdeu_jogo || venceu_jogo) {
    char nome_do_arquivo[] = "matriz.txt";
    remove(nome_do_arquivo);
  }
  
}

void processar_primeira_rodada(tabuleiro ** mat, time_t p_tempo){
  // talvez rodar só o clicar ? Só rodar o tempo após o primeiro clique
  
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;

  imprimir_matriz(mat);
  receber_entradas(&l, &c);
  mat[l-1][c-1].bomba = false;
  salvar_bombas(mat, l, c);
  percorrer_matriz(mat);
  clicar_vizinhos(l-1, c-1, N, M, mat); // clicar elemento e seus vizinhos
}

Processamento processar_rodada(tabuleiro ** mat, time_t p_tempo){
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;
  int decisao = menu_rodada();
  
  if (decisao == clicar) { // clicar
    receber_entradas(&l, &c);
    if(mat[l-1][c-1].bomba) { //é bomba
      mat[l-1][c-1].clicado = true;
      return perdeu; 
    } else {  //não é bomba
      clicar_vizinhos(l-1, c-1, N, M, mat); // clicar elemento e seus vizinhos
    }
  } else if (decisao == marcar) { // marcar
    receber_entradas(&l, &c);
      mat[l-1][c-1].marcado = true;
  } else if (decisao == ajuda) { 
    marcacao_ia(mat);
    pedir_ajuda(mat);
  }  else if (decisao == tempo) { // tempo de jogo
      tempo_decorrido(p_tempo);
  } else if (decisao == parar) {
    return parou;
  }
  return continua;
}

void imprimir_intro () {
  printf("Bem vindo ao jogo Campo Minado!\n");
  printf("Digite seu nome: ");
}

int menu_inicial (char nome[]) {
  int n;
  while (!(n==1 || n==2 || n==3)) {
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
      }  else if (mat[l][c].ia_marca){
        printf(" A ");
      } else {
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

void salvar_matriz (tabuleiro ** mat) {
  int N = LINHAS;
  int M = COLUNAS;
  int i, j; 
  FILE *arquivo = fopen( "matriz.txt", "w" );
  if( arquivo == NULL ){
	  printf( "Erro na abertura do arquivo" ); //ver
  } else {
    for(i = 0; i < N; i++) {
      for(j = 0; j < M; j++) {
        if(j == M-1){
          if (mat[i][j].clicado) {
            fprintf(arquivo, "%d\n", 1);
          } else {
            if (mat[i][j].bomba) {
              if (mat[i][j].marcado) {
                fprintf(arquivo, "%d\n", -2);
              } else {
                fprintf(arquivo, "%d\n", -1);
              }
            } else {
              fprintf(arquivo, "%d\n", 0);
            }
          }
        } else {
          if (mat[i][j].clicado) {
            fprintf(arquivo, "%d ", 1);
          } else {
            if (mat[i][j].bomba) {
              if (mat[i][j].marcado) {
                fprintf(arquivo, "%d ", -2);
              } else {
                fprintf(arquivo, "%d ", -1);
              }
              
            } else {
              fprintf(arquivo, "%d ", 0);
            }
          }
        }
      }
    }
    fclose(arquivo); //fecha o arquivo
    }
}

void atribuir_variavel (tabuleiro ** mat, int l, int c, int variavel) {
  int N = LINHAS;
  int M = COLUNAS;
  
  if (variavel == 1) {
    // já foi clicado
    mat[l][c].clicado = true;
    mat[l][c].qtd_bombas = contar_bombas_vizinhas(l, c, N, M, mat);
  } else {
    // 0 ou -1 ou -2
    //não foi clicada
    mat[l][c].clicado = false;
    mat[l][c].qtd_bombas = contar_bombas_vizinhas(l, c, N, M, mat);
    if (variavel==-1) { // é bomba
      mat[l][c].bomba = true;
    } else if (variavel==-2) { // é bomba e foi marcada
      mat[l][c].bomba = true;
      mat[l][c].marcado = true;
    } 
  }
}

void ler_matriz (tabuleiro ** mat) {
  int N = LINHAS;
  int M = COLUNAS;
  float min, seg, hor;
  int i, j; 
  int variavel;
  FILE *arquivo = fopen( "matriz.txt", "r" ); //abre o arquivo

  fscanf(arquivo, "%f\n", &hor); //00:02:20
  fscanf(arquivo, "%f\n", &min); //00:02:20
  fscanf(arquivo, "%f\n", &seg); //00:02:20

  printf("O tempo do último jogo foi: %02.f:%02.f:%02.f\n", hor, min, seg);

  for(i = 0; i < N; i++) {
    for(j = 0; j < M; j++) {
      if(j == M-1){
        fscanf(arquivo, "%d\n", &variavel);
        atribuir_variavel(mat, i, j, variavel);
      } else {
        fscanf(arquivo, "%d ", &variavel);
        atribuir_variavel(mat, i, j, variavel);
      }
    }
  }
  fclose(arquivo); //fecha o arquivo
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
  Bool jogo_existente = false;

  //verigicar se existe um jogo salvo
  FILE *arquivo = fopen( "matriz.txt", "r" );
  char nome_do_arquivo[] = "matriz.txt";
  
  if( arquivo == NULL ){
	  int opcao = menu_inicial(nome);
    //processar jogo
    if (opcao==jogar){
      // começa a contar o tempo
      processar_jogo(mat, jogo_existente);
    } else if (opcao == autom) {
      //processar_jogo_AUTO(mat);
    } else if (opcao == sair) {
      printf("Até mais!");
    }
  } else {
    fclose(arquivo);
    
    jogo_existente = true;
    char c;
    printf("Existe um jogo já iniciado, deseja continuá-lo? (S/N)\n");
    scanf(" %c", &c);
    if (c=='S') {
      ler_matriz(mat);
      processar_jogo(mat, jogo_existente);
    } else {
      jogo_existente = false;
      remove(nome_do_arquivo);
      processar_jogo(mat, jogo_existente);
    }
  }
  
  //liberar espaço de memória
  for(int i=0;i<N;i++){
    free(mat[i]);
  }
  free(mat);
  
}