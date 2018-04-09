#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct
typedef struct lista{
	int qtd;
	struct elemento *inicio;
}lista;

typedef struct elemento{
	char nome[50];
	int matricula;
	struct elemento *proximo;
}elemento;


//Prévia func
lista *alocarlista();
void menu(lista *l);
void inserir(lista *l, int matricula, char nome[50]);
elemento *alocarelemento();

void ordenar(lista *l);
void mostrar(lista *l);

int main(){
	lista *l;

	l = alocarlista();

	menu(l);

	return 0;
}

lista *alocarlista(){
	lista *aux;

	aux = (lista*)malloc(sizeof(lista));

	aux->qtd = 0;
	aux->inicio = NULL;

	return aux;
}

void menu(lista *l){
	int opc, matricula;
	char nome[50];

	do{
		printf("Quantidade: %d\n", l->qtd);
		printf("1-Cadastrar Aluno\n");
		printf("2-Ordenar\n");
		printf("3-Mostrar\n");
		printf("0-Sair\n");
		scanf("%d",&opc);

		switch(opc){
			case 1:
				printf("Nome: ");
				scanf(" %s", nome);
				//fflush(stdin);
				__fpurge(stdin); //limpar buffer
				printf("Matricula: ");
				scanf("%d", &matricula);
				inserir(l, matricula, nome);
				break;
			case 2:
				ordenar(l);
				break;
			case 3:
				mostrar(l);
				break;
		}

		printf("\nPressione qualquer tecla para continuar...\n");
		//fflush(stdin);
		__fpurge(stdin);
		getchar(); //pause

		//system("cls");
		system("clear");
	}while(opc!=0);
}

void inserir(lista *l, int matricula, char nome[50]){
	elemento *novo, *aux;

	novo = alocarelemento();

	strcpy(novo->nome, nome);
	novo->matricula = matricula;

	if(l->inicio == NULL){
		l->inicio = novo;
	} else {
		aux = l->inicio;

		while(aux->proximo != NULL){
			aux = aux->proximo;
		}

		aux->proximo = novo;
	}

	l->qtd++;

	printf("Aluno inserido com sucesso!\n");
}

elemento *alocarelemento(){
	elemento *aux;

	aux = (elemento*)malloc(sizeof(elemento));

	aux->proximo = NULL;
	aux->matricula = 0;
	strcpy(aux->nome, " ");
}

void ordenar(lista *l){
	/*
		Ordenar uma lista trocando os apontamentos usando bubble sort.

		*atual: vai receber o endereco de quem vai ser comparado com os proximos elementos
		*ant: vai guardar o endereco do atual depois de todas as comparacoes
		*prox: vai definir o endereco de quem vai ser comparado com o atual
		*aux: var. auxiliar para guardar enderecos
		*antp: ira guardar o endereco de quem foi comparado com o atual
		first: flag resposavel por informar se estou no primeira elemento da lista
		pos: flag responsavel por informar se estou na primeira comparacao

	*/
	elemento *atual, *ant, *prox, *aux, *antp;
	int first=1, pos=0;

	if(l->qtd < 2){
		printf("Nao foi possivel ordenar a lista!\n");
	} else {
		atual = l->inicio;

		while(atual != NULL){
			prox = atual->proximo;

			while(prox != NULL){
				if(atual->matricula > prox->matricula){
					aux = prox->proximo;

					if(pos == 0){
						prox->proximo = atual;
					} else {
						prox->proximo = atual->proximo;
						atual->proximo = aux;
						antp->proximo = atual; // o anterior ao elemento comparado(prox) deve apontar para o atual
					}

					atual->proximo = aux;

					aux = atual;
					atual = prox; // falando que meu atual sera o prox, pois ele quem tenho que comparar agora com o restante dos elementos
					prox = aux;

					if(first == 1){
						l->inicio = atual;
					} else {
						ant->proximo = atual;
					}
				}

				antp = prox; //guardando o ultimo elemento visitado
				prox = prox->proximo;
				pos++;
			}

			pos=0; // zerar o controlador de posicao, pois vai se iniciar um novo ciclo
			first = 0; // nao irei mais mexer no apontamento do inicio
			ant = atual; // definindo o anterior, pois irei mexer no apontamento dele agr
			atual = atual->proximo;
		}
	}
}

void mostrar(lista *l){
	elemento *aux;

	if(l->qtd == 0){
		printf("Lista vazia!\n");
	} else {
		aux = l->inicio;

		while(aux != NULL){
			printf("%s, %d\n", aux->nome, aux->matricula);
			printf("=================\n");

			aux = aux->proximo;
		}
	}
}
