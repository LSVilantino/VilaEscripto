#include "ficheiro.h"

#include "pilha.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#define FICHEIRO_PRÓXIMO_CHARAC(ficheiro) (char) fgetc(ficheiro)

static LINHA* linhas;
static int recúo_quantidade;
static Pilha pilha;
static int linha_actual_n;
static LINHA linha_actual;

void
ficheiro_lêr_arrancar() {
    linha_actual_n = 0;
    linhas = memória_allocar(sizeof(LINHA));
    pilha = pilha_construir(recúo_quantidade);
    linha_actual = memória_allocar(1);
}

void
ficheiro_lêr_libertar() {
    recúo_quantidade = 0;
    linha_actual_n = 0;
    free(linhas);
    free(pilha.conteúdo);
    free(linha_actual);
}

LINHA
ficheiro_lêr__linha_introduzir_charac(char charac, LINHA linha) {
    LINHA resultado = memória_re_allocar(linha_actual_n + 1, linha);
    resultado[linha_actual_n] = charac;
    resultado[linha_actual_n + 1] = LINHA_NIL;
    linha_actual_n++;

    return resultado;
}

LINHA*
ficheiro_lêr(LINHA caminho) {
    FILE* ficheiro;
    errno_t numErro = fopen_s(&ficheiro, caminho, FICHEIRO_MODO_LEITURA);
    if (numErro != 0) {
        printf("O ficheiro %s não foi encontrado, ou está ocupado.", caminho); abort();
    }

    recúo_quantidade = 3;
    ficheiro_lêr_arrancar();

    for (int i = 0;; i++) {
        pilha = pilha_introduzir(FICHEIRO_PRÓXIMO_CHARAC(ficheiro));

        //printf("\n\n");
        //printf(pilha);
        //printf("\n\n");

        if (pilha.conteúdo[pilha.recúo - 2] == EOF) {
            printf(linha_actual);
            break;
        }
        else if (pilha.conteúdo[pilha.recúo - 1] == LINHA_SALTA) {
            // AFAZER ~ Armazenar linha anteriôr e preparar memória à seguinte.
            printf(linha_actual);
            linha_actual_n = 0;
            continue;
        }

        if (pilha.conteúdo[pilha.recúo - 1] != LINHA_NIL) {
            linha_actual = ficheiro_lêr__linha_introduzir_charac(pilha.conteúdo[pilha.recúo - 1], linha_actual);
        }
    }

    fclose(ficheiro); // Fecha o ficheiro.

    return linhas;
}
