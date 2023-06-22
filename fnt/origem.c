#include "lsve/mapa.h"
#include "lsve/general.h"
#include "lsve/tipo.h"

#include "lsve/desbraga.h"
#include "lsve/ficheiro.h"
#include "lsve/intérprete.h"

#include "consola.h"

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int main(int** ignorado, char** argumentos) {
	SetConsoleOutputCP(65001);
	//setlocale(LC_ALL, "pt_PT.UTF-8");
	setlocale(LC_ALL, ""); // Independente terminal da localidade.

	system("cls");

	// Argumento 0 é o próprio programa.
	char* ficheiroLSVECaminho = argumentos[1];

	if (ficheiroLSVECaminho != NULL) {
		interpretar(ficheiro_lêr(ficheiroLSVECaminho));
	}
	else {
		printf("\nDá-me um ficheiro para lêr.");
		return -1; // Sem ficheiros a ler, sem operação.
	}

	char* ficheiroDesbragaCaminho = argumentos[2];

	if (ficheiroDesbragaCaminho != NULL) {
		interpretar(ficheiro_lêr(ficheiroDesbragaCaminho));

		//desbraga_convenção = mapaDesbraga.valôr;
	}

	int c = -1;
	printf("\n\n\nPrima entra pa sair");
	while (c) {
		c = _getch();

		if (c == 13) {
			break;
		}
	}

	return 0;
}
