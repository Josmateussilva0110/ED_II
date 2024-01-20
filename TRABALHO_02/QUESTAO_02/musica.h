#ifndef MUSICA_H

#define MUSICA_H
typedef struct Musicas Musicas;

struct Musicas
{
    char titulo_musica[20];
    int quant_min;
    Musicas *proximo;
};

int cadastrar_musicas(Musicas** pessoa);
int inserir_musicas(Musicas ** M, Musicas *newa);
void mostrar_M(Musicas *pessoas,char nome[20],int *valid);
void liberarMem_M(Musicas *pessoas);
void removerMusica(Musicas **a, char nome[20]);

#endif