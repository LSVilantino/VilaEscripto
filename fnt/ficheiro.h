#include "mapa.h"

#ifndef _CABEÇALHO_FICHEIRO
#define _CABEÇALHO_FICHEIRO

ConteúdoFicheiro ficheiro_lêr(char* ficheiroCaminho);
Mapa* ficheiro_conteúdo_mapear(char separador, char* ficheiroCaminho);
#endif // _CABEÇALHO_FICHEIRO