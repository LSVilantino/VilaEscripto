#ifndef _CABEÇALHO_LINHA
#define _CABEÇALHO_LINHA

#include "general.h"
#include "mapa.h"

int linha_charactéres_contar(char* linha);
int linha_separador_contar(char separador, char* linha);
bool linha_contém(char* comparador, char* linha);
char* linha_separador_procurar(char* linha);
char** linha_separar(char* separador, char* linha);
char* linha_aparar(char* linha);

Mapa* linha_matriz_mapear(char** linhas);

#endif // _CABEÇALHO_LINHA