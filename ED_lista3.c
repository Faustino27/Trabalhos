#include<stdio.h>
#include<stdlib.h>
typedef struct elemento{
	int id;
	struct elemento* prox;
	struct elemento* ant;
} elemento;
typedef struct elemento* lista;

lista* criar_lista(){
	lista *li;
	li = (lista*) malloc(sizeof(lista));
	*li = NULL;
	return li;

}
void inserir_inicio(lista* li, int id){
	elemento *aux, *aux1 = *li;
	aux = malloc(sizeof(elemento));
	aux->id = id;
	aux->prox = NULL;
	if(*li == NULL){
		aux->ant = NULL;
		*li = aux;
	}
	else{
		while(aux1->prox !=NULL)
			aux1 = aux1->prox;
		aux1->prox = aux;
		aux->ant = aux1;
	}
}
void fila_geral_inicial(lista *li){
	elemento *aux;
	aux = *li;
	int contador = 1;
	printf("Fila geral original\n");
	while(aux != NULL){
		printf("%d - %d\n", contador, aux->id);
		contador++;		
		aux = aux->prox;
	}
}
void fila_preferencial(lista *li){
	elemento *aux;
	aux = *li;
	int contador = 1;
	printf("\nFila preferencial\n");
	while(aux != NULL){
		if(aux->id >=60){
			printf("%d - %d\n", contador, aux->id);
		}
		aux = aux->prox;
		contador++;
	}
}
void fila_geral_atualizada(lista *li){
	elemento* aux;;
	int contador = 1;
	printf("\nFila geral atualizada\n");
	aux = *li;
	while(aux !=NULL){
		if(aux->id < 60){
			printf("%d - %d\n", contador, aux->id);
		}
		aux = aux->prox;
		contador++;
	}
}

void esperado_preferencial(lista* li){
	elemento* aux;
	int contador1 = 1, contador2 = 1;
	printf("\nResultado esperado fila preferencial\n");
	aux = *li;
	while(aux != NULL){
		if(aux->id >= 60){
			printf("%d - %d\n", contador1, contador2);
			contador1++;
		}
		aux = aux->prox;
		contador2++;
	}

}
void esperado_geral(lista* li){
	elemento* aux;
	int contador1 = 1, contador2 = 1;
	printf("\nResultado esperado fila geral\n");
	aux = *li;
	while(aux != NULL){
		if(aux->id < 60){
			printf("%d - %d\n", contador1, contador2);
			contador1++;
		}
		contador2++;
		aux = aux->prox;
	}
}

int main(){
	int id;
	lista* li;
	li = criar_lista();
	while(scanf("%d", &id) >0){
		inserir_inicio(li, id);
	}
	fila_geral_inicial(li);
	fila_preferencial(li);
	fila_geral_atualizada(li);
	esperado_preferencial(li);
	esperado_geral(li);
}