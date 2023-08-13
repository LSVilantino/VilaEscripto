#ifndef _CABEÇALHO_MEMÓRIA_AUTO_MÁTICA
#define _CABEÇALHO_MEMÓRIA_AUTO_MÁTICA

#include <stddef.h>

void ma_arrancar();
void ma_memória_allocar(void** ponteiro, size_t tamanho);
void ma_encerrar();

#endif // #ifndef _CABEÇALHO_MEMÓRIA_AUTO_MÁTICA