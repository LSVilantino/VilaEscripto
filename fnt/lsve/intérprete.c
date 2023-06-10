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
	expressão.operador[operadôr_n].expectação = expectação__concedido;
	expressão.operador[operadôr_n].tipo = operação__concedido;
	expressão.operador[operadôr_n].linha = memória_allocar(1);

    while (recúo > 1)
    {
		if (linha[linha_n] == LINHA_NIL) { recúo--; }
		else {
			pilha_introduzir(linha[linha_n], &pilha);
			linha_n++;
		}
		char charactére = pilha.conteúdo[recúo - 1];

		// As primeiras corridas do ciclo caem em endereço nil.
		if (charactére == LINHA_NIL) continue;
		if (charactére == LINHA_SALTA) {
			if (operadôr_n == 0) {
				expressão.rastilho.tipo = rastilho__carece_concessão;
				expressão.rastilho.erro = "Carece clave";
				/*printf("\n\n\n\n\n\n\n");
				printf("Falta concessão");*/
			}
			if (operadôr_n == 1) { expressão.rastilho.tipo = rastilho__carece_valôr; }
			if (operadôr_n == 2) { expressão.rastilho.tipo = rastilho__nil; }

			operadôr_n = 0;
			break;
		}

		if (expressão.operador[operadôr_n].expectação == expectação__concessão) {
			if (clave_têr_por_tipo(clave_lêr).pala[clave_n] == charactére) {
				operadôr_n++;

				expressão.operador = memória_re_allocar((operadôr_n + 1) * sizeof(Operação), expressão.operador);

				expressão.operador[operadôr_n].expectação = expectação__valôr;
				expressão.operador[operadôr_n].tipo = operação__concessão_directa;
				expressão.operador[operadôr_n].linha = memória_allocar(2);

				operadôr_linha_n = 0;

				expressão.operador[operadôr_n].linha[operadôr_linha_n] = charactére;
				expressão.operador[operadôr_n].linha[operadôr_linha_n + 1] = LINHA_NIL;

				printf("%c", expressão.operador[operadôr_n].linha[operadôr_linha_n]);
			}

			operadôr_linha_n = 0;

			if (expressão.operador[operadôr_n].tipo == operação__concedido) expressão.operador[operadôr_n].expectação = expectação__concedido;
			else if (expressão.operador[operadôr_n].tipo == operação__concessão_directa) {
				operadôr_n++;

				expressão.operador = memória_re_allocar((operadôr_n + 1) * sizeof(Operação), expressão.operador);

				expressão.operador[operadôr_n].expectação = expectação__nil;
				expressão.operador[operadôr_n].tipo = operação__valôr;
				expressão.operador[operadôr_n].linha = memória_allocar(2);
				expressão.operador[operadôr_n].linha[operadôr_linha_n] = LINHA_NIL;
				continue;
			}
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

		/*
		* Quando se espera uma concessão, estamos em estado para armazenar
		* o concedido.
		*/
		if (expressão.operador[operadôr_n].expectação == expectação__concedido || expressão.operador[operadôr_n].expectação == expectação__nil) {
			linha_introduzir_charactére(pilha.conteúdo[recúo - 1], operadôr_linha_n, &expressão.operador[operadôr_n].linha);
			printf("%c", expressão.operador[operadôr_n].linha[operadôr_linha_n]);
			operadôr_linha_n++;

			if (expressão.operador[operadôr_n].tipo == operação__concedido) expressão.operador[operadôr_n].expectação = expectação__concessão;
		}
    }

    return expressão;
}

Intérprete interpretar(char** linhas) {
    Intérprete resultado;

	int expressão_n = 0;
	resultado.expressão = memória_allocar(sizeof(Expressão));

    while(linhas[expressão_n] != LINHA_NIL)
    {
		resultado.expressão = memória_re_allocar((expressão_n + 1) * sizeof(Expressão), resultado.expressão);
        resultado.expressão[expressão_n] = expressão_interpretar(linhas[expressão_n]);

		if (resultado.expressão[expressão_n].rastilho.tipo != rastilho__nil) {
			printf("\n\n--------------------------------\n");
			printf("Erro: %s", resultado.expressão[expressão_n].rastilho.erro);
			printf("\n--------------------------------\n\n");
			break;
		}

		expressão_n++;
    }

    return resultado;
}
