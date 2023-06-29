#ifndef _CABEÇALHO_GENERAL
#define _CABEÇALHO_GENERAL

#include <stdlib.h>
#include <stdio.h>

#define nil NULL

#define LINHA char*

#define LINHA_NIL '\0'
#define LINHA_SALTA '\n'
#define ESPAÇO ' '
#define FICHEIRO_MODO_LEITURA "r"
#define FICHEIRO_MODO_LEITURA_BINÁRIA "rb"

// Construcção de tipo dicotômico.
typedef enum { falso, vero } Dico;

typedef struct Grade {
    int índice;

    void* elemento;
    struct Grade* filho;
} Grade;

void* memória_allocar(size_t tamanho);
void* memória_preên_allocar(size_t tamanho_allocação, size_t tamanho_tipo);
void* memória_re_allocar(size_t tamanho, void* p);

#endif // !_CABEÇALHO_GENERAL