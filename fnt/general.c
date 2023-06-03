#include "general.h"

#include <stdio.h>
#include  <stdlib.h>

void*
memória_allocar(size_t tamanho) {
    void* ponteiro = malloc(tamanho);
    if (ponteiro == NULL) {
        printf("Não se pôde alocar %zu digbis.\n", tamanho);
        abort();
    }

    return ponteiro;
}

void*
memória_re_allocar(size_t tamanho, void* p) {
    void* ponteiro = realloc(p, tamanho);
    if (ponteiro == NULL) {
        printf("Não se pôde re-alocar %zu digbis.\n", tamanho);
        abort();
    }

    return ponteiro;
}
