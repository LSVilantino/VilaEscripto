#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

char** ficheiro_lêr(char* ficheiroNome) {
    char** linhas = malloc(sizeof(char*));
    char* linhaActualDoFicheiro = malloc(sizeof(char*));
    char charactéreActualDoFicheiro = '\0';
    FILE* ficheiroLido = fopen(ficheiroNome, "r");

    int n = 0;
    int nl = 0;
    int i = 0;
    while (charactéreActualDoFicheiro != EOF) {
        charactéreActualDoFicheiro = fgetc(ficheiroLido);

        if (charactéreActualDoFicheiro == '\n' || charactéreActualDoFicheiro == EOF) {
            linhas[nl] = malloc(sizeof(char*));
            linhas[nl] = strdup(linhaActualDoFicheiro);

            linhas = realloc(linhas, (nl + 1 * sizeof(linhas)) * sizeof(char**));

            linhaActualDoFicheiro = malloc(sizeof(char*));

            n = 0;
            nl = nl + 1;
            continue;
        }
        else {
            linhaActualDoFicheiro[n] = charactéreActualDoFicheiro;
            //linhaActualDoFicheiro = realloc(linhaActualDoFicheiro, (n + 1 * sizeof(linhaActualDoFicheiro)) * sizeof(char*));
            linhaActualDoFicheiro = realloc(linhaActualDoFicheiro, n + 1 * sizeof(char*)); // n + 1 é necessário pela 'regra do múltiplo a índice 0'.
            linhaActualDoFicheiro[n + 1] = '\0';
            n = n + 1;
            i = i + 1;
        }

        //printf("\n%c - %s", charactéreActualDoFicheiro, linhaActualDoFicheiro);
    }

    //printf("\n");

    free(linhaActualDoFicheiro);
    fclose(ficheiroLido);

    return linhas;
}

int linha_contar_charactéres(char* linha) {
    int n = 0;

    for (int i = 0; linha[i] != '\0'; i++) { n = i; }

    return n;
}

int linha_contar_separador(char separador, char* linha) {
    int n = 1;

    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == separador) {
            n = n + 1;
        }
    }

    return n;
}

char** linha_separar(char separador, char* linha) {
    int n = 0;
    int n2 = 0;
    int n3 = 0;

    char** matrizTratada = malloc(sizeof(char*));
    char* linhaTratada = "";

    for (int i = 0; linha[i] != '\0'; i++) {
        //printf("\n%c _ %s", linha[i], linha);

        if (linha[i] == separador) {
            linhaTratada = "";

            n3 = 0;
            n2 = n2 + 1;

            n = n + 1;
            continue;
        }

        strncpy(&linhaTratada[n3], &linha[i], sizeof(linha[i] - 1));
        linhaTratada[n3 + 1] = '\0';
        matrizTratada[n] = strdup(linhaTratada);

        n2 = n2 + 1;
        n3 = n3 + 1;
    }

    //printf("\n0~%s\n1~%s", matrizTratada[0], matrizTratada[1]);
    //printf("\nlinha - %s", linhaTratada);

    return matrizTratada;
}

char* linha_aparar(char* linha) {
    int n = 0;

    while(linha[n] == ' ') { n = n + 1; }

    char* linhaTratada = "";
    int i = 0;
    while(linha[n] != '\0') {
        strncpy(&linhaTratada[i], &linha[n], sizeof(linha[n] - 1));

        linhaTratada[i + 1] = '\0';

        //printf("\n%d %d %c %c", i, n, linha[n], linhaTratada[i]);
        n = n + 1;
        i = i + 1;
    }

    int diferença = n - i;
    int índexReal = n - diferença;

    //printf("%d", índexReal);

    while(linhaTratada[índexReal - 1] == ' ' || linhaTratada[índexReal - 1] == '\n' || linhaTratada[índexReal - 1] == '\r' || linhaTratada[índexReal - 1] == '\t') {
        linhaTratada[índexReal - 1] = '\0';
        //printf("\n%d %c", índexReal, linhaTratada[índexReal - 1]);
        índexReal = índexReal - 1;
    }

    return strdup(linhaTratada);
}


typedef struct Mapa {
    void* passe;
    void* valôr;
    int i; //Índex
} Mapa;

typedef enum Tipo {
    tipo_int,
    tipo_char,
} Tipo;

Mapa* mapa_construir() {
    Mapa* mapa = malloc(sizeof(Mapa*));

    mapa[0].passe = NULL;
    mapa[0].valôr = NULL;
    mapa[0].i = 1;

    //printf("%s %s %d\n", (char*)mapa[0].passe, (char*)mapa[0].valôr, mapa[0].i);
    return mapa;
}

void mapa_introduzir(Mapa* mapa[], Mapa valôr) {
    Mapa* mappa = (*mapa);
    int i = 0;

    while (mappa[i].i == i) { i = i + 1; }
    if (valôr.i != i) valôr.i = i;

    mappa[i] = valôr;
}

Mapa* mapa_procurar__s(Tipo tipo, void* procura, Mapa* mapa) {
    int i = 0;

    switch (tipo)
    {
        case tipo_char: 
            while (mapa[i].i == i) {
                if (strcmp((char*)mapa[i].passe, (char*)procura) == 0) {
                    return &mapa[i];
                }

                i = i + 1;
            }
            break;
        default:
            break;
    }

    return NULL;
}

int main(int** a, char** b) {
    setlocale(LC_CTYPE, "pt_PT.UTF-8");

    // Define saída para usar sequências de consola virtual
    HANDLE lindanteDeSaída = GetStdHandle(STD_OUTPUT_HANDLE);
    if (lindanteDeSaída == INVALID_HANDLE_VALUE) { return GetLastError(); }

    DWORD modoConsola = 0;
    if (!GetConsoleMode(lindanteDeSaída, &modoConsola)) { return GetLastError(); }

    modoConsola |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(lindanteDeSaída, modoConsola)) { return GetLastError(); }

    char* caminho_relativo = "../../ficheiros.txt";
    char** ficheiroCaminhoConteúdo = ficheiro_lêr(caminho_relativo);

    Mapa* mapa = mapa_construir();

    int n = 0;
    while (ficheiroCaminhoConteúdo) {
        if (ficheiroCaminhoConteúdo[n] != NULL) {
            char** linhaSeparada = linha_separar('>', ficheiroCaminhoConteúdo[n]);
            mapa_introduzir(&mapa, (Mapa) { linha_aparar(linhaSeparada[0]), linha_aparar(linhaSeparada[1]), n });
            printf("%s %s %d\n", (char*)mapa[n].passe, (char*)mapa[n].valôr, mapa[n].i);

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

    n = 0;

    system("cls");

    Mapa* mapaEncontrado = mapa_procurar__s(tipo_char, "construc", mapa);

    wprintf(L"\x1b[34;46m\n%S %S %d\r\n", (char*)mapaEncontrado[0].passe, (char*)mapaEncontrado[0].valôr, mapaEncontrado[0].i);
    wprintf(L"\x1b[39m");
    wprintf(L"\x1b[49m");

    char** ficheiroConteúdoConstrucção = ficheiro_lêr(mapaEncontrado[0].valôr);
    while (ficheiroConteúdoConstrucção)
    {
        wprintf(L"\x1b[34;46m%S\r\n", linha_aparar(linha_separar('>', ficheiroConteúdoConstrucção[n])[0]));
        wprintf(L"\x1b[39m");
        wprintf(L"\x1b[49m");
        n = n + 1;
    }
    //printf("%s %s %d\n", (char*)mapa[0].passe, (char*)mapa[0].valôr, mapa[0].i);

	return 0;
}