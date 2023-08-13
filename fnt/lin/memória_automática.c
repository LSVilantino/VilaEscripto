#include "memória_automática.h"
#include "general.h"

typedef struct {
    size_t tamanho;
    int quantidade;
    void*** ponteiro;
} Memória_AutoMática;

static Memória_AutoMática ma;

void 
ma_arrancar() {
    ma = (Memória_AutoMática) {
    .tamanho = 0,
    .quantidade = 0,
    .ponteiro = nil
    };
}

void 
ma_memória_allocar(void** ponteiro, size_t tamanho) {
#define ponteiro_ (*ponteiro)

    ponteiro_ = memória_allocar(tamanho);
    ma.tamanho += tamanho;
    ma.ponteiro = memória_re_allocar(ma.tamanho, ma.ponteiro);

    ma.ponteiro[ma.quantidade] = &ponteiro_;
    ma.quantidade++;

#undef ponteiro_
}

void 
ma_encerrar() {
    int quantidade = 0;

    while(ma.quantidade != quantidade) {
        memória_des_allocar((void**) &ma);
        quantidade++;
    }

    memória_des_allocar((void**) &ma.ponteiro);
}