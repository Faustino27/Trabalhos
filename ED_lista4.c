#include<stdio.h>
#include<stdlib.h>

typedef struct elemento{
	int dado;
	struct elemento* prox;
	struct elemento* ant;
}elemento;
typedef struct elemento* lista;

lista* criar_lista(){
	lista *li;
	li = (lista*) malloc(sizeof(lista));
	(*li) = NULL;
	return li;
}
void imprime(lista* li){
	elemento *aux;
	int contador = 0;
	aux = *li;
	if(*li == NULL){
		printf("Tamanho: %d", contador);
		return;
	}
	while(aux != NULL){
		printf("%d -", aux->dado);
		if(aux->ant != NULL)
			printf(" 1 -");
		else printf(" 0 -");
		if(aux->prox != NULL)
			printf(" 1\n");
		else
			printf(" 0\n");
		aux = aux->prox;
		contador ++;
	}
	printf("Tamanho: %d", contador);
}

void inserir_final(lista* li, int dado){
	elemento *aux, *aux1 = *li;
	aux = malloc(sizeof(elemento));
		aux->dado = dado;
		aux->prox = NULL;
	if(*li == NULL){
		aux->ant = NULL;
		*li = aux;
	}
	else{
		while(aux1->prox != NULL)
			aux1 = aux1->prox;
		aux1->prox = aux;
		aux->ant = aux1; 

	}
}

void instrucao_doistres(lista* li){
	elemento *aux, *aux1 = *li;
	aux = malloc(sizeof(elemento));
	aux->dado = 43;
	aux->prox = NULL;
	if(*li == NULL){
		aux->ant = NULL;
		*li = aux;
		aux->prox = malloc(sizeof(elemento));
		aux = aux->prox;
		aux->ant = *li;
		aux->dado = 65;
	}
	else{
		while(aux1->prox !=NULL)
			aux1 = aux1->prox;
		aux1->prox = aux;
		aux->ant = aux1;
		aux1 = aux;
		aux->prox = malloc(sizeof(elemento));
		aux = aux->prox;
		aux->ant = aux1;
		aux->dado = 65;
	}
}

void instrucao_cincoseis(lista* li){
	elemento* aux;
	aux = malloc(sizeof(elemento));
	aux->dado = 56;
	aux->ant = NULL;
	if(*li == NULL){
		aux->prox = NULL;
		*li = aux;
		aux->ant = malloc(sizeof(elemento));
		aux = aux->ant;
		aux->dado = 12;
		aux->prox = *li;
		aux->ant = NULL;
		*li = aux;
	}
	else{
		aux->prox = *li;
		(*li)->ant = aux;
		*li = aux;
		aux->ant = malloc(sizeof(elemento));
		aux = aux->ant;
		aux->ant = NULL;
		aux->dado = 12;
		aux->prox = *li;
		*li = aux;
	}
}

void instrucao_oitonove(lista* li){
	elemento* aux = *li, *novo;
	int contador = 1;
	while(contador != 3){
		aux = aux->prox;
		contador++;
	}
	novo = malloc(sizeof(elemento));
	novo->ant = aux->ant;
	novo->prox = aux;
	novo->dado = 10;
	aux->ant->prox = novo;
	aux->ant = novo;

	//aux = NULL;
	aux = malloc(sizeof(elemento));
	aux->prox = *li;
	(*li)->ant = aux;
	aux->dado = 15;
	aux->ant = NULL;
	*li = aux;
}

void remover_tres(lista* li){
	elemento *aux, *aux1;
	aux = *li;
	while(aux->prox != NULL){
		aux1 = aux;
		aux = aux->prox;
	}
	aux1->prox = NULL;
	free(aux);
	aux = aux1->ant;
	aux->prox = NULL;
	free(aux1);
	aux1 = aux->ant;
	aux1->prox = NULL;
	free(aux);
}

void remover_inicio_tres(lista* li){
	elemento* aux;
	int contador = 0;
	while((*li) != NULL && contador != 3){
		aux = *li;
		(*li) = (*li)->prox;
		free(aux);
		contador++;
	}
	if((*li) != NULL)
		(*li)->ant = NULL;
}

elemento* remover_ultimo(lista* li){
	elemento* aux, *aux1;
	aux = *li;
	if(*li == NULL)
		return NULL;
	while(aux->prox != NULL){
		aux1 = aux;
		aux = aux->prox;
	}
	aux1->prox = NULL;
	free(aux);
	return aux1;
}

void remover_terceiro(lista *li){
	elemento* aux, *aux1;
	aux = *li;
	if(*li == NULL)
		return;
	int contador = 1;
	while(contador != 3){
		if(aux->prox == NULL)
			return;
		aux1 = aux;
		aux = aux->prox;
		contador++;
	}
	aux1->prox = aux->prox;
	aux->prox->ant = aux1;
	free(aux);
}

void impreme_contrario(elemento* ultimo, lista* li){
	elemento* aux;
	int contador = 0;
	aux = ultimo;
	if(ultimo == NULL){
		printf("Tamanho: %d", contador);
		return;
	}
	while(aux != NULL){
		printf("%d - ", aux->dado);
		if(aux->ant != NULL)
			printf("1 -");
		else printf("0 -");
		if(aux->prox != NULL)
			printf(" 1\n");
		else
			printf(" 0\n");
		aux = aux->ant;
		contador++;
	}
	printf("Tamanho: %d", contador);

}
void libera(lista *li){
	elemento* aux;
	while(*li != NULL){
		aux = *li;
		(*li) = (*li)->prox;
		free(aux);
	}
}

int main(){
	int dado;
	elemento *ultimo;
	lista* li = criar_lista();
	while(scanf("%d", &dado) > 0){
		inserir_final(li, dado);
	}
	imprime(li);
	printf("\n\n");
	instrucao_doistres(li);
	imprime(li);
	printf("\n\n");
	instrucao_cincoseis(li);
	imprime(li);
	printf("\n\n");
	instrucao_oitonove(li);
	imprime(li);
	printf("\n\n");
	remover_tres(li);
	imprime(li);
	printf("\n\n");
	remover_inicio_tres(li);
	imprime(li);
	printf("\n\n");
	ultimo = remover_ultimo(li);
	remover_terceiro(li);
	imprime(li);
	printf("\n\n");
	impreme_contrario(ultimo, li);
	printf("\n");
	libera(li);

}