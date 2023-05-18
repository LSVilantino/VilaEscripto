#include "general.h"
#include <stdio.h>

char clave_ficheiro_encerro = EOF;
char clave_ficheiro_forçar_encerro = '%';
char clave_ficheiro_comentário = '#';

char* clave_lêr = ">";
char* clave_lêr_e_avançar = ">>";
char* clave_procurar_abre = "$(";
char* clave_lêr_avançar_e_procurar = ">$(";
char* clave_corrêr = ">@>";
char* clave_lêr_e_escolher = ">>>";