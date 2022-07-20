#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Todo arquivo .c deve incluir o seu correspondente .h
#include "func-normal.h"
#include "func-ajuda.h"
#include "func-auto.h"
#include "estruturas.h"

tabuleiro ** matriz(int N, int M){
  /*
  Esta função irá criar, dinamicamente, uma matriz N por M.
  */
  tabuleiro ** mat = (tabuleiro**) malloc((N)*sizeof(tabuleiro*)); // n linhas
  for(int i=0;i<N;i++){
    mat[i] = (tabuleiro*) malloc((M)*sizeof(tabuleiro)); // n colunas
  }
  return mat;
}

Bool celula_valida(int l, int c, int N, int M){
    // Retorna true se a linha e coluna são válidas (estão dentro do escopo do tabuleiro)
    if (l >= 0 && l < N && c >= 0 && c < M ){
      return true;
    } 
    return false;
}

int contar_bombas_vizinhas(int l, int c, int N, int M, tabuleiro ** mat) {
  /*
  Esta função irá contar as quantidade de bombas ao redor de uma casa met[l][c].
  */
  int count = 0;

  // percorre as 8 casas ao redor de mat[l][c]
  for(int i=(-1) ; i<=1 ; i++){
    for(int j=(-1) ; j<=1 ; j++){
      // conta as células que são válidas e que posuem bombas
      if (celula_valida(l+i, c+j, N, M) && mat[l+i][c+j].bomba) count++;
    }
  }

  return count;
}

void percorrer_matriz (tabuleiro ** mat) {
  /*
  Esta função irá percorrer toda a matriz, chamando a função contar_bombas_vizinhas em cada elemento. de modo a salvar na variável mat[l][c].qtd_bombas, a quantidade de bombas existente ao redor da referida casa.
  */
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
  /*
  Esta função irá retornar true se a casa selecionada, mat[l][c], possuir bomba, for ingual à primeira casa selecionada pelo jogador ou pela IA (mat[l][c]==mat[l_entrada][c_entrada]), ou se estiver localizada em até duas posições (válidas) adjacentes.
  */
  
  if (mat[l][c].bomba) return true;
  if (l == l_entrada && c == c_entrada) return true;

  int N = LINHAS;
  int M = COLUNAS;

  for(int i=(-2) ; i<=2 ; i++){
      for(int j=(-2); j<=2 ; j++){
        if (celula_valida(l_entrada+i, c_entrada+j, N, M)){
          if (l_entrada+i == l && c_entrada+j == c) return true;
        }
      }
    }
  
  return false;
}

void salvar_bombas(tabuleiro **  mat, int l_entrada, int c_entrada) {
  /*
  Esta função irá inserir 40 bombas ao redor do tabuleiro, de modo aleatório. A função irá chamar a função area_invalida dentro de uma estrutura de repetição while, de modo a apenas inserir bombas em casas diferentes da primeira casa selecionada pelo usuário ou muito próximas a esta, assim como, casas onde ainda não foram inseridas bombas.
  */
  int i = 0;
  int qtd = BOMBAS;
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;
  srand(time(NULL));
  while(i<qtd) {
    l = rand() % N; // retorna um número aleatório de 0 a N
    c = rand() % M; // retorna um número aleatório de 0 a M
    while (area_invalida(mat, l, c, l_entrada, c_entrada)) {
      l = rand() % N; // retorna um número aleatório de 0 a N
      c = rand() % M; // retorna um número aleatório de 0 a M
    }
    mat[l][c].bomba = true;
    i++;
  }
}


int tamanho(int n, char str[n]) {
  // retorna o tamanho de uma string
  int cont=0;
  while(cont<n && str[cont]!='\0') cont++;
  return cont;
}

char minusculo(char c) {
  //tranforma um char maiúsculo em minúsculo
  if(c >=65 && c <=90) c +=32;
  return c;
}

Bool comparar(char a[], char b[]) {
  // compara duas strings
  Bool cmp = false;
  
  int tamanho_a = tamanho(10, a);
  int tamanho_b = tamanho(10, b);
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
  // saída para quando o usuário perder o jogo
  printf("CABUUUUM!\n");
  printf("Game Over....\n");
}

void sobreviveu () {
  // saída para quando o usuário ganhar o jogo
  printf("Parabéns! Você sobreviveu!\n");
}

void clicar_vizinhos (int l, int c, int N, int M, tabuleiro **  mat) {
  /*
  Esta função irá clicar a casa selecionada pelo jogador, e irá chamar clicar_vizinhos, recursivamente, para clicar nas casas em volta de todas as casas que não possuírem bombas em suas vizinhanças (condição mat[l][c].qtd_bombas==0).
  */
  if (celula_valida(l, c, N, M) && !mat[l][c].clicado) {
    mat[l][c].clicado = true;
    if (mat[l][c].qtd_bombas==0) {
      clicar_vizinhos(l+1, c, N, M, mat);
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
  /*
  Esta função irá verificar se todas as casas que não são bombas do tabuleiro foram clicadas, ou seja, reveladas. E desse modo, servirá de controle para a situação em que o jogador ganha o jogo (retornará true).
  */
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


int menu_rodada () {
  /*
  Imprime o menu com ações para cada rodada, a partir da segunda, e recebe e retorna a entrada do usuário.
  */
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
  /*
  Recebe entradas válidas do usuário para a seleção de uma casa, a partir da linha e coluna. Os valores de l e c são retornados por meio de passagem por referência.
  */
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
  /*
  Calcula o tempo decorrido de jogo.
  */

  float min, seg, hor;
  time_t s_tempo;

  s_tempo = time(NULL);

  hor = ((s_tempo-p_tempo)/60)/60;
  min = (s_tempo-p_tempo)/60;
  seg = ((s_tempo-p_tempo)%60);
  
  printf("\nTempo decorrido: %02.f:%02.f:%02.f\n\n", hor, min, seg);
}

void processar_jogo (tabuleiro ** mat, Bool jogo_existente){
  /*
  Esta função processa o andamento das rodadas a partir da verificação do estado atual do jogo(se o jogo continua, se foi parado, se o jogador perdeu ou venceu).
  */
  int N = LINHAS;
  int M = COLUNAS;
  int i = 0;
  time_t p_tempo = time(NULL);
  int estado;
  Bool perdeu_jogo = false;
  Bool venceu_jogo = false;
  Bool parou_jogo = false;
  // o jogo será processado enquanto o jogador não perdeu, não venceu e não parou o jogo
  while (!perdeu_jogo && !venceu_jogo && !parou_jogo) { 
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
        salvar_matriz(mat); // salva matriz no arquivo "matriz.txt"
        parou_jogo = true;
      }
    }
    i++;
  }
  // se o jogador chegou ao final de um jogo (perdeu ou ganhou), qualquer jogo salvo existente será excluído
  if (perdeu_jogo || venceu_jogo) {
    char nome_do_arquivo[] = "matriz.txt";
    remove(nome_do_arquivo);
  }
  
}

void processar_primeira_rodada(tabuleiro ** mat, time_t p_tempo){
  /*
  Esta função processa a primeira rodada do jogo, inserindo as informações do tabuleiro e recebendo a primeira entrada do jogador.
  */
  
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;
  //imprime tabuleiro
  imprimir_matriz(mat);
  //recebe as primeiras entradas
  receber_entradas(&l, &c);
  // salva as 40 bombas em casas aleatórias
  salvar_bombas(mat, l, c);
  // percerre matriz para guardar o número de bombas na vizinhança de cada casa
  percorrer_matriz(mat);
  // clica elemento e seus vizinhos
  clicar_vizinhos(l-1, c-1, N, M, mat); 
}

Processamento processar_rodada(tabuleiro ** mat, time_t p_tempo){
  /*
  Esta função processa a decisão do jogador em cada rodada (clicar, marcar, parar), e retorna se a decisão levou o jogador a perder, parar, ou continuar no jogo até vencer.
  */
  int N = LINHAS;
  int M = COLUNAS;
  int l, c;
  int decisao = menu_rodada();
  
  if (decisao == clicar) { 
    receber_entradas(&l, &c);
    if(mat[l-1][c-1].bomba) { 
      mat[l-1][c-1].clicado = true;
      return perdeu;
    } else {  
      // clica elemento e seus vizinhos
      clicar_vizinhos(l-1, c-1, N, M, mat); 
    }
  } else if (decisao == marcar) { 
    receber_entradas(&l, &c);
    mat[l-1][c-1].marcado = true;
  } else if (decisao == ajuda) { 
    pedir_ajuda(mat);
  }  else if (decisao == tempo) { 
    tempo_decorrido(p_tempo);
  } else if (decisao == parar) {
    return parou;
  }
  return continua;
}

void imprimir_intro () {
  // Imprime mensagem inicial
  printf("Bem vindo ao jogo Campo Minado!\n");
  printf("Digite seu nome: ");
}

int menu_inicial (char nome[]) {
  //Imprime menu inicial do jogo
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

Bool intro_jogo_existente (char nome[]) {
  int resposta;
  printf("Olá, %s. Existe um jogo já iniciado, deseja continuá-lo?\n", nome);
  printf("1 - Sim.\n");
  printf("2 - Não.\n");
  scanf("%d", &resposta);
  while (resposta!=1 && resposta!=2) {
    printf("Digite uma resposta válida:\n");
    printf("1 - Sim.\n");
    printf("2 - Não.\n");
    scanf("%d", &resposta);
  }
  if (resposta==1) {
    return true;
  } else if (resposta==2) {
    return false;
  }
}

void imprimir_barra (int n) {
  // Imprime barra da estrutura visual do tabuleiro
  int i = 0;
  printf("\t");
  while (i<n) {
    printf("----");
    i++;
  }
  printf("\n");
  
}

void imprimir_matriz (tabuleiro ** mat) {
  /*
  Imprime a matriz em cada rodada.
  */
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
      } else if (mat[l][c].marcado /*&& mat[l][c].bomba*/) {
        printf(" B ");
      }/*  else if (mat[l][c].ia_marca){
        printf(" A ");
      } else if (mat[l][c].ia_limpo && !mat[l][c].clicado){
        printf(" L ");
      } */else {
        printf(" * ");
      }
      printf("|");
    }  
    printf("\n");
  }
  imprimir_barra(M);
}

void revelar_matriz (tabuleiro ** mat) {
  /*
  Revela a matriz no final do jogo.
  */
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
  /*
  Esta função é chamada apenas quando o jogo é parado, o objetivo dela é salvar as informações do tabuleiro atual para que o jogador possa continuar o jogo em outro momento.
  */
  int N = LINHAS;
  int M = COLUNAS;
  int i, j; 
  FILE *arquivo = fopen( "matriz.txt", "w" ); 
  // verifica se o arquivo foi aberto corretamente
  if( arquivo == NULL ){ 
	  printf( "Erro na abertura do arquivo" ); 
  } else {
    // e inicia o processo de salvar os dados da matriz
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
              if (mat[i][j].marcado) {
                fprintf(arquivo, "%d\n", -3);
              } else {
                fprintf(arquivo, "%d\n", 0);
              }
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
              if (mat[i][j].marcado) {
                fprintf(arquivo, "%d ", -3);
              } else {
                fprintf(arquivo, "%d ", 0);
              }
            }
          }
        }
      }
    }
    fclose(arquivo); //fecha o arquivo
    }
}

void atribuir_variavel (tabuleiro ** mat, int l, int c, int variavel) {
  /*
  Atribui as características de cada casa (se é bomba, se foi clicada, se foi marcada, etc.) de acordo com a variável atribuida à casa no arquivo "matriz.txt" (0, 1, -1, -2 ou -3). Chama a função contar_bombas_vizinhas para as casas que não possuem bombas.
  */
  
  int N = LINHAS;
  int M = COLUNAS;
  
  if (variavel == 1) {
    // já foi clicado
    mat[l][c].clicado = true;
    mat[l][c].qtd_bombas = contar_bombas_vizinhas(l, c, N, M, mat);
  } else {
    //não foi clicada
    // 0 == não é bomba
    // -1 == é bomba
    // -2 == é bomba e foi marcada
    // -3 == não é bomba e foi marcada
    mat[l][c].clicado = false;
    mat[l][c].qtd_bombas = contar_bombas_vizinhas(l, c, N, M, mat);
    if (variavel==-1) { // é bomba
      mat[l][c].bomba = true;
    } else if (variavel==-2) { // é bomba e foi marcada
      mat[l][c].bomba = true;
      mat[l][c].marcado = true;
    } else if (variavel==-3) { // não é bomba e foi marcada
      mat[l][c].marcado = true;
    } 
  }
}

void ler_matriz (tabuleiro ** mat) {
  /*
  Esta função lê o arquivo "matriz.txt", chamando a função atribuir_variavel para fazer o processamento das características de cada casa do tabuleiro, de modo que o jogo possa ser continuado de onde o jogador parou.
  */
  int N = LINHAS;
  int M = COLUNAS;
  float min, seg, hor;
  int i, j; 
  int variavel;
  FILE *arquivo = fopen( "matriz.txt", "r" ); //abre o arquivo

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

void ler_linha_com_terminador(char linha[], int tam, FILE * f) {
  // Lê linha até o '\n' e insere o \0 no fim da string
  fgets(linha, tam, f);
  while(linha[0] == '\n'){
    fgets(linha, tam, f);
  }
  for (int i=0; i<tamanho(tam, linha); i++) {
    if(linha[i] == '\n')
      linha[i] = '\0';
  }
}

void opcoes_de_jogo (char nome[], Bool jogo_existente, tabuleiro ** mat) {
  /*
  Esta função processa as opções de jogo da função menu_inicial.
  */
  int opcao = menu_inicial(nome);
    //processar jogo
    if (opcao==jogar){
      // começa a contar o tempo
      processar_jogo(mat, jogo_existente);
    } else if (opcao == autom) {
      processar_jogo_AUTO(mat);
    } else if (opcao == sair) {
      printf("Até mais!");
    }
}

void iniciar_jogo() {
  /*
  Esta função chama todas funções necessárias para o início do jogo: chama a função matriz, imrpime uma introdução e recebe o nome do jogador, verifica se há um jogo existente que pode ser continuado e pergunta ao usuário se ele deseja continuar esse jogo, inicia a função de processamento de jogo, e, por fim, libera o espaço atribuído dinamicamente para a matriz.
  */
  
  // tabuleiro
  // matriz N por M
  int N = LINHAS;
  int M = COLUNAS;
  tabuleiro ** mat = matriz(N, M);
  
  // introdução e nome do usuário
  imprimir_intro();
  char nome[255];
  ler_linha_com_terminador(nome, 255, stdin);

  // verifica se existe um jogo salvo
  FILE *arquivo = fopen( "matriz.txt", "r" );
  char nome_do_arquivo[] = "matriz.txt";

  Bool jogo_existente = false;
  
  if( arquivo == NULL ){
    //não existe jogo salvo
	  opcoes_de_jogo(nome, jogo_existente, mat);
  } else {
    //existe jogo salvo
    fclose(arquivo);
    Bool jogo_existente = intro_jogo_existente(nome);
    if (jogo_existente) {
      // processa o tabuleiro para continuar o jogo salvo
      ler_matriz(mat);
      percorrer_matriz(mat);
      imprimir_matriz(mat);
      // inicia o processamento do jogo 
      processar_jogo(mat, jogo_existente);
    } else {
      remove(nome_do_arquivo);
      opcoes_de_jogo(nome, jogo_existente, mat);
    }
  }
  
  // libera espaço de memória
  for(int i=0;i<N;i++){
    free(mat[i]);
  }
  free(mat);
}