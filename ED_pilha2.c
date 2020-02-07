#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct roupas{
	int x;
	char tipo[50];
	char cor[50];
	struct roupas* prox;
}roupas;

typedef struct roupas* pilha;

pilha* criar_pilha(){
	pilha* pi;
	pi = (pilha*) malloc(sizeof(pilha));
	return pi;
}
void empilhar(pilha* pi, char tipo[50], char cor[50], int x){
	roupas* aux = malloc(sizeof(roupas));
	aux->prox = *pi;
	aux->x = x;
	strcpy(aux->tipo, tipo);
	strcpy(aux->cor, cor);
	*pi = aux;
}

void printar(pilha* pi){
	roupas* aux;
	int contador = 0, total = 0;
	while(*pi != NULL){
		aux = *pi;
		*pi = (*pi)->prox;
		printf("Tipo: %s Cor: %s\n", aux->tipo, aux->cor);
		contador++;
		total += aux->x;
		free(aux);
	}
	printf("Total de roupas = %d\n", contador);
	printf("Total de tempo = %d\n", total);

}


int main(){
	int x;
	char tipo[50], cor[50];
	pilha* pi = criar_pilha();

	while(1){
		scanf("%s", tipo);
		if(!strcmp(tipo, "end")){
			printar(pi);
			return 0;;
		}
		scanf("%s", cor);
		scanf("%d", &x);
		empilhar(pi, tipo, cor, x);

	}

}