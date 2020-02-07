#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_encadeada_char.h"

elemento_t* elemento(const info_t* info, elemento_t* ant, elemento_t* prox){
	if(ant == NULL)
		return 0;
	elemento_t* no;
	no = (elemento_t*) malloc(sizeof(elemnto_t));
	if(no == NULL)
		return 0;
	no -> info = info;
	no -> prox = (*ant);
	ant -> prox = no;
	return 1;
}
void libera(elemento_t** ptr){
	
}