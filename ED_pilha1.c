#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct numero{
	char numero[100];
	struct numero* prox;

}numero;

typedef struct palavra{
	char palavra[100];
	struct palavra *prox;
}palavra;
typedef struct palavra* pa;
typedef struct numero* num;

pa* criar_pilhan(){
	pa* pi;
	pi = (pa*) malloc(sizeof(pa));
	return pi;
}

num* criar_pilha(){
	num* pi;
	pi = (num*) malloc(sizeof(num));
	return pi;
}

void libere_palabra(pa* pi){
	printf("Palavras:\n");
	if(pi != NULL){
		palavra* aux;
		aux = *pi;
		*pi = (*pi)->prox;
		free(aux);
		while((*pi) != NULL){
			aux = *pi;
			printf("%s\n", aux->palavra);
			*pi = (*pi)->prox;
			free(aux);
		}
		free(pi);
	}
}

void libera_num(num* pi){
	printf("Numeros:\n");
	if(pi != NULL){
		numero *aux;
		while((*pi) != NULL){
			aux = *pi;
			printf("%s\n", aux->numero);
			*pi = (*pi)->prox;
			free(aux);
		}
		free(pi);
	}
}

void insere_numero(num* tn, char nume[100]){
	numero* no;
	no  = malloc(sizeof(numero));
	strcpy(no->numero, nume);
	no->prox = *tn;
	*tn = no;

}

void insere_palavra(pa* tp, char palav[100]){
	palavra* no = malloc(sizeof(palavra));
	strcpy(no->palavra, palav);
	no->prox = *tp;
	*tp = no;
}

int main(){
	char palavra[100];
	num* tn = criar_pilha();
	pa* tp = criar_pilhan();
	while(strcmp(palavra, "end")){
		scanf("%s", palavra);
		if(palavra[0] >47 && palavra[0] < 58){
			insere_numero(tn, palavra);
		}
		else{
			insere_palavra(tp, palavra);
		}
	}
	libere_palabra(tp);
	libera_num(tn);

}