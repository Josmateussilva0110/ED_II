#include "exemplos.h"
#include <stdlib.h>
#include <stdio.h>

struct arvore
{
    Arvore *direita;
    Arvore *esquerda;
    int valor;
    Arvore *pai;
};


Arvore *criar_no(int valor)
{
    Arvore *new = (Arvore*) malloc(sizeof(Arvore));
    if(new != NULL)
    {
        new->valor = valor;
        new->esquerda = NULL;
        new->direita = NULL;
    }
    return new;
}

Arvore *inserir(Arvore *no, int valor)
{
    if(no == NULL)
        return criar_no(valor);
    else if(valor < no->valor)
        no->esquerda = inserir(no->esquerda, valor);
    else
        no->direita = inserir(no->direita, valor);
    return no;
}

void exibir(Arvore *no)
{
    if(no != NULL)
    {
        exibir(no->esquerda);
        printf("%d\n",no->valor);
        exibir(no->direita);
    }
}

Arvore *tree_min(Arvore *no)
{
    while(no->esquerda != NULL)
        no = no->esquerda;
    return no;
}

Arvore *tree_max(Arvore *no)
{
    while(no->direita != NULL)
        no = no->direita;
    return no;
}

Arvore *tree_search(Arvore *x, int k)
{
    if(x == NULL || k == x->valor)
        return x;
    if(k < x->valor)
    {
        return tree_search(x->esquerda, k);
    }
    else
    {
        return tree_search(x->direita, k);
    }
}

Arvore *tree_sucessor(Arvore *x)
{
    if(x->direita != NULL)
        return tree_min(x->direita);
    Arvore *y = NULL;
    while(x != NULL && x == x->pai->direita)
    {
        y = x;
        x = x->pai;
    }
    return y;
}
