#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Artista 
{
    char nome[50];
    char estilo_musical[50];
    int num_albuns;
    struct Artista *esq, *dir;  // Ponteiros para a árvore vermelha-preta
    int cor;  // 0 para preto, 1 para vermelho
    struct Artista *pai;
} Artista;


int eh_nulo_raiz(Artista **raiz)
{
    return (*raiz == NULL);
}

int eh_nulo_dir(Artista **raiz)
{
    return ((*raiz)->dir == NULL);
}

int eh_nulo_esq(Artista **raiz)
{
    return ((*raiz)->esq == NULL);
}


void rotacao_esquerda(Artista **raiz) 
{
    Artista *aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = 1;
    (*raiz) = aux;
}

void rotacao_direita(Artista **raiz) 
{
    Artista *aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = 1;
    (*raiz) = aux;
}

void trocar_cor(Artista **raiz)
{
    if((*raiz)->pai != NULL)
        (*raiz)->cor = 1;
    (*raiz)->esq->cor = 0;
    (*raiz)->dir->cor = 0;
}

void balancear(Artista **raiz)
{
    if(!eh_nulo_dir(raiz) && (*raiz)->dir->cor == 1)
        rotacao_esquerda(raiz);
    if(!eh_nulo_esq(raiz) && (*raiz)->esq->cor == 1 && (*raiz)->esq->esq != NULL && (*raiz)->esq->esq->cor == 1)
        rotacao_direita(raiz);
    if(!eh_nulo_esq(raiz) && (*raiz)->esq->cor == 1 && !eh_nulo_dir(raiz) && (*raiz)->dir->cor == 1)
        trocar_cor(raiz);
}

// Função para criar um novo nó de artista
Artista *criar_artista(char *nome_artista, char *estilo_musical, int numero_albuns) 
{
    Artista *novo_artista = (Artista *)malloc(sizeof(Artista));
    strcpy(novo_artista->nome, nome_artista);
    strcpy(novo_artista->estilo_musical, estilo_musical);
    novo_artista->num_albuns = numero_albuns;
    novo_artista->esq = NULL;
    novo_artista->dir = NULL;
    novo_artista->pai = NULL;
    novo_artista->cor = 1;
    return novo_artista;
}


void inserir_artista(Artista **raiz, Artista *pai, char *nome, char *estilo, int num_albuns) 
{
    if (*raiz == NULL) 
    {
        *raiz = criar_artista(nome, estilo, num_albuns);
        (*raiz)->pai = pai;

        if (pai == NULL)
            (*raiz)->cor = 0;
    }  
    else 
    {
        if (strcmp(nome, (*raiz)->nome) < 0)
            inserir_artista(&((*raiz)->esq), *raiz, nome, estilo, num_albuns);
        else if (strcmp(nome, (*raiz)->nome) > 0)
            inserir_artista(&((*raiz)->dir), *raiz, nome, estilo, num_albuns);
    }
    balancear(raiz); 
}

// exibe em ordem 
void exibir_arvore(Artista **raiz)
{
    if (!eh_nulo_raiz(raiz))
    {
        exibir_arvore(&(*raiz)->esq);
        printf("nome: %s\n", (*raiz)->nome);
        printf("estilo: %s\n", (*raiz)->estilo_musical);
        printf("numero albuns: %d\n", (*raiz)->num_albuns);
        printf("cor: %d\n", (*raiz)->cor);
        exibir_arvore(&(*raiz)->dir);
    }
}