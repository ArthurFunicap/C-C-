// Esboço do código de uma Stack de números inteiros implementada utilizando o conceito de lista encadeada.
// Implementar as partes do código que estão incompletas.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct noPilha {
    int info;
    struct noPilha* prox;
} TNoPilha;
typedef TNoPilha* Stack;

void inicializar(Stack* pilha) {
    *pilha = NULL;
}

void push(Stack* pilha, int valor) { // empilhar
    TNoPilha* novo;
    novo = (TNoPilha*)malloc(sizeof(TNoPilha));

    novo->info = valor;
    novo->prox = *pilha;
    *pilha = novo;
}

int pop(Stack* pilha) {  // desempilhar
    Stack aux;
    int valor;

    valor = (*pilha)->info;
    aux = *pilha;

    *pilha = (*pilha)->prox;

    free(aux);

    return valor;
}

int top(Stack pilha) {   // retornar o valor que está no topo
    return pilha->info;
}

int isFull(Stack pilha) {  // checa se a pilha está cheia
    return 0;
}

int isEmpty(Stack pilha) { // checa se a pilha está vazia
    if(pilha == NULL)
        return 1;
    else
        return 0;
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Push \n");
    printf("2 - Pop \n");
    printf("3 - Top \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main()
{
    Stack minhaPilha;
    inicializar(&minhaPilha);
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
        case 1: printf("Informe o valor: ");
            scanf("%d", &num);
            if (isFull(minhaPilha) == 0) {
                push(&minhaPilha, num);
                printf("Valor empilhado!\n");
            }
            else {
                printf("Stack full\n");
            }
            break;
        case 2: if(isEmpty(minhaPilha) == 1)
                printf("A pilha está vazia!\n");
            else
                printf("Valor desempilhado: %d\n", pop(&minhaPilha));
            break;
        case 3: if(isEmpty(minhaPilha) == 1)
                printf("A pilha está vazia!\n");
            else
                printf("Valor no topo da pilha: %d\n", top(minhaPilha));
            break;
        case 0: printf("Fim de programa!\n");
            break;
        default: printf("Opção inválida!\n");
        }
    } while (op != 0);
    return 0;
}
