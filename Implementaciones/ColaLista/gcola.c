#include "gcola.h"


void* no_copia(void* dato) {
    return dato;
}

void no_destruye(void *dato) {
    return;
}

GCola gcola_crear() {
    return gdlist_crear();
}

GCola gcola_queue(GCola cola, void *dato) {
    return gdlist_agregar_inicio(cola, dato, no_copia);
}

GCola gcola_dequeue(GCola cola) {
    return gdlist_eliminar_inicio(cola, no_destruye);
}

void *gcola_first(GCola cola) {
    return gdlist_primero(cola);
}

int gcola_len(GCola cola) {
    return gdlist_largo(cola);
}

void gcola_destruir(GCola cola) {
    gdlist_destruir(cola, no_destruye);
}

int gcola_vacia(GCola cola) {
    return gdlist_vacia(cola);
}