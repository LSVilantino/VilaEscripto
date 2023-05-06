#include "ficheiro.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** 
ficheiro_lêr(char* ficheiroNome) {
    char** linhas = malloc(sizeof(char*));
    char* linhaActualDoFicheiro = malloc(sizeof(char*));
    char charactéreActualDoFicheiro = '\0';
    FILE* ficheiroLido = fopen(ficheiroNome, "r");

    int n = 0;
    int nl = 0;
    int i = 0;
    while (charactéreActualDoFicheiro != EOF) {
        charactéreActualDoFicheiro = fgetc(ficheiroLido);

        if (charactéreActualDoFicheiro == '\n' || charactéreActualDoFicheiro == EOF) {
            linhas[nl] = malloc(sizeof(char*));
            linhas[nl] = strdup(linhaActualDoFicheiro);

            linhas = realloc(linhas, (nl + 1 * sizeof(linhas)) * sizeof(char**));

            linhaActualDoFicheiro = malloc(sizeof(char*));

            n = 0;
            nl = nl + 1;
            continue;
        }
        else {
            linhaActualDoFicheiro[n] = charactéreActualDoFicheiro;
            //linhaActualDoFicheiro = realloc(linhaActualDoFicheiro, (n + 1 * sizeof(linhaActualDoFicheiro)) * sizeof(char*));
            linhaActualDoFicheiro = realloc(linhaActualDoFicheiro, n + 1 * sizeof(char*)); // n + 1 é necessário pela 'regra do múltiplo a índice 0'.
            linhaActualDoFicheiro[n + 1] = '\0';
            n = n + 1;
            i = i + 1;
        }

        //printf("\n%c - %s", charactéreActualDoFicheiro, linhaActualDoFicheiro);
    }

    //printf("\n");

    free(linhaActualDoFicheiro);
    fclose(ficheiroLido);

    return linhas;
}