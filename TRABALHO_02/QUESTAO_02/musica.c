#include "artista.h"
#include "album.h"
#include "musica.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Para cada música deve se ter o título, e a quantidade de minutos.

int cadastrar_musicas(Musicas** pessoa) {
    Musicas* new = (Musicas*)malloc(sizeof(Musicas));
    printf("\n\nDiga o nome da musica: ");
    scanf(" %[^\n]", new->titulo_musica);
    printf("\nDiga a quantidade de minutos nela: ");
    scanf(" %d", &new->quant_min);

    int inseridoComSucesso = inserir_musicas(pessoa, new);

    if (inseridoComSucesso) {
        printf("Musica cadastrada com sucesso!\n");
    } else {
        printf("Erro ao cadastrar a musica. Musica ja existe.\n");
        free(new);
    }

    return inseridoComSucesso;
}

int inserir_musicas(Musicas ** M, Musicas *newa) {
    Musicas* atual = *M;
    Musicas* anterior = NULL;
    int valida;

    while (atual != NULL && strcmp(newa->titulo_musica, atual->titulo_musica) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) {
        valida = 0;
    }

    atual = *M;
    anterior = NULL;
    while (atual != NULL && strcmp(newa->titulo_musica, atual->titulo_musica) > 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior == NULL) {
        newa->proximo = *M;
        *M = newa;
    } else {
        anterior->proximo = newa;
        newa->proximo = atual;
    }
    valida = 1;
    return valida;
}



void mostrar_M(Musicas *pessoas,char nome[20],int *valid){
    *valid = 0;
	Musicas *aux;
	aux = pessoas;
	while(aux != NULL){
        if(strcmp(nome,pessoas->titulo_musica)==0){
		    printf("\n\nNome da musica: %s", aux->titulo_musica);
		    printf("\nTempo em minutos: %d", aux->quant_min);
            *valid = 1;
        }
        aux = aux->proximo;

	}

}

void removerMusica(Musicas **a, char nome[20]) {
    Musicas *atual = *a;
    Musicas *ant = NULL;

    while (atual != NULL && strcmp(atual->titulo_musica, nome) != 0) {
        ant = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) {
        if (ant == NULL) {
            *a = atual->proximo;
        } else {
            ant->proximo = atual->proximo;
        }
        free(atual);
    } else {
        printf("\nMusica nao encontrada!!!");
    }
}

void liberarMem_M(Musicas *pessoas){
    Musicas *aux;
    aux = pessoas;
	Musicas *aux2;
    aux2 = NULL;

	while (aux != NULL) {
		aux2 = aux;
		aux = aux->proximo;
		free(aux2);
		aux2 = NULL;
	}
	free(aux);
}
