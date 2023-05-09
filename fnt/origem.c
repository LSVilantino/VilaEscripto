#include "tipo.h"
#include "mapa.h"
#include "linha.h"
#include "ficheiro.h"

#include "consola.h"

#include "lsve.h"

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

char signal_de_maior = '>';

int 
main(int** a, char** b) {
    setlocale(LC_CTYPE, "pt_PT.UTF-8");

    // Define saída para usar sequências de consola virtual
    HANDLE lindanteDeSaída = GetStdHandle(STD_OUTPUT_HANDLE);
    if (lindanteDeSaída == INVALID_HANDLE_VALUE) { return GetLastError(); }

    DWORD modoConsola = 0;
    if (!GetConsoleMode(lindanteDeSaída, &modoConsola)) { return GetLastError(); }

    modoConsola |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(lindanteDeSaída, modoConsola)) { return GetLastError(); }

    char* ficheiroIndicador_CaminhoRelativo = "../../ficheiros.txt";

    Mapa* mapaIndicador = ficheiro_conteúdo_mapear(signal_de_maior, ficheiroIndicador_CaminhoRelativo);

    Mapa* mapaEncontrado = mapa_procurar(tipo_char, "construc", mapaIndicador);
    //wprintf(L"\x1b[34;46m\n%S %S %d\r\n", (char*)mapaEncontrado[0].passe, (char*)mapaEncontrado[0].valôr, mapaEncontrado[0].i);
    ConteúdoFicheiro ficheiroConstrucção = ficheiro_lêr(mapaEncontrado[0].valôr);

    char* opçãoSeleccionada = consola_construir_menu(ficha_tratar(signal_de_maior, ficheiroConstrucção.conteúdo));

    int n = 0;
    Mapa** mapaFicheiro = malloc(sizeof(Mapa**));
    while (mapaIndicador)
    {
        mapaFicheiro[n] = ficheiro_conteúdo_mapear(signal_de_maior, mapaIndicador[n].valôr);

        Mapa* mapaConstrucção = mapa_procurar(tipo_char, opçãoSeleccionada, mapaFicheiro[n]);
        mapaIndicador[n].valôr = mapaConstrucção[0].valôr;

        wprintf(L"\x1b[34;46m\n%S %S %d\r\n", (char*)mapaIndicador[n].passe, (char*)mapaIndicador[n].valôr, mapaIndicador[n].i);
        wprintf(L"\x1b[39m");
        wprintf(L"\x1b[49m");

        mapaFicheiro = realloc(mapaFicheiro, (n + 1 * sizeof *mapaFicheiro) * sizeof(Mapa**));
        n = n + 1;
    }

    //printf("%s %s %d\n", (char*)mapa[0].passe, (char*)mapa[0].valôr, mapa[0].i);

	return 0;
}