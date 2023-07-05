#include "general.h"
#include "ficheiro.h"
#include "teclado/ASCII.h"

#include "LSVEgeneral.h"
#include "LSVEintérprete.h"

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int argumentos_requiridos = 3;

int main(int argquan, char** argumentos) {
	char* ficheiroDesbraga = nil;
	char* ficheiroLSVE = nil;

	if (argquan > argumentos_requiridos) { abort(); }

	if (argquan == argumentos_requiridos) {
		if (argumentos[2]) { ficheiroDesbraga = argumentos[2]; }
		if (argumentos[1]) { ficheiroLSVE = argumentos[1]; }
	}
	else if (argquan < 3) {
		if (argumentos[1]) { ficheiroLSVE = argumentos[1]; }
	}

	Grade* grade_intérprete = nil;

	Intérprete* intérprete = memória_allocar(sizeof(Intérprete));
	intérprete->expressão = nil;

	grade_introduzir(&grade_intérprete, 0, lsve_tipo_intérprete, vero, intérprete);

	if(ficheiroDesbraga) {
		Grade* ficheiroDesbraga_linhas = ficheiro_lêr(ficheiroDesbraga);
		interpretar(&ficheiroDesbraga_linhas, &grade_intérprete);
		grade_des_allocar(&ficheiroDesbraga_linhas);
	}

	if(ficheiroLSVE) {
		Grade* ficheiroLSVE_linhas = ficheiro_lêr(ficheiroLSVE);
		//interpretar(ficheiroLSVE_linhas, intérprete);
		grade_des_allocar(&ficheiroLSVE_linhas);
	}

    int c;
	printf("\n\nPrima entra pa sair");
	while (1) {
		fflush(stdin);
		c = getc(stdin);

		if (c == entra) {
			break;
		}
	}

	grade_des_allocar(&grade_intérprete);
	return 0;
}
