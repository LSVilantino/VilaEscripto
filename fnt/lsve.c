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

    char** matrizTratada = memória_allocar(2 * sizeof(char*));
    // Alloca-se 2 linhas, com uma só o programa fecha, por algum motivo que desconheço. 
    /* 
    Talvez só não seja memória o suficiente para a declaração, mas não está de acordo com o normal,
    pode haver algo incorrecto com allocações anteriôres no programa, nada aparente, 
    suspeito do método de leitura de ficheiros.

    Actualização: Eu eliminei a allocação de 2 linhas e parece ter funcionado sem motivo aparente, 
    não se sabe a causa dos fechines anteriôres, manterei só por segurança.
     */
    if (matrizTratada == NULL) return matrizTratada;

    char* linhaTratada = memória_allocar(sizeof(char));

    while (linha[n2]) {
        //printf("\n%c _ %s %s", linha[n2], separadôr, linha);
        if (linha[n2] != '\0') {
            char* charactéreActual = memória_allocar(2 * sizeof(char));
            charactéreActual[0] = linha[n2];
            charactéreActual[1] = '\0';

            //printf("%c", charactéreActual[0]);
            if (linha_contém(separadôr, linhaTratada)) {
                //printf(linhaTratada);
                linhaTratada[(n3 - linha_charactéres_contar(separadôr)) - 1] = '\0';
                matrizTratada[n] = strdup(linhaTratada);

                //printf("\n1-%s-1", matrizTratada[n]);
                
                n++;

                matrizTratada[n] = strdup(separadôr);
                //printf("\n2-%s-2\n", matrizTratada[n]);

                linhaTratada[0] = '\0';

                n3 = 0;
                n2 = n2 + 1;

                n++;
                continue;
            }

            strncpy(&linhaTratada[n3], &linha[n2], sizeof(linha[n2]));
            linhaTratada[n3 + 1] = '\0';
            matrizTratada[n] = strdup(linhaTratada);

            if (matrizTratada[n] != NULL) {
                n2++;
                n3++;
            }
        }
    }
    //printf("\n0~%s\n1~%s", matrizTratada[0], matrizTratada[1]);
    //printf("\nlinha - %s", linhaTratada);

    return matrizTratada;
}

char*
lsve_linha_separador_procurar(char* linha) {
    if (linha_contém(clave_lêr_e_escolher, linha)) return clave_lêr_e_escolher;
    else if (linha_contém(clave_corrêr, linha)) return clave_corrêr;
    else if (linha_contém(clave_lêr_avançar_e_procurar, linha)) return clave_lêr_avançar_e_procurar;
    else if (linha_contém(clave_lêr_e_avançar, linha)) return clave_lêr_e_avançar;
    else if (linha_contém(clave_lêr, linha)) return clave_lêr;

    return NULL;
}

char**
lsve_ficha_tratar(char** linhas) {
    char** fichaTítulo = memória_allocar(sizeof(char*));

    int n = 0;
    while (linhas) {
        if (linhas[n] != NULL) {
            fichaTítulo = realloc(fichaTítulo, (n + 1 * sizeof(fichaTítulo)) * sizeof(char*));
            fichaTítulo[n] = linha_aparar(linha_separar(lsve_linha_separador_procurar(linhas[n]), linhas[n])[0]);
            n = n + 1;
        }
        else break;
    }

    return fichaTítulo;
}

char*
lsve_ficheiro_valôr_tratar(Tipo clave_tipo, void* clave, LSVEMapa* propriedades) {
    char* separadôr;

    printf("\n\n~");
    printf((char*)clave);
    printf("~\n\n"); 

    LSVEMapa mapa = *lsve_mapa_procurar(clave_tipo, clave, propriedades);
    printf("%s- %s- %s- %d-\n", (char*)mapa.passe, (char*)mapa.separadôr, (char*)mapa.valôr, mapa.i);
    mapa = lsve_ficheiro_valôr_tratar_variável(clave_tipo, clave, mapa, propriedades);

    separadôr = lsve_linha_separador_procurar(mapa.separadôr);

    if (separadôr == clave_corrêr) {
        system(mapa.valôr);

        return (char*) mapa.valôr;
    }
    else if (separadôr == clave_lêr_e_escolher) {
        //ConteúdoFicheiro cf = ficheiro_lêr(linha_aparar(mapa.valôr));
        //LSVEMapa* mapa_propriedade = lsve_linha_matriz_mapear(cf); // problema

        LSVEMapa* mapa_propriedade = lsve_ficheiro_conteúdo_mapear(linha_aparar(mapa.valôr)); // problema
        char** mapa_propriedade_matriz = memória_allocar(2 * sizeof(char*));

        int n = 0;
        while (mapa_propriedade[n].i == n) {
            mapa_propriedade_matriz = realloc(mapa_propriedade_matriz, (n + 1 * sizeof * mapa_propriedade_matriz) * sizeof(char*));
            mapa_propriedade_matriz[n] = strdup(mapa_propriedade[n].passe);
            //printf("%s %s\n", (char*)mapa_propriedade[n].valôr, mapa_propriedade_matriz[n]);
            n++;
        }

        char* opçãoSeleccionada_construcção = consola_construir_menu(mapa_propriedade_matriz);
        if (opçãoSeleccionada_construcção == NULL) return opçãoSeleccionada_construcção;

        LSVEMapa* mapa_seleccionado = lsve_mapa_procurar(clave_tipo, opçãoSeleccionada_construcção, mapa_propriedade);
        mapa_seleccionado->i = 0;
        // Não eliminas esta linha! Durante a comparação na busca, manipula o algorítmo que inicia procura por valôr 0.
        // 
        // Ao seleccionar o mapa aqui, têm-se o número da ordem escolhida. Se removeres esta linha, somente a primeira 
        // opção será válida.

        mapa.valôr = lsve_ficheiro_valôr_tratar(clave_tipo, mapa_seleccionado->passe, mapa_propriedade);
        free(mapa_propriedade_matriz);
        free(mapa_propriedade);

        return strdup(mapa.valôr);
    }
    else if (separadôr == clave_lêr_avançar_e_procurar) {
        printf(mapa.passe);
        return strdup(mapa.valôr);
    }
    else if (separadôr == clave_lêr_e_avançar) {
        printf(mapa.passe);
        return strdup(mapa.valôr);
    }
    else if (separadôr == clave_lêr) {
        printf(mapa.passe);
        return strdup(mapa.valôr);
    }

    return strdup(mapa.valôr);
}

LSVEMapa 
lsve_ficheiro_valôr_tratar_variável(Tipo clave_tipo, void* clave, LSVEMapa mapa, LSVEMapa* propriedades) {
    bool seAbre = 0;
    bool seFecha = 0;

ciclo_volta:
    int n = 0;
    char* commando = (char*)mapa.valôr;

    char* clave_commando = memória_allocar(sizeof(char)); // Nome da clave do commando.
    char* clave_reposição = memória_allocar(2 * sizeof(char)); // Nome da clave, incluso os sinais, que será reposta.

    if (linha_contém("$(", mapa.valôr)) {

        while (commando[n] != '\0')
        {
            printf("%c", commando[n]);
            if (commando[n] == '$' && commando[n + 1] == '(') {
                int n_reposição = 0;
                seAbre = 1;

                printf("%c", commando[n + 1]);

                n += 2;

                clave_reposição = linha_complementar("$(", clave_reposição);

                int n_clave = 0;
                while (commando[n]) {
                    printf("%c", commando[n]);
                    if (commando[n] == ')') {
                        seFecha = 1;

                        clave_reposição = linha_complementar(clave_commando, clave_reposição);
                        clave_reposição = linha_complementar(")", clave_reposição);


                        printf("\n%s", clave_commando);
                        LSVEMapa mapa_corrida = *lsve_mapa_procurar(clave_tipo, clave_commando, propriedades);
                        printf("\n\n%s- %s- %s- %d-\n", (char*)mapa_corrida.passe, (char*)mapa_corrida.separadôr, (char*)mapa_corrida.valôr, mapa_corrida.i);

                        mapa.valôr = linha_repôr(mapa_corrida.valôr, clave_reposição, mapa.valôr);

                        printf("\n\n");
                        printf(mapa.valôr);

                        goto ciclo_volta;
                    }

                    clave_commando = realloc(clave_commando, (n_clave + 1 * sizeof(char)));
                    clave_commando[n_clave] = commando[n];
                    clave_commando[n_clave + 1] = '\0';

                    n_clave++;
                    n++;
                }
            }
            n++;
        }
    }

    return mapa;
}

void
lsve_mapa_construir(LSVEMapa** mapa) {
    *mapa = memória_allocar(2 * sizeof(LSVEMapa));

    (*mapa)[0].passe = "NIL";
    (*mapa)[0].separadôr = "NIL";
    (*mapa)[0].valôr = "NIL";
    (*mapa)[0].i = 1; // Deve ser mantido a um, por conta das comparações do método de introducção.

    //printf("%s %s %d\n", (char*)(*mapa)[0].passe, (char*)(*mapa)[0].valôr, (*mapa)[0].i);
}

LSVEMapa*
lsve_ficheiro_conteúdo_mapear(char* ficheiroCaminho) {
    ConteúdoFicheiro cf = ficheiro_lêr(ficheiroCaminho);
    printf("\n\n-%s- %d-\n\n", ficheiroCaminho, cf.quantidade_conteúdo);

    LSVEMapa* mapa;
    LSVEMapa mapa_introductôr = { 0 };
    char* separadôr;
    char** linhaSeparada;

    lsve_mapa_construir(&mapa);

    int n = 0;
    while (cf.quantidade_conteúdo != n) {
        //printf(cf.conteúdo[n]);
        //printf("\n\n");

        separadôr = lsve_linha_separador_procurar(cf.conteúdo[n]);
        linhaSeparada = lsve_linha_separar(separadôr, cf.conteúdo[n]);

        mapa_introductôr.passe = linha_aparar(linhaSeparada[0]);
        mapa_introductôr.separadôr = linha_aparar(linhaSeparada[1]);
        mapa_introductôr.valôr = linha_aparar(linhaSeparada[2]);
        mapa_introductôr.i = n;

        printf("a%s- %s- %s- %d-\n", (char*)mapa_introductôr.passe, (char*)mapa_introductôr.separadôr, (char*)mapa_introductôr.valôr, mapa_introductôr.i);

        lsve_mapa_introduzir(&mapa, mapa_introductôr);
        printf("b%s- %s- %s- %d-\n\n", (char*)mapa[n].passe, (char*)mapa[n].separadôr, (char*)mapa[n].valôr, mapa[n].i);

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
        n++;
    }

    return mapa;
}

LSVEMapa* 
lsve_linha_matriz_mapear(ConteúdoFicheiro cf) {
    LSVEMapa* mapa;
    lsve_mapa_construir(&mapa);

    int n = 0;
    char* separadôr;
    char** linhaSeparada;
    while (cf.quantidade_conteúdo != n) {
        separadôr = lsve_linha_separador_procurar(cf.conteúdo[n]);

        linhaSeparada = lsve_linha_separar(separadôr, cf.conteúdo[n]);
        lsve_mapa_introduzir(&mapa, (LSVEMapa) { linha_aparar(linhaSeparada[0]), linha_aparar(linhaSeparada[2]), n, linha_aparar(linhaSeparada[1]) });
        printf("%s- %s- %s- %d-\n", (char*)mapa[n].passe, (char*)mapa[n].separadôr, (char*)mapa[n].valôr, mapa[n].i);

        n++;
    }

    return mapa;
}

void
lsve_mapa_introduzir(LSVEMapa** mapa, LSVEMapa valôr) {
    int i = 0;
    while ((*mapa)[i].i == i) { i = i + 1; }
    if (valôr.i != i) valôr.i = i;

    //*mapa = memória_re_allocar((i + 1 * sizeof(**mapa)) * sizeof(valôr), *mapa); // Método "funcional"
    *mapa = memória_re_allocar((i + 1) * sizeof(LSVEMapa), *mapa); // Como resolver isto?
    (*mapa)[i] = valôr;

    printf("\n%d %d %d\n\n", (*mapa)[i].i, valôr.i, i);
}

LSVEMapa*
lsve_mapa_procurar(Tipo tipo, void* procura, LSVEMapa* mapa) {
    int i = 0;

    switch (tipo)
    {
    case tipo_char:
        while (mapa[i].passe != '\0') {
            //printf("(/%d-%s-%s\\)\n", i, (char*)mapa[i].passe, (char*)procura);
            //printf("(/%s-%s\\)\n", (char*)mapa[i].passe, (char*)procura);
            if (linha_compara((char*)procura, (char*)mapa[i].passe)) {
                //printf("encontrado");
                return &mapa[i];
            }
            i = i + 1;
        }
        break;
    default: break;
    }

    //printf("não encontrado");

    return NULL;
}

char**
lsve_mapa_a_matriz_char(LSVEMapa* mapa) {
    char** linhas = malloc(sizeof(char*));

    int n = 0;
    while (mapa) {
        if (mapa[n].valôr != NULL) {
            char* linhaTratada = "";
            linha_complementar(mapa[n].passe, linhaTratada);
            linha_complementar(mapa[n].separadôr, linhaTratada);
            linha_complementar(mapa[n].valôr, linhaTratada);

            linhas[n] = linha_aparar(linha_separar(mapa[n].separadôr, linhaTratada)[0]);
            linhas = realloc(linhas, (n + 1 * sizeof(linhas)) * sizeof(char*));
            n = n + 1;
        }
        else break;
    }

    return linhas;
}
