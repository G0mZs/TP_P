/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "tabuleiro.h"

int randomLinhas(){

    int linhas = 0;
    linhas = intUniformRnd(3,5);
    
    return linhas;
}

void geraMatriz(tabuleiro *tab,int linhas,int colunas){ 
    
    tab->colunas = colunas;
    tab->linhas = linhas;
    
    char** matriz= (char**)malloc((linhas)*sizeof(char*));
    for(int i = 0; i < tab->linhas; i++)
    {
        matriz[i] = (char*)malloc((colunas)*sizeof(char));
    }
    tab->matriz = matriz; 
}

void geraMatriz_guardada(pJogadas lista_jogadas,tabuleiro *tab){
    
    pJogadas aux;
    
    aux = lista_jogadas;
    
    if(aux == NULL){
        return;
    }
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    
    int linhas = 0, colunas = 0;
    tab->colunas = aux->colunas;
    tab->linhas = aux->linhas;
    linhas = tab->linhas;
    colunas = tab->colunas;
    
    
    
    char** matriz= (char**)malloc((linhas)*sizeof(char*));
    for(int i = 0; i < tab->linhas; i++)
    {
        matriz[i] = (char*)malloc((colunas)*sizeof(char));
    }
    tab->matriz = matriz;
    
    for(int i = 0; i < tab->linhas; i++){
        for(int j = 0; j < tab->colunas; j++){
            tab->matriz[i][j] = aux->matriz[i][j];
        }
    }
    
}

void tab_inicial(tabuleiro *tab){
    
    char inicial;
 
    
    for(int i = 0; i < tab->linhas;i++){
        for(int j = 0; j < tab->colunas; j++){
       
            tab->matriz[i][j] = '_';
        }
    }
   
}

void menu_jogo(tabuleiro *tab,pJogadas lista_jogadas){
    
      int op;

menu:
  

    clearScreen();
    header();
    

    printf("\n\t# 1 - Jogar contra outro jogador");
    printf("\n\t# 2 - Jogar contra o programa");


    printf("\n\n\t### : ");
    scanf("%d", &op);

    switch (op) {
        case 1:
            clearScreen();
            inicia_jogo(tab,lista_jogadas);
            break;
        case 2:
            clearScreen();
            jogo_contra_programa(tab,lista_jogadas);
            break;
        default:
            printf("\n\t# Opcao invalida\n");
            PressEnterToContinue();
            clearScreen();
            goto menu;
    }
    goto menu;
    
    
}

void inicia_jogo(tabuleiro *tab,pJogadas lista_jogadas){
    
    int op;
    char jogador;
    int jogada = ultima_jogada(lista_jogadas);
    int linhas = 0,colunas = 0;
    
    if(ultimo_jogador(lista_jogadas) != 'A' && ultimo_jogador(lista_jogadas) != 'B')
    {
        lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,jogada,lista_jogadas->descricao,tab);
        lista_jogadas = remove_primeiroNo(lista_jogadas);
    }

 do{ 
     
     
     
    clearScreen();
    mostra_tabela(tab);
    
     if(ultimo_jogador(lista_jogadas) == 'A'){
        goto menu2;
    }
    
    
    
    
 menu:
    jogada = ultima_jogada(lista_jogadas);       
    jogador = 'A';
    printf("\n\t# E a vez do jogador A\n");       
    printf("\n\t# 1 - Colocar uma peca Verde numa celula vazia");
    printf("\n\t# 2 - Trocar uma peca Verde que esteja colocada no tabuleiro por uma peca Amarela");
    printf("\n\t# 3 - Trocar uma peca Amarela que esteja colocada no tabuleiro por uma peca Vermelha");
    printf("\n\t# 4 - Colocar uma pedra numa celula vazia");
    printf("\n\t# 5 - Acrescentar uma linha ou coluna ao tabuleiro");
    printf("\n\t# 6 - Interromper o jogo");

    printf("\n\n\t### : ");
    scanf("%d", &op);

    switch (op) {
        case 1:
            clearScreen();
            coloca_verde(tab,jogador,jogada,lista_jogadas);
            
            break;
        case 2:
            clearScreen();
                if(averigua_PlayAmarela(tab) == 1){
                    troca_amarela(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    printf("Nao existem pecas verdes para trocar");
                    header();
                    mostra_tabela(tab);
                    goto menu;
                }
            
            break;
        case 3:
            clearScreen();
             if(averigua_PlayVermelha(tab) == 1){
                    troca_vermelha(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    printf("Nao existem pecas amarelas para trocar");
                    header();
                    mostra_tabela(tab);
                    goto menu;
                }
         
            break;
        case 4:
            
            if(verifica_pedrasA(lista_jogadas) == 0){
                clearScreen();
                coloca_pedra(tab,jogador,jogada,lista_jogadas);
            }
            else{
                printf("\n\t#Apenas pode selecionar esta opcao uma vez por jogo\n");
                PressEnterToContinue();
                goto menu;
            }
            
            break;
        case 5:
            if(verifica_acrescentaA(lista_jogadas) < 2){
             clearScreen();
             acrescenta(tab,jogador,jogada,lista_jogadas);
            }
            else{
               printf("\n\t#Apenas pode selecionar esta opcao duas vezes por jogo\n");
               PressEnterToContinue();
               goto menu; 
            }
             break;
        case 6:
            clearScreen();
            lista_jogadas = remove_primeiroNo(lista_jogadas);
            guarda_jogo2(lista_jogadas);
            header();
            printf("\n  O Jogo foi interrompido");
            liberta_lista(lista_jogadas);
            free(tab);
            exit(0);
            break;
        default:
            printf("\n\t# Opcao invalida\n");
            PressEnterToContinue();
            clearScreen();
            goto menu;
    }
     
    
    if(averigua_vitoria(tab) == 1){
        clearScreen();
        mostra_tabela(tab);
        anuncia_vencedor(lista_jogadas);
        exporta_dados(lista_jogadas);
        liberta_lista(lista_jogadas);
        free(tab);
        exit(0);
    }
    else if(averigua_vitoria(tab) == 2){
        clearScreen();
        mostra_tabela(tab);
        printf("\n  O Jogo acabou num empate!!\n");
        exporta_dados(lista_jogadas);
        liberta_lista(lista_jogadas);
        free(tab);
        exit(0);
    }
    
    
    clearScreen();
    mostra_tabela(tab);
    

 menu2:
      
    jogada = ultima_jogada(lista_jogadas);          
  

    jogador = 'B';
    printf("\n\t# E a vez do jogador B\n");        
    printf("\n\t# 1 - Colocar uma peca Verde numa celula vazia");
    printf("\n\t# 2 - Trocar uma peca Verde que esteja colocada no tabuleiro por uma peca Amarela");
    printf("\n\t# 3 - Trocar uma peca Amarela que esteja colocada no tabuleiro por uma peca Vermelha");
    printf("\n\t# 4 - Colocar uma pedra numa celula vazia");
    printf("\n\t# 5 - Acrescentar uma linha ou coluna ao tabuleiro");
    printf("\n\t# 6 - Interromper o jogo");


    printf("\n\n\t### : ");
    scanf("%d", &op);

        switch (op) {
            case 1:
                clearScreen();
                coloca_verde(tab,jogador,jogada,lista_jogadas);
                
                break;
            case 2:
                clearScreen();
                if(averigua_PlayAmarela(tab) == 1){
                    troca_amarela(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    printf("Nao existem pecas verdes para trocar");
                    header();
                    mostra_tabela(tab);
                    goto menu2;
                }
            
                break;
            case 3:
                clearScreen();
                 if(averigua_PlayVermelha(tab) == 1){
                    troca_vermelha(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    printf("Nao existem pecas amarelas para trocar");
                    header();
                    mostra_tabela(tab);
                    goto menu2;
                }
         
              
                break;
            case 4:
                if(verifica_pedrasB(lista_jogadas) == 0){
                    clearScreen();
                    coloca_pedra(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    printf("\n\t#Apenas pode selecionar esta opcao uma vez por jogo\n");
                    PressEnterToContinue();
                    goto menu2;
                }
                break;
            case 5:
                if(verifica_acrescentaB(lista_jogadas) < 2){
                    clearScreen();
                    acrescenta(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    printf("\n\t#Apenas pode selecionar esta opcao duas vezes por jogo\n");
                    PressEnterToContinue();
                    goto menu; 
                }
                break;
            case 6:
                clearScreen();
                lista_jogadas = remove_primeiroNo(lista_jogadas);
                guarda_jogo2(lista_jogadas);
                header();
                printf("\n  O Jogo foi interrompido");
                liberta_lista(lista_jogadas);
                free(tab);
                exit(0);
                break;
            default:
                printf("\n\t# Opcao invalida\n");
                PressEnterToContinue();
                clearScreen();
                goto menu2;
        }  
    
    }
    while(averigua_vitoria(tab) == 0);//Fazer função para verificar se algum ganha
    
    
     if(averigua_vitoria(tab) == 1){
        clearScreen();
        mostra_tabela(tab);
        anuncia_vencedor(lista_jogadas);
        exporta_dados(lista_jogadas);
        liberta_lista(lista_jogadas);
        free(tab);
        exit(0);
    }
    else if(averigua_vitoria(tab) == 2){
        clearScreen();
        mostra_tabela(tab);
        printf("\n  O Jogo acabou num empate!!\n"); 
        exporta_dados(lista_jogadas);
        liberta_lista(lista_jogadas);
        free(tab);
        exit(0);
    }
    
}

void jogo_contra_programa(tabuleiro *tab,pJogadas lista_jogadas){
    
    int op;
    char jogador;
    int jogada = ultima_jogada(lista_jogadas);
    int contador_pedraP = 0,contador_acrescentaP = 0;
    int linhas = 0,colunas = 0;
    
     if(ultimo_jogador(lista_jogadas) != 'A' && ultimo_jogador(lista_jogadas) != 'P')
    {
        lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,jogada,lista_jogadas->descricao,tab);
        lista_jogadas = remove_primeiroNo(lista_jogadas);
    }
    
     
    jogada++; 
    clearScreen();
 
    
 do{
    
    
    mostra_tabela(tab);
    
 menu:
    jogada = ultima_jogada(lista_jogadas);  
    jogador = 'A';
    printf("\n\t# E a vez do jogador A\n");       
    printf("\n\t# 1 - Colocar uma peca Verde numa celula vazia");
    printf("\n\t# 2 - Trocar uma peca Verde que esteja colocada no tabuleiro por uma peca Amarela");
    printf("\n\t# 3 - Trocar uma peca Amarela que esteja colocada no tabuleiro por uma peca Vermelha");
    printf("\n\t# 4 - Colocar uma pedra numa celula vazia");
    printf("\n\t# 5 - Acrescentar uma linha ou coluna ao tabuleiro");
    printf("\n\t# 6 - Interromper o jogo");
    
    printf("\n\n\t### : ");
    scanf("%d", &op);

    
    //Meter o tabuleiro a ser mostrado em cada opção e mudar ao esoclher a linha e coluna para jogar para - 1
    
    switch (op) {
        case 1:
            clearScreen();
            coloca_verde(tab,jogador,jogada,lista_jogadas);
            
            break;
        case 2:
            clearScreen();
             if(averigua_PlayAmarela(tab) == 1){
                    troca_amarela(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    printf("Nao existem pecas verdes para trocar");
                    header();
                    mostra_tabela(tab);
                    goto menu;
                }
         
            
            break;
        case 3:
            clearScreen();
             if(averigua_PlayVermelha(tab) == 1){
                    troca_vermelha(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    printf("Nao existem pecas amarelas para trocar");
                    header();
                    mostra_tabela(tab);
                    goto menu;
                }
         
            break;
        case 4:
            
            if(verifica_pedrasA(lista_jogadas) == 0){
                clearScreen();
                coloca_pedra(tab,jogador,jogada,lista_jogadas);
            }
            else{
                printf("\n\t#Apenas pode selecionar esta opcao uma vez por jogo\n");
                PressEnterToContinue();
                goto menu;
            }
            
            break;
        case 5:
            if(verifica_acrescentaA(lista_jogadas) < 2){
             clearScreen();
             acrescenta(tab,jogador,jogada,lista_jogadas);
            }
            else{
               printf("\n\t#Apenas pode selecionar esta opcao duas vezes por jogo\n");
               PressEnterToContinue();
               goto menu; 
            }
             break;
        case 6:
            clearScreen();
            lista_jogadas = remove_primeiroNo(lista_jogadas);
            guarda_jogo2(lista_jogadas);
            header();
            printf("\n  O Jogo foi interrompido");
            liberta_lista(lista_jogadas);
            free(tab);
            exit(0);
            break;
        default:
            printf("\n\t# Opcao invalida\n");
            PressEnterToContinue();
            clearScreen();
            goto menu;
    }
    
     if(averigua_vitoria(tab) == 1){
        clearScreen();
        mostra_tabela(tab);
        anuncia_vencedor(lista_jogadas);
        lista_jogadas = remove_primeiroNo(lista_jogadas);
        exporta_dados(lista_jogadas);
        liberta_lista(lista_jogadas);
        free(tab);
        exit(0);
    }
    else if(averigua_vitoria(tab) == 2){
        clearScreen();
        mostra_tabela(tab);
        printf("\n  O Jogo acabou num empate!!\n");
        lista_jogadas = remove_primeiroNo(lista_jogadas);
        exporta_dados(lista_jogadas);
        liberta_lista(lista_jogadas);
        free(tab);
        exit(0);
    }
    
    
    clearScreen();
    mostra_tabela(tab);
    
    
menu2:
     jogada = ultima_jogada(lista_jogadas);    
    

    jogador = 'P';
    op = intUniformRnd(1,5);


        switch (op) {
            case 1:
                clearScreen();
                programa_coloca_verde(tab,jogador,jogada,lista_jogadas);
                
                break;
            case 2:
                clearScreen();
                if(averigua_PlayAmarela(tab) == 1){
                    programa_troca_amarela(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    printf("Nao existem pecas verdes para trocar");
                    header();
                    goto menu2;
                }
           
                break;
            case 3:
                clearScreen();
                 if(averigua_PlayVermelha(tab) == 1){
                    programa_troca_vermelha(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    printf("Nao existem pecas amarelas para trocar");
                    header();
                    goto menu2;
                }
         
                break;
            case 4:
                if(contador_pedraP == 0){
                    contador_pedraP++;
                    clearScreen();
                    programa_coloca_pedra(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    goto menu2;
                }
                break;
            case 5:
                if(contador_acrescentaP < 2){
                    contador_acrescentaP++;
                    clearScreen();
                    programa_acrescenta(tab,jogador,jogada,lista_jogadas);
                }
                else{
                    goto menu2;  
                }
             break;
                break;
            default:
                printf("\n\t# Opcao invalida\n");
                PressEnterToContinue();
                clearScreen();
                goto menu2;
        }  
    }
    while(averigua_vitoria(tab) == 0);
    
     if(averigua_vitoria(tab) == 1){
        clearScreen();
        mostra_tabela(tab);
        anuncia_vencedor(lista_jogadas);
        lista_jogadas = remove_primeiroNo(lista_jogadas);
        exporta_dados(lista_jogadas);
        liberta_lista(lista_jogadas);
        free(tab);
        exit(0);
    }
    else if(averigua_vitoria(tab) == 2){
        clearScreen();
        mostra_tabela(tab);
        printf("\n  O Jogo acabou num empate!!\n");
        lista_jogadas = remove_primeiroNo(lista_jogadas);
        exporta_dados(lista_jogadas);
        liberta_lista(lista_jogadas);
        free(tab);
        exit(0);
    }
    
    
}



void programa_coloca_verde(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas){
    
    int linhas, colunas,averigua = 0;
    char descricao[50] = "Colocou uma peca verde";
    
    do{
    
        linhas = intUniformRnd(0,tab->linhas - 1);
        colunas = intUniformRnd(0,tab->colunas - 1);
   
    
        if(tab->matriz[linhas][colunas] == '_'){

            tab->matriz[linhas][colunas] = 'G';
            averigua = 0;
        }
        else{
            averigua = 1;
        }
        
   
    
    }while(averigua == 1);
    
    printf("\n  O Programa colocou uma peca verde na linha %d e coluna %d \n",linhas,colunas);
    njogada = njogada + 1;
    lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,njogada,descricao,tab);
    
    
     
   
    
}



void programa_troca_amarela(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas){
    
    int linhas, colunas,averigua = 0;
    char descricao[50] = "Trocou uma peca verde por uma amarela";
    
    do{
    
        linhas = intUniformRnd(0,tab->linhas - 1);
        colunas = intUniformRnd(0,tab->colunas - 1);
    
     
    
            
    if(tab->matriz[linhas][colunas] != 'G'){
 
        averigua = 1;
    }
    else{
        tab->matriz[linhas][colunas] = 'Y';
        averigua = 0;
    }
    
    
    
    
    }while(averigua == 1);
    
    printf("\n  O Programa trocou uma peca verde por uma amarela na linha %d e coluna %d \n",linhas,colunas);
 
    njogada = njogada + 1;
    lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,njogada,descricao,tab);
}



void programa_troca_vermelha(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas){
    
     int linhas, colunas,averigua = 0;
     char descricao[50] = "Trocou uma peca amarela por uma vermelha";
    
    do{
    
        linhas = intUniformRnd(0,tab->linhas - 1);
        colunas = intUniformRnd(0,tab->colunas - 1);
    
     
    
            
    if(tab->matriz[linhas][colunas] != 'Y'){
 
        averigua = 1;
    }
    else{
        tab->matriz[linhas][colunas] = 'R';
        averigua = 0;
    }
    
    
    
    
    }while(averigua == 1);
    
    printf("\n  O Programa trocou uma peca amarela por uma vermelha na linha %d e coluna %d \n",linhas,colunas);
    
    njogada = njogada + 1;
    lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,njogada,descricao,tab);
    
}

void programa_coloca_pedra(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas){
    
     int linhas, colunas,averigua = 0;
    char resposta;
    char descricao[50] = "Colocou uma pedra";
    
    do{
    
        linhas = intUniformRnd(0,tab->linhas - 1);
        colunas = intUniformRnd(0,tab->colunas - 1);
    
   
        if(tab->matriz[linhas][colunas] == '_'){

            tab->matriz[linhas][colunas] = 'O';
            averigua = 0;
        }
        else{
            averigua = 1;
        }
        
   
    
    }while(averigua == 1);
    
    printf("\n  O programa colocou uma pedra na linha %d coluna %d\n",linhas,colunas);
    

    njogada = njogada + 1;
    lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,njogada,descricao,tab);
}

void programa_acrescenta(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas){
    
     char resposta[50];
    int linhas = 0;
    int colunas = 0;
    char resp;
    int continua = 0;
    int escolha = 0;
    char descricao[50];
    
    
    
    do{
        
        escolha = intUniformRnd(1,2);
        
        if(escolha == 1){
            strcpy(resposta,"linha");
        }
        else{
            strcpy(resposta,"coluna");
        }

        if(strcmp(resposta,"linha") == 0){
            strcpy(descricao,"Acrescentou uma linha");
            continua++;
            tab->linhas = tab->linhas + 1;
            altera_linhas(tab);
            printf("\n  O programa acrescentou uma linha\n");
        }
        if(strcmp(resposta,"coluna") == 0){
            strcpy(descricao,"Acrescentou uma coluna");
            continua++;
            tab->colunas = tab->colunas + 1;
            altera_colunas(tab);
            printf("\n  O programa acrescentou uma coluna\n");
        }
       

    }while(continua == 0);
    
    njogada = njogada + 1;
    lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,njogada,descricao,tab);
    
}



void mostra_tabela(tabuleiro *tab){
    int a;
    
    printf("\n\n");
    for(int i = 0; i < tab->linhas;i++){
        for(int j = 0; j < tab->colunas; j++){
            printf("    %c  ",tab->matriz[i][j]);
        }
        printf("\n");
    }
    
}

void coloca_pedra(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas){
    
    int linhas, colunas,averigua = 0;
    char resposta;
    char descricao[50] = "Colocou uma pedra";
    
  do{ 
    printf("\n  Deseja ver os tabuleiros anteriores?[S-Sim,N-Nao]: ");
    scanf(" %c",&resposta);
    
    if(resposta == 'S'){
        listar_ktabuleiros(lista_jogadas);
    }
    
    
  }
  while(resposta != 'S' && resposta != 'N');
    printf("\n");
    mostra_tabela(tab);
    do{
    
    printf("\n  Introduza a linha onde quer inserir a pedra compreendidas no intervalo [0,%d]: ",tab->linhas - 1);
    scanf("%d",&linhas);
    printf("\n  Introduza a coluna onde quer inserir a pedra compreendidas no intervalo [0,%d]: ",tab->colunas - 1);
    scanf("%d",&colunas);
    
    if(colunas >= 0 && colunas < tab->colunas && linhas >= 0 && linhas < tab->linhas){
    
    
            if(tab->matriz[linhas][colunas] == '_'){

                tab->matriz[linhas][colunas] = 'O';
                averigua = 0;
            }
            else{
                printf("\n  Este espaco ja esta preenchido !!Tente outra posicao\n");
                averigua = 1;
            }
        
    }
    else{
        printf("\n   O numero da linha ou coluna introduzido excede o intervalo!!\n");
    }
    
    }while(colunas < 0 || colunas > tab->colunas - 1 || linhas < 0 || linhas > tab->linhas - 1 || averigua == 1);
    njogada = njogada + 1;
    lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,njogada,descricao,tab);
    
 
}

void coloca_verde(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas){
    
    int linhas, colunas,averigua = 0;
    char resposta;
    char descricao[50] = "Colocou uma peca verde";
    
  do{ 
    printf("\n  Deseja ver os tabuleiros anteriores?[S-Sim,N-Nao]: ");
    scanf(" %c",&resposta);
    
    if(resposta == 'S'){
        listar_ktabuleiros(lista_jogadas);
    }
    
    
  }
  while(resposta != 'S' && resposta != 'N');
    printf("\n");
    mostra_tabela(tab);
    do{
    
    printf("\n  Introduza a linha onde quer inserir a peca verde compreendidas no intervalo [0,%d]: ",tab->linhas - 1);
    scanf("%d",&linhas);
    printf("\n  Introduza a coluna onde quer inserir a peca verde compreendidas no intervalo [0,%d]: ",tab->colunas - 1);
    scanf("%d",&colunas);
    
    if(colunas >= 0 && colunas < tab->colunas && linhas >= 0 && linhas < tab->linhas){
    
    
            if(tab->matriz[linhas][colunas] == '_'){ 

                tab->matriz[linhas][colunas] = 'G';
                averigua = 0;
            }
            else{
                printf("\n  Este espaco ja esta preenchido !!Tente outra posicao\n");
                averigua = 1;
            }
        
    }
    else{
        printf("\n   O numero da linha ou coluna introduzido excede o intervalo!!\n");
    }
    
    }while(colunas < 0 || colunas > tab->colunas - 1 || linhas < 0 || linhas > tab->linhas - 1 || averigua == 1);
    njogada = njogada + 1;
    lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,njogada,descricao,tab);
   
    
}


void troca_amarela(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas){
    
    int linhas, colunas,averigua = 0;
    char resposta;
    char descricao[50] = "Trocou uma peca verde por uma amarela";
    
  do{ 
        printf("\n  Deseja ver os tabuleiros anteriores?[S-Sim,N-Nao]: ");
        scanf(" %c",&resposta);
        
        if(resposta == 'S'){
           listar_ktabuleiros(lista_jogadas);
        }
    
    
  }
  while(resposta != 'S' && resposta != 'N');
    printf("\n");
    mostra_tabela(tab);
    do{
    
        printf("\n  Introduza a linha onde quer trocar a peca verde pela a amarela compreendidas no intervalo [0,%d]: ",tab->linhas - 1);
        scanf("%d",&linhas);
        printf("\n  Introduza a coluna onde quer trocar a peca verde pela a amarela compreendidas no intervalo [0,%d]: ",tab->colunas - 1);
        scanf("%d",&colunas);
    
     
        if(colunas >= 0 && colunas < tab->colunas && linhas >= 0 && linhas < tab->linhas){
                
            if(tab->matriz[linhas][colunas] != 'G'){
                printf("\n  Este espaco nao possui uma peca Verde!!\n");
                averigua = 1;
            }
            else{
                tab->matriz[linhas][colunas] = 'Y';
                averigua = 0;
            }
        }
        else{
            printf("\n   O numero da linha ou coluna introduzido excede o intervalo!!\n");
        }
    
    
    }while(colunas < 0 || colunas > tab->colunas - 1 || linhas < 0 || linhas > tab->linhas - 1 || averigua == 1);
    
    njogada = njogada + 1;
    lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,njogada,descricao,tab);
    
    
 
  
}

void troca_vermelha(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas){
    
    int linhas, colunas, averigua = 0;
    char resposta;
    char descricao[50] = "Trocou uma peca amarela por uma vermelha";
    
   do{ 
    printf("\n  Deseja ver os tabuleiros anteriores?[S-Sim,N-Nao]: ");
    scanf(" %c",&resposta);
    
    if(resposta == 'S'){
        listar_ktabuleiros(lista_jogadas);
    }
    
    
  }
  while(resposta != 'S' && resposta != 'N');
    printf("\n");
    mostra_tabela(tab);
     do{
    
    printf("\n  Introduza a linha onde quer trocar a peca amarela pela a vermelha compreendidas no intervalo [0,%d]: ",tab->linhas - 1);
    scanf("%d",&linhas);
    printf("\n  Introduza a coluna onde quer trocar a peca amarela pela a vermelha compreendidas no intervalo [0,%d]: ",tab->colunas - 1);
    scanf("%d",&colunas);
    
    if(colunas >= 0 && colunas < tab->colunas && linhas >= 0 && linhas < tab->linhas){
         
        if(tab->matriz[linhas][colunas] != 'Y'){
            printf("\n  Este espaco nao possui uma peca Amarela!!\n");
            averigua = 1;
        }
        else{
            tab->matriz[linhas][colunas] = 'R';
            averigua = 0;
        }
    
     }
     else{
        printf("\n   O numero da linha ou coluna introduzido excede o intervalo!!\n");
    }
    
    
    }while(colunas < 0 || colunas > tab->colunas - 1 || linhas < 0 || linhas > tab->linhas - 1 || averigua == 1);
    
   njogada = njogada + 1;
    lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,njogada,descricao,tab);
    
   
    
}


void acrescenta(tabuleiro *tab,char jogador,int njogada,pJogadas lista_jogadas){
    
    char resposta[50];
    int linhas = 0;
    int colunas = 0;
    char resp;
    int continua = 0;
    char descricao[50];
    
  do{ 
    printf("\n  Deseja ver os tabuleiros anteriores?[S-Sim,N-Nao]: ");
    scanf(" %c",&resp);
    
    if(resp == 'S'){
        listar_ktabuleiros(lista_jogadas);
    }
    
    
  }
  while(resp != 'S' && resp != 'N');
  printf("\n");
    mostra_tabela(tab);
    do{
        
        printf("\n  Pretende acrescentar uma linha ou uma coluna? Resposta: ");
        scanf("%s",resposta);

        if(strcmp(resposta,"linha") == 0){
            strcpy(descricao,"Acrescentou uma linha");
            continua++;
            tab->linhas = tab->linhas + 1;
            altera_linhas(tab);
        }
        if(strcmp(resposta,"coluna") == 0){
            strcpy(descricao,"Acrescentou uma coluna");
            continua++;
            tab->colunas = tab->colunas + 1;
            altera_colunas(tab);
        }
       

    }while(continua == 0);
    
   
    njogada = njogada + 1;
    lista_jogadas = inserir_dados_jogadas(lista_jogadas,jogador,linhas,colunas,njogada,descricao,tab);
    
    
  
    
}

void altera_linhas(tabuleiro *tab){
    
   
    char** matriz = (char**)realloc(tab->matriz,(tab->linhas)*sizeof(char*));
    
    if( matriz ){
        tab->matriz = matriz;
        for(int i = 0; i < 1; i++){
            
            tab->matriz[(tab->linhas - 1) + i] =(char*)malloc((tab->colunas)*sizeof(char));
            
        }
    }
    
    
  
    for(int i = 0; i < tab->linhas; i++){
        for(int j = 0; j < tab->colunas; j++){
            if(tab->matriz[i][j] != 'G' && tab->matriz[i][j] != 'Y' && tab->matriz[i][j] != 'R' && tab->matriz[i][j] != 'O' && tab->matriz[i][j] != '_'){
                tab->matriz[i][j] = '_';
       
            }
        }
    }
  
   

}

void altera_colunas(tabuleiro *tab){
    
    
    for(int i = 0; i < tab->linhas; i++)
    {
        char *matriz = (char*)realloc(tab->matriz[i],(tab->colunas)*sizeof(char));
        if(matriz){
            tab->matriz[i] = matriz;
        }
    }
    
    for(int i = 0; i < tab->linhas; i++){
        for(int j = 0; j < tab->colunas; j++){
            if(tab->matriz[i][j] != 'G' && tab->matriz[i][j] != 'Y' && tab->matriz[i][j] != 'R' && tab->matriz[i][j] != 'O' && tab->matriz[i][j] != '_'){
                tab->matriz[i][j] = '_';
       
            }
        }
    }
    
} 


int averigua_vitoria(tabuleiro* tab){
    
    
    int contador_colunasG = 0,contador_colunasY = 0,contador_colunasR = 0,contador_linhasG = 0,contador_linhasY = 0,contador_linhasR = 0, contador_diagonaisG = 0,contador_diagonaisR = 0,contador_diagonaisY = 0,empate = 0,coluna_aux = 0;
    char temp;
    
 
    //Verifica as linhas;
    for(int i = 0; i < tab->linhas; i++){
        for(int j = 0; j < tab->colunas; j++){
            if(tab->matriz[i][j] == 'G'){
                contador_linhasG++;
                
            }
            if(tab->matriz[i][j] == 'Y'){
                contador_linhasY++;
                
            }
            if(tab->matriz[i][j] == 'R'){
                contador_linhasR++;
                
            }
        }
        if(contador_linhasG == tab->colunas){
            return 1;
        }
         if(contador_linhasY == tab->colunas){
            return 1;
        }
         if(contador_linhasR == tab->colunas){
            return 1;
        }
        contador_linhasG = 0;
        contador_linhasY = 0;
        contador_linhasR = 0;
    }   
    
    
 //Verifica as colunas
    for(int i = 0; i < tab->colunas; i++){
        for(int j = 0; j < tab->linhas; j++){
            if(tab->matriz[j][i] == 'G'){ 
                contador_colunasG++;
            
            }
            if(tab->matriz[j][i] == 'Y'){
                contador_colunasY++;
            
            }
            if(tab->matriz[j][i] == 'R'){
                contador_colunasR++;
            
            }
        }
        
        if(contador_colunasG == tab->linhas){
            return 1;
        }
    
        if(contador_colunasY == tab->linhas){
           return 1;
       }
    
        if(contador_colunasR == tab->linhas){
           return 1;
       }
        
        contador_colunasG = 0;
        contador_colunasY = 0;
        contador_colunasR = 0;
        
    }
    

   //Verifica a diagonal principal e a secundária   
    //Só se verifica as diagonais caso seja um quadrado
    if(tab->linhas == tab->colunas){
        
        //Diagonal principal
      for(int i = 0; i < tab->linhas; i++){
          if(tab->matriz[i][i] == 'G'){
              contador_diagonaisG++;
          }
          else if(tab->matriz[i][i] == 'Y'){
              contador_diagonaisY++;
          }
          else if(tab->matriz[i][i] == 'R'){
              contador_diagonaisR++;
          }
        }
      
        if(contador_diagonaisG == tab->linhas){
            return 1;
        }
        else if(contador_diagonaisY == tab->linhas){
            return 1;
        }
        else if(contador_diagonaisR == tab->linhas){
            return 1;
        }
      
      //Resetar variáveis para poder avaliar a diagonal secundária
        contador_diagonaisG = 0;
        contador_diagonaisR = 0;
        contador_diagonaisY = 0;
        
        //Diagonal Secundária
        coluna_aux = tab->colunas - 1;
        
        for(int i = 0; i < tab->linhas; i++){
           if(tab->matriz[i][coluna_aux] == 'G'){
              contador_diagonaisG++;
          }
          else if(tab->matriz[i][coluna_aux] == 'Y'){
              contador_diagonaisY++;
          }
          else if(tab->matriz[i][coluna_aux] == 'R'){
              contador_diagonaisR++;
          }
            coluna_aux--;
            
        }
        
        if(contador_diagonaisG == tab->linhas){
            return 1;
        }
        else if(contador_diagonaisY == tab->linhas){
            return 1;
        }
        else if(contador_diagonaisR == tab->linhas){
            return 1;
        }
      
     }
    
    
    //Verificar se há empate
    //Se todos os espaços da matriz tiverem sido preenchidos com vermelho ou pedras da return a 2 e temos um empate;  
       for(int i = 0; i < tab->linhas; i++){
        for(int j = 0; j < tab->colunas; j++){
            
            if(tab->matriz[i][j] == 'R' || tab->matriz[i][j] == 'O'){
                empate++;
            }
            
            
        }
     }
    
    if(empate == tab->linhas * tab->colunas){
        return 2;
    }
     

    //Devolve 0 caso nenhuma das verificações acima se registem
    return 0;
 
}

int averigua_PlayAmarela(tabuleiro *tab){
    int contador = 0; 
    
    for(int i = 0; i < tab->linhas; i++){
        for(int j = 0; j< tab->colunas; j++){
            if(tab->matriz[i][j] == 'G'){
                contador++;
            }
        }
    }
    
    if(contador > 0){
        return 1;
    }
    else
        return 0;
}

int averigua_PlayVermelha(tabuleiro *tab){
    int contador = 0; 
    
    for(int i = 0; i < tab->linhas; i++){
        for(int j = 0; j< tab->colunas; j++){
            if(tab->matriz[i][j] == 'Y'){
                contador++;
            }
        }
    }
    
    if(contador > 0){
        return 1;
    }
    else
        return 0;
}
