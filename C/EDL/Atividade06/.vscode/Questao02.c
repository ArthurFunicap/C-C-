#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* pedidoPronto;
int i = 1;

typedef struct noQueue{
    int numero;
    char descricao[35];
    struct noQueue* prox;
} TNoQueue;

typedef struct queue{
    TNoQueue* inicio, * fim;
} Queue;

void inicializar(Queue* fila){
    fila->inicio = NULL;
    fila->fim = NULL;
}

void enqueue(Queue* fila, char* pedido){
    TNoQueue* novo;
    novo = (TNoQueue*)malloc(sizeof(TNoQueue));

    novo->numero = i;
    strcpy(novo->descricao, pedido);
    novo->prox = NULL;

    if(fila->inicio == NULL){
        fila->inicio = novo;
        fila->fim = novo;
    }else{
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    i++;
}

int dequeue(Queue* fila){
    TNoQueue* aux;
    int numero;

    aux = (TNoQueue*)malloc(sizeof(TNoQueue));
    aux = fila->inicio;
    numero = fila->inicio->numero;
    pedidoPronto = (char*)malloc(sizeof(strlen(fila->inicio->descricao)));
    strcpy(pedidoPronto, fila->inicio->descricao);

    fila->inicio = fila->inicio->prox;
    free(aux);

    if(fila->inicio == NULL)
        fila->fim = NULL;
    
    return numero;
}

void head(Queue fila){
    printf("Pedido no inicio da fila:\n");
    printf("Numero: %d\n", fila.inicio->numero);
    printf("Descrição: %s\n", fila.inicio->descricao);
}

int isFull(Queue* fila){
    return 0;
}

int isEmpty(Queue* fila){
    if(fila->inicio == NULL && fila->fim == NULL)
        return 1;
    else
        return 0;
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Adicionar pedido \n");
    printf("2 - Pedido pronto \n");
    printf("3 - Head \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main(){
    Queue minhaFila;
    int opcao;
    char desc[35];

    inicializar(&minhaFila);

    do{
        exibirOpcoes();
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            if(isFull(&minhaFila) == 0){
                printf("Digite a descrição do pedido: ");
                scanf("%s", desc);
                enqueue(&minhaFila, desc);
                printf("Pedido adicionado à lista!\n\n");
            }else{
                printf("Fila cheia!\n\n");
            }
            break;
        case 2:
            if(isEmpty(&minhaFila) == 0){
                printf("Pedido pronto:\n");
                printf("Número: %d\n", dequeue(&minhaFila));
                printf("Descrição: %s\n\n", pedidoPronto);
            }else{
                printf("A fila está vazia!\n\n");
            }
            break;
        case 3:
            if(isEmpty(&minhaFila) == 0){
                head(minhaFila);
                printf("\n");
            }else{
                printf("A fila está vazia!\n\n");
            }
            break;
        case 0:
            printf("Programa encerrado!\n");
            break;
        default:
            printf("Opção inválido!\n");
            break;
        }
    } while (opcao != 0);
    
}