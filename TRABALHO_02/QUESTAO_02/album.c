#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "album.h"
#include "artista.h"


Album *criaNo_album(char *titulo, int ano_Album, int num_musicas, Album *noEsq, Album *noCentro) 
{
    Album *no = (Album*)malloc(sizeof(Album)); 
    no->info_1 = (Info_album*)malloc(sizeof(Info_album));
    strcpy(no->info_1->titulo, titulo);
    no->info_1->ano_Album = ano_Album;
    no->info_1->num_musicas = num_musicas;
    no->num_info = 1;
    no->esq = noEsq;
    no->centro = noCentro;
    no->dir = NULL;
    no->musicas = NULL;
    no->info_2 = NULL;
    return no;
}

void adicionaNo_album(Album **raiz, char *titulo, int ano_Album, int num_musicas, Album *filho) 
{
    (*raiz)->info_2 = (Info_album*)malloc(sizeof(Info_album));
    if(strcmp(titulo, (*raiz)->info_1->titulo) > 0)
    {
        strcpy((*raiz)->info_2->titulo, titulo);
        (*raiz)->info_2->ano_Album = ano_Album;
        (*raiz)->info_2->num_musicas = num_musicas;
        (*raiz)->dir = filho;
    }
    else
    {
        strcpy((*raiz)->info_2->titulo, (*raiz)->info_1->titulo);
        (*raiz)->info_2->ano_Album = (*raiz)->info_1->ano_Album;
        (*raiz)->info_2->num_musicas = (*raiz)->info_1->num_musicas;

        strcpy((*raiz)->info_1->titulo, titulo);
        (*raiz)->info_1->ano_Album = ano_Album;
        (*raiz)->info_1->num_musicas = num_musicas;

        (*raiz)->dir = (*raiz)->centro;
        (*raiz)->centro = filho;
    }
    (*raiz)->num_info = 2;
}

Album *quebraNo_album(Album **raiz, Album *filho, char *titulo, int ano_Album, int num_musicas, Info_album *sobe) 
{
    Album *maiorNo;
    maiorNo = NULL;

    if (strcmp(titulo, (*raiz)->info_2->titulo) > 0) 
    {
        strcpy(sobe->titulo, (*raiz)->info_2->titulo);
        sobe->ano_Album = (*raiz)->info_2->ano_Album;
        sobe->num_musicas = (*raiz)->info_2->num_musicas;

        maiorNo = criaNo_album(titulo, ano_Album, num_musicas, (*raiz)->dir, filho);
    } 
    
    else if (strcmp(titulo, (*raiz)->info_1->titulo) < 0) 
    {
        strcpy(sobe->titulo, (*raiz)->info_1->titulo);
        sobe->ano_Album = (*raiz)->info_1->ano_Album;
        sobe->num_musicas = (*raiz)->info_1->num_musicas;

        maiorNo = criaNo_album((*raiz)->info_2->titulo, (*raiz)->info_2->ano_Album, (*raiz)->info_2->num_musicas, (*raiz)->centro, (*raiz)->dir);
        
        strcpy((*raiz)->info_1->titulo, titulo);
        (*raiz)->info_1->ano_Album = ano_Album;
        (*raiz)->info_1->num_musicas = num_musicas;
        (*raiz)->centro = filho;
    }

    else 
    {
        strcpy(sobe->titulo, titulo);
        sobe->ano_Album = ano_Album;
        sobe->num_musicas = num_musicas;
        maiorNo = criaNo_album((*raiz)->info_2->titulo,(*raiz)->info_2->ano_Album, (*raiz)->info_2->num_musicas, filho, (*raiz)->dir);  
    }

    (*raiz)->num_info = 1;
    (*raiz)->info_2 = NULL;
    (*raiz)->dir = NULL; 
    return maiorNo;
}

int folha_album(Album *raiz)
{
    int valid = 0;
    if(raiz->esq == NULL)
        valid = 1;
    return valid;
}

Album *inserir_Album(Album **raiz, char *titulo, int ano_Album, int num_musicas, Album *pai, Info_album *infoSobe)
{
    printf("entrou em inserir album\n");
    Album *maiorNo;
    if (*raiz == NULL)
        *raiz = criaNo_album(titulo, ano_Album, num_musicas, NULL, NULL);
    else
    {
        if (folha_album(*raiz))
        {
            if ((*raiz)->num_info == 1)
            {
                adicionaNo_album(raiz, titulo, ano_Album, num_musicas, NULL);
                maiorNo = NULL;
            }
            else
            {
                maiorNo = quebraNo_album(raiz, NULL, titulo, ano_Album, num_musicas, infoSobe);

                if (pai == NULL)
                {
                    *raiz = criaNo_album(infoSobe->titulo, infoSobe->ano_Album, infoSobe->num_musicas, *raiz, maiorNo);
                    maiorNo = NULL;
                }
            }
        }
        else
        {
            if (strcmp(titulo, (*raiz)->info_1->titulo) < 0)   
                maiorNo = inserir_Album(&((*raiz)->esq), titulo, ano_Album, num_musicas, *raiz, infoSobe);
            else if (((*raiz)->num_info == 1) || (((*raiz)->num_info == 2) && strcmp(titulo, (*raiz)->info_2->titulo) < 0))
                maiorNo = inserir_Album(&((*raiz)->centro), titulo, ano_Album, num_musicas, *raiz, infoSobe);
            else
                maiorNo = inserir_Album(&((*raiz)->dir), titulo, ano_Album, num_musicas, *raiz, infoSobe);   

            if (maiorNo != NULL)
            {
                if ((*raiz)->num_info == 1)
                {
                    adicionaNo_album(raiz, infoSobe->titulo, infoSobe->ano_Album, infoSobe->num_musicas, maiorNo);
                    maiorNo = NULL;
                }
                else
                {
                    maiorNo = quebraNo_album(raiz, maiorNo, infoSobe->titulo, infoSobe->ano_Album, infoSobe->num_musicas, infoSobe);
                    if (pai == NULL)
                    {
                        *raiz = criaNo_album(infoSobe->titulo, infoSobe->ano_Album, infoSobe->num_musicas, *raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }
    return maiorNo;
}

void imprimir_Album(Album *raiz)
{
    if(raiz != NULL)
    {
        imprimir_Album(raiz->esq);
        printf("Info 1 titulo: %s\n", raiz->info_1->titulo);
        printf("Info 1 ano lancamento: %d\n", raiz->info_1->ano_Album);
        printf("Info 1 numero musicas: %d\n", raiz->info_1->num_musicas);
        printf("\n");
        imprimir_Album(raiz->centro);
        if(raiz->num_info == 2)
        {
            printf("Info 2 titulo: %s\n", raiz->info_2->titulo);
            printf("Info 2 ano lancamento: %d\n", raiz->info_2->ano_Album);
            printf("Info 2 numero musicas: %d\n", raiz->info_2->num_musicas);
        }
        imprimir_Album(raiz->dir);
    }
}

Album *busca_Album(Album *raiz, const char *palavra)
{
    Album *encontrada = NULL;

    if(raiz != NULL)
    {
        if(strcmp(palavra, raiz->info_1->titulo) == 0)
            encontrada = raiz;

        if(raiz->num_info == 2 && strcmp(palavra, raiz->info_2->titulo) == 0)
            encontrada = raiz;

        if(encontrada == NULL)
        {
            if(strcmp(palavra, raiz->info_1->titulo) < 0)
                encontrada = busca_Album(raiz->esq, palavra);
            else if((raiz->num_info == 1 || (raiz->num_info == 2 && strcmp(palavra, raiz->info_2->titulo) < 0)))
                encontrada = busca_Album(raiz->centro, palavra);
            else
                encontrada = busca_Album(raiz->dir, palavra);
        }
    }
    return encontrada;
}

Album *achar_album(Album *raiz, const char *nome, int *posicao){
    Album *encontrada;
    encontrada = NULL;
    if(raiz != NULL){
        if(strcmp(nome, raiz->info_1->titulo) == 0){
            encontrada = raiz;
            *posicao = 1;

        }

        if(raiz->num_info == 2){
            if(strcmp(nome, raiz->info_1->titulo) == 0){
                encontrada = raiz;
                *posicao = 1;
            }
            else if(strcmp(nome, raiz->info_2->titulo) == 0){
                encontrada = raiz;
                *posicao = 2; 
            }
        }

        if(encontrada == NULL){
            if(strcmp(nome, raiz->info_1->titulo) < 0)
                encontrada = achar_album(raiz->esq, nome,posicao);
            else if((raiz->num_info == 1 || (raiz->num_info == 2 && strcmp(nome, raiz->info_2->titulo) < 0)))
                encontrada = achar_album(raiz->centro, nome,posicao);
            else
                encontrada = achar_album(raiz->dir, nome,posicao);
        }
    }
    return encontrada;
}




Album* findminimum(Album* no) {
    
    while (no->esq != NULL) 
        no = no->esq;
    
    return no;
}

Album* findmaximum(Album* no) {
    
    while (no->dir != NULL) 
        no = no->dir;
    
    return no;
}

void merge(Album *raiz) {

    Album *pai = NULL; 
    Album *irmao = NULL; 

    if (raiz->esq != NULL) {
        pai = raiz;
        irmao = raiz->esq;
    } else if (raiz->dir != NULL) {
        pai = raiz;
        irmao = raiz->dir;
    } else if (raiz->centro != NULL) {
        pai = raiz;
        irmao = raiz->centro;
    } else if (raiz->esq != NULL && raiz->dir != NULL) {
        pai = raiz;
        irmao = raiz->esq;
    }

    if (irmao != NULL && irmao->num_info == 1) {
        if (pai->esq == raiz) {
            pai->centro = irmao->esq;
            pai->info_2 = pai->info_1;
            pai->info_1 = irmao->info_1;
            pai->dir = irmao->centro;
            free(irmao);
            pai->num_info = 2;
        } else if (pai->centro == raiz) {
            pai->info_2 = irmao->info_1;
            pai->dir = pai->centro;
            pai->centro = irmao->centro;
            free(irmao);
            pai->num_info = 2;
        } else if (pai->dir == raiz) {
            pai->info_2 = irmao->info_1;
            pai->dir = irmao->centro;
            free(irmao);
            pai->num_info = 2;
        }
    } else {
        if (pai->esq == raiz) {
            irmao->info_1 = pai->info_1;
            pai->info_1 = pai->info_2;
            irmao->centro = irmao->esq;
            irmao->esq = irmao->dir;
            irmao->dir = NULL;
            pai->num_info = 1;
        } else if (pai->centro == raiz) {
            irmao->info_1 = pai->info_1;
            pai->info_1 = pai->info_2;
            irmao->dir = irmao->esq;
            irmao->esq = irmao->centro;
            irmao->centro = NULL;
            pai->num_info = 1;
        } else if (pai->dir == raiz) {
            irmao->info_1 = pai->info_2;
            irmao->centro = irmao->dir;
            irmao->dir = NULL;
            pai->num_info = 1;
        }
    }
}

void remove_Album(Album *candidate, char titulo[50]) {
    if (candidate != NULL)
    {

        if (strcmp(candidate->info_1->titulo, titulo) == 0 || strcmp(candidate->info_2->titulo, titulo) == 0) {
            if (folha_album(candidate)) {
                if (strcmp(candidate->info_1->titulo, titulo) == 0)
                    free(candidate->info_1);
                else
                    free(candidate->info_2);
            } else {
                
                if (strcmp(candidate->info_1->titulo, titulo) == 0) {
                    Album *swap = findmaximum(candidate->esq);
                    free(candidate->info_1);
                    candidate->info_1 = swap->info_1;
                    remove_Album(candidate->esq, swap->info_1->titulo);
                } else {
                    
                    Album *swap = findminimum(candidate->dir);
                    free(candidate->info_2);
                    candidate->info_2 = swap->info_2;
                    remove_Album(candidate->dir, swap->info_2->titulo);
                }
            }
        } else {
            if (strcmp(candidate->info_1->titulo, titulo) > 0) {
                remove_Album(candidate->esq, titulo); 
            } else if (strcmp(candidate->info_1->titulo, titulo) <= 0 && candidate->num_info == 2) {
    
                remove_Album(candidate->centro, titulo);
            } else {
                if (strcmp(candidate->info_1->titulo, titulo) < 0) {

                    remove_Album(candidate->centro, titulo);
                } else {

                    remove_Album(candidate->dir, titulo);
                }
            }
        }
    }

    merge(candidate); 
}