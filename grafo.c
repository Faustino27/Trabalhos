#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAMANHO 24

/*typedef struct {
    char vertices[TAMANHO];
    unsigned int arestas[TAMANHO][TAMANHO];
    unsigned int ordem;
} grafo_t;*/
typedef struct {
    char vertices[TAMANHO];
    unsigned int arestas[TAMANHO][TAMANHO];
    unsigned int ordem;
} grafo_t;


int idx_vertice(grafo_t* g, char v) {
     //recebe um ponteiro para o grafo e um caractere, e retorna o índice do vértice com o caractere dado, se existir, -1 caso contrário 
    if(g == NULL)
        return -1;
    int i;

    for(i = 0; i < TAMANHO; i++){
    	if(g->vertices[i] == v)
    		return i;
    }
    return -1;
}

/*_Bool aresta(grafo_t* grafo, char origem, char destino) {
   	Insira seu código aqui. 
    int a, b;
    a = idx_vertice(grafo, origem);
    b = idx_vertice(grafo, destino);
    if(a == -1 || b == -1)
    	return false;
    grafo->arestas[a][b] = 1;
    grafo->arestas[b][a] = 1;

    return true;

}*/

/*vertice_t* vertice(grafo_t* g, char chave) {
    Insira seu código aqui. 
	int i;
	char c; 
	if(g == NULL || !(chave >= 65 && chave <= 123))
		return NULL;
	for(i = 0;i < TAMANHO; i++){
		c = g->vertices[i].chave;
		if(c == chave)
			return &g->vertices[i];
	}
	return NULL;
}*/

int grau_de_entrada(grafo_t* g, char vertice) {
    /* Insira seu código aqui. */
    int i = 0, j, k = 0;
     i = idx_vertice(g, vertice);
     if(i == -1)
     	return 0;

    for(j = 0;j< TAMANHO; j++){
    	if(g->arestas[j][i] == 1)
    		k++;
    }
    return k;
}


int main(){
	//grafo_t* g;
	//g = malloc(sizeof(grafo_t));

	/*int x;
	g->vertices[1] = 'A';
	g->vertices[2] = 'B';
	aresta(g, 'A', 'B');
	x = g->arestas[1][2];
	printf("%d", x);*/
	//printf("%p", vertice(g, 0));
}