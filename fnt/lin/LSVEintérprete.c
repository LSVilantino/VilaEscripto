#include "LSVEintérprete.h"

#include "LSVEgeneral.h"
#include "linha.h"
#include "pilha.h"
#include "ficheiro.h"

//#include "LSVEconsola.h"
//#include "LSVEgeneral.h"

#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>

void operação_re_definir(int operador_n, Grade* expressão, Expectação expectação, Operação_Tipo operação_tipo, size_t linha_t) {
#if !defined(operação_re_definir__3)

#define operação_re_definir__3
#define expressão__3            (*expressão)
#define operadores__3           (expressão__3.filho)
#define operador_grade__3       (operadores__3[operador_n])
#define operador__3             (*(Operação*) operador_grade__3.elemento)

#endif // #if !defined(operação_re_definir__3)

	grade_introduzir(&operadores__3,
		(Grade) {
		.índice = operador_n,
        .constatação = nil,
		.tipo = lsve_tipo_operador,
		.precisa_libertar = vero,
		.elemento = memória_allocar(sizeof(Operação))
		}
	);
    
	operador__3.índice = operador_n;
	operador__3.tipo = operação_tipo;
	operador__3.expectação = expectação;

	int índice = 0;

	grade_introduzir(&operador_grade__3.filho,
		(Grade) {
		.índice = índice++,
		.constatação = var_nome(linha),
		.tipo = lsve_tipo_linha,
		.precisa_libertar = vero,
		.elemento = memória_allocar(linha_t)
		}
	);

#undef operação_re_definir__3
#undef expressão__3
#undef operadores__3
#undef operador__3
}

void 
interpretar_linha(const Grade* linha, Grade* intérprete, int* expressão_n) {
#if !defined(interpretar_linha__2)

#define interpretar_linha__2
#define linha__2				((char*) (*linha).elemento)
#define intérprete__2			(*((Intérprete*)(*intérprete)->elemento))
#define intérprete_grade__2		(*intérprete)
#define rastilho__2				(*(Rastilho*) &intérprete__2.filho[1].elemento)
#define expressão_n__2			(*expressão_n)
#define expressões__2			(intérprete_grade__2.filho)
#define expressão__2			((Expressão) intérprete_grade__2.filho[0].elemento[expressão_n__2])
#define expressão_grade__2		(intérprete_grade__2.filho[expressão_n__2])
#define operadores_grade__2		(expressão_grade__2.filho)
#define operadores__2			(*(Operação**) &expressão_grade__2.filho[operador_n].elemento)
#define operador__2				((*(Operação**) &expressão_grade__2.filho[operador_n].elemento)[operador_n])
#define operador_grade__2		(expressão_grade__2.filho[operador_n])
#define recúo__2                recúo - 1

#endif // #if !defined(interpretar_linha__2)

	int
    linha_n = 0,

    operador_n = 0,
    operador_linha_n = 0,

    clave_n = 0,
    ficha_n = 0,

    pula = 0
    ;

    Pilha pilha = pilha_construir((Lato[])
    {
        (Lato) { tipo_tamanho, fal, &(int){3} }
    });

    int recúo = pilha.recúo;

    Linha ficha = memória_preên_allocar(1, sizeof(char));

    DESBRAGA_MENSAGEM("LINHA A DESBRAGAR %s", linha__2)

    grade_introduzir(&expressões__2, 
        (Grade) {
        .índice = 0, 
        .constatação = var_nome(expressão),
        .tipo = lsve_tipo_expressão, 
        .precisa_libertar = vero, 
        .elemento = memória_allocar(sizeof(Grade))
        }
    );

    expressão_grade__2.filho = nil;

    grade_introduzir(&operadores_grade__2, 
        (Grade) {
        .índice = 0, 
        .constatação = var_nome(operação),
        .tipo = lsve_tipo_operador, 
        .precisa_libertar = vero, 
        .elemento = nil
        }
    );
    
    operação_re_definir(operador_n, &expressão_grade__2, expectação__concedido, operação__concedido, 1);

    while(recúo > 1) {
        /* Ao fim da linha, diminui - se o recúo da pilha, até chegar à ponta,
		*  o último charactére armazenado.
		*
		* Se a linha não estiver ao fim, introduz o último charactére à pilha.
		*/
		if (linha__2[linha_n] == LINHA_NIL) { recúo--; }
		else {
			pilha_introduzir(linha__2[linha_n], &pilha);
			
            linha_n++;
		}
        
		char charactére = pilha.conteúdo[recúo__2];
        //DESBRAGA_MENSAGEM("%c", charactére)

        /*
			As primeiras corridas do ciclo caem em endereço nil,
			ficam armazenadas no início da pilha.
			
			Quanto maior a pilha, mais iterações levam para chegar
			algum valôr. Até lá, foram-se os índices.
		*/


		if (charactére == LINHA_NIL) continue;

		if (pula != 0) {
			pula--;
			continue;
		}







        if (operador__2.expectação == expectação__concedido ||
            operador__2.expectação == expectação__nil
        )
		{
            Grade* linha_grade = grade_procurar(var_nome(linha), &operadores_grade__2);
            linha_introduzir_charactére(charactére, operador_linha_n, (Linha*) &linha_grade->elemento);
			DESBRAGA_MENSAGEM("%c", ((Linha) linha_grade->elemento)[operador_linha_n]);

			operador_linha_n++;

			if (operador__2.tipo == operação__concedido) operador__2.expectação = expectação__concessão;
		}
    }

fim:

free(pilha.conteúdo);
free(ficha);

#undef interpretar_linha__2
#undef linha__2
#undef intérprete__2
#undef intérprete_grade__2
#undef rastilho__2
#undef expressão_n__2
#undef expressões__2
#undef expressão__2
#undef expressão_grade__2
#undef operadores_grade__2
#undef operadores__2
#undef operador__2
#undef recúo__2
return;
}

void
interpretar(Grade** linhas, Grade** intérprete) {
#if !defined(interpretar__1)

#define interpretar__1
#define linhas__1                   (*linhas)
#define intérprete_grade__1         ((*intérprete)[0])
#define intérprete__1               (*(Intérprete*) intérprete_grade__1.elemento)
#define expressões__1               (intérprete_grade__1.filho)
#define expressão__1                ((Expressão) intérprete__1.filho[0].elemento[expressão_n - 1])
#define expressão_grade__1          intérprete__1.filho[0]
#define rastilho__1                 ((Rastilho*) intérprete__1.filho[1].elemento)

#endif // #if !defined(interpretar__1)

    if (intérprete_grade__1.tipo != lsve_tipo_intérprete) { 
        DESBRAGA_MENSAGEM("Grade não é do tipo correcto")
        goto fim;
    }

    int 
    linhas_n = 0, 
    expressão_n = 0
    ;

    while(linhas__1[linhas_n].índice == linhas_n) {
        if (linhas__1[linhas_n].tipo == tipo_linha) {
            expressões__1 = memória_re_allocar((expressão_n + 1) * sizeof(Grade), expressões__1);

            interpretar_linha(&linhas__1[linhas_n], &intérprete_grade__1, &expressão_n);
            linhas_n++;

            goto fim;
        }
    }

fim:
#undef interpretar__1
#undef linhas__1
#undef intérprete_grade__1
#undef intérprete__1
#undef expressões__1
#undef expressão__1
#undef expressão_grade__1
#undef rastilho__1
return;
}
