﻿#include "consola.h"
#include "linha.h"

#include <stdio.h>
#include <stdlib.h>
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

    int n = 0;
    while (opções[n] != '\0')
    {
        if (n == opçãoSeleccionada) {
            wprintf(L"\x1b[34;46m%S\r\n", opções[n]);
            wprintf(L"\x1b[39m");
            wprintf(L"\x1b[49m");
        }
        else {
            printf("%s\r\n", opções[n]);
        }
        n = n + 1;
    }
}

char*
consola_construir_menu(char** opções) {
    int opção = 0;
    consola_opção_mostrar(opção, opções);

    char* opçãoSeleccionada = "";
    char c = -1;
    while (c != 27) {
        c = getch();

        switch (c) {
        case 72: { printf("CIMA"); opção = opção - 1; consola_opção_mostrar(opção, opções); break; }
        case 80: { printf("BAIXO"); opção = opção + 1; consola_opção_mostrar(opção, opções); break; }
        case 75: { printf("ESQUERDA"); opção = opção - 1; consola_opção_mostrar(opção, opções); break; }
        case 77: { printf("DIREITA"); opção = opção + 1; consola_opção_mostrar(opção, opções); break; }
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