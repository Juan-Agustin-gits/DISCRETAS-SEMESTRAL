#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


#define MAX_LINE_LENGTH 256
#define MAX_NEIGHBORS 10


typedef struct Node {
    int node;
    int neighbors[MAX_NEIGHBORS];
    int neighbor_count;
} Node;

int verificarArchivo(const char *nombreArchivo);
const char* listar_archivos(const char *carpeta);
int* seleccionar_opciones();
char *strdup(const char *s);
void parse_file(const char *filename, int *order, Node **nodes);

#endif // MENU_H