#ifndef _CABEÇALHO_LSVE_GENERAL
#define _CABEÇALHO_LSVE_GENERAL

#include <stdio.h>

typedef enum { false, true } bool;

const char* clave_ficha;
const char* clave_ficha_abre;
const char* clave_ficha_fecha;

const char clave_ficheiro_encerro;
const char clave_ficheiro_forçar_encerro;
const char clave_ficheiro_comentário;
/*
* Atribui o valôr bruto e literal à clave.
*
* ex.: PLATAFORMA > WINDOWS
* ex.: COMPILADÔR > ..\..\Compiladôres.txt
*	— o valôr é literalmente o caminho
*/
const char* clave_lêr;
/*
* Selecciona todos (quando sem parâmetros),
* ou algum valôr especificado em outro ficheiro de forma automática.
*
* ex.: COMPILADÔRES >> ..\..\Compiladôres.txt
* ex.: COMPILADÔR DA PLATAFORMA >$(Plataforma)> ..\..\Compiladôres.txt
*/
const char* clave_lêr_e_avançar;
const char* clave_lêr_avançar_e_procurar;
/*
* Usa a função 'system' para corrêr um commando atribuído à clave.
*
* ex.: IR_CAMINHO_PROJECTO * cd $(Caminho do Projecto)
*/
const char* clave_corrêr;
/*
* Permite a selecção de algum valôr em outro ficheiro.
*
* ex.: COMPILADÔR >>> ..\..\Compiladôres.txt
*/
const char* clave_lêr_e_escolher;

#endif // !_CABEÇALHO_LSVE_GENERAL
