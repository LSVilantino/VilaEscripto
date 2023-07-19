#include "general.h"
#include "linha.h"

#include <stdio.h>
#include <stdlib.h>

void 
grade_introduzir(Grade** grade, Grade modelo) {
#define grade__1 (*grade)
#define alvo__1 grade__1[modelo.índice]

    grade__1 = memória_re_allocar((modelo.índice + 2) * sizeof(Grade), grade__1);
    alvo__1.índice = modelo.índice;
    alvo__1.constatação = modelo.constatação;
    alvo__1.tipo = modelo.tipo;
    alvo__1.precisa_libertar = modelo.precisa_libertar;
    alvo__1.elemento = modelo.elemento;
    alvo__1.filho = nil;

    grade__1[modelo.índice + 1].índice = -1;

#undef grade__1
#undef alvo__1
}

Grade*
grade_procurar(Linha constatação, Grade** grade) {
#ifndef grade_procurar__1

#define grade_procurar__1
#define grade__1 (*grade)

#endif // #ifndef grade_des_allocar

    if(grade__1 != nil) {
        int i = 0;
        
        while(grade__1[i].índice == i) {
            if(linha_comparar(constatação, grade__1[i].constatação)) { 
                DESBRAGA_MENSAGEM("Grade encontrada: %d - %s", grade__1[i].índice, grade__1[i].constatação);
                return &grade__1[i];
            }

            DESBRAGA_MENSAGEM("%d", grade__1[i].índice, i);

            Grade* resultado = grade_procurar(constatação, (Grade**) &grade__1[i].filho);
            if (resultado->índice != -1) {
                return resultado;
            }

            i++;
        }
    }

#undef grade_procurar__1
#undef grade__1

    return &(Grade) { .índice = -1 };
}

void
grade_des_allocar(Grade** grade) {
#ifndef grade_des_allocar__1

#define grade_des_allocar__1
#define grade__1 (*grade)

#endif // #ifndef grade_des_allocar

    int i = 0;
    while(grade__1[i].índice == i) {
        DESBRAGA_MENSAGEM("%d - %d", grade__1[i].índice, i);

        if (grade__1[i].precisa_libertar == vero) { free(grade__1[i].elemento); }
        if (grade__1[i].filho != nil) { grade_des_allocar((Grade**) &grade__1[i].filho); }

        i++;
    }

    free(grade__1);

#undef grade_des_allocar__1
#undef grade__1
}

void*
memória_allocar(size_t tamanho) {
    void* ponteiro = malloc(tamanho);
    if (!ponteiro) {
        DESBRAGA_MENSAGEM("Não se pôde alocar %zu digbis.\n", tamanho);
        abort();
    }

    return ponteiro;
}

void*
memória_preên_allocar(size_t tamanho_allocação, size_t tamanho_tipo) {
    void* ponteiro = calloc(tamanho_allocação, tamanho_tipo);
    if (!ponteiro) {
        DESBRAGA_MENSAGEM("Não se pôde preêncher com allocação %zu digbis.\n", (tamanho_allocação * tamanho_tipo));
        abort();
    }

    return ponteiro;
}

void*
memória_re_allocar(size_t tamanho, void* p) {
    void* ponteiro = realloc(p, tamanho);
    if (!ponteiro) {
        DESBRAGA_MENSAGEM("Não se pôde re-alocar %zu digbis.\n", tamanho);
        abort();
    }

    return ponteiro;
}

void
memória_des_allocar(void** ponteiro) {
#define ponteiro__1 (*ponteiro)

    if (!ponteiro__1) {
        DESBRAGA_MENSAGEM("Não se deve des-allocar nil.");
        abort();
    }

    free(ponteiro__1);
    ponteiro__1 = nil;

#undef ponteiro__1
}
