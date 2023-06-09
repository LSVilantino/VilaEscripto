#include "linha.h"
#include "general.h"

int
linha_contar(char* linha) {
    int tamanho = 0;
    while (linha[tamanho]) tamanho++;

    return tamanho;
}

void
linha_introduzir_charactére(char charactére, int posição, char** linha)
{
	(*linha) = memória_re_allocar(posição + 2, (*linha));
	(*linha)[posição] = charactére;
	(*linha)[posição + 1] = LINHA_NIL;
}

void matriz_linha_introduzir_linha(char* linha, int posição, char*** matriz)
{
	(*matriz) = memória_re_allocar((posição + 2) * sizeof(LINHA), (*matriz));
	(*matriz)[posição] = linha_duplicar(linha);
	(*matriz)[posição + 1] = LINHA_NIL;
}

char*
linha_duplicar(char* linha) {
    char* duplicata; int tamanho = linha_contar(linha);

    duplicata = memória_allocar(tamanho + 1); // mais nil.

    for (int i = 0; i < tamanho; i++) duplicata[i] = linha[i];
    duplicata[tamanho] = LINHA_NIL;

    return duplicata;
}

Dico
linha_comparar(char* comparadôr, const char* linha)
{
	return falso;
}
