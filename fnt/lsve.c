#include "lsve.h"
#include "linha.h"
#include "ficheiro.h"
#include "consola.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char**
lsve_linha_separar(char* separadôr, char* linha) {
    int separadôr_i = 0;
    int separadôr_t = linha_charactéres_contar(separadôr);
    int resultado_i = 0;
    int resultado_charac_i = 0;

    char** resultado = memória_allocar(sizeof(char*));
    resultado[resultado_i] = memória_allocar(2 * sizeof(char));

    for (int i = 0; linha[i] != '\0'; i++)
    {
        if (separadôr[separadôr_i] == linha[i]) {
            separadôr_i++;

            if (separadôr_i == separadôr_t) {
                resultado = memória_re_allocar(resultado_i + 1 * sizeof(char*), resultado);

                resultado_i++;
                resultado[resultado_i] = strdup(separadôr);

                resultado_i++;
                resultado[resultado_i] = memória_allocar(2 * sizeof(char));
                resultado_charac_i = 0;
                separadôr_i = 0;
                continue;
            }
            else continue;
        }
        else separadôr_i = 0;

        resultado[resultado_i] = memória_re_allocar(resultado_charac_i + 2, resultado[resultado_i]);
        resultado[resultado_i][resultado_charac_i] = linha[i];
        resultado[resultado_i][resultado_charac_i + 1] = '\0';

        printf("%c-", resultado[resultado_i][resultado_charac_i]);
        resultado_charac_i++;
    }

    return resultado;






    //char** resultado = memória_allocar(sizeof(char*));
    //char* porçãoActual = memória_allocar(sizeof(char));

    //int porçãoActual_i = 0;
    //int resultado_i = 0;
    //resultado[resultado_i] = memória_allocar(sizeof(char));
    //for (int i = 0; linha[i] != '\0'; i++)
    //{
    //    porçãoActual = memória_re_allocar(porçãoActual_i + 2, porçãoActual);
    //    /*resultado[resultado_i] = memória_re_allocar(porçãoActual_i + 2, resultado[resultado_i]);
    //    resultado[resultado_i][porçãoActual_i] = porçãoActual[porçãoActual_i] = linha[i];
    //    resultado[resultado_i][porçãoActual_i + 1] = porçãoActual[porçãoActual_i + 1] = '\0';*/

    //    porçãoActual[porçãoActual_i] = linha[i];
    //    porçãoActual[porçãoActual_i + 1] = '\0';

    //    resultado[resultado_i] = porçãoActual;

    //    printf("%c", porçãoActual[porçãoActual_i]);
    //    porçãoActual_i++;

    //    if (linha_contém(separadôr, porçãoActual)) {
    //        printf("\n\n%s-\n\n", porçãoActual);
    //        porçãoActual[(porçãoActual_i - linha_charactéres_contar(separadôr))] = '\0';
    //        //printf("%c", porçãoActual[porçãoActual_i]);

    //        resultado = memória_re_allocar(resultado_i + 1 * sizeof(char*), resultado);
    //        resultado[resultado_i] = strdup(porçãoActual);

    //        //printf("\n1-%s-1", resultado[resultado_i]);

    //        resultado_i++;

    //        resultado = memória_re_allocar(resultado_i + 1 * sizeof(char*), resultado);
    //        resultado[resultado_i] = strdup(separadôr);

    //        //printf("\n2-%s-2\n", resultado[resultado_i]);

    //        free(porçãoActual); porçãoActual = NULL;
    //        porçãoActual = memória_allocar(sizeof(char));

    //        porçãoActual_i = 0;
    //        resultado_i++;

    //        //resultado[resultado_i] = memória_allocar(sizeof(char));
    //        continue;
    //    }
    //}

    //free(porçãoActual);

    //return resultado;
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
        LSVEMapa* mapa_propriedade = lsve_ficheiro_conteúdo_mapear(linha_aparar(mapa.valôr));
        char** mapa_propriedade_matriz = lsve_mapa_a_matriz_char(mapa_propriedade);

        char* opçãoSeleccionada_construcção = consola_construir_menu(mapa_propriedade_matriz);
        if (opçãoSeleccionada_construcção == NULL) return opçãoSeleccionada_construcção;

        LSVEMapa* mapa_seleccionado = lsve_mapa_procurar(clave_tipo, opçãoSeleccionada_construcção, mapa_propriedade);
        mapa_seleccionado->i = 0;
        // Não eliminas esta linha! Durante a comparação na busca, manipula o algorítmo que inicia procura por valôr 0.
        // 
        // Ao seleccionar o mapa aqui, têm-se o número da ordem escolhida. Se removeres esta linha, somente a primeira 
        // opção será válida.

        mapa.valôr = lsve_ficheiro_valôr_tratar(clave_tipo, mapa_seleccionado->passe, mapa_propriedade);

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
    printf((char*)clave);

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
                printf("%c", commando[n + 1]);

                n += 2;

                clave_reposição = linha_complementar("$(", clave_reposição);

                int n_clave = 0;
                while (commando[n]) {
                    printf("%c", commando[n]);
                    if (commando[n] == ')') {
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
    char** linhaSeparada = memória_allocar(sizeof(char*));

    lsve_mapa_construir(&mapa);

    int n = 0;
    while (cf.quantidade_conteúdo != n) {
        printf(cf.conteúdo[n]);
        printf("\n\n");

        separadôr = lsve_linha_separador_procurar(cf.conteúdo[n]); printf("A");
        linhaSeparada = lsve_linha_separar(separadôr, cf.conteúdo[n]); printf("B");

        printf("----------%s----------\n", linhaSeparada[0]);
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

//LSVEMapa* 
//lsve_linha_matriz_mapear(ConteúdoFicheiro cf) {
//    LSVEMapa* mapa;
//    lsve_mapa_construir(&mapa);
//
//    int n = 0;
//    char* separadôr;
//    char** linhaSeparada;
//    while (cf.quantidade_conteúdo != n) {
//        separadôr = lsve_linha_separador_procurar(cf.conteúdo[n]);
//
//        linhaSeparada = lsve_linha_separar(separadôr, cf.conteúdo[n]);
//        lsve_mapa_introduzir(&mapa, (LSVEMapa) { linha_aparar(linhaSeparada[0]), linha_aparar(linhaSeparada[2]), n, linha_aparar(linhaSeparada[1]) });
//        printf("%s- %s- %s- %d-\n", (char*)mapa[n].passe, (char*)mapa[n].separadôr, (char*)mapa[n].valôr, mapa[n].i);
//
//        n++;
//    }
//
//    return mapa;
//}

void
lsve_mapa_introduzir(LSVEMapa** mapa, LSVEMapa valôr) {
    int i = 0;
    while ((*mapa)[i].i == i) { i = i + 1; }
    if (valôr.i != i) valôr.i = i;

    //*mapa = memória_re_allocar((i + 1 * sizeof(**mapa)) * sizeof(valôr), *mapa);
    (*mapa) = memória_re_allocar((i + 1) * sizeof(LSVEMapa), *mapa);
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

    for (int i = 0; mapa[i].i == i; i++) {
        linhas = memória_re_allocar((i + 1) * sizeof(char*), linhas);
        linhas[i] = mapa[i].passe;
    }

    return linhas;
}
