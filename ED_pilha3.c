#include<stdio.h>
#include<stdlib.h>

typedef struct elemento{
	int peso;
	struct elemento* prox;
} elemento;

typedef struct elemento* pilha;

pilha* criar_pilha(){
	pilha* pi;
	pi = (pilha*) malloc(sizeof(pilha));
	return pi;
}

void empilhar(pilha* pi, int peso){
	elemento* aux = malloc(sizeof(elemento));
	aux->prox = *pi;
	aux->peso = peso;
	*pi = aux;
}

void procurar(pilha* pi, int peso){
	elemento* aux = *pi;
	int contador = 0, total = 0;
	if(*pi !=NULL){
		if((*pi)->prox == NULL){
			aux = *pi;
			printf("Peso retirado: %d\n", aux->peso);
			contador++;
			total += aux->peso;
			printf("Anilhas retiradas: %d\n", contador);
			printf("Peso retirado: %d\n", total);
			return;
		}

		while(aux->peso != peso){
			aux = *pi;
			*pi = (*pi)->prox;
			if(aux->peso != peso){
				printf("Peso retirado: %d\n", aux->peso);
				contador++;
				total += aux->peso;
			}
		}
		printf("Anilhas retiradas: %d\n", contador);
		printf("Peso retirado: %d\n", total);
	}
}


int main(){
	int peso;
	pilha* pi = criar_pilha();
	while(1){
		scanf("%d", &peso);
		if(peso == 0){
			scanf("%d", &peso);
			procurar(pi, peso);
			return 0;
		}
		empilhar(pi, peso);
	}

}