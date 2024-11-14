#ifndef COLA_H
#define COLA_H

#define SIZE 100  // Definir SIZE



// Declaración de la variable global `cola` como `extern`
// Esto indica que la variable está definida en otro archivo (en `COLA.c`).
extern struct cola cola;

// Declaración de funciones
struct cola* crearCola();
void enColar(struct cola* q, int valor);
int desColar(struct cola* q);
int esVacia(struct cola* q);
void imprimirCola(struct cola* q);
void liberarCola(struct cola* q);

#endif // COLA_H

