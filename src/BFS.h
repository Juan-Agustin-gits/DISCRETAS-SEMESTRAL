#ifndef BFS_H
#define BFS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "COLA.h"
#include "graph.h"

extern struct cola cola;

int bfs(struct Graph* graph, int StartVert);

#endif // BFS_H
