#ifndef _CABEÇALHO_LSVE_INTÉRPRETE
#define _CABEÇALHO_LSVE_INTÉRPRETE

#include "../general.h"

/*
* Qual o erro foi gerado?
*/

typedef enum Rastilho_Tipo {
	rastilho__carece_concedido,
	rastilho__carece_concessão,
	rastilho__carece_concessão_válida,
	rastilho__carece_valôr,
	rastilho__expressão_excedente, // Quando se tem elementos mais do que esperados.
	rastilho__encerro_forçado, // Quando se encontra quebra-de-ficheiro na linha.
	rastilho__comentário, // Linha comentada.
	rastilho__nil,
} Rastilho_Tipo;


typedef struct Rastilho {
    Rastilho_Tipo tipo;
    char* erro;
} Rastilho;

/*
* O quê foi lido?
*
* Um concedido (variável)?
* Uma concessão direta? Onde se concede o valôr bruto?
*/

typedef enum Operação_Tipo {
	operação__concedido,
	operação__concessão_directa,
	operação__concessão_passiva,
	operação__concessão_selectiva,
	operação__concessão_corredora,
	operação__valôr,
} Operação_Tipo;

/*
* O quê se espera que venha a seguir?
*/
typedef enum Expectação {
    expectação__concedido,
    expectação__concessão,
    expectação__valôr,
    expectação__ficha_abre,
    expectação__ficha_fecha,

	expectação__nil // Nada a aguardar/descohece-se o quê aguardar.
} Expectação;

typedef struct Operação {
    Operação_Tipo tipo;
	Expectação expectação;
    /*Dico seAbre;
    Dico seFecha;*/
    char* linha;
} Operação;

typedef struct Expressão {
    Operação* operador;
	Rastilho rastilho;
    char* linha;
} Expressão;

typedef struct Intérprete {
    Expressão* expressão;
    Rastilho* rastilho;
} Intérprete;

Expressão expressão_interpretar(char* linha);
Intérprete interpretar(char** linha);

#endif // !_CABEÇALHO_LSVE_INTÉRPRETE
