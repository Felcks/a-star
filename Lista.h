struct node{
	int x;
	int y;
	int dist;
	int current_cost;
};

typedef struct elemento* Lista;

struct node* cria_node(int x, int y, struct node final, int current_cost);

Lista* cria_lista();

void libera_lista(Lista* li);