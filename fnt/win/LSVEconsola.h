#ifndef _CABEÇALHO_LSVE_CONSOLA
#define _CABEÇALHO_LSVE_CONSOLA

#include "LSVEintérprete.h"

void lsve_consola_limpar();
void lsve_consola_opção_mostrar(int opçãoSeleccionada, Expressão* expressões);
Operação lsve_consola_construir_menu(Expressão* expressões);

#endif // _CABEÇALHO_LSVE_CONSOLA
