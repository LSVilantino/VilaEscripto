#include "LSVEgeneral.h"
#include "general.h"

#include "linha.h"

#include <stdio.h>
#include  <stdlib.h>

Palaclave claves[] = {
	{ (char*) ((char)EOF), clave_ficheiro_encerro },
	{ "%", clave_ficheiro_forçar_encerro },
	{ "#", clave_ficheiro_comentário },
	/*{ '(', clave_ficha_abre },
	{ ')', clave_ficha_fecha },*/
	{ ">$()>", clave_lêr_avançar_e_procurar },
	{ "$()", clave_ficha },
	{ "(", clave_ficha_abre },
	{ ")", clave_ficha_fecha },
	{ ">>>", clave_lêr_e_escolher },
	{ ">*", clave_corrêr },
	{ ">>", clave_lêr_e_avançar },
	{ ">", clave_lêr },
};

Palaclave
clave_têr_por_tipo(Palaclave_Tipo tipo) {
	int i = 0;
	while (claves[i].pala != LINHA_NIL) {
		if (claves[i].tipo == tipo) break;
		i++;
	}

	return claves[i];
}

Palaclave_Tipo clave_comparar(char* linha) {
	Palaclave clave;

	int i = 0;
	while (claves[i].pala != LINHA_NIL) {
		clave = claves[i];
		linha_comparar(linha, clave.pala);
		i++;
	}

	return clave.tipo;
}
