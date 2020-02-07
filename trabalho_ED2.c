#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
  analisa quantos "pixels" pretos uma "Imagem" tem apartir da entrada seguinte "e" = pixel branco no setor, "f" = pixel preto no setor
   e "p" = partição do setor em mais 4 setores.
   então uma entradas válidas seriam
   eeee
   ffff
   efef
   epfffepeeefe
   o tamanho da "Imagem" é de 1024 pixel particionada em 4 quadrantes que podem ser particionados em mais quatro quadrantes e assim por diantes
*/


typedef struct ArvQuart{
	char dado;
	struct ArvQuart* Conquest;
	struct ArvQuart* War;
	struct ArvQuart* Famine;
	struct ArvQuart* Death;
} ArvQuart;

ArvQuart** criar(){
	ArvQuart** raiz = malloc(sizeof(ArvQuart*));
	return raiz;
}

void libera_memoria(ArvQuart** raiz){
	if(raiz == NULL || *raiz == NULL)
		return;
	libera_memoria(&((*raiz)->Conquest));
	libera_memoria(&((*raiz)->War));
	libera_memoria(&((*raiz)->Famine));
	libera_memoria(&((*raiz)->Death));

	free(*raiz);

}

int interpreta(ArvQuart** raiz, char string[2000], int i){
	ArvQuart* aux;
	if(raiz == NULL)
		return 0;
	if(string[i] == 'p'){
		*raiz = malloc(sizeof(ArvQuart));
		aux = *raiz;
		aux->dado = 'p';
		i++;
		i = interpreta(&(aux->Conquest), string, i);
		i = interpreta(&(aux->War), string, i);
		i = interpreta(&(aux->Famine), string, i);
		i = interpreta(&(aux->Death), string, i);
		return i;
	}
	if(string[i] == 'e'){
		*raiz = malloc(sizeof(ArvQuart));
		aux = *raiz;
		aux->dado = 'e';
		i++;
		return i;
	}
	if(string[i] == 'f'){
		*raiz = malloc(sizeof(ArvQuart));
		aux = *raiz;
		aux->dado = 'f';
		i++;
		return i;
	}
	return i ;
}

void mostra_arvore(ArvQuart* raiz){
	printf("(");
	if(raiz == NULL){
		printf(")");
		return;
	}
	printf("%c ", raiz->dado);
	mostra_arvore(raiz->Conquest);
	printf(" ");
	mostra_arvore(raiz->War);
	printf(" ");
	mostra_arvore(raiz->Famine);
	printf(" ");
	mostra_arvore(raiz->Death);
	printf(")");

}
void junta(ArvQuart** raiz1, ArvQuart** raiz2){
	if(raiz1 == NULL || raiz2 == NULL)
		return;
	if(*raiz1 == NULL || *raiz2 == NULL)
		return;

	if((*raiz2)->dado == 'f' && (*raiz1)->dado != 'f'){
		if((*raiz1)->dado == 'p')
			libera_memoria(&(*raiz1));
		else if((*raiz1)->dado == 'e')
			free(*raiz1);
		*raiz1 = malloc(sizeof(ArvQuart));
		(*raiz1)->dado = 'f';
		return;
	}

	if((*raiz1)->dado != 'f' && (*raiz1)->dado != 'p' && (*raiz2)->dado == 'p'){
		free(*raiz1);
		*raiz1 = malloc(sizeof(ArvQuart));
		(*raiz1)->dado = 'p';
		junta(&((*raiz1)->Conquest), &((*raiz2)->Conquest));
		junta(&((*raiz1)->War), &((*raiz2)->War));
		junta(&((*raiz1)->Famine), &((*raiz2)->Famine));
		junta(&((*raiz1)->Death), &((*raiz2)->Death));
		return;
	}

	if((*raiz1)->dado == 'p' && (*raiz2)->dado == 'p'){
		junta(&((*raiz1)->Conquest), &((*raiz2)->Conquest));
		junta(&((*raiz1)->War), &((*raiz2)->War));
		junta(&((*raiz1)->Famine), &((*raiz2)->Famine));
		junta(&((*raiz1)->Death), &((*raiz2)->Death));
	}

	/*if(((*raiz1)->dado != 'f' && (*raiz1)->dado != 'p') && (*raiz2)->dado == 'e'){
		(*raiz1)->dado = 'e';

	}*/
	else return;

}


int pixels(ArvQuart** raiz, int tamanho){
	if(raiz == NULL || *raiz == NULL)
		return 0;
	ArvQuart* aux = *raiz;
	int x = 0;
	if(aux->dado == 'p'){
		x += pixels(&(aux->Conquest), tamanho/2);
		x += pixels(&(aux->War), tamanho/2);
		x += pixels(&(aux->Famine), tamanho/2);
		x += pixels(&(aux->Death), tamanho/2);
		return x;
		
	}
	else if(aux->dado == 'f'){
		return(tamanho*tamanho) + x;
	}
	else
		return 0;
}


int main(){
	char imagem1[2000];
	char imagem2[2000];
	int x;
	ArvQuart** raiz1 = criar();
	ArvQuart** raiz2 = criar();
	scanf("%s", imagem1);
	scanf("%s", imagem2);
	interpreta(raiz1, imagem1, 0);
	interpreta(raiz2, imagem2, 0);
	junta(raiz1, raiz2);
	x = pixels(raiz1, 32);
	printf("%d\n", x);
	libera_memoria(raiz2);
	libera_memoria(raiz1);
	free(raiz1);
	free(raiz2);
	return 0;

}
