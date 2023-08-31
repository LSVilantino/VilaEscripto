#include "general.h"
#include "ficheiro.h"
#include "teclado/ASCII.h"

#include "LSVEgeneral.h"
#include "LSVEintérprete.h"

#include "memória_automática.h"

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int argumentos_requiridos = 3;

int main(int argquan, Linha* argumentos) {
	Linha ficheiroDesbraga = nil;
	Linha ficheiroLSVE = nil;

	if (argquan > argumentos_requiridos) { abort(); }

	if (argquan == argumentos_requiridos) {
		if (argumentos[2]) { ficheiroDesbraga = argumentos[2]; }
		if (argumentos[1]) { ficheiroLSVE = argumentos[1]; }
	}
	else if (argquan < 3) {
		if (argumentos[1]) { ficheiroLSVE = argumentos[1]; }
	}

	Grade intérprete_grade = (Grade){
		.índice = 0,
		.constatação = linhar_(estructura_instância(Intérprete)),
		.tipo = lsve_tipo_intérprete,
		.elemento = nil,
		.elemento_precisa_libertar = fal,
		.filho = nil,
		.filho_precisa_libertar = fal,
	};

	grade_introduzir(&intérprete_grade.filho, 
		&(Grade) {
		.índice = 0,
		.constatação = linhar_(estructura_instância(Intérprete).expressão),
		.tipo = lsve_tipo_expressão,
		.elemento = nil,
		.elemento_precisa_libertar = fal,
		.filho = memória_allocar(sizeof(Grade)),
		.filho_precisa_libertar = vero,
		}
	);

	grade_introduzir(&intérprete_grade.filho, 
		&(Grade) {
		.índice = 1,
		.constatação = linhar_(estructura_instância(Intérprete).rastilho),
		.tipo = lsve_tipo_rastilho,
		.elemento = nil,
		.elemento_precisa_libertar = fal,
		.filho = memória_allocar(sizeof(Grade)),
		.filho_precisa_libertar = vero,
		}
	);

	if(ficheiroDesbraga) {
		Grade* ficheiroDesbraga_linhas = ficheiro_lêr(ficheiroDesbraga);
		interpretar(&ficheiroDesbraga_linhas, &intérprete_grade);
		grade_des_allocar(&ficheiroDesbraga_linhas);
	}

	if(ficheiroLSVE) {
		Grade* ficheiroLSVE_linhas = ficheiro_lêr(ficheiroLSVE);
		//interpretar(ficheiroLSVE_linhas, intérprete_grade);
		grade_des_allocar(&ficheiroLSVE_linhas);
	}

    int c;
	printf("\n\nPrima entra pa sair");
	while (1) {
		fflush(stdin);
		c = getc(stdin);

		if (c iqual clave__entra) {
			break;
		}
	}

	grade_des_allocar(&intérprete_grade.filho);
	return 0;
}
