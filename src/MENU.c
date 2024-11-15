#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>

#define MAX_VALORES 100




int verificarArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return 0;
    }

    int n, a_i, b;
    if (fscanf(archivo, "%d", &n) != 1) {
        fprintf(stderr, "Error al leer el valor de n\n");
        fclose(archivo);
        return 0;
    }

    int ultimo_a = 0;  // Último valor a_i leído para verificar orden ascendente

    for (int i = 0; i < n; i++) {
        // Leer el valor `a_i` y el carácter ':' que sigue
        if (fscanf(archivo, "%d :", &a_i) != 1) {
            fprintf(stderr, "Error al leer el valor %d\n", i + 1);  // Cambio aquí
            fclose(archivo);
            return 0;
        }

        // Verificar que `a_i` esté en orden ascendente y sin repetirse
        if (a_i <= ultimo_a || a_i > n) {
            fprintf(stderr, "Error: el valor %d no cumple el orden ascendente o está fuera de rango\n", a_i);
            fclose(archivo);
            return 0;
        }
        ultimo_a = a_i;

        // Array para verificar unicidad de los valores en la línea
        int valoresLinea[MAX_VALORES];
        int numValores = 0;

        while (fscanf(archivo, "%d", &b) == 1) {
            // Verificar que `b` no sea igual a `a_i`
            if (b == a_i) {
                fprintf(stderr, "Error: el valor %d en la lista no puede ser igual a %d\n", b, a_i);
                fclose(archivo);
                return 0;
            }

            // Verificar que `b` esté en el rango [1, n]
            if (b < 1 || b > n) {
                fprintf(stderr, "Error: el valor %d en la lista de %d está fuera de rango\n", b, i + 1);  // Cambio aquí
                fclose(archivo);
                return 0;
            }

            // Verificar que `b` no esté repetido en la misma línea
            for (int j = 0; j < numValores; j++) {
                if (valoresLinea[j] == b) {
                    fprintf(stderr, "Error: el valor %d está repetido en el vertice %d\n", b, i + 1);  // Cambio aquí
                    fclose(archivo);
                    return 0;
                }
            }

            // Agregar `b` a la lista de valores únicos para la verificación
            valoresLinea[numValores++] = b;

            // Leer y verificar si hay una coma o salto de línea
            char c = fgetc(archivo);
            if (c == '\n' || c == EOF) break;
            if (c != ',') {
                fprintf(stderr, "Error de formato: se esperaba una coma o fin de línea\n");
                fclose(archivo);
                return 0;
            }
        }
    }

    // Verificar que el archivo no tenga líneas adicionales
    char extra;
    if (fscanf(archivo, "%c", &extra) != EOF) {
        fprintf(stderr, "Error: el archivo contiene más de %d líneas\n", n);
        fclose(archivo);
        return 0;
    }

    fclose(archivo);
    return 1;
}

char *strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy) {
        memcpy(copy, s, len);
    }
    return copy;
}

const char* listar_archivos(const char *carpeta) {
    if (carpeta == NULL) {
        printf("La carpeta proporcionada es NULL.\n");
        return NULL;
    }

    struct dirent *entrada;
    DIR *dir = opendir(carpeta);

    if (dir == NULL) {
        printf("No se pudo abrir la carpeta: %s\n", carpeta);
        return NULL;
    }

    char *archivos[100];  // Array para guardar los nombres de los archivos
    int contador = 0;

    // Lee los archivos y los enumera
    while ((entrada = readdir(dir)) != NULL) {
        if (entrada->d_type == DT_REG) {  // Solo archivos regulares
            archivos[contador] = strdup(entrada->d_name);  // Guardar el nombre del archivo
            if (archivos[contador] == NULL) {
                printf("Error al asignar memoria para el archivo %s\n", entrada->d_name);
                closedir(dir);
                return NULL;
            }
            printf("%d. %s\n", contador + 1, archivos[contador]);
            contador++;
        }
    }

    closedir(dir);

    if (contador == 0) {
        printf("No hay archivos en esta carpeta.\n");
        return NULL;
    }

    while (1) {
        int seleccion;
        printf("Selecciona un archivo por número (o -1 para salir): ");
        scanf("%d", &seleccion);

        if (seleccion == -1) {
            printf("Saliendo del programa...\n");
            for (int i = 0; i < contador; i++) {
                free(archivos[i]);
            }
            return NULL;
        }

        if (seleccion >= 1 && seleccion <= contador) {
            // Asigna memoria para la ruta completa
            char *ruta_completa = malloc(PATH_MAX);
            if (ruta_completa == NULL) {
                printf("Error al asignar memoria para la ruta completa.\n");
                for (int i = 0; i < contador; i++) {
                    free(archivos[i]);
                }
                return NULL;
            }

            // Verificar si la carpeta ya contiene el prefijo './'
            if (carpeta[0] == '.' && carpeta[1] == '/') {
                // Carpeta ya tiene './', concatenamos directamente
                snprintf(ruta_completa, PATH_MAX, "%s%s", carpeta, archivos[seleccion - 1]);
            } else {
                // Carpeta no tiene './', concatenamos con './'
                snprintf(ruta_completa, PATH_MAX, "./%s/%s", carpeta, archivos[seleccion - 1]);
            }

            printf("Has seleccionado el archivo: %s\n", ruta_completa);

            // Liberar memoria de los archivos
            for (int i = 0; i < contador; i++) {
                free(archivos[i]);
            }

            return ruta_completa;  // Devolver la ruta completa
        } else {
            printf("Selección inválida. Intenta de nuevo.\n");
        }
    }
}

int* seleccionar_opciones() {
    printf("Opcion 1: Grado maximo y grado minimo. Opcion 2: matriz de adyacencia , Opcion 3: CONECTIVIDAD & CONEXIVIDAD");
    int opcion;
    int* seleccionadas = (int*)malloc(3 * sizeof(int));  // Asignar memoria para 4 opciones
    for (int i = 0; i < 3; i++) {
        seleccionadas[i] = 0;  // Inicializar todas las opciones en 0 (no seleccionadas)
    }
    
    while (1) {
        // Mostrar las opciones al usuario
        printf("Seleccione una opcion:\n");
        for (int i = 0; i < 3; i++) {
            if (seleccionadas[i] == 1) {
                printf("[ X ] - Opcion %d\n", i + 1);
            } else {
                printf("[ %d ] - Opcion %d\n", i + 1, i + 1);
            }
        }

        // Solicitar la opción que el usuario desea seleccionar
        printf("Ingresa una opción (1, 2, 3) o 0 para continuar, -1 para salir: ");
        scanf("%d", &opcion);

        // Si el usuario elige -1, sale del programa
        if (opcion == -1) {
            printf("Saliendo...\n");
            break;
        }

        // Si el usuario ingresa 0, muestra las opciones seleccionadas y termina el programa
        if (opcion == 0) {
            // Verifica si se seleccionó alguna opción antes de continuar
            int es_vacio = 1;
            for (int i = 0; i < 3; i++) {
                if (seleccionadas[i] != 0) {
                    es_vacio = 0;  // Si encontramos un valor diferente a 0, no es igual a {0, 0, 0}
                    break;
                }
            }
            // Hacer la acción si el array es igual a {0, 0, 0}
            if (es_vacio) {
                printf("Seleccione una opcion antes de continuar\n");
            } else {
                printf("Seleccionaste las siguientes opciones: ");
                int primera = 1;
                for (int i = 0; i < 3; i++) {
                    if (seleccionadas[i] == 1) {
                        if (!primera) {
                            printf(" y ");
                        }
                        printf("%d", i + 1);
                        primera = 0;
                    }
                }
                printf("\n");
                break;  // Finaliza el programa después de mostrar las opciones seleccionadas
            }
        }
        // Si el usuario elige una opción válida (1-3), la marca como seleccionada
        else if (opcion >= 1 && opcion <= 3) {
            seleccionadas[opcion - 1] = 1;  // Marca la opción como seleccionada
            printf("Opción %d seleccionada.\n", opcion);
        } else {
            printf("Opción no válida. Por favor, elige una opción entre 1 y 3, o 0 para ver las seleccionadas.\n");
        }
    }

    return seleccionadas;  // Devolvemos el arreglo de opciones seleccionadas
}


