#include "pilha.h"
#include "linha.h"
#include "general.h"

#include <string.h>

static Pilha pilha;

Pilha pilha_construir(size_t tamanho) {
    pilha.recúo = tamanho;
    pilha.tamanho_actual = 0;
    pilha.conteúdo = memória_allocar(tamanho++);

    return pilha;
}

Pilha pilha_introduzir(char charac) {
    char* cópia = linha_duplicar(pilha.conteúdo);

    pilha.conteúdo[0] = charac;
    cópia[pilha.tamanho_actual] = LINHA_NIL;
    if (pilha.tamanho_actual != pilha.recúo) pilha.tamanho_actual++;
    pilha.conteúdo[pilha.tamanho_actual] = LINHA_NIL;
    pilha.conteúdo[pilha.recúo - 1] = LINHA_NIL;

    for (int i = pilha.tamanho_actual - 1; i > 0; i--) pilha.conteúdo[i] = cópia[i - 1];

    free(cópia);
    return pilha;
}
