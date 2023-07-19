#include "ficheiro.h"

#include "general.h"

#include "linha.h"
#include "pilha.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#define FICHEIRO_PRÓXIMO_CHARAC(ficheiro) fgetc(ficheiro)

Grade*
ficheiro_lêr(Linha caminho) {
    FILE* ficheiro;

	ficheiro = fopen(caminho, FICHEIRO_MODO_LEITURA);
    if (!ficheiro) {
        printf("O ficheiro %s não foi encontrado, ou está ocupado.", caminho); abort();
    }

    Pilha pilha = pilha_construir((Lato[])
    {
        (Lato){tipo_tamanho, fal, &(int){3}}
    });

    int 
    linha_actual_n = 0, 
    linha_n = 0
    ;

    Grade* linhas = nil;
    grade_introduzir(&linhas, 
        (Grade) {
        .índice = linha_n,
        .constatação = "linha",
        .tipo = tipo_linha,
        .precisa_libertar = vero,
        .elemento = nil,
        }
    );

    // recúo = tamanho da pilha, o quanto os charactéres recuam.
    // recúo - 1 = último charactére
    // recúo - 2 = ...

    while (1) {
        char charactére = FICHEIRO_PRÓXIMO_CHARAC(ficheiro);
        pilha_introduzir(charactére, &pilha);

        //DESBRAGA_MENSAGEM("%c - %s\n", charactére, pilha.conteúdo);

        // Valida se o fim do ficheiro é seguido por um salta-linhas.
        if (pilha.conteúdo[pilha.recúo - 1] == EOF) {
            // Introduz a linha à matriz e esquece a última linha-salta.
            linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, (Linha*) &linhas[linha_n].elemento); 
            linha_actual_n = 0; 

            break;
        }

		// Verifica se o último charactére da pilha é um linha-salta.
        if (pilha.conteúdo[pilha.recúo - 1] == LINHA_SALTA) {
            // Valida se o fim do ficheiro é seguido por um salta-linhas.
            if (pilha.conteúdo[pilha.recúo - 2] == EOF) {
				// Introduz a linha à matriz e esquece a última linha-salta.
				linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 2], linha_actual_n, (Linha*) &linhas[linha_n].elemento);
                linha_actual_n = 0;

                break;
            }

			// Introduz a linha-salta e sua linha à matriz.
			linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, (Linha*) &linhas[linha_n].elemento);
            linha_actual_n = 0;
			linha_n++;
            grade_introduzir(&linhas, 
                (Grade) {
                .índice = linha_n,
                .constatação = "linha",
                .tipo = tipo_linha,
                .precisa_libertar = vero,
                .elemento = nil,
                }
            );

            continue;
        }

		// Introduz último charactére da pilha à linha actual.
        if (pilha.conteúdo[pilha.recúo - 1] != LINHA_NIL) {
			linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, (Linha*) &linhas[linha_n].elemento); 
            linha_actual_n++;
        }
    }

	// Fecha o ficheiro e libera variáveis.
    fclose(ficheiro);
    memória_des_allocar(&pilha.conteúdo);

    return linhas;
}
