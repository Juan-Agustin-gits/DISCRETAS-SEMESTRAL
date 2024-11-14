#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "BFS.h"
// Compilar usando gcc main.c graph.c -o main

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

	printf("Matriz de adyacencia del grafo ingresada:\n");
	printGraph(g);
	if(bfs(g,0)){
	    printf("El grafo es conexo.\n");
	}else{
		printf("El grafo NO es conexo.\n");
	}
	freeGraph(g);
	return 0;
}

