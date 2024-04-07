#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Arquivos {
    char nomeArquivo[25];
    struct Arquivos* prox;
} Arquivo;

typedef struct ArquivoFila {
    Arquivo* inicio, * fim;
} Fila;

void inicializar(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Push \n");
    printf("2 - Pop \n");
    printf("3 - Head \n");
    printf("4 - Cancel\n");
    printf("5 - List\n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int isFull(Fila fila) {
    return 0;
}

int isEmpty(Fila fila) {
    if (fila.inicio == NULL && fila.fim == NULL)
        return 1;
    else
        return 0;
}

void enqueue(Fila* fila, char* nome) {
    Arquivo* novo;
    novo = (Arquivo*)malloc(sizeof(Arquivo));

    strcpy(novo->nomeArquivo, nome);
    novo->prox = NULL;

    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    }
    else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

char* dequeue(Fila* fila){
    Arquivo* aux;
    char *nome;

    nome = (char*)malloc(sizeof(strlen(fila->inicio->nomeArquivo)+1));

    aux = (Arquivo*)malloc(sizeof(Arquivo));

    strcpy(nome, fila->inicio->nomeArquivo);

    aux = fila->inicio;
    fila->inicio = fila->inicio->prox;
    free(aux);

    if(fila->inicio == NULL)
        fila->fim = NULL;
    
    return nome;
}

void head(Fila fila){
    printf("%s\n", fila.inicio->nomeArquivo);
}

int cancel(Fila* fila, char* nome){
    int result = 0;
    Arquivo* atual, *anterior;
    
    atual = fila->inicio;
    anterior = NULL;

    while(atual != NULL){
        if(strcmp(nome, atual->nomeArquivo) == 0){
            result = 1;
            if(anterior != NULL)
                anterior->prox = atual->prox;
            else
                fila->inicio = anterior;
        
            if(atual == fila->fim)
                fila->fim = anterior;

            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return result;
}

void list(Fila* fila){
    Arquivo* aux;

    aux = (Arquivo*)malloc(sizeof(Arquivo));

    aux = fila->inicio;
    
    while(fila->inicio != NULL){
        printf("%s\n", fila->inicio->nomeArquivo);
        fila->inicio = fila->inicio->prox;
    }

    fila->inicio = aux;
}

int main() {
    Fila filaArquivo;
    int opcao, valor;
    char nomeArquivo[25], *arquivoRemovido[25];

    inicializar(&filaArquivo);

    do {
        exibirOpcoes();
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                printf("Digite o nome do arquivo: ");
                scanf("%s", nomeArquivo);
                if (isFull(filaArquivo) == 0) {
                    enqueue(&filaArquivo, nomeArquivo);
                    printf("Nome adicionado!\n");
                }
                else {
                    printf("Fila cheia!");
                }
                break;
            case 2:
                if (isEmpty(filaArquivo) == 0) {
                    printf("Arquivo desenfileirado do inicio da fila: %s\n", dequeue(&filaArquivo));
                }else{
                    printf("A fila está vazia!\n");
                }
                break;
            case 3:
                if(isEmpty(filaArquivo) == 0){
                    printf("Arquivo no inicio da fila: ");
                    head(filaArquivo);
                    printf("\n");
                }else{
                    printf("A fila está vazia!\n");
                }
                break;
            case 4:
                if(isEmpty(filaArquivo) == 0){
                    printf("Digite o nome do arquivo que deseja cancelar a impressão: ");
                    scanf("%s", nomeArquivo);
                    valor = cancel(&filaArquivo, nomeArquivo);
                    if(valor == 1){
                        printf("A impressão do arquivo %s foi cancelada!\n", nomeArquivo);
                    }else{
                        printf("Arquivo não encontrado!\n");
                    }
                }else{
                    printf("A fila está vazia!\n");
                }
                break;
            case 5:
                if(isEmpty(filaArquivo) == 0)
                    list(&filaArquivo);
                else
                    printf("A fila está vazia!\n");
                break;
            case 0:
                printf("Fim de programa!\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
            }
    } while (opcao != 0);
}