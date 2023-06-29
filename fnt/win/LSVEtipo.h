#ifndef _CABEÇALHO_LSVE_TIPO
#define _CABEÇALHO_LSVE_TIPO

typedef struct Conteúdo {
    char** fichas;
    int quantidade;
} Conteúdo;

typedef enum ConteúdoTipo {
    ct_int,
    ct_char,
} ConteúdoTipo;

#endif // !_CABEÇALHO_LSVE_TIPO
