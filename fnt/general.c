#include "general.h"

/*
* Usa a função 'system' para corrêr um commando atribuído à clave.
* 
* ex.: IR_CAMINHO_PROJECTO >* cd $(Caminho do Projecto)
*/ 
char* clave_corrêr = ">*";
/*
* Permite a selecção de algum valôr em outro ficheiro.
* 
* ex.: COMPILADÔR >>> ..\..\Compiladôres.txt
*/
char* clave_lêr_e_escolher = ">>>";
/*
* Selecciona todos (quando sem parâmetros), 
* ou algum valôr especificado em outro ficheiro de forma automática.
* 
* ex.: COMPILADÔRES >> ..\..\Compiladôres.txt
* ex.: COMPILADÔR DA PLATAFORMA >$(Plataforma)> ..\..\Compiladôres.txt
*/
char* clave_lêr_e_avançar = ">>";
/*
* Atribui o valôr bruto e literal à clave. 
* 
* ex.: PLATAFORMA > WINDOWS
* ex.: COMPILADÔR > ..\..\Compiladôres.txt 
*	— o valôr é literalmente o caminho
*/
char* clave_lêr = ">";