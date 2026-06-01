#ifndef __HEAP_H__
#define __HEAP_H__

#include "../VectorDinamico/vector.h"

typedef int (*FuncionComparadora)(void*, void*);

typedef struct {
    GVector vector;
    FuncionComparadora compara;
} Heap;


Heap heap_crear(FuncionComparadora, FuncionCopia, FuncionDestructora);

Heap heap_insertar(Heap, void*);

Heap heap_eliminar(Heap, void*);

void* heap_maximo(Heap);

int heap_vacio(Heap);

void heap_destruir(Heap);

void heap_recorrer(Heap, FuncionVisitante);

void heap_imprimir(Heap, FuncionImpresora);






#endif