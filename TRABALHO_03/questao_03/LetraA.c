#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_VETOR_DESTINO_1 101
#define TAMANHO_VETOR_DESTINO_2 150
// Feito, só posso colocar até 101 posições, porque se colocar mais ele fica em loop tentando inserir.
#define NUM_FUNCIONARIOS 1000

typedef struct {
    char matricula[7];
    char nome[50];
    char funcao[20];
    double salario;
} Funcionario;

typedef struct {
    Funcionario* dados;
    int colisoes;
} EntradaHash;


void rotacionarEsquerda(char *numero) {
    if (strlen(numero) == 6) {
        char digito1 = numero[4];
        char digito2 = numero[5];
        memmove(numero + 2, numero, 4); 
        numero[0] = digito1;
        numero[1] = digito2;
    }
}


// Função Hashing A
int funcaoHashA(const char* matricula, int tamanhoVetor) {
    int posicao;

    char matriculaOriginal[7];
    strcpy(matriculaOriginal, matricula);

    char matriculaRotacionada[7];
    strcpy(matriculaRotacionada, matricula);
    rotacionarEsquerda(matriculaRotacionada);

    // Imprimir o número após a rotação
    printf("Matricula original: %s\n", matriculaOriginal);
    printf("Numero apos rotacao: %s\n", matriculaRotacionada);

    // Imprimir os dígitos extraídos na ordem correta
    int digito6 = matriculaRotacionada[1] - '0';
    int digito2 = matriculaRotacionada[3] - '0';
    int digito3 = matriculaRotacionada[5] - '0';
    printf("Digitos extraidos: %d %d %d\n", digito6, digito2, digito3);

    posicao = ((digito6) * 100 + (digito2) * 10 + (digito3)) % tamanhoVetor;
    printf("Ficou na posicao: %d\n\n", posicao);

    return posicao;
}

// Tratamento de colisões para Função Hashing A
int tratarColisaoA(EntradaHash* vetorHash, int posicao, const char* matricula, int tamanhoVetor) {
    int offset = matricula[0] - '0';
    int novaPosicao = (posicao + offset) % tamanhoVetor;
    int primeiraPosicaoOcupada = -1; // Marcador para a primeira posição ocupada

    printf("Tratamento de colisao A:\n");
    printf("Posicao original: %d\n", posicao);
    printf("Offset (primeiro dígito da matricula): %d\n", offset);

    // Verificar se todas as posições possíveis estão ocupadas
    while (vetorHash[novaPosicao].dados != NULL && novaPosicao != posicao) {
        printf("Colisao detectada! Tentando nova posicao...\n");

        if (primeiraPosicaoOcupada == -1) {
            primeiraPosicaoOcupada = novaPosicao;
        }

        novaPosicao = (novaPosicao + offset) % tamanhoVetor;
    }

    // Verificar se todas as posições possíveis estão ocupadas
    if (novaPosicao == posicao) {
        printf("Todas as posicoes possiveis estao ocupadas! Retirando informacao da primeira posicao...\n");

        // Encontrar o primeiro número na posição original e substituir
        int primeiraMatricula = atoi(vetorHash[posicao].dados->matricula);
        free(vetorHash[posicao].dados);

        // Substituir a informação na posição original
        vetorHash[posicao].dados = (Funcionario*)malloc(sizeof(Funcionario));
        memcpy(vetorHash[posicao].dados, vetorHash[primeiraPosicaoOcupada].dados, sizeof(Funcionario));

        // Limpar a informação na posição onde o primeiro número foi encontrado
        free(vetorHash[primeiraPosicaoOcupada].dados);
        vetorHash[primeiraPosicaoOcupada].dados = NULL;

        printf("Esse numero estava por primeiro la: %d\n", primeiraMatricula);
    }

    printf("Nova posicao encontrada: %d\n\n", novaPosicao);

    return novaPosicao;
}




// Inserção de funcionário com tratamento de colisões para Função Hashing A
void inserirFuncionarioA(EntradaHash* vetorHash, int tamanhoVetor, const Funcionario* funcionario) {
    int posicao = funcaoHashA(funcionario->matricula, tamanhoVetor);

    printf("Inserindo na posicao: %d\n", posicao);

    if (vetorHash[posicao].dados != NULL) {
        vetorHash[posicao].colisoes++;

        printf("Colisao detectada! Tratando colisao...\n");

        posicao = tratarColisaoA(vetorHash, posicao, funcionario->matricula, tamanhoVetor);

        printf("Posicao ajustada apos tratamento de colisao: %d\n", posicao);
    }

    vetorHash[posicao].dados = (Funcionario*)malloc(sizeof(Funcionario));
    memcpy(vetorHash[posicao].dados, funcionario, sizeof(Funcionario));
    printf("Funcionario inserido com sucesso!\n\n");
}

// Função para gerar matrícula aleatória
void gerarMatricula(Funcionario* funcionario) {
    int digito1, digito2, digito3, digito4, digito5, digito6;

    // Garante que o primeiro dígito seja diferente de zero
    digito1 = 1 + rand() % 9; // Números de 1 a 9

    // Gera os demais dígitos de forma aleatória
    digito2 = rand() % 10;
    digito3 = rand() % 10;
    digito4 = rand() % 10;
    digito5 = rand() % 10;
    digito6 = rand() % 10;

    sprintf(funcionario->matricula, "%d%d%d%d%d%d", digito1, digito2, digito3, digito4, digito5, digito6);
}

// Impressão do número de colisões para Função Hashing A
void imprimirColisoesA(const EntradaHash* vetorHash, int tamanhoVetor) {
    printf("Numero de colisoes para Funcao Hashing A:\n");
    for (int i = 0; i < tamanhoVetor; i++) {
        printf("[%d]: %d colisoes\n", i, vetorHash[i].colisoes);
    }
}

// Liberação de memória do vetor hash para Função Hashing A
void liberarVetorHashA(EntradaHash* vetorHash, int tamanhoVetor) {
    for (int i = 0; i < tamanhoVetor; i++) {
        free(vetorHash[i].dados);
    }
    free(vetorHash);
}

int main() {
    int opcao;
    clock_t inicio, fim;
    srand(time(NULL));

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Vetor de 101 posicoes\n");
        printf("2 - Vetor de 150 posicoes\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                EntradaHash* vetorHash101A = (EntradaHash*)malloc(TAMANHO_VETOR_DESTINO_1 * sizeof(EntradaHash));
                memset(vetorHash101A, 0, TAMANHO_VETOR_DESTINO_1 * sizeof(EntradaHash));

                inicio = clock();

                for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
                    Funcionario funcionario;
                    gerarMatricula(&funcionario);
                    sprintf(funcionario.nome, "Funcionario%d", i);
                    sprintf(funcionario.funcao, "Cargo%d", i);
                    funcionario.salario = 5000.0 + (rand() % 5000) / 100.0;

                    inserirFuncionarioA(vetorHash101A, TAMANHO_VETOR_DESTINO_1, &funcionario);
                }

                fim = clock();

                printf("\nColisoes para vetor de 101 posicoes:\n");
                imprimirColisoesA(vetorHash101A, TAMANHO_VETOR_DESTINO_1);

                printf("Posicoes ocupadas no vetor:\n");
                for (int i = 0; i < TAMANHO_VETOR_DESTINO_1; i++) {
                    if (vetorHash101A[i].dados != NULL) {
                        printf("Posicao %d: Matricula: %s, Nome: %s, Funcao: %s, Salario: %.2f\n", i,
                               vetorHash101A[i].dados->matricula, vetorHash101A[i].dados->nome, vetorHash101A[i].dados->funcao,
                               vetorHash101A[i].dados->salario);
                    }
                }

                printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

                liberarVetorHashA(vetorHash101A, TAMANHO_VETOR_DESTINO_1);
                break;
            }
            case 2: {

                EntradaHash* vetorHash150A = (EntradaHash*)malloc(TAMANHO_VETOR_DESTINO_2 * sizeof(EntradaHash));
                memset(vetorHash150A, 0, TAMANHO_VETOR_DESTINO_2 * sizeof(EntradaHash));

                inicio = clock();

                for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
                    Funcionario funcionario;
                    gerarMatricula(&funcionario);
                    sprintf(funcionario.nome, "Funcionario%d", i);
                    sprintf(funcionario.funcao, "Cargo%d", i);
                    funcionario.salario = 5000.0 + (rand() % 5000) / 100.0;

                    inserirFuncionarioA(vetorHash150A, TAMANHO_VETOR_DESTINO_2, &funcionario);
                }

                fim = clock();

                printf("\nColisoes para vetor de 150 posicoes:\n");
                imprimirColisoesA(vetorHash150A, TAMANHO_VETOR_DESTINO_2);

                printf("\nPosicoes ocupadas no vetor de 150 posicoes:\n");
                for (int i = 0; i < TAMANHO_VETOR_DESTINO_2; i++) {
                    if (vetorHash150A[i].dados != NULL) {
                        printf("Posicao %d: Matricula: %s, Nome: %s, Funcao: %s, Salario: %.2f\n", i,
                               vetorHash150A[i].dados->matricula, vetorHash150A[i].dados->nome, vetorHash150A[i].dados->funcao,
                               vetorHash150A[i].dados->salario);
                    }
                }

                printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

                liberarVetorHashA(vetorHash150A, TAMANHO_VETOR_DESTINO_2);
                break;
            }
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
