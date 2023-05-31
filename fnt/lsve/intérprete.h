#ifndef _CABEÇALHO_LSVE_INTÉRPRETE
#define _CABEÇALHO_LSVE_INTÉRPRETE

#include "../general.h"

typedef struct Rastilho {
    char* erro;
} Rastilho;

typedef enum Operação_Tipo {
    concessão_directa,
    concessão_passiva,
    concessão_selectiva,
    concessão_corredora,
} Operação_Tipo;

typedef struct Operação {
    Operação_Tipo tipo;
    char* linha;
} Operação;

typedef struct Expressão {
    Operação* operador;
    Dico seAbre;
    Dico seFecha;
} Expressão;

typedef struct Intérprete {
    Expressão* espressão;
    Rastilho* rastilho;
} Intérprete;

Expressão expressão_interpretar(char* linha);

#endif // !_CABEÇALHO_LSVE_INTÉRPRETE
