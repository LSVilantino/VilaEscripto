#include "ficheiro.h"

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
        (Lato){tipo_tamanho, &(int){3}}
    });

    int linha_actual_n = 0;
    int linha_n = 0;

    Grade* resultado = memória_allocar(sizeof(Grade));
    resultado[linha_n].índice = linha_n;
    resultado[linha_n].elemento = memória_preên_allocar(1, 1);
    ((Linha) resultado[linha_n].elemento)[0] = LINHA_NIL;
    resultado[linha_n].tipo = tipo_linha;

    // recúo = tamanho da pilha, o quanto os charactéres recuam.
    // recúo - 1 = último charactére
    // recúo - 2 = ...

    while (1) {
        char charactére = FICHEIRO_PRÓXIMO_CHARAC(ficheiro);
        pilha_introduzir(charactére, &pilha);

        printf("%c - %s\n", charactére, pilha.conteúdo);

        // Valida se o fim do ficheiro é seguido por um salta-linhas.
        if (pilha.conteúdo[pilha.recúo - 1] == EOF) {
            resultado = memória_re_allocar(linha_n + 1 * sizeof(Grade), resultado);
            resultado[linha_n].índice = linha_n + 1;
            resultado[linha_n].tipo = tipo_linha;

            // Introduz a linha à matriz e esquece a última linha-salta.
            linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, (Linha*) (&resultado[linha_n].elemento)); linha_actual_n++;

            break;
        }

        // Introduz último charactére da pilha à linha actual.
        if (pilha.conteúdo[pilha.recúo - 1] != LINHA_NIL) {
			linha_introduzir_charactére(pilha.conteúdo[pilha.recúo - 1], linha_actual_n, (Linha*) (&resultado[linha_n].elemento)); linha_actual_n++;
        }
    }

	// Fecha o ficheiro e libera variáveis.
    fclose(ficheiro);
    free(pilha.conteúdo);

    return resultado;
}
