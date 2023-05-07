#include "mapa.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Mapa* 
mapa_construir() {
    Mapa* mapa = malloc(sizeof(Mapa*));

    mapa[0].passe = NULL;
    mapa[0].valôr = NULL;
    mapa[0].i = 1;

    //printf("%s %s %d\n", (char*)mapa[0].passe, (char*)mapa[0].valôr, mapa[0].i);
    return mapa;
}

void 
mapa_introduzir(Mapa* mapa[], Mapa valôr) {
    Mapa* mappa = (*mapa);

    int i = 0;
    while (mappa[i].i == i) { i = i + 1; }
    if (valôr.i != i) valôr.i = i;

    mappa[i] = valôr;
    //mappa = realloc(mappa, i + 1 * (sizeof(*mappa) * sizeof(valôr))); // n + 1 é necessário pela 'regra do múltiplo a índice 0'.
}

Mapa* 
mapa_procurar(Tipo tipo, void* procura, Mapa* mapa) {
    int i = 0;

    switch (tipo)
    {
    case tipo_char:
        while (mapa[i].i == i) {
            if (strcmp((char*)mapa[i].passe, (char*)procura) == 0) {
                return &mapa[i];
            }

            i = i + 1;
        }
        break;
    default:
        break;
    }

    return NULL;
}