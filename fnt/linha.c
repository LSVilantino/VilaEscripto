#include "linha.h"
#include "lsve.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool 
linha_contém(char* comparadôr, char* linha) {
    int tamanho_comparadôr = 0;
    while (comparadôr[tamanho_comparadôr] != '\0') {
        tamanho_comparadôr++;
    }

    tamanho_comparadôr--;

    int n = 0;
    int n_comparador = 0;
    while (linha[n] != '\0') {
        //printf("(%c//%c) ", linha[n], comparador[n_comparador]);
        if (linha[n] == comparadôr[n_comparador]) {
            //printf("(%d %c/%d %c - %d) ", n, linha[n], n_comparador, comparador[n_comparador], tamanho_comparador);
            if (n_comparador == tamanho_comparadôr) return 1;
            n_comparador++;
        }
        else {
            n_comparador = 0;
        }
        n++;
    }

    return 0;
}

int
linha_charactéres_contar(char* linha) {
    int n = 0;

    for (int i = 0; linha[i] != '\0'; i++) { n = i; }

    return n;
}

int
linha_separador_contar(char separador, char* linha) {
    int n = 1;

    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == separador) {
            n = n + 1;
        }
    }

    return n;
}

char** 
linha_separar(char* separadôr, char* linha) {
    int n = 0;
    int n2 = 0;
    int n3 = 0;

    char** matrizTratada = malloc(sizeof(char*));
    if (matrizTratada == NULL) return matrizTratada;

    char* linhaTratada = "";

    while (linha[n2]) {
        //printf("\n%c _ %s", linha[n2], linha);
        if (linha[n2] != '\0') {
            char* charactéreActual = malloc(2 * sizeof(char));
            charactéreActual[0] = linha[n2];
            charactéreActual[1] = '\0';

            if (linha_contém(separadôr, linhaTratada)) {
                linhaTratada[n3 - linha_charactéres_contar(separadôr) - 1] = '\0';
                matrizTratada[n] = strdup(linhaTratada);

                linhaTratada[0] = '\0';

                n3 = 0;
                n2 = n2 + 1;

                n = n + 1;
                continue;
            }

            strncpy(&linhaTratada[n3], &linha[n2], sizeof(linha[n2]));
            linhaTratada[n3 + 1] = '\0';
            matrizTratada[n] = strdup(linhaTratada);

            if (matrizTratada[n] != NULL) {
                n2 = n2 + 1;
                n3 = n3 + 1;
            }
        }
    }
    //printf("\n0~%s\n1~%s", matrizTratada[0], matrizTratada[1]);
    //printf("\nlinha - %s", linhaTratada);

    return matrizTratada;
}

char* 
linha_aparar(char* linha) {
    int n = 0;

    while (linha[n] == ' ') { n = n + 1; }

    char* linhaTratada = "";
    int i = 0;
    while (linha[n] != '\0') {
        strncpy(&linhaTratada[i], &linha[n], sizeof(linha[n] - 1));

        linhaTratada[i + 1] = '\0';

        //printf("\n%d %d %c %c", i, n, linha[n], linhaTratada[i]);
        n = n + 1;
        i = i + 1;
    }

    int diferença = n - i;
    int índexReal = n - diferença;

    //printf("%d", índexReal);

    while (linhaTratada[índexReal - 1] == ' ' || linhaTratada[índexReal - 1] == '\n' || linhaTratada[índexReal - 1] == '\r' || linhaTratada[índexReal - 1] == '\t') {
        linhaTratada[índexReal - 1] = '\0';
        //printf("\n%d %c", índexReal, linhaTratada[índexReal - 1]);
        índexReal = índexReal - 1;
    }

    return strdup(linhaTratada);
}

char* 
linha_repôr(char* reposição, char* alvo, char* linha) {
    int n = 0;
    int n_lc = 0;
    int n_a = 0;

    int tamanho_alvo = 0;
    while (alvo[tamanho_alvo] != '\0') {
        tamanho_alvo++;
    }

    tamanho_alvo--;

    printf("\n\n");
    while (linha[n] != '\0') {
        printf(" %c-%c ", linha[n], alvo[n_a]);
        if (linha[n] == alvo[n_a]) {
            if (n_a == tamanho_alvo) {
                int n_pós_alvo = n + linha_charactéres_contar(alvo) - 1;
                int n_pré_alvo = n - linha_charactéres_contar(alvo);
                int n_pa = 0;
                int n_linha = n_pós_alvo + n_pa;
                char* linha_cópia = malloc(sizeof(char*));

                while (linha[n_linha] != '\0') {
                    linha_cópia = realloc(linha_cópia, (n_pa + 1 * sizeof(char*)));
                    linha_cópia[n_pa] = linha[n_linha];
                    n_pa++;
                    n_linha++;
                }

                linha[n_pré_alvo] = '\0';

                strcat(linha, reposição);
                strcat(linha, linha_cópia);

                free(linha_cópia);

                n = n_pós_alvo;
                n++;
            }
            n_a++;
        }
        else {
            n_a = 0;
        }
        n++;
    }

    return linha;
}

Mapa* 
linha_matriz_mapear(char** linhas) {
    Mapa* mapa = malloc(sizeof(Mapa*));

    int n = 0;
    while (linhas[n] != '\0') {
        char** linhaSeparada = linha_separar(lsve_linha_separador_procurar(linhas[n]), linhas[n]);
        mapa_introduzir(&mapa, (Mapa) { linha_aparar(linhaSeparada[0]), linha_aparar(linhaSeparada[1]), n });

        printf("%s- %s- %d-\n", (char*)mapa[n].passe, (char*)mapa[n].valôr, mapa[n].i);
        n = n + 1;
    }

    return mapa;
}