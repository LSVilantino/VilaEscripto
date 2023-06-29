#ifndef _CABEÇALHO_LSVE_INTÉRPRETE
#define _CABEÇALHO_LSVE_INTÉRPRETE

#include "general.h"

#define ÍNDICE_ERRO -1

/*
* Qual o erro foi gerado?
*/

typedef enum Rastilho_Tipo {
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
	// Clave
	operação__concedido,
	// O valôr da clave é literalmente o que seguir.
	operação__concessão_directa,
	// O valôr da clave é o caminho do ficheiro,
	// importa-se as claves de outro ficheiro
	operação__concessão_passiva,
	// O valôr da clave é o da clave de outro ficheiro.
	// Indica-se o nome da clave e é buscado em outro ficheiro.
	operação__concessão_objectiva,
	// O valôr da clave é o que o utilizador seleccionar.
	operação__concessão_selectiva,
	// Corre-se o commando que segue a clave.
	operação__concessão_corredora,
	// Valôr da clave.
	operação__valôr,
	// Nada.
	operação__nil // Terminação das operações
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
    char* linha;

	int índice;
} Operação;

typedef struct Expressão {
    Operação* operador;
	Rastilho rastilho;
    char* linha;

	int índice;
} Expressão;

typedef struct Intérprete {
    Expressão* expressão;
    Rastilho* rastilho;
} Intérprete;

Operação operação_construir_falha();
Operação operação_daExpressão_têrPorTipo(Operação_Tipo tipo, Expressão expressão);
void operação_re_definir(int operadôr_n, Expressão* expressão, Expectação expectação, Operação_Tipo operação_tipo, size_t linha_t);
Expressão expressão_construir_falha();
Operação operação_daExpressão_têrPorClave(LINHA linha, Expressão expressão);
Dico operação_daExpressão_seTem_PorClave(LINHA linha, Expressão expressão);
Expressão expressões_têrPorClave(LINHA clave, Expressão* expressões);

void expressão_interpretar(char* linha, Intérprete* intérprete, int* expressão_n);
int intérprete_expressões_contar(Intérprete* intérprete);
Intérprete* interpretar(char** linhas, Intérprete* intérprete);

#endif // !_CABEÇALHO_LSVE_INTÉRPRETE
