#ifndef MATRIZESPARSA_H_INCLUDED
#define MATRIZESPARSA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct elemento
{
    struct elemento *Direita, *Baixo;
    int Lin, Col;
    int Valor;
};
typedef struct elemento elemento_t;

int criaMatriz(elemento_t *m, int l, int c);
void insereMatriz(elemento_t *m, int l, int c);
int checaElemento(elemento_t *m, int c, int l);
void contaVizinhanca(elemento_t *m, elemento_t *n);

#endif // MATRIZESPARSA_H_INCLUDED
