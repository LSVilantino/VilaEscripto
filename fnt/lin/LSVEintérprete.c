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

#endif // #if defined(DEFINIÇÃO)

	DESBRAGA_TÓPICO("%d - %s", expressão->índice, linhar_(estructura_instância(Expressão).operação));
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

	Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), operação_n);
	void_como(operação->elemento, Operação*)[0] = (Operação) {
		.índice = operação_n,
		.tipo = operação_tipo,
		.expectação = expectação,
	};

	grade_introduzir(&operação->filho,
		&(Grade) {
		.índice = 0,
		.constatação = linhar_(estructura_instância(Operação).linha),
		.tipo = lsve_tipo_linha,
		.elemento = memória_allocar(linha_t),
		.elemento_precisa_libertar = vero,
		.filho = nil,
		.filho_precisa_libertar = fal,
		}
	);

	Grade* operação_linha = grade_procurar(operação->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);
	void_como(operação_linha->elemento, Linha)[0] = linha_nil;

#if defined(DES_DEFINIÇÃO)

#endif // #if defined(DES_DEFINIÇÃO)
}

Grade
operação_falha() {
	return grade_falha(linhar_(estructura_instância(Operação)));
}

Grade*
expressão_têr_por_ficha(Grade* expressões, Linha ficha) {
	Grade grade_falha = expressão_falha();
	Grade* resultado = &grade_falha;

	int expressão_n = 0;
	Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n);

	enquanto (expressão->índice iqual expressão_n) {
		se (expressão_operação_têr_por_ficha(expressão, ficha).índice differente -1) {
			resultado = expressão;
			goto fim;
		}

		expressão_n++;
		expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n);
		
		DESBRAGA_TÓPICO("%d", expressão_n);
	}

fim:
	return resultado;
}

Grade
expressão_operação_têr_por_ficha(Grade* expressão, Linha linha) {
#define operação_linha_       	void_como(operação_linha->elemento, Linha)

	Grade resultado = operação_falha();

	Grade operação = expressão_operação_têr_por_tipo(expressão, operação__concedido);
	Grade* operação_linha = grade_procurar(operação.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

	se (linha_comparar(linha, operação_linha_)) {
		resultado = operação;
		goto fim;
	}

fim:
	devolve resultado;

#undef operação_linha_
}

Grade
expressão_operação_têr_por_tipo(Grade* expressão, Operação_Tipo tipo) {
#define operação_				(void_como(operação->elemento, Operação*))

	int operação_n = 0;

	Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
	Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), operação_n);

	Grade resultado = operação_falha();

  	enquanto (operação->índice iqual operação_n) {
		se (operação_->tipo iqual tipo) {
			resultado = *operação;
			goto fim;
		}

		operação_n++;
		operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), operação_n);
	}

fim:
	devolve resultado;

#undef operação_
}

Grade
expressão_falha() {
	return grade_falha(linhar_(estructura_instância(Expressão)));
}

Dico interpretar_linha__clave_verificar_indicador_ficha(EF_Interpretar* ef, Grade* intérprete) {
#define expressão_n_			(*ef->expressão_n)
#define operação_				void_como(operação->elemento, Operação*)

	Dico resultado = fal;

	se (clave_têr_por_tipo(clave_ficha).pala[0] iqual ef->charactére) {
		Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
		Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);
		Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
		Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef->operação_n);
		
		operação_->expectação = expectação__ficha_abre;

		resultado = vero;
	}

	return resultado;

#undef expressão_n_
#undef operação_
}

Dico interpretar_linha__clave_verificar_indicador_ficha_abre(EF_Interpretar* ef, Grade* intérprete) {
#define expressão_n_			(*ef->expressão_n)
#define operação_				void_como(operação->elemento, Operação*)

	Dico resultado = fal;

	se (clave_têr_por_tipo(clave_ficha).pala[1] iqual ef->charactére) {
		Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
		Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);
		Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
		Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef->operação_n);

		operação_->expectação = expectação__ficha_fecha;

		resultado = vero;
	}

	return resultado;

#undef expressão_n_
#undef operação_
}

Dico interpretar_linha__procurar_ficha(EF_Interpretar* ef, Grade* intérprete) {
#define expressão_n_			(*ef->expressão_n)
#define operação_				void_como(operação->elemento, Operação*)
#define operação_linha_       	void_como(operação_linha->elemento, Linha)
#define ficha_valôr_linha_		void_como(valôrDaFicha_linha->elemento, Linha)

	Dico resultado = fal;

	se (clave_têr_por_tipo(clave_ficha).pala[2] iqual ef->charactére) {

		Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
		Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);
		Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
		Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef->operação_n);
		Grade* operação_linha = grade_procurar(operação->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		// Uma vez lida a clave da ficha, obtém-se seu valôr.
		Grade valôrDaFicha = expressão_operação_têr_por_tipo(expressão_têr_por_ficha(expressões, ef->ficha), operação__valôr);

		se (valôrDaFicha.índice iqual -1) {
			ef->intérprete_rastilho_definir(&ef, intérprete, rastilho__carece_ficha_válida);
			expressão->índice = expressão_n_;
			expressão_n_++;
			abort();
		}

		Grade* valôrDaFicha_linha = grade_procurar(valôrDaFicha.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);
		linha_agregar_linha(ficha_valôr_linha_, &ef->operação_linha_n, &operação_linha_);

		memória_des_allocar(&ef->ficha);
		ef->ficha = memória_allocar(sizeof(char) * 2);
		ef->ficha[0] = linha_nil;
		ef->ficha_n = 0;

		operação_->expectação = expectação__nil;

		resultado = vero;
	}

	return resultado;

#undef expressão_n_
#undef operação_
}

Dico interpretar_linha__clave_verificar_encerro_forçado(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define ef_						(*ef)
#define expressão_n_			(*ef_.expressão_n)
#define operação_				void_como(operação->elemento, Operação*)
#define operação_linha_       	void_como(operação_linha->elemento, Linha)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_ficheiro_forçar_encerro).pala[0] iqual ef_.charactére) {
		Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
		Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);
		Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
		Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef_.operação_n);
		Grade* operação_linha = grade_procurar(operação, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		*expressão = expressão_falha();
		ef_.intérprete_rastilho_definir(&ef_, intérprete, rastilho__encerro_forçado);
		operação_linha_ = linha_nil;

		expressão->índice = expressão_n_;
		expressão_n_++;

		resultado = vero;
	}

	return resultado;

#if defined(DES_DEFINIÇÃO)

#undef ef_
#undef expressão_n_
#undef operação_
#undef operação_linha_

#endif // #if defined(DES_DEFINIÇÃO)

}

Dico interpretar_linha__clave_verificar_comentário(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define ef_						(*ef)
#define expressão_n_			(*ef_.expressão_n)
#define expressão_				void_como(expressão->elemento, Expressão*)
#define operação_				void_como(operação->elemento, Operação*)
#define operação_linha_       	void_como(operação_linha->elemento, Linha)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	se (clave_têr_por_tipo(clave_ficheiro_comentário).pala[0] iqual ef_.charactére) {
		Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
		Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);
		Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
		Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef_.operação_n);
		Grade* operação_linha = grade_procurar(operação, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		*expressão = expressão_falha();
		ef->intérprete_rastilho_definir(&ef_, intérprete, rastilho__comentário);
		operação_->tipo = operação__concedido;
		operação_linha_ = linha_nil;

		expressão->índice = expressão_n_;
		expressão_n_++;

		resultado = vero;
	}

	return resultado;

#if defined(DES_DEFINIÇÃO)

#undef ef_
#undef expressão_n_
#undef expressão_
#undef operação_
#undef operação_linha_

#endif // #if defined(DES_DEFINIÇÃO)
}

void interpretar_linha__introduzir_concedido(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define ef_						(*ef)
#define expressão_n_			(*ef_.expressão_n)
#define operação_				void_como(operação->elemento, Operação*)
#define operação_linha_       	void_como(operação_linha->elemento, Linha)

#endif // #if defined(DEFINIÇÃO)

	Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
	Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);
	Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
	Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef_.operação_n);
	
	se (operação_->expectação iqual expectação__concedido ou operação_->expectação iqual expectação__nil)
	{
		Grade* operação_linha = grade_procurar(operação->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		linha_introduzir_charactére(ef_.charactére, ef_.operação_linha_n, &operação_linha_);
		DESBRAGA_MENSAGEM("%c – %d", operação_linha_[ef_.operação_linha_n], ef_.operação_linha_n);

		ef_.operação_linha_n++;

		se (operação_->tipo iqual operação__concedido) operação_->expectação = expectação__concessão;
	}

#if defined(DES_DEFINIÇÃO)

#undef ef_
#undef expressão_n_
#undef operação_
#undef operação_linha_

#endif // #if defined(DES_DEFINIÇÃO)
}

Dico interpretar_linha__clave_verificar_concessão_directa(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define ef_						(*ef)
#define expressão_n_			(*ef_.expressão_n)
#define operação_				void_como(operação->elemento, Operação*)
#define operação_linha_       	void_como(operação_linha->elemento, Linha)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	se (clave_têr_por_tipo(clave_lêr).pala[ef_.clave_n] iqual ef_.charactére) {
		Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
		Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);
		Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
		Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef_.operação_n);
		Grade* operação_linha = grade_procurar(operação->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		linha_aparar(&operação_linha_);

		ef_.operação_n++;
		operação_re_definir(ef_.operação_n, expressão, expectação__valôr, operação__concessão_directa, sizeof(char) * 2);

		operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef_.operação_n);
		operação_linha = grade_procurar(operação->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);
		
		ef_.operação_linha_n = 0;
		operação_linha_[ef_.operação_linha_n] = ef_.charactére;
		operação_linha_[ef_.operação_linha_n + 1] = linha_nil;

		DESBRAGA_MENSAGEM("OPERAÇÃO LINHA %c, %d", operação_linha_[ef_.operação_linha_n], operação_->índice);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef ef_
#undef expressão_n_
#undef operação_
#undef operação_linha_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

Dico interpretar_linha__clave_verificar_concessão_corredora(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define expressão_n_			(*ef->expressão_n)
#define operação_				void_como(operação->elemento, Operação*)
#define operação_linha_       	void_como(operação_linha->elemento, Linha)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_corrêr).pala[1] iqual ef->pilha.conteúdo[ef->recúo - 2]) {
		Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
		Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);
		Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
		Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef->operação_n);
		Grade* operação_linha = grade_procurar(operação->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		ef->operação_linha_n++;
		operação_linha_[ef->operação_linha_n] = ef->pilha.conteúdo[ef->recúo - 2];
		operação_linha_[ef->operação_linha_n + 1] = linha_nil;

		operação_->tipo = operação__concessão_corredora;

		ef->pula = 1;

		DESBRAGA_MENSAGEM("%c, %d", operação_linha_[ef->operação_linha_n], operação_->índice);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef expressão_n_
#undef operação_
#undef operação_linha_

#endif // #if defined(DES_DEFINIÇÃO)

	return resultado;
}

Dico interpretar_linha__clave_verificar_concessão_objectiva(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define ef_						(*ef)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[ef_.rastilho_n].elemento)
#define expressão_n_			(*ef_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[ef_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[ef_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(ef_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)
	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_ficha).pala[1] iqual ef_.pilha.conteúdo[ef_.recúo - 2]) {
		Grade* operação_linha_grade = grade_procurar(operações_grade_, linhar_(estructura_instância(Operação).linha), índice__qualquer);
		linha_aparar(&operação_linha_);

		ef_.operação_n++;
		operação_re_definir(ef_.operação_n, &expressão_grade_, expectação__valôr, operação__concessão_directa, 1);

		ef_.operação_linha_n = 0;
		operação_.expectação = expectação__nil;
		operação_.tipo = operação__concessão_objectiva;

		ef_.pula = 1;
		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef ef_
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

Dico interpretar_linha__clave_verificar_concessão_passiva(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define ef_						(*ef)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[ef_.rastilho_n].elemento)
#define expressão_n_			(*ef_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[ef_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[ef_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(ef_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[ef_.clave_n] iqual ef_.pilha.conteúdo[ef_.recúo - 2]) {
		Grade* operação_linha_grade = grade_procurar(operações_grade_, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		ef_.operação_linha_n++;
		operação_linha_[ef_.operação_linha_n] = ef_.pilha.conteúdo[ef_.recúo - 2];
		operação_linha_[ef_.operação_linha_n + 1] = linha_nil;

		operação_.tipo = operação__concessão_passiva;

		ef_.pula = 1;

		DESBRAGA_MENSAGEM("%c", operação_linha_[ef_.operação_linha_n]);

		resultado = vero;
	}


#if defined(DES_DEFINIÇÃO)

#undef ef_
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

Dico interpretar_linha__clave_verificar_concessão_selectiva(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define ef_						(*ef)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[ef_.rastilho_n].elemento)
#define expressão_n_			(*ef_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[ef_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[ef_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(ef_.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	if (clave_têr_por_tipo(clave_lêr).pala[ef_.clave_n] iqual ef_.pilha.conteúdo[ef_.recúo - 3]) {
		Grade* operação_linha_grade = grade_procurar(operações_grade_, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		ef_.operação_linha_n++;
		operação_linha_[ef_.operação_linha_n] = ef_.pilha.conteúdo[ef_.recúo - 3];
		operação_linha_[ef_.operação_linha_n + 1] = linha_nil;

		operação_.tipo = operação__concessão_selectiva;

		ef_.pula = 2;

		DESBRAGA_MENSAGEM("%c", operação_linha_[ef_.operação_linha_n]);

		resultado = vero;
	}

#if defined(DES_DEFINIÇÃO)

#undef ef_
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

Dico interpretar_linha__expressão_verificar_concessão_corredora(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define expressão_n_			(*ef->expressão_n)
#define operação_linha_       	(void_como(operação_linha->elemento, Linha))

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
	Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);

	// Todos as operações que precisam dos valôres completos são validados após o registro de toda a linha.
	se (expressão_operação_têr_por_tipo(expressão, operação__concessão_corredora).índice differente -1) {
		Grade operação = expressão_operação_têr_por_tipo(expressão, operação__valôr);
		Grade* operação_linha = grade_procurar(operação.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		system(operação_linha_);

		expressão_n_++;
		resultado = vero;
	}

	return resultado;

#if defined(DES_DEFINIÇÃO)

#undef expressão_n_
#undef operação_linha_

#endif // #if defined(DES_DEFINIÇÃO)
}

Dico interpretar_linha__expressão_verificar_concessão_passiva(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define expressão_n_			(*ef->expressão_n)
#define operação_linha_       	(void_como(operação_linha->elemento, Linha))

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
	Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);

	se (expressão_operação_têr_por_tipo(expressão, operação__concessão_passiva).índice differente -1) {
		// As expressões do agregado devem ser NULL, copia e elimina as expressões, que devem ser vazias.
		Grade caminho = expressão_operação_têr_por_tipo(expressão, operação__valôr);
		Grade* intérprete_cópia = intérprete;

		Grade* intérprete_cópia_expressões = grade_procurar(intérprete_cópia->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
		intérprete_cópia_expressões = nil;

		Grade intérprete_agregado = intérprete_confeccionar(ef, intérprete, caminho);

		expressão_n_++;

		intérprete_agregar(ef, &intérprete_agregado, expressões, expressão_n_);
		grade_des_allocar(&intérprete_agregado.filho);

		resultado = vero;
	}

	return resultado;

#if defined(DES_DEFINIÇÃO)

#undef expressão_n_
#undef operação_linha_

#endif // #if defined(DES_DEFINIÇÃO)
}

Dico interpretar_linha__expressão_verificar_concessão_objectiva(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define expressão_n_			(*ef->expressão_n)
#define operação_linha_       	(void_como(operação_linha->elemento, Linha))

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
	Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);

	Grade operação = operação_falha();
	if ((operação = expressão_operação_têr_por_tipo(expressão, operação__concessão_objectiva)).índice differente -1) {
		Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
		Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), expressão_operação_têr_por_tipo(expressão, operação__valôr).índice);

		Grade* operação_linha = grade_procurar(operação->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);
		Grade* operação_valôr_linha = grade_procurar(operação->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		Grade caminho = expressão_operação_têr_por_tipo(expressão, operação__valôr);
		Grade intérprete_agregado = intérprete_confeccionar(ef, intérprete, caminho);
		Grade* expressões = grade_procurar(intérprete_agregado.filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);

		Grade* expressão_seleccionada = expressão_têr_por_ficha(expressões->filho, void_como(operação_linha->elemento, Linha));
		Grade expressão_seleccionada_operação_valôr = expressão_operação_têr_por_tipo(expressão_seleccionada, operação__valôr);
		Grade* expressão_seleccionada_operação_valôr_linha = grade_procurar(expressão_seleccionada_operação_valôr.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		//Grade* operação = grade_procurar(expressão_seleccionada->filho, linhar_(estructura_instância(Operação)), expressão_seleccionada_operação_valôr->índice);

		operação_linha_ = void_como(expressão_seleccionada_operação_valôr_linha, Linha);
		expressão_n_++;
		grade_des_allocar(&intérprete_agregado.filho);

		resultado = vero;
	}

	return resultado;

#if defined(DES_DEFINIÇÃO)

#undef expressão_n_
#undef operação_linha_

#endif // #if defined(DES_DEFINIÇÃO)
}

Dico interpretar_linha__expressão_verificar_concessão_selectiva(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define expressão_n_			(*ef->expressão_n)
#define operação_linha_       	(void_como(operação_linha->elemento, Linha))

#endif // #if defined(DEFINIÇÃO)

	Dico resultado = fal;

	Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
	Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);

	se (expressão_operação_têr_por_tipo(expressão, operação__concessão_selectiva).índice differente -1) {
		Grade* intérprete_cópia = intérprete;
		// As expressões do agregado devem ser NULL, copia e elimina as expressões.
		Grade* intérprete_cópia_expressões = grade_procurar(intérprete_cópia->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
		intérprete_cópia_expressões = nil;

		Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
		Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), expressão_operação_têr_por_tipo(expressão, operação__valôr).índice);

		Grade* operação_linha = grade_procurar(operações->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		Grade caminho = expressão_operação_têr_por_tipo(expressão, operação__valôr);
		Grade intérprete_agregado = intérprete_confeccionar(ef, intérprete_cópia, caminho);
		Grade* expressões = grade_procurar(intérprete_agregado.filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);

		Grade operaçãoSeleccionada = lsve_consola_construir_menu(expressões->filho);
		Grade* operaçãoSeleccionada_linha = grade_procurar(operaçãoSeleccionada.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		Grade* expressão_seleccionada = expressão_têr_por_ficha(expressões->filho, void_como(operaçãoSeleccionada_linha->elemento, Linha));
		Grade expressão_seleccionada_operação_valôr = expressão_operação_têr_por_tipo(expressão_seleccionada, operação__valôr);
		Grade* expressão_seleccionada_operação_valôr_linha = grade_procurar(expressão_seleccionada_operação_valôr.filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

		//Grade* operação = grade_procurar(expressão_seleccionada->filho, linhar_(estructura_instância(Operação)), expressão_seleccionada_operação_valôr->índice);

		operação_linha = void_como(expressão_seleccionada_operação_valôr_linha, Linha);
		expressão_n_++;
		grade_des_allocar(&intérprete_agregado.filho);

		resultado = vero;
	}

	return resultado;

#if defined(DES_DEFINIÇÃO)

#undef expressão_n_
#undef operação_linha_

#endif // #if defined(DES_DEFINIÇÃO)
}

void interpretar_linha__operação_aparar_e_re_definir(EF_Interpretar* ef, Grade* intérprete) {
#if defined(DEFINIÇÃO)

#define expressão_n_			(*ef->expressão_n)
#define operação_				void_como(operação->elemento, Operação*)
#define operação_linha_       	void_como(operação_linha->elemento, Linha)

#endif // #if defined(DEFINIÇÃO)

	Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
	Grade* expressão = grade_procurar(expressões->filho, linhar_(estructura_instância(Expressão)), expressão_n_);
	Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
	Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef->operação_n);
	Grade* operação_linha = grade_procurar(operação->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

	linha_aparar(&operação_linha_);

	ef->operação_linha_n = 0;
	ef->operação_n++;
	operação_re_definir(ef->operação_n, expressão, expectação__nil, operação__valôr, sizeof(char) * 2);

#if defined(DES_DEFINIÇÃO)

#undef expressão_n_
#undef operação_
#undef operação_linha_

#endif // #if defined(DES_DEFINIÇÃO)
}

void interpretar_linha__intérprete_rastilho_definir(EF_Interpretar* ef, Grade* intérprete, Rastilho_Tipo rastilho_tipo) {
#if defined(DEFINIÇÃO)

#define ef_						(*ef)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[ef_.rastilho_n].elemento)
#define expressão_n_			(*ef_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[ef_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[ef_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(ef_.recúo - 1)

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

#undef ef_
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

void intérprete_agregar(EF_Interpretar* ef, Grade* intérprete, Grade *expressões, int posição) {
#if defined(DEFINIÇÃO)

#define ef_						(*ef)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[ef_.rastilho_n].elemento)
#define expressão_n_			(*ef_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[ef_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[ef_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(ef_.recúo - 1)

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

#undef ef_
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

Grade intérprete_confeccionar(EF_Interpretar* ef, Grade* intérprete, Grade caminho) {
#if defined(DEFINIÇÃO)

#define ef_						(*ef)
#define intérprete_grade_		(*intérprete)
#define intérprete_				(*((Intérprete*) intérprete_.elemento))
#define rastilhos_				(intérprete_grade_.filho[1].filho)
#define rastilho_				(**(Rastilho**) &rastilhos_[ef_.rastilho_n].elemento)
#define expressão_n_			(*ef_.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[ef_.operação_n])
#define operação_				(**(Operação**) &operações_.elemento)
#define operação_grade_			(operações_grade_[ef_.operação_n])
#define operação_linha_       	(*(Linha*) &operação_linha_grade->elemento)
#define recúo_                	(ef_.recúo - 1)

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

	intérprete_agregar(&ef_, &intérprete_confeccionado, expressões_grade_, 0);
	interpretar(&ficheiro_linhas, &intérprete_grade_);

	return intérprete_confeccionado;

#if defined(DES_DEFINIÇÃO)

#undef ef_
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
#define rastilho_				(**(Rastilho**) &rastilhos_[ef.rastilho_n].elemento)
#define expressão_n_			(*ef.expressão_n)
#define expressões_grade_		(intérprete_grade_.filho[0].filho)
#define expressão_				(**(Expressão**) &expressões_grade_[expressão_n_].elemento)
#define expressão_grade_		(expressões_grade_[expressão_n_])
#define operações_grade_		(expressão_grade_.filho)
#define operações_				(operações_grade_[ef.operação_n])
#define operação_				(void_como(operação->elemento, Operação*))
#define operação_grade_			(operações_grade_[ef.operação_n])
#define operação_linha_       	void_como(operação_linha->elemento, Linha)
#define ficha_valôr_linha_		(*(Linha*) &valôrDaFicha_linha_grade->elemento)
#define recúo_                	(ef.recúo - 1)

#endif // #if defined(DEFINIÇÃO)

	EF_Interpretar ef = {
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

		.clave_verificar_indicador_ficha = interpretar_linha__clave_verificar_indicador_ficha,
		.clave_verificar_indicador_ficha_abre = interpretar_linha__clave_verificar_indicador_ficha_abre,
		.procurar_ficha = interpretar_linha__procurar_ficha,

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

	linha_introduzir_charactére(linha_nil, ef.ficha_n, &ef.ficha);

    ef.recúo = ef.pilha.recúo;

	DESBRAGA_MENSAGEM("LINHA A DESBRAGAR: %s, expressão %d", linha_, expressão_n_);

	Grade* expressões = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).expressão), índice__qualquer);
	Grade* rastilho = grade_procurar(intérprete->filho, linhar_(estructura_instância(Intérprete).rastilho), índice__qualquer);

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

    operação_re_definir(ef.operação_n, expressão, expectação__concedido, operação__concedido, sizeof(char));

	Grade* operações = grade_procurar(expressão, linhar_(estructura_instância(Expressão).operação), índice__qualquer);
	Grade* operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef.operação_n);
	Grade* operação_linha = grade_procurar(operação, linhar_(estructura_instância(Operação).linha), índice__qualquer);

	DESBRAGA_TÓPICO("%s", operações->constatação);
	DESBRAGA_TÓPICO("%s", operação->constatação);
	DESBRAGA_TÓPICO("%s", operação_linha->constatação);

    while(ef.recúo > 1) {
        /*
			Ao fim da linha, diminui - se o recúo da pilha, até chegar à ponta,
			o último charactére armazenado.

			Se a linha não estiver ao fim, introduz o último charactére à pilha.
		*/
		se (linha_[ef.linha_n] iqual linha_nil) { ef.recúo--; }
		se_não {
			pilha_introduzir(linha_[ef.linha_n], &ef.pilha);

            ef.linha_n++;
		}

		ef.charactére = ef.pilha.conteúdo[recúo_];
        //DESBRAGA_MENSAGEM("%c", charactére)

        /*
			As primeiras corridas do ciclo caem em endereço nil,
			ficam armazenadas no início da pilha.

			Quanto maior a pilha, mais iterações levam para chegar
			algum valôr. Até lá, foram-se os índices.
		*/


		se (ef.charactére iqual linha_nil) continue;
		se (ef.pula differente 0) {
			ef.pula--;
			continue;
		}

		/*
			Se o encerro forçado for encontrado, encerra-se tudo e retorna o que foi armazenado.

			Reporta rastilho.
		*/
		se (ef.clave_verificar_encerro_forçado(&ef, &intérprete_grade_)) {
			DESBRAGA_TÓPICO("ENCERRO FORÇADO");
			break;
		}

		/*
			Se um comentário for encontrado, ignora a linha.

			Reporta rastilho.
		*/

		se (ef.clave_verificar_comentário(&ef, &intérprete_grade_)) {
			break;
		}

		se (ef.clave_verificar_indicador_ficha(&ef, intérprete)) {
			continue;
		}

		se (operação_->expectação iqual expectação__ficha_abre)
		{
			se (ef.clave_verificar_indicador_ficha_abre(&ef, intérprete)) {
				continue;
			}
		}

		// Leitura da ficha
		se (operação_->expectação iqual expectação__ficha_fecha) {
			se (ef.procurar_ficha(&ef, intérprete)) {				
				operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef.operação_n);
				operação_linha = grade_procurar(operação->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

				continue;
			}

			linha_introduzir_charactére(ef.charactére, ef.ficha_n, &ef.ficha);
			ef.ficha_n++;
			continue;
		}

		//
		/*
		if (operação_->tipo iqual operação__concessão_objectiva e
		clave_têr_por_tipo(clave_ficha).pala[2] iqual ef.charactére)
		{
			if (clave_têr_por_tipo(clave_lêr).pala[0] iqual ef.pilha.conteúdo[ef.recúo - 2]) {
				linha_aparar(&operação_->linha);

				ef.operação_linha_n = 0;
				ef.operação_n++;

				operação_re_definir(ef.operação_n, &expressão_grade_, expectação__nil, operação__valôr, 1);

				ef.pula = 1;
				continue;
			}
			else
			{
				ef.intérprete_rastilho_definir(&ef, &intérprete_grade_, rastilho__carece_concessão_válida);
				expressão_n_++;
				break;
			}
		}
		*/

		/*
			A linha é o limitante que separa cada linha, quando for atingido, avalia-se a linha
			e seus elementos para averiguar a sua integridade.
		*/
		se (ef.charactére iqual linha_salta ou ef.charactére iqual EOF) {
			expressão->índice = expressão_n_;

			DESBRAGA_TÓPICO("%s", operação_linha_);

			linha_aparar(&operação_linha_);

			se (ef.operação_n iqual 0 e operação_linha_[ef.operação_linha_n] differente linha_nil) {
				ef.intérprete_rastilho_definir(&ef, &intérprete_grade_, rastilho__carece_concessão);
			}
			ou_se (ef.operação_n iqual 0 e operação_linha_[ef.operação_linha_n] iqual linha_nil) {
				// Se a linha estiver vazia, inteiramente, não mostra mensagens, é irritante.
				*expressão = expressão_falha();
				ef.intérprete_rastilho_definir(&ef, &intérprete_grade_, rastilho__nil);
				DESBRAGA_MENSAGEM("\n");
				break;
			}

			se (ef.operação_n iqual 1) {
				ef.intérprete_rastilho_definir(&ef, &intérprete_grade_, rastilho__carece_valôr);
			}
			se (ef.operação_n iqual 2) {
				ef.intérprete_rastilho_definir(&ef, &intérprete_grade_, rastilho__nil);
			}

			// Todos as operações que precisam dos valôres completos são validados após o registro de toda a linha.
			/*
			se (ef.expressão_verificar_concessão_corredora(&ef, &intérprete_grade_)) continue;
			se (ef.expressão_verificar_concessão_passiva(&ef, &intérprete_grade_)) continue;
			se (ef.expressão_verificar_concessão_objectiva(&ef, &intérprete_grade_)) continue;
			se (ef.expressão_verificar_concessão_selectiva(&ef, &intérprete_grade_)) continue;
			*/

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
		se (operação_->expectação iqual expectação__concessão) {
			se (ef.clave_verificar_concessão_directa(&ef, &intérprete_grade_)) {

				DESBRAGA_TÓPICO("CONCESSÃO DIRECTA");

				/*
				if (ef.clave_verificar_concessão_objectiva(&ef, &intérprete_grade_)) {
					DESBRAGA_MENSAGEM();
					DESBRAGA_MENSAGEM("CONCESSÃO OBJECTIVA");
					DESBRAGA_MENSAGEM();

					continue;
				}

				if (ef.clave_verificar_concessão_corredora(&ef, &intérprete_grade_)) {
					ef.operação_aparar_e_re_definir(&ef, &intérprete_grade_);
					continue;
				}

				if (ef.clave_verificar_concessão_passiva(&ef, &intérprete_grade_)) {
					if (ef.clave_verificar_concessão_selectiva(&ef, &intérprete_grade_)) {
						ef.operação_aparar_e_re_definir(&ef, &intérprete_grade_);
						continue;
					}

					ef.operação_aparar_e_re_definir(&ef, &intérprete_grade_);
					continue;
				}
				*/

				ef.operação_aparar_e_re_definir(&ef, intérprete);
				operação = grade_procurar(operações->filho, linhar_(estructura_instância(Operação)), ef.operação_n);
				operação_linha = grade_procurar(operação->filho, linhar_(estructura_instância(Operação).linha), índice__qualquer);

				continua;
			}

			operação_->expectação = expectação__concedido;
		}

		ef.introduzir_concedido(&ef, intérprete);
		DESBRAGA_MENSAGEM("%d", ef.operação_n);
    }

fim:

	memória_des_allocar(&ef.pilha.conteúdo);
	memória_des_allocar(&ef.ficha);
	devolve;

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

#define linhas_                 (*linhas)
#define linha_					((Linha) (*linha).elemento)

#endif // #if defined(DEFINIÇÃO)

    se (intérprete->tipo differente lsve_tipo_intérprete) {
		DESBRAGA_TÓPICO("Grade não é do tipo correcto");
		abort();
        goto fim;
    }

    int expressão_n = 0;

    enquanto (linhas_[expressão_n].índice iqual expressão_n) {
        se (linhas_[expressão_n].tipo differente tipo_linha) abort();

		DESBRAGA_MENSAGEM("%d", expressão_n);
		interpretar_linha(&linhas_[expressão_n], intérprete, &expressão_n);

		prossegue;

		goto fim;
    }

fim:

	return;

#if defined(DES_DEFINIÇÃO)

#undef linha_
#undef linhas_

#endif // #if defined(DES_DEFINIÇÃO)
}
