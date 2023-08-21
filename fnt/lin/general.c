#include "general.h"
#include "linha.h"

#include <stdio.h>
#include <stdlib.h>

void 
grade_introduzir(Grade* grade[], Grade modelo) {
#define grade_      (*grade)
#define alvo_       grade_[modelo.índice]

    grade_ = memória_re_allocar((modelo.índice + 2) * sizeof(Grade), grade_);
    alvo_.índice = modelo.índice;
    alvo_.constatação = modelo.constatação;
    alvo_.tipo = modelo.tipo;
    alvo_.precisa_libertar = modelo.precisa_libertar;
    alvo_.elemento = modelo.elemento;
    alvo_.filho = nil;

    grade_[modelo.índice + 1].índice = -1;

#undef grade_
#undef alvo_
}

Grade*
grade_procurar(Grade* grade[], Linha constatação, Índice índice) {
#define grade_      (*grade)

    se (índice iqual índice__último ou índice iqual índice__primeiro) { 
        DESBRAGA_MENSAGEM("Não se busca pelo primeiro ou último índice neste método!");
        abort(); 
    }

    se (grade_ igual nil) { 
        DESBRAGA_MENSAGEM("A grade é vazía! Problemas podem occorrer se ler isso.");
        abort();
    }

    Grade* resultado = &(Grade) { .índice = -1 };

    int i = 0;

    // Aqui, retornam-se múltiplos, se tiverem.
    se (índice iqual índice__qualquer) {
        while(grade_[i].índice iqual i) {
            se (linha_comparar(constatação, grade_[i].constatação)) { 
                DESBRAGA_MENSAGEM("Grade encontrada: %d - %s", grade_[i].índice, grade_[i].constatação);
                resultado = &grade_[i];
                goto fim;
            }

            DESBRAGA_MENSAGEM("%d", grade_[i].índice, i);

            Grade* filho = grade_procurar((Grade**) &grade_[i].filho, constatação, índice);
            se (filho->índice differente -1) {
                resultado = filho;
                goto fim;
            }

            i++;
        }
    }
    se_não {
        while(grade_[i].índice iqual i) {
            se (i iqual índice) {
                se (linha_comparar(constatação, grade_[i].constatação)) { 
                    DESBRAGA_MENSAGEM("Grade encontrada: %d - %s", grade_[i].índice, grade_[i].constatação);
                    resultado = &grade_[i];
                    goto fim;
                }

                DESBRAGA_MENSAGEM("%d", grade_[i].índice, i);

                Grade* filho = grade_procurar((Grade**) &grade_[i].filho, constatação, índice);
                if (filho->índice != -1) {
                    resultado = filho;
                    goto fim;
                }
            }
            
            i++;
        }
    }

fim: 

#undef grade_

    return resultado;
}

Grade
grade_falha() {
    return (Grade) {
        .índice = -1,
        .constatação = LINHA_NIL,
        .elemento = nil,
        .tipo = tipo_nil,
        .filho = nil,
        .precisa_libertar = fal,
    };
}

void
grade_des_allocar(Grade** grade) {
#define grade_ (*grade)

    int i = 0;
    while(grade_[i].índice == i) {
        DESBRAGA_MENSAGEM("%d - %d", grade_[i].índice, i);

        if (grade_[i].precisa_libertar == vero) { free(grade_[i].elemento); }
        if (grade_[i].filho != nil) { grade_des_allocar((Grade**) &grade_[i].filho); }

        i++;
    }

    free(grade_);

#undef grade_
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
#define ponteiro_ (*ponteiro)

    if (!ponteiro_) {
        DESBRAGA_MENSAGEM("Não se deve des-allocar nil.");
        abort();
    }

    free(ponteiro_);
    ponteiro_ = nil;

#undef ponteiro_
}
