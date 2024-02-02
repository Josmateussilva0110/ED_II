#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_VETOR_DESTINO_1 101
#define TAMANHO_VETOR_DESTINO_2 150
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

int funcaoHashB(const char* matricula, int tamanhoVetor) {
    int posicao;

    // Extrair os dois números de três dígitos
    int numero1 = (matricula[0] - '0') * 100 + (matricula[2] - '0') * 10 + (matricula[5] - '0');
    int numero2 = (matricula[1] - '0') * 100 + (matricula[3] - '0') * 10 + (matricula[4] - '0');

    // Aplicar a fórmula de folding shift nos dois números
    posicao = ((numero1 + numero2)) % tamanhoVetor;

    // Imprimir os números extraídos
    printf("Numeros extraidos: %d %d\n", numero1, numero2);

    printf("Matricula: %s\n", matricula);
    printf("Posicao calculada pela funcaoHashB: %d\n\n", posicao);

    return posicao;
}

// Tratamento de colisões para Função Hashing B Adaptada
int tratarColisaoB(EntradaHash* vetorHash, int posicao, int tamanhoVetor) {
    int offset = 7;
    int novaPosicao = (posicao + offset) % tamanhoVetor;
    int primeiraPosicaoOcupada = -1; // Marcador para a primeira posição ocupada

    printf("Tratamento de colisao B:\n");
    printf("Posicao original: %d\n", posicao);
    printf("Offset: %d\n", offset);

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

// Inserção de funcionário com tratamento de colisões para Função Hashing B Adaptada
void inserirFuncionarioB(EntradaHash* vetorHash, int tamanhoVetor, const Funcionario* funcionario) {
    int posicao = funcaoHashB(funcionario->matricula, tamanhoVetor);

    printf("Inserindo na posicao: %d\n", posicao);

    if (vetorHash[posicao].dados != NULL) {
        printf("Colisao detectada! Tratando colisao...\n");
        vetorHash[posicao].colisoes++;
        posicao = tratarColisaoB(vetorHash, posicao, tamanhoVetor);
        printf("Posicao ajustada apos tratamento de colisao: %d\n", posicao);
    }

    vetorHash[posicao].dados = (Funcionario*)malloc(sizeof(Funcionario));
    memcpy(vetorHash[posicao].dados, funcionario, sizeof(Funcionario));
    printf("Funcionario inserido com sucesso!\n\n");
}


// Impressão do número de colisões para Função Hashing B
void imprimirColisoesB(const EntradaHash* vetorHash, int tamanhoVetor) {
    printf("Numero de colisoes para Funcao Hashing B:\n");
    for (int i = 0; i < tamanhoVetor; i++) {
        printf("[%d]: %d colisoes\n", i, vetorHash[i].colisoes);
    }
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

// Liberação de memória do vetor hash para Função Hashing B
void liberarVetorHashB(EntradaHash* vetorHash, int tamanhoVetor) {
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
        printf("1 - Vetor de 101 posicoes (Funcao Hashing B)\n");
        printf("2 - Vetor de 150 posicoes (Funcao Hashing B)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                // Função Hashing B
                EntradaHash* vetorHash101B = (EntradaHash*)malloc(TAMANHO_VETOR_DESTINO_1 * sizeof(EntradaHash));
                memset(vetorHash101B, 0, TAMANHO_VETOR_DESTINO_1 * sizeof(EntradaHash));

                inicio = clock();

                for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
                    Funcionario funcionario;
                    gerarMatricula(&funcionario);
                    sprintf(funcionario.nome, "Funcionario%d", i);
                    sprintf(funcionario.funcao, "Cargo%d", i);
                    funcionario.salario = 5000.0 + (rand() % 5000) / 100.0;

                    inserirFuncionarioB(vetorHash101B, TAMANHO_VETOR_DESTINO_1, &funcionario);
                }

                fim = clock();

                printf("\nColisoes para vetor de 101 posicoes (Funcao Hashing B):\n");
                imprimirColisoesB(vetorHash101B, TAMANHO_VETOR_DESTINO_1);

                printf("Posicoes ocupadas no vetor (Funcao Hashing B):\n");
                for (int i = 0; i < TAMANHO_VETOR_DESTINO_1; i++) {
                    if (vetorHash101B[i].dados != NULL) {
                        printf("Posicao %d: Matricula: %s, Nome: %s, Funcao: %s, Salario: %.2f\n", i,
                               vetorHash101B[i].dados->matricula, vetorHash101B[i].dados->nome, vetorHash101B[i].dados->funcao,
                               vetorHash101B[i].dados->salario);
                    }
                }

                printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

                liberarVetorHashB(vetorHash101B, TAMANHO_VETOR_DESTINO_1);
                break;
            }
            case 2: {
                // Função Hashing B
                EntradaHash* vetorHash150B = (EntradaHash*)malloc(TAMANHO_VETOR_DESTINO_2 * sizeof(EntradaHash));
                memset(vetorHash150B, 0, TAMANHO_VETOR_DESTINO_2 * sizeof(EntradaHash));

                inicio = clock();

                for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
                    Funcionario funcionario;
                    gerarMatricula(&funcionario);
                    sprintf(funcionario.nome, "Funcionario%d", i);
                    sprintf(funcionario.funcao, "Cargo%d", i);
                    funcionario.salario = 5000.0 + (rand() % 5000) / 100.0;

                    inserirFuncionarioB(vetorHash150B, TAMANHO_VETOR_DESTINO_2, &funcionario);
                }

                fim = clock();

                printf("\nColisoes para vetor de 150 posicoes (Funcao Hashing B):\n");
                imprimirColisoesB(vetorHash150B, TAMANHO_VETOR_DESTINO_2);

                printf("Posicoes ocupadas no vetor (Funcao Hashing B):\n");
                for (int i = 0; i < TAMANHO_VETOR_DESTINO_2; i++) {
                    if (vetorHash150B[i].dados != NULL) {
                        printf("Posicao %d: Matricula: %s, Nome: %s, Funcao: %s, Salario: %.2f\n", i,
                               vetorHash150B[i].dados->matricula, vetorHash150B[i].dados->nome, vetorHash150B[i].dados->funcao,
                               vetorHash150B[i].dados->salario);
                    }
                }

                printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

                liberarVetorHashB(vetorHash150B, TAMANHO_VETOR_DESTINO_2);
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
