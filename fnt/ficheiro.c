#include "ficheiro.h"

#include "pilha.h"
#include "linha.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#define FICHEIRO_PRÓXIMO_CHARAC(ficheiro) (char) fgetc(ficheiro)

static int linha_n;
static int linha_actual_n;

void
ficheiro_lêr__linhas_introduzir_linha(LINHA linha, LINHA** linhas) {
    (*linhas) = memória_re_allocar((linha_n + 1) * sizeof(LINHA), (*linhas));
    (*linhas)[linha_n] = linha_duplicar(linha);
    (*linhas)[linha_n + 1] = LINHA_NIL;
    printf("%s", (*linhas)[linha_n]);

    linha_n++;
}

void
ficheiro_lêr__linha_introduzir_charac(char charac, LINHA* linha) {
    *linha = memória_re_allocar(linha_actual_n + 2, *linha);
    (*linha)[linha_actual_n] = charac;
    (*linha)[linha_actual_n + 1] = LINHA_NIL;
    //printf("%c", (*linha)[linha_actual_n]);
    linha_actual_n++;
}

LINHA*
ficheiro_lêr(LINHA caminho) {
    FILE* ficheiro;
    errno_t numErro = fopen_s(&ficheiro, caminho, FICHEIRO_MODO_LEITURA);
    if (numErro != 0) {
        printf("O ficheiro %s não foi encontrado, ou está ocupado.", caminho); abort();
    }

    Pilha pilha = pilha_construir(3);
    LINHA* linhas = memória_allocar(sizeof(LINHA));
    LINHA linha_actual = memória_allocar(1);

    linha_actual_n = 0;
    linha_n = 0;

    // recúo = tamanho da pilha, o quanto os charactéres recuam.
    // recúo - 1 = último charactére
    // recúo - 2 = ...

    for (int i = 0;; i++) {
        pilha_introduzir(FICHEIRO_PRÓXIMO_CHARAC(ficheiro));

        //printf("\n\n");
        //printf(pilha);
        //printf("\n\n");

        if (pilha_têr().conteúdo[pilha_têr().recúo - 1] == LINHA_SALTA) {
            // valida se o fim do ficheiro é seguido por um salta-linhas.
            if (pilha_têr().conteúdo[pilha_têr().recúo - 2] == EOF) {
                ficheiro_lêr__linhas_introduzir_linha(linha_actual, &linhas);

                break;
            }

            ficheiro_lêr__linha_introduzir_charac(pilha_têr().conteúdo[pilha_têr().recúo - 1], &linha_actual);
            ficheiro_lêr__linhas_introduzir_linha(linha_actual, &linhas);

            linha_actual_n = 0;
            continue;
        }

        if (pilha_têr().conteúdo[pilha_têr().recúo - 1] != LINHA_NIL) {
            ficheiro_lêr__linha_introduzir_charac(pilha_têr().conteúdo[pilha_têr().recúo - 1], &linha_actual);
        }
    }

    fclose(ficheiro); // Fecha o ficheiro.
    free(pilha.conteúdo);
    free(linha_actual);

    return linhas;
}
