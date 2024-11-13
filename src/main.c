#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
// Compilar usando gcc main.c graph.c -o main

int main(int argc, char const *argv[])
{
	Graph* graph = createGraph(5);
	if (graph == NULL)
	{
		fprintf(stderr,"Error al crear grafo\n");
		free(graph);
	}
	printGraph(graph);
	addEdge(graph, 1, 4);
	printGraph(graph);
	addEdge(graph, 0, 2);
	printGraph(graph);
	delEdge(graph, 0, 2);
	printGraph(graph);

	freeGraph(graph);
	return 0;
}

