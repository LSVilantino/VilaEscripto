#ifndef _CABEÇALHO_LINHA
#define _CABEÇALHO_LINHA

#include "general.h"

/*
	Arranca todos os charactéres da linha.
*/
void linha_arrancar(size_t tamanho, LINHA linha);

/*
	Conta os charactéres de uma linha.
*/
int linha_contar(const LINHA linha);
/*
	Introduz um novo charactére numa linha allocada.
	
	Foi criada inicialmente para facilitar a introducção em ciclos
	e evitar repetição.
	
*/
void linha_introduzir_charactére(char charactére, int posição, LINHA* linha);
/*
	Introduz uma linha à outra.
*/
void linha_agregar_linha(LINHA linhaIntroduzida, int* posição, LINHA* linha);
/*
	Introduz uma linha numa matriz allocada.
	
	Foi criada inicialmente para facilitar a introducção em ciclos
	e evitar repetição.
*/
void matriz_linha_introduzir_linha(LINHA linha, int posição, LINHA** matriz);
/*
	Duplica a linha dada.
*/
LINHA linha_duplicar(LINHA linha);

/*
	Valida se uma linha está contida em outra.
*/
Dico linha_contém(LINHA comparadôr, const LINHA linha);
/*
	Comparar o conteúdo de duas linhas.
*/
Dico linha_comparar(LINHA comparadôr, const LINHA linha);

/*
Remove espaços do início e fim da linha.
*/
LINHA linha_aparar(LINHA linha);

#endif // !_CABEÇALHO_LINHA
