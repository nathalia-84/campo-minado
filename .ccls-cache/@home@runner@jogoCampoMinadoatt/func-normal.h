#include <time.h>

#ifndef FUNCOES_H_
#define FUNCOES_H_

#include "estruturas.h"

//declaração das funções

tabuleiro ** matriz(int N, int M);

Bool celula_valida(int l, int c, int N, int M);


int contar_bombas_vizinhas(int l, int c, int N, int M, tabuleiro ** mat);

void percorrer_matriz (tabuleiro ** mat);

void salvar_bombas(int qtd, tabuleiro **  mat);

int tamanho(int n, char str[n]);

char minusculo(char c);

Bool comparar(int n_a, char a[], int n_b, char b[]);

void game_over ();

void sobreviveu ();

void clicar_vizinhos (int l, int c, int N, int M, tabuleiro **  mat);

Bool clicou_todas (tabuleiro ** mat);

int menu_rodada ();

void receber_entradas (int * l, int * c);

Bool processar_rodada(tabuleiro ** mat, time_t p_tempo);

void tempo_decorrido(time_t p_tempo);

void processar_jogo (tabuleiro ** mat);

void imprimir_intro ();

void imprimir_menu (char nome[]);

void imprimir_barra (int n);

void imprimir_matriz (tabuleiro ** mat);

void revelar_matriz (tabuleiro ** mat);

#endif
