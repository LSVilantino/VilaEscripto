#include "intérprete.h"

#include "../pilha.h"
#include "../linha.h"
#include "general.h"

#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>

Expressão expressão_interpretar(char* linha) {
    Expressão expressão;

    Pilha pilha = pilha_construir(3);
    int recúo = pilha.recúo;

	int linha_n = 0;
	int operadôr_n = 0;
	int operadôr_linha_n = 0;
	int clave_n = 0;

	expressão.operador = memória_allocar(sizeof(Operação));
	expressão.operador[operadôr_n].expectação = expecta_concedido;
	expressão.operador[operadôr_n].linha = memória_allocar(1);

    while (recúo > 1)
    {
		if (linha[linha_n] == LINHA_NIL) { recúo--; }
		else {
			pilha_introduzir(linha[linha_n], &pilha);
			linha_n++;
		}
		char charactére = pilha.conteúdo[recúo - 1];

		if (charactére == LINHA_NIL) continue;

		if (clave_têr_por_tipo(clave_lêr).pala[clave_n] == charactére) {
			continue;
		}

		/*if (charactére == clave_ficha) expressão.operador[operadôr_n].expectação = expecta_ficha_abre;
		if (charactére == clave_ficha_abre) {
			expressão.operador[operadôr_n].expectação = expecta_ficha_fecha;
			expressão.operador[operadôr_n].seAbre = vero;
		}
		if (clave_têr_por_tipo(clave_ficha_fecha).pala[] == charactére) {
			expressão.operador[operadôr_n].expectação = expecta_nil;
			expressão.operador[operadôr_n].seFecha = vero;
		}*/

		expressão.operador[operadôr_n].seAbre = vero;
		linha_introduzir_charactére(pilha.conteúdo[recúo - 1], operadôr_linha_n, &expressão.operador[operadôr_n].linha);
		printf("%c", expressão.operador[operadôr_n].linha[operadôr_linha_n]);

		operadôr_linha_n++;
    }

    return expressão;
}

Intérprete interpretar(char** linhas) {
    Intérprete resultado = { 0 };

    for (int i = 0; linhas[i] != LINHA_NIL; i++)
    {
        expressão_interpretar(linhas[i]);
    }

    return resultado;
}
