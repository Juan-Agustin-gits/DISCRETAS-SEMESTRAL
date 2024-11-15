#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "BFS.h"
#include "MENU.h"

void imprimirArchivo(const char *rutaArchivo) {
        printf("Intentando abrir el archivo: %s\n", rutaArchivo);  // Imprime la ruta del archivo
    FILE *file = fopen(rutaArchivo, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);  // Imprime cada carácter
    }

    fclose(file);  // Cierra el archivo
}


// Función principal
int main() {
    int choice;
    printf("¿Cómo desea ingresar el grafo para analizar?\n");
    printf("[ 1 ] - Construir manualmente una lista de adyacencia\n");
    printf("[ 2 ] - Importar lista de adyacencia desde archivo\n");
    printf("Seleccione una opción: ");
    scanf("%d", &choice);

    //Graph *g = NULL;

	switch (choice) {
	    case 1: {
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

			int* seleccionadas = seleccionar_opciones();

			if (seleccionadas[0] != 0){
				// Imprimir el grado mínimo y máximo
			    printf("Grado mínimo: %d\n", minDegree(g));
			    printf("Grado máximo: %d\n", maxDegree(g));

			} if (seleccionadas [1] != 0){
				//MATRIZ DE ADYACENCIA
				printf("\n");
				printf("Matriz de adyacencia del grafo ingresada:\n");
				printGraph(g);

			} if (seleccionadas [2] != 0){
				//CONECTIVIDAD & CONEXIVIDAD
				printf("\n");
				int conec = g->n;
				for(int k = 0;k < g->n; k++){
					Graph* g2 = copyGraph(g);
					removeVertex(g2,k);
					if(!bfs(g2,0)){
						conec = k+1;
						printf("El Grafo ingresado tiene %d - Conectividad", conec);
						break;
					}
					freeGraph(g2);
				}

				if (conec == g->n) {
					printf("\n");
			        printf("El Grafo es %d-Conexo\n", conec);
			    }
			}
			// Liberar la memoria del grafo
			freeGraph(g);
			break;
		}
		case 2: {
			    const char *carpeta = "./";  // Ruta de ejemplo
			    const char *rutaArchivo = listar_archivos(carpeta);

			    if (rutaArchivo != NULL) {
			    	if (verificarArchivo(rutaArchivo)) {
			        printf("Archivo seleccionado: %s\n", rutaArchivo);
			        printf("SI FUNCIONAAAAA");
			        imprimirArchivo(rutaArchivo);


					
					Graph* g = cargarGrafoDesdeArchivo(rutaArchivo);
					printf("Grado mínimo: %d\n", minDegree(g));
					printf("Grado máximo: %d\n", maxDegree(g));


					int* seleccionadas = seleccionar_opciones();

					if (seleccionadas[0] != 0){
						// Imprimir el grado mínimo y máximo
					    printf("Grado mínimo: %d\n", minDegree(g));
					    printf("Grado máximo: %d\n", maxDegree(g));

					} if (seleccionadas [1] != 0){
						//MATRIZ DE ADYACENCIA
						printf("\n");
						printf("Matriz de adyacencia del grafo ingresada:\n");
						printGraph(g);

					} if (seleccionadas [2] != 0){
						//CONECTIVIDAD & CONEXIVIDAD
						printf("\n");
						int conec = g->n;
						for(int k = 0;k < g->n; k++){
							Graph* g2 = copyGraph(g);
							removeVertex(g2,k);
							if(!bfs(g2,0)){
								conec = k+1;
								printf("El Grafo ingresado tiene %d - Conectividad", conec);
								break;
							}
							freeGraph(g2);
						}

						if (conec == g->n) {
							printf("\n");
					        printf("El Grafo es %d-Conexo\n", conec);
					    }
					}
					// Liberar la memoria del grafo
					freeGraph(g);
					break;


				    //free(rutaArchivo);  // Liberar la memoria




			        }


			        free((void*)rutaArchivo);  // Liberar memoria
			        break;
			    }

		}
	    default:
	        fprintf(stderr, "Opción no válida.\n");
	        exit(1);
	}



	return 0;
}



 /*
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
	
    // Imprimir el grado mínimo y máximo
    printf("Grado mínimo: %d\n", minDegree(g));
    printf("Grado máximo: %d\n", maxDegree(g));


	//CASO NO CONEXO
	if(!bfs(g,0)){
		fprintf(stderr, "Grafo no conexo.\n");
        freeGraph(g);
        exit(1);
	}
	
	//MATRIZ DE ADYACENCIA
	printf("Matriz de adyacencia del grafo ingresada:\n");
	printGraph(g);

	//CONECTIVIDAD & CONEXIVIDAD
	int conec = g->n;
	for(int k = 0;k < g->n; k++){
		Graph* g2 = copyGraph(g);
		removeVertex(g2,k);
		if(!bfs(g2,0)){
			conec = k+1;
			printf("El Grafo ingresado tiene %d - Conectividad", conec);
			freeGraph(g2);
			break;

		}
		freeGraph(g2);
	}

	if (conec == g->n) {
        printf("El Grafo es %d-Conexo\n", conec);
    }
	freeGraph(g);
	return 0;
}
*/


