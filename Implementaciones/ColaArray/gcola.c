#include "gcola.h"


#define LARGO_INICIAL 100
#define LARGO_ALARGUE 50


void* no_copia(void* dato) {
    return dato;
}

void no_destruye(void *dato) {
    return;
}

GCola gcola_crear() {
    GCola cola = malloc(sizeof(struct __gcola));
    cola->arreglo = arreglo_crear(LARGO_INICIAL);
    cola->primero = 0;
    cola->ultimo = 0;
    cola->largo = 0;
    return cola;
}

void gcola_queue(GCola cola, void *dato) {
    if (cola->largo + 1 > arreglo_capacidad(cola->arreglo)) {
        gcola_expand(cola);
    }

    arreglo_escribir(cola->arreglo, cola->ultimo, dato, no_copia);
    cola->ultimo++;
    cola->largo++;
    if (cola->ultimo >= arreglo_capacidad(cola->arreglo))
        cola->ultimo = 0;
    return cola;
}


void gcola_expand(GCola cola) {
    int antigua_capacidad = arreglo_capacidad(cola->arreglo);
    cola->arreglo = arreglo_redimensionar(cola->arreglo, antigua_capacidad + LARGO_ALARGUE);
    if (cola->ultimo <= cola->primero && !gcola_vacia(cola)) {
        cola->largo = cola->largo - cola->ultimo;
        cola->ultimo = antigua_capacidad - 1;
        for (int i = 0; i < cola->ultimo; i++) {
            gcola_queue(cola, arreglo_leer(cola->arreglo, i));
        }
    }
    return cola;
}



void gcola_dequeue(GCola cola) {
    cola->primero++;
    cola->primero = cola->primero>= arreglo_capacidad(cola->arreglo) ? 0 : cola->primero;
    cola->largo--;
    return cola;
}

void *gcola_first(GCola cola) {
    if (gcola_vacia(cola)) 
        return NULL;
    else 
        return arreglo_leer(cola->arreglo, cola->primero);
}

int gcola_len(GCola cola) {
    return cola->largo;
}

void gcola_destruir(GCola cola) {
    arreglo_destruir(cola->arreglo, no_destruye);
    free(cola);
}

int gcola_vacia(GCola cola) {
    return gcola_len(cola) == 0;
}