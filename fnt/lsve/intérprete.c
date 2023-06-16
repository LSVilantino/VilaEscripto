#include "intérprete.h"

#include "../pilha.h"
#include "../linha.h"
#include "general.h"

#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>

LINHA rastilho_definir_linha_de_erro(Rastilho_Tipo tipo) {
	LINHA linha = LINHA_NIL;

	switch (tipo)
	{
	case rastilho__carece_concedido: { linha = "Carece concedido/clave, indefinido."; break; }
	case rastilho__carece_concessão: { linha = "Carece concessão/separador."; break; }
	case rastilho__carece_concessão_válida: { linha = "A concessão é inválida"; break; }
	case rastilho__carece_ficha_válida: { linha = "A ficha é inválida"; break; }
	case rastilho__carece_valôr: { linha = "Carece valôr à clave"; break; }
	case rastilho__expressão_excedente: { linha = "Existem mais operadores do que o esperado, formatação incorrecta."; break; }
	case rastilho__encerro_forçado: { linha = "Encerrou-se o ficheiro forçadamente."; break; }
	case rastilho__comentário: { linha = "Expressão comentada."; break; }
	case rastilho__nil: { break; }
	default: break;
	}

	return linha;
}

Operação operação_construir_falha() {
	Operação operação = { 0 };
	operação.índice = -1;
	return operação;
}

Operação operação_daExpressão_têrPorTipo(Operação_Tipo tipo, Expressão expressão) {
	int operadôr_n = 0;
	while (expressão.operador[operadôr_n].índice == operadôr_n) {
		if (expressão.operador[operadôr_n].tipo == tipo) {
			return expressão.operador[operadôr_n];
		}

		operadôr_n++;
	}

	return operação_construir_falha();
}

void operação_re_definir(int operadôr_n, Expressão* expressão, Expectação expectação, Operação_Tipo operação_tipo, size_t linha_t) {
	(*expressão).operador = memória_re_allocar((operadôr_n + 1) * sizeof(Operação), (*expressão).operador);

	(*expressão).operador[operadôr_n].índice = operadôr_n;
	(*expressão).operador[operadôr_n].expectação = expectação;
	(*expressão).operador[operadôr_n].tipo = operação_tipo;
	(*expressão).operador[operadôr_n].linha = memória_allocar(linha_t);
	(*expressão).operador[operadôr_n].linha[0] = LINHA_NIL;
}

Expressão expressão_construir_falha() {
	Expressão expressãoFalha = { 0 };
	expressãoFalha.índice = -1;

	operação_re_definir(0, &expressãoFalha, expectação__nil, operação__nil, 1);
	expressãoFalha.operador[0].índice = -1;

	return expressãoFalha;
}

Operação operação_daExpressão_têrPorClave(LINHA linha, Expressão expressão) {
	int operadôr_n = 0;
	Operação operador_clave = operação_daExpressão_têrPorTipo(operação__concedido, expressão);

	if (linha_comparar(linha, operador_clave.linha)) return operador_clave;
	return operação_construir_falha();
}

Dico operação_daExpressão_seTem_PorClave(LINHA linha, Expressão expressão) {
	int operadôr_n = 0;
	Operação operador_clave = operação_daExpressão_têrPorTipo(operação__concedido, expressão);

	if (linha_comparar(linha, operador_clave.linha)) return vero;
	return falso;
}

Expressão expressões_têrPorClave(LINHA clave, Expressão* expressões) {
	int expressão_n = 0;

	while (expressões[expressão_n].índice == expressão_n) {
		if (operação_daExpressão_seTem_PorClave(clave, expressões[expressão_n])) {
			return expressões[expressão_n];
		}

		expressão_n++;
	}

	return expressão_construir_falha();
}

void expressão_rastilho_definir(Expressão* expressão, Rastilho_Tipo rastilho_tipo) {
	(*expressão).rastilho.tipo = rastilho_tipo;
	(*expressão).rastilho.erro = rastilho_definir_linha_de_erro(rastilho_tipo);
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

	LINHA ficha = memória_allocar(1);
	int ficha_n = 0;

	expressão.operador = NULL;
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
			As primeiras corridas do ciclo caem em endereço nil,
			ficam armazenadas no início da pilha.
			
			Quanto maior a pilha, mais iterações levam para chegar
			algum valôr. Até lá, foram-se os índices.
		*/
		if (charactére == LINHA_NIL) continue;

		/*
			Se o encerro forçado for encontrado, encerra-se tudo e retorna o que foi armazenado.
		*/
		if (clave_têr_por_tipo(clave_ficheiro_forçar_encerro).pala[0] == charactére) {
			expressão_rastilho_definir(&expressão, rastilho__encerro_forçado);
			expressão.operador[operadôr_n].linha = LINHA_NIL;

			return expressão;
		}

		if (clave_têr_por_tipo(clave_ficheiro_comentário).pala[0] == charactére) {
			expressão_rastilho_definir(&expressão, rastilho__comentário);
			expressão.operador[operadôr_n].linha = LINHA_NIL;

			return expressão;
		}

		if (clave_têr_por_tipo(clave_ficha).pala[0] == charactére) {
			expressão.operador[operadôr_n].expectação = expectação__ficha_abre;
			continue;
		}

		if (clave_têr_por_tipo(clave_ficha).pala[1] == charactére &&
			expressão.operador[operadôr_n].expectação == expectação__ficha_abre)
		{
			expressão.operador[operadôr_n].expectação = expectação__ficha_fecha;
			continue;
		}

		if (expressão.operador[operadôr_n].expectação == expectação__ficha_fecha) {
			if (clave_têr_por_tipo(clave_ficha).pala[2] == charactére) {
				/*
					Uma vez lida a clave da ficha, obtém-se seu valôr.
				*/
				Expressão expressãoDaFicha = expressões_têrPorClave(ficha, expressões);
				Operação_Tipo a = expressãoDaFicha.operador[2].tipo;
				Operação valôrDaFicha = operação_daExpressão_têrPorTipo(operação__valôr, expressãoDaFicha);

				if (valôrDaFicha.índice == -1) {
					expressão_rastilho_definir(&expressão, rastilho__carece_ficha_válida);
					return expressão;
				}

				linha_introduzir_linha(valôrDaFicha.linha, &operadôr_linha_n, &expressão.operador[operadôr_n].linha);
				printf(expressão.operador[operadôr_n].linha);

				free(ficha);
 				ficha = memória_allocar(2);
				ficha_n = 0;

				expressão.operador[operadôr_n].expectação = expectação__nil;
				continue;
			}

			linha_introduzir_charactére(charactére, ficha_n, &ficha);

			ficha_n++;
			continue;
		}

		/*
			A linha é o limitante que separa cada linha, quando for atingido, avalia-se a linha
			e seus elementos para averiguar a sua integridade.
		*/
		if (charactére == LINHA_SALTA) {
			printf("\n");

			if (operadôr_n == 0) {
				expressão_rastilho_definir(&expressão, rastilho__carece_concessão);
				/*printf("\n\n\n\n\n\n\n");
				printf("Falta concessão");*/
			}
			if (operadôr_n == 1) {
				expressão_rastilho_definir(&expressão, rastilho__carece_valôr);
			}
			if (operadôr_n == 2) {
				expressão_rastilho_definir(&expressão, rastilho__nil);
			}

			operadôr_n = 0;
			return expressão;
		}

		/*
			Ao conceder uma clave, espera-se uma concessão.
		
			Se a concessão vier antes da clave, será tratada como clave e a concessão não será reconhecida.
			Se a concessão vier antes e depois da clave, a primeira concessão fará parte do nome da clave.
			Se a concessão vier antes, depois da clave, e antes ou depois do valôr, será tratada como valôr
			e/ou nome da clave.
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

		/*
			Quando se espera uma concessão, estamos em estado para armazenar
			o concedido.
		*/
		if (expressão.operador[operadôr_n].expectação == expectação__concedido ||
			expressão.operador[operadôr_n].expectação == expectação__nil
			)
		{
			linha_introduzir_charactére(charactére, operadôr_linha_n, &expressão.operador[operadôr_n].linha);
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

		if (resultado.expressão[expressão_n].rastilho.tipo != rastilho__nil) {
			if (resultado.expressão[expressão_n].rastilho.tipo == rastilho__encerro_forçado) {
				printf("\n\n--------------------------------\n");
				printf("Quebra: %s", resultado.expressão[expressão_n].rastilho.erro);
				printf("\n--------------------------------\n\n");
				break;
			}

			if (resultado.expressão[expressão_n].rastilho.tipo == rastilho__comentário) {
				printf("\n\n--------------------------------\n");
				printf("Ignorância: %s", resultado.expressão[expressão_n].rastilho.erro);
				printf("\n--------------------------------\n\n");

				resultado.expressão[expressão_n].índice = expressão_n;
				expressão_n++;
				continue;
			}

			if (resultado.expressão[expressão_n].rastilho.tipo == rastilho__carece_ficha_válida) {
				printf("\n\n--------------------------------\n");
				printf("Problema: %s", resultado.expressão[expressão_n].rastilho.erro);
				printf("\n--------------------------------\n\n");
				break;
			}
		}

		resultado.expressão[expressão_n].índice = expressão_n;
		expressão_n++;
    }

    return resultado;
}
