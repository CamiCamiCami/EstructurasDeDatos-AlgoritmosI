#include "heap.h"
#include <stdlib.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

Heap heap_crear(FuncionComparadora compara, FuncionCopia copia, FuncionDestructora destruye)
{
    Heap heap;
    heap.vector = vector_crear(destruye, copia);
    heap.compara = compara;
    return heap;
}

Heap flotar(Heap heap, void *elem)
{
    int hijoIdx = vector_largo(heap.vector) - 1;
    int padreIdx = hijoIdx / 2;
    void *padre = vector_leer(heap.vector, padreIdx);
    while (padreIdx != 0 && heap.compara(padre, elem) < 0)
    {
        heap.vector = vector_escribir(heap.vector, hijoIdx, padre);
        hijoIdx = padreIdx;
        padreIdx = hijoIdx / 2;
        padre = vector_leer(heap.vector, padreIdx);
    }
    if (padreIdx == 0 && heap.compara(padre, elem) < 0)
    {
        heap.vector = vector_escribir(heap.vector, hijoIdx, padre);
        heap.vector = vector_escribir(heap.vector, padreIdx, elem);
    }
    else
    {
        heap.vector = vector_escribir(heap.vector, hijoIdx, elem);
    }
    return heap;
}

Heap heap_insertar(Heap heap, void *elem)
{
    heap.vector = vector_meter(heap.vector, elem);
    return flotar(heap, elem);
}


void* hijoMayor(Heap heap, int idxPadre, int *idxHijo) {
    if(idxPadre*2+1 >= vector_capacidad(heap.vector)) return NULL;
    void* hijoIzq = vector_leer(heap.vector, idxPadre*2);
    void* hijoDer = vector_leer(heap.vector, idxPadre*2+1);
    if (hijoDer == NULL || hijoIzq == NULL) 
        if (hijoDer == NULL) {
            *idxHijo = idxPadre*2;
            return hijoIzq;
        } else {
            *idxHijo = idxPadre*2+1;
            return hijoDer;
        }
    else
        if(heap.compara(hijoDer, hijoIzq) < 0) {
            *idxHijo = idxPadre*2;
            return hijoIzq;
        } else {
            *idxHijo = idxPadre*2+1;
            return hijoDer;
        }
}


Heap hundir(Heap heap, int idx) {
    void* hundido = vector_leer(heap.vector, idx);
    int idxHijo;
    void* hijo = hijoMayor(heap, idx, &idxHijo);
    while (hijo != NULL && heap.compara(hundido, hijo) < 0)
    {
        vector_escribir(heap.vector, idx, hijo);
        idx = idxHijo;
        void* hijo = hijoMayor(heap, idx, &idxHijo);
    }
    heap.vector = vector_escribir(heap.vector, idx, hundido);
    return heap;
}

Heap heap_eliminar(Heap heap, void* elem) {
    int idx = 0;
    for(void* e = vector_leer(heap.vector, idx); idx < vector_largo(heap.vector) && heap.compara(elem, e); idx++, e = vector_leer(heap.vector, idx));
    if(idx >= vector_largo(heap.vector)) return heap;
    void* ultimo = vector_ultimo(heap.vector);
    heap.vector = vector_escribir(heap.vector, idx, ultimo);
    heap.vector = vector_eliminar(heap.vector, vector_largo(heap.vector) - 1);
    return hundir(heap, idx);
}

Heap heap_top(Heap heap) {
    return heap_eliminar(heap, heap_maximo(heap));
}

void *heap_maximo(Heap heap) {
    if (heap_vacio(heap)) return NULL;
    return vector_leer(heap.vector, 0);
}

int heap_vacio(Heap heap) {
    return vector_largo(heap.vector) == 0;
}

void heap_destruir(Heap heap) {
    vector_destruir(heap.vector);
}

void heap_recorrer(Heap heap, FuncionVisitante visita) {
    vector_recorrer(heap.vector, visita);
}

void heap_imprimir(Heap heap, FuncionImpresora imprime) {
    heap_recorrer(heap, imprime);
}