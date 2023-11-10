#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "participantesAVL.c"


// Estrutura para uma temporada
typedef struct Temporada 
{
    int numeroTemporada;
    char titulo[50];
    int numEpisodios;
    int ano, codigo_serie;
    Participante *participantes; // Lista de participantes
    struct Temporada *esq, *dir;
    int altura;
} Temporada;

// faz o mesmo que na de series
Temporada *criar_temporada(int numeroTemporada, const char *titulo, int numEpisodios, int ano, int codi) 
{
    Temporada *novaTemporada;
    novaTemporada = (Temporada *)malloc(sizeof(Temporada));
    if(novaTemporada != NULL)
    {
        novaTemporada->numeroTemporada = numeroTemporada;
        strcpy(novaTemporada->titulo, titulo);
        novaTemporada->numEpisodios = numEpisodios;
        novaTemporada->ano = ano;
        novaTemporada->codigo_serie = codi;
        novaTemporada->participantes = NULL; // Inicialize a lista de participantes como vazia
        novaTemporada->esq = NULL;
        novaTemporada->dir = NULL;
        novaTemporada->altura = 0;
    }
    return novaTemporada;
}

// Função para encontrar o maior de dois números
int maior(int a, int b) {
    int maior;
    if (a > b) {
        maior = a; 
    } else {
        maior = b;  
    }
    
    return maior;  
}

int altura(Temporada *no) {
    int altura = -1;

    if (no != NULL) {
        altura = no->altura;
    }

    return altura; 
}

// Função para calcular o fator de balanceamento de um nó
int fatorBalanceamento(Temporada *no) {
    int fator = 0;
    if (no) {
        int altura_esq = altura(no->esq);
        int altura_dir = altura(no->dir);
        fator = altura_esq - altura_dir;
    }
    return fator;
}


// Funções de rotação
Temporada *rotacaoEsq(Temporada *no) {
    Temporada *y,*f;
    y = no->dir;
    f = y->esq;

    y->esq = no;
    no->dir = f;

    no->altura = maior(altura(no->esq), altura(no->dir)) + 1;
    y->altura = maior(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

Temporada *rotacaoDir(Temporada *no) {
    Temporada *y,*f;
    y = no->esq;
    f = y->dir;

    y->dir = no;
    no->esq = f;

    no->altura = maior(altura(no->esq), altura(no->dir)) + 1;
    y->altura = maior(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

Temporada *rotacaoEsqDir(Temporada *no) {
    no->esq = rotacaoEsq(no->esq);
    return rotacaoDir(no);
}

Temporada *rotacaoDirEsq(Temporada *no) {
    no->dir = rotacaoDir(no->dir);
    return rotacaoEsq(no);
}

// Função para balancear a árvore
Temporada *balancear(Temporada *raiz) {
    int fb = fatorBalanceamento(raiz);

    if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
    {
        raiz = rotacaoEsq(raiz);
    }else if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
    {
        raiz = rotacaoDir(raiz);
    }else if (fb > 1 && fatorBalanceamento(raiz->esq) < 0)
    {
        raiz = rotacaoEsqDir(raiz);
    }else if (fb < -1 && fatorBalanceamento(raiz->dir) > 0)
    {
        raiz = rotacaoDirEsq(raiz);
    }
    return raiz;
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

        raizTemp->altura = maior(altura(raizTemp->esq), altura(raizTemp->dir)) + 1;
        novaTemp = balancear(raizTemp);
    }
    return novaTemp;
}


int contar_temporadas(Temporada *raiz, int codigoSerie) 
{
    if (raiz == NULL) 
        return 0; // Se não houver temporadas, retorna 0.

    // Inicializa o contador de temporadas para este nó.
    int contador = 0;

    if (raiz->codigo_serie == codigoSerie) 
        contador = 1; // Incrementa o contador se a temporada pertence à série desejada.

    // Verifica as temporadas da subárvore esquerda e direita e adiciona aos contadores.
    contador += contar_temporadas(raiz->esq, codigoSerie);
    contador += contar_temporadas(raiz->dir, codigoSerie);

    return contador;
}

// exibe a arvore de temporada
void exibir_Temp(Temporada *no)
{
    if (no)
    {
       
        exibir_Temp(no->esq); // Exibe os nós da subárvore esquerda
        printf("Numero da Temporada: %d\n", no->numeroTemporada);
        printf("Numero de episodios: %d\n", no->numEpisodios);
        printf("ano: %d\n", no->ano);
        printf("Titulo da temporada: %s\n", no->titulo);
        exibir_Temp(no->dir); // Exibe os nós da subárvore direita
    }
}


// busca uma temporada a partir do numero da temporada
Temporada *achar_temporada(Temporada *temporada, int codigo)
{
    Temporada *Temp_Enc = NULL;

    if (temporada != NULL) 
    {
        if (codigo == temporada->numeroTemporada) 
            Temp_Enc = temporada;
        else if (codigo < temporada->numeroTemporada) 
            Temp_Enc = achar_temporada(temporada->esq, codigo);
        else
            Temp_Enc = achar_temporada(temporada->dir, codigo);
    }
    return Temp_Enc;
}


///Prticipantes

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
        //liberar_participantes(temporadas->participantes);
        free(temporadas);
    }
}