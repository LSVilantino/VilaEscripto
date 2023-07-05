#include "general.h"

#include <stdio.h>
#include <stdlib.h>

void 
grade_introduzir(Grade** grade, int índice, Tipo tipo, Dico precisa_libertar, void* elemento) {
    (*grade) = memória_re_allocar((índice + 2) * sizeof(Grade), (*grade));
    (*grade)[índice].índice = índice;
    (*grade)[índice].tipo = tipo;
    (*grade)[índice].precisa_libertar = precisa_libertar;
    (*grade)[índice].elemento = elemento;
    (*grade)[índice].filho = nil;

    (*grade)[índice + 1].índice = -1;
}

Dico 
grade_é_do_tipo(Tipo tipo, Grade grade) {
    if (grade.tipo == tipo) return vero;
    else return fal;
}

void
grade_des_allocar(Grade** grade) {
    int i = 0;
    while((*grade)[i].índice == i) {
        DESBRAGA_MENSAGEM("%d - %d\n", (*grade)[i].índice, i);

        if ((*grade)[i].precisa_libertar) { free((*grade)[i].elemento); }
        if ((*grade)[i].filho != nil) { grade_des_allocar((*grade)[i].filho); }

        i++;
    }

    if ((*grade) != nil) free((*grade));
}

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
