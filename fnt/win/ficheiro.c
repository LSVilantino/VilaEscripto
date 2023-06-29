#include "ficheiro.h"

#include "pilha.h"
#include "linha.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#define FICHEIRO_PRÓXIMO_CHARAC(ficheiro) fgetc(ficheiro)

static int linha_n;
static int linha_actual_n;

LINHA*
ficheiro_lêr(LINHA caminho) {
    FILE* ficheiro;

	ficheiro = fopen(caminho, FICHEIRO_MODO_LEITURA);
    if (ficheiro == NULL) {
        printf("O ficheiro %s não foi encontrado, ou está ocupado.", caminho); abort();
    }

    Pilha pilha = pilha_construir(3);
    LINHA* linhas = memória_allocar(sizeof(LINHA));
    LINHA linha_actual = memória_allocar(4);

    linha_actual_n = 0;
    linha_n = 0;

    // recúo = tamanho da pilha, o quanto os charactéres recuam.
    // recúo - 1 = último charactére
    // recúo - 2 = ...

    for (int i = 0;; i++) {
        pilha_introduzir(FICHEIRO_PRÓXIMO_CHARAC(ficheiro), &pilha);

        //printf("\n\n");
        //printf(pilha);
        //printf("\n\n");

		// Valida se o fim do ficheiro é seguido por um salta-linhas.
		if (pilha.conteúdo[pilha.recúo - 1] == EOF) {
			// Introduz a linha à matriz e esquece a última linha-salta.
			linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, &linha_actual); linha_actual_n++;
			matriz_linha_introduzir_linha(linha_actual, linha_n, &linhas); linha_n++;

			break;
		}

		// Verifica se o último charactére da pilha é um linha-salta.
        if (pilha.conteúdo[pilha.recúo - 1] == LINHA_SALTA) {
            // Valida se o fim do ficheiro é seguido por um salta-linhas.
            if (pilha.conteúdo[pilha.recúo - 2] == EOF) {
				// Introduz a linha à matriz e esquece a última linha-salta.
				linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 2], linha_actual_n, &linha_actual); linha_actual_n++;
				matriz_linha_introduzir_linha(linha_actual, linha_n, &linhas); linha_n++;

                break;
            }

			// Introduz a linha-salta e sua linha à matriz.
			linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, &linha_actual); linha_actual_n++;
			matriz_linha_introduzir_linha(linha_actual, linha_n, &linhas); linha_n++;

            linha_actual_n = 0;
            continue;
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
