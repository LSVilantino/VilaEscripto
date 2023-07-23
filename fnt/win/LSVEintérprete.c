#include "LSVEintérprete.h"

#include "pilha.h"
#include "linha.h"
#include "ficheiro.h"
#include "LSVEconsola.h"
#include "LSVEgeneral.h"

#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>

LINHA rastilho_definir_linha_de_erro(Rastilho_Tipo tipo) {
	LINHA linha = LINHA_NIL;

	switch (tipo)
	{
	case rastilho__carece_concedido: 				{ linha = "Carece concedido/clave, indefinido."; 									break; }
	case rastilho__carece_concessão: 				{ linha = "Carece concessão/separador."; 											break; }
	case rastilho__carece_concessão_válida: 		{ linha = "A concessão é inválida"; 												break; }
	case rastilho__carece_ficha_válida: 			{ linha = "A ficha é inválida"; 													break; }
	case rastilho__carece_valôr: 					{ linha = "Carece valôr à clave"; 													break; }
	case rastilho__expressão_excedente: 			{ linha = "Existem mais operadores do que o esperado, formatação incorrecta."; 		break; }
	case rastilho__encerro_forçado: 				{ linha = "Encerrou-se o ficheiro forçadamente."; 									break; }
	case rastilho__comentário: 						{ linha = "Expressão comentada."; 													break; }
	case rastilho__nil: 							{ 																					break; }
	default: break;
	}

	return linha;
}

Operação operação_construir_falha() {
	Operação operação = { 0 };
	operação.índice = ÍNDICE_ERRO;
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
	expressãoFalha.índice = ÍNDICE_ERRO;

	operação_re_definir(0, &expressãoFalha, expectação__nil, operação__nil, 1);
	expressãoFalha.operador[0].índice = ÍNDICE_ERRO;

	return expressãoFalha;
}

Operação operação_daExpressão_têrPorClave(LINHA linha, Expressão expressão) {
	Operação operador_clave = operação_daExpressão_têrPorTipo(operação__concedido, expressão);

	if (linha_comparar(linha, operador_clave.linha)) return operador_clave;
	return operação_construir_falha();
}

Dico operação_daExpressão_seTem_PorClave(LINHA linha, Expressão expressão) {
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

void intérprete_agregar(Expressão* expressões, int* posição, Intérprete* agregado) {

	//printf("\n\n\n---------------\n\n\n");

	int expressão_n = 0;
	while (expressões[expressão_n].índice == expressão_n) {
		(*agregado).expressão = memória_re_allocar(((*posição) + 1) * sizeof(Expressão), (*agregado).expressão);
		(*agregado).expressão[(*posição)] = expressões[expressão_n];

		(*agregado).expressão[(*posição)].índice = (*posição);

		//printf("%d - %s\n", (*agregado).expressão[(*posição)].índice, (*agregado).expressão[(*posição)].operador[0].linha);

		expressão_n++; (*posição)++;
	}
}

void expressão_interpretar(char* linha, Intérprete* intérprete, int* expressão_n) {
	(*intérprete).expressão[(*expressão_n)].linha = linha;

    Pilha pilha = pilha_construir(3);
    int recúo = pilha.recúo;

	int linha_n = 0;
	int operadôr_n = 0;
	int operadôr_linha_n = 0;
	int clave_n = 0;

	LINHA ficha = memória_allocar(1);
	ficha[0] = LINHA_NIL;
	int ficha_n = 0;

	// Quantos ciclos devem ser pulados?
	// Utiliza-se quando se lê e valida charactéres da pilha.
	int pula = 0;

	(*intérprete).expressão[(*expressão_n)].operador = NULL;
	operação_re_definir(operadôr_n, &(*intérprete).expressão[(*expressão_n)], expectação__concedido, operação__concedido, 1);

	while (recúo > 1)
	{
		/* 
			Ao fim da linha, diminui - se o recúo da pilha, até chegar à ponta,
			o último charactére armazenado.
		
			Se a linha não estiver ao fim, introduz o último charactére à pilha.
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

		if (pula != 0) {
			pula--;
			continue;
		}

		/*
			Se o encerro forçado for encontrado, encerra-se tudo e retorna o que foi armazenado.
		*/
		if (clave_têr_por_tipo(clave_ficheiro_forçar_encerro).pala[0] == charactére) {
			(*intérprete).expressão[(*expressão_n)] = expressão_construir_falha();
			expressão_rastilho_definir(&(*intérprete).expressão[(*expressão_n)], rastilho__encerro_forçado);
			(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha = LINHA_NIL;

			(*intérprete).expressão[(*expressão_n)].índice = (*expressão_n);
			(*expressão_n)++;
			break;
		}

		if (clave_têr_por_tipo(clave_ficheiro_comentário).pala[0] == charactére) {
			(*intérprete).expressão[(*expressão_n)] = expressão_construir_falha();
			expressão_rastilho_definir(&(*intérprete).expressão[(*expressão_n)], rastilho__comentário);
			(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo = operação__concedido;
			(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha = LINHA_NIL;

			(*intérprete).expressão[(*expressão_n)].índice = (*expressão_n);
			(*expressão_n)++;
			break;
		}

		if (clave_têr_por_tipo(clave_ficha).pala[0] == charactére) {
			(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].expectação = expectação__ficha_abre;
			continue;
		}

		if (clave_têr_por_tipo(clave_ficha).pala[1] == charactére &&
			(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].expectação == expectação__ficha_abre)
		{
			(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].expectação = expectação__ficha_fecha;
			continue;
		}

		if ((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].expectação == expectação__ficha_fecha) {
			if (clave_têr_por_tipo(clave_ficha).pala[2] == charactére) {
				/*
					Uma vez lida a clave da ficha, obtém-se seu valôr.
				*/
				Expressão expressãoDaFicha = expressões_têrPorClave(ficha, (*intérprete).expressão);
				Operação valôrDaFicha = operação_daExpressão_têrPorTipo(operação__valôr, expressãoDaFicha);

				if (valôrDaFicha.índice == ÍNDICE_ERRO) {
					expressão_rastilho_definir(&(*intérprete).expressão[(*expressão_n)], rastilho__carece_ficha_válida);
					(*intérprete).expressão[(*expressão_n)].índice = (*expressão_n)++;
					break;
				}

				linha_agregar_linha(valôrDaFicha.linha, &operadôr_linha_n, &(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha);
				printf(valôrDaFicha.linha);

				free(ficha);
				ficha = memória_allocar(2);
				ficha[0] = LINHA_NIL;
				ficha_n = 0;

				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].expectação = expectação__nil;
				continue;
			}

			linha_introduzir_charactére(charactére, ficha_n, &ficha);
			ficha_n++;
			continue;
		}

		if ((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo == operação__concessão_objectiva &&
			clave_têr_por_tipo(clave_ficha).pala[2] == charactére) {
			if (clave_têr_por_tipo(clave_lêr).pala[0] == pilha.conteúdo[recúo - 2]) {
				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha = linha_aparar((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha);
				operadôr_linha_n = 0;
				operadôr_n++;

				operação_re_definir(operadôr_n, &(*intérprete).expressão[(*expressão_n)], expectação__nil, operação__valôr, 1);

				pula = 1;
				continue;
			}
			else
			{
				expressão_rastilho_definir(&(*intérprete).expressão[(*expressão_n)], rastilho__carece_concessão_válida);
				(*expressão_n)++;
				break;
			}
		}

		/*
			A linha é o limitante que separa cada linha, quando for atingido, avalia-se a linha
			e seus elementos para averiguar a sua integridade.
		*/
		if (charactére == LINHA_SALTA || charactére == EOF) {
			printf("\n");

			(*intérprete).expressão[(*expressão_n)].índice = (*expressão_n);
			(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha = linha_aparar((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha);

			if (operadôr_n == 0 && (*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n] != LINHA_NIL) {
				expressão_rastilho_definir(&(*intérprete).expressão[(*expressão_n)], rastilho__carece_concessão);
			}
			else if (operadôr_n == 0 && (*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n] == LINHA_NIL) {
				// Se a linha estiver vazia, inteiramente, não mostra mensagens, é irritante.
				(*intérprete).expressão[(*expressão_n)] = expressão_construir_falha();
				expressão_rastilho_definir(&(*intérprete).expressão[(*expressão_n)], rastilho__nil);
				printf("\n");
				break;
			}

			if (operadôr_n == 1) {
				expressão_rastilho_definir(&(*intérprete).expressão[(*expressão_n)], rastilho__carece_valôr);
			}
			if (operadôr_n == 2) {
				expressão_rastilho_definir(&(*intérprete).expressão[(*expressão_n)], rastilho__nil);
			}

			Operação a = operação_construir_falha();

			// Todos as operações que precisam dos valôres completos são validados após o registro de toda a linha.
			if ((a = operação_daExpressão_têrPorTipo(operação__concessão_corredora, (*intérprete).expressão[(*expressão_n)])).índice != ÍNDICE_ERRO) {
				system(operação_daExpressão_têrPorTipo(operação__valôr, (*intérprete).expressão[(*expressão_n)]).linha);
			}

			if ((a = operação_daExpressão_têrPorTipo(operação__concessão_passiva, (*intérprete).expressão[(*expressão_n)])).índice != ÍNDICE_ERRO) {
				Operação caminho = operação_daExpressão_têrPorTipo(operação__valôr, (*intérprete).expressão[(*expressão_n)]);
				char** ficheiro_linhas = ficheiro_lêr(caminho.linha);
				Intérprete* dado = memória_allocar(sizeof(Intérprete));
				dado->expressão = NULL;
				interpretar(ficheiro_linhas, dado);

				(*expressão_n)++;

				intérprete_agregar(dado->expressão, expressão_n, intérprete);
				free(dado);
				continue;
			}

			if ((a = operação_daExpressão_têrPorTipo(operação__concessão_objectiva, (*intérprete).expressão[(*expressão_n)])).índice != ÍNDICE_ERRO) {
				Operação caminho = operação_daExpressão_têrPorTipo(operação__valôr, (*intérprete).expressão[(*expressão_n)]);
				char** ficheiro_linhas = ficheiro_lêr(caminho.linha);
				Intérprete* dado = memória_allocar(sizeof(Intérprete));
				dado->expressão = NULL;
				int dado_n = 0;
				intérprete_agregar((*intérprete).expressão, &dado_n, dado);

				interpretar(ficheiro_linhas, dado);

				Expressão b = expressões_têrPorClave(a.linha, dado->expressão);
				Operação d = operação_daExpressão_têrPorTipo(operação__valôr, b);

				(*intérprete).expressão[(*expressão_n)].operador[caminho.índice].linha = b.operador[d.índice].linha;
				(*expressão_n)++;
				free(dado);
				continue;
			}

			if ((a = operação_daExpressão_têrPorTipo(operação__concessão_selectiva, (*intérprete).expressão[(*expressão_n)])).índice != ÍNDICE_ERRO) {
				Operação caminho = operação_daExpressão_têrPorTipo(operação__valôr, (*intérprete).expressão[(*expressão_n)]);
				char** ficheiro_linhas = ficheiro_lêr(caminho.linha);
				Intérprete* dado = memória_allocar(sizeof(Intérprete));
				dado->expressão = NULL;
				interpretar(ficheiro_linhas, dado);

				Operação operaçãoSeleccionada = lsve_consola_construir_menu(dado->expressão);

				Expressão b = expressões_têrPorClave(operaçãoSeleccionada.linha, dado->expressão);
				Operação d = operação_daExpressão_têrPorTipo(operação__valôr, b);

				(*intérprete).expressão[(*expressão_n)].operador[caminho.índice].linha = b.operador[d.índice].linha;
				(*expressão_n)++;
				free(dado);
				continue;
			}

			(*expressão_n)++;
			continue;
		}

		/*
			Ao conceder uma clave, espera-se uma concessão.
		
			Se a concessão vier antes da clave, será tratada como clave e a concessão não será reconhecida.
			Se a concessão vier antes e depois da clave, a primeira concessão fará parte do nome da clave.
			Se a concessão vier antes, depois da clave, e antes ou depois do valôr, será tratada como valôr
			e/ou nome da clave.
		*/
		if ((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].expectação == expectação__concessão) {
			if (clave_têr_por_tipo(clave_lêr).pala[clave_n] == charactére &&
				clave_têr_por_tipo(clave_ficha).pala[1] == pilha.conteúdo[recúo - 2])
			{
				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha = linha_aparar((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha);

				operadôr_n++;
				operação_re_definir(operadôr_n, &(*intérprete).expressão[(*expressão_n)], expectação__valôr, operação__concessão_directa, 1);

				operadôr_linha_n = 0;

				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].expectação = expectação__nil;
				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo = operação__concessão_objectiva;

				pula = 1;
				continue;
			}

			if (clave_têr_por_tipo(clave_lêr).pala[clave_n] == charactére) {
				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha = linha_aparar((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha);

				operadôr_n++;
				operação_re_definir(operadôr_n, &(*intérprete).expressão[(*expressão_n)], expectação__valôr, operação__concessão_directa, 2);

				operadôr_linha_n = 0;

				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n] = charactére;
				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n + 1] = LINHA_NIL;

				printf("%c", (*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n]);

				if (clave_têr_por_tipo(clave_corrêr).pala[1] == pilha.conteúdo[recúo - 2]) {
					operadôr_linha_n++;
					(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n] = pilha.conteúdo[recúo - 2];
					(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n + 1] = LINHA_NIL;

					(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo = operação__concessão_corredora;

					pula = 1;

					printf("%c", (*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n]);
				}

				if (clave_têr_por_tipo(clave_lêr).pala[clave_n] == pilha.conteúdo[recúo - 2]) {
					operadôr_linha_n++;
					(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n] = pilha.conteúdo[recúo - 2];
					(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n + 1] = LINHA_NIL;

					(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo = operação__concessão_passiva;

					pula = 1;

					printf("%c", (*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n]);
				}

				if (clave_têr_por_tipo(clave_lêr).pala[clave_n] == pilha.conteúdo[recúo - 3]) {
					operadôr_linha_n++;
					(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n] = pilha.conteúdo[recúo - 3];
					(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n + 1] = LINHA_NIL;

					(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo = operação__concessão_selectiva;

					pula = 2;

					printf("%c", (*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n]);
				}
			}

			if ((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo == operação__concedido) (*intérprete).expressão[(*expressão_n)].operador[operadôr_n].expectação = expectação__concedido;
			else if ((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo == operação__concessão_directa ||
				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo == operação__concessão_corredora ||
				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo == operação__concessão_passiva ||
				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo == operação__concessão_selectiva
				) {
				(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha = linha_aparar((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha);
				operadôr_linha_n = 0;
				operadôr_n++;

				operação_re_definir(operadôr_n, &(*intérprete).expressão[(*expressão_n)], expectação__nil, operação__valôr, 1);
				continue;
			}
		}

		/*
			Quando se espera uma concessão, estamos em estado para armazenar
			o concedido.
		*/
		if ((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].expectação == expectação__concedido ||
			(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].expectação == expectação__nil
			)
		{
			linha_introduzir_charactére(charactére, operadôr_linha_n, &(*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha);
			printf("%c", (*intérprete).expressão[(*expressão_n)].operador[operadôr_n].linha[operadôr_linha_n]);

			operadôr_linha_n++;

			if ((*intérprete).expressão[(*expressão_n)].operador[operadôr_n].tipo == operação__concedido) (*intérprete).expressão[(*expressão_n)].operador[operadôr_n].expectação = expectação__concessão;
		}
    }
}


int intérprete_expressões_contar(Intérprete* intérprete) {
	int expressão_n = 0;

	if ((*intérprete).expressão != NULL) {
		while ((*intérprete).expressão[expressão_n].índice == expressão_n) expressão_n++;
	}

	return expressão_n;
}

Intérprete* interpretar(char** linhas, Intérprete* intérprete) {
	int expressão_n = intérprete_expressões_contar(intérprete);

	if (expressão_n == 0) {
		(*intérprete).expressão = memória_re_allocar(sizeof(Expressão), (*intérprete).expressão);
	}

	int linha_n = 0;

	while (linhas[linha_n] != LINHA_NIL)
	{
		(*intérprete).expressão = memória_re_allocar((expressão_n + 1) * sizeof(Expressão), (*intérprete).expressão);
		expressão_interpretar(linhas[linha_n], intérprete, &expressão_n);

		if ((*intérprete).expressão[expressão_n - 1].rastilho.tipo != rastilho__nil) {
			if ((*intérprete).expressão[expressão_n - 1].rastilho.tipo == rastilho__encerro_forçado) {
				printf("\n\n--------------------------------\n");
				printf("Quebra: %s", (*intérprete).expressão[expressão_n - 1].rastilho.erro);
				printf("\n--------------------------------\n\n");

				_set_abort_behavior(0, _WRITE_ABORT_MSG);
				abort();
				break;
			}

			if ((*intérprete).expressão[expressão_n - 1].rastilho.tipo == rastilho__comentário) {
				printf("\n\n--------------------------------\n");
				printf("Ignorância: %s", (*intérprete).expressão[expressão_n - 1].rastilho.erro);
				printf("\n--------------------------------\n\n");

				linha_n++;
				continue;
			}

			if ((*intérprete).expressão[expressão_n - 1].rastilho.tipo == rastilho__carece_concessão) {
				printf("\n\n--------------------------------\n");
				printf("%s", (*intérprete).expressão[expressão_n - 1].rastilho.erro);
				printf("\n--------------------------------\n\n");

				linha_n++;
				continue;
			}

			if ((*intérprete).expressão[expressão_n - 1].rastilho.tipo == rastilho__carece_ficha_válida) {
				printf("\n\n--------------------------------\n");
				printf("Problema: %s", (*intérprete).expressão[expressão_n - 1].rastilho.erro);
				printf("\n--------------------------------\n\n");
				break;
			}

			linha_n++;
		}

		linha_n++;
	}

	return intérprete;
}
