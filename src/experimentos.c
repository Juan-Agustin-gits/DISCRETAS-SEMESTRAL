#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "BFS.h"
#include "MENU.h"

// Compilar usando gcc experimentos.c graph.c COLA.c BFS.c MENU.c -o exp

int main(int argc, char const *argv[]){
	clock_t start = clock();
	if (argc < 2) {
        printf("Por favor, ejecuta el programa de la siguiente forma: %s <nombre_del_archivo>\n", argv[0]);
        return 1; // Terminar el programa si no se proporciona un archivo
    }

	verificarArchivo(argv[1]);

    int orden;
	Node *nodes = NULL;

    parse_file(argv[1], &orden, &nodes);

    Graph* g = createGraph(orden);
    printf("Orden: %d\n", orden);

	for (int i = 0; i < orden; i++) {
	    //printf("Valor %d: ", nodes[i].node);
	    for (int j = 0; j < nodes[i].neighbor_count; j++) {

	        //INTERACTUAR CON LOS VALORES

	        addEdge(g, i, nodes[i].neighbors[j] -1 );
	    }
	    //printf("\n");
	}

	printf("\n");
	printf("Matriz de adyacencia del grafo ingresado:\n");
	printGraph(g);
    printf("Grado mínimo: %d\n", minDegree(g));
    printf("Grado máximo: %d\n", maxDegree(g));


	printf("\n");
	int conec = g->n;
	for(int k = 0;k < g->n; k++){
		Graph* g2 = copyGraph(g);
		removeVertex(g2,k);
		if(!bfs(g2,k)){
			conec = k+1;
			printf("El Grafo ingresado tiene conectividad %d\n", conec);
			printf("Maximo k = %d tal que g es %d-conexo.\n", conec, conec);
			break;
		}
		freeGraph(g2);
	}

	if (conec == g->n) {
        printf("El Grafo es %d-Conexo\n", conec);
    }
    clock_t end = clock();

    double tiempo_transcurrido = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%.6f\n", tiempo_transcurrido);
	return 0;
}

/* Version antigua de main.c
	
	Graph* g = createGraph(orden);


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
*/
