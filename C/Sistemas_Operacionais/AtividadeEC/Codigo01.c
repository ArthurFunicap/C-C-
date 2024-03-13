#include <stdio.h>
#include <stdlib.h>

//Fiz essas declarações porque sem elas o VSCode fica marcando as funções com uma
//frase de "declaração implícita"
__pid_t fork(void);
__pid_t getpid(void);
__pid_t wait(void);

int main(){
    //Criando um Identificador de Processo para o Processo-Filho
    __pid_t pid;

    //O fork() cria um Processo-Filho
    pid = fork();

    if(pid == 0){
        //O fork() retorna 0 quando é possível criar o Processo-Filho
        printf("Processo-Filho criado com sucesso!\n");
        printf("PID do Processo-Filho: %d\n\n", getpid());
    } else if(pid > 0){
        //A função wait() diz ao Processo-Pai para que ele espere o Processo-Filho
        //terminar para assim poder executar suas linhas de código
        wait();
        //O Processo-pai será executado assim que o Processo-Filho terminar
        printf("Processo-Pai sendo executado!\n");
        printf("PID do Processo-Pai: %d\n", getpid());
    } else{
        //Caso o Processo-Filho não seja criado
        printf("Não foi possível criar o Processo-Filho!\n");
    }
    return 0;
}