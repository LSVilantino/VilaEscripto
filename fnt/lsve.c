#include "lsve.h"
#include "linha.h"

#include <stdio.h>
#include <stdlib.h>

char**
ficha_tratar(char** linhas) {
    char** fichaTítulo = malloc(sizeof(char*));

    int n = 0;
    while (linhas) {
        if (linhas[n] != NULL) {
            fichaTítulo = realloc(fichaTítulo, (n + 1 * sizeof(fichaTítulo)) * sizeof(char*));
            fichaTítulo[n] = linha_aparar(linha_separar(linha_separador_procurar(linhas[n]), linhas[n])[0]);
            n = n + 1;
        }
        else break;
    }

    return fichaTítulo;
}

char**
mapa_a_matriz_char(char* separador, Mapa* mapa) {
    char** linhas = malloc(sizeof(char*));

    int n = 0;
    while (mapa) {
        if (mapa[n].valôr != NULL) {
            char* linhaTratada = "";
            strcat(linhaTratada, mapa[n].valôr);
            strcat(linhaTratada, mapa[n].passe);

            linhas[n] = linha_aparar(linha_separar(separador, linhaTratada)[0]);
            linhas = realloc(linhas, (n + 1 * sizeof(linhas)) * sizeof(char*));
            n = n + 1;
        }
        else break;
    }

    return linhas;
}