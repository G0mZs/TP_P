/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "jogadas.h"

pJogadas inserir_dados_jogadas(pJogadas lista_jogadas, char jogador,int jogadaLinha,int jogadaColuna,int numero_jogada,char descricao[50],tabuleiro *tab){
 

    
    pJogadas data;

    // Alocar memória para a posição atual
    data = (pJogadas) malloc(sizeof (jogadas));
    if (data == NULL) {
        printf("\n\tERRO a realocar memoria b\n");
        return data;
    }
    // Copiar os dados recebidos para a estrutura
    data->jogador = jogador;
    data->numero_jogada = numero_jogada;
    data->posicao_coluna = jogadaColuna;
    data->posicao_linha = jogadaLinha;
    strcpy(data->descricao,descricao);
    data->linhas = tab->linhas;
    data->colunas = tab->colunas;
    
    
    char** matriz= (char**)malloc((tab->linhas)*sizeof(char*));
    for(int i = 0; i < tab->linhas; i++)
    {
        matriz[i] = (char*)malloc((tab->colunas)*sizeof(char));
    }
    data->matriz = matriz;
    
    for(int i = 0; i < data->linhas; i++){
        for(int j = 0; j < data->colunas; j++){
            
            data->matriz[i][j] = tab->matriz[i][j];
        }
    }
    
    data->prox = NULL;
    
    // Se a lista for nula 
    if (lista_jogadas == NULL) {
    
        lista_jogadas = data;
    } else {

        pJogadas aux = lista_jogadas;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = data;
    }
    

    return lista_jogadas;
}


void anuncia_vencedor(pJogadas lista_jogadas){
    
    pJogadas aux;
    
    aux = lista_jogadas;
    
    if(aux == NULL){
        return;
    }
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    
    //Colocar um header que combine com a tabela para ficar um fim de jogo mais bonito
    printf("\n\n  O Jogador %c venceu o jogo ao jogar na posicao [%d,%d]\n",aux->jogador,aux->posicao_linha,aux->posicao_coluna);
    //Acrescentar a este printf a descrição que é (colocar peça verde , trocar ,etc)
    
}

void exporta_dados(pJogadas lista_jogadas){
    
    printf("\n  Insira o nome do ficheiro para guardar os dados do tabuleiro e das jogadas: ");
    
    char nomeFicheiro[50];
    
    scanf(" %s",&nomeFicheiro);
    
    FILE *ficheiro = fopen(nomeFicheiro,"wt");
    
    if(ficheiro == NULL){
        printf("\n  Erro ao criar ficheiro");
        return;
    }
    
    fprintf(ficheiro,"Sucessões do Tabuleiro: ");
    fprintf(ficheiro,"\n\n");
    
    pJogadas tab = lista_jogadas;
    
    while(tab != NULL){
        
        for(int i = 0; i < tab->linhas; i++){
            for(int j = 0; j < tab->colunas;j++){
                
                fprintf(ficheiro,"   %c   ",tab->matriz[i][j]);
            }
            fprintf(ficheiro,"\n");
        }
        fprintf(ficheiro,"\n\n");
        tab = tab->prox;
    }
    
    pJogadas aux = lista_jogadas;
    
    while(aux != NULL){
        fprintf(ficheiro,"\nJogada: %d || Jogador: %c",aux->numero_jogada,aux->jogador);
        fprintf(ficheiro,"\n%s",aux->descricao);
        fprintf(ficheiro,"\nJogou na linha %d e na coluna %d",aux->posicao_linha,aux->posicao_coluna);
        fprintf(ficheiro,"\n\n");
        
        aux = aux->prox;
    }
     
    printf("\n  Dados Guardados com sucesso !!\n");
    
    
    fclose(ficheiro);
    
   
}



void guarda_jogo2(pJogadas lista_jogadas){
    
    FILE *f;
    int i;
    pJogadas aux = lista_jogadas;
   
    
    
    f = fopen("jogo.bin", "wb");
    if(f==NULL)
    {
        clearScreen();
        header();
        printf("\n  Erro no acesso ao ficheiro\n");
        PressEnterToContinue();
        exit(0);
    }
    
     while(aux != NULL){
            fwrite(&aux->numero_jogada,sizeof(aux->numero_jogada),1,f);
            fwrite(&aux->jogador,sizeof(aux->jogador),1,f);
            fwrite(&aux->posicao_linha,sizeof(aux->posicao_linha),1,f);
            fwrite(&aux->posicao_coluna,sizeof(aux->posicao_coluna),1,f);
            fwrite(aux->descricao,sizeof(aux->descricao),1,f);
            fwrite(&aux->linhas,sizeof(aux->linhas),1,f);
            fwrite(&aux->colunas,sizeof(aux->colunas),1,f);
            
            for(int i = 0; i < aux->linhas; i++){
             for(int j = 0; j < aux->colunas; j++){     
                fwrite(&aux->matriz[i][j],sizeof(aux->matriz[i][j]),1,f);            }
        }
            
            aux = aux->prox;
        }

   
    fclose(f);
}

 

pJogadas retoma_jogadas(pJogadas lista_jogadas){
    
    
    FILE *f;
    int a;
    tabuleiro* tab;
    
    f = fopen("jogo.bin", "rb");
    if(f==NULL)
    {
        clearScreen();
        header();
        printf("\n  Erro no acesso ao ficheiro\n");
        PressEnterToContinue();
        exit(0);
    }
    pJogadas aux =(pJogadas)malloc(sizeof(jogadas));
   
        while(fread(&aux->numero_jogada,sizeof(aux->numero_jogada),1,f) > 0){
            
            fread(&aux->jogador,sizeof(aux->jogador),1,f);
            fread(&aux->posicao_linha,sizeof(aux->posicao_linha),1,f);
            fread(&aux->posicao_coluna,sizeof(aux->posicao_coluna),1,f);
            fread(aux->descricao,sizeof(aux->descricao),1,f);
            fread(&aux->linhas,sizeof(aux->linhas),1,f);
            fread(&aux->colunas,sizeof(aux->colunas),1,f);
            
            char** matrix= (char**)malloc((aux->linhas)*sizeof(char*));
            for(int i = 0; i < aux->linhas; i++)
            {
                matrix[i] = (char*)malloc((aux->colunas)*sizeof(char));
            }
            aux->matriz = matrix;
            
            for(int i = 0; i < aux->linhas; i++){
             for(int j = 0; j < aux->colunas; j++){     
                fread(&aux->matriz[i][j],sizeof(aux->matriz[i][j]),1,f);            }
        }
            
            
            
            pJogadas data;

            // Alocar memória para a posição atual
            data = (pJogadas) malloc(sizeof (jogadas));
            if (data == NULL) {
                printf("\n\tERRO a realocar memoria b\n");
                return data;
            }
            // Copiar os dados recebidos para a estrutura
            data->jogador = aux->jogador;
            data->numero_jogada = aux->numero_jogada;
            data->posicao_coluna = aux->posicao_coluna;
            data->posicao_linha = aux->posicao_linha;
            strcpy(data->descricao,aux->descricao);
            data->linhas = aux->linhas;
            data->colunas = aux->colunas;


            char** matriz= (char**)malloc((aux->linhas)*sizeof(char*));
            for(int i = 0; i < aux->linhas; i++)
            {
                matriz[i] = (char*)malloc((aux->colunas)*sizeof(char));
            }
            data->matriz = matriz;

            for(int i = 0; i < data->linhas; i++){
                for(int j = 0; j < data->colunas; j++){

                    data->matriz[i][j] = aux->matriz[i][j];
                }
            }

            data->prox = NULL;


            // Se os dados forem inseridos no inicio do programa aponta para a
            // proxima posição da lista
            // Caso contrário aponta para a lista ja existente
            if (lista_jogadas == NULL) {

                lista_jogadas = data;
            } else {

                pJogadas aux = lista_jogadas;
                while(aux->prox != NULL)
                    aux = aux->prox;
                aux->prox = data;
            }
    
    }
   
 
    fclose(f);
    remove("jogo.bin");
    return lista_jogadas;
}
 
  

int verifica_ficheiro(){
    
    FILE *f;
    int i;
    
    
    f = fopen("jogo.bin", "rb");
    if(f==NULL)
    {
        return 0;
    }
    
    if(check_empty(f) == 1){
        return 0;
    }
    
    return 1;
    
    fclose(f);
    
}

int ultima_jogada(pJogadas lista_jogadas){
    
    pJogadas aux;
    
    aux = lista_jogadas;
    

    while(aux->prox != NULL){
        aux = aux->prox;
    }
    
    return aux->numero_jogada;
    
}

char ultimo_jogador(pJogadas lista_jogadas){
    pJogadas aux;
    
    aux = lista_jogadas;
    

    while(aux->prox != NULL){
        aux = aux->prox;
    }
    
    return aux->jogador;
}


int verifica_pedrasA(pJogadas lista_jogadas){
    
    pJogadas aux;
    int contador = 0;
    
    aux = lista_jogadas;
    

    
    while(aux != NULL){
        if(aux->jogador == 'A' && strcmp(aux->descricao,"Colocou uma pedra") == 0){
            contador++;
        }
        aux = aux->prox;
    }
    
    return contador;
    
}

int verifica_pedrasB(pJogadas lista_jogadas){
    
    pJogadas aux;
    int contador = 0;
    
    aux = lista_jogadas;
    
    while(aux != NULL){
        if(aux->jogador == 'B' && strcmp(aux->descricao,"Colocou uma pedra") == 0){
            contador++;
        }
        aux = aux->prox;
    }
    
    return contador;
    
}

int verifica_acrescentaA(pJogadas lista_jogadas){
    
    pJogadas aux;
    int contador = 0;
    
    aux = lista_jogadas;
    

    while(aux != NULL){
        
        if(aux->jogador == 'A'){
            if(strcmp(aux->descricao,"Acrescentou uma linha") == 0 || strcmp(aux->descricao,"Acrescentou uma coluna") == 0){
                contador++;
            }
        }
        
        aux = aux->prox;
    }
    
    return contador;
}

int verifica_acrescentaB(pJogadas lista_jogadas){
    
    pJogadas aux;
    int contador = 0;
    
    aux = lista_jogadas;
    

     while(aux != NULL){
        
        if(aux->jogador == 'B'){
            if(strcmp(aux->descricao,"Acrescentou uma linha") == 0 || strcmp(aux->descricao,"Acrescentou uma coluna") == 0){
                contador++;
            }
        }
        
        aux = aux->prox;
    }
    
    return contador;
}

pJogadas remove_primeiroNo(pJogadas lista_jogadas){
    
    
    pJogadas temp = lista_jogadas;
    
    lista_jogadas = lista_jogadas->prox;
    
    free(temp);
    delete temp;
    
    return lista_jogadas;
}

void listar_ktabuleiros(pJogadas lista_jogadas){
    
    int numero = 0;
    pJogadas aux = lista_jogadas;
    
    clearScreen();
    printf("  Introduza o numero de tabuleiros anteriores que deseja ver: ");
    scanf("%d",&numero);
            
    if(numero > ultima_jogada(lista_jogadas)){
        printf("\n  Ainda nao existe esse numero de tabuleiros!!\n");
        PressEnterToContinue();
        return;
    }
    if(numero <= 0){
        printf("\n  O numero que introduziu e incorreto!!\n");
        PressEnterToContinue();
        return;
    }
        else{
            printf("\n");

            while(aux != NULL){
                if(aux->numero_jogada > ultima_jogada(lista_jogadas) - numero){

                    for(int i = 0; i < aux->linhas; i++){
                        for(int j = 0; j < aux->colunas; j++){

                            printf("    %c    ",aux->matriz[i][j]);

                        }
                        printf("\n");
                    }
                    printf("\n\n");
            }
            aux = aux->prox;
        }

        PressEnterToContinue();
    }
    
    
}

void liberta_lista(pJogadas lista_jogadas){
    pJogadas aux;
    while(lista_jogadas != NULL){
        aux = lista_jogadas;
        lista_jogadas = lista_jogadas->prox;
        free(aux);
    }
}

int verificaComputador(pJogadas lista_jogadas){
    pJogadas aux = lista_jogadas;
    int contador = 0;
    
    while(aux != NULL){
        if(aux->jogador == 'P'){
            contador++;
        }
        aux = aux->prox;
    }
    
    if(contador > 0){
        return 1;
    }
    else
        return 0;
}