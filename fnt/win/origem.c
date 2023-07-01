#include "LSVEgeneral.h"
#include "LSVEtipo.h"

#include "LSVEdesbraga.h"
#include "ficheiro.h"
#include "LSVEintérprete.h"

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

	Intérprete* intérprete = memória_allocar(sizeof(Intérprete));
	intérprete->expressão = NULL;

	char* ficheiroDesbragaCaminho = argumentos[2];

	if (ficheiroDesbragaCaminho != NULL) {
		interpretar(ficheiro_lêr(ficheiroDesbragaCaminho), intérprete);

		//desbraga_convenção = mapaDesbraga.valôr;
	}

	// Argumento 0 é o próprio programa.
	char* ficheiroLSVECaminho = argumentos[1];

	if (ficheiroLSVECaminho != NULL) {
		interpretar(ficheiro_lêr(ficheiroLSVECaminho), intérprete);
	}
	else {
		printf("\nDá-me um ficheiro para lêr.");
		return -1; // Sem ficheiros a ler, sem operação.
	}

	int c = -1;
	printf("\n\nPrima entra pa sair");
	while (c) {
		c = getc(stdin);

		if (c == 13) {
			break;
		}
	}

	return 0;
}
