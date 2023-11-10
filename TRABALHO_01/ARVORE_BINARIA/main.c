#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serie.c"
#include <time.h>

void menu()
{
    printf("\n");
    printf("Digite a opcao desejada:\n0 - Sair\n1 - Cadastrar_Serie\n2 - Cadastrar_Temporada\n3 - Cadastrar_Participantes\n4 - exibir serie(a)\n5- exibir temporada(b)\n6- exibir personagens(c)\n7- exibir artistas(d)\n>>> ");
}

int main()
{
    Serie *arvore = NULL;
    Serie *aux;
    Temporada *encontrada = NULL;
    int codigo, numTemporadas,op,numeroTemporada, numEpisodios, ano,temp;
    char titulo[50];
    do
    {
        menu();
        scanf("%d", &op);
        
        switch (op)
        {
            case 0:
                break;
            case 1:
                printf("Codigo da serie: ");
                scanf("%d", &codigo);
                limparBuffer();
                printf("Numero de temporadas: ");
                scanf("%d", &numTemporadas);
                limparBuffer();
                printf("Titulo da serie: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                arvore = inserir_serie(arvore, codigo, titulo, numTemporadas); // insercao dos valores da arvore series
                break;
            case 2:
                printf("\nInsira o codigo da serie: "); 
                scanf("%d", &codigo);
                printf("Numero da temporada: ");
                scanf("%d", &numeroTemporada);
                printf("Numero de episodios: ");
                scanf("%d", &numEpisodios);
                printf("Ano: ");
                scanf("%d", &ano);
                printf("Titulo da temporada: ");
                scanf("%49s", titulo);
                cadastrar_temporadas(arvore,codigo,numeroTemporada,numEpisodios,ano,titulo); // faz o cadastro da temporada caso encontre o codigo da serie 
                break;
            
            case 3:
                printf("Insira o codigo da serie: "); 
                scanf("%d", &codigo);
                aux = achar_serie(arvore, codigo);
                if (aux) 
                {
                    printf("Informe o numero da temporada: ");
                    scanf("%d", &temp);
                    encontrada = achar_temporada(aux->temporadas, temp);
                    if (encontrada) 
                    {
                        char nomeArtista[50];
                        char nomePersonagem[50];
                        char descricao[100];
                        printf("Nome do artista: ");
                        scanf("%49s", nomeArtista);
                        limparBuffer();
                        printf("Nome do personagem: ");
                        scanf("%49s", nomePersonagem);
                        limparBuffer();
                        printf("Descricao: ");
                        fgets(descricao, sizeof(descricao), stdin);

                        cadastrar_participante(encontrada, temp, nomeArtista, nomePersonagem, descricao);

                    } 
                    else 
                        printf("Temporada nao encontrada.\n");
                } 
                else 
                    printf("Serie nao encontrada.\n");
                break;
            
            case 4:
                exibir_Serie(arvore);
                break;
            
            case 5:
                printf("\nInsira o codigo da serie: "); 
                scanf("%d", &codigo);
                aux = achar_serie(arvore, codigo);
                if(aux)
                    mostrar_temporadas(aux, codigo); // mostra uma temporada caso encontre o codigo da serie 
                else
                    printf("serie nao encontrada.\n");
                break;
            
            case 6:
                printf("\nInsira o codigo da serie: "); 
                scanf("%d", &codigo);
                aux = achar_serie(arvore, codigo);
                if(aux)
                {
                    printf("informe o numero da temporada: \n");
                    scanf("%d",&temp);
                    encontrada = achar_temporada(aux->temporadas, temp);
                    if(encontrada)
                    {
                        printf("codigo da serie: %d\n",codigo);
                        exibir_nome_personagens(encontrada->participantes);
                    }
                    else
                        printf("temporada nao encontrada.\n");
                } 
                else
                    printf("serie nao encontrada.\n");
                break;
            case 7:
                printf("Insira o codigo da serie: ");
                scanf("%d", &codigo);
                char nomePersonagem[50];
                printf("Insira o nome do personagem: ");
                scanf("%49s", nomePersonagem);
                imprimir_artistas_do_personagem(arvore, codigo, nomePersonagem);
                break;
            default:
                if (op != 0)
                    printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op != 0);    
    liberar_series(arvore);
    return 0;
}