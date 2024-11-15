#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "COLA.h"
#include "graph.h"


int bfs(struct Graph* graph, int StartVert){
    struct cola* q = crearCola();

    int* visitados  = (int*)malloc(graph->n * sizeof(int));
    for (int i = 0; i< graph->n;i++){
        visitados[i] = 0;
    }
    
    visitados[StartVert] = 1;
    enColar(q, StartVert);

    int contador_visitados = 1;
    while (!esVacia(q)){
        int ActVert = desColar(q);
        printf(" vertice actual: %d ", ActVert);
        
        // analizar vecindad
        for (int i = 0; i < graph->n; i++){
            if (graph->adjMatrix[ActVert][i] == 1 && !visitados[i]){
                visitados[i] = 1;
                enColar(q,i);
                contador_visitados++;
            }
        }
    }
    int esConexo;
    if(contador_visitados == graph->n){
        esConexo = 1;

    }else{
        esConexo = 0;
    }
    
    printf("\n");
    liberarCola(q);
    free(visitados);
    return esConexo;

}