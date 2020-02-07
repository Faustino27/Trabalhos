#include <stdio.h>
#include <stdlib.h>

typedef struct abb_int{
	int dado;
	struct abb_int *esq;
	struct abb_int *dir;
} abb_int;

abb_int** criar_arvore(){
	abb_int** raiz = malloc(sizeof(abb_int*));
	return raiz;
}
void mostra_arvore(abb_int* raiz){
	printf("(");
	if(raiz == NULL){
		printf(")");
		return;
	}
	printf("%d ", raiz->dado);
	mostra_arvore(raiz->esq);
	printf(" ");
	mostra_arvore(raiz->dir);
	printf(")");

}

void insere(abb_int** raiz,int dado){
	abb_int* aux;
	if(*raiz == NULL){
		*raiz = malloc(sizeof(abb_int));
		(*raiz)->dado = dado;
		return;
	}
	if(dado > (*raiz)->dado){
		if((*raiz)->dir == NULL){
			aux = malloc(sizeof(abb_int));
			aux->dado = dado;
			(*raiz)->dir = aux;
			return;
		}
		else{
			insere(&((*raiz)->dir), dado);
			return;
		}
	}
	else if(dado <= (*raiz)->dado){
		if((*raiz)->esq == NULL){
			aux = malloc(sizeof(abb_int));
			aux->dado = dado;
			(*raiz)->esq = aux;
			return;
		}
		else{
			insere(&((*raiz)->esq), dado);
			return;
		}
	}
}
void comprime(ab_int **p_raiz, int rotacoes) {
    /* ajuda a comprimir uma arvore desbalanceada */
	if(p_raiz == NULL || *p_raiz == NULL)
		return;
	if(rotacoes <= 0)
		return;
	rotaciona_esquerda(p_raiz);
	rotacoes--;
	comprime(&((*p_raiz)->dir), rotacoes);
}
int main(){
	int N, i, dado;
	abb_int** raiz = criar_arvore();
	scanf("%d", &N);
	for(i = 0;i < N; i++){
		scanf("%d", &dado);
		insere(raiz, dado);
	}
	mostra_arvore(*raiz);



	return 0;
}