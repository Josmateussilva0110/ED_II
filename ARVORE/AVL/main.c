#include <stdio.h>
#include <stdlib.h>
#include "inserir.c"


int main()
{
    Avl *arvore = NULL;
    arvore = inserir(arvore, 3);
    arvore = inserir(arvore, 1);
    arvore = inserir(arvore, 5);
    arvore = inserir(arvore, 10);
}