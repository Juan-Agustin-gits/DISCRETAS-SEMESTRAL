#include <stdio.h>
#include <stdlib.h>>
#include <stdbool.h>>
#define SIZE 100
struct cola{
    int items[SIZE];
    int start;
    int end;
}cola;

struct cola* crearCola(){
    struct cola* q = malloc(sizeof(struct cola));
    q ->start = -1;
    q ->end = -1;
    return q;
};

int esVacia(struct cola* q){
    if(q ->end == -1){
        return 1;
    
    }
    else{
        return 0;
    }
};

void enColar(struct cola* q, int valor){
    if (q -> end == SIZE - 1){
        printf("\n Cola llena");
    }else{
        if (q -> start == -1){
            q -> start = 0;
        }
        q -> end++;
        q -> items[q -> end] = valor;
    }

}
int desColar(struct cola* q){
    int item;
    if(esVacia(q)){
        printf("cola vacía ");
        item = - 1;
    }else{
        item = q -> items[q -> start];
        q -> start++;
        if(q -> start > q -> end){
            q -> start = q -> end = -1;
        }
        
    }
    return item;
}
void imprimirCola(struct cola* q){
    int i = q -> start;

    if (esVacia(q)){
        printf("la cola esta vacía");
    }else{
        printf("\n Cola \n");
        for (i = q -> start; i < q -> end + 1; i++)
        {
            printf("%d", q -> items[i]);
        }
        
    }

}
int BFS(int Grafo[], int nodo_inicial, int tamaño){
    bool visitado[tamaño];

}