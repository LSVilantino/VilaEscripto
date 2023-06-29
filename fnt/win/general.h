#ifndef _CABEÇALHO_GENERAL
#define _CABEÇALHO_GENERAL

#include <stdio.h>

#define LINHA char*

#define LINHA_NIL '\0'
#define LINHA_SALTA '\n'
#define ESPAÇO ' '
#define FICHEIRO_MODO_LEITURA "r"
#define FICHEIRO_MODO_LEITURA_BINÁRIA "rb"

typedef enum { falso, vero } Dico;

void* memória_allocar(size_t tamanho);
void* memória_re_allocar(size_t tamanho, void* p);

#endif // !_CABEÇALHO_GENERAL
