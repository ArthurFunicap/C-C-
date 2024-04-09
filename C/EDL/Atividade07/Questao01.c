#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct NoLSE{
    int info;
    struct NoLSE* prox;
} TNoLSE;

typedef struct LseInt{
    TNoLSE* inicio;
    TNoLSE* fim;
    int qtd;
}LSEInteiros;

void inicializar(LSEInteiros* lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(LSEInteiros lista){
    if(lista.qtd == 0)
        return TRUE;
    else
        return FALSE;
}

void inserir(LSEInteiros* lista, int valor){
    TNoLSE* novo, *anterior, *atual;

    if(isEmpty(*lista)){
        novo = (TNoLSE*)malloc(sizeof(TNoLSE));
        novo->info = valor;
        novo->prox = NULL;
        lista->inicio = novo;
        lista->fim = novo;
        lista->qtd = 1;
        printf("Inserção efetuada!\n");
    }else if(valor < lista->inicio->info){
        novo = (TNoLSE*)malloc(sizeof(TNoLSE));
        novo->info = valor;
        novo->prox = lista->inicio;
        lista->inicio = novo;
        lista->qtd++;
        printf("Inserção efetuada!\n");
    }else if(valor == lista->inicio->info){
        printf("Valor repetido. Inserção não efetuada!\n");
    }else if(valor > lista->fim->info){
        novo = (TNoLSE*)malloc(sizeof(TNoLSE));
        novo->info = valor;
        novo->prox = NULL;
        lista->fim->prox = novo;
        lista->fim = novo;
        lista->qtd++;
        printf("Inserção efetuada!\n");
    }else if(valor == lista->fim->info){
        printf("Valor repetido. Inserção não efetuada!\n");
    }else{
        anterior = lista->inicio;
        atual = anterior->prox;
        while(TRUE){
            if(valor == atual->info){
                printf("Valor repetido. Inserção não efetuada!\n");
                break;
            }else if(atual->info > valor){
                novo = (TNoLSE*)malloc(sizeof(TNoLSE));
                novo->info = valor;
                anterior->prox = novo;
                novo->prox = atual;
                lista->qtd++;
                printf("Inserção efetuada!\n");
                break;
            }else{
                atual = atual->prox;
                anterior = anterior->prox;
            }
        }
    }
}

int remover(LSEInteiros* lista, int num){
    TNoLSE* anterior, *atual, *aux;
    int resultado = 0;

    anterior = (TNoLSE*)malloc(sizeof(TNoLSE));
    atual = (TNoLSE*)malloc(sizeof(TNoLSE));
    aux = (TNoLSE*)malloc(sizeof(TNoLSE));

    aux = lista->inicio;

    atual = lista->inicio;
    anterior = NULL;

    while(atual != NULL){
        if(num == atual->info){
            resultado = 1;
            if(anterior == NULL){
                anterior = atual->prox;
                lista->inicio = anterior;
            }else{
                anterior->prox = atual->prox;
                lista->inicio = aux;
            }

            if(atual == lista->fim){
                lista->fim = anterior;
            }

            lista->qtd--;
            
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return resultado;
}

void listar(LSEInteiros* lista){
    TNoLSE* aux;
    aux = (TNoLSE*)malloc(sizeof(TNoLSE));

    aux = lista->inicio;

    printf("Valores na LSE:\n");
    while(lista->inicio != NULL){
        printf("%d\n", lista->inicio->info);
        lista->inicio = lista->inicio->prox;
    }

    lista->inicio = aux;
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 – Inserir valor\n");
    printf("2 – Remover valor\n");
    printf("3 – Exibir lista\n");
    printf("0 -Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main(){
    LSEInteiros listaInteiros;
    int opcao, valor, verificador;

    inicializar(&listaInteiros);
    do{
        exibirOpcoes();
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &valor);
                inserir(&listaInteiros, valor);
                break;
            case 2:
                if(isEmpty(listaInteiros) == 0){
                    printf("Digite o valorq ue deseja remover: ");
                    scanf("%d", &valor);
                    verificador = remover(&listaInteiros, valor);
                    if(verificador == 1){
                        printf("Valor removido com sucesso!\n");
                    }else{
                        printf("Valor não encontrado!\n");
                    }
                }else{
                    printf("Lista vazia!\n");
                }
                break;
            case 3:
                if(isEmpty(listaInteiros) == 0){
                    listar(&listaInteiros);
                }else{
                    printf("Lista vazia!\n");
                }
                break;
            case 0:
                printf("Programa encerrado!\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }while(opcao != 0);
}