#include <stdio.h>
#include <time.h>
#include "estruturas.h"
#include "func-ajuda.h"

#ifndef FUNCOESN_H_
#define FUNCOESN_H_

//declaração das funções

tabuleiro ** matriz(int N, int M);

Bool celula_valida(int l, int c, int N, int M);

int contar_bombas_vizinhas(int l, int c, int N, int M, tabuleiro ** mat);

void percorrer_matriz (tabuleiro ** mat);

Bool area_valida(tabuleiro ** mat, int l, int c, int l_entrada, int c_entrada);

void salvar_bombas(tabuleiro **  mat, int l_entrada, int c_entrada);

int tamanho(int n, char str[n]);

char minusculo(char c);

Bool comparar(char a[], char b[]);

void game_over ();

void sobreviveu ();

void clicar_vizinhos (int l, int c, int N, int M, tabuleiro **  mat);

Bool clicou_todas (tabuleiro ** mat);

int menu_rodada ();

void receber_entradas (int * l, int * c);

void processar_primeira_rodada(tabuleiro ** mat, time_t p_tempo);

Processamento processar_rodada(tabuleiro ** mat, time_t p_tempo);

void tempo_decorrido(time_t p_tempo);

void processar_jogo (tabuleiro ** mat, Bool jogo_existente);

void imprimir_intro ();

int menu_inicial (char nome[]);

void imprimir_barra (int n);

void imprimir_matriz (tabuleiro ** mat);

void revelar_matriz (tabuleiro ** mat);

void salvar_matriz (tabuleiro ** mat);

void atribuir_variavel (tabuleiro ** mat, int l, int c, int variavel);

void ler_matriz (tabuleiro ** mat);

void ler_linha_com_terminador(char linha[], int tam, FILE* f);

void opcoes_de_jogo (char nome[], Bool jogo_existente, tabuleiro ** mat);

void iniciar_jogo ();

#endif
