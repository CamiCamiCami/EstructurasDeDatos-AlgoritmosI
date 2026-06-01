#include "gpila.h"



void* no_copia(void *dato)  {
    return dato;
}

void no_destruye(void *dato) {
    return;
}

GPila gpila_crear() {
    return glist_crear();
}

GPila gpila_push(GPila pila, void *dato) {
    return glist_agregar_inicio(pila, dato, no_copia);
}


GPila gpila_pop(GPila pila)
{
    return glist_eliminar(pila, 0, no_destruye);
}


void *gpila_top(GPila pila) {
    return glist_buscar(pila, 0);
}


int gpila_largo(GPila pila) {
    return glist_largo(pila);
}


void gpila_destruir(GPila pila) {
    glist_destruir(pila, no_destruye);
}


int gpila_vacia(GPila pila) {
    return glist_vacia(pila);
}