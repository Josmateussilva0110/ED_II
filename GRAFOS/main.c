#include <stdio.h>
#include <stdlib.h>
#include "grafo.c"


void menu()
{
    printf("\n");
    printf("0- sair\n1- inserir vertice\n2- inserir aresta\n3- mostrar matriz\n4- mostrar vertices\n>>> ");
}

int main()
{
    int vertices, op;
    Grafo grafo;
    int valor, inicio, fim;
    printf("quantidade de vertices: ");
    scanf("%d",&vertices);
    iniciar_grafo(&grafo, vertices);
    do
    {
        menu();
        scanf("%d",&op);
        switch (op)
        {
            case 0:
                break;

            case 1:
                printf("valor do vertice: ");
                scanf("%d",&valor);
                insere_vertice(valor, &grafo);
                break;
            
            case 2:
                printf("inicio: ");
                scanf("%d",&inicio);
                printf("fim: ");
                scanf("%d",&fim);
                insere_aresta(&grafo, fim, inicio, 1);
                break;
            
            case 3:
                imprimir_matriz(&grafo);
                break;
            
            case 4:
                imprimir_vertices(&grafo);
                break;
            default:
                break;
        }
    } while (op != 0);
    liberar_memoria(&grafo);
}