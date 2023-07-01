#include "LSVEconsola.h"
#include "linha.h"

#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void
lsve_consola_limpar()
{
	HANDLE lidanteSaída = GetStdHandle(STD_OUTPUT_HANDLE);
	fflush(NULL); // Limpa carga de entrada.

	CONSOLE_SCREEN_BUFFER_INFO consolaInfo;
	COORD início = { 0, 0 };

	// Pega o tamanho do quadro da consola
	if (!GetConsoleScreenBufferInfo(lidanteSaída, &consolaInfo)) { abort(); }

	DWORD tamanho = consolaInfo.dwSize.X * consolaInfo.dwSize.Y;
	DWORD escripto;

	FillConsoleOutputCharacter(lidanteSaída, TEXT(' '), tamanho, início, &escripto); // Preênche consola com vazios.
	FillConsoleOutputAttribute(lidanteSaída, consolaInfo.wAttributes, tamanho, início, &escripto); // Limpa atributos (coloração) da consola.

	SetConsoleCursorPosition(lidanteSaída, início);
}

void
lsve_consola_opção_mostrar(int opçãoSeleccionada, Expressão* expressões) {
#ifdef _WIN32
	lsve_consola_limpar();
#endif

	for (int i = 0; expressões[i].índice == i; i++)
	{
		Operação operação = operação_daExpressão_têrPorTipo(operação__concedido, expressões[i]);
		if (opçãoSeleccionada != i) { printf("%s\n", operação.linha); }
		else {
			printf("\x1b[34;46m%s\n", operação.linha);
			printf("\x1b[39m");
			printf("\x1b[49m");
		}
	}
}

Operação
lsve_consola_construir_menu(Expressão* expressões) {
	int expressão = 0;

	lsve_consola_opção_mostrar(expressão, expressões);

	Operação opçãoSeleccionada = operação_construir_falha();
	int c = -1;
	while (c) {
		c = getc(stdin);

		/*
		* Utiliza - se a tabela de códigos ASCII para a detecção da clave.
		* 72 = ACIMA
		* 80 = ABAIXO
		* 75 = ESQUERDA
		* 77 = DIREITA
		*
		* 13 = ENTRA
		*/

		switch (c) {
		case 27: { printf("ESCAPE"); return operação_construir_falha(); }
		case 72: { printf("CIMA"); expressão--; lsve_consola_opção_mostrar(expressão, expressões); printf("%d ", expressão); break; }
		case 80: { printf("BAIXO"); expressão++; lsve_consola_opção_mostrar(expressão, expressões); printf("%d ", expressão); break; }
		case 75: { printf("ESQUERDA"); expressão--; lsve_consola_opção_mostrar(expressão, expressões); printf("%d ", expressão); break; }
			   //case 77: { printf("DIREITA"); opção++; consola_opção_mostrar(opção, opções); break; }
		case 77: {
			lsve_consola_opção_mostrar(expressão, expressões);
			opçãoSeleccionada = operação_daExpressão_têrPorTipo(operação__concedido, expressões[expressão]);
			printf("ENTRA - %s\n", opçãoSeleccionada.linha);
			goto ciclo_quebrar;
		}
		case 13: {
			lsve_consola_opção_mostrar(expressão, expressões);
			opçãoSeleccionada = operação_daExpressão_têrPorTipo(operação__concedido, expressões[expressão]);
			printf("ENTRA - %s\n", opçãoSeleccionada.linha);
			goto ciclo_quebrar;
		}
		default: { break; }
		}
	}

ciclo_quebrar:
	return opçãoSeleccionada;
}
