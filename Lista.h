typedef struct node{
	int x;
	int y;
	int dist;
	int mov_cost;
	int total_cost;
} Node;

typedef struct tabuleiro{
	int rows;
	int columns;
} Tabuleiro;

struct elemento{
	struct node dados;
	struct elemento *prox;
	struct elemento *discovered_by;
};
typedef struct elemento Elem;

typedef struct elemento* Lista;

struct node* cria_node(int x, int y, struct node final, int mov_cost, Tabuleiro* tabuleiro);

struct node* cria_node_final(int x, int y);

Tabuleiro* cria_tabuleiro(int rows, int columns);

Lista* cria_lista();

void libera_lista(Lista* li);

int insere_lista_final(Lista* li, struct node node, struct elemento* discovered_by);

int insere_lista_final_start(Lista* li, struct node node);

int remove_lista(Lista* li, int x, int y);

int existe_na_lista(Lista* li, int x, int y);

Elem* pega_menor_custo(Lista* li);

void printa_lista(Lista* li);