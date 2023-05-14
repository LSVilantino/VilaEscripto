#ifndef _CABEÇALHO_LSVE
#define _CABEÇALHO_LSVE

#include "mapa.h"

char** lsve_linha_separar(char* separadôr, char* linha);
char** lsve_ficha_tratar(char** linhas);
char* lsve_ficheiro_linha_tratar(char* linha);
char** lsve_mapa_a_matriz_char(char* separador, Mapa* linhas);
Mapa* lsve_ficheiro_conteúdo_mapear(char* ficheiroCaminho);
#endif // _CABEÇALHO_LSVE