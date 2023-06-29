#include "general.h"

#include <stdio.h>
#include <stdlib.h>

void*
memória_allocar(size_t tamanho) {
    void* ponteiro = malloc(tamanho);
    if (!ponteiro) {
        printf("Não se pôde alocar %zu digbis.\n", tamanho);
        abort();
    }

    return ponteiro;
}

void*
memória_preên_allocar(size_t tamanho_allocação, size_t tamanho_tipo) {
    void* ponteiro = calloc(tamanho_allocação, tamanho_tipo);
    if (!ponteiro) {
        printf("Não se pôde preêncher com allocação %zu digbis.\n", (tamanho_allocação * tamanho_tipo));
        abort();
    }

    return ponteiro;
}

void*
memória_re_allocar(size_t tamanho, void* p) {
    void* ponteiro = realloc(p, tamanho);
    if (!ponteiro) {
        printf("Não se pôde re-alocar %zu digbis.\n", tamanho);
        abort();
    }

    return ponteiro;
}
