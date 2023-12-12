#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.c"


int main()
{
    Artista *arvore = NULL;
    char nome[50], estilo[50];
    int numero_album;
    printf("Nome do artista: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Estilo musical: ");
    fgets(estilo, sizeof(estilo), stdin);
    estilo[strcspn(estilo, "\n")] = '\0';
    printf("Numero de albuns: ");
    scanf("%d", &numero_album);
    inserir_artista(&arvore, NULL, nome, estilo, numero_album);
    exibir_arvore(&arvore);
}