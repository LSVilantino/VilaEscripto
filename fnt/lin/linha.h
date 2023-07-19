#ifndef _CABEÇALHO_LINHA
#define _CABEÇALHO_LINHA

#include "general.h"

/*
	Arranca todos os charactéres da linha.
*/
void linha_arrancar(size_t tamanho, Linha linha);

/*
	Conta os charactéres de uma linha.
*/
int linha_contar(const Linha linha);
/*
	Introduz um novo charactére numa linha allocada.
	
	Foi criada inicialmente para facilitar a introducção em ciclos
	e evitar repetição.
	
*/
void linha_introduzir_charactére(char charactére, int posição, Linha* linha);
/*
	Introduz uma linha à outra.
*/
void linha_agregar_linha(Linha linhaIntroduzida, int* posição, Linha* linha);
/*
	Introduz uma linha numa matriz allocada.
	
	Foi criada inicialmente para facilitar a introducção em ciclos
	e evitar repetição.
*/
void matriz_linha_introduzir_linha(Linha linha, int posição, Linha** matriz);
/*
	Duplica a linha dada.
*/
Linha linha_duplicar(Linha linha);

/*
	Valida se uma linha está contida em outra.
*/
Dico linha_contém(Linha comparador, const Linha linha);
/*
	Comparar o conteúdo de duas linhas.
*/
Dico linha_comparar(Linha comparador, const Linha linha);

/*
Remove espaços do início e fim da linha.
*/
void linha_aparar(Linha* linha);

#endif // !_CABEÇALHO_LINHA
