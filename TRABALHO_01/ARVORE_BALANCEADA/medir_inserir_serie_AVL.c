#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "serieAVL.c"

int main()
{
    double tempoTotalInsercao[30] = {0.0}; // Array para armazenar o tempo total de inserção para cada número
    LARGE_INTEGER frequencia;
    QueryPerformanceFrequency(&frequencia); // Obtenha a frequência do contador de desempenho

    // Repita o processo 30 vezes para validar o tempo de inserção
    for (int repeat = 0; repeat < 100; repeat++)
    {
        Serie *arvoreSerie = NULL; // Crie uma nova árvore para cada repetição

        // Popule um array com códigos de séries em ordem
        int codigosEmOrdem[30] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

        // Embaralhe os códigos para criar ordens diferentes
        for (int i = 0; i < 30; i++)
        {
            int temp = codigosEmOrdem[i];
            int randomIndex = rand() % 30;
            codigosEmOrdem[i] = codigosEmOrdem[randomIndex];
            codigosEmOrdem[randomIndex] = temp;
        }

        for (int i = 0; i < 30; i++)
        {
            LARGE_INTEGER inicio, fim;
            QueryPerformanceCounter(&inicio); // Início da medição
            // Insira a série com o código codigosEmOrdem[i]
            arvoreSerie = inserir_serie(arvoreSerie, codigosEmOrdem[i], "aaaaa", 10); // Substitua "Titulo" e 5 pelos valores reais
            QueryPerformanceCounter(&fim); // Fim da medição

            double tempoInsercao = (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart; // Calcula o tempo decorrido em segundos
            tempoTotalInsercao[codigosEmOrdem[i] - 1] += tempoInsercao; // Acumule o tempo de inserção para o número

            // Imprima o tempo de inserção para o número
            //printf("Tempo de insercao para %d na repeticao %d: %f segundos\n", codigosEmOrdem[i], repeat + 1, tempoInsercao);
        }

        // Limpe a árvore após cada repetição
        liberar_series(arvoreSerie);
    }

    // Calcule e imprima o tempo médio de inserção para cada número
    for (int i = 0; i < 30; i++)
    {
        double tempoMedioInsercao = tempoTotalInsercao[i] / 100; // Dividido pelo número total de repetições
        printf("Tempo medio de insercao para o numero %d: %f segundos\n", i + 1, tempoMedioInsercao);
    }
    return 0;
}