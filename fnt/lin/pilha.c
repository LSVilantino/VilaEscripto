#include "pilha.h"
#include "linha.h"

#include <stdint.h>
#include <string.h>

Pilha pilha_construir(Lato elementos[]) {
    Pilha pilha;

    if (elementos[0].tipo == tipo_tamanho) {
        int* tamanho = (int*) elementos[0].elemento;
        pilha.recúo = *tamanho;

        (*tamanho)++;

        pilha.tamanho_actual = 0;
        pilha.conteúdo = memória_preên_allocar(*tamanho, 1);
    }

    return pilha;
}

void pilha_introduzir(char charac, Pilha* pilha) {
    char* cópia = linha_duplicar(pilha->conteúdo);

    pilha->conteúdo[0] = charac;
    cópia[pilha->tamanho_actual] = LINHA_NIL;
    if (pilha->tamanho_actual != pilha->recúo) pilha->tamanho_actual++;

    pilha->conteúdo[pilha->recúo] = LINHA_NIL;
    
    for (int i = pilha->tamanho_actual - 1; i > 0; i--) pilha->conteúdo[i] = cópia[i - 1];

    free(cópia);
}
