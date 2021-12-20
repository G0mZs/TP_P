/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: FNAC
 *
 * Created on 19 de abril de 2021, 12:58
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogadas.h"
#include "utils.h"
#include "estruturas.h"
#include "tabuleiro.h"
#include "misc.h"

int main()
{
	initRandom();
        char resposta;
       
        
        int linhas,colunas;
	tabuleiro *tab = NULL;
	pJogadas lista_jogadas = NULL;
	linhas = randomLinhas();
        colunas = linhas;
       
 
        tab = malloc(sizeof(tabuleiro));
        if(tab == NULL){
		printf("\n\tErro a alocar memoria\n");
		exit(0);
	}

        
        if(verifica_ficheiro() == 1){
            printf("\n  Possui um jogo guardado!!Deseja retoma-lo?[S-Sim,N-Nao]: ");
            scanf(" %c",&resposta);
            
        }
        
        if(resposta == 'S'){ 
 
            lista_jogadas = retoma_jogadas(lista_jogadas);
            
           
            geraMatriz_guardada(lista_jogadas,tab);
            
            if(verificaComputador(lista_jogadas) == 0){
                inicia_jogo(tab,lista_jogadas);
            }
            else{
                jogo_contra_programa(tab,lista_jogadas);
            }
        }
 
         else{

            geraMatriz(tab,linhas,colunas);
            
            lista_jogadas = (pJogadas)malloc(sizeof(jogadas));
            if(lista_jogadas == NULL){
                printf("\n\tErro a alocar memoria\n");
                exit(0);
            }
        
            lista_jogadas->jogador = 'C';
            lista_jogadas->numero_jogada = 0;
            strcpy(lista_jogadas->descricao,"Por jogar");
            lista_jogadas->prox = NULL;

            menu(tab,lista_jogadas);
         }
         
	
}
        

void menu(tabuleiro *tab, pJogadas lista_jogadas) {

    int op;

menu:
  
    tab_inicial(tab);
    clearScreen();
    header();
    
   
    printf("\n\t# 1 - Iniciar um novo jogo");
    printf("\n\t# 0 - Sair\n\n");

    printf("\t### : ");
    scanf("%d", &op);

    switch (op) {
        case 1:
            clearScreen();
            menu_jogo(tab, lista_jogadas);
            break;
        case 0:
            clearScreen();
            exit(0);
            break;
        default:
            printf("\n\t# Opcao invalida\n");
            PressEnterToContinue();
            clearScreen();
            goto menu;
    }
    goto menu;
}