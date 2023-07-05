#include "LSVEintérprete.h"

#include "LSVEgeneral.h"
#include "linha.h"
#include "pilha.h"
#include "ficheiro.h"

//#include "LSVEconsola.h"
//#include "LSVEgeneral.h"

#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>

void 
expressão_interpretar(Grade** linha, Grade** intérprete, int* expressão_n) {

}

void 
interpretar(Grade** linhas, Grade** intérprete) {
    if ((*intérprete)->tipo != lsve_tipo_intérprete) { 
        printf("Grade não é do tipo correcto");
        return; 
    }

    int linhas_n = 0;
    int expressão_n = 0;

    while((*linhas)[linhas_n].índice != linhas_n) {
        if (grade_é_do_tipo(tipo_linha, (*linhas)[linhas_n])) {
                expressão_interpretar(&linhas[linhas_n], &(*intérprete), &expressão_n);
            linhas_n++;
        }
    }
}