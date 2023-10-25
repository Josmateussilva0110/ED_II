#include <stdio.h>
#include <stdlib.h>


typedef struct avl
{
    int valor;
    struct avl *esq, *dir;
    int altura;
}Avl;


int maior_sub_arvore(int a, int b)
{
    return (a > b) ? a: b;
}

int altura_no(Avl *no)
{
    if(no == NULL)
        return -1;
    else
        return no->altura;
}


// fb
int fator_balanceamento(Avl *no)
{
    if(no)
        return (altura_no(no->esq) - altura_no(no->dir));
    else
        return 0;
}

// rotacao para esquerda
Avl *rotacao_esquerda(Avl *raiz)
{
    Avl *sub_r, *aux;
    sub_r = raiz->dir;
    aux = sub_r->esq;

    sub_r->esq = raiz;
    raiz->dir = aux;

    raiz->altura = maior_sub_arvore(altura_no(raiz->esq), altura_no(raiz->dir)) + 1;
    sub_r->altura = maior_sub_arvore(altura_no(sub_r->esq), altura_no(sub_r->dir)) + 1;

    return sub_r;
}

//rotacao para direita
Avl *rotacao_direita(Avl *raiz)
{
    Avl *sub_r, *aux;
    sub_r = raiz->esq;
    aux = sub_r->dir;

    sub_r->dir = raiz;
    raiz->esq = aux;

    raiz->altura = maior_sub_arvore(altura_no(raiz->esq), altura_no(raiz->dir)) +1;
    sub_r->altura = maior_sub_arvore(altura_no(sub_r->esq), altura_no(sub_r->dir)) +1;

    return sub_r;
}


//rotacao dupla
Avl *rotacao_direita_esquerda(Avl *raiz)
{
    raiz->dir = rotacao_direita(raiz->dir);
    return rotacao_esquerda(raiz);
}

//rotacao dupla
Avl *rotacao_esquerda_direita(Avl *raiz)
{
    raiz->esq = rotacao_esquerda(raiz->esq);
    return rotacao_direita(raiz);
}

// fazer o balanceamento
Avl *balancear(Avl *raiz)
{
    int fb = fator_balanceamento(raiz);
    
    // rotacao para a esquerda
    if(fb < -1 && fator_balanceamento(raiz->dir) <= 0)
        raiz = rotacao_esquerda(raiz);
    
    // rotacao para a direita
    else if(fb > 1 && fator_balanceamento(raiz->esq) >= 0)
        raiz = rotacao_direita(raiz);
    
    // rotacao dupla para a esquerda
    else if(fb > 1 && fator_balanceamento(raiz->esq) < 0)
        raiz = rotacao_esquerda_direita(raiz);
    
    // rotacao dupla a direita
    else if(fb < -1 && fator_balanceamento(raiz->dir) > 0)
        raiz = rotacao_direita_esquerda(raiz);
    return raiz;
}

Avl *criar_no(int valor)
{
    Avl *new = malloc(sizeof(Avl));
    if(new)
    {
        new->valor = valor;
        new->esq = NULL;
        new->dir = NULL;
        new->altura = 0;
    }
    else
        printf("erro ao alocar memoria.\n");
    return new;
}

Avl *inserir(Avl *raiz, int valor)
{
    if(raiz == NULL)
        return criar_no(valor);
    else
    {
        if(valor < raiz->valor)
            raiz->esq = inserir(raiz->esq, valor);
        else if(valor > raiz->valor)
            raiz->dir = inserir(raiz->dir, valor);
        else
            printf("erro valor %d ja inserido\n", valor);
    }
    // recalcular a altura dos nos 
    raiz->altura = maior_sub_arvore(altura_no(raiz->esq), altura_no(raiz->dir)) +1;
    // verificar se precisa balancear 
    raiz = balancear(raiz);
    return raiz;
}
