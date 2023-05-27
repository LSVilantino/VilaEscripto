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

bool linha_compara(char* comparadôr, char* linha) {
    int linha_t = linha_charactéres_contar(linha) - 1;
    int comparadôr_t = linha_charactéres_contar(comparadôr) - 1;

    if (linha_t < comparadôr_t) return 0;

    //printf("\n\n(/%s/%s\\)\n\n", linha, comparadôr);

    int n = 0;
    while (linha[n] != '\0') {
        //printf("(/%c―%c\\) ", linha[n], comparadôr[n]);
        if (comparadôr[n] == linha[n]) {
            if (n == linha_t) return 1;
            n++;
        }
        else return 0;
    }

    return 0;
}

int
linha_charactéres_contar(char* linha) {
    int n = 0;
    while(linha[n] != '\0') n++;

    return n;
}

int
linha_separadôr_contar(char* separador, char* linha) {
    int separadôr_t = linha_charactéres_contar(separador) - 1;
    int separadôr_qtd = 0;
    int n = 0;

    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == separador[n]) {
            if (n == separadôr_t) {
                separadôr_qtd++;
            }
            n++;
        }
        else n = 0;
    }

    return n;
}

char* 
linha_complementar(char* complemento, char* linha) {
    if (complemento == '\0') return linha;

    int linha_t = linha_charactéres_contar(linha);
    int complemento_t = linha_charactéres_contar(complemento);
    int total_t = linha_t + complemento_t;

    char* resultado = memória_allocar(total_t + 1 * sizeof(char));

    int linha_n = 0;
    while (linha_n != linha_t) {
        resultado[linha_n] = linha[linha_n];
        resultado[linha_n + 1] = '\0';
        linha_n++;
    }

    int complemento_n = 0;
    while (complemento_n != complemento_t) {
        resultado[linha_n] = complemento[complemento_n];
        resultado[linha_n + 1] = '\0';
        linha_n++;
        complemento_n++;
    }

    return resultado;
}

char** 
linha_separar(char* separadôr, char* linha) {
    int n = 0;
    int n2 = 0;
    int n3 = 0;

    char** matrizTratada = malloc(2 * sizeof(char*));
    if (matrizTratada == NULL) return matrizTratada;

    char* linhaTratada = "";

    while (linha[n2] != '\0') {
        //printf("\n%c _ %s", linha[n2], linha);
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
    //printf("\n0~%s\n1~%s", matrizTratada[0], matrizTratada[1]);
    //printf("\nlinha - %s", linhaTratada);

    return matrizTratada;
}

char* 
linha_aparar(char* linha) {
    //int n = 0; // Número à linha a partir da falta de espaço inicial.
    //int i = 0;

    //while (linha[n] == ' ') { n = n + 1; }

    //char* linhaTratada = malloc(linha_charactéres_contar(linha) + 1 * sizeof(char));
    //while (linha[n] != '\0') {

    //    linhaTratada[i] = linha[n];
    //    linhaTratada[i + 1] = '\0';

    //    printf("\n%d %c %d %c", i, linhaTratada[i], n, linha[n]);
    //    //printf("\n%s\n", linhaTratada);

    //    n++;
    //    i++;
    //}

    //printf("linhaTratada -%s", linhaTratada);

    //int diferença = n - i;
    //int índexReal = n - diferença;

    ////printf("%d", índexReal);

    //while (linhaTratada[índexReal - 1] == ' ' || linhaTratada[índexReal - 1] == '\n' || linhaTratada[índexReal - 1] == '\r' || linhaTratada[índexReal - 1] == '\t') {
    //    índexReal--;
    //    linhaTratada = memória_re_allocar(índexReal, linhaTratada);
    //    linhaTratada[índexReal] = '\0';
    //    //printf("\n%d %c", índexReal, linhaTratada[índexReal - 1]);
    //}


    while (*linha == ' ') linha++;

    char* término = linha + linha_charactéres_contar(linha) - 1;
    while (término > linha && *término == ' ' || *término == '\n' || *término == '\r' || *término == '\t') término--;
    término[1] = '\0';

    printf("%s\n", linha);

    return linha;
}

char* 
linha_cortar(int de, int até, char* linha) {
    if (de > até || de == até) return '\0';
    char* resultado = malloc((até - de + 1) * sizeof(char));

    int n = 0;
    while (linha) {
        if ((de + n) != até) {
            resultado[n] = linha[de + n];
            resultado[n + 1] = '\0';
            n++;
        }
        else break;
    }

    return resultado;
}

char* 
linha_repôr(char* reposição, char* alvo, char* linha) {
    int n = 0;
    int n_a = 0;
    int alvo_t = linha_charactéres_contar(alvo) - 1;
    int linha_t_i = linha_charactéres_contar(linha);

    printf("\n\n");
    while (linha[n] != '\0') {
        if (linha[n] == alvo[n_a]) {
            //printf(" %c-%c ", linha[n], alvo[n_a]);
            if (n_a == alvo_t) {
                int n_pós_alvo = n + 1;
                int n_pré_alvo = n - alvo_t;

                printf(" %d-%d ", n_pós_alvo, linha_t_i);

                char* linha_cópia = linha_cortar(n_pós_alvo, linha_t_i, linha);

                printf("\n\n");
                printf("YYYYYYYY%s", linha_cópia);

                linha[n_pré_alvo] = '\0';

                linha = linha_complementar(reposição, linha);
                linha = linha_complementar(linha_cópia, linha);

                linha_t_i = linha_charactéres_contar(linha);

                linha[linha_t_i] = '\0';

                printf("\n\n");
                printf(linha);

                free(linha_cópia);

                n_a = 0;
                continue;
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
