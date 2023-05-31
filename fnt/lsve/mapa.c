#include "mapa.h"
#include "general.h"
#include "ficheiro.h"

#include <string.h>

char* lsve_valôr_tratar(ConteúdoTipo clave_tipo, void* clave, LSVEMapa* mapa) {
    LSVEMapa mapa_ = *mapa;

    ficheiro_lêr(mapa_.valôr);
    
    return strdup(mapa_.valôr);
}
