#include "ficheiro.h"
#include "general.h"

#include "pilha.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#define FICHEIRO_PRÓXIMO_CHARAC(ficheiro) (char) fgetc(ficheiro)

char**
ficheiro_lêr(char* caminho) {
    FILE* ficheiro;
    errno_t numErro = fopen_s(&ficheiro, caminho, "r");
    if (numErro != 0) {
        printf("O ficheiro %s não foi encontrado, ou está ocupado.", caminho); abort();
    }

    char** linhas = memória_allocar(sizeof(char*));
    int recúo_quantidade = 3;
    char* pilha = pilha_construir(recúo_quantidade);
    int linhaActual_n = 0;
    char* linhaActual = memória_allocar(1);

    for (int i = 0;; i++) {
        pilha = pilha_introduzir(FICHEIRO_PRÓXIMO_CHARAC(ficheiro));

        //printf("\n\n");
        //printf(pilha);
        //printf("\n\n");

        if (pilha[recúo_quantidade - 1] == EOF) {
            printf(linhaActual);
            break;
        }
        else if (pilha[recúo_quantidade] == LINHA_SALTA) {
            // AFAZER ~ Armazenar linha anteriôr e preparar memória à seguinte.
            printf(linhaActual);
        }

        linhaActual = memória_re_allocar(linhaActual_n + 1, linhaActual);
        linhaActual[linhaActual_n] = pilha[0];
        linhaActual_n++;
    }

    fclose(ficheiro);

    return linhas;
}
