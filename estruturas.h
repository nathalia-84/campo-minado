#ifndef FUNCOES_H
#define FUNCOES_H

#define LINHAS 10;
#define COLUNAS 20;
#define BOMBAS 40;

typedef enum { true = 1, false = 0 } Bool;

typedef enum { clicar = 1, marcar = 2, ajuda = 3, tempo = 4, parar = 5 } Decisao;

typedef enum { jogar = 1, autom = 2, sair = 3} Jogo;

typedef enum { perdeu = 1, continua = 2, parou = 3} Processamento;

typedef struct {
  Bool clicado;
  Bool marcado;
  Bool bomba;
  int qtd_bombas;
} tabuleiro;

#endif