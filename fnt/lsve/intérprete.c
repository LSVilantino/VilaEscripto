#include "intérprete.h"

#include "../pilha.h"
#include "../linha.h"
#include "general.h"

#include <stdio.h>
#include <stdlib.h>

Expressão expressão_interpretar(char* linha) {
    Expressão resultado;

    Pilha pilha = pilha_construir(3);
    int recúo = pilha.recúo;

	int linha_n = 0;
	int operadôr_n = 0;
	int operadôr_linha_n = 0;

	resultado.operador = memória_allocar(sizeof(Operação));
	resultado.operador[operadôr_n].expectação = expecta_concedido;
	resultado.operador[operadôr_n].linha = memória_allocar(1);

    while (recúo > 1)
    {
		if (linha[linha_n] == LINHA_NIL) { recúo--; }
		else {
			pilha_introduzir(linha[linha_n], &pilha);
			linha_n++;
		}

		if (pilha.conteúdo[recúo - 1] == LINHA_NIL) continue;

		resultado.operador[operadôr_n].seAbre = vero;
		linha_introduzir_charactére(pilha.conteúdo[recúo - 1], operadôr_linha_n, &resultado.operador[operadôr_n].linha);
		printf("%c", resultado.operador[operadôr_n].linha[operadôr_linha_n]);

		operadôr_linha_n++;
    }

    return resultado;
}

Intérprete interpretar(char** linhas) {
    Intérprete resultado = { 0 };

    for (int i = 0; linhas[i] != LINHA_NIL; i++)
    {
        expressão_interpretar(linhas[i]);
    }

    return resultado;
}
