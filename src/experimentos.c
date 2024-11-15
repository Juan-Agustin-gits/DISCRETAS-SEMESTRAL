#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "BFS.h"
// Compilar usando gcc main.c graph.c COLA.C BFS.C -o main
int main(int argc, char const *argv[]){
	// Primera linea de entrada, orden del grafo.
	int orden;
	scanf("%d", &orden);
	if (orden <= 0){
		fprintf(stderr, "Error. Orden del grafo no válido.\n");
		exit(1);
	}
	Graph* g = createGraph(orden);
	// Lectura de conexiones del grafo (se asume que se comienza desde el 1 para el usuario):
	for (int i = 0; i < orden; i++){
		printf("%d: ", i+1);
		for (int j = 0; j < orden; j++){
			int valor;
			scanf("%d", &valor);
			if (valor > orden) {
				fprintf(stderr,"Valor %d es superior al orden del grafo.\n", valor);
				exit(1);
			}
			if (valor == -1){
				break;
			}
			addEdge(g, i, valor-1);
		}
	}

	printf("Matriz de adyacencia del grafo ingresado:\n");
	printGraph(g);
	verificarAdjMatrix(g);

	if(!bfs(g,0)){
		fprintf(stderr, "Por favor ingresa un grafo conexo.\n");
        freeGraph(g);
        exit(1);
	}
	
	int conec = g->n;
	for(int k = 0;k < g->n; k++){
		Graph* g2 = copyGraph(g);
		removeVertex(g2,k);
		if(!bfs(g2,0)){
			conec = k+1;
			printf("El Grafo ingresado tiene %d - Conectividad\n", conec);
			freeGraph(g2);
			break;
		}
		freeGraph(g2);
	}

	if (conec == g->n) {
        printf("El Grafo es %d-Conexo\n", conec);
    }
	freeGraph(g);
	return 0;
}

