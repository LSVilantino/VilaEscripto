#include "linha.h"
#include "general.h"

#include <stdlib.h>

void 
linha_arrancar(size_t tamanho, Linha linha) {
	for(int i = 0; i < tamanho; i++) { linha[i] = LINHA_NIL; }
}

int
linha_contar(const Linha linha) {
    int tamanho = 0;
    while (linha[tamanho]) tamanho++;

    return tamanho;
}

void
linha_introduzir_charactére(char charactére, int posição, Linha* linha)
{
	(*linha) = memória_re_allocar(posição + 2, (*linha));
	(*linha)[posição] = charactére;
	(*linha)[posição + 1] = LINHA_NIL;
}

void
linha_agregar_linha(Linha linhaIntroduzida, int* posição, Linha* linha)
{
	int linhaIntroduzida_t = linha_contar(linhaIntroduzida);
	int linha_t = linha_contar((*linha));
	int linha_ttl = linhaIntroduzida_t + linha_t;

	(*linha) = memória_re_allocar(linha_ttl + 1, (*linha));

	int linhaIntroduzida_n = 0;
	while (linhaIntroduzida_n != linhaIntroduzida_t && (*posição) != linha_ttl) {
		(*linha)[(*posição)++] = linhaIntroduzida[linhaIntroduzida_n++];
	}

	(*linha)[linha_ttl] = LINHA_NIL;
}

void
matriz_linha_introduzir_linha(Linha linha, int posição, Linha** matriz)
{
	(*matriz) = memória_re_allocar((posição + 2) * sizeof(Linha), (*matriz));
	(*matriz)[posição] = linha_duplicar(linha);
}

Linha
linha_duplicar(Linha linha) {
	int tamanho = linha_contar(linha);

	Linha duplicata = memória_preên_allocar((tamanho + 1), sizeof(char));

	for (int i = 0; i < tamanho; i++) {
		duplicata[i] = linha[i];
	}

	duplicata[tamanho] = LINHA_NIL;

    return duplicata;
}

Dico
linha_contém(Linha comparadôr, const Linha linha) {
	int tamanho_comparadôr = 0;
	while (comparadôr[tamanho_comparadôr] != LINHA_NIL) {
		tamanho_comparadôr++;
	}

	tamanho_comparadôr--;

	int n = 0;
	int n_comparador = 0;
	while (linha[n] != LINHA_NIL) {
		//printf("(%c//%c) ", linha[n], comparador[n_comparador]);
		if (linha[n] == comparadôr[n_comparador]) {
			//printf("(%d %c/%d %c - %d) ", n, linha[n], n_comparador, comparador[n_comparador], tamanho_comparador);
			if (n_comparador == tamanho_comparadôr) return 1;
			n_comparador++;
		}
		else {
			n_comparador = 0;
		}
		n++;
	}

	return 0;
}

Dico
linha_comparar(Linha comparadôr, const Linha linha) {
	if (linha == NULL || comparadôr == NULL) return 0;

	int linha_t = linha_contar(linha) - 1;
	int comparadôr_t = linha_contar(comparadôr) - 1;

	if (linha_t < comparadôr_t) return 0;

	//printf("\n\n(/%s/%s\\)\n\n", linha, comparadôr);

	int n = 0;
	while (linha[n] != LINHA_NIL) {
		//printf("(/%c―%c\\) ", linha[n], comparadôr[n]);
		if (comparadôr[n] == linha[n]) {
			if (n == linha_t) return 1;
			n++;
		}
		else return 0;
	}

	return 0;
}

Linha
linha_aparar(Linha linha) {
	while (*linha == ESPAÇO) linha++;

	Linha término = linha + linha_contar(linha) - 1; // Posição da linha a partir do sem-espaço.
	while (término > linha && *término == ESPAÇO || *término == LINHA_SALTA || *término == '\r' || *término == '\t') término--;
	término[1] = LINHA_NIL;

	//printf("%s\n", linha);

	return linha;
}
