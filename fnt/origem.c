#include "lsve/mapa.h"
#include "lsve/general.h"
#include "lsve/tipo.h"

#include "lsve/desbraga.h"

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

int main(int** ignorado, char** argumentos) {
    setlocale(LC_CTYPE, "pt_PT.UTF-8");

    char* ficheiroLSVECaminho = argumentos[1];
    char* ficheiroDesbragaCaminho = argumentos[2];

    LSVEMapa mapaDesbraga;
    if (ficheiroDesbragaCaminho != '\0') {
        mapaDesbraga = (LSVEMapa) { { "desbraga", ficheiroDesbragaCaminho, 0 }, clave_lêr_e_escolher };

        mapaDesbraga.valôr = lsve_valôr_tratar(ct_char, mapaDesbraga.clave, &mapaDesbraga);
        desbraga_convenção = mapaDesbraga.valôr;
    }

    return 0;
}
