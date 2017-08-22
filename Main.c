#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Lista.h"

int main(void){

	Lista* openList = cria_lista();
	Lista* closedList = cria_lista();
	Tabuleiro* tabuleiro = cria_tabuleiro(6, 6); //depois passar o tabuleiro

	Node* final = cria_node_final(4, 5);
	Node* start = cria_node(1, 2, *final, 0, tabuleiro);

	insere_lista_final_start(closedList, *start);

	
	Elem* el = *closedList;
	while(el != NULL){

		//variação de zero a 1 - talvez utilizar uma função sen?
		//Agora tenho que pegar os vizinhos e adicionar na open list
		int possiblesX[3] = { el->dados.x - 1, el->dados.x, el->dados.x + 1};
		int possiblesY[3] = { el->dados.y - 1, el->dados.y, el->dados.y + 1};
		int costs[9] = { 14, 10, 14, 10, 0, 10, 14, 10, 14 };
		
		int i = 0, j = 0;
		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){

				Node* node = cria_node(possiblesX[i], possiblesY[j], *final,
									   el->dados.mov_cost + costs[i * 3 + j] , tabuleiro);

				if(node != NULL){
					//verificar se ja existe na closed list ou na open
					if(!existe_na_lista(openList, node->x, node->y) &&
					   !existe_na_lista(closedList, node->x, node->y)){
							insere_lista_final(openList, *node, el);
					}
				}
			}
		}


			printa_lista(openList);

		Elem* element = pega_menor_custo(openList);
		insere_lista_final(closedList, element->dados, element->discovered_by);
		remove_lista(openList, element->dados.x, element->dados.y);
		el = element;
		printf("Elemento x:%i y:%i\n", el->dados.x, el->dados.y );

		if(el->dados.dist == 1){
			printf("Achou!!!\n");
			break;
		}

	}

	printf("Caminho ao contrario agora!\n");
	while(el != NULL){
		printf("x: %i y:%i\n", el->dados.x, el->dados.y);
		el = el->discovered_by;	
	}

	return 0;
}