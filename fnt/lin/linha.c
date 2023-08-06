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
#define linha_ (*linha)

	linha_ = memória_re_allocar(posição + 2, linha_);
	linha_[posição] = charactére;
	linha_[posição + 1] = LINHA_NIL;

#undef linha_
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
linha_contém(Linha comparador, const Linha linha) {
	int tamanho_comparador = 0;
	while (comparador[tamanho_comparador] != LINHA_NIL) {
		tamanho_comparador++;
	}

	tamanho_comparador--;

	int n = 0;
	int n_comparador = 0;
	while (linha[n] != LINHA_NIL) {
		if (linha[n] == comparador[n_comparador]) {
			if (n_comparador == tamanho_comparador) return 1;
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
linha_comparar(Linha comparador, const Linha linha) {
	Dico resultado = fal;

	if (linha == nil || comparador == nil) {
		resultado = fal; 
		goto fim;
	}

	int linha_t = linha_contar(linha) - 1;
	int comparador_t = linha_contar(comparador) - 1;

	if (linha_t < comparador_t) {
		resultado = fal; 
		goto fim;
	}

	int n = 0; 
	while (linha[n] != LINHA_NIL) {
		if (comparador[n] == linha[n]) {
			if (n == linha_t) {
				resultado = vero;
				goto fim;
			}

			n++;
		}
		else {
			resultado = fal; 
			goto fim;
		}
	}

fim:
	return fal;
}

void
linha_aparar(Linha* linha) {
#define linha_ (*linha)

	while (*linha_ == ESPAÇO) linha_++;

	Linha término = linha_ + linha_contar(linha_) - 1; // Posição da linha a partir do sem-espaço.
	while (término > linha_ && *término == ESPAÇO || *término == LINHA_SALTA) término--;
	término[1] = LINHA_NIL;

	//printf("%s\n", linha);

#undef linha_
}
