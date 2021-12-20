/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estruturas.h
 * Author: FNAC
 *
 * Created on 19 de abril de 2021, 13:03
 */

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct JOGADAS jogadas, *pJogadas;

typedef struct JOGADAS{
    
    int numero_jogada;
    int posicao_linha;
    int posicao_coluna;
    char jogador;
    char descricao[50];
    int linhas;
    int colunas;
    char **matriz;
    struct JOGADAS *prox;


}jogadas;

typedef struct TABULEIRO{
    int linhas;
    int colunas;
    char **matriz;
    
 
}tabuleiro;



#ifdef __cplusplus
}
#endif

#endif /* ESTRUTURAS_H */

