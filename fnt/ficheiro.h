#ifndef _CABEÇALHO_FICHEIRO

#include "mapa.h"

#define _CABEÇALHO_FICHEIRO

ConteúdoFicheiro ficheiro_lêr(char* ficheiroCaminho);
char* ficheiro_linha_tratar(char* linha);
Mapa* ficheiro_conteúdo_mapear(char* ficheiroCaminho);
#endif // _CABEÇALHO_FICHEIRO