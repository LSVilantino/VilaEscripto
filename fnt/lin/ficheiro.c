#include "ficheiro.h"

#include "pilha.h"
#include "linha.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#define FICHEIRO_PRÓXIMO_CHARAC(ficheiro) fgetc(ficheiro)

LINHA*
ficheiro_lêr(LINHA caminho) {
    FILE* ficheiro;

	ficheiro = fopen(caminho, FICHEIRO_MODO_LEITURA);
    if (!ficheiro) {
        printf("O ficheiro %s não foi encontrado, ou está ocupado.", caminho); abort();
    }

    Pilha pilha = pilha_construir(3);
    LINHA* linhas = memória_preên_allocar(1, sizeof(LINHA));
    LINHA linha_actual = memória_preên_allocar(1, 1);
    linha_actual[0] = LINHA_NIL;

    int linha_actual_n = 0;
    int linha_n = 0;

    // recúo = tamanho da pilha, o quanto os charactéres recuam.
    // recúo - 1 = último charactére
    // recúo - 2 = ...

    
    while (1) {
        char charactére = FICHEIRO_PRÓXIMO_CHARAC(ficheiro);
        pilha_introduzir(charactére, &pilha);

        printf("%c - %s\n", charactére, pilha.conteúdo);

        // Valida se o fim do ficheiro é seguido por um salta-linhas.
        if (pilha.conteúdo[pilha.recúo - 1] == EOF) {
            // Introduz a linha à matriz e esquece a última linha-salta.
            linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, &linha_actual); linha_actual_n++;
            matriz_linha_introduzir_linha(linha_actual, linha_n, &linhas); linha_n++;

            break;
        }

        // Introduz último charactére da pilha à linha actual.
        if (pilha.conteúdo[pilha.recúo - 1] != LINHA_NIL) {
			linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, &linha_actual); linha_actual_n++;
        }
    }

	// Fecha o ficheiro e libera variáveis.
    fclose(ficheiro);
    free(pilha.conteúdo);
    free(linha_actual);

    return linhas;
}
