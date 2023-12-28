#include <stdio.h>
#include <stdlib.h>
#include "funcoes.c"



int main()
{
    Arvore_4_5 *arvore = NULL;
    int *sobe;
    int op, valor, flag = 0;;
    while(1)
    {
        Arvore_4_5 *pai = NULL;
        printf("0- sair\n1- inserir\n2- exibir\n>>> ");
        scanf("%d",&op);
        if(op == 0)
            break;
        else if(op == 1)
        {
            printf("digite o valor: ");
            scanf("%d",&valor);
            inserir(&arvore, pai, &sobe, valor, &flag);
            if(flag == 1)
                printf("insercao completa.\n");
            else
                printf("erro a inserir.\n");
        }
        else if(op == 2)
            imprimir(arvore);
    }
}