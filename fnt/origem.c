#include "lsve/mapa.h"
#include "lsve/general.h"
#include "lsve/tipo.h"

#include "lsve/desbraga.h"
#include "lsve/ficheiro.h"

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

int main(int** ignorado, char** argumentos) {
    SetConsoleOutputCP(65001);
    setlocale(LC_CTYPE, "pt_PT.UTF-8");

    char* ficheiroLSVECaminho = argumentos[1];

    if (ficheiroLSVECaminho == '\0') {
        printf("\nDá-me um ficheiro para lêr.");
        return -1; // Sem ficheiros a ler, sem operação.
    }

    char* ficheiroDesbragaCaminho = argumentos[2];

    if (ficheiroDesbragaCaminho != '\0') {
        ficheiro_lêr(ficheiroDesbragaCaminho);
        //desbraga_convenção = mapaDesbraga.valôr;
    }

    return 0;
}
