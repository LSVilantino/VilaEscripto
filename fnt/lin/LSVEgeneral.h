#ifndef _CABEÇALHO_LSVE_GENERAL
#define _CABEÇALHO_LSVE_GENERAL

#include "general.h"

#include <stdio.h>

#define grade_como(var, tipo) (*(tipo*) (var).elemento)

typedef enum { 
    elems_tipo(lsve_)
    lsve_tipo_grade,
    lsve_tipo_intérprete,
    lsve_tipo_expressão,
    lsve_tipo_operação,
    lsve_tipo_rastilho,
}
LSVE_Tipo;

typedef struct LSVE_Grade LSVE_Grade;
struct LSVE_Grade {
	elems_lato(LSVE_);

    int índice;
    LSVE_Grade* filho;
};

typedef enum {
clave_ficha, // $
clave_ficha_abre, // (
clave_ficha_fecha, // )

clave_ficheiro_encerro, // EOF
clave_ficheiro_forçar_encerro, // %
clave_ficheiro_comentário, // #
/*
* Atribui o valôr bruto e literal à clave.
*
* ex.: PLATAFORMA > WINDOWS
* ex.: COMPILADÔR > ..\..\Compiladôres.txt
*	— o valôr é literalmente o caminho
*/
clave_lêr, // >
/*
* Selecciona todos (quando sem parâmetros),
* ou algum valôr especificado em outro ficheiro de forma automática.
*
* ex.: COMPILADÔRES >> ..\..\Compiladôres.txt
* ex.: COMPILADÔR DA PLATAFORMA >$(Plataforma)> ..\..\Compiladôres.txt
*/
clave_lêr_e_avançar, // >>
clave_lêr_avançar_e_procurar, // >$(CLAVE)>
/*
* Usa a função 'system' para corrêr um commando atribuído à clave.
*
* ex.: IR_CAMINHO_PROJECTO * cd $(Caminho do Projecto)
*/
clave_corrêr, // *
/*
* Permite a selecção de algum valôr em outro ficheiro.
*
* ex.: COMPILADÔR >>> ..\..\Compiladôres.txt
*/
clave_lêr_e_escolher // >>>
} Palaclave_Tipo;

typedef struct {
	Linha pala;
	Palaclave_Tipo tipo;
} Palaclave;

Palaclave clave_têr_por_tipo(Palaclave_Tipo tipo);
Palaclave_Tipo clave_comparar(Linha linha);

#endif // !_CABEÇALHO_LSVE_GENERAL
