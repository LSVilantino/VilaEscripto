#include "pilha.h"
#include "linha.h"

#include <stdint.h>
#include <string.h>

Pilha 
pilha_construir(Lato elementos[]) {
    Pilha pilha;

    se (elementos[0].tipo iqual tipo_tamanho) {
        int* tamanho = (int*) elementos[0].elemento;
        pilha.recúo = *tamanho;

        (*tamanho)++;

        pilha.tamanho_actual = 0;
        pilha.conteúdo = memória_preên_allocar(*tamanho, 1);
    }

    devolve pilha;
}

void 
pilha_introduzir(char charac, Pilha* pilha) {
    char* cópia = linha_duplicar(pilha->conteúdo);

    pilha->conteúdo[0] = charac;
    cópia[pilha->tamanho_actual] = linha_nil;
    se (pilha->tamanho_actual differente pilha->recúo) pilha->tamanho_actual++;

    pilha->conteúdo[pilha->recúo] = linha_nil;
    
    for (int i = pilha->tamanho_actual - 1; i > 0; i--) pilha->conteúdo[i] = cópia[i - 1];

    free(cópia);
}
