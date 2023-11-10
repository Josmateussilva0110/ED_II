#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temporadasAVL.c"

typedef struct Serie 
{
    int codigo;
    char titulo[50];
    int numTemporadas;
    Temporada *temporadas; // Árvore de temporadas
    struct Serie *esq, *dir;
    int altura_serie1;
} Serie;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Serie *criar_Serie(int codigo, char *titulo, int numTemporadas) 
{
    Serie *new;
    new = (Serie*)malloc(sizeof(Serie));
    new->codigo = codigo;
    strcpy(new->titulo, titulo);
    new->numTemporadas = numTemporadas;
    new->temporadas = NULL;
    new->esq = NULL;
    new->dir = NULL;
    new->altura_serie1 = 0;
    return new;
}

int maior_serie(int a, int b) {
    int maior;
    if (a > b) {
        maior = a;
    } else {
        maior = b; 
    }
    
    return maior;
}


int altura_serie(Serie *serie) {
    int altura_series = -1;

    if (serie != NULL) {
        altura_series = serie->altura_serie1;
    }

    return altura_series;
}

int fatorBalanceamento_serie(Serie *serie) {
    int fator = 0;

    if (serie) {
        int alt_esq_serie = altura_serie(serie->esq);
        int alt_dir_serie = altura_serie(serie->dir);
        fator = alt_esq_serie - alt_dir_serie;
    }

    return fator; 
}


Serie *rotacaoEsq_serie(Serie *serie) {
    Serie *y,*f;
    y = serie->dir;
    f = y->esq;

    y->esq = serie;
    serie->dir = f;

    serie->altura_serie1 = maior_serie(altura_serie(serie->esq),altura_serie(serie->dir)) + 1;
    y->altura_serie1 = maior_serie(altura_serie(y->esq),altura_serie(y->dir)) + 1;

    return y;
}

Serie *rotacaoDir_serie(Serie *serie)
{
    Serie *y,*f;

    y = serie->esq;
    f = y->dir;

    y->dir = serie;
    serie->esq = f;

    serie->altura_serie1 = maior_serie(altura_serie(serie->esq),altura_serie(serie->dir)) + 1;
    y->altura_serie1 = maior_serie(altura_serie(y->esq),altura_serie(y->dir)) + 1;

    return y;
}

Serie *rotacaoEsqDir_serie(Serie *serie) {
    serie->esq = rotacaoEsq_serie(serie->esq);
    return rotacaoDir_serie(serie);
}

Serie *rotacaoDirEsq_serie(Serie *serie) {
    serie->dir = rotacaoDir_serie(serie->dir);
    return rotacaoEsq_serie(serie);
}

Serie *balancear_serie(Serie *raiz) {
    int fb = fatorBalanceamento_serie(raiz);

    if (fb < -1 && fatorBalanceamento_serie(raiz->dir) <= 0)
    {
        raiz = rotacaoEsq_serie(raiz);
    }else if (fb > 1 && fatorBalanceamento_serie(raiz->esq) >= 0)
    {
        raiz = rotacaoDir_serie(raiz);
    }
    else if (fb > 1 && fatorBalanceamento_serie(raiz->esq)<0)
    {
        raiz = rotacaoEsqDir_serie(raiz);
    }
    else if (fb < 1 && fatorBalanceamento_serie(raiz->dir)>0)
    {
        raiz = rotacaoDirEsq_serie(raiz);
    }
    return raiz;
}

Serie *inserir_serie(Serie *raiz, int codigo, char *titulo, int numTemporadas) {
    Serie *novaRaiz = raiz;

    if (raiz == NULL) 
        novaRaiz = criar_Serie(codigo, titulo, numTemporadas);
    else 
    {
        if (codigo < raiz->codigo) 
            raiz->esq = inserir_serie(raiz->esq, codigo, titulo, numTemporadas);
        else if (codigo > raiz->codigo) 
            raiz->dir = inserir_serie(raiz->dir, codigo, titulo, numTemporadas);
        else 
            printf("Insercao nao realizada.\n");
        
        
        raiz->altura_serie1 = maior_serie(altura_serie(raiz->esq), altura_serie(raiz->dir)) + 1;
        novaRaiz = balancear_serie(raiz);
    }
    
    return novaRaiz;
}


void exibir_Serie(Serie *serie) 
{
    printf("Entrou aqui na funcao de exibir_serie\n");
    if (serie != NULL) 
    {
        exibir_Serie(serie->esq);
        printf("Codigo: %d\n", serie->codigo);
        printf("Titulo: %s\n", serie->titulo);
        printf("Numero de temporadas: %d\n", serie->numTemporadas);
        exibir_Serie(serie->dir);
    }
}

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


void cadastrar_temporadas(Serie *series, int codigo, int numeroTemporada, int numEpisodios, int ano, const char *titulo) 
{
    Serie *aux = achar_serie(series, codigo);
    if (aux)
        aux->temporadas = inserir_temporada(aux->temporadas, numeroTemporada, numEpisodios, ano, titulo, codigo);
    else
        printf("Serie nao existe.\n");
}

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


// funcao para encontrar os artistas das temporadas
void imprimir_artistas_do_personagem(Serie *serie, int codigoSerie, const char *nomePersonagem) 
{
    Serie *encontrada = achar_serie(serie, codigoSerie); // procura a serie
    if (encontrada != NULL) 
    {
        int qnt_temp = contar_temporadas(encontrada->temporadas, codigoSerie); //conta a quantidade de temporadas
        buscar_e_imprimir_artistas(encontrada->temporadas, nomePersonagem, qnt_temp); // percorre a arvore de temporadas lincagem com temporadas.c
    } 
    else 
        printf("Serie nao encontrada.\n");
    printf("\n");
}

void liberar_series(Serie *serie) 
{
    if (serie != NULL) {
        liberar_series(serie->esq);
        liberar_series(serie->dir);
        liberar_temporadas(serie->temporadas);
        free(serie);
    }
}