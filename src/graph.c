#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph* createGraph(int orden) {
	// inicializamos dinamicamente el grafo (para liberar o asignar mas memoria)
	Graph* grafo = (Graph*)malloc(sizeof(Graph));
	if (grafo == NULL){
		fprintf(stderr, "Error al asignar memoria para el grafo.\n");
		exit(1);
	}
	grafo->n = orden;

	grafo->adjMatrix = (int**)malloc(orden * sizeof(int*));
	if (grafo->adjMatrix == NULL) {
		fprintf(stderr, "Error al asignar memoria para la matriz.\n");
		free(grafo);
		exit(1);
	}

	for (int i = 0; i < orden; i++){
		// se asigna memoria a cada fila de la matriz de adyacencia
		grafo->adjMatrix[i] = (int*)malloc(sizeof(int) * orden);
		if(grafo->adjMatrix[i] == NULL) {
			fprintf(stderr, "Error al asignar memoria para adjMatrix[%d].\n", i);
            // Liberar memoria asignada hasta el momento antes de salir
            for (int j = 0; j < i; j++) {
                free(grafo->adjMatrix[j]);
            }
            free(grafo->adjMatrix);
            free(grafo);
            exit(1);
        }
		for (int j = 0; j < orden; j++){
			// inicializamos toda la matriz en 0
			grafo->adjMatrix[i][j] = 0;
		}
	}
	return grafo;
}

void addEdge(Graph *g, int src, int dest) {
	g->adjMatrix[src][dest] = 1;
}

void delEdge(Graph *g, int src, int dest) {
	g->adjMatrix[src][dest] = 0;
}

void printGraph(Graph *g) {
	int n = g->n;
	for (int i = 0; i<n; i++) {
		for(int j = 0; j<n; j++) {
			printf("%d ", g->adjMatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void freeGraph(Graph *g) {
	int n = g->n;
    for (int i = 0; i<n; i++) {
        free(g->adjMatrix[i]);
    }

    free(g->adjMatrix);
    free(g);
}