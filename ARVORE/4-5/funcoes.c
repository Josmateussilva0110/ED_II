#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Arvore_4_5
{
	int info_1, info_2, info_3, info_4;
	struct Arvore_4_5 *esq, *cen_esq, *centro, *cen_dir, *dir;
	int n_info;

}Arvore_4_5;


int folha(Arvore_4_5 *no)
{
    int flag = 0;
    if(no->esq == NULL)
        flag = 1;
    return flag;
}


Arvore_4_5 *criaNo(int valor, Arvore_4_5 *esq, Arvore_4_5 *cen_esq)
{
    Arvore_4_5 *no;
    no = (Arvore_4_5 *)malloc(sizeof(Arvore_4_5));
    no->info_1 = valor;
    no->n_info = 1;
    no->esq = esq;
    no->cen_esq = cen_esq;
    no->centro = NULL;
    no->cen_dir = NULL;
    no->dir = NULL;
    return no;
}


void adicionaNo(Arvore_4_5 **No, int valor, Arvore_4_5 *filho)
{

    if((*No)->n_info == 1)
    {
        if(valor > (*No)->info_1)
        {
            (*No)->info_2 = valor;
            (*No)->centro = filho;
        }
        else
        {
            (*No)->info_2 = (*No)->info_1;
            (*No)->info_1 = valor;

            (*No)->centro = (*No)->cen_esq;
            (*No)->cen_esq = filho;

        }
        (*No)->n_info = 2;

    }
    else if((*No)->n_info == 2)
    {
        if(valor > (*No)->info_2)
        {
            (*No)->info_3 = valor;
            (*No)->cen_dir = filho;
        }
        else if(valor > (*No)->info_1 && valor < (*No)->info_2)
        {
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = valor;

            (*No)->cen_dir = (*No)->centro;
            (*No)->centro = filho;

        }
        else
        {
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = (*No)->info_1;
            (*No)->info_1 = valor;

            (*No)->cen_dir = (*No)->centro;
            (*No)->centro = (*No)->cen_esq;
            (*No)->cen_esq = filho;

        }
        (*No)->n_info = 3;

    }
    else
    {
        if(valor > (*No)->info_3)
        {
            (*No)->info_4 = valor;
            (*No)->dir = filho;

        }else if(valor > (*No)->info_2 && valor < (*No)->info_3)
        {
            (*No)->info_4 = (*No)->info_3;
            (*No)->info_3 = valor;

            (*No)->dir = (*No)->cen_dir;
            (*No)->cen_dir = filho;

        }
        else if (valor > (*No)->info_1 && valor < (*No)->info_2)
        {
            (*No)->info_4 = (*No)->info_3;
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = valor;

            (*No)->dir = (*No)->cen_dir;
            (*No)->cen_dir = (*No)->centro;
            (*No)->centro = filho;

        }
        else
        {
            (*No)->info_4 = (*No)->info_3;
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = (*No)->info_1;
            (*No)->info_1 = valor;

            (*No)->dir = (*No)->cen_dir;
            (*No)->cen_dir = (*No)->centro;
            (*No)->centro = (*No)->cen_esq;
            (*No)->cen_esq = filho;
        }
        (*No)->n_info = 4; 
    }
}


Arvore_4_5 *quebraNo(Arvore_4_5 **raiz, int valor, int **sobe, Arvore_4_5 *filho) 
{
    Arvore_4_5 *maiorNo;
    if (valor > (*raiz)->info_4) 
    {
        *sobe = &((*raiz)->info_3);

        maiorNo = criaNo((*raiz)->info_4, (*raiz)->cen_dir, (*raiz)->dir);
        
        maiorNo->info_2 = valor;

        maiorNo->centro = filho;

        maiorNo->n_info = 2;
    } 
    else if (valor > (*raiz)->info_3) 
    {
        *sobe = &((*raiz)->info_3);

        maiorNo = criaNo(valor, (*raiz)->cen_dir, filho);
        
        maiorNo->info_2 = (*raiz)->info_4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->n_info = 2;
    } 
    else if (valor > (*raiz)->info_2) 
    {
        *sobe = &((*raiz)->info_3);

        maiorNo = criaNo((*raiz)->info_4, (*raiz)->cen_dir, (*raiz)->dir);
        
        maiorNo->info_2 = valor;

        maiorNo->centro = filho;

        maiorNo->n_info = 2;

        (*raiz)->info_3 = (*raiz)->info_2;
        (*raiz)->info_2 = valor;

        (*raiz)->cen_dir = (*raiz)->centro;
        (*raiz)->centro = filho;
    } 
    else if (valor > (*raiz)->info_1) 
    {
        *sobe = &((*raiz)->info_2);

        maiorNo = criaNo((*raiz)->info_3, (*raiz)->centro, (*raiz)->cen_dir);
        
        maiorNo->info_2 = (*raiz)->info_4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->n_info = 2;

        (*raiz)->info_2 = valor;
        (*raiz)->centro = filho;
    } 
    else 
    {
        *sobe = &((*raiz)->info_2);

        maiorNo = criaNo((*raiz)->info_3, (*raiz)->centro, (*raiz)->cen_dir);
        
        maiorNo->info_2 = (*raiz)->info_4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->n_info = 2;

        (*raiz)->info_2 = (*raiz)->info_1;
        (*raiz)->centro = (*raiz)->cen_esq;
        
        (*raiz)->info_1 = valor;
        (*raiz)->cen_esq = filho;
    }

    (*raiz)->n_info = 2;
    (*raiz)->cen_dir = NULL;
    (*raiz)->dir = NULL;

    return maiorNo;
}

Arvore_4_5 *inserir(Arvore_4_5 **raiz, Arvore_4_5 *pai, int **sobe, int valor, int *flag)
{
    Arvore_4_5 *maiorNO;
    maiorNO = NULL;

    if(*raiz == NULL)
        *raiz = criaNo(valor, NULL, NULL);
    else
    {
        if(folha(*raiz))
        {
            if((*raiz)->n_info < 4)
            {
                adicionaNo(raiz, valor, NULL);
                maiorNO = NULL;
                *flag = 1;
            }
            else
            {
                maiorNO = quebraNo(raiz, valor, sobe, NULL);

                if(pai == NULL)
                {
                    *raiz = criaNo(**sobe, *raiz, maiorNO);
                    maiorNO = NULL;
                }
            }
        }
        else
        {
            if(valor < (*raiz)->info_1)
                maiorNO = inserir(&((*raiz)->esq), *raiz, sobe, valor, flag);

            else if((*raiz)->n_info == 1 || ((*raiz)->n_info <= 4 && valor < (*raiz)->info_2))
                maiorNO = inserir(&((*raiz)->cen_esq), *raiz, sobe, valor, flag);

            else if(((*raiz)->n_info == 2)  || ((*raiz)->n_info <= 4 && valor < (*raiz)->info_3))
                maiorNO = inserir(&((*raiz)->centro), *raiz,  sobe, valor, flag);

            else if(((*raiz)->n_info == 3) || ((*raiz)->n_info == 4 && valor < (*raiz)->info_4))
                maiorNO = inserir(&((*raiz)->cen_dir), *raiz, sobe, valor, flag);

            else 
                maiorNO = inserir(&((*raiz)->dir), *raiz, sobe, valor, flag);

            if(maiorNO)
            {
                if((*raiz)->n_info < 4)
                {
                    adicionaNo(raiz, **sobe, maiorNO);
                    maiorNO = NULL;
                    *flag = 1;
                }
                else
                {
                    maiorNO = quebraNo(raiz, **sobe, sobe, maiorNO);

                    if(pai == NULL){
                        *raiz = criaNo(**sobe, *raiz, maiorNO);
                        maiorNO = NULL;
                    }
                }
            }
        }
    }
    return maiorNO;
}

void imprimir(Arvore_4_5 *Raiz)
{
    if (Raiz != NULL)
    {
        imprimir(Raiz->esq);

        if (Raiz->n_info >= 1)
            printf("%d\n", Raiz->info_1);

        imprimir(Raiz->cen_esq);

        if (Raiz->n_info >= 2)
            printf("%d\n", Raiz->info_2);

        imprimir(Raiz->centro);

        if (Raiz->n_info >= 3)
            printf("%d\n", Raiz->info_3);

        if (Raiz->n_info == 4)
            printf("%d\n", Raiz->info_4);

        imprimir(Raiz->cen_dir);
        imprimir(Raiz->dir);
    }
}
