#ifndef _CABEÇALHO_GENERAL
#define _CABEÇALHO_GENERAL

#include <stdlib.h>
#include <stdio.h>

#define nil NULL
// Nil para estructuras, sem ponteiros.
#define nil_e {0}

#define LINHA_NIL '\0'
#define LINHA_SALTA '\n'
#define ESPAÇO ' '
#define FICHEIRO_MODO_LEITURA "r"
#define FICHEIRO_MODO_LEITURA_BINÁRIA "rb"




/*
    construir depois alguns sinais indicadores para
    controlar o fluxo da aplicação
*/

//#if defined(DESBRAGA) && DESBRAGA > 0
#define DESBRAGA_MENSAGEM(formato, ...) printf("DESBRAGA ― %s:%d:%s: " \
formato, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
printf("%c", LINHA_SALTA); \
//#else
//#define DESBRAGA_MENSAGEM(formato, ...) /* Faz nada em modo público */
//#endif













// 'linha' (repare o 'L' minúsculo) muitas das vezes é nome de variáveis
typedef void* Objecto;
// Não se usa typedef aqui, se não se considera como outro tipo.
typedef char* Linha;

// Construcção de tipo dicotômico.
typedef enum { fal, vero } Dico;

//-------------------------
// DEFINIÇÕES FUNCIONAIS
//-------------------------

#define var_nome(var) #var

#define definição(prefixo, base, sufixo) prefixo##base##sufixo

#define linha_juntar(a, b) a ## b
#define linha_juntar_cobra(a, b) a ## _ ## b

/*
    reutilização em enumeradores precisam seguir uma ordem
    específica para estarem sempre alinhados uns com os outros,
    em formato de cadeia de dependência.

    #define elems_A(prefixo) linha_juntar(prefixo, A_um)
    #define elems_B(prefixo) linha_juntar(prefixo, B_um)
    #define elems_C(prefixo) linha_juntar(prefixo, C_um)

    enum A {
        elems_A() (A_um = 1)
    }

    enum B {
        elems_A(B_) (B_A_um = 1, compatível com enum A)
        elems_B() (B_um = 2, elemento de B)
    }

    enum C {
        elems_A(C_) (C_A_um = 1, compatível com enum A e B)
        elems_B(C_) (C_B_um = 2, compatível com enum B)
        elems_C() (C_um = 3, elemento de C)
    }
*/

#define elems_tipo(nome) \
    linha_juntar(nome, tipo_charactére), /*char*/               \
    linha_juntar(nome, tipo_linha),      /*char* ou Linha */    \
    linha_juntar(nome, tipo_inteiro),    /*int*/                \
    linha_juntar(nome, tipo_tamanho),    /*size_t*/             \

typedef enum { elems_tipo() } Tipo;

//-------------------------
// DEFINIÇÕES DE ELEMENTOS
//-------------------------

/*
    definem-se os elementos em macros, para que possam
    ser re-utilizados em estructuras.

    GCC não suporta declaração de estruturas anônimas
    como MS CL suporta. Então, declarações assim, não fucionam:

    struct A {
        int elemento1;
    }

    struct B {
        struct A; 
        (implicitamente, importa-se 'elemento1')
        int elemento2;
    }

    Com o uso dos macros, é possível re-definir os campos sem
    que se tornem muito irreparáveis à larga escala, ou
    simplesmente para que não se tenha os efeitos de têr que
    replicar os mesmos campos em todos os lugares necessários.
*/
#define elems_lato(prefixoTipo)                 \
    linha_juntar(prefixoTipo, Tipo) tipo;       \
    Dico precisa_libertar;                      \
    Objecto elemento;                           \

typedef struct { elems_lato() } Lato;

typedef struct Grade Grade;
struct Grade {
	elems_lato();
	
	Linha constatação;
	int índice;
	Grade* filho;
};

void grade_introduzir(Grade** grade, Grade modelo);
Grade* grade_procurar(Linha constatação, Grade** grade);
void grade_des_allocar(Grade** grade);

void* memória_allocar(size_t tamanho);
void* memória_preên_allocar(size_t tamanho_allocação, size_t tamanho_tipo);
void* memória_re_allocar(size_t tamanho, void* p);

#endif // !_CABEÇALHO_GENERAL
