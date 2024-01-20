#include "album.h"

#ifndef ARTISTA_H
#define ARTISTA_H

typedef struct Info Info;
typedef struct Artista Artista;

struct Info{
    char nome[50];
    char estilo_musical[50];
    int num_albuns;
    ListaAlbum *lista_albuns;  // Lista de árvores de álbuns
};

struct Artista {
    Info *info_1, *info_2;
    int num_info;
    Artista *esq, *dir, *centro; 
};

void limparBuffer();
Artista *criaNo_Artista(char *nome, char *estilo, int num_albuns, Artista *noEsq, Artista *noCentro) ;
void adicionaNo_Artista(Artista **raiz, char *nome, char *estilo, int num_albuns, Artista *filho) ;
Artista *quebraNo_Artista(Artista **raiz, Artista *filho, char *nome, char *estilo, int num_albuns, Info *sobe) ;
int folha_Artista(Artista *raiz);
Artista *inserir_Artista(Artista **raiz, char *nome, char *estilo, int num_albuns, Artista *pai, Info *infoSobe, int *flag);
void imprimir_Artista(Artista *raiz);
Artista *achar_artista(Artista *raiz, const char *nome, int *posicao);
void cadastrar_albuns(Artista *albuns, char *titulo, int ano_Album, int num_musicas, int posicao);
void mostrar_album(Artista *raiz, int posicao);
Artista* findminimum_A(Artista* no);
Artista* findmaximum_A(Artista* no);
void merge_A(Artista **raiz);
void remove_Artista(Artista **raiz, char titulo[50]);
Album *busca_lista_album(Artista *raiz, char nome[50], int *posicao);

#endif 