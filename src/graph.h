#ifndef GRAPH_H
#define GRAPH_H 

typedef struct Graph {
	int n;
	int** adjMatrix;
} Graph;

Graph* createGraph(int orden);
void addEdge(Graph *g, int src, int dest);
void delEdge(Graph *g, int src, int dest);
void printGraph(Graph *g);
void freeGraph(Graph *g);
void removeVertex(Graph* g, int vert);
Graph* copyGraph(Graph* g);
void verificarAdjMatrix(Graph *g);

#endif