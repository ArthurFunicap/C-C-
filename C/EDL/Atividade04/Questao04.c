// Esboço do código de uma Queue de números inteiros implementada utilizando o conceito de lista encadeada.
// Implementar as partes do código que estão incompletas.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct noQueue {
    int info;
    struct noQueue* prox;
}TNoQueue;

typedef struct queue {
    TNoQueue* inicio, * fim;
} Queue;

void inicializar(Queue* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void enqueue(Queue* fila, int valor) { // enfileirar
    TNoQueue* novo;
    novo = (TNoQueue*)malloc(sizeof(TNoQueue));

    novo->info = valor;
    novo->prox = NULL;

    if(fila->inicio == NULL){
        fila->inicio = novo;
        fila->fim = novo;
    } else{
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

int dequeue(Queue* fila) {  // desenfileirar
    TNoQueue* aux;
    int valor, i;

    valor = fila->inicio->info;
    aux = fila->inicio;
 
    fila->inicio = fila->inicio->prox;

    free(aux);

    if(fila->inicio == NULL)
        fila->fim = NULL;
    
    return valor;
}

int head(Queue fila) {   // retornar o valor que está no início da fila
    return fila.inicio->info;
}

int isFull(Queue fila) { // checa se a fila está cheia
    return 0;
}

int isEmpty(Queue fila) { // checa se a fila está vazia
    if(fila.inicio == NULL && fila.fim == NULL)
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
        case 2: if(isEmpty(minhaFila) == 1)
                printf("Fila vazia!\n");
                else
                printf("Valor desenfileirado: %d\n", dequeue(&minhaFila));
            break;
        case 3: if(isEmpty(minhaFila) == 1) 
                printf("A fila está vazia!\n");
                else
                printf("Valor que está no inicio da fila: %d\n", head(minhaFila));
            break;
        case 0: printf("Fim de programa!\n");
            break;
        default: printf("Opção inválida!\n");
            break;
        }
    } while (op != 0);
    return 0;
}