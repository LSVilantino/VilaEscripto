#include "ficheiro.h"
#include "general.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

char**
ficheiro_lêr(char* caminho) {
    FILE* ficheiro;
    errno_t numErro = fopen_s(&ficheiro, caminho, "r");
    if (numErro != 0) {
        printf("O ficheiro %s não foi encontrado, ou está ocupado.", caminho); abort();
    }

    char** linhas = memória_allocar(sizeof(char*));
    int quantidadeDeRecúo = 3;
    // A quantía de charactéres a lêr adiantados.
    char* charactéresActuais = memória_allocar(quantidadeDeRecúo);
    // Com um só, aloca-se um só, guarda-se somente um charactére.
    // A depender do que se fôr feito, precisa pré-visibilidade.
    char* linhaActual = memória_allocar(1);


    fclose(ficheiro);

    return linhas;
}
