#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

struct elemento{
	struct node dados;
	struct elemento *discovered_by;
};
typedef struct elemento Elem;


struct node* cria_node(int x, int y, struct node final, int current_cost){

	struct node* node;
	node = (struct node*)malloc(sizeof(struct node));
	node->x = x;
	node->y = y;
	node->current_cost = current_cost;

	int distX = abs(final.x - x);
	int distY = abs(final.y - y);
	node->dist = distX + distY;

	return node;
}

Lista* cria_lista() {

	Lista* li = (Lista*)malloc(sizeof(Lista));
	if(li != NULL)
		*li = NULL;

	return li;
}

void libera_lista(Lista* li){
	
	if(li != NULL){
		Elem* no;
		while((*li) != NULL){
			no = *li;
			*li = (*li)->discovered_by;
			free(no);
		}
		free(li);
	}
}

int insere_lista_final(Lista* li, struct node no, Elem* discovered_by){

	if(li == NULL) return 0;

	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) return 0;
	no->dados = al;
	no->discovered_by = discovered_by;

	*li = no;

	return 1;
}
