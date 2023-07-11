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

void 
interpretar_linha(Grade* linha, Grade** intérprete, int* expressão_n) {
#define _linha ((char*) (*linha).elemento)
#define _expressão_n (*expressão_n)

#define _operador ((Operação) _expressão_grade.filho[operador_n])
#define _operadores ((Operação) _expressão_grade.filho)

#define _recúo recúo - 1

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
        (Lato){tipo_tamanho, fal, &(int){3}}
    });

    int recúo = pilha.recúo;

    Linha ficha = memória_preên_allocar(1, sizeof(char));

    DESBRAGA_MENSAGEM("LINHA A DESBRAGAR %s", _linha)

    while(recúo > 1) {
        /* Ao fim da linha, diminui - se o recúo da pilha, até chegar à ponta,
		*  o último charactére armazenado.
		*
		* Se a linha não estiver ao fim, introduz o último charactére à pilha.
		*/
		if (_linha[linha_n] == LINHA_NIL) { recúo--; }
		else {
			pilha_introduzir(_linha[linha_n], &pilha);
			
            linha_n++;
		}
        
		char charactére = pilha.conteúdo[_recúo];
        DESBRAGA_MENSAGEM("%c", charactére)

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
    }

fim:

free(pilha.conteúdo);
free(ficha);

#undef _linha
#undef _expressão_n
return;
}

void
interpretar(Grade** linhas, Grade** intérprete) {
#define _linhas (*linhas)
#define _intérprete (*intérprete)

#define _expressões ((Expressão*) _intérprete.filho)
#define _expressão ((Expressão) _intérprete.filho[0].elemento[_expressão_n - 1])
#define _expressão_grade _intérprete.filho[0]
#define _rastilho ((Rastilho*) _intérprete.filho[1].elemento)

    if (_intérprete->tipo != lsve_tipo_intérprete) { 
        DESBRAGA_MENSAGEM("Grade não é do tipo correcto")
        goto fim;
    }

    int 
    linhas_n = 0, 
    expressão_n = 0
    ;

    while(_linhas[linhas_n].índice == linhas_n) {
        if (_linhas[linhas_n].tipo == tipo_linha) {
            interpretar_linha(&_linhas[linhas_n], &_intérprete, &expressão_n);
            linhas_n++;

            goto fim;
        }
    }

fim:
#undef _linhas 
#undef _intérprete

#undef _expressões
#undef _expressão
#undef _rastilho
return;
}