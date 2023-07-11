#include "general.h"

#include <stdio.h>
#include <stdlib.h>

void 
grade_introduzir(Grade** grade, int índice, Tipo tipo, Dico precisa_libertar, void* elemento) {
#define _grade (*grade)

    _grade = memória_re_allocar((índice + 2) * sizeof(Grade), _grade);
    _grade[índice].índice = índice;
    _grade[índice].tipo = tipo;
    _grade[índice].precisa_libertar = precisa_libertar;
    _grade[índice].elemento = elemento;
    _grade[índice].filho = nil;

    _grade[índice + 1].índice = -1;

#undef _grade
}

void
grade_des_allocar(Grade** grade) {
#define _grade (*grade)

    int i = 0;
    while(_grade[i].índice == i) {
        DESBRAGA_MENSAGEM("%d - %d\n", _grade[i].índice, i);

        if (_grade[i].precisa_libertar == vero) { free(_grade[i].elemento); }
        if (_grade[i].filho != nil) { grade_des_allocar(&_grade[i].filho); }

        i++;
    }

    free(_grade);

#undef _grade
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
