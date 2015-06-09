#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "MatrizEsparsa.h"


int main()
{
    int i = 0;
    elemento_t *m, *n;
    m = (elemento_t*)malloc(sizeof(elemento_t));
    n = (elemento_t*)malloc(sizeof(elemento_t));

    if(!criaMatriz(m, 18, 18))
        return 0;
    if(!criaMatriz(n, 18, 18))
        return 0;
    insereMatriz(m, 1, 1);
    insereMatriz(m, 1, 2);
    insereMatriz(m, 1, 3);
    while(i < 1)
    {
        contaVizinhanca(m, n);
        system("cls");
        //printf("\n-------------------\n");
        contaVizinhanca(n, m);
        system("cls");
        //printf("\n-------------------\n");
        //i++;
    }
return 0;
}
void insereMatriz(elemento_t *m, int l, int c)
{
    elemento_t *elemento, *refLin, *refCol, *aux;
    int j;

    elemento = (elemento_t*)malloc(sizeof(elemento_t));

    elemento->Col = c;
    elemento->Lin = l;
    elemento->Valor = 1;

    refLin = m->Baixo;
    while(refLin->Lin != l)
        refLin = refLin->Baixo;

    j = 0;
    while((j < c) && refLin->Direita->Col != -1)
    {
        if(refLin->Direita->Col > c)
        {
            aux = refLin->Direita;
            refLin->Direita = elemento;
            elemento->Direita = aux;
        }
        else
            refLin = refLin->Direita;

        j++;
    }

    if(refLin->Direita->Col == -1)
    {
        refLin->Direita = elemento;
        elemento->Direita = refLin;
    }

    refCol = m->Direita;
    while(refCol->Col != c)
        refCol = refCol->Direita;

    j = 0;
    while((j < l) && refCol->Baixo->Lin != -1)
    {
        if(refCol->Baixo->Lin > l)
        {
            aux = refCol->Baixo;
            refCol->Baixo = elemento;
            elemento->Baixo = aux;
        }
        else
            refCol = refCol->Baixo;

        j++;
    }

    if(refCol->Baixo->Lin == -1)
    {
        refCol->Baixo = elemento;
        elemento->Baixo = refCol;
    }
}

int checaElemento(elemento_t *m, int l, int c)
{
    elemento_t *refCol, *refLin;
    refCol = m->Direita;
    refLin = m->Baixo;
    if(l-1 < -1 || c-1 < -1 || l+1 > 17 || c+1 > 17) //Se o elemento ultrapassar os limites, retorna 0.
        return 0;
    while(refCol->Col != c) //percorre a cabeça da coluna.
        refCol = refCol->Direita;
    if(refCol->Baixo->Lin != -1) //se existir elemento inserido.
    {
        while(refLin->Lin != l) //percorre a cabeça da linha.
            refLin = refLin->Baixo;
        if(refLin->Direita->Col != -1) //se também existir elemento inserido retorna 1.
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

void contaVizinhanca(elemento_t *m, elemento_t *n)
{
    int cont, i, j;
    for(i=0; i < 16; i++)
    {
        printf("\n");
        for(j=0; j < 16; j++)
        {
            cont = 0;                   /*checa elemento retorna 1 se achou elemento no parametro passado.
                                        se achou o elemento, faz uma verificação, se n tem elemento faz outra. */
            if(checaElemento(m, i, j))
            {
                //printf("ACHOU\n");
                cont += checaElemento(m, i-1, j-1);
                cont += checaElemento(m, i-1, j);
                cont += checaElemento(m, i-1, j+1);

                cont += checaElemento(m, i, j-1);
                cont += checaElemento(m, i, j+1);

                cont += checaElemento(m, i+1, j-1);
                cont += checaElemento(m, i+1, j);
                cont += checaElemento(m, i+1, j+1);

                if(cont == 3 || cont == 2)
                {
                    printf(" O");
                    insereMatriz(n, i, j);
                }
                else
                    printf(" .");
            }
            else
            {
                //printf("n achou elemento\n");
                cont += checaElemento(m, i-1, j-1);
                cont += checaElemento(m, i-1, j);
                cont += checaElemento(m, i-1, j+1);

                cont += checaElemento(m, i, j-1);
                cont += checaElemento(m, i, j+1);

                cont += checaElemento(m, i+1, j-1);
                cont += checaElemento(m, i+1, j);
                cont += checaElemento(m, i+1, j+1);
                if(cont == 3)
                {
                    printf(" O");
                    insereMatriz(n, i, j);
                }
                else
                    printf(" .");
            }
        }
    }
}
int criaMatriz(elemento_t *m, int l, int c)
{
    elemento_t *Lin, *Col;
    int i;

	m->Direita = m;
	m->Baixo = m;
	m->Lin = -1;
	m->Col = -1;

    Lin = (elemento_t*)malloc(l*sizeof(elemento_t)); //cria dois arrays que serao os cabeças de colunas e linhas.
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
