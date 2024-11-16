#!/bin/bash

PROGRAMA="./exp"

ARCHIVO_GRAFO="experiments/k10"

ITERACIONES=20

ARCHIVO_RESULTADO="experiments/k10.csv"

# Verificar si el archivo de grafo existe
if [ ! -f "$ARCHIVO_GRAFO" ]; then
    echo "El archivo de grafo $ARCHIVO_GRAFO no existe."
    exit 1
fi

# Crear o limpiar el archivo de resultados
echo "Iteración,Tiempo (segundos)" > "$ARCHIVO_RESULTADO"

# Ejecutar el programa 20 veces con el archivo de grafo
for ((i=1; i<=ITERACIONES; i++)); do
    # Ejecutar el programa y capturar el tiempo desde la última línea de su salida
    tiempo=$("$PROGRAMA" "$ARCHIVO_GRAFO" | tail -n 1)

    # Guardar la iteración y el tiempo en el archivo de resultados
    echo "$i,$tiempo" >> "$ARCHIVO_RESULTADO"

    # Mostrar progreso en la terminal
    echo "Iteración $i: $tiempo segundos"
done

echo "Tiempos almacenados en $ARCHIVO_RESULTADO."
