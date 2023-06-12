#include "intérprete.h"

#include "../pilha.h"
#include "../linha.h"
#include "general.h"

#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>

Expressão operação_daExpressão_têrPorClave(LINHA linha, Expressão expressão) {
	int operadôr_n = 0;

	while (expressão.operador[operadôr_n].linha != LINHA_NIL) {
		printf("\n\n\n");
		printf(expressão.operador[operadôr_n].linha);
		if (linha_comparar(linha, expressão.operador[operadôr_n].linha)) {
			return expressão;
		}

		operadôr_n++;
	}

	return (Expressão) { 0 };
}

Expressão operação_dasExpressões_têr(LINHA clave, Expressão* expressões) {
	int expressão_n = 0;
	while (expressões[expressão_n].linha != LINHA_NIL) {
		Expressão expressãoEncontrada = operação_daExpressão_têrPorClave(clave, expressões[expressão_n]);
		if (expressãoEncontrada.linha != LINHA_NIL) { return expressãoEncontrada; }

		expressão_n++;
	}

	return (Expressão) { 0 };
}

Operação operação_daExpressão_têr(Operação_Tipo tipo, Expressão expressão) {
	int operadôr_n = 0;
	while (expressão.operador[operadôr_n].linha != LINHA_NIL) {
		if (expressão.operador[operadôr_n].tipo == tipo) {
			return expressão.operador[operadôr_n];
		}

		operadôr_n++;
	}

	return (Operação) { 0 };
}

void operação_re_definir(int operadôr_n, Expressão* expressão, Expectação expectação, Operação_Tipo operação_tipo, size_t linha_t) {
	(*expressão).operador = memória_re_allocar((operadôr_n + 1) * sizeof(Operação), (*expressão).operador);

	(*expressão).operador[operadôr_n].expectação = expectação;
	(*expressão).operador[operadôr_n].tipo = operação_tipo;
	(*expressão).operador[operadôr_n].linha = memória_allocar(linha_t);
	(*expressão).operador[operadôr_n].linha[0] = LINHA_NIL;
}

void expressão_rastilho_definir(Expressão* expressão, Rastilho_Tipo rastilho_tipo, LINHA linha) {
	(*expressão).rastilho.tipo = rastilho_tipo;
	(*expressão).rastilho.erro = linha;
}

Expressão expressão_interpretar(char* linha, Expressão* expressões) {
    Expressão expressão;
	expressão.linha = linha;

    Pilha pilha = pilha_construir(3);
    int recúo = pilha.recúo;

	int linha_n = 0;
	int operadôr_n = 0;
	int operadôr_linha_n = 0;
	int clave_n = 0;

	expressão.operador = memória_allocar(sizeof(Operação));
	operação_re_definir(operadôr_n, &expressão, expectação__concedido, operação__concedido, 1);

    while (recúo > 1)
    {
		/* Ao fim da linha, diminui - se o recúo da pilha, até chegar à ponta,
		*  o último charactére armazenado.
		*
		* Se a linha não estiver ao fim, introduz o último charactére à pilha.
		*/
		if (linha[linha_n] == LINHA_NIL) { recúo--; }
		else {
			pilha_introduzir(linha[linha_n], &pilha);
			linha_n++;
		}
		char charactére = pilha.conteúdo[recúo - 1];

		/*
		* As primeiras corridas do ciclo caem em endereço nil,
		* ficam armazenadas no início da pilha.
		*
		* Quanto maior a pilha, mais iterações levam para chegar
		* algum valôr. Até lá, foram-se os índices.
		*/ 
		if (charactére == LINHA_NIL) continue;

		/*
		* Se o encerro forçado for encontrado, encerra-se tudo e retorna o que foi armazenado.
		*/
		if (clave_têr_por_tipo(clave_ficheiro_forçar_encerro).pala[0] == charactére) {
			expressão_rastilho_definir(&expressão, rastilho__encerro_forçado, "Encerro forçado");
			expressão.operador[operadôr_n].linha = LINHA_NIL;

			printf(operação_dasExpressões_têr(operação_daExpressão_têr(operação__concedido, expressão).linha, expressões).linha);

			return expressão;
		}

		if (clave_têr_por_tipo(clave_ficheiro_comentário).pala[0] == charactére) {
			expressão_rastilho_definir(&expressão, rastilho__comentário, "Comentário");

			return expressão;
		}

		/*
		* A linha é o limitante que separa cada linha, quando for atingido, avalia-se a linha
		* e seus elementos para averiguar a sua integridade.
		*/
		if (charactére == LINHA_SALTA) {
			if (operadôr_n == 0) {
				expressão_rastilho_definir(&expressão, rastilho__carece_concessão, "Carece clave");
				/*printf("\n\n\n\n\n\n\n");
				printf("Falta concessão");*/
			}
			if (operadôr_n == 1) {
				expressão_rastilho_definir(&expressão, rastilho__carece_valôr, "Carece valôr");
			}
			if (operadôr_n == 2) {
				expressão_rastilho_definir(&expressão, rastilho__nil, LINHA_NIL);
			}

			operadôr_n = 0;
			return expressão;
		}

		/*
		* Ao conceder uma clave, espera-se uma concessão.
		*
		* Se a concessão vier antes da clave, será tratada como clave e a concessão não será reconhecida.
		* Se a concessão vier antes e depois da clave, a primeira concessão fará parte do nome da clave.
		* Se a concessão vier antes, depois da clave, e antes ou depois do valôr, será tratada como valôr
		* e/ou nome da clave.
		*/
		if (expressão.operador[operadôr_n].expectação == expectação__concessão) {
			if (clave_têr_por_tipo(clave_lêr).pala[clave_n] == charactére) {
				operadôr_n++;

				operação_re_definir(operadôr_n, &expressão, expectação__valôr, operação__concessão_directa, 2);

				operadôr_linha_n = 0;

				expressão.operador[operadôr_n].linha[operadôr_linha_n] = charactére;
				expressão.operador[operadôr_n].linha[operadôr_linha_n + 1] = LINHA_NIL;

				printf("%c", expressão.operador[operadôr_n].linha[operadôr_linha_n]);
			}


			if (expressão.operador[operadôr_n].tipo == operação__concedido) expressão.operador[operadôr_n].expectação = expectação__concedido;
			else if (expressão.operador[operadôr_n].tipo == operação__concessão_directa) {
				operadôr_linha_n = 0;
				operadôr_n++;

				operação_re_definir(operadôr_n, &expressão, expectação__nil, operação__valôr, 1);
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
        resultado.expressão[expressão_n] = expressão_interpretar(linhas[expressão_n], resultado.expressão);

		//if (resultado.expressão[expressão_n].rastilho.tipo != rastilho__nil) {
		//	if (resultado.expressão[expressão_n].rastilho.tipo == rastilho__encerro_forçado) {
		//		printf("\n\n--------------------------------\n");
		//		printf("Quebra: %s", resultado.expressão[expressão_n].rastilho.erro);
		//		printf("\n--------------------------------\n\n");
		//		break;
		//	}

		//	if (resultado.expressão[expressão_n].rastilho.tipo == rastilho__comentário) {
		//		printf("\n\n--------------------------------\n");
		//		printf("Quebra: %s", resultado.expressão[expressão_n].rastilho.erro);
		//		printf("\n--------------------------------\n\n");

		//		expressão_n++;
		//		continue;
		//	}
		//}

		expressão_n++;
    }

    return resultado;
}
