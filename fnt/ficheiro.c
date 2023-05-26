#include "general.h"
#include "ficheiro.h"
#include "mapa.h"
#include "linha.h"
#include "consola.h"
#include "lsve.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

ConteúdoFicheiro
ficheiro_lêr(char* ficheiroNome) {
    FILE* ficheiroLido = fopen(ficheiroNome, "r");

    char** linhas = memória_allocar(sizeof(char*));
    char* linhaActualDoFicheiro = memória_allocar(sizeof(char));
    char charactéreActualDoFicheiro = fgetc(ficheiroLido);
    char charactéreAnteriôrDoFicheiro = charactéreActualDoFicheiro;

    if (linhas == NULL) return (ConteúdoFicheiro) { 0 };

    int n = 0;
    int nl = 0;
    while (charactéreActualDoFicheiro = fgetc(ficheiroLido)) {
        if (charactéreAnteriôrDoFicheiro == clave_ficheiro_comentário) {
            while (charactéreAnteriôrDoFicheiro = fgetc(ficheiroLido))
            {
                if (charactéreAnteriôrDoFicheiro == '\n') break;
            }

            charactéreActualDoFicheiro = fgetc(ficheiroLido);
            charactéreAnteriôrDoFicheiro = charactéreActualDoFicheiro;
            //charactéreActualDoFicheiro = fgetc(ficheiroLido);

            n = 0;
            continue;
        }

        if (charactéreActualDoFicheiro == clave_ficheiro_forçar_encerro || charactéreActualDoFicheiro == clave_ficheiro_encerro) {
            linhaActualDoFicheiro[n] = charactéreAnteriôrDoFicheiro;

            n = n + 1;

            linhaActualDoFicheiro[n] = '\0';

            linhas = realloc(linhas, (nl + 1 * sizeof(linhas)) * sizeof(char**));
            linhas[nl] = strdup(linhaActualDoFicheiro);

            n = 0;
            nl = nl + 1;

            break;
        }

        if (charactéreAnteriôrDoFicheiro == '\n') {
            linhaActualDoFicheiro[n] = charactéreAnteriôrDoFicheiro;

            n = n + 1;

            linhaActualDoFicheiro[n] = '\0';
            linhaActualDoFicheiro = realloc(linhaActualDoFicheiro, n * sizeof(char*)); // n + 1 é necessário pela 'regra do múltiplo a índice 0'.

            linhas = realloc(linhas, (nl + 1 * sizeof(linhas)) * sizeof(char**));
            linhas[nl] = strdup(linhaActualDoFicheiro);
            linhaActualDoFicheiro = memória_allocar(sizeof(char*));

            n = 0;
            nl = nl + 1;

            charactéreAnteriôrDoFicheiro = charactéreActualDoFicheiro;

            continue;
        }

        linhaActualDoFicheiro[n] = charactéreAnteriôrDoFicheiro;

        n = n + 1;

        linhaActualDoFicheiro[n] = '\0';
        //linhaActualDoFicheiro = realloc(linhaActualDoFicheiro, (n + 1 * sizeof(linhaActualDoFicheiro)) * sizeof(char*));
        linhaActualDoFicheiro = realloc(linhaActualDoFicheiro, n * sizeof(char*)); // n + 1 é necessário pela 'regra do múltiplo a índice 0'.

        charactéreAnteriôrDoFicheiro = charactéreActualDoFicheiro;
        //printf("\n%c - %s", charactéreActualDoFicheiro, linhaActualDoFicheiro);
    }

    ConteúdoFicheiro cf = (ConteúdoFicheiro){ linhas, nl };

    //int i = 0;
    //while (cf.quantidade_conteúdo != i) {
    //    printf("%s", cf.conteúdo[i]);
    //    i++;
    //}

    printf("\n");

    return cf;
}

Mapa* 
ficheiro_conteúdo_mapear(char* ficheiroCaminho) {
    ConteúdoFicheiro cf = ficheiro_lêr(ficheiroCaminho);
    Mapa* mapa = mapa_construir();

    printf("\n\n%s - %d \n\n", ficheiroCaminho, cf.quantidade_conteúdo);

    int n = 0;
    while (cf.conteúdo) {
        if (n != cf.quantidade_conteúdo) {
            //printf(ficheiroConteúdo.conteúdo[n]);
            char** linhaSeparada = linha_separar(lsve_linha_separador_procurar(cf.conteúdo[n]), cf.conteúdo[n]);
            mapa_introduzir(&mapa, (Mapa) { linha_aparar(linhaSeparada[0]), linha_aparar(linhaSeparada[1]), n });
            printf("%s- %s- %d-\n", (char*)mapa[n].passe, (char*)mapa[n].valôr, mapa[n].i);

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
