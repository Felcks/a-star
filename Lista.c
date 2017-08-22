#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

struct node* cria_node(int x, int y, struct node final, int mov_cost, Tabuleiro* tabuleiro){

	if(x < 0 || y < 0)
		return NULL;
	else if(x >= tabuleiro->rows || y >= tabuleiro->columns)
		return NULL;

	struct node* node;
	node = (struct node*)malloc(sizeof(struct node));
	node->x = x;
	node->y = y;
	node->mov_cost = mov_cost;

	int distX = abs(final.x - x);
	int distY = abs(final.y - y);
	node->dist = distX + distY;

	node->total_cost = node->dist + node->mov_cost;

	return node;
}

struct node* cria_node_final(int x, int y){

	struct node* node;
	node = (struct node*)malloc(sizeof(struct node));
	node->x = x;
	node->y = y;
	node->mov_cost = -1;
	node->dist = -1;
	node->total_cost = -1;

	return node;
}

Tabuleiro* cria_tabuleiro(int rows, int columns){

	Tabuleiro* tabuleiro;
	tabuleiro = (Tabuleiro*)malloc(sizeof(Tabuleiro));
	tabuleiro->rows = rows;
	tabuleiro->columns = columns;

	return tabuleiro;
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
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}

int insere_lista_final(Lista* li, struct node node, Elem* discovered_by){
	if(li == NULL) return 0;

	if(node.x == discovered_by->dados.x && node.y == discovered_by->dados.y)
		return -1;

	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) return 0;
	no->dados = node;
	no->discovered_by = discovered_by;
	no->prox = NULL;

	if((*li) == NULL){ //Lista vazia
		*li = no;
	}
	else{
		Elem* aux = *li;
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = no;
	}

	return 1;
}

int insere_lista_final_start(Lista* li, struct node node){
	if(li == NULL) return 0;

	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) return 0;
	no->dados = node;
	no->discovered_by = NULL;
	no->prox = NULL;

	if((*li) == NULL){ //Lista vazia
		*li = no;
	}
	else{
		Elem* aux = *li;
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = no;
	}

	return 1;
}

int remove_lista(Lista* li, int x, int y){

	if(*li == NULL)
		return -1;

	Elem* aux = *li;
	Elem* ant = NULL;

	while(aux != NULL){
		if(aux->dados.x == x && aux->dados.y == y){
			if(ant == NULL){
				*li = aux->prox;
			}
			else{
				ant->prox = aux->prox;
			}
			break;
		}
		aux = aux->prox;
	}

	return 1;
}


int existe_na_lista(Lista* li, int x, int y){

	if(*li == NULL)
		return 0;

	Elem* aux = *li;
	while(aux != NULL){
		if(aux->dados.x == x && aux->dados.y == y){
			return 1;
			break;
		}
		aux = aux->prox;
	}

	return 0;
}

Elem* pega_menor_custo(Lista* li){

	if(*li == NULL)
		return NULL;

	Elem* menor = *li;
	Elem* aux = *li;
	while(aux != NULL){
		if(aux->dados.total_cost < menor->dados.total_cost){
			menor = aux;
		}
		aux = aux->prox;
	}

	return menor;
}

void printa_lista(Lista* li){
	Elem* aux = *li;
	while(aux != NULL){
		printf("x:%i y:%i total_cost:%i\n", aux->dados.x, aux->dados.y, aux->dados.total_cost);
		aux = aux->prox;
	}
	return;
}
