#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int verificarArchivo(const char *nombreArchivo);
const char* listar_archivos(const char *carpeta);
int* seleccionar_opciones();
char *strdup(const char *s);


#endif // MENU_H