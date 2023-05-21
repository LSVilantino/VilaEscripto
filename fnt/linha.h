#ifndef _CABEÇALHO_LINHA
#define _CABEÇALHO_LINHA

#include "general.h"
#include "mapa.h"

int linha_charactéres_contar(char* linha);
int linha_separadôr_contar(char* separador, char* linha);

bool linha_contém(char* comparador, char* linha);
bool linha_compara(char* comparadôr, char* linha);

char* linha_complementar(char* complemento, char* linha);

char** linha_separar(char* separador, char* linha);
char* linha_aparar(char* linha);
char* linha_cortar(int de, int até, char*);

char* linha_repôr(char* reposição, char* alvo, char* linha);

Mapa* linha_matriz_mapear(char** linhas);

#endif // _CABEÇALHO_LINHA