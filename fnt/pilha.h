#ifndef _CABEÇALHO_PILHA
#define _CABEÇALHO_PILHA

#include <stdlib.h>

typedef struct Pilha {
    char* conteúdo;
    int recúo;
    int tamanho_actual;
} Pilha;

Pilha pilha_construir(size_t tamanho);
Pilha pilha_introduzir(char charac);

#endif // !_CABEÇALHO_PILHA
