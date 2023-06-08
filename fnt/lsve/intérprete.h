#ifndef _CABEÇALHO_LSVE_INTÉRPRETE
#define _CABEÇALHO_LSVE_INTÉRPRETE

#include "../general.h"

/*
* Qual o erro foi gerado?
*/

typedef enum Rastilho_Tipo {
    carece_concedido,
    carece_concessão,
    carece_concessão_válida,
    carece_valôr,
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
    cocedido,
    concessão_directa,
    concessão_passiva,
    concessão_selectiva,
    concessão_corredora,
} Operação_Tipo;

/*
* O quê se espera que venha a seguir?
*/
typedef enum Expectação {
    expecta_concedido,
    expecta_concessão,
    expecta_valôr
} Expectação;

typedef struct Operação {
    Operação_Tipo tipo;
	Expectação expectação;
    Dico seAbre;
    Dico seFecha;
    char* linha;
} Operação;

typedef struct Expressão {
    Operação* operador;
    char* linha;
} Expressão;

typedef struct Intérprete {
    Expressão* expressão;
    Rastilho* rastilho;
} Intérprete;

Expressão expressão_interpretar(char* linha);
Intérprete interpretar(char** linha);

#endif // !_CABEÇALHO_LSVE_INTÉRPRETE
