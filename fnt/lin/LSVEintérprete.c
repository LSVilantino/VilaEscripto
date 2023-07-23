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

	Dico (*clave_verificar_concessão_directa)(TF_Interpretar* tf, Grade* expressão_grade, Linha* operador_linha);
	Dico (*clave_verificar_concessão_corredora)(TF_Interpretar* tf, Operação* operador, Linha* operador_linha);
	Dico (*clave_verificar_concessão_objectiva)(TF_Interpretar* tf, Grade* expressão_grade, Linha* operador_linha);
	Dico (*clave_verificar_concessão_passiva)(TF_Interpretar* tf, Operação* operador, Linha* operador_linha);
	Dico (*clave_verificar_concessão_selectiva)(TF_Interpretar* tf, Operação* operador, Linha* operador_linha);
	void (*introduzir_concedido)(TF_Interpretar* tf, Operação* operador, Linha* operador_linha);

	void (*operador_aparar_e_re_definir)(TF_Interpretar* tf, Grade* expressão_grade, Linha* operador_linha);
} ;

void interpretar_linha__introduzir_concedido(TF_Interpretar* tf, Operação* operador, Linha* operador_linha) {
#if 0==0

#define tf__4 					(*tf)
#define operador__4 			(*operador)
#define operador_linha__4 		(*operador_linha)

#endif // #if 0==0

	if (operador__4.expectação == expectação__concedido || operador__4.expectação == expectação__nil)
	{
		linha_introduzir_charactére(tf__4.charactére, tf__4.operador_linha_n, &operador_linha__4);
		DESBRAGA_MENSAGEM("%c, %d", operador_linha__4[tf__4.operador_linha_n], operador__4.índice);

		tf__4.operador_linha_n++;

		if (operador__4.tipo == operação__concedido) operador__4.expectação = expectação__concessão;
	}

#if 0==0

#undef tf__4
#undef operador__4
#undef operador_linha__4

#endif // #if 0==0
}

Dico interpretar_linha__clave_verificar_concessão_directa(TF_Interpretar* tf, Grade* expressão_grade, Linha* operador_linha) {
#if 0==0

#define tf__6 					(*tf)
#define expressão_grade__6 		(*expressão_grade)
#define operadores_grade__6		(expressão_grade__6.filho)
#define operadores__6			(**(Operação**) &operadores_grade__6[tf__6.operador_n].elemento)
#define operador__6				((operadores__6))
#define operador_linha__6 		(*operador_linha)

#endif // #if 0==0

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf__6.clave_n] == tf__6.charactére) {
		linha_aparar(&operador_linha__6);

		tf__6.operador_n++;
		operação_re_definir(tf__6.operador_n, &expressão_grade__6, expectação__valôr, operação__concessão_directa, 2);

		tf__6.operador_linha_n = 0;
		operador_linha__6[tf__6.operador_linha_n] = tf__6.charactére;
		operador_linha__6[tf__6.operador_linha_n + 1] = LINHA_NIL;

		DESBRAGA_MENSAGEM("%c, %d", operador_linha__6[tf__6.operador_linha_n], operador__6.índice);

		resultado = vero;
	}

#if 0==0

#undef tf__6
#undef expressão_grade__6
#undef operador__6
#undef operador_linha__6

#endif // #if 0==0

return resultado;
}

Dico interpretar_linha__clave_verificar_concessão_corredora(TF_Interpretar* tf, Operação* operador, Linha* operador_linha) {
#if 0==0

#define tf__7 					(*tf)
#define operador__7 			(*operador)
#define operador_linha__7 		(*operador_linha)

#endif // #if 0==0

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_corrêr).pala[1] == tf__7.pilha.conteúdo[tf__7.recúo - 2]) {
		tf__7.operador_linha_n++;
		operador_linha__7[tf__7.operador_linha_n] = tf__7.pilha.conteúdo[tf__7.recúo - 2];
		operador_linha__7[tf__7.operador_linha_n + 1] = LINHA_NIL;

		operador__7.tipo = operação__concessão_corredora;

		tf__7.pula = 1;

		DESBRAGA_MENSAGEM("%c, %d", operador_linha__7[tf__7.operador_linha_n], operador__7.índice);

		resultado = vero;
	}

#if 0==0

#undef tf__7
#undef operador__7
#undef operador_linha__7

#endif // #if 0==0

return resultado;
}

Dico interpretar_linha__clave_verificar_concessão_objectiva(TF_Interpretar* tf, Grade* expressão_grade, Linha* operador_linha) {
#if 0==0

#define tf__5 					(*tf)
#define expressão_grade__5 		(*expressão_grade)
#define operadores_grade__5		(expressão_grade__5.filho)
#define operadores__5			(**(Operação**) &operadores_grade__5[tf__5.operador_n].elemento)
#define operador__5				((operadores__5))
#define operador_linha__5 		(*operador_linha)

#endif // #if 0==0

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_ficha).pala[1] == tf__5.pilha.conteúdo[tf__5.recúo - 2])
	{
		linha_aparar(&operador_linha__5);

		tf__5.operador_n++;
		operação_re_definir(tf__5.operador_n, &expressão_grade__5, expectação__valôr, operação__concessão_directa, 1);

		tf__5.operador_linha_n = 0;
		operador__5.expectação = expectação__nil;
		operador__5.tipo = operação__concessão_objectiva;

		tf__5.pula = 1;
		resultado = vero;
	}

#if 0==0

#undef tf__5
#undef expressão_grade__5
#undef operadores_grade__5
#undef operadores__5
#undef operador__5
#undef operador_linha__5

#endif // #if 0==0

return resultado;
}

Dico interpretar_linha__clave_verificar_concessão_passiva(TF_Interpretar* tf, Operação* operador, Linha* operador_linha) {
#if 0==0

#define tf__8 					(*tf)
#define operador__8				(*operador)
#define operador_linha__8 		(*operador_linha)

#endif // #if 0==0
	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf__8.clave_n] == tf__8.pilha.conteúdo[tf__8.recúo - 2]) {
		tf__8.operador_linha_n++;
		operador_linha__8[tf__8.operador_linha_n] = tf__8.pilha.conteúdo[tf__8.recúo - 2];
		operador_linha__8[tf__8.operador_linha_n + 1] = LINHA_NIL;

		operador__8.tipo = operação__concessão_passiva;

		tf__8.pula = 1;

		DESBRAGA_MENSAGEM("%c", operador_linha__8[tf__8.operador_linha_n]);

		resultado = vero;
	}


#if 0==0

#undef tf__8
#undef operador__8
#undef operador_linha__8

#endif // #if 0==0

return resultado;
}

Dico interpretar_linha__clave_verificar_concessão_selectiva(TF_Interpretar* tf, Operação* operador, Linha* operador_linha) {
#if 0==0

#define tf__9 					(*tf)
#define operador__9				(*operador)
#define operador_linha__9 		(*operador_linha)

#endif //#if 0==0

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf__9.clave_n] == tf__9.pilha.conteúdo[tf__9.recúo - 3]) {
		tf__9.operador_linha_n++;
		operador_linha__9[tf__9.operador_linha_n] = tf__9.pilha.conteúdo[tf__9.recúo - 3];
		operador_linha__9[tf__9.operador_linha_n + 1] = LINHA_NIL;

		operador__9.tipo = operação__concessão_selectiva;

		tf__9.pula = 2;

		DESBRAGA_MENSAGEM("%c", operador_linha__9[tf__9.operador_linha_n]);

		resultado = vero;
	}

#if 0==0

#undef tf__9
#undef operador__9
#undef operador_linha__9

#endif // #if 0==0

return resultado;
}

void interpretar_linha__operador_aparar_e_re_definir(TF_Interpretar* tf, Grade* expressão_grade, Linha* operador_linha) {
#define tf__9 					(*tf)
#define expressão_grade__9 		(*expressão_grade)
#define operadores_grade__9		(expressão_grade__9.filho)
#define operadores__9			(**(Operação**) &operadores_grade__9[tf__9.operador_n].elemento)
#define operador__9				((operadores__9))
#define operador_linha__9 		(*operador_linha)

	linha_aparar(&operador_linha__9);
	tf__9.operador_linha_n = 0;

	tf__9.operador_n++;
	operação_re_definir(tf__9.operador_n, &expressão_grade__9, expectação__nil, operação__valôr, 1);

#undef tf__9
#undef expressão_grade__9
#undef operadores_grade__9
#undef operadores__9
#undef operador__9
#undef operador_linha__9
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
#define operadores__2			(**(Operação**) &operadores_grade__2[tf.operador_n].elemento)
#define operador__2				((operadores__2))
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
		
		.clave_verificar_concessão_directa = interpretar_linha__clave_verificar_concessão_directa,
		.clave_verificar_concessão_corredora = interpretar_linha__clave_verificar_concessão_corredora,
		.clave_verificar_concessão_objectiva = interpretar_linha__clave_verificar_concessão_objectiva,
		.clave_verificar_concessão_passiva = interpretar_linha__clave_verificar_concessão_passiva,
		.clave_verificar_concessão_selectiva = interpretar_linha__clave_verificar_concessão_selectiva,

		.operador_aparar_e_re_definir = interpretar_linha__operador_aparar_e_re_definir
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
        /* 
			Ao fim da linha, diminui - se o recúo da pilha, até chegar à ponta,
			o último charactére armazenado.

			Se a linha não estiver ao fim, introduz o último charactére à pilha.
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




		if (tf.charactére == LINHA_SALTA || tf.charactére == EOF) {
			expressão_n__2++;
			continue;
		}
































        linha_grade = grade_procurar(var_nome(linha), &operadores_grade__2);


		/*
			Ao conceder uma clave, espera-se uma concessão.
		
			Se a concessão vier antes da clave, será tratada como clave e a concessão não será reconhecida.
			Se a concessão vier antes e depois da clave, a primeira concessão fará parte do nome da clave.
			Se a concessão vier antes, depois da clave, e antes ou depois do valôr, será tratada como valôr
			e/ou nome da clave.
		*/
		if (operador__2.expectação == expectação__concessão) {
			if (tf.clave_verificar_concessão_directa(&tf, &expressão_grade__2, &operador_linha__2)) {				
				if (tf.clave_verificar_concessão_objectiva(&tf, &expressão_grade__2, &operador_linha__2))
				{
					continue;
				}

				if (tf.clave_verificar_concessão_corredora(&tf, &operador__2, &operador_linha__2)) {
					tf.operador_aparar_e_re_definir(&tf, &expressão_grade__2, &operador_linha__2);
					continue;
				}

				if (tf.clave_verificar_concessão_passiva(&tf, &operador__2, &operador_linha__2)) {
					if (tf.clave_verificar_concessão_selectiva(&tf, &operador__2, &operador_linha__2)) {
						tf.operador_aparar_e_re_definir(&tf, &expressão_grade__2, &operador_linha__2);
						continue;	
					}

					tf.operador_aparar_e_re_definir(&tf, &expressão_grade__2, &operador_linha__2);
					continue;
				}

				tf.operador_aparar_e_re_definir(&tf, &expressão_grade__2, &operador_linha__2);
				continue;
			}

			operador__2.expectação = expectação__concedido;
		}


		tf.introduzir_concedido(&tf, &operador__2, &operador_linha__2);
    }

fim:

memória_des_allocar((void**) &tf.pilha.conteúdo);
memória_des_allocar((void**) &tf.ficha);

#if 0==0

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

#endif // #if 0==0

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
            intérprete_grade__1.filho = memória_re_allocar((expressão_n + 1) * sizeof(Grade), intérprete_grade__1.filho);

            interpretar_linha(&linhas__1[linhas_n], &intérprete_grade__1, &expressão_n);
            linhas_n++;

			continue;
        }
        
		goto fim;
    }

fim:

return;

#if 0==0

#undef interpretar__1
#undef linhas__1
#undef intérprete_grade__1
#undef intérprete__1
#undef expressões__1
#undef expressão__1
#undef expressão_grade__1
#undef rastilho__1

#endif // #if 0==0
}
