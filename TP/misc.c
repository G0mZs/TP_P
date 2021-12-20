/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */

// Verificar se o ficheiro está vazio

int check_empty(FILE *file) {
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0) {
        return 1;
    }

    fseek(file, savedOffset, SEEK_SET);
    return 0;
}

// Função para limpar o buffer

void clear_newlines(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

// Função para limpar ecrã, funciona de acordo com o SO

void clearScreen(void) {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

// Cabeçalho do programa

void header(void) {
    printf("\n\n");
    printf("\t#############################################################\n");
    printf("\t###################                        ##################\n");
    printf("\t###################    Jogo do Semaforo    ##################\n");
    printf("\t###################                        ##################\n");
    printf("\t#############################################################\n");
}

// Pressionar enter para continuar, alternativa ao getch()

void PressEnterToContinue(void) {
    printf("\t# Pressione ENTER para continuar\n");
    clear_newlines();
    while (getchar() != '\n')
        ;
}