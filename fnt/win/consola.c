#include "consola.h"
#include "linha.h"

#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void
consola_limpar()
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
consola_opção_mostrar(int opçãoSeleccionada, char** opções) {
	consola_limpar();

	for (int i = 0; opções[i] != LINHA_NIL; i++)
	{
		if (opçãoSeleccionada != i) { printf("%s\n", opções[i]); }
		else {
			printf("\x1b[34;46m%s\n", opções[i]);
			printf("\x1b[39m");
			printf("\x1b[49m");
		}
	}
}

char*
consola_construir_menu(char** opções) {
	int opção = 0;

	consola_opção_mostrar(opção, opções);

	char* opçãoSeleccionada = "";
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
		case 27: { printf("ESCAPE"); return NULL; }
		case 72: { printf("CIMA"); opção--; consola_opção_mostrar(opção, opções); printf("%d ", opção); break; }
		case 80: { printf("BAIXO"); opção++; consola_opção_mostrar(opção, opções); printf("%d ", opção); break; }
		case 75: { printf("ESQUERDA"); opção--; consola_opção_mostrar(opção, opções); printf("%d ", opção); break; }
			   //case 77: { printf("DIREITA"); opção++; consola_opção_mostrar(opção, opções); break; }
		case 77: {
			consola_opção_mostrar(opção, opções);
			opçãoSeleccionada = opções[opção];
			printf("ENTRA - %s\n", opçãoSeleccionada);
			goto ciclo_quebrar;
		}
		case 13: {
			consola_opção_mostrar(opção, opções);
			opçãoSeleccionada = opções[opção];
			printf("ENTRA - %s\n", opçãoSeleccionada);
			goto ciclo_quebrar;
		}
		default: { break; }
		}
	}

ciclo_quebrar:
	return opçãoSeleccionada;
}
