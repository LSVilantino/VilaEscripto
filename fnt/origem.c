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

    ficheiro_linha_tratar("teste >>> ..\\..\\..\\escripto\\acólito\\teste.txt");


    /*if (linha_contém(">>>", "repositório >>> ..\\..\\..\\escripto\\acólito\\repositório.txt") == 1) {
        printf("Contém");
    }
    else printf("Não contém");*/


    return 0;

    char* ficheiroPropriedade_caminhoRelativo = "../../propriedade.txt";
    Mapa* mapa_propriedade = ficheiro_conteúdo_mapear(ficheiroPropriedade_caminhoRelativo);

    Mapa* mapa_construcção = mapa_procurar(tipo_char, "construc", mapa_propriedade);
    ConteúdoFicheiro ficheiro_construcção = ficheiro_lêr(mapa_construcção[0].valôr);
    char* opçãoSeleccionada_construcção = consola_construir_menu(ficha_tratar(ficheiro_construcção.conteúdo));

    // ---------------------------------------------------------------------------------------------------

    int n_propriedade = 0;
    Mapa** mapaFicheiro_construcção = malloc(sizeof(Mapa**));
    while (mapa_propriedade)
    {
        if (n_propriedade == mapa_propriedade[n_propriedade].i) {
            printf("%d %d", n_propriedade, mapa_propriedade[n_propriedade].i);
            mapaFicheiro_construcção = realloc(mapaFicheiro_construcção, (n_propriedade + 1 * sizeof * mapaFicheiro_construcção) * sizeof(Mapa**));
            mapaFicheiro_construcção[n_propriedade] = ficheiro_conteúdo_mapear(mapa_propriedade[n_propriedade].valôr);
            //ficheiro_linha_tratar(mapa_propriedade[n_propriedade].valôr);
            //ficheiro_conteúdo_mapear(signal_de_maior, mapa_propriedade[n_propriedade].valôr);

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
        (char*)mapa_procurar(tipo_char, "construir", mapa_propriedade)->valôr,
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