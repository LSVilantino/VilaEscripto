#ifndef _CABEÇALHO_LSVE_INTÉRPRETE
#define _CABEÇALHO_LSVE_INTÉRPRETE

#include "LSVEgeneral.h"
#include "pilha.h"

/*
	Qual o erro foi gerado?
*/

typedef enum {
	rastilho__carece_concedido,
	rastilho__carece_concessão,
	rastilho__carece_concessão_válida,
	rastilho__carece_ficha_válida,
	rastilho__carece_valôr,
	rastilho__expressão_excedente,			// Quando se tem elementos mais do que esperados.
	rastilho__encerro_forçado,				// Quando se encontra quebra-de-ficheiro na linha.
	rastilho__comentário,					// Linha comentada.
	rastilho__nil,
} Rastilho_Tipo;

Linha rastilho_têr_linha_por_tipo(Rastilho_Tipo tipo);

typedef struct {
	int índice;

    Rastilho_Tipo tipo;
    Linha erro;
} Rastilho;

/*
	O quê foi lido?
	
	Um concedido (variável)?
	Uma concessão direta? Onde se concede o valôr bruto?
*/

typedef enum {
	operação__concedido,				// Clave. 
	operação__concessão_directa,		// O valôr da clave é literalmente o que seguir.
	operação__concessão_passiva,		// O valôr da clave é são as claves de outro ficheiro.
	operação__concessão_objectiva,		// Indica-se o nome da clave e é buscado em outro ficheiro.
	operação__concessão_selectiva,		// O valôr da clave é o que o utilizador seleccionar.
	operação__concessão_corredora,		// Corre-se o commando que segue a clave.
	operação__valôr,					// Valôr da clave.
	operação__nil						// Nada. Terminação das operações
} Operação_Tipo;

/*
	O quê se espera que venha a seguir?
*/
typedef enum {
    expectação__concedido,
    expectação__concessão,
    expectação__valôr,
    expectação__ficha_abre,
    expectação__ficha_fecha,

	expectação__nil // Nada a aguardar/desconhece-se o quê aguardar.
} Expectação;

typedef struct {
	int índice;

    Operação_Tipo tipo;
	Expectação expectação;
    Linha linha;
} Operação;

void operação_re_definir(int operação_n, Grade* expressão, Expectação expectação, Operação_Tipo operação_tipo, size_t linha_t);
Grade operação_falha();

typedef struct {
	int índice;

    Operação* operação;
    Linha linha;
} Expressão;

Grade* expressão_têr_por_ficha(Grade* expressões, Linha ficha);
Grade expressão_operação_têr_por_ficha(Grade* expressão, Linha ficha);
Grade expressão_operação_têr_por_tipo(Grade* expressão, Operação_Tipo tipo);
Grade expressão_falha();

typedef struct {
    Expressão* expressão;
    Rastilho* rastilho;
} Intérprete;

typedef struct EF_Interpretar EF_Interpretar;
struct EF_Interpretar {
	int
	ref expressão_n,
    operação_n,
    operação_linha_n,
    linha_n,
    clave_n,
    ficha_n,
	rastilho_n,
    pula
    ;

	Pilha pilha; int recúo;
	Linha ficha; char charactére;

	void (*intérprete_rastilho_definir)(EF_Interpretar ref tf, Grade ref intérprete, Rastilho_Tipo rastilho_tipo);

	Dico (*clave_verificar_encerro_forçado)(EF_Interpretar ref tf, Grade ref intérprete);
	Dico (*clave_verificar_comentário)(EF_Interpretar ref tf, Grade ref intérprete);

	Dico (*clave_verificar_indicador_ficha)(EF_Interpretar* ef, Grade* intérprete);
	Dico (*clave_verificar_indicador_ficha_abre)(EF_Interpretar* ef, Grade* intérprete);
	Dico (*procurar_ficha)(EF_Interpretar* ef, Grade* intérprete);

	Dico (*clave_verificar_concessão_directa)(EF_Interpretar ref tf, Grade ref intérprete);
	Dico (*clave_verificar_concessão_corredora)(EF_Interpretar ref tf, Grade ref intérprete);
	Dico (*clave_verificar_concessão_objectiva)(EF_Interpretar ref tf, Grade ref intérprete);
	Dico (*clave_verificar_concessão_passiva)(EF_Interpretar ref tf, Grade ref intérprete);
	Dico (*clave_verificar_concessão_selectiva)(EF_Interpretar ref tf, Grade ref intérprete);

	Dico (*expressão_verificar_concessão_corredora)(EF_Interpretar ref tf, Grade ref intérprete);
	Dico (*expressão_verificar_concessão_passiva)(EF_Interpretar ref tf, Grade ref intérprete);
	Dico (*expressão_verificar_concessão_objectiva)(EF_Interpretar ref tf, Grade ref intérprete);
	Dico (*expressão_verificar_concessão_selectiva)(EF_Interpretar ref tf, Grade ref intérprete);

	void (*introduzir_concedido)(EF_Interpretar ref tf, Grade ref intérprete);

	void (*operação_aparar_e_re_definir)(EF_Interpretar ref tf, Grade ref intérprete);
};

void intérprete_agregar(EF_Interpretar ref tf, Grade ref intérprete, Grade* expressões, int posição);
Grade intérprete_confeccionar(EF_Interpretar ref tf, Grade ref intérprete, Grade caminho);
int intérprete_expressões_contar(const Grade* intérprete);
void interpretar_linha(Grade ref linha, Grade ref intérprete, int ref expressão_n);
void interpretar(Grade* ref linhas, Grade *intérprete);

#endif // !_CABEÇALHO_LSVE_INTÉRPRETE
