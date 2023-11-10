#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temporadas.c"


// Estrutura para uma série
typedef struct Serie 
{
    int codigo;
    char titulo[50];
    int numTemporadas;
    Temporada *temporadas; // Árvore de temporadas
    struct Serie *esq, *dir;
} Serie;


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Serie *criar_Serie(int codigo, char *titulo, int numTemporadas) 
{
    Serie *new = (Serie*)malloc(sizeof(Serie));
    new->codigo = codigo;
    strcpy(new->titulo, titulo);
    new->numTemporadas = numTemporadas;
    new->temporadas = NULL;
    new->esq = NULL;
    new->dir = NULL;
    return new;
}

//Dita a direção
Serie *inserir_serie(Serie *raiz, int codigo,char *titulo , int numTemporadas)
{
    Serie *novaRaiz = raiz;
    if (raiz == NULL)
        novaRaiz= criar_Serie(codigo, titulo, numTemporadas);
    else
    {
        if (codigo < raiz->codigo)
            raiz->esq = inserir_serie(raiz->esq,codigo,titulo,numTemporadas);
        else if (codigo > raiz->codigo)
            raiz->dir = inserir_serie(raiz->dir,codigo,titulo,numTemporadas);
        else
            printf("insercao nao realizada\n");
    }
    return novaRaiz;
}

//Exibir a serie a partir de seu codigo
void exibir_Serie(Serie *serie)
{
    if (serie != NULL) 
    {
        exibir_Serie(serie->esq);
        printf("Codigo: %d\n", serie->codigo);
        printf("Titulo: %s\n", serie->titulo);
        printf("Numero de temporadas: %d\n", serie->numTemporadas);
        exibir_Serie(serie->dir);
    }
}


// faz uma busca na arvore de serie e retorna o no caso encontre
Serie *achar_serie(Serie *serie, int codigo) 
{
    Serie *serieEncontrada = NULL;

    if (serie != NULL) 
    {
        if (codigo == serie->codigo) 
            serieEncontrada = serie;
        else if (codigo < serie->codigo) 
            serieEncontrada = achar_serie(serie->esq, codigo);
        else
            serieEncontrada = achar_serie(serie->dir, codigo);
    }

    return serieEncontrada;
}

// cadastra uma temporada no campo temporada da struct
void cadastrar_temporadas(Serie *temporadas, int codigo,int numeroTemporada,int numEpisodios,int ano,const char *titulo)
{
    Serie *aux = achar_serie(temporadas, codigo);
    if(aux)
        aux->temporadas = inserir_temporada(aux->temporadas,numeroTemporada,numEpisodios,ano,titulo, codigo); // lincagem
    else
        printf("serie nao existe.\n");
}


// exibe uma temporada a partir do codigo da serie
void mostrar_temporadas(Serie *serie, int codigo) 
{
    printf("\n");
    printf("Dados da Serie: \n");
    printf("Codigo da serie: %d\n", codigo);
    printf("Nome da serie: %s\n", serie->titulo);
    printf("Numero de temporadas: %d\n", serie->numTemporadas);
    printf("\nDados das temporadas da Serie: \n");
    exibir_Temp(serie->temporadas);
    printf("--------------------------------\n");
    printf("\n");
}

// funçao para procurar o nome do artista que interpreta determinado personagem
void imprimir_artistas_do_personagem(Serie *serie, int codigoSerie, const char *nomePersonagem) 
{
    Serie *encontrada = achar_serie(serie, codigoSerie); // procura a serie
    if (encontrada != NULL) // se achou
    {
        int qnt_temp = contar_temporadas(encontrada->temporadas, codigoSerie);
        buscar_e_imprimir_artistas(encontrada->temporadas, nomePersonagem, qnt_temp); // percorre a arvore de temporadas lincagem com temporadas.c
    } 
    else 
        printf("Serie nao encontrada.\n");
    printf("\n");
}


// libera memoria
void liberar_series(Serie *serie) 
{
    if (serie != NULL) {
        liberar_series(serie->esq);
        liberar_series(serie->dir);
        liberar_temporadas(serie->temporadas);
        free(serie);
    }
}