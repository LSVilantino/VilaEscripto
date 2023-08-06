#ifndef _CABEÇALHO_LSVE_INTÉRPRETE
#define _CABEÇALHO_LSVE_INTÉRPRETE

#include "general.h"

/*
* Qual o erro foi gerado?
*/

typedef enum {
	rastilho__carece_concedido,
	rastilho__carece_concessão,
	rastilho__carece_concessão_válida,
	rastilho__carece_ficha_válida,
	rastilho__carece_valôr,
	rastilho__expressão_excedente, // Quando se tem elementos mais do que esperados.
	rastilho__encerro_forçado, // Quando se encontra quebra-de-ficheiro na linha.
	rastilho__comentário, // Linha comentada.
	rastilho__nil,
} Rastilho_Tipo;


typedef struct {
    Rastilho_Tipo tipo;
    Linha erro;
} Rastilho;

/*
* O quê foi lido?
*
* Um concedido (variável)?
* Uma concessão direta? Onde se concede o valôr bruto?
*/

typedef enum {
	operação__concedido, // Clave. 
	operação__concessão_directa, // O valôr da clave é literalmente o que seguir.
	operação__concessão_passiva, // O valôr da clave é são as claves de outro ficheiro.
	operação__concessão_objectiva, // Indica-se o nome da clave e é buscado em outro ficheiro.
	operação__concessão_selectiva, // O valôr da clave é o que o utilizador seleccionar.
	operação__concessão_corredora, // Corre-se o commando que segue a clave.
	operação__valôr, // Valôr da clave.
	operação__nil // Nada. Terminação das operações
} Operação_Tipo;

/*
* O quê se espera que venha a seguir?
*/
typedef enum {
    expectação__concedido,
    expectação__concessão,
    expectação__valôr,
    expectação__ficha_abre,
    expectação__ficha_fecha,

	expectação__nil // Nada a aguardar/descohece-se o quê aguardar.
} Expectação;

typedef struct {
	int índice;

    Operação_Tipo tipo;
	Expectação expectação;
    Linha linha;
} Operação;

Operação operação_construir_falha();
Operação operação_daExpressão_têrPorTipo(Operação_Tipo tipo, Grade expressão);
void operação_re_definir(int operador_n, Grade* expressão, Expectação expectação, Operação_Tipo operação_tipo, size_t linha_t);
Operação operação_daExpressão_têrPorClave(Linha linha, Grade expressão);
Dico operação_daExpressão_seTem_PorClave(Linha linha, Grade expressão);

typedef struct {
	int índice;

    Operação* operador;
	Rastilho rastilho;
    Linha linha;
} Expressão;

Expressão expressão_construir_falha();
Grade expressões_têrPorClave(Linha clave, Grade** expressões);

typedef struct {
    Expressão* expressão;
    Rastilho* rastilho;
} Intérprete;


int intérprete_expressões_contar(Grade* intérprete);

/*
	1. ponteiro real de matriz
	2. ponteiro real de matriz
*/
void interpretar(Grade** linhas, Grade** intérprete);
/*
	1. ponteiro real
	2. ponteiro real
	3. ponteiro real, auto-incremental.
*/
void interpretar_linha(const Grade* linha, Grade* intérprete, int* expressão_n);

#endif // !_CABEÇALHO_LSVE_INTÉRPRETE
