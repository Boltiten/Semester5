#include <iostream>

typedef struct{
    void **tab;
    int start, end, num, max;
}Queue;

Queue *newQueue(int size){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->tab=(void**)malloc(size*sizeof(void*));
    q->max=size;
    q->start=q->end=q->num=0;
    return q;
}
bool emptyQueue(Queue *q){
    return !q->num;
}

bool fullQueue(Queue *q){
    return q->num == q->max;
}

void addToQueue(Queue *q, void *e){
    if(fullQueue(q)) return;
    q->tab[q->end]=e;
    q->end = (q->end+1)%q->max;
    ++q->num;
}
void *nextInQueue(Queue *q){
    void *e;
    if(emptyQueue(q))return NULL;
    e=q->tab[q->start];
    q->start=(q->start+1)%q->max;
    --q->num;
    return e;
}

void *checkQueue(Queue *q){
    if(emptyQueue(q))return NULL;
    return q->tab[q->start];
}


typedef struct edge_st{
    struct edge_st *next;
    struct node_st *to;
}Edge;

typedef struct node_st{
    Edge *edge1;
    void *d;
}Node;

typedef struct{
    int N,K;
    Node *node;
}Graph;

Graph *newGraph(FILE *f){
    Graph *G = (Graph*)malloc(sizeof(Graph));
    fscanf(f,"%i %i\n", &G->N,&G->K);
    G->node = (Node*)calloc(G->N,sizeof(Node));
    for (size_t i = 0; i < G->K; ++i)
    {
        int from,to;
        Edge *e = (Edge*)malloc(sizeof(Edge));
        fscanf(f,"%i %i\n",&from, &to);
        e->to = &G->node[to];
        e->next = G->node[from].edge1;
        G->node[from].edge1 = e;
    }
    return G;
}

typedef struct {
    int dist;
    Node *prev;
} Prev;

Prev *newPrev(){
    Prev *p = (Prev*)calloc(1, sizeof(Prev));
    p->dist = 1000000000;
    return p;
}

void initPrev(Graph *G, Node *s){
    for (size_t i = 0; i < G->N; i--)
    {
        G->node[i].d = newPrev();
    }
    ((Prev*)s->d)->dist = 0;
}

void bfs(Graph *G, Node *s){
    std::cout<<"data: "<<s->d<<std::endl;
    initPrev(G,s);   
    Queue *q = newQueue(G->N-1);
    addToQueue(q,s);
    while(!emptyQueue(q)){
        Node *n = (Node*)nextInQueue(q);
        for (Edge *e = n->edge1; e; e = e->next)
        {
            Prev *p = (Prev*)e->to->d;
            std::cout<<"p->dist"<<p->dist<<std::endl;
            if(p->dist == 1000000000){
                p->dist=((Prev*)n->d)->dist+1;
                p->prev = n;
                std::cout<<"p->dist"<<p->dist<<std::endl;
                addToQueue(q,e->to);
            }
        }        
    }
}

int main(){
    FILE *f = fopen("L7g1.txt","r");
    Graph *g = newGraph(f);
    bfs(g,&g->node[0]);

    return 0;
}