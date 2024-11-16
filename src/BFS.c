#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "COLA.h"
#include "graph.h"

// Función para verificar si un grafo es conexo excluyendo ciertos nodos
bool esConexo(Graph *g, int excluidos[], int tamanoExcluidos) {
    int *visitados = calloc(g->n, sizeof(int));

    // Marcar nodos excluidos como visitados
    for (int i = 0; i < tamanoExcluidos; i++) {
        visitados[excluidos[i]] = 1;
    }

    // Encontrar un nodo inicial válido
    int nodoInicial = -1;
    for (int i = 0; i < g->n; i++) {
        if (!visitados[i]) {
            nodoInicial = i;
            break;
        }
    }

    if (nodoInicial == -1) {
        free(visitados);
        return false;  // No hay nodos válidos
    }

    // Realizar BFS
    struct cola *q = crearCola();
    enColar(q, nodoInicial);
    visitados[nodoInicial] = 1;

    while (!esVacia(q)) {
        int actual = desColar(q);
        for (int i = 0; i < g->n; i++) {
            if (g->adjMatrix[actual][i] == 1 && !visitados[i]) {
                enColar(q, i);
                visitados[i] = 1;
            }
        }
    }

    liberarCola(q);

    // Verificar si todos los nodos no excluidos fueron visitados
    for (int i = 0; i < g->n; i++) {
        if (!visitados[i]) {
            free(visitados);
            return false;
        }
    }

    free(visitados);
    return true;
}

int calcularConectividad(Graph *g) {
    for (int k = 1; k <= g->n; k++) {
        // Generar combinaciones de k nodos para excluir
        int excluidos[k];
        for (int i = 0; i < k; i++) {
            excluidos[i] = i;
        }

        int fin = 0;
        while (!fin) {
            if (!esConexo(g, excluidos, k)) {
                return k;
            }

            // Generar la siguiente combinación
            fin = 1;
            for (int i = k - 1; i >= 0; i--) {
                if (excluidos[i] < g->n - k + i) {
                    excluidos[i]++;
                    for (int j = i + 1; j < k; j++) {
                        excluidos[j] = excluidos[j - 1] + 1;
                    }
                    fin = 0;
                    break;
                }
            }
        }
    }

    return g->n - 1;
}



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
        //printf(" vertice actual: %d ", ActVert);
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