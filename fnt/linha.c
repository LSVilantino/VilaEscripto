#include "linha.h"
#include "general.h"

int linha_contar(char* linha) {
    int tamanho = 0;
    while (linha[tamanho]) tamanho++;

    return tamanho;
}

char* linha_duplicar(char* linha) {
    char* duplicata;
    int tamanho = linha_contar(linha);

    duplicata = memória_allocar(tamanho + 1); // mais nil

    for (int i = 0; i < tamanho; i++) duplicata[i] = linha[i];
    
    duplicata[tamanho] = LINHA_NIL;

    return duplicata;
}
