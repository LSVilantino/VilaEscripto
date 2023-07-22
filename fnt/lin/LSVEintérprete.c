#include "LSVEintérprete.h"
#include "LSVEgeneral.h"

#include "general.h"
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
#define operador__3             (**(Operação**) &operador_grade__3.elemento)

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
#undef operador_grade__3
#undef operador__3
}


typedef struct TF_Interpretar TF_Interpretar;
struct TF_Interpretar{
	int
    linha_n,
    operador_n,
    operador_linha_n,
    clave_n,
    ficha_n,
    pula
    ;

	Pilha pilha; int recúo;
	Linha ficha;
	char charactére;

	void (*introduzir_concedido)(TF_Interpretar* tf, Operação* operador, Linha* operador_linha);
	Dico (*verificar_concessão_objectiva)(TF_Interpretar* tf, Grade* expressão_grade, Operação* operador, Linha* operador_linha);
} ;

Dico interpretar_linha__verificar_concessão_objectiva(TF_Interpretar* tf, Grade* expressão_grade, Operação* operador, Linha* operador_linha) {
#define tf__5 (*tf)
#define operador__5 (*operador)
#define operador_linha__5 (*operador_linha)
#define expressão_linha__5 (*expressão_grade)

	if (clave_têr_por_tipo(clave_lêr).pala[tf__5.clave_n] == tf__5.charactére &&
		clave_têr_por_tipo(clave_ficha).pala[1] == tf__5.pilha.conteúdo[tf__5.recúo - 2])
	{
		linha_aparar(&operador_linha__5);

		tf__5.operador_n++;
		operação_re_definir(tf__5.operador_n, &expressão_linha__5, expectação__valôr, operação__concessão_directa, 1);

		tf__5.operador_linha_n = 0;
		operador__5.expectação = expectação__nil;
		operador__5.tipo = operação__concessão_objectiva;

		tf__5.pula = 1;
		return vero;
	}

	return fal;

#undef tf__5
}

void interpretar_linha__introduzir_concedido(TF_Interpretar* tf, Operação* operador, Linha* operador_linha) {
#define tf__4 (*tf)
#define operador__4 (*operador)
#define operador_linha__4 (*operador_linha)

	if (operador__4.expectação == expectação__concedido ||
		operador__4.expectação == expectação__nil
	)
	{
		linha_introduzir_charactére(tf__4.charactére, tf__4.operador_linha_n, &operador_linha__4);
		DESBRAGA_MENSAGEM("%c, %d", operador_linha__4[tf__4.operador_linha_n], operador__4.índice);

		tf__4.operador_linha_n++;

		if (operador__4.tipo == operação__concedido) operador__4.expectação = expectação__concessão;
	}

#undef tf__4
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
#define expressão__2			((Expressão) expressões__2[0].elemento[expressão_n__2])
#define expressão_grade__2		(expressões__2[expressão_n__2])
#define operadores_grade__2		(expressão_grade__2.filho)
#define operadores__2			(*(Operação**) &operadores_grade__2[tf.operador_n].elemento)
#define operador__2				((operadores__2)[0])
#define operador_grade__2		(operadores_grade__2[tf.operador_n])
#define operador_linha__2       (*(Linha*) &linha_grade->elemento)
#define recúo__2                tf.recúo - 1

#endif // #if !defined(interpretar_linha__2)

	Grade* linha_grade = nil;

	TF_Interpretar tf = {
		.linha_n = 0,

    	.operador_n = 0,
    	.operador_linha_n = 0,

    	.clave_n = 0,
    	.ficha_n = 0,

    	.pula = 0,

		.pilha = pilha_construir((Lato[])
		{
			(Lato) { tipo_tamanho, fal, &(int){3} }
		}),

		.ficha = memória_preên_allocar(1, sizeof(char)),

		.introduzir_concedido = interpretar_linha__introduzir_concedido,
		.verificar_concessão_objectiva = interpretar_linha__verificar_concessão_objectiva
	};

    tf.recúo = tf.pilha.recúo;

    DESBRAGA_MENSAGEM("LINHA A DESBRAGAR %s", linha__2)

    grade_introduzir(&expressões__2, 
        (Grade) {
        .índice = expressão_n__2,
        .constatação = var_nome(expressão),
        .tipo = lsve_tipo_expressão, 
        .precisa_libertar = vero, 
        .elemento = memória_allocar(sizeof(Grade))
        }
    );

    operação_re_definir(tf.operador_n, &expressão_grade__2, expectação__concedido, operação__concedido, 1);

    while(tf.recúo > 1) {
        /* Ao fim da linha, diminui - se o recúo da pilha, até chegar à ponta,
		*  o último charactére armazenado.
		*
		* Se a linha não estiver ao fim, introduz o último charactére à pilha.
		*/
		if (linha__2[tf.linha_n] == LINHA_NIL) { tf.recúo--; }
		else {
			pilha_introduzir(linha__2[tf.linha_n], &tf.pilha);
			
            tf.linha_n++;
		}
        
		tf.charactére = tf.pilha.conteúdo[recúo__2];
        //DESBRAGA_MENSAGEM("%c", charactére)

        /*
			As primeiras corridas do ciclo caem em endereço nil,
			ficam armazenadas no início da pilha.
			
			Quanto maior a pilha, mais iterações levam para chegar
			algum valôr. Até lá, foram-se os índices.
		*/


		if (tf.charactére == LINHA_NIL) continue;

		if (tf.pula != 0) {
			tf.pula--;
			continue;
		}





































        // MUDAR AS LINHAS PELO FILHO NA GRADE
        // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

        linha_grade = grade_procurar(var_nome(linha), &operadores_grade__2);


		/*
			Ao conceder uma clave, espera-se uma concessão.
		
			Se a concessão vier antes da clave, será tratada como clave e a concessão não será reconhecida.
			Se a concessão vier antes e depois da clave, a primeira concessão fará parte do nome da clave.
			Se a concessão vier antes, depois da clave, e antes ou depois do valôr, será tratada como valôr
			e/ou nome da clave.
		*/
		if (operador__2.expectação == expectação__concessão) {
			if (tf.verificar_concessão_objectiva(&tf, &expressão_grade__2, &operador__2, &operador_linha__2))
			{
				continue;
			}

			if (clave_têr_por_tipo(clave_lêr).pala[tf.clave_n] == tf.charactére) {
				linha_aparar(&operador_linha__2);

				tf.operador_n++;
				operação_re_definir(tf.operador_n, &expressão_grade__2, expectação__valôr, operação__concessão_directa, 2);

				tf.operador_linha_n = 0;
				operador_linha__2[tf.operador_linha_n] = tf.charactére;
				operador_linha__2[tf.operador_linha_n + 1] = LINHA_NIL;

				DESBRAGA_MENSAGEM("%c, %d", operador_linha__2[tf.operador_linha_n], operador__2.índice);

				if (clave_têr_por_tipo(clave_corrêr).pala[1] == tf.pilha.conteúdo[tf.recúo - 2]) {
					tf.operador_linha_n++;
					operador_linha__2[tf.operador_linha_n] = tf.pilha.conteúdo[tf.recúo - 2];
					operador_linha__2[tf.operador_linha_n + 1] = LINHA_NIL;

					operador__2.tipo = operação__concessão_corredora;

					tf.pula = 1;

					DESBRAGA_MENSAGEM("%c, %d", operador_linha__2[tf.operador_linha_n], operador__2.índice);
				}

				if (clave_têr_por_tipo(clave_lêr).pala[tf.clave_n] == tf.pilha.conteúdo[tf.recúo - 2]) {
					tf.operador_linha_n++;
					operador_linha__2[tf.operador_linha_n] = tf.pilha.conteúdo[tf.recúo - 2];
					operador_linha__2[tf.operador_linha_n + 1] = LINHA_NIL;

					operador__2.tipo = operação__concessão_passiva;

					tf.pula = 1;

					DESBRAGA_MENSAGEM("%c", operador_linha__2[tf.operador_linha_n]);

					if (clave_têr_por_tipo(clave_lêr).pala[tf.clave_n] == tf.pilha.conteúdo[tf.recúo - 3]) {
						tf.operador_linha_n++;
						operador_linha__2[tf.operador_linha_n] = tf.pilha.conteúdo[tf.recúo - 3];
						operador_linha__2[tf.operador_linha_n + 1] = LINHA_NIL;

						operador__2.tipo = operação__concessão_selectiva;

						tf.pula = 2;

						DESBRAGA_MENSAGEM("%c", operador_linha__2[tf.operador_linha_n]);
					}
				}
			}

			if (operador__2.tipo == operação__concedido) operador__2.expectação = expectação__concedido;
			else if (operador__2.tipo == operação__concessão_directa ||
				operador__2.tipo == operação__concessão_corredora ||
				operador__2.tipo == operação__concessão_passiva ||
				operador__2.tipo == operação__concessão_selectiva
				) {
				linha_aparar(&operador_linha__2);
				tf.operador_linha_n = 0;

				tf.operador_n++;
				operação_re_definir(tf.operador_n, &expressão_grade__2, expectação__nil, operação__valôr, 1);
				continue;
			}
		}


































		tf.introduzir_concedido(&tf, &operador__2, &operador_linha__2);
    }

fim:

memória_des_allocar(&tf.pilha.conteúdo);
memória_des_allocar(&tf.ficha);

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
#undef operador_grade__2
#undef operador_linha__2
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
