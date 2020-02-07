#include <stdio.h>
#include <stdlib.h>

typedef struct arvore{
	char c;
	struct arvore* dir;
	struct arvore* esq;
} arvore;

void rotaciona_esquerda(ab_char **p_raiz) {
    /* Insira o código aqui. */
    if(*p_raiz == NULL)
    	return;
    if((*p_raiz)->dir == NULL)
    	return;
    ab_char *aux = (*p_raiz)->dir;
    ab_char *troca = (*p_raiz);
    troca->dir = aux->esq;
    aux->esq = troca;
    *p_raiz = aux;
}

void mostra_arvore(ab_char* raiz){
	printf("(");
	if(raiz == NULL){
		printf(")");
		return;
	}
	printf("%c ", raiz->dado);
	mostra_arvore(raiz->esq);
	printf(" ");
	mostra_arvore(raiz->dir);
	printf(")");

}


void em_lista(ab_char **p_raiz) {
    /* Insira o código aqui. */
    if(*p_raiz == NULL || p_raiz == NULL)
    	return;

    if((*p_raiz)->dir != NULL){
    	rotaciona_esquerda(p_raiz);
    }
}

int main(){
	

}