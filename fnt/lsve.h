/*
	Devem ser incluídas funções de propósito exclusivo ao LSVE,
	estas são feitas para os casos de inviabilidade das de uso geral.

	Se, por exemplo, o LSVE requêr que o mapeamento de um ficheiro seja
	diferente pela adição de algum campo à estrutura de mapa, herda desta
	e incrementa suas propriedades exclusivas.
*/

#ifndef _CABEÇALHO_LSVE
#define _CABEÇALHO_LSVE

#include "mapa.h"

typedef struct LSVEMapa {
	struct Mapa;
	char* separadôr;
} LSVEMapa;

char** lsve_linha_separar(char* separadôr, char* linha);
char** lsve_ficha_tratar(char** linhas);

char* lsve_ficheiro_valôr_tratar(Tipo clave_tipo, void* clave, LSVEMapa* mapa);
LSVEMapa* lsve_ficheiro_conteúdo_mapear(char* ficheiroCaminho);

LSVEMapa* lsve_mapa_construir();
LSVEMapa* lsve_mapa_procurar(Tipo tipo, void* procura, LSVEMapa* mapa);
void lsve_mapa_introduzir(LSVEMapa** mapa, LSVEMapa valôr);
char** lsve_mapa_a_matriz_char(LSVEMapa* linhas);
#endif // _CABEÇALHO_LSVE