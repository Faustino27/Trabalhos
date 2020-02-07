/** Matricula:SUA 190013249
 *       Nome: Gabriel Faustino Lima da Rocha
 *      Turma: A */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int top;
	double vetor[201];
	
}pilha;

void empilha(pilha* empilhadora, double dado){
	empilhadora->vetor[++empilhadora->top] = dado;
}

double remover(pilha* removedora){
	return removedora->vetor[removedora->top--];

}

double calcula(const char* posfixa) {
    pilha* aux = malloc(sizeof(pilha));
    int i = 0, j = 0;
    double x, a, b;
    char *numero;
    aux->top = -1;
    while(posfixa[i] != '\0'){
    	if(posfixa[i] >= 48 && posfixa[i] <= 57){
    		numero = calloc(12, sizeof(char));
    		j = 0;
    		while(posfixa[i] != ' '){
    			numero[j] = posfixa[i];
    			j++;
    			i++;
    		}
    		x = atof(numero);
    		empilha(aux, x);
    	}
    	if(posfixa[i] == '+'){
    		a = remover(aux);
    		b = remover(aux);
    		x = a + b;
    		empilha(aux, x);
    	}
    	else if(posfixa[i] == '-'){
    		a = remover(aux);
    		b = remover(aux);
    		x = b - a;
    		empilha(aux, x);
    	}
    	else if(posfixa[i] == '*'){
    		a = remover(aux);
    		b = remover(aux);
    		x = a*b;
    		empilha(aux, x);
    	}
    	else if(posfixa[i] == '/'){
    		a = remover(aux);
    		b = remover(aux);
    		x = b/a;
    		empilha(aux, x);
    	}
    	else if(posfixa[i] == '^'){
    		a = remover(aux);
    		b = remover(aux);
    		x = pow(b, a);
    		empilha(aux, x);
    	}
    	i++;
    }
    return x;
}

int main() {
    char posfixa[201];

    scanf("%200[^\n]", posfixa);
    printf("%.5lf\n", calcula(posfixa));

    return 0;
}
