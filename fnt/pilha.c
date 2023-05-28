#include "pilha.h"
#include "linha.h"
#include "general.h"

#include <string.h>

static char* pilha;
static int recúo_quantidade;

char* pilha_construir(int tamanho) {
    recúo_quantidade = tamanho++;
    pilha = memória_allocar(tamanho);

    return pilha;
}

char* pilha_introduzir(char charac) {
    pilha[0] = charac;

    char* cópia = linha_duplicar(pilha);
    pilha[recúo_quantidade - 1] = '\0';

    for (int i = recúo_quantidade; i > 0; i--) pilha[i] = cópia[i - 1];

    return pilha;
}
