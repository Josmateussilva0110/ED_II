
#ifndef ALBUM_H

#define ALBUM_H

typedef struct Info_album Info_album;
typedef struct Album Album;
typedef struct ListaAlbum ListaAlbum;

struct ListaAlbum{
    Album *arvore_album;
    ListaAlbum *prox;
};

struct Info_album
{
    char titulo[50];
    int ano_Album;
    int num_musicas;
};

struct Album {
    Info_album *info_1, *info_2;
    Musicas *musicas;
    Album *esq, *dir, *centro;
    int num_info;
};

Album *criaNo_album(char *titulo, int ano_Album, int num_musicas, Album *noEsq, Album *noCentro) ;
void adicionaNo_album(Album **raiz, char *titulo, int ano_Album, int num_musicas, Album *filho) ;
Album *quebraNo_album(Album **raiz, Album *filho, char *titulo, int ano_Album, int num_musicas, Info_album *sobe) ;
int folha_album(Album *raiz);
Album *inserir_Album(Album **raiz, char *titulo, int ano_Album, int num_musicas, Album *pai, Info_album *infoSobe);
void imprimir_Album(Album *raiz);
Album *busca_Album(Album *raiz, const char *palavra);
Album* findminimum(Album* no);
Album* findmaximum(Album* no);
void merge(Album *raiz);
void remove_Album(Album *candidate, char titulo[50]) ;
Album *achar_album(Album *raiz, const char *nome, int *posicao);


#endif
