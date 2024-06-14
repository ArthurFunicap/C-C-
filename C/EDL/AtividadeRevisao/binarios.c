// Aula de reposição - 21-05-2024
// Exercício de revisão de manipulação de arquivos binários

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
    char ra[12];
    char nome[100];
    float media;
    int faltas;
    int status;
} TAluno;

void exibirOpcoes() {
    printf("1 - Cadastrar aluno \n");
    printf("2 - Exibir alunos cadastrados \n");
    printf("3 - Exibir os dados de um aluno \n");
    printf("4 - Alterar a média de um aluno \n");
    printf("5 - Alterar a quantidade de faltas de um aluno \n");
    printf("6 - Remover um aluno do cadastro \n");
    printf("0 - Encerrar o programa \n");
}

FILE* prepararArquivo(char nomeArq[]) {
    FILE* arq;
    arq = fopen(nomeArq, "r+b");
    if (arq == NULL) {
        arq = fopen(nomeArq, "w+b");
    }
    return arq;
}

void cadastrarAluno (FILE* arq) {
    TAluno novoAluno;

    char ra[12];
    printf("Digite o RA do aluno: ");
    fgets(ra, 12, stdin);
    strcpy(novoAluno.ra, ra);

    char nome[12];
    printf("Digite o nome do aluno: ");
    fgets(nome, 100, stdin);
    strcpy(novoAluno.nome, nome);

    float media;
    printf("Digite a média do aluno: ");
    scanf("%f", &media);
    novoAluno.media = media;

    int faltas;
    printf("Digite a qtd. de faltas do aluno: ");
    scanf("%d", &faltas);
    novoAluno.faltas = faltas;

    novoAluno.status = 1;

    fseek(arq, sizeof(TAluno), SEEK_END);
    fwrite(&novoAluno, sizeof(TAluno), 1, arq);
}

void exibirTodos (FILE* arq) {
    TAluno aluno;

    rewind(arq);

    printf("Dados dos alunos:\n");
    while(fread(&aluno, sizeof(TAluno), 1, arq)){
        printf("RA: %s\n", aluno.ra);
        printf("Nome: %s\n", aluno.nome);
        printf("Média: %.2f\n", aluno.media);
        printf("Faltas: %d\n", aluno.faltas);
        printf("\n");
    }
}

void exibirAluno(FILE* arq, char ra[]) {
    TAluno aluno;

    int status = 0;

    rewind(arq);

    while(fread(&aluno, sizeof(TAluno), 1, arq)){
        if(strcmp(aluno.ra, ra) == 0){
            printf("Nome: %s\n", aluno.nome);
            printf("Média: %.2f\n", aluno.media);
            printf("Faltas: %d\n", aluno.faltas);
            status = 1;
            break;
        }
    }

    if(status == 0){
        printf("O aluno não pertence à turma!\n");
    }
}

void alterarMedia(FILE* arq, char ra[]) {
    TAluno aluno;

    int status = 0;
    float media;

    rewind(arq);

    while(fread(&aluno, sizeof(TAluno), 1, arq)){
        if(strcmp(aluno.ra, ra) == 0){
            printf("Digite a nova média do aluno: ");
            scanf("%f", &media);
            
            aluno.media = media;

            fseek(arq, -sizeof(TAluno), SEEK_CUR);
            fwrite(&aluno, sizeof(TAluno), 1, arq);

            status = 1;
            break;
        }
    }

    if(status == 0){
        printf("O aluno não pertence à turma!\n");
    }

    printf("Média alterada\n");
}

void alterarFaltas(FILE* arq, char ra[]) {
    TAluno aluno;

    int status = 0;
    int faltas;

    rewind(arq);

    while(fread(&aluno, sizeof(TAluno), 1, arq)){
        if(strcmp(aluno.ra, ra) == 0){
            printf("Digite a nova qtd. de faltas do aluno: ");
            scanf("%d", &faltas);
            
            aluno.faltas = faltas;

            fseek(arq, -sizeof(TAluno), SEEK_CUR);
            fwrite(&aluno, sizeof(TAluno), 1, arq);

            status = 1;
            break;
        }
    }

    if(status == 0){
        printf("O aluno não pertence à turma!\n");
    }

    printf("Qtd. de faltas alteradas\n");
}

void removerAluno(FILE* arq, char ra[]) {
    TAluno aluno;

    int status = 0;
    
    rewind(arq);

    while(fread(&aluno, sizeof(TAluno), 1, arq)){
        if(strcmp(aluno.ra, ra) == 0){
            aluno.status = 0;

            fseek(arq, -sizeof(TAluno), SEEK_CUR);
            fwrite(&aluno, sizeof(TAluno), 1, arq);

            status = 1;
            break;
        }
    }

    if(status == 0){
        printf("O aluno não pertence à turma!\n");
    }

    printf("Aluno removido!\n");    
}

void limparArquivo(FILE* arq) {
    FILE* novo;
    TAluno aluno;

    novo = prepararArquivo("aux.dat");

    rewind(arq);

    while(fread(&aluno, sizeof(TAluno), 1, arq)){
        if(aluno.status == 1){
            fseek(novo, sizeof(TAluno), SEEK_END);
            fwrite(&aluno, sizeof(TAluno), 1, novo);
        }
    }

    fclose(novo);
    fclose(arq);

    remove(arq);
    rename("aux.dat", "prog1.dat");
}

int main() {
    FILE* turma;
    char nomeFile[100] = "prog1.dat";
    char ra [12];
    int op;
    turma = prepararArquivo (nomeFile);
    if (turma == NULL) {
        printf("Erro ao tentar criar/abrir o arquivo \n");
    }
    else { 
        do {
            exibirOpcoes();
            scanf("%d", &op); fflush(stdin);
            switch (op) {
            case 1: cadastrarAluno(turma);
                break;
            case 2: exibirTodos(turma);
                break;
            case 3: printf("Informe o RA do aluno: ");
                gets_s(ra); fflush(stdin);
                exibirAluno(turma, ra);
                break;
            case 4: printf("Informe o RA do aluno: ");
                gets_s(ra); fflush(stdin);
                alterarMedia(turma, ra);
                break;
            case 5: printf("Informe o RA do aluno: ");
                gets_s(ra); fflush(stdin);
                alterarFaltas(turma, ra);
                break;
            case 6: printf("Informe o RA do aluno: ");
                gets_s(ra); fflush(stdin);
                removerAluno(turma, ra);
                break;
            case 0: limparArquivo(turma);
                break;
            default: printf("Opção inválida \n");
            }
        } while (op != 0);
    }
    return 0;
}