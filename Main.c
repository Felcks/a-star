#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{
	int x;
	int y;
	int dist;
	int current_cost;
	struct node* discovered_by;
};
typedef struct node Node;

struct node* cria_node(int x, int y, struct node final, int current_cost, struct node* discovered_by){

	struct node* node;
	node = (struct node*)malloc(sizeof(struct node));
	node->x = x;
	node->y = y;
	node->current_cost = current_cost;
	node->discovered_by = discovered_by;

	int distX = abs(final.x - x);
	int distY = abs(final.y - y);
	node->dist = distX + distY;

	return node;
}

int distance(Node node, Node target){

	return abs(target.x - node.x) + abs(target.y - node.y);
}


int main(void) {
		
	Node openList[100];
	int open_count = 0;

	Node closedList[100];
	int closed_count = 0;



	int dimX = 5;
	int dimY = 5;
	int tabuleiro[dimX][dimY];
	
	int row = 0;
	int column = 0;

	for(row = 0; row < dimY; row++){
		for(column = 0; column < dimX; column++){
			tabuleiro[row][column] = 0;
		}
	}

	for(row = 0; row < dimY; row++){
		for(column = 0; column < dimX; column++){
			printf("%i ", tabuleiro[row][column]);
		}
		printf("\n");
	}

	struct node empty;
	struct node* final = cria_node(4, 4, empty, 0, NULL);
	struct node* start = cria_node(0, 0, *final, 0, NULL);


	closedList[closed_count] = *start;
	closed_count++;
	while(distance(closedList[closed_count - 1], *final) > 1){

		Node node = closedList[closed_count - 1];

		for(row = 0; row < dimY; row++){
			for(column = 0; column < dimX; column++){

				if(abs(row - node.x) + abs(column - node.y) == 1){
					struct node* no = cria_node(row, column, *final, node.current_cost + 10, &node);

					int i = 0;
					for(i = 0; i < open_count; i++){
						if(openList[i].x == row && openList[i].y == column){
							//vou adicionar o melhor
							if(openList[i].current_cost + openList[i].dist < no->dist + no->current_cost)
								continue;
							else{
								openList[i] = *no;
							}
						}
					}

					openList[open_count] = *no;
					open_count++;

					//printf("ROW %i COLUMN %i DIST %i \n", row, column, no->dist + no->current_cost);
				}
				else if(abs(row - node.x) == 1 &&  abs(column - node.y) == 1){
					struct node* no = cria_node(row, column, *final, node.current_cost + 14, &node);

					int i = 0;
					for(i = 0; i < open_count; i++){
						if(openList[i].x == row && openList[i].y == column){
							//vou adicionar o melhor
							if(openList[i].current_cost + openList[i].dist < no->dist + no->current_cost)
								continue;
							else{
								openList[i] = *no;
							}
						}
					}

					openList[open_count] = *no;
					open_count++;

					//printf("ROW %i COLUMN %i DIST %i \n", row, column, no->dist + no->current_cost);
				}
			}
		}

		int i = 0;
		int melhor = 0;
		int menorCusto = openList[i].dist + openList[i].current_cost;

		for(i = 1; i < open_count; i++){

			if(openList[i].dist + node.current_cost < menorCusto){
				melhor = i;
				menorCusto = openList[i].dist + openList[i].current_cost;
			}
		}

		closedList[closed_count] = openList[melhor];
		closed_count++;

		printf("%i %i\n", openList[melhor].x, openList[melhor].y);

		openList[melhor] = openList[open_count - 1];
		open_count--;


		Node last = closedList[closed_count - 1];
		if(distance(last, *final) == 1){
			printf("distancia e 1\n");
			break;
		}

	
	}


	return 0;
}