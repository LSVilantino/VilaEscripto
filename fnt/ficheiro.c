#include "ficheiro.h"
#include "general.h"

#include "pilha.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#define FICHEIRO_PRÓXIMO_CHARAC(ficheiro) (char) fgetc(ficheiro)

static char** linhas;
static int recúo_quantidade;
static char* charactéres_pilha;
static int linha_actual_n;
static char* linha_actual;

void ficheiro_lêr__linha_introduzir_charac(char charac, char** linha) {
    char* linhaActual = *linha;
    linhaActual = memória_re_allocar(linha_actual_n + 1, linhaActual);
    linhaActual[linha_actual_n] = charac;
    linhaActual[linha_actual_n + 1] = LINHA_NIL;
    linha_actual_n++;
}

void ficheiro_lêr_arrancar() {
    linhas = memória_allocar(sizeof(char*));
    charactéres_pilha = pilha_construir(recúo_quantidade);
    linha_actual_n = 0;
    linha_actual = memória_allocar(1);
}

char**
ficheiro_lêr(char* caminho) {
    FILE* ficheiro;
    errno_t numErro = fopen_s(&ficheiro, caminho, "r");
    if (numErro != 0) {
        printf("O ficheiro %s não foi encontrado, ou está ocupado.", caminho); abort();
    }

    recúo_quantidade = 3;
    ficheiro_lêr_arrancar();

    for (int i = 0;; i++) {
        charactéres_pilha = pilha_introduzir(FICHEIRO_PRÓXIMO_CHARAC(ficheiro));

        //printf("\n\n");
        //printf(pilha);
        //printf("\n\n");

        if (charactéres_pilha[recúo_quantidade - 1] == EOF) {
            printf(linha_actual);
            break;
        }
        else if (charactéres_pilha[recúo_quantidade] == LINHA_SALTA) {
            // AFAZER ~ Armazenar linha anteriôr e preparar memória à seguinte.
            printf(linha_actual);
        }

        ficheiro_lêr__linha_introduzir_charac(charactéres_pilha[0], &linha_actual);
    }

    fclose(ficheiro); // Fecha o ficheiro.

    return linhas;
}
