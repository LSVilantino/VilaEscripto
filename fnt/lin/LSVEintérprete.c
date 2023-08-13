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

Linha 
rastilho_têr_linha_por_tipo(Rastilho_Tipo tipo) {
	Linha linha = LINHA_NIL;

	switch (tipo)
	{
	case rastilho__carece_concedido: 				{ linha = "Carece concedido/clave, indefinido."; 									break; }
	case rastilho__carece_concessão: 				{ linha = "Carece concessão/separador."; 											break; }
	case rastilho__carece_concessão_válida: 		{ linha = "A concessão é inválida"; 												break; }
	case rastilho__carece_ficha_válida: 			{ linha = "A ficha é inválida"; 													break; }
	case rastilho__carece_valôr: 					{ linha = "Carece valôr à clave"; 													break; }
	case rastilho__expressão_excedente: 			{ linha = "Existem mais operaçãoes do que o esperado, formatação incorrecta."; 		break; }
	case rastilho__encerro_forçado: 				{ linha = "Encerrou-se o ficheiro forçadamente."; 									break; }
	case rastilho__comentário: 						{ linha = "Expressão comentada."; 													break; }
	
	default: break;
	}

	return linha;
}

void 
operação_re_definir(int operação_n, Grade* expressão, Expectação expectação, Operação_Tipo operação_tipo, size_t linha_t) {
#if defined(DEFINIÇÃO)

#define expressão_            		(*expressão)
#define operaçãoes_           		(expressão_.filho)
#define operação_grade_       		(operaçãoes_[operação_n])
#define operação_             		(**(Operação**) &operação_grade_.elemento)

#endif // #if defined(DEFINIÇÃO)

	grade_introduzir(&operaçãoes_,
		(Grade) {
		.índice = operação_n,
        .constatação = nil,
		.tipo = lsve_tipo_operação,
		.precisa_libertar = vero,
		.elemento = memória_allocar(sizeof(Operação))
		}
	);
    
	operação_.índice = operação_n;
	operação_.tipo = operação_tipo;
	operação_.expectação = expectação;

	int índice = 0;

	grade_introduzir(&operação_grade_.filho,
		(Grade) {
		.índice = índice++,
		.constatação = var_nome(membros(Operação).linha),
		.tipo = lsve_tipo_linha,
		.precisa_libertar = vero,
		.elemento = memória_allocar(linha_t)
		}
	);

#if defined(DES_DEFINIÇÃO)

#undef operação_re_definir__
#undef expressão_
#undef operaçãoes_
#undef operação_grade_
#undef operação_

#endif // #if defined(DES_DEFINIÇÃO)
}

Grade 
operação_falha() {
	return grade_falha();
}

Grade 
expressão_têr_por_ficha(Grade expressões[], Linha ficha) {
#define expressão_ (expressões[expressão_n])

	int expressão_n = 0;

	while (expressão_.índice == expressão_n) {
		if (expressão_operação_têr_por_ficha(expressão_, ficha).índice differente -1) {
			return expressão_;
		}

		expressão_n++;
	}

	return expressão_falha();

#undef expressão_
}

Grade 
expressão_operação_têr_por_ficha(Grade expressão, Linha linha) {
#define operação_linha_ (*(Linha*) &operação_linha_grade->elemento)

	Grade operação = expressão_operação_têr_por_tipo(expressão, operação__concedido);
	Grade* operação_linha_grade = grade_procurar(var_nome(membros(Operação).linha), (Grade**) &operação);

	if (linha_comparar(linha, operação_linha_)) return operação;
	return operação_falha();

#undef operação_linha_
}

Grade 
expressão_operação_têr_por_tipo(Grade expressão, Operação_Tipo tipo) {
#define operação_grade_ 	(expressão.filho[operação_n])
#define operação_ 			(**(Operação**) &expressão.filho[operação_n].elemento)

	int operação_n = 0;

  	while (operação_grade_.índice == operação_n) {
		if (operação_.tipo == tipo) {
			return operação_grade_;
		}

		operação_n++;
	}

	return operação_falha();

#undef operação_grade_
#undef operação_
}

Grade 
expressão_falha() {
	Grade expressãoFalha = grade_falha();

	operação_re_definir(0, &expressãoFalha, expectação__nil, operação__nil, 1);
	expressãoFalha.filho[0] = grade_falha();

	return expressãoFalha;
}

typedef struct TF_Interpretar TF_Interpretar;
struct TF_Interpretar{
	int
	*expressão_n,
    operação_n,
    operação_linha_n,
    linha_n,
    clave_n,
    ficha_n,
	rastilho_n,
    pula
    ;

	Pilha pilha; int recúo;
	Linha ficha;
	char charactére;

	void (*intérprete_rastilho_definir)(TF_Interpretar* tf, Grade* intérprete, Rastilho_Tipo rastilho_tipo);

	Dico (*clave_verificar_encerro_forçado)(TF_Interpretar* tf, Grade* intérprete);
	Dico (*clave_verificar_comentário)(TF_Interpretar* tf, Grade* intérprete);

	Dico (*clave_verificar_concessão_directa)(TF_Interpretar* tf, Grade* intérprete);
	Dico (*clave_verificar_concessão_corredora)(TF_Interpretar* tf, Grade* intérprete);
	Dico (*clave_verificar_concessão_objectiva)(TF_Interpretar* tf, Grade* intérprete);
	Dico (*clave_verificar_concessão_passiva)(TF_Interpretar* tf, Grade* intérprete);
	Dico (*clave_verificar_concessão_selectiva)(TF_Interpretar* tf, Grade* intérprete);
	void (*introduzir_concedido)(TF_Interpretar* tf, Grade* intérprete);

	void (*operação_aparar_e_re_definir)(TF_Interpretar* tf, Grade* intérprete);
};

Dico interpretar_linha__clave_verificar_encerro_forçado(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_				(*((Intérprete*) (*intérprete)->elemento))
#define intérprete_grade_		(*intérprete)
#define rastilho_				(Rastilho*) &intérprete_.filho[1].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operaçãoes_grade_		(expressão_grade_.filho)
#define operaçãoes_				(**(Operação**) &operaçãoes_grade_[tf_.operação_n].elemento)
#define operação_				(operaçãoes_)
#define operação_grade_			(operaçãoes_grade_[tf_.operação_n])
#define operação_linha_      	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_ficheiro_forçar_encerro).pala[0] iqual tf_.charactére) {
		Grade* operação_linha_grade = grade_procurar(var_nome(membros(Operação).linha), &operaçãoes_grade_);
		
		//expressão_ = expressão_falha();
		//expressão_rastilho_definir(&expressão_, rastilho_encerro_forçado);
		operação_linha_ = LINHA_NIL;

		expressão_.índice = expressão_n_;
		expressão_n_++;

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef intérprete_grade_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operaçãoes_grade_
#undef operaçãoes_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

Dico interpretar_linha__clave_verificar_comentário(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_				(*((Intérprete*) (*intérprete)->elemento))
#define intérprete_grade_		(*intérprete)
#define rastilho_				(Rastilho*) &intérprete_.filho[1].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operaçãoes_grade_		(expressão_grade_.filho)
#define operaçãoes_				(**(Operação**) &operaçãoes_grade_[tf_.operação_n].elemento)
#define operação_				(operaçãoes_)
#define operação_grade_			(operaçãoes_grade_[tf_.operação_n])
#define operação_linha_      	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;


	if (clave_têr_por_tipo(clave_ficheiro_comentário).pala[0] iqual tf_.charactére) {
		Grade* operação_linha_grade = grade_procurar(var_nome(membros(Operação).linha), &operaçãoes_grade_);
		
		//expressão_ = expressão_falha();
		//expressão_rastilho_definir(&expressão_, rastilho_comentário);
		operação_.tipo = operação__concedido;
		operação_linha_ = LINHA_NIL;

		expressão_.índice = expressão_n_;
		expressão_n_++;

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef intérprete_grade_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operaçãoes_grade_
#undef operaçãoes_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

void interpretar_linha__introduzir_concedido(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_				(*((Intérprete*) (*intérprete)->elemento))
#define intérprete_grade_		(*intérprete)
#define rastilho_				(Rastilho*) &intérprete_.filho[1].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operaçãoes_grade_		(expressão_grade_.filho)
#define operaçãoes_				(**(Operação**) &operaçãoes_grade_[tf_.operação_n].elemento)
#define operação_				(operaçãoes_)
#define operação_grade_			(operaçãoes_grade_[tf_.operação_n])
#define operação_linha_      	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	if (operação_.expectação iqual expectação__concedido ou operação_.expectação iqual expectação__nil)
	{
		Grade* operação_linha_grade = grade_procurar(var_nome(membros(Operação).linha), &operaçãoes_grade_);

		linha_introduzir_charactére(tf_.charactére, tf_.operação_linha_n, &operação_linha_);
		DESBRAGA_MENSAGEM("%c, %d", operação_linha_[tf_.operação_linha_n], operação_.índice);

		tf_.operação_linha_n++;

		if (operação_.tipo iqual operação__concedido) operação_.expectação = expectação__concessão;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef intérprete_grade_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operaçãoes_grade_
#undef operaçãoes_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
}

Dico interpretar_linha__clave_verificar_concessão_directa(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_				(*((Intérprete*) (*intérprete)->elemento))
#define intérprete_grade_		(*intérprete)
#define rastilho_				(Rastilho*) &intérprete_.filho[1].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operaçãoes_grade_		(expressão_grade_.filho)
#define operaçãoes_				(**(Operação**) &operaçãoes_grade_[tf_.operação_n].elemento)
#define operação_				(operaçãoes_)
#define operação_grade_			(operaçãoes_grade_[tf_.operação_n])
#define operação_linha_      	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf_.clave_n] iqual tf_.charactére) {
		Grade* operação_linha_grade = grade_procurar(var_nome(membros(Operação).linha), &operaçãoes_grade_);

		linha_aparar(&operação_linha_);

		tf_.operação_n++;
		operação_re_definir(tf_.operação_n, &expressão_grade_, expectação__valôr, operação__concessão_directa, 2);

		tf_.operação_linha_n = 0;
		operação_linha_[tf_.operação_linha_n] = tf_.charactére;
		operação_linha_[tf_.operação_linha_n + 1] = LINHA_NIL;

		DESBRAGA_MENSAGEM("%c, %d", operação_linha_[tf_.operação_linha_n], operação_.índice);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef intérprete_grade_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operaçãoes_grade_
#undef operaçãoes_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

Dico interpretar_linha__clave_verificar_concessão_corredora(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_				(*((Intérprete*) (*intérprete)->elemento))
#define intérprete_grade_		(*intérprete)
#define rastilho_				(Rastilho*) &intérprete_.filho[1].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operaçãoes_grade_		(expressão_grade_.filho)
#define operaçãoes_				(**(Operação**) &operaçãoes_grade_[tf_.operação_n].elemento)
#define operação_				(operaçãoes_)
#define operação_grade_			(operaçãoes_grade_[tf_.operação_n])
#define operação_linha_      	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_corrêr).pala[1] iqual tf_.pilha.conteúdo[tf_.recúo - 2]) {
		Grade* operação_linha_grade = grade_procurar(var_nome(membros(Operação).linha), &operaçãoes_grade_);

		tf_.operação_linha_n++;
		operação_linha_[tf_.operação_linha_n] = tf_.pilha.conteúdo[tf_.recúo - 2];
		operação_linha_[tf_.operação_linha_n + 1] = LINHA_NIL;

		operação_.tipo = operação__concessão_corredora;

		tf_.pula = 1;

		DESBRAGA_MENSAGEM("%c, %d", operação_linha_[tf_.operação_linha_n], operação_.índice);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef intérprete_grade_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operaçãoes_grade_
#undef operaçãoes_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

Dico interpretar_linha__clave_verificar_concessão_objectiva(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_				(*((Intérprete*) (*intérprete)->elemento))
#define intérprete_grade_		(*intérprete)
#define rastilho_				(Rastilho*) &intérprete_.filho[1].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operaçãoes_grade_		(expressão_grade_.filho)
#define operaçãoes_				(**(Operação**) &operaçãoes_grade_[tf_.operação_n].elemento)
#define operação_				(operaçãoes_)
#define operação_grade_			(operaçãoes_grade_[tf_.operação_n])
#define operação_linha_      	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_ficha).pala[1] iqual tf_.pilha.conteúdo[tf_.recúo - 2]) {
		Grade* operação_linha_grade = grade_procurar(var_nome(membros(Operação).linha), &operaçãoes_grade_);
		linha_aparar(&operação_linha_);

		tf_.operação_n++;
		operação_re_definir(tf_.operação_n, &expressão_grade_, expectação__valôr, operação__concessão_directa, 1);

		tf_.operação_linha_n = 0;
		operação_.expectação = expectação__nil;
		operação_.tipo = operação__concessão_objectiva;

		tf_.pula = 1;
		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef intérprete_grade_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operaçãoes_grade_
#undef operaçãoes_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

Dico interpretar_linha__clave_verificar_concessão_passiva(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_				(*((Intérprete*) (*intérprete)->elemento))
#define intérprete_grade_		(*intérprete)
#define rastilho_				(Rastilho*) &intérprete_.filho[1].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operaçãoes_grade_		(expressão_grade_.filho)
#define operaçãoes_				(**(Operação**) &operaçãoes_grade_[tf_.operação_n].elemento)
#define operação_				(operaçãoes_)
#define operação_grade_			(operaçãoes_grade_[tf_.operação_n])
#define operação_linha_      	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf_.clave_n] iqual tf_.pilha.conteúdo[tf_.recúo - 2]) {
		Grade* operação_linha_grade = grade_procurar(var_nome(membros(Operação).linha), &operaçãoes_grade_);

		tf_.operação_linha_n++;
		operação_linha_[tf_.operação_linha_n] = tf_.pilha.conteúdo[tf_.recúo - 2];
		operação_linha_[tf_.operação_linha_n + 1] = LINHA_NIL;

		operação_.tipo = operação__concessão_passiva;

		tf_.pula = 1;

		DESBRAGA_MENSAGEM("%c", operação_linha_[tf_.operação_linha_n]);

		resultado = vero;
	}


#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef intérprete_grade_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operaçãoes_grade_
#undef operaçãoes_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

Dico interpretar_linha__clave_verificar_concessão_selectiva(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_				(*((Intérprete*) (*intérprete)->elemento))
#define intérprete_grade_		(*intérprete)
#define rastilho_				(Rastilho*) &intérprete_.filho[1].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operaçãoes_grade_		(expressão_grade_.filho)
#define operaçãoes_				(**(Operação**) &operaçãoes_grade_[tf_.operação_n].elemento)
#define operação_				(operaçãoes_)
#define operação_grade_			(operaçãoes_grade_[tf_.operação_n])
#define operação_linha_      	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf_.clave_n] iqual tf_.pilha.conteúdo[tf_.recúo - 3]) {
		Grade* operação_linha_grade = grade_procurar(var_nome(membros(Operação).linha), &operaçãoes_grade_);

		tf_.operação_linha_n++;
		operação_linha_[tf_.operação_linha_n] = tf_.pilha.conteúdo[tf_.recúo - 3];
		operação_linha_[tf_.operação_linha_n + 1] = LINHA_NIL;

		operação_.tipo = operação__concessão_selectiva;

		tf_.pula = 2;

		DESBRAGA_MENSAGEM("%c", operação_linha_[tf_.operação_linha_n]);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef intérprete_grade_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operaçãoes_grade_
#undef operaçãoes_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

void interpretar_linha__operação_aparar_e_re_definir(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_				(*((Intérprete*) (*intérprete)->elemento))
#define intérprete_grade_		(*intérprete)
#define rastilho_				(*(Rastilho*) &intérprete_.filho[1].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operaçãoes_grade_		(expressão_grade_.filho)
#define operaçãoes_				(**(Operação**) &operaçãoes_grade_[tf_.operação_n].elemento)
#define operação_				(operaçãoes_)
#define operação_grade_			(operaçãoes_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Grade* operação_linha_grade = grade_procurar(var_nome(membros(Operação).linha), &operaçãoes_grade_);

	linha_aparar(&operação_linha_);
	tf_.operação_linha_n = 0;

	tf_.operação_n++;
	operação_re_definir(tf_.operação_n, &expressão_grade_, expectação__nil, operação__valôr, 1);

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef intérprete_grade_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operaçãoes_grade_
#undef operaçãoes_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
}

void interpretar_linha__intérprete_rastilho_definir(TF_Interpretar* tf, Grade* intérprete, Rastilho_Tipo rastilho_tipo) {
#if defined(DEFINIÇÃO)

#define tf_ 				(*tf)
#define intérprete_grade_ 	(*intérprete)
#define intérprete_ 		(*(Intérprete*) intérprete_grade_.elemento)
#define rastilhos_			(intérprete_grade_.filho[1].filho)
#define rastilho_			(rastilhos_[tf_.rastilho_n])

#endif // #if defined(DEFINIÇÃO)

	grade_introduzir(&rastilhos_, (Grade) {
		.constatação = var_nome(rastilho),
		.índice = 0,
		.elemento = &(Rastilho) {
			.índice = 0,
			.tipo = rastilho_tipo,
			.erro = rastilho_definir_linha_de_erro(rastilho_tipo)
		},
		.precisa_libertar = fal,
		.tipo = lsve_tipo_rastilho
	});

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef rastilhos_
#undef rastilho_

#endif // #if defined(DES_DEFINIÇÃO)
}

void intérprete_agregar(Expressão* expressões, int* posição, Intérprete* agregado) {

	//printf("\n\n\n---------------\n\n\n");

	int expressão_n = 0;
	while (expressões[expressão_n].índice == expressão_n) {
		(*agregado).expressão = memória_re_allocar(((*posição) + 1) * sizeof(Expressão), (*agregado).expressão);
		(*agregado).expressão[(*posição)] = expressões[expressão_n];

		(*agregado).expressão[(*posição)].índice = (*posição);

		//printf("%d - %s\n", (*agregado).expressão[(*posição)].índice, (*agregado).expressão[(*posição)].operação[0].linha);

		expressão_n++; (*posição)++;
	}
}

void 
interpretar_linha(const Grade* linha, Grade* intérprete, int* expressão_n) {
#if defined(DEFINIÇÃO)

#define linha_					((Linha) (*linha).elemento)
#define intérprete_				(*((Intérprete*) (*intérprete).elemento))
#define intérprete_grade_		(*intérprete)
#define rastilhos_				(intérprete_.filho[1].filho)
#define rastilho_				(*(Rastilho*) rastilhos_[tf.rastilho_n].elemento)
#define expressão_n_			(*tf.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(*(Expressão*) expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operaçãoes_grade_		(expressão_grade_.filho)
#define operaçãoes_				(operaçãoes_grade_[tf.operação_n])
#define operação_				(*(Operação*) operaçãoes_.elemento)
#define operação_grade_			(operaçãoes_grade_[tf.operação_n])
#define operação_linha_       	((Linha) operação_linha_grade->elemento)
#define ficha_valôr_linha_		((Linha) valôrDaFicha_linha_grade->elemento)
#define recúo_                	(tf.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Grade* operação_linha_grade = nil;

	TF_Interpretar tf = {
		.expressão_n = &(*expressão_n),
    	.operação_n = 0,
    	.operação_linha_n = 0,

		.linha_n = 0,
    	.clave_n = 0,
    	.ficha_n = 0,

    	.pula = 0,

		.pilha = pilha_construir((Lato[])
		{
			(Lato) { tipo_tamanho, fal, &(int){3} }
		}),

		.ficha = memória_preên_allocar(1, sizeof(char)),

		.intérprete_rastilho_definir = interpretar_linha__intérprete_rastilho_definir,

		.introduzir_concedido = interpretar_linha__introduzir_concedido,
		
		.clave_verificar_comentário = interpretar_linha__clave_verificar_comentário,
		.clave_verificar_encerro_forçado = interpretar_linha__clave_verificar_encerro_forçado,
		.clave_verificar_concessão_directa = interpretar_linha__clave_verificar_concessão_directa,
		.clave_verificar_concessão_corredora = interpretar_linha__clave_verificar_concessão_corredora,
		.clave_verificar_concessão_objectiva = interpretar_linha__clave_verificar_concessão_objectiva,
		.clave_verificar_concessão_passiva = interpretar_linha__clave_verificar_concessão_passiva,
		.clave_verificar_concessão_selectiva = interpretar_linha__clave_verificar_concessão_selectiva,

		.operação_aparar_e_re_definir = interpretar_linha__operação_aparar_e_re_definir,
	};

    tf.recúo = tf.pilha.recúo;

    DESBRAGA_MENSAGEM("LINHA A DESBRAGAR %s", linha_)

    grade_introduzir(&expressões_grade_, 
        (Grade) {
        .índice = expressão_n_,
        .constatação = var_nome(expressão),
        .tipo = lsve_tipo_expressão, 
        .precisa_libertar = vero, 
        .elemento = memória_allocar(sizeof(Grade))
        }
    );

    operação_re_definir(tf.operação_n, &expressão_grade_, expectação__concedido, operação__concedido, 1);

    while(tf.recúo > 1) {
        /* 
			Ao fim da linha, diminui - se o recúo da pilha, até chegar à ponta,
			o último charactére armazenado.

			Se a linha não estiver ao fim, introduz o último charactére à pilha.
		*/
		if (linha_[tf.linha_n] iqual LINHA_NIL) { tf.recúo--; }
		else {
			pilha_introduzir(linha_[tf.linha_n], &tf.pilha);
			
            tf.linha_n++;
		}
        
		tf.charactére = tf.pilha.conteúdo[recúo_];
        //DESBRAGA_MENSAGEM("%c", charactére)

        /*
			As primeiras corridas do ciclo caem em endereço nil,
			ficam armazenadas no início da pilha.
			
			Quanto maior a pilha, mais iterações levam para chegar
			algum valôr. Até lá, foram-se os índices.
		*/


		if (tf.charactére iqual LINHA_NIL) continue;
		if (tf.pula differente 0) {
			tf.pula--;
			continue;
		}

		/*
			Se o encerro forçado for encontrado, encerra-se tudo e retorna o que foi armazenado.

			Reporta rastilho.
		*/
		if (tf.clave_verificar_encerro_forçado(&tf, &intérprete_grade_)) {
			break;
		}

		/*
			Se um comentário for encontrado, ignora a linha.

			Reporta rastilho.
		*/
		if (tf.clave_verificar_comentário(&tf, &intérprete_grade_)) {
			break;
		}

		if (clave_têr_por_tipo(clave_ficha).pala[0] iqual tf.charactére) {
			operação_.expectação = expectação__ficha_abre;
			continue;
		}

		if (clave_têr_por_tipo(clave_ficha).pala[1] iqual tf.charactére e
			operação_.expectação iqual expectação__ficha_abre)
		{
			operação_.expectação = expectação__ficha_fecha;
			continue;
		}

		// Leitura da ficha
		if (operação_.expectação iqual expectação__ficha_fecha) {
			if (clave_têr_por_tipo(clave_ficha).pala[2] iqual tf.charactére) {
				/*
					Uma vez lida a clave da ficha, obtém-se seu valôr.
				*/
				Grade valôrDaFicha = expressão_operação_têr_por_tipo(expressão_têr_por_ficha(&expressões_grade_, tf.ficha), operação__valôr);

				if (valôrDaFicha.índice iqual -1) {
					tf.intérprete_rastilho_definir(&tf, &intérprete_grade_, rastilho__carece_ficha_válida);
					expressão_.índice = expressão_n_++;
					break;
				}

				Grade* valôrDaFicha_linha_grade = grade_procurar(var_nome(membros(Operação).linha), &valôrDaFicha);
				linha_agregar_linha(&ficha_valôr_linha_, &tf.operação_linha_n, &operação_linha_);

				memória_des_allocar((void**) &tf.ficha);
				tf.ficha = memória_allocar(sizeof(char) * 2);
				tf.ficha[0] = LINHA_NIL;
				tf.ficha_n = 0;

				operação_.expectação = expectação__nil;
				continue;
			}

			linha_introduzir_charactére(tf.charactére, tf.ficha_n, &tf.ficha);
			tf.ficha_n++;
			continue;
		}

		// 
		if (operação_.tipo iqual operação__concessão_objectiva e 
		clave_têr_por_tipo(clave_ficha).pala[2] iqual tf.charactére)
		{
			if (clave_têr_por_tipo(clave_lêr).pala[0] iqual tf.pilha.conteúdo[tf.recúo - 2]) {
				linha_aparar(&operação_.linha);

				tf.operação_linha_n = 0;
				tf.operação_n++;

				operação_re_definir(tf.operação_n, &expressão_, expectação__nil, operação__valôr, 1);

				tf.pula = 1;
				continue;
			}
			else
			{
				tf.intérprete_rastilho_definir(&tf, &intérprete_grade_, rastilho__carece_concessão_válida);
				expressão_n_++;
				break;
			}
		}

		operação_linha_grade = grade_procurar(var_nome(membros(Operação).linha), &operaçãoes_grade_);

		/*
			A linha é o limitante que separa cada linha, quando for atingido, avalia-se a linha
			e seus elementos para averiguar a sua integridade.
		*/
		if (tf.charactére iqual LINHA_SALTA ou tf.charactére iqual EOF) {
			
			expressão_grade_.índice = (*expressão_n);
			linha_aparar(&operação_linha_);

			if (tf.operação_n iqual 0 e operação_linha_[tf.operação_linha_n] differente LINHA_NIL) {
				expressão_rastilho_definir(&expressão_grade_, rastilho__carece_concessão);
			}
			else if (tf.operação_n iqual 0 e operação_linha_[tf.operação_linha_n] iqual LINHA_NIL) {
				// Se a linha estiver vazia, inteiramente, não mostra mensagens, é irritante.
				expressão_grade_ = expressão_falha();
				expressão_rastilho_definir(&expressão_grade_, rastilho__nil);
				DESBRAGA_MENSAGEM("\n");
				break;
			}

			if (tf.operação_n iqual 1) {
				expressão_rastilho_definir(&expressão_grade_, rastilho__carece_valôr);
			}
			if (tf.operação_n iqual 2) {
				expressão_rastilho_definir(&expressão_grade_, rastilho__nil);
			}

			// Todos as operações que precisam dos valôres completos são validados após o registro de toda a linha.
			if (expressão_operação_têr_por_tipo(expressão_grade_, operação__concessão_corredora).índice differente -1) {
				Grade operação = expressão_operação_têr_por_tipo(expressão_grade_, operação__valôr);
				Grade operação_linha = grade_procurar(var_nome(membros(Operação).linha), &operação);

				system((Linha) operação_linha.elemento);
			}

			if (expressão_operação_têr_por_tipo(expressão_grade_, operação__concessão_passiva).índice differente -1) {
				Grade caminho = expressão_operação_têr_por_tipo(expressão_grade_, operação__valôr);
				char** ficheiro_linhas = ficheiro_lêr(caminho.linha);
				Intérprete* dado = memória_allocar(sizeof(Intérprete));
				dado->expressão = NULL;
				interpretar(ficheiro_linhas, dado);

				(*expressão_n)++;

				intérprete_agregar(dado->expressão, expressão_n, intérprete);
				free(dado);
				continue;
			}

			if (expressão_operação_têr_por_tipo(expressão_grade_, operação__concessão_objectiva).índice differente -1) {
				Grade caminho = expressão_operação_têr_por_tipo(expressão_grade_, operação__valôr);
				char** ficheiro_linhas = ficheiro_lêr(caminho.linha);
				Intérprete* dado = memória_allocar(sizeof(Intérprete));
				dado->expressão = NULL;
				int dado_n = 0;
				intérprete_agregar((*intérprete).expressão, &dado_n, dado);

				interpretar(ficheiro_linhas, dado);

				Expressão b = expressão_têr_por_ficha(dado->expressão, a.linha);
				Operação d = expressão_operação_têr_por_tipo(b, operação__valôr);

				expressão_grade_.operação[caminho.índice].linha = b.operação[d.índice].linha;
				(*expressão_n)++;
				free(dado);
				continue;
			}

			if (expressão_operação_têr_por_tipo(expressão_grade_, operação__concessão_selectiva).índice differente -1) {
				Grade caminho = expressão_operação_têr_por_tipo(expressão_grade_, operação__valôr);
				char** ficheiro_linhas = ficheiro_lêr(caminho.linha);
				Intérprete* dado = memória_allocar(sizeof(Intérprete));
				dado->expressão = NULL;
				interpretar(ficheiro_linhas, dado);

				Operação operaçãoSeleccionada = lsve_consola_construir_menu(dado->expressão);

				Expressão b = expressão_têr_por_ficha(operaçãoSeleccionada.linha, dado->expressão);
				Operação d = expressão_operação_têr_por_tipo(b, operação__valôr);

				expressão_grade_.operação[caminho.índice].linha = b.operação[d.índice].linha;
				(*expressão_n)++;
				free(dado);
				continue;
			}
			
			
			expressão_n_++;
			continue;
		}

		/*
			Ao conceder uma clave, espera-se uma concessão.
		
			Se a concessão vier antes da clave, será tratada como clave e a concessão não será reconhecida.
			Se a concessão vier antes e depois da clave, a primeira concessão fará parte do nome da clave.
			Se a concessão vier antes, depois da clave, e antes ou depois do valôr, será tratada como valôr
			e/ou nome da clave.
		*/
		if (operação_.expectação iqual expectação__concessão) {
			if (tf.clave_verificar_concessão_directa(&tf, &intérprete_grade_)) {				
				if (tf.clave_verificar_concessão_objectiva(&tf, &intérprete_grade_)) {
					continue;
				}

				if (tf.clave_verificar_concessão_corredora(&tf, &intérprete_grade_)) {
					tf.operação_aparar_e_re_definir(&tf, &intérprete_grade_);
					continue;
				}

				if (tf.clave_verificar_concessão_passiva(&tf, &intérprete_grade_)) {
					if (tf.clave_verificar_concessão_selectiva(&tf, &intérprete_grade_)) {
						tf.operação_aparar_e_re_definir(&tf, &intérprete_grade_);
						continue;	
					}

					tf.operação_aparar_e_re_definir(&tf, &intérprete_grade_);
					continue;
				}

				tf.operação_aparar_e_re_definir(&tf, &intérprete_grade_);
				continue;
			}

			operação_.expectação = expectação__concedido;
		}

		tf.introduzir_concedido(&tf, &intérprete_grade_);
    }

fim:

#if defined(DES_DEFINIÇÃO)

#undef interpretar_linha__
#undef linha__
#undef intérprete_
#undef intérprete_grade_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operaçãoes_grade_
#undef operaçãoes_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	memória_des_allocar((void**) &tf.pilha.conteúdo);
	memória_des_allocar((void**) &tf.ficha);

	return;
}

void
interpretar(const Grade* linhas[], Grade* intérprete[]) {
#if defined(DEFINIÇÃO)

#define linhas_                   (*linhas)
#define intérprete_grade_         ((*intérprete)[0])
#define intérprete_               (*(Intérprete*) intérprete_grade_.elemento)
#define expressões_grade_         (intérprete_grade_.filho)
#define expressão_grade_          (intérprete_.filho[0])
#define expressão_                ((Expressão) expressão_grade_.elemento[expressão_n - 1])
#define rastilho_                 ((Rastilho*) intérprete_.filho[1].elemento)

#endif // #if defined(DEFINIÇÃO)

    if (intérprete_grade_.tipo differente lsve_tipo_intérprete) { 
        DESBRAGA_MENSAGEM("Grade não é do tipo correcto")
		abort();
        goto fim;
    }

    int 
    linhas_n = 0, 
    expressão_n = 0
    ;

    while(linhas_[linhas_n].índice iqual linhas_n) {
        if (linhas_[linhas_n].tipo iqual tipo_linha) {
            intérprete_grade_.filho = memória_re_allocar((expressão_n + 1) * sizeof(Grade), intérprete_grade_.filho);

            interpretar_linha(&linhas_[linhas_n], &intérprete_grade_, &expressão_n);
            linhas_n++;

			continue;
        }
        
		goto fim;
    }

fim:

#if defined(DES_DEFINIÇÃO)

#undef interpretar_
#undef linhas_
#undef intérprete_grade_
#undef intérprete_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef rastilho_

#endif // #if defined(DES_DEFINIÇÃO)

	return;
}
