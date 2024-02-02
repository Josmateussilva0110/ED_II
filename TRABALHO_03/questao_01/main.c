#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define NUMERO_DISCOS 4    
#define NUM_PINOS 3  
#define NUM_CONFIGURACOES 81

typedef struct Vertice
{
    int localizacao[NUMERO_DISCOS];
}Vertice;



int arestas_Adjacentes(Vertice v1, Vertice v2) 
{
    int result;
    int diferencaCont = 0;
    for (int i = 0; i < NUMERO_DISCOS; i++) 
    {
        if (v1.localizacao[i] != v2.localizacao[i]) 
        {
            diferencaCont++;
            if (diferencaCont > 1) {
                result = 0;
            }
        }
    }
    if(diferencaCont == 1)
        result = 1;
    
    return result;
}

void fordMooreBellman(Vertice grafo[], int incio, int fim) 
{
    int distancia[NUM_CONFIGURACOES];
    int pais[NUM_CONFIGURACOES];
    int v;

    for (int i = 0; i < NUM_CONFIGURACOES; i++) 
    {
        distancia[i] = INT_MAX;
        pais[i] = -1;
    }

    distancia[incio] = 0;

    for (int i = 0; i < NUM_CONFIGURACOES - 1; i++) 
    {
        for (int j = 0; j < NUM_CONFIGURACOES; j++) 
        {
            if (distancia[j] != INT_MAX) 
            {
                for (int v = 0; v < NUM_CONFIGURACOES; v++) {
                    if (arestas_Adjacentes(grafo[j], grafo[v]) && distancia[j] + 1 < distancia[v]) {
                        distancia[v] = distancia[j] + 1;
                        pais[v] = j;
                    }
                }
            }
        }
    }

    if (distancia[fim] == INT_MAX)
        printf("Nao ha caminho entre as configuracoes %d e %d\n", incio, fim);

    printf("Caminho minimo entre as configuracoes %d e %d:\n", incio, fim);
    printf("%d ", fim);
    v = pais[fim];
    while (v != incio) 
    {
        printf("%d ", v);
        v = pais[v];
    }
    printf("%d\n", incio);
}

void imprimeConfiguracao(Vertice v) 
{
    for (int i = 0; i < NUMERO_DISCOS; i++) {
        printf("Disco %d: Pino %d\n", i + 1, v.localizacao[i]);
    }
    printf("\n");
}

void imprimeTodasConfiguracoes(Vertice grafo[]) 
{
    for (int i = 0; i < NUM_CONFIGURACOES; i++) 
    {
        printf("Configuracao %d:\n", i);
        imprimeConfiguracao(grafo[i]);
    }
}

int main() 
{
    int inicial, final;
    clock_t inicio, fim;
    Vertice grafo[NUM_CONFIGURACOES];
    for (int i = 0; i < NUM_CONFIGURACOES; i++) {
        int num = i;
        for (int j = 0; j < NUMERO_DISCOS; j++) {
            grafo[i].localizacao[j] = num % NUM_PINOS + 1;
            num /= NUM_PINOS;
        }
    }
    printf("digite a configuracao inicial: ");
    scanf("%d",&inicial);
    printf("digite a configuracao final: ");
    scanf("%d",&final);

    imprimeTodasConfiguracoes(grafo);
    inicio = clock();
    fordMooreBellman(grafo, inicial, final);
    fim = clock();
    printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);
}
