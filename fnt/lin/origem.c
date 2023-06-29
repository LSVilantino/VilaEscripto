#include "general.h"
#include "ficheiro.h"

#include "LSVEintérprete.h"

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argquan, char** argumentos) {
	char* ficheiroDesbraga = nil;
	char* ficheiroLSVE = nil;

	if (argquan == 3) {
		if (argumentos[2]) { ficheiroDesbraga = argumentos[2]; }
		if (argumentos[1]) { ficheiroLSVE = argumentos[1]; }
	}
	else if (argquan < 3) {
		if (argumentos[1]) { ficheiroLSVE = argumentos[1]; }
	}

	Intérprete* intérprete = memória_allocar(sizeof(Intérprete));
	intérprete->expressão = nil;
	intérprete->expressão = memória_allocar(sizeof(Expressão));

	if(ficheiroDesbraga) {
		LINHA* ficheiroDesbraga_linhas = ficheiro_lêr(ficheiroDesbraga);
		free(ficheiroDesbraga_linhas[0]);
		free(ficheiroDesbraga_linhas);
	}

	if(ficheiroLSVE) {
		LINHA* ficheiroLSVE_linhas = ficheiro_lêr(ficheiroLSVE);
		free(ficheiroLSVE_linhas[0]);
		free(ficheiroLSVE_linhas);
	}

    int c;
	printf("\n\nPrima entra pa sair");
	while (1) {
		fflush(stdin);
		c = getc(stdin);

		if (c == 10) {
			break;
		}
	}

	free(intérprete->expressão);
	free(intérprete);

	return 0;
}
