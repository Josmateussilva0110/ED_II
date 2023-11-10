#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Estrutura para um participante
typedef struct Participante 
{
    char nomeArtista[50];
    char nomePersonagem[50];
    char descricao[100];
    struct Participante *prox;
} Participante;

Participante* criarParticipante(const char* nomeArtista, const char* nomePersonagem, const char* descricao) 
{
    Participante* novoParticipante = (Participante*)malloc(sizeof(Participante));
    strcpy(novoParticipante->nomeArtista, nomeArtista);
    strcpy(novoParticipante->nomePersonagem, nomePersonagem);
    strcpy(novoParticipante->descricao, descricao);
    novoParticipante->prox = NULL;
    return novoParticipante;
}

Participante* inserirParticipanteOrdenado(Participante* lista, const char* nomeArtista, const char* nomePersonagem, const char* descricao) 
{
    Participante* novoParticipante = criarParticipante(nomeArtista, nomePersonagem, descricao);

    // Se a lista está vazia ou o novo participante deve ser inserido no início
    if (lista == NULL || strcmp(nomeArtista, lista->nomeArtista) < 0) 
    {
        novoParticipante->prox = lista;
        return novoParticipante;
    }

    // Caso contrário, percorra a lista para encontrar a posição correta
    Participante* atual = lista;
    while (atual->prox != NULL && strcmp(nomeArtista, atual->prox->nomeArtista) > 0) 
        atual = atual->prox;

    // Insira o novo participante entre 'atual' e 'atual->prox'
    novoParticipante->prox = atual->prox;
    atual->prox = novoParticipante;

    return lista;
}

void exibir_participantes(Participante *lista)
{
    if (lista == NULL)
    {
        printf("lista vazia.\n");
        return;
    }
    
    Participante *atual = lista;
    
    while (atual != NULL) 
    {
        printf("Nome do artista: %s\n", atual->nomeArtista);
        printf("Nome do personagem: %s\n", atual->nomePersonagem);
        printf("Descrição: %s\n", atual->descricao);
        printf("\n");
        atual = atual->prox;
    }
}

// funcao que valida se nome foi encontrado
int contar_artistas_da_temporada(Participante *participantes, const char *nomePersonagem) 
{
    int valid = 0; // false
    Participante *atual = participantes;
    // percorre a lista 
    while (atual != NULL) 
    {
        if (strcmp(atual->nomePersonagem, nomePersonagem) == 0) // se o nome do personagem for igual
            valid = 1; // true
        atual = atual->prox;
    }
    return valid;
}

// percorre toda a lista de participantes
void exibir_artistas_da_temporada(Participante *participantes, const char *nomePersonagem) 
{
    Participante *atual = participantes;
    // percorre a lista 
    while (atual != NULL) 
    {
        if (strcmp(atual->nomePersonagem, nomePersonagem) == 0) // se o nome do personagem for igual
            printf("Artista: %s\n", atual->nomeArtista); // exibe 
        atual = atual->prox;
    }
}

void exibir_nome_personagens(Participante *lista)
{
    if (lista == NULL)
    {
        printf("lista vazia.\n");
        return;
    }
    if(lista->prox != NULL)
        exibir_nome_personagens(lista->prox);
    printf("nome do personagem: %s\n", lista->nomePersonagem);
}


// liberar memoria 
void liberar_participantes(Participante *lista) 
{
    Participante *atual = lista;
    while (atual != NULL) {
        Participante *prox = atual->prox;
        free(atual);
        atual = prox;
    }
}
