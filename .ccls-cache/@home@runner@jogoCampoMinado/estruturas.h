#ifndef FUNCOES_H
#define FUNCOES_H

#define LINHAS 10;
#define COLUNAS 20;
#define BOMBAS 40;

typedef enum { true = 1, false = 0 } Bool;

typedef struct {
  Bool clicado;
  Bool marcado;
  Bool bomba;
  int qtd_bombas;
} tabuleiro;

#endif