#include <stdio.h>
#include <stdlib.h>

typedef struct Grafo
{
    int numero_vertice;
    int max_vertice;
    int *vertices;
    int **matriz_adj;
}Grafo;


void iniciar_grafo(Grafo *grafo, int max_vertice)
{
    grafo->numero_vertice = 0;
    grafo->max_vertice = max_vertice;
    grafo->vertices = (int*)malloc(max_vertice * sizeof(int));

    grafo->matriz_adj = (int**)malloc(max_vertice * sizeof(int*));
    for (int i = 0; i < max_vertice; i++)
        grafo->matriz_adj[i] = (int*)malloc(max_vertice * sizeof(int));

    for (int i = 0; i < max_vertice; i++)
    {
        for (int j = 0; j < max_vertice; j++)
        {
            grafo->matriz_adj[i][j] = -1;
        }
    }
}

void liberar_memoria(Grafo *grafo) 
{
    free(grafo->vertices);

    for (int i = 0; i < grafo->max_vertice; i++) 
        free(grafo->matriz_adj[i]);

    free(grafo->matriz_adj);
}


int obter_indice(int valor, Grafo *grafo, int numero_vertice)
{
    int retorno = -1;
    for (int i = 0; i < numero_vertice; i++)
    {
        if (grafo->vertices[i] == valor)
        {
            retorno = i;
            break;
        }
    }
    return retorno;
}

int esta_cheio(Grafo *grafo)
{
    return (grafo->numero_vertice == grafo->max_vertice);
}


void insere_vertice(int valor, Grafo *grafo)
{
    int indice = grafo->numero_vertice;
    if (esta_cheio(grafo))
        printf("O numero maximo de vertices foi alcancado!\n");
    else
    {
        grafo->vertices[indice] = valor;
        grafo->numero_vertice++;
    }
}


void insere_aresta(Grafo *grafo, int no_saida, int no_entrada, int peso)
{
    int linha = obter_indice(no_saida, grafo, grafo->numero_vertice);
    int coluna = obter_indice(no_entrada, grafo, grafo->numero_vertice);

    grafo->matriz_adj[linha][coluna] = peso;

    grafo->matriz_adj[coluna][linha] = peso; 
}


/*int obter_peso(Grafo *grafo, int no_saida, int no_entrada)
{
    int linha = obter_indice(no_saida, grafo, grafo->numero_vertice);
    int coluna = obter_indice(no_entrada, grafo, grafo->numero_vertice);
    if(linha != -1 && coluna != -1)
        return grafo->matriz_adj[linha][coluna];        
}*/


int obter_grau(Grafo *grafo, int valor)
{
    int linha = obter_indice(valor, grafo, grafo->numero_vertice);
    int grau = 0;
    if(linha != -1)
    {
        for (int i=0; i<grafo->max_vertice; i++)
        {
            if (grafo->matriz_adj[linha][i] != -1)
                grau++;
        }
    }
    return grau;
}

void imprimir_matriz(Grafo *grafo)
{
    for (int i=0 ; i < grafo->max_vertice; i++)
    {
        for (int j=0 ; j < grafo->max_vertice; j++)
        {
            printf("%d ", grafo->matriz_adj[i][j]);
        }
        printf("\n");
    }
}


void imprimir_vertices(Grafo *grafo)
{
    for (int i = 0; i < grafo->numero_vertice; i++)
        printf("%d - %d\n", i, grafo->vertices[i]);
}

