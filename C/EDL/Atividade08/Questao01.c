#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define TAM 100

typedef struct noLSE{
    char nome[TAM];
    char email[50];
    char fone[20];
    struct noLSE* prox;
} TNoLSE;

typedef struct lseOrdenada{
    TNoLSE* inicio;
    TNoLSE* fim;
    int qtd;
} LSEOrdenada;

int isEmpty(LSEOrdenada lista){
    if(lista.qtd == 0){
        return TRUE;
    }else{
        return FALSE;
    }
}

void inicializar(LSEOrdenada* lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

TNoLSE* buscar(LSEOrdenada lista, char nome[]){
    TNoLSE* aux;
    if(isEmpty(lista) == TRUE){
        return NULL;
    }
    else{
        if(strcmp(lista.inicio->nome, nome) == 0){
            return lista.inicio;
        }
        else if(strcmp(lista.inicio->nome, nome) < 0){
            return NULL;
        }
        else if(strcmp(lista.fim->nome, nome) == 0){
            return lista.fim;
        }
        else if(strcmp(lista.fim->nome, nome) > 0){
            return NULL;
        }
        else{
            aux = lista.inicio->prox;
            while(aux != NULL){
                if(strcmp(aux->nome, nome) == 0){
                    return aux;
                }
                else if(strcmp(aux->nome, nome) > 0){
                    return NULL;
                }
                else{
                    aux = aux->prox;
                }
            }
        }
    }
}

void procurar(LSEOrdenada lista, char nome[]){
    if(isEmpty(lista) == TRUE){
        printf("Agenda vazia!\n");
    }
    else{
        TNoLSE* retorno = buscar(lista, nome);
        if(retorno == NULL){
            printf("Contato não cadastrado!\n");
        }
        else{
            printf("Fone: %s\n", retorno->fone);
            printf("Email: %s\n", retorno->email);
        }
    }
}

void alterar(LSEOrdenada lista, char nome[]){
    if(isEmpty(lista) == TRUE){
        printf("Agenda vazia!\n");
    }
    else{
        TNoLSE* retorno = buscar(lista, nome);
        if(retorno == NULL){
            printf("Contato não cadastrado!\n");
        }
        else{
            printf("Fone atual: %s\n", retorno->fone);
            printf("Digite o novo fone: ");
            fgets(retorno->fone, 20, stdin);
            printf("E-mail atual: %s\n", retorno->email);
            printf("Digite o novo e-mail: ");
            fgets(retorno->email, 50, stdin);
        }
    }
}

void inserir(LSEOrdenada* lista, char nome[TAM]){
    TNoLSE* anterior = NULL, *atual = NULL, *novo;

    if(isEmpty(*lista) == TRUE){
        novo = (TNoLSE*)malloc(sizeof(TNoLSE));
        novo->prox = NULL;
        strcpy(novo->nome, nome);
        printf("Digite o e-mail: ");
        fgets(novo->email, 50, stdin);
        printf("Digite o fone: ");
        fgets(novo->fone, 20, stdin);
        lista->inicio = novo;
        lista->fim = novo;
        lista->qtd = 1;
        printf("Contato adicionado!\n");
    }
    else{
        if(strcmp(lista->inicio->nome, nome) == 0 || strcmp(lista->fim->nome, nome) == 0){
            printf("Contato já cadastrado!\n");
        }
        else if(strcmp(lista->inicio->nome, nome) < 0){
            novo = (TNoLSE*)malloc(sizeof(TNoLSE));
            novo->prox = NULL;
            strcpy(novo->nome, nome);
            printf("Digite o e-mail: ");
            fgets(novo->email, 50, stdin);
            printf("Digite o fone: ");
            fgets(novo->fone, 20, stdin);
            novo->prox = lista->inicio;
            lista->inicio = novo;
            lista->qtd++;
            printf("Contato adicionado!\n");
        }
        else if(strcmp(lista->fim->nome, nome) > 0){
            novo = (TNoLSE*)malloc(sizeof(TNoLSE));
            novo->prox = NULL;
            strcpy(novo->nome, nome);
            printf("Digite o e-mail: ");
            fgets(novo->email, 50, stdin);
            printf("Digite o fone: ");
            fgets(novo->fone, 20, stdin);
            lista->fim->prox = novo;
            lista->fim = novo;
            lista->qtd++;
            printf("Contato adicionado!\n");
        }
        else{
            anterior = lista->inicio;
            atual = lista->inicio->prox;

            while(atual != NULL){
                if(strcmp(atual->nome, nome) == 0){
                    printf("Contato já cadastrado!\n");
                    break;
                }
                else if(strcmp(atual->nome, nome) > 0){
                    anterior = atual;
                    atual = atual->prox;
                }
                else{
                    novo = (TNoLSE*)malloc(sizeof(TNoLSE));
                    novo->prox = NULL;
                    strcpy(novo->nome, nome);
                    printf("Digite o email: ");
                    fgets(novo->email, 50, stdin);
                    printf("Digite o fone: ");
                    fgets(novo->fone, 20, stdin);
                    novo->prox = atual;
                    anterior->prox = novo;
                    lista->qtd++;
                    printf("Contato adicionado!\n");
                    break;
                }
            }
        }
    }
}

void remover(LSEOrdenada* lista, char nome[TAM]){
    TNoLSE* anterior, *atual;
    
    if(isEmpty(*lista) == TRUE){
        printf("Agenda vazia!");
    }
    else if(strcmp(lista->inicio->nome, nome) == 0){
        atual = lista->inicio;
        lista->inicio = lista->inicio->prox;
        free(atual);
        if(lista->inicio == NULL){
            lista->fim = NULL;
        }
        lista->qtd--;
    }
    else{
        anterior = lista->inicio;
        atual = lista->inicio->prox;

        while(atual != NULL){
            if(strcmp(atual->nome, nome) == 0){
                anterior->prox = atual->prox;
                free(atual);
                lista->qtd--;
            }
            else{
                anterior = atual;
                atual = atual->prox;
            }
        }
    }
}

void exibir(LSEOrdenada lista){
    TNoLSE* aux;

    if(isEmpty(lista) == TRUE){
        printf("Agenda vazia!\n");
    }
    else{
        aux = lista.inicio;

        while(aux != NULL){
        printf("Nome: %s\n", aux->nome);
        printf("E-mail: %s\n", aux->email);
        printf("Fone: %s\n", aux->fone);
        printf("\n");
        aux = aux->prox;
        }
    }
}

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 – Cadastrar novo contato \n");
    printf("2 – Remover contato \n");
    printf("3 – Procurar contato \n");
    printf("4 – Alterar dados do contato \n");
    printf("5 – Exibir todos os contatos \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    LSEOrdenada agenda;
    inicializar(&agenda);
    int op;
    char nome[TAM];
    do {
        exibirOpcoes();
        scanf("%d",&op);
        limpaBuffer();
        switch (op) {
            case 1: printf("Informe o nome do contato: ");
                fgets(nome, TAM, stdin);
                inserir(&agenda, nome);
                break;
            case 2: printf("Informe o nome do contato: ");
                fgets(nome, TAM, stdin);
                remover(&agenda, nome);
                break;
            case 3: printf("Informe o nome do contato: ");
                fgets(nome, TAM, stdin);
                procurar(agenda, nome);
                break;
            case 4: printf("Informe o nome do contato: ");
                fgets(nome, TAM, stdin);
                alterar(agenda, nome);
                break;
            case 5:
                exibir(agenda);
                break;
            case 0: printf("Fim de programa! \n");
                break;
            default: printf("Opção inválida! \n");
        }
    } while (op != 0);
    return 0;
}