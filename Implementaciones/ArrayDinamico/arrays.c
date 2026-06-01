#include "arrays.h"


GArreglo arreglo_crear(int capacidad) {
    GArreglo arreglo;
    arreglo.capacidad = capacidad;
    arreglo.direccion = malloc(sizeof(void *) * capacidad);
    for (int i = 0; i < arreglo.capacidad; i++)
        arreglo.direccion[i] = NULL;
    return arreglo;
}

void arreglo_destruir(GArreglo arreglo, FuncionDestructora destruir) {
    for (int i = 0; i < arreglo.capacidad; i++)
        destruir(arreglo.direccion[i]);
    free(arreglo.direccion);
}

void* arreglo_leer(GArreglo arreglo, int pos) {
    return arreglo.direccion[pos];
}

void arreglo_escribir(GArreglo arreglo, int pos, void* dato, FuncionCopia copiar) {
    arreglo.direccion[pos] = copiar(dato);
}

int arreglo_capacidad(GArreglo arreglo) {
    return arreglo.capacidad;
}

void arreglo_recorrer(GArreglo arreglo, FuncionVisitante visitar) {
    for (int i = 0; i < arreglo.capacidad; i++)
        visitar(arreglo.direccion[i]);
}

GArreglo arreglo_redimensionar(GArreglo arreglo, int capacidad) {
    arreglo.direccion = realloc(arreglo.direccion, capacidad);
    arreglo.capacidad = capacidad;
    return arreglo;
}
