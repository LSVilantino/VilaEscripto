#ifndef _CABEÇALHO_LSVE_MAPA
#define _CABEÇALHO_LSVE_MAPA

#include "../mapa.h"
#include "tipo.h"

typedef struct LSVEMapa {
    struct Mapa;
    const char* separadôr;
} LSVEMapa;

char* lsve_valôr_tratar(ConteúdoTipo clave_tipo, void* clave, LSVEMapa* mapa);


#endif // !_CABEÇALHO_LSVE_MAPA
