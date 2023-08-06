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

Linha rastilho_definir_linha_de_erro(Rastilho_Tipo tipo) {
	Linha linha = LINHA_NIL;

	switch (tipo)
	{
	case rastilho__carece_concedido: 				{ linha = "Carece concedido/clave, indefinido."; 									break; }
	case rastilho__carece_concessão: 				{ linha = "Carece concessão/separador."; 											break; }
	case rastilho__carece_concessão_válida: 		{ linha = "A concessão é inválida"; 												break; }
	case rastilho__carece_ficha_válida: 			{ linha = "A ficha é inválida"; 													break; }
	case rastilho__carece_valôr: 					{ linha = "Carece valôr à clave"; 													break; }
	case rastilho__expressão_excedente: 			{ linha = "Existem mais operadores do que o esperado, formatação incorrecta."; 		break; }
	case rastilho__encerro_forçado: 				{ linha = "Encerrou-se o ficheiro forçadamente."; 									break; }
	case rastilho__comentário: 						{ linha = "Expressão comentada."; 													break; }
	case rastilho__nil: 							{ 																					break; }
	default: break;
	}

	return linha;
}

void operação_re_definir(int operador_n, Grade* expressão, Expectação expectação, Operação_Tipo operação_tipo, size_t linha_t) {
#if defined(DEFINIÇÃO)

#define expressão_            		(*expressão)
#define operadores_           		(expressão_.filho)
#define operador_grade_       		(operadores_[operador_n])
#define operador_             		(**(Operação**) &operador_grade_.elemento)

#endif // #if defined(DEFINIÇÃO)

	grade_introduzir(&operadores_,
		(Grade) {
		.índice = operador_n,
        .constatação = nil,
		.tipo = lsve_tipo_operador,
		.precisa_libertar = vero,
		.elemento = memória_allocar(sizeof(Operação))
		}
	);
    
	operador_.índice = operador_n;
	operador_.tipo = operação_tipo;
	operador_.expectação = expectação;

	int índice = 0;

	grade_introduzir(&operador_grade_.filho,
		(Grade) {
		.índice = índice++,
		.constatação = var_nome(linha),
		.tipo = lsve_tipo_linha,
		.precisa_libertar = vero,
		.elemento = memória_allocar(linha_t)
		}
	);

#if defined(DES_DEFINIÇÃO)

#undef operação_re_definir__
#undef expressão_
#undef operadores_
#undef operador_grade_
#undef operador_

#endif // #if defined(DES_DEFINIÇÃO)
}

typedef struct TF_Interpretar TF_Interpretar;
struct TF_Interpretar{
	int
	*expressão_n,
    operador_n,
    operador_linha_n,
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

	void (*operador_aparar_e_re_definir)(TF_Interpretar* tf, Grade* intérprete);
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
#define operadores_grade_		(expressão_grade_.filho)
#define operadores_				(**(Operação**) &operadores_grade_[tf_.operador_n].elemento)
#define operador_				(operadores_)
#define operador_grade_			(operadores_grade_[tf_.operador_n])
#define operador_linha_      	(*(Linha*) &linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_ficheiro_forçar_encerro).pala[0] == tf_.charactére) {
		Grade* linha_grade = grade_procurar(var_nome(linha), &operadores_grade_);
		
		//expressão_ = expressão_construir_falha();
		//expressão_rastilho_definir(&expressão_, rastilho_encerro_forçado);
		operador_linha_ = LINHA_NIL;

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
#undef operadores_grade_
#undef operadores_
#undef operador_
#undef operador_grade_
#undef operador_linha_
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
#define operadores_grade_		(expressão_grade_.filho)
#define operadores_				(**(Operação**) &operadores_grade_[tf_.operador_n].elemento)
#define operador_				(operadores_)
#define operador_grade_			(operadores_grade_[tf_.operador_n])
#define operador_linha_      	(*(Linha*) &linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;


	if (clave_têr_por_tipo(clave_ficheiro_comentário).pala[0] == tf_.charactére) {
		Grade* linha_grade = grade_procurar(var_nome(linha), &operadores_grade_);
		
		//expressão_ = expressão_construir_falha();
		//expressão_rastilho_definir(&expressão_, rastilho_comentário);
		operador_.tipo = operação__concedido;
		operador_linha_ = LINHA_NIL;

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
#undef operadores_grade_
#undef operadores_
#undef operador_
#undef operador_grade_
#undef operador_linha_
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
#define operadores_grade_		(expressão_grade_.filho)
#define operadores_				(**(Operação**) &operadores_grade_[tf_.operador_n].elemento)
#define operador_				(operadores_)
#define operador_grade_			(operadores_grade_[tf_.operador_n])
#define operador_linha_      	(*(Linha*) &linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	if (operador_.expectação == expectação__concedido || operador_.expectação == expectação__nil)
	{
		Grade* linha_grade = grade_procurar(var_nome(linha), &operadores_grade_);

		linha_introduzir_charactére(tf_.charactére, tf_.operador_linha_n, &operador_linha_);
		DESBRAGA_MENSAGEM("%c, %d", operador_linha_[tf_.operador_linha_n], operador_.índice);

		tf_.operador_linha_n++;

		if (operador_.tipo == operação__concedido) operador_.expectação = expectação__concessão;
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
#undef operadores_grade_
#undef operadores_
#undef operador_
#undef operador_grade_
#undef operador_linha_
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
#define operadores_grade_		(expressão_grade_.filho)
#define operadores_				(**(Operação**) &operadores_grade_[tf_.operador_n].elemento)
#define operador_				(operadores_)
#define operador_grade_			(operadores_grade_[tf_.operador_n])
#define operador_linha_      	(*(Linha*) &linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf_.clave_n] == tf_.charactére) {
		Grade* linha_grade = grade_procurar(var_nome(linha), &operadores_grade_);

		linha_aparar(&operador_linha_);

		tf_.operador_n++;
		operação_re_definir(tf_.operador_n, &expressão_grade_, expectação__valôr, operação__concessão_directa, 2);

		tf_.operador_linha_n = 0;
		operador_linha_[tf_.operador_linha_n] = tf_.charactére;
		operador_linha_[tf_.operador_linha_n + 1] = LINHA_NIL;

		DESBRAGA_MENSAGEM("%c, %d", operador_linha_[tf_.operador_linha_n], operador_.índice);

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
#undef operadores_grade_
#undef operadores_
#undef operador_
#undef operador_grade_
#undef operador_linha_
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
#define operadores_grade_		(expressão_grade_.filho)
#define operadores_				(**(Operação**) &operadores_grade_[tf_.operador_n].elemento)
#define operador_				(operadores_)
#define operador_grade_			(operadores_grade_[tf_.operador_n])
#define operador_linha_      	(*(Linha*) &linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_corrêr).pala[1] == tf_.pilha.conteúdo[tf_.recúo - 2]) {
		Grade* linha_grade = grade_procurar(var_nome(linha), &operadores_grade_);

		tf_.operador_linha_n++;
		operador_linha_[tf_.operador_linha_n] = tf_.pilha.conteúdo[tf_.recúo - 2];
		operador_linha_[tf_.operador_linha_n + 1] = LINHA_NIL;

		operador_.tipo = operação__concessão_corredora;

		tf_.pula = 1;

		DESBRAGA_MENSAGEM("%c, %d", operador_linha_[tf_.operador_linha_n], operador_.índice);

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
#undef operadores_grade_
#undef operadores_
#undef operador_
#undef operador_grade_
#undef operador_linha_
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
#define operadores_grade_		(expressão_grade_.filho)
#define operadores_				(**(Operação**) &operadores_grade_[tf_.operador_n].elemento)
#define operador_				(operadores_)
#define operador_grade_			(operadores_grade_[tf_.operador_n])
#define operador_linha_      	(*(Linha*) &linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_ficha).pala[1] == tf_.pilha.conteúdo[tf_.recúo - 2]) {
		Grade* linha_grade = grade_procurar(var_nome(linha), &operadores_grade_);
		linha_aparar(&operador_linha_);

		tf_.operador_n++;
		operação_re_definir(tf_.operador_n, &expressão_grade_, expectação__valôr, operação__concessão_directa, 1);

		tf_.operador_linha_n = 0;
		operador_.expectação = expectação__nil;
		operador_.tipo = operação__concessão_objectiva;

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
#undef operadores_grade_
#undef operadores_
#undef operador_
#undef operador_grade_
#undef operador_linha_
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
#define operadores_grade_		(expressão_grade_.filho)
#define operadores_				(**(Operação**) &operadores_grade_[tf_.operador_n].elemento)
#define operador_				(operadores_)
#define operador_grade_			(operadores_grade_[tf_.operador_n])
#define operador_linha_      	(*(Linha*) &linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf_.clave_n] == tf_.pilha.conteúdo[tf_.recúo - 2]) {
		Grade* linha_grade = grade_procurar(var_nome(linha), &operadores_grade_);

		tf_.operador_linha_n++;
		operador_linha_[tf_.operador_linha_n] = tf_.pilha.conteúdo[tf_.recúo - 2];
		operador_linha_[tf_.operador_linha_n + 1] = LINHA_NIL;

		operador_.tipo = operação__concessão_passiva;

		tf_.pula = 1;

		DESBRAGA_MENSAGEM("%c", operador_linha_[tf_.operador_linha_n]);

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
#undef operadores_grade_
#undef operadores_
#undef operador_
#undef operador_grade_
#undef operador_linha_
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
#define operadores_grade_		(expressão_grade_.filho)
#define operadores_				(**(Operação**) &operadores_grade_[tf_.operador_n].elemento)
#define operador_				(operadores_)
#define operador_grade_			(operadores_grade_[tf_.operador_n])
#define operador_linha_      	(*(Linha*) &linha_grade->elemento)
#define recúo_               	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf_.clave_n] == tf_.pilha.conteúdo[tf_.recúo - 3]) {
		Grade* linha_grade = grade_procurar(var_nome(linha), &operadores_grade_);

		tf_.operador_linha_n++;
		operador_linha_[tf_.operador_linha_n] = tf_.pilha.conteúdo[tf_.recúo - 3];
		operador_linha_[tf_.operador_linha_n + 1] = LINHA_NIL;

		operador_.tipo = operação__concessão_selectiva;

		tf_.pula = 2;

		DESBRAGA_MENSAGEM("%c", operador_linha_[tf_.operador_linha_n]);

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
#undef operadores_grade_
#undef operadores_
#undef operador_
#undef operador_grade_
#undef operador_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

void interpretar_linha__operador_aparar_e_re_definir(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_				(*((Intérprete*) (*intérprete)->elemento))
#define intérprete_grade_		(*intérprete)
#define rastilho_				(*(Rastilho*) &intérprete_.filho[1].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operadores_grade_		(expressão_grade_.filho)
#define operadores_				(**(Operação**) &operadores_grade_[tf_.operador_n].elemento)
#define operador_				(operadores_)
#define operador_grade_			(operadores_grade_[tf_.operador_n])
#define operador_linha_       	(*(Linha*) &linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Grade* linha_grade = grade_procurar(var_nome(linha), &operadores_grade_);

	linha_aparar(&operador_linha_);
	tf_.operador_linha_n = 0;

	tf_.operador_n++;
	operação_re_definir(tf_.operador_n, &expressão_grade_, expectação__nil, operação__valôr, 1);

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef intérprete_grade_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operadores_grade_
#undef operadores_
#undef operador_
#undef operador_grade_
#undef operador_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
}

void interpretar_linha__intérprete_rastilho_definir(TF_Interpretar* tf, Grade* intérprete, Rastilho_Tipo rastilho_tipo) {
#if defined(DEFINIÇÃO)

#define tf_ 				(*tf)
#define intérprete_ 		(**(Intérprete**) &(*intérprete).elemento)
#define rastilhos_			(intérprete_.rastilho)
#define rastilho_			(rastilhos_[tf_.rastilho_n])

#endif // #if defined(DEFINIÇÃO)

	memória_re_allocar(tf_.rastilho_n + 1, &rastilhos_);
	rastilho_.tipo = rastilho_tipo;
	rastilho_.erro = rastilho_definir_linha_de_erro(rastilho_tipo);

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_
#undef rastilhos_
#undef rastilho_

#endif // #if defined(DES_DEFINIÇÃO)
}

void 
interpretar_linha(const Grade* linha, Grade* intérprete, int* expressão_n) {
#if defined(DEFINIÇÃO)

#define linha_					((char*) (*linha).elemento)
#define intérprete_				(*((Intérprete*) (*intérprete)->elemento))
#define intérprete_grade_		(*intérprete)
#define rastilho_				(*(Rastilho*) &intérprete_.filho[1].elemento)
#define expressão_n_			(*tf.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operadores_grade_		(expressão_grade_.filho)
#define operadores_				(operadores_grade_[tf.operador_n])
#define operador_				(**(Operação**) &operadores_.elemento)
#define operador_grade_			(operadores_grade_[tf.operador_n])
#define operador_linha_       	(*(Linha*) &linha_grade->elemento)
#define recúo_                	(tf.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Grade* linha_grade = nil;

	TF_Interpretar tf = {
		.expressão_n = &(*expressão_n),
    	.operador_n = 0,
    	.operador_linha_n = 0,

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

		.operador_aparar_e_re_definir = interpretar_linha__operador_aparar_e_re_definir,
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

    operação_re_definir(tf.operador_n, &expressão_grade_, expectação__concedido, operação__concedido, 1);

    while(tf.recúo > 1) {
        /* 
			Ao fim da linha, diminui - se o recúo da pilha, até chegar à ponta,
			o último charactére armazenado.

			Se a linha não estiver ao fim, introduz o último charactére à pilha.
		*/
		if (linha_[tf.linha_n] == LINHA_NIL) { tf.recúo--; }
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


		if (tf.charactére == LINHA_NIL) continue;

		if (tf.pula != 0) {
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

		if (clave_têr_por_tipo(clave_ficha).pala[0] == tf.charactére) {
			operador_.expectação = expectação__ficha_abre;
			continue;
		}

		if (clave_têr_por_tipo(clave_ficha).pala[1] == tf.charactére &&
			operador_.expectação == expectação__ficha_abre)
		{
			operador_.expectação = expectação__ficha_fecha;
			continue;
		}

		// Leitura da ficha
		if (operador_.expectação == expectação__ficha_fecha) {
			if (clave_têr_por_tipo(clave_ficha).pala[2] == tf.charactére) {
				/*
					Uma vez lida a clave da ficha, obtém-se seu valôr.
				*/
				Operação valôrDaFicha = operação_daExpressão_têrPorTipo(operação__valôr, expressões_têrPorClave(tf.ficha, &expressões_grade_));

				if (valôrDaFicha.índice == -1) {
					tf.intérprete_rastilho_definir(&tf, &intérprete_grade_, rastilho__carece_ficha_válida);
					expressão_.índice = expressão_n_++;
					break;
				}

				linha_agregar_linha(valôrDaFicha.linha, &tf.operador_linha_n, &operador_.linha);

				memória_des_allocar((void**) &tf.ficha);
				tf.ficha = memória_allocar(sizeof(char) * 2);
				tf.ficha[0] = LINHA_NIL;
				tf.ficha_n = 0;

				operador_.expectação = expectação__nil;
				continue;
			}

			linha_introduzir_charactére(tf.charactére, tf.ficha_n, &tf.ficha);
			tf.ficha_n++;
			continue;
		}

		// 
		if (operador_.tipo == operação__concessão_objectiva &&
			clave_têr_por_tipo(clave_ficha).pala[2] == tf.charactére) {
			if (clave_têr_por_tipo(clave_lêr).pala[0] == tf.pilha.conteúdo[tf.recúo - 2]) {
				linha_aparar(&operador_.linha);

				tf.operador_linha_n = 0;
				tf.operador_n++;

				operação_re_definir(tf.operador_n, &expressão_, expectação__nil, operação__valôr, 1);

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

		if (tf.charactére == LINHA_SALTA || tf.charactére == EOF) {
			expressão_n_++;
			continue;
		}

		linha_grade = grade_procurar(var_nome(linha), &operadores_grade_);

		/*
			Ao conceder uma clave, espera-se uma concessão.
		
			Se a concessão vier antes da clave, será tratada como clave e a concessão não será reconhecida.
			Se a concessão vier antes e depois da clave, a primeira concessão fará parte do nome da clave.
			Se a concessão vier antes, depois da clave, e antes ou depois do valôr, será tratada como valôr
			e/ou nome da clave.
		*/
		if (operador_.expectação == expectação__concessão) {
			if (tf.clave_verificar_concessão_directa(&tf, &intérprete_grade_)) {				
				if (tf.clave_verificar_concessão_objectiva(&tf, &intérprete_grade_))
				{
					continue;
				}

				if (tf.clave_verificar_concessão_corredora(&tf, &intérprete_grade_)) {
					tf.operador_aparar_e_re_definir(&tf, &intérprete_grade_);
					continue;
				}

				if (tf.clave_verificar_concessão_passiva(&tf, &intérprete_grade_)) {
					if (tf.clave_verificar_concessão_selectiva(&tf, &intérprete_grade_)) {
						tf.operador_aparar_e_re_definir(&tf, &intérprete_grade_);
						continue;	
					}

					tf.operador_aparar_e_re_definir(&tf, &intérprete_grade_);
					continue;
				}

				tf.operador_aparar_e_re_definir(&tf, &intérprete_grade_);
				continue;
			}

			operador_.expectação = expectação__concedido;
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
#undef operadores_grade_
#undef operadores_
#undef operador_
#undef operador_grade_
#undef operador_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	memória_des_allocar((void**) &tf.pilha.conteúdo);
	memória_des_allocar((void**) &tf.ficha);

	return;
}

void
interpretar(Grade** linhas, Grade** intérprete) {
#if defined(DEFINIÇÃO)

#define linhas_                   (*linhas)
#define intérprete_grade_         ((*intérprete)[0])
#define intérprete_               (*(Intérprete*) intérprete_grade_.elemento)
#define expressões_grade_         (intérprete_grade_.filho)
#define expressão_grade_          (intérprete_.filho[0])
#define expressão_                ((Expressão) expressão_grade_.elemento[expressão_n - 1])
#define rastilho_                 ((Rastilho*) intérprete_.filho[1].elemento)

#endif // #if defined(DEFINIÇÃO)

    if (intérprete_grade_.tipo != lsve_tipo_intérprete) { 
        DESBRAGA_MENSAGEM("Grade não é do tipo correcto")
		abort();
        goto fim;
    }

    int 
    linhas_n = 0, 
    expressão_n = 0
    ;

    while(linhas_[linhas_n].índice == linhas_n) {
        if (linhas_[linhas_n].tipo == tipo_linha) {
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
