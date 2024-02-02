#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 1000

typedef struct {
    int vertice;
    double confiabilidade;
} Aresta;

typedef struct {
    Aresta *arestas;
    int num_arestas;
} Grafo;

typedef struct {
    double confiabilidade;
    int vertice;
} Lista_prioridade;


// Estrutura para armazenar os predecessores
typedef struct {
    int vertice;
    int predecessor;
} Caminho;

void exibirCaminho(const Caminho *predecessores, int inicio, int destino) {
    printf("Caminho: ");
    while (destino != inicio) {
        printf("%d ", destino);
        destino = predecessores[destino].predecessor;
    }
    printf("%d", inicio);
}


void dijkstra(const Grafo *grafo, int origem, int destino, int num_vertices) {
    bool *visitados = (bool *)malloc(num_vertices * sizeof(bool));
    bool caminhoEncontrado = false;
    double *confiabilidade = (double *)malloc(num_vertices * sizeof(double));
    Caminho *predecessores = (Caminho *)malloc(num_vertices * sizeof(Caminho));
    for (int i = 0; i < num_vertices; ++i) {
        visitados[i] = false;
        confiabilidade[i] = 0.0;
        predecessores[i].vertice = -1;
    }
    confiabilidade[origem] = 1.0;

    Lista_prioridade *fp = (Lista_prioridade *)malloc(num_vertices * sizeof(Lista_prioridade));
    int tamanho_fp = 0;
    fp[tamanho_fp++] = (Lista_prioridade){1.0, origem};

    while (tamanho_fp > 0) {
        Lista_prioridade min_confiab = fp[0];
        int min_idx = 0;
        for (int i = 1; i < tamanho_fp; ++i) {
            if (fp[i].confiabilidade > min_confiab.confiabilidade) {
                min_confiab = fp[i];
                min_idx = i;
            }
        }

        fp[min_idx] = fp[--tamanho_fp];
        visitados[min_confiab.vertice] = true;

        if (min_confiab.vertice == destino) 
        {
            caminhoEncontrado = true;
            double confiabilidadePercentual = min_confiab.confiabilidade * 100.0;
            printf("O caminho mais confiavel entre %d e %d tem confiabilidade de %.2lf%%\n",
                   origem, destino, confiabilidadePercentual);
            exibirCaminho(predecessores, origem, destino);
            free(visitados);
            free(confiabilidade);
            free(fp);
            free(predecessores);
            // return;
        }  
        for (int i = 0; i < grafo[min_confiab.vertice].num_arestas; ++i) {
            Aresta aresta = grafo[min_confiab.vertice].arestas[i];
            if (!visitados[aresta.vertice]) {
                double nova_confiab = min_confiab.confiabilidade * aresta.confiabilidade;
                if (nova_confiab > confiabilidade[aresta.vertice]) {
                    confiabilidade[aresta.vertice] = nova_confiab;
                    predecessores[aresta.vertice].predecessor = min_confiab.vertice;
                    fp[tamanho_fp++] = (Lista_prioridade){nova_confiab, aresta.vertice};
                }
            }
        }
    }

    if (!caminhoEncontrado) {
        printf("Nao ha caminho confiavel entre %d e %d\n", origem, destino);
    }
    free(visitados);
    free(confiabilidade);
    free(fp);
    free(predecessores);
}


int main() {
    FILE *arquivo = fopen("../grafo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int num_vertices, num_arestas;
    fscanf(arquivo, "%d %d", &num_vertices, &num_arestas);

    Grafo *grafo = (Grafo *)malloc(num_vertices * sizeof(Grafo));
    for (int i = 0; i < num_vertices; ++i) {
        grafo[i].num_arestas = 0;
        grafo[i].arestas = NULL;
    }

    for (int i = 0; i < num_arestas; ++i) {
        int u, v;
        double confiabilidade;
        fscanf(arquivo, "%d %d %lf", &u, &v, &confiabilidade);
        
        grafo[u].arestas = (Aresta *)realloc(grafo[u].arestas, (grafo[u].num_arestas + 1) * sizeof(Aresta));
        grafo[u].arestas[grafo[u].num_arestas++] = (Aresta){v, confiabilidade};
    }

    int origem, destino;
    printf("Digite o vertice de origem e o vertice de destino: ");
    scanf("%d %d", &origem, &destino);

    dijkstra(grafo, origem, destino, num_vertices);

    for (int i = 0; i < num_vertices; ++i) {
        free(grafo[i].arestas);
    }
    free(grafo);

    fclose(arquivo);

    return 0;   
}