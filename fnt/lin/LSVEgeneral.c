#include "LSVEgeneral.h"
#include "general.h"

#include "linha.h"

#include <stdio.h>
#include  <stdlib.h>

Palaclave claves[] = {
	{ (Linha) ((char)EOF), clave_ficheiro_encerro },
	{ "%", clave_ficheiro_forçar_encerro },
	{ "#", clave_ficheiro_comentário },
	{ ">$()>", clave_lêr_avançar_e_procurar },
	{ "$()", clave_ficha },
	{ "(", clave_ficha_abre },
	{ ")", clave_ficha_fecha },
	{ ">>>", clave_lêr_e_escolher },
	{ ">*", clave_corrêr },
	{ ">>", clave_lêr_e_avançar },
	{ ">", clave_lêr },
	{ 0 }
};

Palaclave
clave_têr_por_tipo(Palaclave_Tipo tipo) {
	int i = 0;
	while (claves[i].pala != 0) {
		if (claves[i].tipo == tipo) break;
		i++;
	}

	return claves[i];
}

Palaclave_Tipo 
clave_comparar(Linha linha) {
	Palaclave clave;

	int i = 0;
	while (claves[i].pala[0] != LINHA_NIL) {
		clave = claves[i];
		linha_comparar(linha, clave.pala);
		i++;
	}

	return clave.tipo;
}
