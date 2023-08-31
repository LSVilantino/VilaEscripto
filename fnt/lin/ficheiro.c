#include "ficheiro.h"

#include "general.h"

#include "linha.h"
#include "pilha.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

Grade*
ficheiro_lêr(Linha caminho) {
    FILE* ficheiro;

	ficheiro = fopen(caminho, ficheiro_modo_leitura);
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
        &(Grade) {
        .índice = linha_n,
        .constatação = linha_nil,
        .tipo = tipo_linha,
        .elemento = memória_allocar(1),
        .elemento_precisa_libertar = vero,

        .filho_precisa_libertar = fal,
        .filho = nil
        }
    );

    // recúo = tamanho da pilha, o quanto os charactéres recuam.
    // recúo - 1 = último charactére
    // recúo - 2 = ...

    while (1) {
        char charactére = fgetc(ficheiro);
        pilha_introduzir(charactére, &pilha);

        //DESBRAGA_MENSAGEM("%c - %s\n", charactére, pilha.conteúdo);

        if (pilha.conteúdo[pilha.recúo - 1] iqual ficheiro_fim) {
            linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, (Linha*) &linhas[linha_n].elemento); 
            linha_actual_n = 0; 

            break;
        }

        if (pilha.conteúdo[pilha.recúo - 1] iqual linha_salta) {
            if (pilha.conteúdo[pilha.recúo - 2] iqual ficheiro_fim) {
				linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 2], linha_actual_n, (Linha*) &linhas[linha_n].elemento);
                linha_actual_n = 0;

                break;
            }

			linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, (Linha*) &linhas[linha_n].elemento);
            linha_actual_n = 0;
			linha_n++;
            grade_introduzir(&linhas, 
                &(Grade) {
                .índice = linha_n,
                .constatação = linha_nil,
                .tipo = tipo_linha,
                .elemento = nil,
                .elemento_precisa_libertar = vero,

                .filho = nil,
                .filho_precisa_libertar = fal,
                }
            );

            continue;
        }

        if (pilha.conteúdo[pilha.recúo - 1] differente linha_nil) {
			linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, (Linha*) &linhas[linha_n].elemento); 
            linha_actual_n++;
        }
    }

    fclose(ficheiro);
    memória_des_allocar(&pilha.conteúdo);

    return linhas;
}