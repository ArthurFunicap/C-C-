#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

__pid_t fork(void);
__pid_t getpid(void);
__pid_t wait(void);

//Função que vai rodar um D20
int dadoPai();
//Função que vai rodar um D6
int dadoFilho();
//Função que vai rodar um D1
int erroDado();

int main(){
    __pid_t pid;
    
    printf("Informações sobre os dados (de RPG):\n\n");
    printf("1.O Processo-Pai vai rodar um D20\n");
    printf("2.Se o Processo-Filho for criado, ele vai rodar um D6\n");
    printf("3.Se o Processo-Filho NÃO for criado, será rodado um D1\n\n");

    //A função sleep() atrasa a execução do código em 2 segundos
    sleep(2);

    pid = fork();

    if(pid == 0){
        //Bloco de código do Processo-filho
        printf("Girando um D6...\n");
        //A função sleep() atrasa a execução do código em 3 segundos
        sleep(3);
        printf("Valor do dado D6: %d\n", dadoFilho());
    } else if(pid > 0){
        //Bloco de código do Processo-pai
        wait();
        printf("Girando um D20...\n");
        //A função sleep() atrasa a execução do código em 3 segundos
        sleep(3);
        printf("Valor do dado D20: %d\n", dadoPai());
    } else{
        //Bloco de código do Erro (quando dá erro na criação do Processo-Filho)
        printf("Girando um D1...\n");
        //A função sleep() atrasa a execução do código em 3 segundos
        sleep(1);
        printf("Valor do dado D1: %d\n", erroDado());
        //A função exit() encerra o programa, o valor 1 indica que o programa está
        //sendo terminado por causa de um erro genérico
        exit(1);
    }
    return 0;
}

int dadoFilho(){
    int D6;

    srand(time(NULL));
    //Operação que vai gerar um valor aleatório entre 1 e 6
    D6 = rand() % 6 + 1;

    return D6;
}

int dadoPai(){
    int D20;

    srand(time(NULL));
    //Operação que vai gerar um valor aleatório entre 1 e 20
    D20 = rand() % 20 + 1;

    return D20;
}

int erroDado(){
    //Retorna 1 por se tratar de um erro na criação do Processo-Filho
    return 1;
}