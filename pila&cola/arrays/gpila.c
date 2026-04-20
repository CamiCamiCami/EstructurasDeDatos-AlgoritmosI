#include "gpila.h"


#define LARGO_INICIAL 100
#define LARGO_ALARGUE 50

void* no_copia(void *dato)  {
    return dato;
}

void no_destruye(void *dato) {
    return;
}

GPila gpila_crear() {
    GPila pila = malloc(sizeof(struct __gpila));
    pila->arreglo = arreglo_crear(LARGO_INICIAL);
    pila->ultimo = -1;
    return pila;
}

void gpila_push(GPila pila, void *dato) {
    if(pila->ultimo >= arreglo_capacidad(pila->arreglo)) {
        gpila_expand(pila);
    }
    arreglo_escribir(pila->arreglo, pila->ultimo, dato, no_copia);
    pila->ultimo++;
}

void gpila_expand(GPila pila) {
    pila->arreglo = arreglo_redimensionar(pila->arreglo, arreglo_capacidad(pila->arreglo) + LARGO_ALARGUE);
}

void gpila_pop(GPila pila) {
    if (gpila_vacia(pila)) return;
    pila->ultimo--;
}

void *gpila_top(GPila pila) {
    if (gpila_vacia(pila)) return NULL;
    return arreglo_leer(pila->arreglo, pila->ultimo);
}

int gpila_largo(GPila pila) {
    return pila->ultimo + 1;
}

void gpila_destruir(GPila pila) {
    arreglo_destruir(pila->arreglo, no_destruye);
    free(pila);
}

int gpila_vacia(GPila pila) {
    return gpila_largo(pila) == 0;
}