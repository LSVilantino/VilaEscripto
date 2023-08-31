#include "LSVEintérprete.h"
#include "LSVEconsola.h"

#include "linha.h"
#include "ficheiro.h"

#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>

Linha
rastilho_têr_linha_por_tipo(Rastilho_Tipo tipo) {
	Linha linha = linha_nil;

	switch (tipo)
	{
	case rastilho__carece_concedido: 				{ linha = "Carece concedido/clave, indefinido."; 									break; }
	case rastilho__carece_concessão: 				{ linha = "Carece concessão/separador."; 											break; }
	case rastilho__carece_concessão_válida: 		{ linha = "A concessão é inválida"; 												break; }
	case rastilho__carece_ficha_válida: 			{ linha = "A ficha é inválida"; 													break; }
	case rastilho__carece_valôr: 					{ linha = "Carece valôr à clave"; 													break; }
	case rastilho__expressão_excedente: 			{ linha = "Existem mais operações do que o esperado, formatação incorrecta."; 		break; }
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
#define operações_           		(expressão_.filho)
#define operação_grade_       		(operações_[operação_n])
#define operação_             		(**(Operação**) &operação_grade_.elemento)

#endif // #if defined(DEFINIÇÃO)

	Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
	if (operações->índice iqual inválido) { abort(); }

	grade_introduzir(&operações->filho,
		&(Grade) {
		.índice = operação_n,
        .constatação = linhar_(estructura_instância(Operação)),
		.tipo = lsve_tipo_operação,
		.elemento = memória_allocar(sizeof(Operação)),
		.elemento_precisa_libertar = vero,
		.filho = memória_allocar(sizeof(Grade)),
		.filho_precisa_libertar = vero,
		}
	);

	((Operação*) operações->filho[operação_n].elemento)[0] = (Operação) {
		.índice = operação_n,
		.tipo = operação_tipo,
		.expectação = expectação,
	};

	int índice = 0;

	grade_introduzir(&operações->filho[operação_n].filho,
		&(Grade) {
		.índice = índice,
		.constatação = linhar_(estructura_instância(Operação).linha),
		.tipo = lsve_tipo_linha,
		.elemento_precisa_libertar = vero,
		.elemento = memória_allocar(linha_t),
		.filho_precisa_libertar = fal,
		.filho = nil,
		}
	);

#if defined(DES_DEFINIÇÃO)

#undef operação_re_definir__
#undef expressão_
#undef operações_
#undef operação_grade_
#undef operação_

#endif // #if defined(DES_DEFINIÇÃO)
}

Grade
operação_falha() {
	return grade_falha(linhar_(estructura_instância(Operação)));
}

Grade
expressão_têr_por_ficha(Grade* expressões, Linha ficha) {
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
	Grade* operação_linha_grade = grade_procurar(&operação, linhar_(estructura_instância(Operação).), índice__qualquer);

	if (linha_comparar(linha, operação_linha_)) return operação;
	return operação_falha();

#undef operação_linha_
}

Grade
expressão_operação_têr_por_tipo(Grade expressão, Operação_Tipo tipo) {
#define operação_grade_ 	(expressão.filho[operação_n])
#define operação_ 			(**(Operação**) &expressão.filho[operação_n].elemento)

	int operação_n = 0;

  	while (operação_grade_.índice iqual operação_n) {
		if (operação_.tipo iqual tipo) {
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
	Grade expressãoFalha = grade_falha(linhar_(estructura_instância(Expressão)));
	operação_re_definir(0, &expressãoFalha, expectação__nil, operação__nil, 1);

	Grade operaçãoFalha = grade_falha(linhar_(estructura_instância(Expressão).operação));
	grade_introduzir(&expressãoFalha.filho, &operaçãoFalha);

	return expressãoFalha;
}

Dico interpretar_linha__clave_verificar_encerro_forçado(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_ficheiro_forçar_encerro).pala[0] iqual tf_.charactére) {
		Grade* operação_linha_grade = grade_procurar(operações_grade_, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		expressão_grade_ = expressão_falha();
		tf_.intérprete_rastilho_definir(&tf_, &expressão_grade_, rastilho__encerro_forçado);
		operação_linha_ = linha_nil;

		expressão_grade_.índice = expressão_n_;
		expressão_n_++;

		resultado = vero;
	}

	return resultado;

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

}

Dico interpretar_linha__clave_verificar_comentário(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;


	if (clave_têr_por_tipo(clave_ficheiro_comentário).pala[0] iqual tf_.charactére) {
		Grade* operação_linha_grade = grade_procurar(operações_grade_, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		expressão_grade_ = expressão_falha();
		tf->intérprete_rastilho_definir(&tf_, &expressão_grade_, rastilho__comentário);
		operação_.tipo = operação__concedido;
		operação_linha_ = linha_nil;

		expressão_grade_.índice = expressão_n_;
		expressão_n_++;

		resultado = vero;
	}

	return resultado;

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
}

void interpretar_linha__introduzir_concedido(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define expressão_n_			(*tf_.expressão_n)
#define operação_				void_como(operação->elemento, Operação*)
#define operação_linha_       	void_como(operação_linha->elemento, Linha)

#endif // #if defined(DEFINIÇÃO)

	Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
	Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);
	Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
	Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), tf_.operação_n);
	
	se (operação_->expectação iqual expectação__concedido ou operação_->expectação iqual expectação__nil)
	{
		Grade* operação_linha = grade_procurar(operação, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		linha_introduzir_charactére(tf_.charactére, tf_.operação_linha_n, &operação_linha_);
		DESBRAGA_MENSAGEM("%c, %d", operação_linha_[tf_.operação_linha_n], operação_->índice);

		tf_.operação_linha_n++;

		se (operação_->tipo iqual operação__concedido) operação_->expectação = expectação__concessão;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef expressão_n_
#undef operação_
#undef operação_linha_

#endif // #if defined(DES_DEFINIÇÃO)
}

Dico interpretar_linha__clave_verificar_concessão_directa(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf_.clave_n] iqual tf_.charactére) {
		Grade* operação_linha_grade = grade_procurar(operações_grade_, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		linha_aparar(&operação_linha_);

		tf_.operação_n++;
		operação_re_definir(tf_.operação_n, &expressão_grade_, expectação__valôr, operação__concessão_directa, 2);

		tf_.operação_linha_n = 0;
		operação_linha_[tf_.operação_linha_n] = tf_.charactére;
		operação_linha_[tf_.operação_linha_n + 1] = linha_nil;

		DESBRAGA_MENSAGEM("%c, %d", operação_linha_[tf_.operação_linha_n], operação_.índice);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
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
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_corrêr).pala[1] iqual tf_.pilha.conteúdo[tf_.recúo - 2]) {
		Grade* operação_linha_grade = grade_procurar(operações_grade_, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		tf_.operação_linha_n++;
		operação_linha_[tf_.operação_linha_n] = tf_.pilha.conteúdo[tf_.recúo - 2];
		operação_linha_[tf_.operação_linha_n + 1] = linha_nil;

		operação_.tipo = operação__concessão_corredora;

		tf_.pula = 1;

		DESBRAGA_MENSAGEM("%c, %d", operação_linha_[tf_.operação_linha_n], operação_.índice);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
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
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)
	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_ficha).pala[1] iqual tf_.pilha.conteúdo[tf_.recúo - 2]) {
		Grade* operação_linha_grade = grade_procurar(operações_grade_, linhar_(estructura_instância(Operação).linha), índice__qualquer);
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
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
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
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf_.clave_n] iqual tf_.pilha.conteúdo[tf_.recúo - 2]) {
		Grade* operação_linha_grade = grade_procurar(operações_grade_, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		tf_.operação_linha_n++;
		operação_linha_[tf_.operação_linha_n] = tf_.pilha.conteúdo[tf_.recúo - 2];
		operação_linha_[tf_.operação_linha_n + 1] = linha_nil;

		operação_.tipo = operação__concessão_passiva;

		tf_.pula = 1;

		DESBRAGA_MENSAGEM("%c", operação_linha_[tf_.operação_linha_n]);

		resultado = vero;
	}


#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
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
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[tf_.clave_n] iqual tf_.pilha.conteúdo[tf_.recúo - 3]) {
		Grade* operação_linha_grade = grade_procurar(operações_grade_, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		tf_.operação_linha_n++;
		operação_linha_[tf_.operação_linha_n] = tf_.pilha.conteúdo[tf_.recúo - 3];
		operação_linha_[tf_.operação_linha_n + 1] = linha_nil;

		operação_.tipo = operação__concessão_selectiva;

		tf_.pula = 2;

		DESBRAGA_MENSAGEM("%c", operação_linha_[tf_.operação_linha_n]);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
	return resultado;
}

Dico interpretar_linha__expressão_verificar_concessão_corredora(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	// Todos as operações que precisam dos valôres completos são validados após o registro de toda a linha.
	if (expressão_operação_têr_por_tipo(expressão_grade_, operação__concessão_corredora).índice differente -1) {
		Grade operação_valôr = expressão_operação_têr_por_tipo(expressão_grade_, operação__valôr);
		Grade* operação_linha = grade_procurar(operação_valôr.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		system(void_como(operação_linha->elemento, Linha));

		expressão_n_++;
		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
	return resultado;
}

Dico interpretar_linha__expressão_verificar_concessão_passiva(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (expressão_operação_têr_por_tipo(expressão_grade_, operação__concessão_passiva).índice differente -1) {
		// As expressões do agregado devem ser NULL, copia e elimina as expressões, que devem ser vazias.
		Grade caminho = expressão_operação_têr_por_tipo(expressão_grade_, operação__valôr);
		Grade intérprete_cópia = intérprete_grade_;

		Grade* intérprete_cópia_expressões = grade_procurar(intérprete_cópia.filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
		intérprete_cópia_expressões = nil;

		Grade intérprete_agregado = intérprete_confeccionar(&tf_, &intérprete_grade_, caminho);

		expressão_n_++;

		intérprete_agregar(&tf_, &intérprete_agregado, expressões_grade_, expressão_n_);
		grade_des_allocar(&intérprete_agregado.filho);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

Dico interpretar_linha__expressão_verificar_concessão_objectiva(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	Grade operação;
	if ((operação = expressão_operação_têr_por_tipo(expressão_grade_, operação__concessão_objectiva)).índice differente -1) {
		Grade* operação_linha = grade_procurar(operação.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);
		Grade* operação_valôr_linha = grade_procurar(operações_grade_[expressão_operação_têr_por_tipo(expressão_grade_, operação__valôr).índice].filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		Grade caminho = expressão_operação_têr_por_tipo(expressão_grade_, operação__valôr);
		Grade intérprete_agregado = intérprete_confeccionar(&tf_, &intérprete_grade_, caminho);
		Grade* expressões = grade_procurar(intérprete_agregado.filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);

		Grade expressão_seleccionada = expressão_têr_por_ficha(expressões->filho, void_como(operação_linha->elemento, Linha));
		Grade expressão_seleccionada_operação_valôr = expressão_operação_têr_por_tipo(expressão_seleccionada, operação__valôr);
		Grade* expressão_seleccionada_operação_valôr_linha = grade_procurar(expressão_seleccionada_operação_valôr.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		Grade* operação = grade_procurar(expressão_seleccionada.filho, linhar_(estructura_instância(Operação)), expressão_seleccionada_operação_valôr.índice);

		void_como(operação_valôr_linha->elemento, Linha) = void_como(expressão_seleccionada_operação_valôr_linha, Linha);
		expressão_n_++;
		grade_des_allocar(&intérprete_agregado.filho);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

Dico interpretar_linha__expressão_verificar_concessão_selectiva(TF_Interpretar* tf, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (expressão_operação_têr_por_tipo(expressão_grade_, operação__concessão_selectiva).índice differente -1) {
		Grade intérprete_cópia = intérprete_grade_;
		// As expressões do agregado devem ser NULL, copia e elimina as expressões.
		Grade* intérprete_cópia_expressões = grade_procurar(intérprete_cópia.filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
		intérprete_cópia_expressões = nil;

		Grade* operação_valôr_linha = grade_procurar(operações_grade_[expressão_operação_têr_por_tipo(expressão_grade_, operação__valôr).índice].filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		Grade caminho = expressão_operação_têr_por_tipo(expressão_grade_, operação__valôr);
		Grade intérprete_agregado = intérprete_confeccionar(&tf_, &intérprete_cópia, caminho);
		Grade* expressões = grade_procurar(intérprete_agregado.filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);

		Grade operaçãoSeleccionada = lsve_consola_construir_menu(expressões->filho);
		Grade* operaçãoSeleccionada_linha = grade_procurar(operaçãoSeleccionada.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		Grade expressão_seleccionada = expressão_têr_por_ficha(expressões->filho, void_como(operaçãoSeleccionada_linha->elemento, Linha));
		Grade expressão_seleccionada_operação_valôr = expressão_operação_têr_por_tipo(expressão_seleccionada, operação__valôr);
		Grade* expressão_seleccionada_operação_valôr_linha = grade_procurar(expressão_seleccionada_operação_valôr.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		Grade* operação = grade_procurar(expressão_seleccionada.filho, linhar_(estructura_instância(Operação)), expressão_seleccionada_operação_valôr.índice);

		void_como(operação_valôr_linha->elemento, Linha) = void_como(expressão_seleccionada_operação_valôr_linha, Linha);
		expressão_n_++;
		grade_des_allocar(&intérprete_agregado.filho);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
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
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Grade* operação_linha_grade = grade_procurar(operações_grade_, linhar_(estructura_instância(Operação).linha), índice__qualquer);

	linha_aparar(&operação_linha_);
	tf_.operação_linha_n = 0;

	tf_.operação_n++;
	operação_re_definir(tf_.operação_n, &expressão_grade_, expectação__nil, operação__valôr, 1);

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
}

void interpretar_linha__intérprete_rastilho_definir(TF_Interpretar* tf, Grade* intérprete, Rastilho_Tipo rastilho_tipo) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	grade_introduzir(&rastilhos_, &(Grade) {
		.constatação = linhar_(estructura_instância(Intérprete).rastilho),
		.índice = 0,
		.elemento = &(Rastilho) {
			.índice = 0,
			.tipo = rastilho_tipo,
			.erro = rastilho_têr_linha_por_tipo(rastilho_tipo)
		},
		.elemento_precisa_libertar = fal,
		.filho = nil,
		.filho_precisa_libertar = fal,
		.tipo = lsve_tipo_rastilho
	});

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
}

void intérprete_agregar(TF_Interpretar* tf, Grade* intérprete, Grade *expressões, int posição) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	if (expressões iqual nil) { return; }

	int expressão_n = 0;
	while (expressões[expressão_n].índice igual expressão_n) {
		expressões_grade_ = memória_re_allocar((posição + 1) * sizeof(Expressão), expressões_grade_);
		expressões_grade_[posição] = expressões[expressão_n];
		expressões_grade_[posição].índice = posição;

		expressão_n++; posição++;
	}

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
}

Grade intérprete_confeccionar(TF_Interpretar* tf, Grade* intérprete, Grade caminho) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Grade* caminho_linha = grade_procurar(caminho.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);
	Grade* ficheiro_linhas = ficheiro_lêr(void_como(caminho_linha->elemento, Linha));
	Grade intérprete_confeccionado = grade_falha(linhar_(estructura_instância(Intérprete)));

	grade_introduzir(&intérprete_confeccionado.filho,
		&(Grade) {
		.índice = 0,
		.constatação = linhar_(estructura_instância(Intérprete).expressão),
		.tipo = lsve_tipo_intérprete,
		.filho_precisa_libertar = vero,
		.filho = memória_allocar(sizeof(Grade))
		}
	);

	grade_introduzir(&intérprete_confeccionado.filho,
		&(Grade) {
		.índice = 1,
		.constatação = linhar_(estructura_instância(Intérprete).rastilho),
		.tipo = lsve_tipo_intérprete,
		.filho_precisa_libertar = vero,
		.filho = memória_allocar(sizeof(Grade))
		}
	);

	Grade* expressões = grade_procurar(intérprete_confeccionado.filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);

	grade_introduzir(&expressões,
		&(Grade) {
		.índice = 0,
		.constatação = linhar_(estructura_instância(Expressão)),
		.tipo = lsve_tipo_intérprete,
		.filho_precisa_libertar = vero,
		.filho = memória_allocar(sizeof(Grade))
		}
	);

	*grade_procurar(expressões, linhar_(estructura_instância(Expressão)), 0) = grade_falha(linhar_(estructura_instância(Expressão)));

	intérprete_agregar(&tf_, &intérprete_confeccionado, expressões_grade_, 0);
	interpretar(&ficheiro_linhas, &intérprete_grade_);

	return intérprete_confeccionado;

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
}

void
interpretar_linha(Grade* linha, Grade* intérprete, int* expressão_n) {
#if defined(DEFINIÇÃO)

#define linha_					((Linha) (*linha).elemento)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[tf.rastilho_n].elemento)
#define expressão_n_			(*tf.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf.operação_n])
#define operação_				(void_como(operação->elemento, Operação))
#define operação_grade_			(operações_grade_[tf.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define ficha_valôr_linha_		(*(Linha*) &valôrDaFicha_linha_grade->elemento)
#define recúo_                	(tf.recúo - 1)

#endif // #if defined(DEFINIÇÃO)
	Grade* operação_linha_grade = nil;

	TF_Interpretar tf = {
		.expressão_n = expressão_n,
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

		.expressão_verificar_concessão_corredora = interpretar_linha__expressão_verificar_concessão_corredora,
		.expressão_verificar_concessão_passiva = interpretar_linha__expressão_verificar_concessão_passiva,
		.expressão_verificar_concessão_objectiva = interpretar_linha__expressão_verificar_concessão_objectiva,
		.expressão_verificar_concessão_selectiva = interpretar_linha__expressão_verificar_concessão_selectiva,

		.operação_aparar_e_re_definir = interpretar_linha__operação_aparar_e_re_definir,
	};

    tf.recúo = tf.pilha.recúo;

	DESBRAGA_MENSAGEM("LINHA A DESBRAGAR %s", linha_);

	Grade* rastilho = grade_procurar(intérprete_grade_.filho, linhar_(estructura_instância(Intérprete).rastilho), índice__qualquer);
	Grade* expressões = grade_procurar(intérprete_grade_.filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);

    grade_introduzir(&expressões->filho,
        &(Grade) {
        .índice = expressão_n_,
        .constatação = linhar_(estructura_instância(Expressão)),
        .tipo = lsve_tipo_expressão,
		.elemento = nil,
		.elemento_precisa_libertar = fal,
        .filho = memória_allocar(sizeof(Grade)),
        .filho_precisa_libertar = vero,
        }
    );

	Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);

	grade_introduzir(&expressão->filho,
		&(Grade) {
		.índice = 0,
		.constatação = linhar_(estructura_instância(Expressão).linha),
		.tipo = lsve_tipo_linha,
		.elemento = nil,
		.elemento_precisa_libertar = fal,
		.filho = memória_allocar(sizeof(Grade)),
		.filho_precisa_libertar = vero,
		}
	);

	grade_introduzir(&expressão->filho,
        &(Grade) {
        .índice = 1,
        .constatação = linhar_(estructura_instância(Expressão).operação),
        .tipo = lsve_tipo_operação,
		.elemento = nil,
		.elemento_precisa_libertar = fal,
        .filho = memória_allocar(sizeof(Grade)),
        .filho_precisa_libertar = vero,
        }
    );

    operação_re_definir(tf.operação_n, expressão, expectação__concedido, operação__concedido, sizeof(char));

	Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
	Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), tf.operação_n);
	Grade* operação_linha = grade_procurar(operação, linhar_(estructura_instância(Operação).linha), índice__qualquer);

	DESBRAGA_MENSAGEM("%s", operações->constatação);
	DESBRAGA_MENSAGEM("%s", operação->constatação);
	DESBRAGA_MENSAGEM("%s", operação_linha->constatação);

    while(tf.recúo > 1) {
        /*
			Ao fim da linha, diminui - se o recúo da pilha, até chegar à ponta,
			o último charactére armazenado.

			Se a linha não estiver ao fim, introduz o último charactére à pilha.
		*/
		if (linha_[tf.linha_n] iqual linha_nil) { tf.recúo--; }
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


		if (tf.charactére iqual linha_nil) continue;
		if (tf.pula differente 0) {
			tf.pula--;
			continue;
		}

		/*
			Se o encerro forçado for encontrado, encerra-se tudo e retorna o que foi armazenado.

			Reporta rastilho.
		*/
		/*
		if (tf.clave_verificar_encerro_forçado(&tf, &intérprete_grade_)) {
			break;
		}
		*/

		/*
			Se um comentário for encontrado, ignora a linha.

			Reporta rastilho.
		*/

		/*
		if (tf.clave_verificar_comentário(&tf, &intérprete_grade_)) {
			break;
		}
		*/

		/*
		if (clave_têr_por_tipo(clave_ficha).pala[0] iqual tf.charactére) {
			operação_.expectação = expectação__ficha_abre;
			continue;
		}
		*/

		/*
		if (clave_têr_por_tipo(clave_ficha).pala[1] iqual tf.charactére e operação_.expectação iqual expectação__ficha_abre)
		{
			operação_.expectação = expectação__ficha_fecha;
			continue;
		}
		*/

		// Leitura da ficha
		/*
		if (operação_.expectação iqual expectação__ficha_fecha) {
			if (clave_têr_por_tipo(clave_ficha).pala[2] iqual tf.charactére) {
				// Uma vez lida a clave da ficha, obtém-se seu valôr.
				Grade valôrDaFicha = expressão_operação_têr_por_tipo(expressão_têr_por_ficha(expressões_grade_, tf.ficha), operação__valôr);

				if (valôrDaFicha.índice iqual -1) {
					tf.intérprete_rastilho_definir(&tf, &intérprete_grade_, rastilho__carece_ficha_válida);
					expressão_.índice = expressão_n_++;
					abort();
					break;
				}

				Grade* valôrDaFicha_linha_grade = grade_procurar(valôrDaFicha.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);
				linha_agregar_linha(ficha_valôr_linha_, &tf.operação_linha_n, &operação_linha_);

				memória_des_allocar((void**) &tf.ficha);
				tf.ficha = memória_allocar(sizeof(char) * 2);
				tf.ficha[0] = linha_nil;
				tf.ficha_n = 0;

				operação_.expectação = expectação__nil;
				continue;
			}

			linha_introduzir_charactére(tf.charactére, tf.ficha_n, &tf.ficha);
			tf.ficha_n++;
			continue;
		}
		*/

		//
		/*
		if (operação_.tipo iqual operação__concessão_objectiva e
		clave_têr_por_tipo(clave_ficha).pala[2] iqual tf.charactére)
		{
			if (clave_têr_por_tipo(clave_lêr).pala[0] iqual tf.pilha.conteúdo[tf.recúo - 2]) {
				linha_aparar(&operação_.linha);

				tf.operação_linha_n = 0;
				tf.operação_n++;

				operação_re_definir(tf.operação_n, &expressão_grade_, expectação__nil, operação__valôr, 1);

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
		*/

		/*
			A linha é o limitante que separa cada linha, quando for atingido, avalia-se a linha
			e seus elementos para averiguar a sua integridade.
		*/

		/*
		if (tf.charactére iqual linha_salta ou tf.charactére iqual EOF) {
			expressão_grade_.índice = expressão_n_;
			linha_aparar(&operação_linha_);

			if (tf.operação_n iqual 0 e operação_linha_[tf.operação_linha_n] differente linha_nil) {
				tf.intérprete_rastilho_definir(&tf, &intérprete_grade_, rastilho__carece_concessão);
			}
			else if (tf.operação_n iqual 0 e operação_linha_[tf.operação_linha_n] iqual linha_nil) {
				// Se a linha estiver vazia, inteiramente, não mostra mensagens, é irritante.
				expressão_grade_ = expressão_falha();
				tf.intérprete_rastilho_definir(&tf, &intérprete_grade_, rastilho__nil);
				DESBRAGA_MENSAGEM("\n");
				break;
			}

			if (tf.operação_n iqual 1) {
				tf.intérprete_rastilho_definir(&tf, &intérprete_grade_, rastilho__carece_valôr);
			}
			if (tf.operação_n iqual 2) {
				tf.intérprete_rastilho_definir(&tf, &intérprete_grade_, rastilho__nil);
			}

			// Todos as operações que precisam dos valôres completos são validados após o registro de toda a linha.
			if (tf.expressão_verificar_concessão_corredora(&tf, &intérprete_grade_)) {
				continue;
			}

			if (tf.expressão_verificar_concessão_passiva(&tf, &intérprete_grade_)) {
				continue;
			}

			if (tf.expressão_verificar_concessão_objectiva(&tf, &intérprete_grade_)) {
				continue;
			}

			if (tf.expressão_verificar_concessão_selectiva(&tf, &intérprete_grade_)) {
				continue;
			}

			expressão_n_++;
			continue;
		}
		*/


		/*
			Ao conceder uma clave, espera-se uma concessão.

			Se a concessão vier antes da clave, será tratada como clave e a concessão não será reconhecida.
			Se a concessão vier antes e depois da clave, a primeira concessão fará parte do nome da clave.
			Se a concessão vier antes, depois da clave, e antes ou depois do valôr, será tratada como valôr
			e/ou nome da clave.
		*/
		/*
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
		*/
		tf.introduzir_concedido(&tf, &intérprete_grade_);
    }

fim:

	memória_des_allocar(&tf.pilha.conteúdo);
	memória_des_allocar(&tf.ficha);
	abort();
	return;

#if defined(DES_DEFINIÇÃO)

#undef linha_
#undef intérprete_grade_
#undef intérprete_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef ficha_valôr_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
}

void
interpretar(Grade* ref linhas, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define tf_						(*tf)
#define linha_					((Linha) (*linha).elemento)
#define linhas_                 (*linhas)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_grade_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(*(Rastilho*) rastilhos_[tf_.rastilho_n].elemento)
#define expressão_n_			(*tf_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(*(Expressão*) expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[tf_.operação_n])
#define operação_				(*(Operação*) operações_.elemento)
#define operação_grade_			(operações_grade_[tf_.operação_n])
#define operação_linha_       	((Linha) operação_linha_grade->elemento)
#define ficha_valôr_linha_		((Linha) valôrDaFicha_linha_grade->elemento)
#define recúo_                	(tf_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

    if (intérprete_grade_.tipo differente lsve_tipo_intérprete) {
		DESBRAGA_MENSAGEM("Grade não é do tipo correcto");
		abort();
        goto fim;
    }

    int expressão_n = 0;

    while(linhas_[expressão_n].índice iqual expressão_n) {
        if (linhas_[expressão_n].tipo iqual tipo_linha) {
			DESBRAGA_MENSAGEM("%d", expressão_n);
            interpretar_linha(&linhas_[expressão_n], &intérprete_grade_, &expressão_n);

			continue;
        }

		goto fim;
    }

fim:

	return;

#if defined(DES_DEFINIÇÃO)

#undef tf_
#undef linha_
#undef linhas_
#undef intérprete_
#undef intérprete_grade_
#undef rastilhos_
#undef rastilho_
#undef expressão_n_
#undef expressões_grade_
#undef expressão_
#undef expressão_grade_
#undef operações_grade_
#undef operações_
#undef operação_
#undef operação_grade_
#undef operação_linha_
#undef ficha_valôr_linha_
#undef recúo_

#endif // #if defined(DES_DEFINIÇÃO)
}
