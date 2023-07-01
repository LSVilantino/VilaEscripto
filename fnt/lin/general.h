#ifndef _CABEÇALHO_GENERAL
#define _CABEÇALHO_GENERAL

#include <stdlib.h>
#include <stdio.h>

#define nil NULL

// 'linha' (repare o i minúsculo) muitas das vezes é nome de variáveis
#define Linha char*

#define LINHA_NIL '\0'
#define LINHA_SALTA '\n'
#define ESPAÇO ' '
#define FICHEIRO_MODO_LEITURA "r"
#define FICHEIRO_MODO_LEITURA_BINÁRIA "rb"

typedef void* Objecto;

// Construcção de tipo dicotômico.
typedef enum { falso, vero } Dico;

typedef enum {
    tipo_charactére, // char
    tipo_linha, // char* / Linha
    tipo_inteiro, // int
    tipo_tamanho, // size_t
} Tipo;

//-------------------------
// DEFINIÇÕES DE ELEMENTOS
//-------------------------

/*
    definem-se os elementos em macros, para que possam
    ser re-utilizados em estructuras.

    GCC não suporta declaração de estruturas anônimas
    como MS CL suporta. Então, declarações assim, não fucionam:

    struct A {
        int elemento1;
    }

    struct B {
        struct A; 
        (implicitamente, importa-se 'elemento1')
        int elemento2;
    }

    Com o uso dos macros, é possível re-definir os campos sem
    que se tornem muito irreparáveis à larga escala, ou
    simplesmente para que não se tenha os efeitos de têr que
    replicar os mesmos campos em todos os lugares necessários.
*/
#define elems_lato {        \
    Tipo tipo;              \
    Objecto elemento;       \
}                           \

typedef struct Lato elems_lato Lato;

typedef struct Grade {
    int índice;

    struct elems_lato;
    struct Grade* filho;
} Grade;

void des_allocar_grade(Grade* grade);

void* memória_allocar(size_t tamanho);
void* memória_preên_allocar(size_t tamanho_allocação, size_t tamanho_tipo);
void* memória_re_allocar(size_t tamanho, void* p);

#endif // !_CABEÇALHO_GENERAL