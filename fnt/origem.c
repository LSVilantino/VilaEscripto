#include "tipo.h"
#include "mapa.h"
#include "linha.h"
#include "ficheiro.h"

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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

    //wprintf(L"\x1b[34;46m\n%S %S %d\r\n", (char*)mapaEncontrado[0].passe, (char*)mapaEncontrado[0].valôr, mapaEncontrado[0].i);
    wprintf(L"\x1b[39m");
    wprintf(L"\x1b[49m");

    char** ficheiroConteúdoConstrucção = ficheiro_lêr(mapaEncontrado[0].valôr);
    while (ficheiroConteúdoConstrucção)
    {
        if (n == 2) {
            wprintf(L"\x1b[34;46m%S\r\n", linha_aparar(linha_separar('>', ficheiroConteúdoConstrucção[n])[0]));
            wprintf(L"\x1b[39m");
            wprintf(L"\x1b[49m");
        }
        else {
            printf("%s\r\n", linha_aparar(linha_separar('>', ficheiroConteúdoConstrucção[n])[0]));
        }
        n = n + 1;
    }
    //printf("%s %s %d\n", (char*)mapa[0].passe, (char*)mapa[0].valôr, mapa[0].i);

	return 0;
}