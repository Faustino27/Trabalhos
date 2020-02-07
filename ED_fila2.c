#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct fila{
	char tarefa[25];
	struct fila* prox;
}fila;
typedef struct fila* Fila;

Fila* criar_fila(){
	Fila* fi;
    fi = (Fila*)malloc(sizeof(Fila));
    *fi = NULL;
    return fi;
}

void colocar_na_fila(Fila* fi, char tarefa[25]){
	fila* novo = malloc(sizeof(fila)), *aux;
	aux = *fi;
	if(aux == NULL){
		*fi = novo;
		strcpy(novo->tarefa, tarefa);
		novo->prox = NULL;
		return;
	}
	while(aux->prox != NULL)
		aux = aux->prox;
	aux->prox = novo;
	novo->prox = NULL;
	strcpy(novo->tarefa, tarefa);
	return;
}

int imprime(Fila* fi, int tempo, int prioridade){
	fila* aux, *aux2;
	aux = *fi;
	while(tempo != 0 && aux != NULL){
		aux2 = aux;
		aux = aux->prox;
		*fi = aux;
		free(aux2);
		tempo--;
	}
	while(aux != NULL){
		printf("Atividade: %s Prioridade: #%d\n", aux->tarefa, prioridade);
		aux2 = aux;
		aux = aux->prox;
		*fi = aux;
		free(aux2);
	}
	return tempo;
}

int main(){
	int prioridade, tempo, contador = 0;
	char comando[25];
	Fila* fi1 = criar_fila(), *fi2 = criar_fila(), *fi3 = criar_fila(), *fi4 = criar_fila(), *fi5 = criar_fila();
	Fila* fi6 = criar_fila(), *fi7 = criar_fila(), *fi8 = criar_fila(), *fi9 = criar_fila(), *fi10 = criar_fila();
	while(scanf("%s", comando) && !(comando[0] >= 48 && comando[0] <= 57)){
		scanf("%d", &prioridade);
		if(prioridade == 1)
			colocar_na_fila(fi1, comando);
		if(prioridade == 2)
			colocar_na_fila(fi2, comando);
		if(prioridade == 3)
			colocar_na_fila(fi3, comando);
		if(prioridade == 4)
			colocar_na_fila(fi4, comando);
		if(prioridade == 5)
			colocar_na_fila(fi5, comando);
		if(prioridade == 6)
			colocar_na_fila(fi6, comando);
		if(prioridade == 7)
			colocar_na_fila(fi7, comando);
		if(prioridade == 8)
			colocar_na_fila(fi8, comando);
		if(prioridade == 9)
			colocar_na_fila(fi9, comando);
		if(prioridade == 10)
			colocar_na_fila(fi10, comando);
		contador++;
	}
	tempo = atoi(comando);
	contador -= tempo;
	if(contador < 0)
		contador = 0;
	printf("Tamanho da fila: %d\n", contador);
	tempo = imprime(fi1, tempo, 1);
	tempo = imprime(fi2, tempo, 2);
	tempo = imprime(fi3, tempo, 3);
	tempo = imprime(fi4, tempo, 4);
	tempo = imprime(fi5, tempo, 5);
	tempo = imprime(fi6, tempo, 6);
	tempo = imprime(fi7, tempo, 7);
	tempo = imprime(fi8, tempo, 8);
	tempo = imprime(fi9, tempo, 9);
	tempo = imprime(fi10, tempo, 10);

}