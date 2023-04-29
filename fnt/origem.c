#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

char** ficheiro_lêr(char* ficheiroNome) {
    char** linhas = malloc(sizeof(char*));
    char* linhaActualDoFicheiro = malloc(sizeof(char*));
    char charactéreActualDoFicheiro = '\0';
    FILE* ficheiroLido = fopen(ficheiroNome, "r");

    int n = 0;
    int nl = 0;
    for (int i = 0; charactéreActualDoFicheiro != EOF; i++) {
        charactéreActualDoFicheiro = fgetc(ficheiroLido);

        linhaActualDoFicheiro[n] = charactéreActualDoFicheiro;
        linhaActualDoFicheiro = realloc(linhaActualDoFicheiro, (n + 1 * sizeof(linhaActualDoFicheiro)) * sizeof(char*));
        linhaActualDoFicheiro[n + 1] = '\0';

        if (charactéreActualDoFicheiro == '\n') {
            linhas[nl] = malloc(sizeof(char*));
            linhas[nl] = strdup(linhaActualDoFicheiro);

            linhas = realloc(linhas, (nl + 1 * sizeof(linhas)) * sizeof(char**));

            linhaActualDoFicheiro = malloc(sizeof(char*));

            n = 0;
            nl = nl + 1;
            continue;
        }

        printf("\n%c - %s", charactéreActualDoFicheiro, linhaActualDoFicheiro);

        n = n + 1;
    }

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

    char** matrizTratada = malloc(sizeof(char*) * linha_contar_separador(separador, linha));
    char* linhaTratada = "";

    for (int i = 0; linha[i] != '\0'; i++) {
        //printf("\n%c _ %s", linha[i], linha);

        strncpy(&linhaTratada[n3], &linha[i], sizeof(linha[i] - 1));
        linhaTratada[n3 + 1] = '\0';
        matrizTratada[n] = strdup(linhaTratada);

        if (linha[i] == '>') {
            linhaTratada = "";

            n3 = 0;
            n2 = n2 + 1;

            n = n + 1;
            continue;
        }

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

    return linhaTratada;
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

struct Mapa* mapa_construir() {
    Mapa* mapa = malloc(sizeof(Mapa*));

    //printf("%s", (char*) mapa[0].passe);

    return mapa;
}

void mapa_introduzir(Mapa** mapa, Mapa valôr) {
    int i = 0;

    Mapa* mappa = (*mapa);

    while (mappa[i].i == i) {
        i = i + 1;
    }

    if (valôr.i != i) {
        valôr.i = i;
    }

    // Incrementar espaço à matrix

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

    printf("");

    Mapa* mapa = mapa_construir();

    mapa_introduzir(&mapa, (Mapa) { "A - Chave", "A - Valôr", 0 });
    printf("%s %s %d\n", (char*)mapa[0].passe, (char*)mapa[0].valôr, mapa[0].i);

    Mapa* mapaEncontrado = mapa_procurar__s(tipo_char, "A - Chave", mapa);
    printf("%s %s %d\n", (char*)mapaEncontrado[0].passe, (char*)mapaEncontrado[0].valôr, mapaEncontrado[0].i);

    mapa_introduzir(&mapa, (Mapa) { "B - Chave", "B - Valôr", 1 });
    printf("%s %s %d\n", (char*)mapa[1].passe, (char*)mapa[1].valôr, mapa[1].i);

    mapa_introduzir(&mapa, (Mapa) { "C - Chave", "C - Valôr", 3 });
    printf("%s %s %d\n", (char*)mapa[2].passe, (char*)mapa[2].valôr, mapa[2].i);

    //printf("%s %s\n", (char*) mapaEncontrado->passe, (char*) mapaEncontrado->valôr);

    /*char* caminho_relativo = "ficheiros.txt";
    char** ficheiroCaminhoConteúdo = ficheiro_lêr(caminho_relativo);

    printf("\n\n");

    int n = 0;
    while (ficheiroCaminhoConteúdo) {
        ficheiro_lêr(linha_aparar(linha_separar('>', ficheiroCaminhoConteúdo[n])[1]));
        n = n + 1;
    }*/

	return 0;
}