#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 53

int posArq = 0;

typedef struct carro {
	char placa[8];
	char marca[15];
	char modelo[15];
	char cor[15];
	int status;
} CARRO;

typedef struct noTabela {
	char placa[8];
	int posicao;
	struct noTabela* prox;
} NO;

FILE* prepararArquivo(char nome[]);
void fecharArquivo(FILE* arq);
int buscar(NO* tabelaHashing[], char placa[]);
void cadastrar(FILE* arq, NO* tabelaHashing[]);
void consultar(FILE* arq, NO* tabelaHashing[]);
void alterar(FILE* arq, NO* tabelaHashing[]);
void remover(FILE* arq, NO* tabelaHashing[]);
void exibirCadastro(FILE* arq);
void criarIndice(FILE* arq, NO* tabelaHashing[]);
void desalocarIndice(NO* tabelaHashing[]);
void inserirTabelaHash(NO* tabelaHashing[], char placa[], int pos);
int hashing(char placa[]);
void exibirOpcoes();
void limparBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

int main() {
	char nomeArq[] = "carros.dat";
	int op;
	FILE* cadastro;
	NO* tabelaHashing[N] = {NULL};
	cadastro = prepararArquivo(nomeArq);
	if (cadastro == NULL)
		printf("Erro na abertura do arquivo. Programa encerrado \n");
	else {
		criarIndice(cadastro, tabelaHashing);
		do {
			exibirOpcoes();
			scanf("%d",&op);
			getchar();
			switch (op) {
			case 1: cadastrar(cadastro, tabelaHashing);
				break;
			case 2: consultar(cadastro, tabelaHashing);
				break;
			case 3: alterar(cadastro, tabelaHashing);
				break;
			case 4: remover(cadastro, tabelaHashing);
				break;
			case 5: exibirCadastro(cadastro);
				break;
			case 0: fecharArquivo(cadastro);
				desalocarIndice(tabelaHashing);
				break;
			default: printf("Opcao invalida\n");
				break;
			}
		} while (op != 0);
	}
	return 0;
}

FILE* prepararArquivo(char nome[]) {
	FILE* aux;
	aux = fopen(nome, "r+b");
	if (aux == NULL)
		aux = fopen(nome, "w+b");
	return aux;
}

void fecharArquivo(FILE* arq) {
	FILE* copia;
	CARRO carroCopia;
	copia = prepararArquivo("carrosCopia.dat");
	
	rewind(arq);
	
	while(fread(&carroCopia, sizeof(CARRO), 1, arq)){
	    if(carroCopia.status == 1){
	        fwrite(&carroCopia, sizeof(CARRO), 1, copia);
	    }
	}
	
	fclose(arq);
	fclose(copia);
	
	remove("carros.dat");
	rename("carrosCopia.dat", "carros.dat");
}

void criarIndice(FILE* arq, NO* tabelaHashing[]) {
	CARRO carro;

	rewind(arq);

	while(fread(&carro, sizeof(carro), 1, arq)){
		int posTabela = hashing(carro.placa);

		NO* novoNo = (NO*)malloc(sizeof(NO));
		NO* aux, *anterior;

		aux = tabelaHashing[posTabela];
		anterior = NULL;

		strcpy(novoNo->placa, carro.placa);
		novoNo->posicao = posArq;
		novoNo->prox = NULL;

		while(aux != NULL){
			if(strcmp(aux->placa, carro.placa) > 0){
				if(anterior == NULL){
					novoNo->prox = tabelaHashing[posTabela];
					tabelaHashing[posTabela] = novoNo;
				}
				else{
					novoNo->prox = aux;
					anterior->prox = novoNo;
				}
			}
			else{
				anterior = aux;
				aux = aux->prox;
			}
		}

		if(aux == NULL){
			tabelaHashing[posTabela] = novoNo;
		}
		posArq++;
	}
}

void desalocarIndice(NO* tabelaHashing[]) {
	NO* aux;

	for(int i = 0; i < N; i++){
		if(tabelaHashing[i] != NULL){
			while(tabelaHashing[i] != NULL){
				aux = tabelaHashing[i];
				tabelaHashing[i] = tabelaHashing[i]->prox;

				free(aux);
			}
		}
	}
}

void exibirOpcoes() {
	printf("Opcoes \n");
	printf("1 - Cadastrar um carro \n");
	printf("2 - Consultar carro \n");
	printf("3 - Alterar dados do carro \n");
	printf("4 - Remover carro \n");
	printf("5 - Exibir carros cadastrados \n");
	printf("0 - Encerrar programa \n");
	printf("Informe a opcao: ");
}

int buscar(NO* tabelaHashing[], char placa[]) {
	int posicao = hashing(placa);

	NO* aux = tabelaHashing[posicao];

	while(aux != NULL){
		if(strcmp(aux->placa, placa) == 0){
			printf("%d\n", aux->posicao);
			return aux->posicao;
		}
		else{
			aux = aux->prox;
		}
	}
	return -1;
}

void inserirTabelaHash(NO* tabelaHashing[], char placa[], int pos) {
	NO* novo = (NO*)malloc(sizeof(NO));
	NO* aux, *anterior;

	int posTabela = hashing(placa);

	aux = tabelaHashing[posTabela];

	if(aux == NULL){
		strcpy(novo->placa, placa);
		novo->posicao = pos;
		novo->prox = NULL;
		tabelaHashing[posTabela] = novo;
	}
	else if(aux->placa, placa > 0){
		strcpy(novo->placa, placa);
		novo->posicao = pos;
		novo->prox = tabelaHashing[posTabela];
		tabelaHashing[posTabela] = novo;
	}
	else{
		anterior = tabelaHashing[posTabela];
		aux = aux->prox;

		while(aux != NULL){
			if(strcmp(aux->placa, placa) == 0){
				printf("Veículo já cadastrado!\n");
				return;
			}
			else if(strcmp(aux->placa, placa) > 0){
				strcpy(novo->placa, placa);
				novo->posicao = pos;
				novo->prox = aux;
				anterior->prox = novo;

				break;
			}
			else{
				anterior = aux;
				aux = aux->prox;
			}
		}
	}
}

void removerTabelaHash(NO* tabelaHashing[], char placa[], int posTabela) {
	NO* aux, *anterior, *remove;

	anterior = NULL;
	aux = tabelaHashing[posTabela];

	while(aux != NULL){
		if(strcmp(aux->placa, placa) == 0){
			if(anterior == NULL){
				remove = tabelaHashing[posTabela];
				tabelaHashing[posTabela] = tabelaHashing[posTabela]->prox;

				free(remove);
				break;
			}
			else{
				remove = aux;
				aux = aux->prox;
				anterior->prox = aux;

				free(remove);
				break;
			}
		}
		else{
			anterior = aux;
			aux = aux->prox;
		}
	}
}

int hashing(char placa[]) {
	int soma = 0, tam = strlen(placa);

	for(int i = 0; i < tam; i++){
		soma += (placa[i] << (i % 8));
	}
	return abs(soma) % N;
}

void cadastrar(FILE* arq, NO* tabelaHashing[]) {
	char placa[8];
	char marca[15];
	char modelo[15];
	char cor[15];
	int status;

	printf("Digite a placa do carro: ");
	fgets(placa, 8, stdin);
	limparBuffer();

	int retorno = buscar(tabelaHashing, placa);

	if(retorno != -1){
		printf("Veículo já cadastrado!\n");
	}
	else{
		CARRO novo;

		strcpy(novo.placa, placa);
		printf("Digite a marca do carro: ");
		fgets(marca, 15, stdin);
		limparBuffer();
		strcpy(novo.marca, marca);
		printf("Digite o modelo do carro: ");
		fgets(modelo, 15, stdin);
		limparBuffer();
		strcpy(novo.modelo, modelo);
		printf("Digite a cor do carro: ");
		fgets(cor, 15, stdin);
		limparBuffer();
		strcpy(novo.cor, cor);
		novo.status = 1;

		fseek(arq, 0, SEEK_END);
		fwrite(&novo, sizeof(CARRO), 1, arq);
		inserirTabelaHash(tabelaHashing, placa, posArq);
		printf("Veículo cadastrado!\n");
		posArq++;
	}
}

void consultar(FILE* arq, NO* tabelaHashing[]) {
	char placa[8];

	printf("Digite a placa do carro: ");
	fgets(placa, 8, stdin);
	limparBuffer();

	int retorno = buscar(tabelaHashing, placa);

	if(retorno == -1){
		printf("Veículo não encontrado!\n");
	}
	else{
		fseek(arq, retorno*sizeof(CARRO), SEEK_SET);
		CARRO carro;
		fread(&carro, sizeof(CARRO), 1, arq);

		printf("Marca: %s\n", carro.marca);
		printf("Modelo: %s\n", carro.modelo);
		printf("Cor: %s\n", carro.cor);
		printf("Status: %d\n", carro.status);
		printf("\n");
	}
}

void alterar(FILE* arq, NO* tabelaHashing[]) {
	char placa[8];

	printf("Digite a placa do carro: ");
	fgets(placa, 8, stdin);
	limparBuffer();

	int retorno = buscar(tabelaHashing, placa);

	if(retorno == -1){
		printf("Veículo não encontrado!\n");
	}
	else{
		CARRO carroAlterar;
		int alterar;

		fseek(arq, retorno * sizeof(CARRO), SEEK_SET);
		fread(&carroAlterar, sizeof(CARRO), 1, arq);

		printf("Dados do carro:\n");
		printf("Marca: %s\n", carroAlterar.marca);
		printf("Modelo: %s\n", carroAlterar.modelo);
		printf("Cor: %s\n", carroAlterar.cor);

		printf("Deseja alterar a marca? (1 - Sim/2 - Nao): ");
		scanf("%d", &alterar);
		getchar();

		if(alterar == 1){
			char marca[15];
			printf("Digite a nova marca: ");
			fgets(marca, 15, stdin);
			limparBuffer();

			strcpy(carroAlterar.marca, marca);
		}

		printf("Deseja alterar o modelo? (1 - Sim/2 - Nao): ");
		scanf("%d", &alterar);
		getchar();

		if(alterar == 1){
			char modelo[15];
			printf("Digite o novo modelo: ");
			fgets(modelo, 15, stdin);
			limparBuffer();

			strcpy(carroAlterar.modelo, modelo);
		}

		printf("Deseja alterar a cor? (1 - Sim/2 - Nao): ");
		scanf("%d", &alterar);
		getchar();

		if(alterar == 1){
			char cor[15];
			printf("Digite a nova cor: ");
			fgets(cor, 15, stdin);
			limparBuffer();

			strcpy(carroAlterar.cor, cor);
		}

		fseek(arq, retorno*sizeof(CARRO), SEEK_SET);
		fwrite(&carroAlterar, sizeof(CARRO), 1, arq);
	}
}

void remover(FILE* arq, NO* tabelaHashing[]) {
	char placa[8];

	printf("Digite a placa do carro: ");
	fgets(placa, 8, stdin);
	limparBuffer();

	int retorno = buscar(tabelaHashing, placa);

	if(retorno == -1){
		printf("Veículo não cadastrado!\n");
	}
	else{
		int remover;
		CARRO carro;
		fseek(arq, retorno*sizeof(CARRO), SEEK_SET);
		fread(&carro, sizeof(CARRO), 1, arq);

		printf("Dados do carro:\n");
		printf("Placa: %s\n", carro.placa);
		printf("Marca: %s\n", carro.marca);
		printf("Modelo: %s\n", carro.modelo);
		printf("Cor: %s\n", carro.cor);
		printf("Deseja remover o carro? (1 - sim / 0 - não)\n");
		scanf("%d", &remover);
		getchar();

		if(remover == 1){
			carro.status = 0;

			int posTabela = hashing(placa);

			fseek(arq, retorno*sizeof(CARRO), SEEK_SET);
			fwrite(&carro, sizeof(CARRO), 1, arq);

			removerTabelaHash(tabelaHashing, placa, posTabela);
			printf("Veículo removido!\n");
		}
		else if(remover == 0){
			printf("Veículo não removido!\n");
		}
		else{
			printf("Valor inválido\n");
		}
	}
}

void exibirCadastro(FILE* arq) {
	CARRO carro;
	fseek(arq, 0, SEEK_SET);

	while(fread(&carro, sizeof(CARRO), 1, arq)){
		if(carro.status == 1){
			printf("\n");
			printf("Placa: %s\n", carro.placa);
			printf("Marca: %s\n", carro.marca);
			printf("Modelo: %s\n", carro.modelo);
			printf("Cor: %s\n", carro.cor);
		}
	}
}