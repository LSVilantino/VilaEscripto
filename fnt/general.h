#ifndef _CABEÇALHO_GENERAL
#define _CABEÇALHO_GENERAL

#include <stdio.h>

typedef enum { false, true } bool;

char* clave_ficha;
char* clave_ficha_abre;
char* clave_ficha_fecha;

char clave_ficheiro_encerro;
char clave_ficheiro_forçar_encerro;
char clave_ficheiro_comentário;
/*
* Atribui o valôr bruto e literal à clave.
*
* ex.: PLATAFORMA > WINDOWS
* ex.: COMPILADÔR > ..\..\Compiladôres.txt
*	— o valôr é literalmente o caminho
*/
char* clave_lêr;
/*
* Selecciona todos (quando sem parâmetros),
* ou algum valôr especificado em outro ficheiro de forma automática.
*
* ex.: COMPILADÔRES >> ..\..\Compiladôres.txt
* ex.: COMPILADÔR DA PLATAFORMA >$(Plataforma)> ..\..\Compiladôres.txt
*/
char* clave_lêr_e_avançar;
char* clave_lêr_avançar_e_procurar;
/*
* Usa a função 'system' para corrêr um commando atribuído à clave.
*
* ex.: IR_CAMINHO_PROJECTO * cd $(Caminho do Projecto)
*/
char* clave_corrêr;
/*
* Permite a selecção de algum valôr em outro ficheiro.
*
* ex.: COMPILADÔR >>> ..\..\Compiladôres.txt
*/
char* clave_lêr_e_escolher;




void* memória_allocar(size_t tamanho);
void* memória_re_allocar(size_t tamanho, void* p);
#endif // _CABEÇALHO_GENERAL
