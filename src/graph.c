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

int minDegree(Graph *g) {
	// recibimos grafo, recorremos su matriz y vemos cual fila es la que menos 1's tiene
	int **matrix = g->adjMatrix;
	int orden = g->n;
	int count = 0;
	// inicializamos min como el orden del grafo, para comparar mas facilmente
	int min = orden;
	for(int i = 0; i<orden; i++) {
		for(int j = 0; j<orden; j++) {
			if(matrix[i][j] == 1){
				count++;
			}
		}
		// en la primera iteracion siempre se encontrará un mínimo
		if(count < min) {
			min = count;
		}
		count = 0;
	}

	return min;
}

int maxDegree(Graph *g) {
	// recibimos grafo, recorremos su matriz y vemos cual fila es la que menos 1's tiene
	int **matrix = g->adjMatrix;
	int orden = g->n;
	int count = 0;
	// inicializamos max en 0, para comparar mas facilmente
	int max = 0;
	for(int i = 0; i<orden; i++) {
		for(int j = 0; j<orden; j++) {
			if(matrix[i][j] == 1){
				count++;
			}
		}
		// en la primera iteracion siempre se encontrará un mínimo
		if(count > max) {
			max = count;
		}
		count = 0;
	}

	return max;
}
void removeVertex(Graph* g, int vert){
	if(vert < 0 || vert >= g->n){
		fprintf(stderr, "Error: el vértice %d está fuera del rango.\n", vert);
        return;
	}
	// eliminar fila
	int n = g-> n;
	for(int i = vert; i < n; i++){
		for(int j = 0; j < n+1; j++){
			g->adjMatrix[i][j] = g->adjMatrix[i+1][j];
		}
	}
	// eliminar columna
	for(int j = vert; j < n-1; j++){
		for(int i = 0; i < n; i++){
			g->adjMatrix[i][j] = g->adjMatrix[i][j + 1];
		}
	}
	free(g->adjMatrix[n - 1]);

	g->adjMatrix = (int**)realloc(g->adjMatrix, (n-1)*sizeof(int*));
	if (g->adjMatrix == NULL && n - 1 > 0) {
        fprintf(stderr, "Error al redimensionar la matriz de adyacencia.\n");
        exit(1);
    }
	g->n--;

}