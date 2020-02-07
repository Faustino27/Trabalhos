#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct fila{
    char nome[25];
    struct fila *prox;
}fila;

typedef struct fila* Fila;

Fila* criar_fila(){
    Fila* fi;
    fi = (Fila*)malloc(sizeof(Fila));
    *fi = NULL;
    return fi;
}

Fila fila_cresce(Fila* fi, char nome[25]){
    fila *aux, *novo = malloc(sizeof(fila));
    aux = *fi;
    if(aux == NULL){
        *fi = novo;
        strcpy(novo->nome, nome);
        novo->prox = NULL;
        return novo;
        
    }
    while(aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;
    novo->prox = NULL;
    strcpy(novo->nome, nome);
    return novo;

}
Fila roda_fila(Fila* fi, Fila final){
    fila *aux;
    final->prox = malloc(sizeof(fila));
    aux = *fi;
    final = final->prox;
    strcpy(final->nome, aux->nome);
    final->prox = NULL;
    (*fi) = (*fi)->prox;
    free(aux);
    return final;

}
void printa(Fila* fi, Fila final){
    printf("Pessoa da frente: %s\n", (*fi)->nome);
    printf("Pessoa do fim: %s\n", final->nome);
}


int main(){
    int x, i;
    char nome[25];
    Fila* fi = criar_fila(), final;
    while(scanf("%d", &x) <= 0){
        scanf("%s", nome);
        final = fila_cresce(fi, nome);
    }
    
   for(i = 0; i < x; i++){
        final =roda_fila(fi, final);
    }
    printa(fi, final);

    return 0;
}