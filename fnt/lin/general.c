#include "general.h"
#include "linha.h"

#include <stdio.h>
#include <stdlib.h>

void 
grade_introduzir(Grade* ref grade, Grade ref modelo) {
#define modelo_     (*modelo)
#define grade_      (*grade)
#define alvo_       grade_[modelo_.índice]

    int multiplicador = modelo_.índice;
    se (multiplicador iqual inválido) multiplicador = 0;

    grade_ = memória_re_allocar((multiplicador + 2) * sizeof(Grade), grade_);
    alvo_.índice = modelo_.índice;
    alvo_.constatação = modelo_.constatação;
    alvo_.tipo = modelo_.tipo;
    alvo_.elemento_precisa_libertar = modelo_.elemento_precisa_libertar;
    alvo_.elemento = modelo_.elemento;
    alvo_.filho_precisa_libertar = modelo_.filho_precisa_libertar;
    alvo_.filho = nil;

    grade_[modelo_.índice + 1] = grade_falha(nil);

#undef modelo_
#undef grade_
#undef alvo_
}

Grade*
grade_procurar(Grade* grade, Linha constatação, Índice índice) {
    se (índice iqual índice__último ou índice iqual índice__primeiro) { 
        DESBRAGA_TÓPICO("Não se busca pelo primeiro ou último índice neste método!");
        abort(); 
    }

    se (grade iqual nil ou grade->índice menor 0) { 
        DESBRAGA_TÓPICO("A grade é vazía! Problemas podem occorrer se ler isso.");
        abort();
    }

    Grade* resultado = memória_allocar(sizeof(Grade));
    resultado[0] = (Grade) { .índice = inválido };

    int i = 0;
    int i_grade = grade[i].índice;

    se (índice iqual índice__qualquer) {
        DESBRAGA_MENSAGEM("Índice: %d | %d", grade[i].índice, i_grade);
        
        enquanto (grade[i].índice iqual i_grade) {
            DESBRAGA_MENSAGEM("Grade: %d - %s", grade[i].índice, grade[i].constatação);

            se (linha_comparar(constatação, grade[i].constatação) iqual vero) { 
                DESBRAGA_MENSAGEM("Grade encontrada: %d - %s", grade[i].índice, grade[i].constatação);
                resultado = &grade[i];
                goto fim;
            }

            se (grade[i].filho differente nil) {
                Grade* filho = grade_procurar(grade[i].filho, constatação, índice);
                se (filho->índice differente inválido) {
                    DESBRAGA_MENSAGEM("Grade encontrada: %d - %s", grade[i].índice, grade[i].constatação);
                    resultado = filho;
                    goto fim;
                } se_não {
                    DESBRAGA_MENSAGEM("Grade inválida: %d - %s", grade[i].índice, grade[i].constatação);
                }
            }

            i_grade = ++i;
        }
    }
    se_não {
        DESBRAGA_MENSAGEM("Grade: %d / %d - %s", i, grade[i].índice, grade[i].constatação);

        enquanto (grade[i].índice iqual i_grade) {
            DESBRAGA_MENSAGEM("Grade: %d - %s", grade[i].índice, grade[i].constatação);

            se (i iqual índice) {
                se (linha_comparar(constatação, grade[i].constatação) iqual vero) { 
                    DESBRAGA_MENSAGEM("Grade encontrada: %d - %s", grade[i].índice, grade[i].constatação);
                    resultado = &grade[i];
                    goto fim;
                }

                se (grade[i].filho differente nil) {
                    Grade* filho = grade_procurar(grade[i].filho, constatação, índice);
                    se (filho->índice differente inválido) {
                        DESBRAGA_MENSAGEM("Grade encontrada: %d - %s", grade[i].índice, grade[i].constatação);
                        resultado = filho;
                        goto fim;
                    } se_não {
                        DESBRAGA_MENSAGEM("Grade inválida: %d - %s", grade[i].índice, grade[i].constatação);
                    }
                }
            }
            
            i_grade = ++i;
        }
    }

fim: 
    return resultado;
}

Grade
grade_falha(Linha constatação) {
    se (constatação iqual nil) constatação = linha_nil;

    Grade gradeFalha = (Grade) {
        .índice = inválido,
        .constatação = constatação,
        .elemento = nil,
        .elemento_precisa_libertar = fal,
        .tipo = tipo_nil,
        .filho = nil,
        .filho_precisa_libertar = fal,
    };

    devolve gradeFalha;
}

void
grade_des_allocar(Grade* ref grade) {
#define grade_ (*grade)

    int i = 0;
    Dico pai_liberar = fal;
    enquanto (grade_[i].índice iqual i ou grade_[i].índice iqual inválido) {
        DESBRAGA_MENSAGEM("%d - %d", grade_[i].índice, i);

        se (grade_[i].elemento_precisa_libertar iqual vero) { 
            se (grade_[i].elemento differente de nil) {
                memória_des_allocar(&grade_[i].elemento); 
            }
        }

        se (grade_[i].filho_precisa_libertar iqual vero) {
            se (grade_[i].filho differente nil) { grade_des_allocar(&grade_[i].filho); }
        }

        i++;
    }

    se (pai_liberar) memória_des_allocar(&grade_);

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
memória_des_allocar(void* ref ponteiro) {
#define ponteiro_ (*ponteiro)

    if (!ponteiro_) {
        DESBRAGA_MENSAGEM("Não se deve des-allocar nil.");
        abort();
    }

    free(ponteiro_);
    ponteiro_ = nil;

#undef ponteiro_
}
