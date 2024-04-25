#include <stdio.h>
#include <stdlib.h>

typedef struct noLSE{
    int valor;
    struct noLSE* prox;
}TNoLSE;

typedef struct lseOrdenada{
    TNoLSE* inicio;
    TNoLSE* fim;
    int qtd;
}LSEOrdenada;

void inicializar(LSEOrdenada* lista1, LSEOrdenada* lista2, LSEOrdenada* lista3){
    lista1->inicio = NULL;
    lista1->fim = NULL;
    lista1->qtd = 0;

    lista2->inicio = NULL;
    lista2->fim = NULL;
    lista2->qtd = 0;

    lista3->inicio = NULL;
    lista3->fim = NULL;
    lista3->qtd = 0;
}

int isEmpty(LSEOrdenada lista){
    if(lista.inicio == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void inserir(LSEOrdenada* lista, int valor){
    TNoLSE* novo = (TNoLSE*)malloc(sizeof(TNoLSE));

    novo->valor = valor;
    novo->prox = NULL;

    if(isEmpty(*lista) == 1){
        lista->inicio = novo;
        lista->fim = novo;
        lista->qtd = 1;
        printf("Valor adicionado!\n");
    }
    else{
        lista->fim->prox = novo;
        lista->fim = novo;
        lista->qtd++;
        printf("Valor adicionado!\n");
    }
}

void somar(LSEOrdenada* lista1, LSEOrdenada* lista2, LSEOrdenada* lista3){
    TNoLSE* aux1, *aux2, *novo;

    if(isEmpty(*lista1) == 1 && isEmpty(*lista2) == 1){
        printf("As listas 1 e 2 estão vazias!\n");
    }
    else{
        aux1 = lista1->inicio;
        aux2 = lista2->inicio;

        novo = (TNoLSE*)malloc(sizeof(TNoLSE));
        novo->valor = 0;
        novo->prox = NULL;

        novo->valor = aux1->valor + aux2->valor;
        lista3->inicio = novo;
        lista3->fim = novo;
        lista3->qtd = 1;

        aux1 = aux1->prox;
        aux2 = aux2->prox;

        if(lista1->qtd > lista2->qtd){
            while(aux1 != NULL){
                novo = (TNoLSE*)malloc(sizeof(TNoLSE));
                novo->valor = 0;
                novo->prox = NULL;

                if(aux2 != NULL){
                    novo->valor = aux1->valor + aux2->valor;
                    lista3->fim->prox = novo;
                    lista3->fim = novo;
                    lista3->qtd++;
                    aux1 = aux1->prox;
                    aux2 = aux2->prox;
                }
                else{
                    novo->valor = aux1->valor;
                    lista3->fim->prox = novo;
                    lista3->fim = novo;
                    lista3->qtd++;
                    aux1 = aux1->prox;
                }
            }
        }
        else{
            while(aux2 != NULL){
                novo = (TNoLSE*)malloc(sizeof(TNoLSE));
                novo->valor = 0;
                novo->prox = NULL;

                if(aux1 != NULL){
                    novo->valor = aux1->valor + aux2->valor;
                    lista3->fim->prox = novo;
                    lista3->fim = novo;
                    lista3->qtd++;
                }
                else{
                    novo->valor = aux2->valor;
                    lista3->fim->prox = novo;
                    lista3->fim = novo;
                    lista3->qtd++;
                }
                aux1 = aux1->prox;
                aux2 = aux2->prox;
            }
        }
    }
    printf("Soma concluída!\n");
}

void exibir(LSEOrdenada* lista){
    TNoLSE* aux;
    aux = lista->inicio;

    printf("Valores: ");

    while(aux != NULL){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
    printf("\n");
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 – Inserir valor na lista 1 \n");
    printf("2 – Inserir valor na lista 2 \n");
    printf("3 – Somar \n");
    printf("4 – Exibir lista 1 \n");
    printf("5 – Exibir lista 2 \n");
    printf("6 - Exibir lista de soma \n");
    printf("0 - Encerrar programa\n");
    printf("Informe a opção desejada: ");
}

int main(){
    LSEOrdenada listaUm, listaDois, listaSoma;
    inicializar(&listaUm, &listaDois, &listaSoma);
    int op, num;

    do{
        exibirOpcoes();
        scanf("%d", &op);

        switch (op){
        case 1:
            printf("Informe um valor: ");
            scanf("%d", &num);
            inserir(&listaUm, num);
            break;
        case 2:
            printf("Informe um valor: ");
            scanf("%d", &num);
            inserir(&listaDois, num);
            break;
        case 3:
            if(isEmpty(listaSoma) == 1){
                somar(&listaUm, &listaDois, &listaSoma);
            }
            else{
                printf("A lista de soma não está vazia!\n");
            }
            break;
        case 4:
            if(isEmpty(listaUm) == 1){
                printf("A lista 1 está vazia!\n");
            }
            else{
                exibir(&listaUm);
            }
            break;
        case 5:
            if(isEmpty(listaDois) == 1){
                printf("A lista 2 está vazia!\n");
            }
            else{
                exibir(&listaDois);
            }
            break;
        case 6:
            if(isEmpty(listaSoma) == 1){
                printf("A lista 1 está vazia!\n");
            }
            else{
                exibir(&listaSoma);
            }
            break;
        case 0:
            printf("FIm de programa!\n");
            break;
        default:
            printf("Valor inválido!\n");
            break;
        }
    }while(op != 0);
}