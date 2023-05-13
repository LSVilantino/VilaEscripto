#ifndef _CABEÇALHO_MAPA

#include "tipo.h"

#define _CABEÇALHO_MAPA

typedef struct Mapa {
    void* passe;
    void* valôr;
    int i; //Índex
} Mapa;

Mapa* mapa_construir();
void mapa_introduzir(Mapa* mapa[], Mapa valôr);
Mapa* mapa_procurar(Tipo tipo, void* procura, Mapa* mapa);

#endif // _CABEÇALHO_MAPA