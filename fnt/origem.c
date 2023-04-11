#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <incls-win.h>

int n = 0;

char** ficheiro_lêr(WIN32_FIND_DATA ficheiro) {
    n = 0;

    char** linhas;
    char* porção = "";
    FILE* ficheiroLido = fopen("C:\\Users\\des\\escripto\\acólito\\ficheiro-construcção.txt", "r");

    if (ficheiroLido)
    {
        while (fgets(porção, 256, ficheiroLido)) {
            //printf("%s", porção);
            linhas[n] = malloc(sizeof(sizeof(char*) + porção));
            linhas[n] = porção;
            printf("%s", linhas[n]);

            n++;
        }

        free(linhas);
        fclose(ficheiroLido);

        return porção;
    }

    return linhas;
}

int main() {
    setlocale(LC_CTYPE, "pt_PT.UTF-8");

	WIN32_FIND_DATA ficheiro;

    ficheiro_lêr(ficheiro);

    for (int i = 0; i >= n; i++) {
    }

	return 0;
}