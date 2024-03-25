// Esboço do código de uma Queue de números inteiros implementada utilizando utilizando uma estrutura sequencial (vetor).
// Implementar as partes do código que estão incompletas.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define TAM  10
typedef struct queue {
    int dados[TAM];
    int inicio, fim;
} Queue;

void inicializar(Queue* fila) {
    int i;
    fila->inicio = -1;
    fila->fim = -1;
    for (i = 0; i < TAM; i++) {
        fila->dados[i] = 0;
    }
}

void enqueue(Queue* fila, int valor) { // enfileirar
        if(fila->inicio != 0){
            fila->inicio++;
            fila->fim++;
            fila->dados[(*fila).inicio] = valor;
        } else{
            fila->fim++;
            fila->dados[(*fila).fim] = valor;
        }
}

int dequeue(Queue* fila) {  // desenfileirar
    int aux, i = 0, j = 1;
    int valor;

    valor = fila->dados[(*fila).inicio];

    if(fila->fim == 0){
        fila->dados[fila->fim] = 0;
    } else{
        while(i < fila->fim){
            fila->dados[i] = 0;
            fila->dados[i] = fila->dados[j];
            i++;
            j++;
        }
    }

    fila->fim--;

    if(fila->fim == -1){
        fila->inicio = -1;
    }

    return valor;
}

int head(Queue fila) {   // retornar o valor que está no início da fila
    return fila.dados[fila.inicio];
}

int isFull(Queue fila) { // checa se a fila está cheia
    if(fila.fim == TAM - 1)
        return 1;
    else
        return 0;
}

int isEmpty(Queue fila) { // checa se a fila está vazia
    if(fila.inicio == -1)
        return 1;
    else
        return 0;
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Enqueue \n");
    printf("2 - Dequeue \n");
    printf("3 - Head \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main()
{
    Queue minhaFila;
    inicializar(&minhaFila);
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
        case 1: printf("Informe o valor: ");
            scanf("%d", &num);
            if (isFull(minhaFila) == 0) {
                enqueue(&minhaFila, num);
                printf("Valor enfileirado!\n");
            }
            else {
                printf("Queue full!\n");
            }
            break;
        case 2: if(isEmpty(minhaFila) != 1)
                    printf("Valor desenfileirado: %d\n", dequeue(&minhaFila));
                else
                    printf("A fila está vazia!\n");
            break;
        case 3: if(isEmpty(minhaFila) != 1)
                    printf("Valor no inicio da fila: %d\n", head(minhaFila));
                else
                    printf("A fila está vazia!\n");
            break;
        case 0: printf("Fim de programa!\n");
            break;
        default: printf("Opção inválida!\n");
        }
    } while (op != 0);
    return 0;
}