#include<stdlib.h>
#include<stdio.h>
int TEMPO = 0;
typedef struct elemento{
	int chave;
	int tempo;
	int posicao;
	struct elemento* prox;
	struct elemento* back;
}elemento;
typedef struct elemento* lista;
lista* criarlista(){
	lista* li;
	li = (lista*)malloc(sizeof(lista));
	*li = NULL;
	return li;
}
void comando_i(int n, int j, lista* li){
	elemento *aux, *posicaoj;
	int contador = 1;
	;
	if(*li == NULL){
		aux = malloc(sizeof(elemento));
		*li = aux;
		aux->prox = NULL;
		aux->chave = n;
		aux->back = NULL;
		aux->tempo = TEMPO;
		TEMPO++;
	}
	else{
		aux = *li;
		while(aux->prox != NULL){
			aux = aux->prox;
			contador++;
		}
		aux->prox = malloc(sizeof(elemento));
		aux->prox->prox = NULL;
		aux->prox->chave = n;
		if(j == 0){
			aux->prox->back = NULL;
		}
		else{
			contador -= j;
			posicaoj = *li;
			if(contador < 0){
				aux->prox->back = NULL;
				aux->prox->tempo = TEMPO;
				TEMPO++;
				return;
			}
			while(contador > 0){
				posicaoj = posicaoj->prox;
				contador--;
			}
			aux->prox->back = posicaoj;
		}
		aux->prox->tempo = TEMPO;
		TEMPO++;
	}
}

void comando_r(int n, lista *li){
	elemento* aux, *local, *ant;
	local = *li;
	while(local->chave != n){
		ant = local;
		local = local->prox;
	}
	aux = *li;
	while(aux != NULL){
		if(aux->back == local){
			aux->back = NULL;
		}
		aux = aux->prox;
	}
	if((*li)->chave == n){
		*li = (*li)->prox;
		free(aux);
		aux = NULL;
	}
	else{
		ant->prox = local->prox;
		free(local);
		local = NULL;
		TEMPO++;
	}
}

void imprimir_lista(lista* li){
	elemento* aux;
	int contador = 0;
	aux = *li;
	if(*li == NULL)
		printf("-1");
	else{
		while(aux != NULL){
			aux->posicao = contador;
			printf("[%d,", aux->chave);
			printf("%d", aux->tempo);
			if(aux->back != NULL){
				printf(",%d] ", aux->back->posicao);
			}
			else printf("] ");
			aux= aux->prox;
			contador++;
		}
		while(*li != NULL){
			aux = *li;
			*li = (*li)->prox;
			free(aux);
			aux = NULL;
		}
	}

}
int main(){
	char comando;
	int n, j;
	lista* li = criarlista();
	while(comando != 'f'){
		scanf("%c", &comando);
		if(comando == 'i'){
			scanf("%d %d", &n, &j);
			comando_i(n , j, li);
		}
		if(comando == 'r'){
			scanf("%d", &n);
			comando_r(n, li);
		}
		if(comando == 'f'){
			imprimir_lista(li);
		}
	}

	return 0;
}