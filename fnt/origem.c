#include "tipo.h"
#include "mapa.h"
#include "linha.h"
#include "ficheiro.h"
#include "consola.h"
#include "lsve.h"

#include "desbraga.h"

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int 
main(int** _, char** argumentos) {
    setlocale(LC_CTYPE, "pt_PT.UTF-8");

    // Define saída para usar sequências de consola virtual
    HANDLE lindanteDeSaída = GetStdHandle(STD_OUTPUT_HANDLE);
    if (lindanteDeSaída == INVALID_HANDLE_VALUE) { return GetLastError(); }

    DWORD modoConsola = 0;
    if (!GetConsoleMode(lindanteDeSaída, &modoConsola)) { return GetLastError(); }

    modoConsola |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(lindanteDeSaída, modoConsola)) { return GetLastError(); }

    char* ficheiro_utilizador = argumentos[1];
    char* ficheiro_desbraga = argumentos[2];

    LSVEMapa* mapa_desbraga;
    if (ficheiro_desbraga != '\0') {
        mapa_desbraga = &(LSVEMapa) { { "desbraga", ficheiro_desbraga, 0 }, clave_lêr_e_escolher };

        mapa_desbraga->valôr = lsve_ficheiro_valôr_tratar(tipo_char, mapa_desbraga->passe, mapa_desbraga);
        desbraga_convenção = mapa_desbraga->valôr;
    }

    char* ficheiroPropriedade_caminho = strdup(ficheiro_utilizador);
    LSVEMapa* mapa_propriedade = lsve_ficheiro_conteúdo_mapear(ficheiroPropriedade_caminho);

    // ---------------------------------------------------------------------------------------------------

    int n_propriedade = 0;
    while (mapa_propriedade)
    {
        if (n_propriedade == mapa_propriedade[n_propriedade].i) {
            printf("%d %d %s", n_propriedade, mapa_propriedade[n_propriedade].i, (char*)mapa_propriedade[n_propriedade].valôr);
            mapa_propriedade[n_propriedade].valôr = lsve_ficheiro_valôr_tratar(tipo_char, mapa_propriedade[n_propriedade].passe, mapa_propriedade);

            if (linha_compara(desbraga_convenção, têr_desbraga_convenção__ficheiro_expôr_valôr_tratado())) {
                printf("\n");
                wprintf(L"\x1b[34;46m%S %S %d", (char*)mapa_propriedade[n_propriedade].passe, (char*)mapa_propriedade[n_propriedade].valôr, mapa_propriedade[n_propriedade].i);
                wprintf(L"\x1b[39m");
                wprintf(L"\x1b[49m");
                printf("\n");
            }

            n_propriedade++;
        }
        else break;
    }

    printf("\n");
    wprintf(L"\x1b[34;46m%S %S %S %S %S %S %S %S %S", 
        (char*)lsve_mapa_procurar(tipo_char, "caminho", mapa_propriedade)->valôr,
        (char*)lsve_mapa_procurar(tipo_char, "sinal", mapa_propriedade)->valôr,
        (char*)lsve_mapa_procurar(tipo_char, "receitu", mapa_propriedade)->valôr,
        (char*)lsve_mapa_procurar(tipo_char, "construc", mapa_propriedade)->valôr,
        (char*)lsve_mapa_procurar(tipo_char, "liga", mapa_propriedade)->valôr,
        (char*)lsve_mapa_procurar(tipo_char, "reposit", mapa_propriedade)->valôr,
        (char*)lsve_mapa_procurar(tipo_char, "subir", mapa_propriedade)->valôr,
        (char*)lsve_mapa_procurar(tipo_char, "construir", mapa_propriedade)->valôr,
        (char*)lsve_mapa_procurar(tipo_char, "repositório", mapa_propriedade)->valôr
    );
    wprintf(L"\x1b[39m");
    wprintf(L"\x1b[49m");
    printf("\n");

    free(mapa_propriedade);
    free(mapa_desbraga);

	return EXIT_SUCCESS;
}
