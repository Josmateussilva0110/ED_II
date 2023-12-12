#include <stdio.h>
#include <stdlib.h>
#include "exemplos.h"
#include "exemplos.c"


int main()
{
    Arvore *arvore = NULL;
    Arvore *min, *max, *ans;
    arvore = inserir(arvore, 2);
    arvore = inserir(arvore, 5);
    arvore = inserir(arvore, 15);
    arvore = inserir(arvore, 1);
    arvore = inserir(arvore, 3);
    exibir(arvore);
    min = tree_min(arvore);
    max = tree_max(arvore);
    ans = tree_search(arvore, 5);
    if(ans)
        printf("valor %d encontrado\n", ans->valor);
    else
        printf("valor nao encontrado\n");
    printf("menor valor = %d\n", min->valor);
    printf("maior valor = %d\n", max->valor);
    Arvore *sucessor = tree_sucessor(arvore);
    if(sucessor != NULL)
        printf("sucessor da raiz = %d\n", sucessor->valor);
    else
        printf("nao ha sucessor para a raiz\n");
}
