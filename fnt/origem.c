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

    char* ficheiroPropriedade_caminhoRelativo = "../../propriedade.txt";
    Mapa* mapa_propriedade = ficheiro_conteúdo_mapear(signal_de_maior, ficheiroPropriedade_caminhoRelativo);

    Mapa* mapa_construcção = mapa_procurar(tipo_char, "construc", mapa_propriedade);
    ConteúdoFicheiro ficheiro_construcção = ficheiro_lêr(mapa_construcção[0].valôr);
    char* opçãoSeleccionada_construcção = consola_construir_menu(ficha_tratar(signal_de_maior, ficheiro_construcção.conteúdo));

    // ---------------------------------------------------------------------------------------------------

    char* ficheiroCommando_caminhoRelativo = "../../commando.txt";
    Mapa* mapa_commando = ficheiro_conteúdo_mapear(signal_de_maior, ficheiroCommando_caminhoRelativo);
    char** opções_commando = malloc(sizeof(char**));

    int n_commando = 0;
    while (mapa_commando) {
        if (n_commando == mapa_commando[n_commando].i) {
            opções_commando = realloc(opções_commando, (n_commando + 1 * sizeof *opções_commando) * sizeof(char*));
            opções_commando[n_commando] = strdup(mapa_commando[n_commando].passe);
            n_commando++;
        }
        else break;
    }

    char* opçãoSeleccionada_commando = consola_construir_menu(opções_commando);
    Mapa* mapaOpção_commando = mapa_procurar(tipo_char, opçãoSeleccionada_commando, mapa_commando);

    ConteúdoFicheiro ficheiro_commando = ficheiro_lêr(mapaOpção_commando->valôr);
    char* opçãoSeleccionada_commando_detalhe = consola_construir_menu(ficha_tratar(signal_de_maior, ficheiro_commando.conteúdo));


    int n_propriedade = 0;
    Mapa** mapaFicheiro_construcção = malloc(sizeof(Mapa**));
    while (mapa_propriedade)
    {
        if (n_propriedade == mapa_propriedade[n_propriedade].i) {
            printf("%d %d", n_propriedade, mapa_propriedade[n_propriedade].i);
            mapaFicheiro_construcção = realloc(mapaFicheiro_construcção, (n_propriedade + 1 * sizeof * mapaFicheiro_construcção) * sizeof(Mapa**));
            mapaFicheiro_construcção[n_propriedade] = ficheiro_conteúdo_mapear(signal_de_maior, mapa_propriedade[n_propriedade].valôr);

            Mapa* mapa_tempor = mapa_procurar(tipo_char, opçãoSeleccionada_construcção, mapaFicheiro_construcção[n_propriedade]);

            if (mapa_tempor->valôr != NULL) {
                mapa_propriedade[n_propriedade].valôr = mapa_tempor->valôr;

                printf("\n");
                wprintf(L"\x1b[34;46m%S %S %d", (char*)mapa_propriedade[n_propriedade].passe, (char*)mapa_propriedade[n_propriedade].valôr, mapa_propriedade[n_propriedade].i);
                wprintf(L"\x1b[39m");
                wprintf(L"\x1b[49m");
                printf("\n");
            }
            n_propriedade = n_propriedade + 1;
        }
        else break;
    }

    printf("\n");
    wprintf(L"\x1b[34;46m%S %S %S %S %S %S %S %S", 
        (char*)mapa_procurar(tipo_char, "construir", mapa_commando)->valôr,
        (char*)mapa_procurar(tipo_char, "caminho", mapa_propriedade)->valôr,
        (char*)mapa_procurar(tipo_char, "construc", mapa_propriedade)->valôr,
        (char*)mapa_procurar(tipo_char, "liga", mapa_propriedade)->valôr,
        (char*)mapa_procurar(tipo_char, "reposit", mapa_propriedade)->valôr,
        (char*)mapa_procurar(tipo_char, "receitu", mapa_propriedade)->valôr,
        (char*)mapa_procurar(tipo_char, "sinal", mapa_propriedade)->valôr,
        (char*)mapa_procurar(tipo_char, "subir", mapa_propriedade)->valôr
    );
    wprintf(L"\x1b[39m");
    wprintf(L"\x1b[49m");
    printf("\n");

    //printf("%s %s %d\n", (char*)mapa[0].passe, (char*)mapa[0].valôr, mapa[0].i);

	return 0;
}