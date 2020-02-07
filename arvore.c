#include <stdio.h>
#include <stdlib.h>


typedef struct ab_char{
	char dado;
	struct ab_char* esq;
	struct ab_char* dir;
}ab_char;


typedef struct ab_int{
	int dado;
	struct ab_int* esq;
	struct ab_int* dir;
}ab_int;

void mostra_arvore(ab_int* raiz){
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

int altura(ab_int* raiz){
	if(raiz == NULL)
		return 0;

	int esquerda = altura(raiz->esq);
	int direita = altura(raiz->dir);
	if(esquerda > direita)
		return esquerda + 1;
	else
		return direita + 1;

}

ab_char** criar(){
	ab_char** raiz = malloc(sizeof(ab_char*));
	return raiz;
}

ab_int** criar_int(){
	ab_int** raiz = malloc(sizeof(ab_int*));
	return raiz;
}


void rotaciona_esquerda(ab_int **p_raiz) {
    /* Insira o código aqui. */
    if(*p_raiz == NULL)
    	return;
    if((*p_raiz)->dir == NULL)
    	return;
    ab_int *aux = (*p_raiz)->dir;
    ab_int *troca = (*p_raiz);
    troca->dir = aux->esq;
    aux->esq = troca;
    *p_raiz = aux;
}

void rotaciona_direita(ab_int **p_raiz) {
    /* Insira o código aqui. */
    if(*p_raiz == NULL)
    	return;
    if((*p_raiz)->esq == NULL)
    	return;
    ab_int *aux = (*p_raiz)->esq;
    ab_int *troca = (*p_raiz);
    troca->esq = aux->dir;
    aux->dir = troca;
    *p_raiz = aux;
}

void comprime(ab_int **p_raiz, int rotacoes) {
    /* ajuda a comprimir uma arvore desbalanceada */
	if(p_raiz == NULL || *p_raiz == NULL)
		return;
	if(rotacoes < 1)
		return;
	rotaciona_esquerda(p_raiz);
	rotacoes--;
	comprime(&((*p_raiz)->dir), rotacoes);
}
/*void comprime(ab_int **p_raiz, int rotacoes) {
     ajuda a comprimir uma arvore desbalanceada 
    int altura = 1, i;
    if(p_raiz == NULL || *p_raiz == NULL)
    	return;
    ab_int *aux = *p_raiz;

    while(altura <= rotacoes && aux != NULL){
    	if(altura == 1){
    		aux = (*p_raiz)->esq;
    		rotaciona_direita(p_raiz);
    		*p_raiz = aux;
    	}
    	else{
    		aux = *p_raiz;
			for(i = 2;i < altura && aux != NULL; i++){
				aux = aux->esq;
			}
			rotaciona_direita(&(aux->esq));
		}
    	altura++;
    }
}*/

/*void insere(ab_char** p_raiz, ab_char* e) {
    // insere na arvore
    if(p_raiz == NULL || *p_raiz == NULL){
    	*p_raiz = e;
    	return;
    }
    if(altura((*p_raiz)->dir) < altura((*p_raiz)->esq))
    	insere(&(*p_raiz)->dir, e);
    else
    	insere(&(*p_raiz)->esq, e);

}*/


void em_lista(ab_int **p_raiz) {
    /* transforma a arvore em uma lista rotacionando à esquerda*/
    if(p_raiz == NULL || *p_raiz == NULL)
    	return;
    if((*p_raiz)->esq != NULL){
    	rotaciona_direita(p_raiz);
    	em_lista(&((*p_raiz)->esq));
    	em_lista(p_raiz);
    } 
    if((*p_raiz)->dir != NULL){
    	em_lista(&((*p_raiz)->dir));
    }
}

void dsw(ab_int **p_raiz) {
    /* Balanceia a arvore */
    if(p_raiz == NULL || *p_raiz == NULL)
    	return;
    int alt;
    em_lista(p_raiz);
    alt  = altura(*p_raiz);
    alt = (alt - 1)/2;
    while(alt > 0){
    	comprime(p_raiz, alt);
    	alt /= 2;
    }

}
int main(){
	ab_char** raiz = criar();
	ab_int** raiz_int = criar_int();
	*raiz_int = malloc(sizeof(ab_int));
	//*raiz_int = NULL;
	*raiz = malloc(sizeof(ab_char));
	ab_char* x = *raiz;
	x->dado = 'A';
	x->dir = malloc(sizeof(ab_char));
	x->esq = malloc(sizeof(ab_char));
	x->dir->dado = 'B';
	x->esq->dado = 'C';
	x->dir->dir = malloc(sizeof(ab_char));
	x->dir->esq = malloc(sizeof(ab_char));
	x->esq->dir = malloc(sizeof(ab_char));
	x->esq->esq = malloc(sizeof(ab_char));
	x->dir->dir->dado = 'D';
	x->dir->esq->dado = 'E';
	x->esq->dir->dado = 'F';
	x->esq->esq->dado = 'G';
	ab_int* y = *raiz_int;
	y->dado = 6;
	y->esq = malloc(sizeof(ab_int));
	//y->dir = malloc(sizeof(ab_int));
	y->esq->esq = malloc(sizeof(ab_int));
	y->esq->esq->esq = malloc(sizeof(ab_int));
	y->esq->dado = 5;
	//y->dir->dado = 3;
	y->esq->esq->dado = 4;
	y->esq->esq->esq->esq = malloc(sizeof(ab_int));
	y->esq->esq->esq->dado = 3;
	y->esq->esq->esq->esq->dado = 2;
	y->esq->esq->esq->esq->esq = malloc(sizeof(ab_int));
	y->esq->esq->esq->esq->esq->dado = 1;

	mostra_arvore(*raiz_int);
	dsw(raiz_int);
	printf("\n");
	mostra_arvore(*raiz_int);

}