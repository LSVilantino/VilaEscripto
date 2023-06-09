#ifndef _CABEÇALHO_LINHA
#define _CABEÇALHO_LINHA

#include "general.h"

/*
* Conta os charactéres de uma linha.
*/
int linha_contar(char* linha);
/*
* Introduz um novo charactére numa linha allocada.
*
* Foi criada inicialmente para facilitar a introducção em ciclos
* e evitar repetição.
* 
*/
void linha_introduzir_charactére(char charactére, int posição, char** linha);
/*
* Introduz uma linha numa matriz allocada.
*
* Foi criada inicialmente para facilitar a introducção em ciclos
* e evitar repetição.
*/
void matriz_linha_introduzir_linha(char* linha, int posição, char*** matriz);
/*
* Duplica a linha dada.
*/
char* linha_duplicar(char* linha);
/*
* Comparar duas linhas.
*/
Dico linha_comparar(char* comparadôr, const char* linha);

#endif // !_CABEÇALHO_LINHA
