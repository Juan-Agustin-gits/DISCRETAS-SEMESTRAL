#ifndef BFS_H
#define BFS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "COLA.h"
#include "graph.h"

extern struct cola cola;

int bfs(struct Graph* graph, int StartVert);
bool esConexo(Graph *g, int excluidos[], int tamanoExcluidos);
int calcularConectividad(Graph *g);

#endif // BFS_H
