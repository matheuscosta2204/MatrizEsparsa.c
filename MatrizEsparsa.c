#include <stdio.h>
#include "MatrizEsparsa.h"


int main()
{
    elemento_t *m;
    m = (elemento_t*)malloc(sizeof(elemento_t));

    if(!criaMatriz(m, 10, 10))
        return 0;

    insereMatriz(m, 0, 0);
    printf("%.2f\n", m->Baixo->Direita->Valor);

    return 0;
}
void insereMatriz(elemento_t *m, int l, int c)
{
    elemento_t *elemento, *refLin, *refCol, *aux;

    elemento = (elemento_t*)malloc(sizeof(elemento_t));
    refLin = (elemento_t*)malloc(sizeof(elemento_t));
    refCol = (elemento_t*)malloc(sizeof(elemento_t));
    aux = (elemento_t*)malloc(sizeof(elemento_t));

    aux = m;
    while(aux->Lin != l)
        aux = aux->Baixo;
    refLin = aux;
    aux = m;
    while(aux->Col != c)
        aux = aux->Direita;
    refCol = aux;

    if(refLin->Direita->Col == -1 && refCol->Baixo->Lin == -1)
    {
        refLin->Direita = elemento;
        refCol->Baixo = elemento;
        elemento->Baixo = refCol;
        elemento->Direita = refLin;
        elemento->Col = c;
        elemento->Lin = l;
        elemento->Valor = 15;
    }

    while(refLin->Direita->Col < c && refLin->Direita->Col != -1)
        refLin = refLin->Direita;

    if(refLin->Col == c)
    {
        aux = refLin->Direita;
        elemento = refLin->Direita;
        elemento->Direita = aux;
    }

    while(refCol->Baixo->Lin < l)
        refCol = refCol->Baixo;

    if(refCol->Lin == l)
    {
        aux = refCol->Baixo;
        elemento = refCol->Baixo;
        elemento->Baixo = aux;
    }

    elemento->Col = c;
    elemento->Lin = l;
    elemento->Valor = 15;

}

int criaMatriz(elemento_t *m, int l, int c)
{
    elemento_t *Lin, *Col;
    int i;

	m->Direita = m;
	m->Baixo = m;
	m->Lin = -1;
	m->Col = -1;

    Lin = (elemento_t*)malloc(l*sizeof(elemento_t));
    Col = (elemento_t*)malloc(c*sizeof(elemento_t));

    if(Lin == NULL || Col == NULL)
	{
	    printf("Erro de alocação no cria Linha ou Coluna!");
        return 0;
	}

    m->Baixo = &Lin[0];
    for(i=0;i<l-1;i++)
    {
        Lin[i].Baixo = &Lin[i+1];
        Lin[i].Lin = i;
        Lin[i].Col = -1;
        Lin[i].Direita = &Lin[i];
    }
    Lin[i].Baixo = m;

    m->Direita = &Col[0];
    for(i=0;i<l-1;i++)
    {
        Col[i].Direita = &Col[i+1];
        Col[i].Lin = -1;
        Col[i].Col = i;
        Col[i].Baixo = &Col[i];
    }
    Col[i].Direita = m;

    return 1;
}
