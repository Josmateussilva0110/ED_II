#include "musica.h"
#include "musica.c"
#include "artista.h"
#include "album.h"
#include "artista.c"
#include "album.c"
#include <stdio.h>
#include <stdlib.h>

void menu()
{
  printf("1 - Inserir artista\n2 - Cadastrar Album\n3 - Cadastrar Musica\n4 - Imprimir Artista\n5 - Imprimir Album\n6 - Imprimir Musica\n7 - Remover musica\n0 - Sair\n");
}

int main(){
    Artista *arvore = NULL;
    Artista *achou = NULL;
    Artista *no = NULL;
    int op, numero_album;
    char nome[70], estilo[70], nome_procurar[70];
    char titulo[70], artista[70];
    int ano_Album, num_musicas;
    do
    {
        int flag, achado, achado_2;
        Info sobe;
        menu();
        scanf("%d",&op);
        switch (op)
        {

            case 1://Cadastrar artista
                printf("Nome do artista: ");
                limparBuffer(); 
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Estilo musical: ");
                fgets(estilo, sizeof(estilo), stdin);
                estilo[strcspn(estilo, "\n")] = '\0';

                printf("Numero de albuns: ");
                scanf("%d", &numero_album);
                limparBuffer(); // Limpar o buffer de entrada
                
                inserir_Artista(&arvore, nome, estilo, numero_album, NULL, &sobe, &flag);
                
                if(flag == 1)
                    printf("Insereco completa.\n");
                else
                    printf("Erro ao inserir_Artista.\n");

                break;
            
            case 2: //cadastrar album
                limparBuffer();
                printf("nome do artista: ");
                fgets(nome_procurar, sizeof(nome_procurar), stdin);
                nome_procurar[strcspn(nome_procurar, "\n")] = '\0';
                no = achar_artista(arvore, nome_procurar, &achado);
                if(no)
                {
                    printf("titulo: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = '\0';
                    printf("ano lancamento: ");
                    scanf("%d",&ano_Album);
                    printf("Numero de albuns: ");
                    scanf("%d", &num_musicas);
                    cadastrar_albuns(no, titulo, ano_Album, num_musicas, achado);
                    printf("insercao completa.\n");
                    break;
                }
                else
                    printf("nao achei\n");
                break;
            case 3: //Cadastrar musica
                limparBuffer();
                printf("nome do artista: ");
                fgets(nome_procurar, sizeof(nome_procurar), stdin);
                nome_procurar[strcspn(nome_procurar, "\n")] = '\0';
                no = achar_artista(arvore, nome_procurar, &achado);
                if(no){
                    Album *noo;
                    printf("\n\nnome do album: ");    
                    fgets(nome_procurar, sizeof(nome_procurar), stdin);

                    nome_procurar[strcspn(nome_procurar, "\n")] = '\0';
                    noo = busca_lista_album(arvore, nome_procurar,&achado);  
                    cadastrar_musicas(&noo->musicas);
                      
                  }else
                    printf("artista nao encontrado!\n");
             break;


            case 4: //procurar artista 
                limparBuffer();
                printf("artista: ");
                scanf("%s", artista);
                achou = achar_artista(arvore, artista, &achado_2);
                 if(achou){
                  printf("Artista encontrado\n\n");
                  if(achado_2 == 1){
                    printf("Nome: %s\n",achou->info_1->nome);
                    printf("Estilo Musical: %s\n",achou->info_1->estilo_musical);
                    printf("Numero de albuns: %d\n",achou->info_1->num_albuns);
                  }else{
                    printf("Nome: %s\n",achou->info_2->nome);
                    printf("Estilo Musical: %s\n",achou->info_2->estilo_musical);
                    printf("Numero de albuns: %d\n",achou->info_2->num_albuns);
                  }
                }else
                    printf("artista nao encontrado\n");
                break;

            case 5:
                limparBuffer();
                printf("artista: ");
                scanf("%s", artista);
                achou = achar_artista(arvore, artista, &achado_2);
                if(achou){
                  limparBuffer();
                  printf("titulo do album: ");
                  scanf("%s", artista);
                  Album *test = NULL;
                  test = busca_lista_album(achou,artista,&achado_2);
                  if(achado_2 == 1){
                    printf("Nome: %s\n",test->info_1->titulo);
                    printf("Estilo Musical: %d\n",test->info_1->ano_Album);
                    printf("Numero de albuns: %d\n",test->info_1->num_musicas);
                  }else{
                    printf("Nome: %s\n",test->info_2->titulo);
                    printf("Estilo Musical: %d\n",test->info_2->ano_Album);
                    printf("Numero de albuns: %d\n",test->info_2->num_musicas);
                  }
                }else
                    printf("Album nao encontrado\n");
             break;
                break;

            case 6:
                limparBuffer();
                printf("artista: ");
                scanf("%s", artista);
                achou = achar_artista(arvore, artista, &achado_2);
                if(achou){
                  limparBuffer();
                  printf("titulo do album: ");
                  scanf("%s", artista);
                  Album *test;
                  test = NULL;
                  test = busca_lista_album(achou,artista,&achado_2);
                  limparBuffer();
                  printf("nome da musica: ");
                  scanf("%s", artista);
                  printf("\n");
                  mostrar_M(test->musicas,artista,&achado_2);
                  if(achado_2 == 0)
  	                printf("Musica nao encontrada!!");
                }else
                    printf("Album nao encontrado\n");
              break;

            case 7:
                limparBuffer();
                printf("artista: ");
                scanf("%s", artista);
                achou = achar_artista(arvore, artista, &achado_2);
                if(achou){
                  limparBuffer();
                  printf("titulo do album: ");
                  scanf("%s", artista);
                  Album *test;
                  test = NULL;
                  test = busca_lista_album(achou,artista,&achado_2);
                  limparBuffer();
                  printf("agora diga o nome da musica: ");
                  scanf("%s", artista);
                  removerMusica(&test->musicas,artista);

                }else
                    printf("Album nao encontrado\n");
                 break;

            case 0:
              break;
           
            default:
                break;
        }
    } while (op != 0);
 return 0;
}
