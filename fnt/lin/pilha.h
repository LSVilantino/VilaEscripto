#ifndef _CABEÇALHO_PILHA
#define _CABEÇALHO_PILHA

#include "general.h"

#include <stdlib.h>

typedef struct Pilha {
    Linha conteúdo;
    int recúo;
    int tamanho_actual;
} Pilha;

/*
recebe
    1 - size_t
*/
Pilha pilha_construir(Lato* elementos);
void pilha_introduzir(char charac, Pilha* pilha);

#endif // !_CABEÇALHO_PILHA
