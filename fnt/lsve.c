#include "lsve.h"
#include "linha.h"

#include <stdio.h>
#include <stdlib.h>

char**
ficha_tratar(char separador, char** linhas) {
    char** opçõesConstrucção = malloc(sizeof(char*));

    int n = 0;
    while (linhas) {
        if (linhas[n] != NULL) {
            opçõesConstrucção[n] = linha_aparar(linha_separar(separador, linhas[n])[0]);
            opçõesConstrucção = realloc(opçõesConstrucção, (n + 1 * sizeof(opçõesConstrucção)) * sizeof(char*));
            n = n + 1;
        }
        else break;
    }

    return opçõesConstrucção;
}

char**
mapa_a_matriz_char(char separador, char** linhas) {
    char** opçõesConstrucção = malloc(sizeof(char*));

    int n = 0;
    while (linhas) {
        if (linhas[n] != NULL) {
            opçõesConstrucção[n] = linha_aparar(linha_separar(separador, linhas[n])[0]);
            opçõesConstrucção = realloc(opçõesConstrucção, (n + 1 * sizeof(opçõesConstrucção)) * sizeof(char*));
            n = n + 1;
        }
        else break;
    }

    return opçõesConstrucção;
}