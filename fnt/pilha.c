#include "pilha.h"
#include "linha.h"
#include "general.h"

#include <string.h>
#include <stdlib.h>

static char* charactéres_pilha;
static int recúo_quantidade;

char* pilha_construir(int tamanho) {
    recúo_quantidade = tamanho;
    charactéres_pilha = memória_allocar(tamanho++);
    charactéres_pilha[0] = LINHA_NIL;

    return charactéres_pilha;
}

char* pilha_introduzir(char charac) {
    char* cópia = linha_duplicar(charactéres_pilha);

    charactéres_pilha[0] = charac;
    charactéres_pilha[recúo_quantidade] = LINHA_NIL;

    for (int i = recúo_quantidade - 1; i > 0; i--) {
        charactéres_pilha[i] = cópia[i - 1];
    }

    free(cópia);
    return charactéres_pilha;
}
