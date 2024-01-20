#include "musica.h"
#include "musica.c"
#include "artista.h"
#include "album.h"
#include "artista.c"
#include "album.c"
#include <stdio.h>
#include <stdlib.h>

// Função para realizar 30 inserções seguidas de uma busca
void experimento_insercao_e_busca(Artista **raiz, char *nomes_artistas[], int num_artistas) {
    clock_t inicio, fim;
    double tempo_total_busca = 0.0;
    srand(time(NULL));

    // Criar 30 artistas aleatórios e inseri-los na árvore
    for (int i = 0; i < num_artistas; i++) {
        char nome[50];
        sprintf(nome, "Artista%d", i);

        char estilo[20];
        sprintf(estilo, "Estilo%d", rand() % 5);

        int num_albuns = rand() % 10 + 1;

        Info infoSobe;
        int flag = 0;

        inserir_Artista(raiz, nome, estilo, num_albuns, NULL, &infoSobe, &flag);
    }

    // Buscas por todos os artistas inseridos
    for (int i = 0; i < num_artistas; i++) {
        int posi; // Declare a variável posi aqui
        inicio = clock();

        // Realiza a busca
        Artista *encontrado = achar_artista(*raiz, nomes_artistas[i], &posi);

        fim = clock();
        double tempo_gasto_busca = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000000.0; // Converte para microssegundos
        tempo_total_busca += tempo_gasto_busca;

        printf("Busca - Artista: %s\n", nomes_artistas[i]);

        if (encontrado != NULL) {
            printf("  Artista encontrado. Tempo gasto: %.2f microssegundos\n", tempo_gasto_busca);
        } else {
            printf("  Artista nao encontrado. Tempo gasto: %.2f microssegundos\n", tempo_gasto_busca);
        }
    }

    printf("Tempo medio gasto para todas as buscas: %.2f microssegundos\n", (tempo_total_busca / num_artistas));
}


int main() 
{
    Artista *arvore = NULL;

    char *nomes_artistas[30];

    // Gerar nomes de artistas automaticamente
    for (int i = 0; i < 30; i++) {
        char nome_artista[20];
        sprintf(nome_artista, "Artista%d", i + 1);
        nomes_artistas[i] = strdup(nome_artista);
    }

    // Realiza o experimento de inserção e busca
    experimento_insercao_e_busca(&arvore, nomes_artistas, 30);

    // Liberar memória alocada para os nomes de artistas
    for (int i = 0; i < 30; i++) {
        free((void *)nomes_artistas[i]);
    }

    return 0;
}
