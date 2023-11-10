#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "participantes.c"


// Estrutura para uma temporada
typedef struct Temporada 
{
    int numeroTemporada;
    char titulo[50];
    int numEpisodios;
    int ano, codigo_serie;
    Participante *participantes; // Lista de participantes
    struct Temporada *esq, *dir;
} Temporada;

// faz o mesmo que na de series
Temporada *criar_temporada(int numeroTemporada, const char *titulo, int numEpisodios, int ano, int codi) 
{
    Temporada *novaTemporada = (Temporada *)malloc(sizeof(Temporada));
    if (novaTemporada != NULL) 
    {
        novaTemporada->numeroTemporada = numeroTemporada;
        strcpy(novaTemporada->titulo, titulo);
        novaTemporada->numEpisodios = numEpisodios;
        novaTemporada->ano = ano;
        novaTemporada->codigo_serie = codi;
        novaTemporada->participantes = NULL; // Inicialize a lista de participantes como vazia
        novaTemporada->esq = NULL;
        novaTemporada->dir = NULL;
    }
    return novaTemporada;
}

//Dita a direção da temporada
Temporada *inserir_temporada(Temporada *raizTemp, int numeroTemporada, int numEpisodios, int ano, const char *titulo, int codigo_serie) 
{
    Temporada *novaTemp = raizTemp;
    if (raizTemp == NULL) 
        novaTemp = criar_temporada(numeroTemporada, titulo, numEpisodios, ano, codigo_serie);
    else
    {
        if (numeroTemporada < raizTemp->numeroTemporada) 
            raizTemp->esq = inserir_temporada(raizTemp->esq, numeroTemporada, numEpisodios, ano, titulo, codigo_serie);
        else if (numeroTemporada > raizTemp->numeroTemporada)
            raizTemp->dir = inserir_temporada(raizTemp->dir, numeroTemporada, numEpisodios, ano, titulo, codigo_serie);
        else
            printf("Insercao nao realizada\n");
    }
    return novaTemp;
}

// funcao para contar a quantidade de temporadas de cada serie
int contar_temporadas(Temporada *raiz, int codigoSerie) 
{
    int contador = 0;
    if (raiz != NULL) 
    { // Se não houver temporadas, retorna 0.

    // Inicializa o contador de temporadas para este nó.

    if (raiz->codigo_serie == codigoSerie) 
        contador = 1; // Incrementa o contador se a temporada pertence à série desejada.

    // Verifica as temporadas da subárvore esquerda e direita e adiciona aos contadores.
    contador += contar_temporadas(raiz->esq, codigoSerie);
    contador += contar_temporadas(raiz->dir, codigoSerie);
    }

    return contador;
}




// exibe a arvore de temporada
void exibir_Temp(Temporada *no)
{
    if (no != NULL)
    {
       
        exibir_Temp(no->esq); // Exibe os nós da subárvore esquerda
        printf("Numero da temporada: %d\n", no->numeroTemporada);
        printf("Numero de episodios: %d\n", no->numEpisodios);
        printf("ano: %d\n", no->ano);
        printf("Titulo da temporada: %s\n", no->titulo);
        // Exiba outros campos, se necessário
        exibir_Temp(no->dir); // Exibe os nós da subárvore direita
    }
}


// busca uma temporada a partir do numero da temporada
Temporada *achar_temporada(Temporada *temporada, int codigo)
{
    Temporada *achada = NULL;
    if(temporada != NULL)
    {
        if(codigo == temporada->numeroTemporada)
            achada = temporada;
        else if(codigo < temporada->numeroTemporada)
            achada = achar_temporada(temporada->esq, codigo);
        else
            achada = achar_temporada(temporada->dir, codigo);
    }
    return achada;
}


///Participantes
 
// cadastra o participante 
void cadastrar_participante(Temporada *temporada, int codigo, const char *nomeArtista, const char *nomePersonagem, const char *descricao) 
{
    Temporada *aux = achar_temporada(temporada, codigo);
    if (aux) 
        aux->participantes = inserirParticipanteOrdenado(aux->participantes, nomeArtista, nomePersonagem, descricao);
    else 
        printf("Temporada nao existe.\n");
}

void mostrar_participantes(Temporada *temporada, int codigo)
{
    printf("\n");
    printf("numero da temporada: %d\n", codigo);
    exibir_participantes(temporada->participantes); // lincagem
    printf("---------------------------------------\n");
    printf("\n");
}


// função usada para contar a quantidade de temporadas que o personagem esta 
void percorrer_e_contar(Temporada *temporada, const char *nomePersonagem, int *cont)
{
    // vai percorrer toda a arvore de temporadas
    if (temporada != NULL) 
    { 
        // caso encontre o nome do artista retorna 1, validando que encontrou
        if(contar_artistas_da_temporada(temporada->participantes, nomePersonagem)) // lincagem com participantes.c
            (*cont)++; // conta a quantidade de temporadas
        percorrer_e_contar(temporada->esq, nomePersonagem, cont); // percorre a arvore de temporadas 
        percorrer_e_contar(temporada->dir, nomePersonagem, cont);
    }
}

// função responsável por percorrer a arvore de temporadas e exibir o nome dos artistas
void exibir_nomes_artistas(Temporada *temporada, const char *nomePersonagem) 
{
    if (temporada != NULL) 
    { 
        exibir_artistas_da_temporada(temporada->participantes, nomePersonagem); // percorre a lista de participantes, lincagem com participantes.c
        // chama recursiva
        exibir_nomes_artistas(temporada->esq, nomePersonagem); // percorre a arvore de temporadas 
        exibir_nomes_artistas(temporada->dir, nomePersonagem);
    }
}

// funcao para exibir o nome dos artistas
void buscar_e_imprimir_artistas(Temporada *temporada, const char *nomePersonagem, int qnt_temporadas) 
{
    int cont = 0; 
    percorrer_e_contar(temporada, nomePersonagem, &cont); // função usada para contar em quantas temporadas um personagem esta cadastrado.
    if(cont == qnt_temporadas) // caso for igual ao numero de temporadas
        exibir_nomes_artistas(temporada, nomePersonagem); // exibi os nomes dos artistas 
    else
        printf("o personagem nao esta em todas as temporadas.\n");
}

// liberar memoria
void liberar_temporadas(Temporada *temporadas) 
{
    if (temporadas != NULL) {
        liberar_temporadas(temporadas->esq);
        liberar_temporadas(temporadas->dir);
        liberar_participantes(temporadas->participantes);
        free(temporadas);
    }
}