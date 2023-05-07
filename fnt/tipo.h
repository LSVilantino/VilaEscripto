#ifndef _CABEÇALHO_TIPO
#define _CABEÇALHO_TIPO

typedef enum Tipo {
    tipo_int,
    tipo_char,
} Tipo;

typedef struct ConteúdoFicheiro {
    char** conteúdo;
    int quantidade_conteúdo;
} ConteúdoFicheiro;

#endif // _CABEÇALHO_TIPO
