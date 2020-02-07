#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct lse_int{
    int dado;
    struct lse_int *prox;
};

typedef struct lse_int* lista;
typedef struct lse_int elemento;

void inserir_final(lista *li, int dado){
    elemento* aux;
    if(*li == NULL){
        aux = malloc(sizeof(elemento));
        *li = aux;
        aux->prox = NULL;
        aux->dado = dado;
    }
    else{
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = malloc(sizeof(elemento));
        aux->prox->dado = dado;
        aux->prox->prox = NULL;
    }
}

void remover_valor(lista* li, int valor){
    elemento *atual, *ant;
    int contador = 0;
    atual = *li;
    ant = *li;
    while(atual != NULL){
        if(atual->dado == valor){
            ant->prox = atual->prox;
            if(atual == *li){
                *li = (*li)->prox;
                free(atual);
            }
            else
                free(atual);
            atual = NULL;
            atual = ant->prox;
            contador++;
        }
        else{
            ant = atual;
            atual = atual->prox;
        }
    }
    printf("%d\n",contador);
}

void inserir_inicio(lista* li,int dado){
    elemento* novo;
    novo = malloc(sizeof(elemento));
    if(novo == NULL){
        return;
    }
    if(*li == NULL){
        *li = novo;
        novo->prox = NULL;
        novo->dado = dado;
    }
    else{
        novo -> dado = dado;
        novo -> prox = *li;
        (*li) = novo;
    }   
}

void remover_inicio(lista* li){
    elemento* aux;
    aux = *li;
    *li = (*li)->prox;
    printf("%d\n", aux->dado);
    free(aux);
    aux = NULL;
}

void remover_posicao(lista* li, int dado){
    elemento *atual, *ant;
    int contador = 1;
    atual = *li;
    ant = *li;
    if(dado == 1){
        printf("%d\n", atual->dado);
        *li = atual->prox;
        free(atual);
        return;
    }
    while(contador != dado){
        ant = atual;
        atual = atual->prox;
        contador++;
    }
    ant->prox = atual->prox;
    printf("%d\n", atual->dado);
    free(atual);
    atual = NULL;
}

void remover_final(lista* li){
    elemento* aux;
    aux = *li;
    if(aux->prox == NULL){
        printf("%d\n", aux->dado);
        free(aux);
        *li = NULL;
        return;
    }
    while(aux->prox->prox != NULL){
        aux = aux->prox;
    }
    printf("%d\n", aux->prox->dado);
    free(aux->prox);
    aux->prox = NULL;
}
void printaelibera(lista* li){
    elemento *aux = *li;
    if(li == NULL || *li == NULL) return;
    printf("\n");

    while(aux!= NULL){
        printf("%d\n", aux->dado);
        aux = aux->prox;
    }
    while(*li != NULL){
        aux = *li;
        *li = (*li) -> prox;
        free(aux);
        aux = NULL;
    }
}

void trocar(lista *li, int dado, int troca){
    elemento* aux;
    aux = *li;
    while(aux->dado != dado && aux->prox !=NULL){
        aux = aux->prox;
    }
    aux->dado = troca;
}

void ocorrencias(lista* li, int valor){
    elemento* aux;
    int contador = 0;
    aux = *li;
    while(aux != NULL){
        if(aux->dado == valor){
            contador++;
        }
        aux = aux->prox;
    }
    printf("%d\n", contador);
}

int main(){
    char letra;
    lista* li;
    int dado, troca;
    li = (lista*) malloc(sizeof(lista));
    *li = NULL;
    if(li == NULL){
        return 0;
    }
    while(letra != 'X'){
    scanf("%c", &letra);
    if(letra == 'I'){
        scanf("%d", &dado);
        inserir_inicio(li, dado);
    }
    if(letra == 'F'){
        scanf("%d", &dado);
        inserir_final(li, dado);
    }
    if(letra == 'P'){
        remover_final(li);
    }
    if(letra == 'D'){
        remover_inicio(li);
    }
    if(letra == 'V'){
        scanf("%d", &dado);
        remover_valor(li, dado);
    }
    if(letra == 'E'){
        scanf("%d", &dado);
        remover_posicao(li, dado);
    }
    if(letra == 'T'){
        scanf("%d %d", &dado, &troca);
        trocar(li, dado, troca);
    }
    if(letra == 'C'){
        scanf("%d", &dado);
        ocorrencias(li, dado);
    }
    if(letra == 'X'){
        printaelibera(li);
        return 0;
    }
    
    }

}