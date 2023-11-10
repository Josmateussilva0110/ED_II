#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "serieAVL.c" 
int main()
{
    Serie *arvoreSerie = NULL;
    double tempoTotalBusca = 0.0;
    clock_t inicio_clock, fim_clock;

    for (int codigoSerie = 1; codigoSerie <= 30; codigoSerie++) 
    {
        // Insira a série
        arvoreSerie = inserir_serie(arvoreSerie, codigoSerie, "Nome", 10);
        printf("Inserindo Serie com codigo %d...\n", codigoSerie);

        for (int i = 0; i < 30; i++)    
        {
            // Cadastre temporadas na série
            cadastrar_temporadas(arvoreSerie, codigoSerie, i, 5, 2023, "Nome");
            printf("Inserindo Temporada %d na Serie %d...\n", i, codigoSerie);
        }
    }

    for (int codigoSerie = 1; codigoSerie <= 30; codigoSerie++) 
    {
        double tempoSerie = 0.0;
        for (int numeroBuscado = 1; numeroBuscado <= 30; numeroBuscado++) {
            inicio_clock = clock();

            // Realize a busca pelo número atual em todas as temporadas da série
            printf("Realizando busca pelo numero %d em todas as temporadas da Serie %d...\n", numeroBuscado, codigoSerie);
            for (int temporada = 0; temporada < 30; temporada++) {
                Temporada *temporadaEncontrada = achar_temporada(arvoreSerie->temporadas, codigoSerie);
                if (temporadaEncontrada) {
                    //printf("achou\n");
                }
            }

            fim_clock = clock();

            double tempoBusca_clock = (double)(fim_clock - inicio_clock) / CLOCKS_PER_SEC;

            tempoSerie += tempoBusca_clock;
        }
        double tempoMedioSerie_clock = tempoSerie / 30;
        printf("Tempo medio de busca na Serie %d: %f segundos (clock)\n", codigoSerie, tempoMedioSerie_clock);
        tempoTotalBusca += tempoMedioSerie_clock;
    }

    // Limpe a árvore após a busca
    liberar_series(arvoreSerie);

    double tempoMedioTotal_clock = tempoTotalBusca / 30;

    printf("Tempo medio de busca em todas as series: %f segundos (clock)\n", tempoMedioTotal_clock);

    return 0;
}