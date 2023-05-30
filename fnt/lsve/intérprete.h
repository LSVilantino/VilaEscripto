#ifndef _CABEÇALHO_LSVE_INTÉRPRETE
#define _CABEÇALHO_LSVE_INTÉRPRETE

typedef enum Expressão_Tipo {
    concessão_directa,
    concessão_passiva,
    concessão_selectiva,
    concessão_corredora,
};

typedef struct Expressão {
    char* linha;
    Expressão_Tipo tipo;
} Expressão;

#endif // !_CABEÇALHO_LSVE_INTÉRPRETE
