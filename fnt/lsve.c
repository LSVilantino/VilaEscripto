#include "lsve.h"
#include "linha.h"
#include "ficheiro.h"
#include "consola.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char**
lsve_linha_separar(char* separadôr, char* linha) {
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

            //printf("%c", charactéreActual[0]);
            if (linha_contém(separadôr, linhaTratada)) {
                linhaTratada[n3 - linha_charactéres_contar(separadôr) - 1] = '\0';
                matrizTratada[n] = strdup(linhaTratada);

                //printf("\n1%s1", matrizTratada[n]);
                
                n = n + 1;

                matrizTratada[n] = strdup(separadôr);
                //printf("\n2%s2\n", matrizTratada[n]);

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

char**
lsve_ficha_tratar(char** linhas) {
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

char*
lsve_ficheiro_linha_tratar(LSVEMapa linha) {
    char* separadôr = "";

    printf("\n\n~");
    printf(linha.valôr);
    printf("~\n\n");

    separadôr = linha_separador_procurar(linha.separadôr);

    if (separadôr == clave_lêr_e_escolher) {
        ConteúdoFicheiro cf = ficheiro_lêr(linha.valôr);
        Mapa* mapa_propriedade = linha_matriz_mapear(cf.conteúdo);

        char** mapa_propriedade_matriz = malloc(sizeof(char**));

        int n = 0;
        while (mapa_propriedade[n].i == n) {
            mapa_propriedade_matriz = realloc(mapa_propriedade_matriz, (n + 1 * sizeof * mapa_propriedade_matriz) * sizeof(char*));
            mapa_propriedade_matriz[n] = mapa_propriedade[n].passe;
            printf("%s ", mapa_propriedade_matriz[n]);
            n++;
        }

        char* opçãoSeleccionada_construcção = consola_construir_menu(mapa_propriedade_matriz);
        if (opçãoSeleccionada_construcção == NULL) return opçãoSeleccionada_construcção;

        LSVEMapa* mapa_seleccionado;
        Mapa* mapa_seleccionado_val = mapa_procurar(tipo_char, opçãoSeleccionada_construcção, mapa_propriedade);
        mapa_seleccionado = &(LSVEMapa) { mapa_seleccionado_val->passe, mapa_seleccionado_val->valôr, mapa_seleccionado_val->i, "NIL"};

        return lsve_ficheiro_linha_tratar(*mapa_seleccionado);
    } 
    else if (separadôr == clave_lêr_e_avançar) {
    } 
    else if (separadôr == clave_lêr) {
        printf(linha.passe);
        return strdup(linha.valôr);
    }

    return linha.valôr;
}

LSVEMapa*
lsve_mapa_construir() {
    LSVEMapa* mapa = malloc(sizeof(LSVEMapa*));

    mapa[0].passe = "NIL";
    mapa[0].separadôr = "NIL";
    mapa[0].valôr = "NIL";
    mapa[0].i = 1; // Deve ser mantido a zero, por conta das comparações do método de introducção.

    //printf("%s %s %d\n", (char*)mapa[0].passe, (char*)mapa[0].valôr, mapa[0].i);
    return mapa;
}

LSVEMapa*
lsve_ficheiro_conteúdo_mapear(char* ficheiroCaminho) {
    ConteúdoFicheiro ficheiroConteúdo = ficheiro_lêr(ficheiroCaminho);
    LSVEMapa* mapa = (LSVEMapa*) mapa_construir();

    printf("\n\n%s - %d \n\n", ficheiroCaminho, ficheiroConteúdo.quantidade_conteúdo);

    int n = 0;
    while (ficheiroConteúdo.conteúdo) {
        if (n != ficheiroConteúdo.quantidade_conteúdo) {
            //printf(ficheiroConteúdo.conteúdo[n]);
            char** linhaSeparada = lsve_linha_separar(linha_separador_procurar(ficheiroConteúdo.conteúdo[n]), ficheiroConteúdo.conteúdo[n]);
            lsve_mapa_introduzir(&mapa, (LSVEMapa) { { linha_aparar(linhaSeparada[0]), linha_aparar(linhaSeparada[2]), n }, linha_aparar(linhaSeparada[1]) });

            printf("%s- %s- %s- %d-\n", (char*)mapa[n].passe, (char*)mapa[n].separadôr, (char*)mapa[n].valôr, mapa[n].i);

            //system("cls");
            //// Try some Set Graphics Rendition (SGR) terminal escape sequences
            //wprintf(L"\x1b[31mThis text has a red foreground using SGR.31.\r\n");
            //wprintf(L"\x1b[1mThis text has a bright (bold) red foreground using SGR.1 to affect the previous color setting.\r\n");
            //wprintf(L"\x1b[mThis text has returned to default colors using SGR.0 implicitly.\r\n");
            //wprintf(L"\x1b[34;46mThis text shows the foreground and background change at the same time.\r\n");
            //wprintf(L"\x1b[0mThis text has returned to default colors using SGR.0 explicitly.\r\n");
            //wprintf(L"\x1b[31;32;33;34;35;36;101;102;103;104;105;106;107mThis text attempts to apply many colors in the same command. Note the colors are applied from left to right so only the right-most option of foreground cyan (SGR.36) and background bright white (SGR.107) is effective.\r\n");
            //wprintf(L"\x1b[39mThis text has restored the foreground color only.\r\n");
            //wprintf(L"\x1b[49mThis text has restored the background color only.\r\n");
            n = n + 1;
        }
        else break;
    }

    return mapa;
}


void
lsve_mapa_introduzir(LSVEMapa** mapa, LSVEMapa valôr) {
    int i = 0;
    while ((*mapa)[i].i == i) { i = i + 1; }
    if (valôr.i != i) valôr.i = i;

    *mapa = realloc((*mapa), (i + 1 * sizeof(*mapa)) * sizeof(valôr)); // n + 1 é necessário pela 'regra do múltiplo a índice 0'.
    (*mapa)[i] = valôr;
}

LSVEMapa*
lsve_mapa_procurar(Tipo tipo, void* procura, LSVEMapa* mapa) {
    int i = 0;

    switch (tipo)
    {
    case tipo_char:
        while (mapa[i].i == i) {
            //printf("%s %s", (char*)mapa[i].passe, (char*)procura);
            if (strcmp((char*)mapa[i].passe, (char*)procura) == 0) return &mapa[i];
            i = i + 1;
        }
        break;
    default: break;
    }

    return NULL;
}

char**
lsve_mapa_a_matriz_char(LSVEMapa* mapa) {
    char** linhas = malloc(sizeof(char*));

    int n = 0;
    while (mapa) {
        if (mapa[n].valôr != NULL) {
            char* linhaTratada = "";
            strcat(linhaTratada, mapa[n].passe);
            strcat(linhaTratada, mapa[n].separadôr);
            strcat(linhaTratada, mapa[n].valôr);

            linhas[n] = linha_aparar(linha_separar(mapa[n].separadôr, linhaTratada)[0]);
            linhas = realloc(linhas, (n + 1 * sizeof(linhas)) * sizeof(char*));
            n = n + 1;
        }
        else break;
    }

    return linhas;
}
