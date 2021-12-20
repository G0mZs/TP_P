/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tabuleiro.h
 * Author: FNAC
 *
 * Created on 19 de abril de 2021, 13:02
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "estruturas.h"
#include "utils.h"
#include "misc.h"
#include "jogadas.h"

#ifndef TABULEIRO_H
#define TABULEIRO_H

#ifdef __cplusplus
extern "C" {
#endif

int randomLinhas();
void geraMatriz(tabuleiro *tab,int linhas,int colunas);
void geraMatriz_guardada(pJogadas lista_jogadas,tabuleiro *tab);
void tab_inicial(tabuleiro *tab);
void menu_jogo(tabuleiro *tab,pJogadas lista_jogadas);
void inicia_jogo(tabuleiro *tab,pJogadas lista_jogadas);
void jogo_contra_programa(tabuleiro *tab,pJogadas lista_jogadas);
void mostra_tabela(tabuleiro *tab);
void acrescenta(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas);
void programa_acrescenta(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas);
void altera_colunas(tabuleiro *tab);
void altera_linhas(tabuleiro *tab);
void coloca_pedra(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas);
void programa_coloca_pedra(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas);
void coloca_verde(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas);
void programa_coloca_verde(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas);
void troca_amarela(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas);
void programa_troca_amarela(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas);
void troca_vermelha(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas);
void programa_troca_vermelha(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas);
int averigua_vitoria(tabuleiro* tab);
int averigua_PlayAmarela(tabuleiro *tab);
int averigua_PlayVermelha(tabuleiro *tab);


#ifdef __cplusplus
}
#endif

#endif /* TABULEIRO_H */

