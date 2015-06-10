#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <allegro.h>
#include "MatrizEsparsa.h"


int main()
{
    start_allegro();

    elemento_t *m, *n;
    m = (elemento_t*)malloc(sizeof(elemento_t));
    n = (elemento_t*)malloc(sizeof(elemento_t));

    BITMAP *buffer = create_bitmap(800, 600);
    if(!criaMatriz(m, 18, 18))
        return 0;
    if(!criaMatriz(n, 18, 18))
        return 0;

    insereMatriz(m, 2, 2);
    insereMatriz(m, 3, 3);
    insereMatriz(m, 4, 3);
    insereMatriz(m, 4, 2);
    insereMatriz(m, 4, 1);

    while(!key[KEY_ESC])
    {
    while(ticks > 0)
    {
        ticks = 1;
        limpaMatriz(n);
        contaVizinhanca(m, n);
        imprimeMatriz(n, buffer);
        blit(buffer, screen, 0,0,0,0, 800, 800);
        clear_bitmap(buffer);

        limpaMatriz(m);
        contaVizinhanca(n, m);
        imprimeMatriz(m, buffer);
        blit(buffer, screen, 0,0,0,0, 800, 800);
        clear_bitmap(buffer);
    }
        ticks--;
    }
    destroy_bitmap(buffer);
return 0;
}
END_OF_MAIN();

void limpaMatriz(elemento_t *m)
{
    elemento_t *refLin, *refCol, *deletado;
    refCol = m->Direita;
    refLin = m->Baixo;

    while(refLin->Lin != -1)
    {
        while(refLin->Direita->Col != -1)
        {
            deletado = refLin->Direita;
            refLin->Direita = deletado->Direita;
        }
        refLin = refLin->Baixo;
    }

    while(refCol->Col != -1)
    {
        while(refCol->Baixo->Lin != -1)
        {
            deletado = refCol->Baixo;
            refCol->Baixo = deletado->Baixo;
            free(deletado);
        }
        refCol = refCol->Direita;
    }
}
void insereMatriz(elemento_t *m, int l, int c)
{
    elemento_t *elemento, *refLin, *refCol, *aux;
    elemento = (elemento_t*)malloc(sizeof(elemento_t));

    elemento->Col = c;
    elemento->Lin = l;
    elemento->Valor = 1;

    refLin = m->Baixo;
    while(refLin->Lin != l)
        refLin = refLin->Baixo;

    while(refLin->Direita->Col < c && (refLin->Direita->Col != -1))
    {
        refLin = refLin->Direita;
    }
    //condicao igual
    aux = refLin->Direita;
    refLin->Direita = elemento;
    elemento->Direita = aux;

    refCol = m->Direita;
    while(refCol->Col != c)
        refCol = refCol->Direita;

    while(refCol->Baixo->Lin < l && refCol->Baixo->Lin != -1)
    {
        refCol = refCol->Baixo;
    }
    //condicao igual
    aux = refCol->Baixo;
    refCol->Baixo = elemento;
    elemento->Baixo = aux;

}

int checaElemento(elemento_t *m, int l, int c)
{
    elemento_t *ref;
    ref = m->Direita;
    if(l-1 <= -1 || c-1 <= -1 || l+1 >= 17 || c+1 >= 17) //Se o elemento ultrapassar os limites, retorna 0.
        return 0;

    while(ref->Col != c) //percorre a cabeça da coluna.
        ref = ref->Direita;

    ref = ref->Baixo;
    while(ref->Lin != l && ref->Lin != -1)
        ref = ref->Baixo;

    if(ref->Lin != -1)
        return 1;
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
                    insereMatriz(n, i, j);
                }
            }
            else
            {
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
                    insereMatriz(n, i, j);
                }
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
    Lin[i].Lin = i;
    Lin[i].Col = -1;
    Lin[i].Direita = &Lin[i];

    m->Direita = &Col[0];
    for(i=0;i<c-1;i++)
    {
        Col[i].Direita = &Col[i+1];
        Col[i].Lin = -1;
        Col[i].Col = i;
        Col[i].Baixo = &Col[i];
    }
    Col[i].Direita = m;
    Col[i].Lin = -1;
    Col[i].Col = i;
    Col[i].Baixo = &Col[i];

    return 1;
}

void start_allegro()
{
    allegro_init(); // inicializaçao da allegro
    install_mouse();//inicializaçao do mouse
    install_keyboard(); // inicializaçao do teclado pra usar allegro
    set_color_depth(32); // set de cor allegro
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0); // set de resoluçao da tela da allegro
    set_window_title("GAME OF LIFE");
}

void imprimeMatriz(elemento_t *m, BITMAP *buffer)
{
    int i, j;
    int x, y = 0;
    for(i = 0; i < 16; i++)
    {
        x = 0;
        for(j = 0; j < 16; j++)
        {
            if(checaElemento(m, i, j))
                rectfill(buffer, x, y, x+20, y+20, makecol(0, 0, 255));
            else
                rectfill(buffer, x, y, x+20, y+20, makecol(0, 0, 0));
            x += 20;
        }
        y += 20;
    }
}

void imprimeElemento(elemento_t * m)
{
    elemento_t * cell;
    cell = m->Baixo;
    while(cell->Lin != -1)
    {
        cell = cell->Direita;
        while(cell->Col != -1)
        {
            printf("%d\t%d\n",cell->Lin,cell->Col);
            cell = cell->Direita;
        }
        cell = cell->Baixo;
    }
}
