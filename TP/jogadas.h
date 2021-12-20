/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   jogadas.h
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


#ifndef JOGADAS_H
#define JOGADAS_H

#include "tabuleiro.h"

#ifdef __cplusplus
extern "C" {
#endif

pJogadas inserir_dados_jogadas(pJogadas lista_jogadas, char jogador,int jogadaLinha,int jogadaColuna,int numero_jogada,char descricao[50],tabuleiro *tab);
void anuncia_vencedor(pJogadas lista_jogadas);
void exporta_dados(pJogadas lista_jogadas);
void guarda_jogo(pJogadas lista_jogadas);
void guarda_lista(pJogadas lista_jogadas,FILE *file);
int verifica_ficheiro();
pJogadas retoma_jogadas(pJogadas lista_jogadas);
void guarda_jogo2(pJogadas lista_jogadas);
int ultima_jogada(pJogadas lista_jogadas);
char ultimo_jogador(pJogadas lista_jogadas);
int verifica_pedrasA(pJogadas lista_jogadas);
int verifica_acrescentaA(pJogadas lista_jogadas);
int verifica_pedrasB(pJogadas lista_jogadas);
int verifica_acrescentaB(pJogadas lista_jogadas);
pJogadas remove_primeiroNo(pJogadas lista_jogadas);
void listar_ktabuleiros(pJogadas lista_jogadas);
void liberta_lista(pJogadas lista_jogadas);
int verificaComputador(pJogadas lista_jogadas);

#ifdef __cplusplus
}
#endif

#endif /* JOGADAS_H */

