#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

Heap heap_crear(FuncionComparadora compara, FuncionCopia copia, FuncionDestructora destruye) {
  Heap heap;
  heap.vector = vector_crear(destruye, copia);
  heap.vector.posInsertar = 1;
  heap.compara = compara;
  return heap;
}

Heap flotar(Heap heap, void *elem) {
  int hijoIdx = vector_largo(heap.vector) - 1;
  int padreIdx = hijoIdx / 2;
  void *padre = vector_leer(heap.vector, padreIdx);
  while (padreIdx > 1 && heap.compara(padre, elem) < 0) {
    heap.vector = vector_escribir(heap.vector, hijoIdx, padre);
    hijoIdx = padreIdx;
    padreIdx = hijoIdx / 2;
    padre = vector_leer(heap.vector, padreIdx);
  }
  if (padreIdx == 1 && heap.compara(padre, elem) < 0) {
    heap.vector = vector_escribir(heap.vector, hijoIdx, padre);
    heap.vector = vector_escribir(heap.vector, padreIdx, elem);
  } else {
    heap.vector = vector_escribir(heap.vector, hijoIdx, elem);
  }
  return heap;
}

Heap heap_insertar(Heap heap, void *elem) {
  heap.vector = vector_meter(heap.vector, elem);
  return flotar(heap, elem);
}

void *hijoMayor(Heap heap, int idxPadre, int *idxHijo) {
  if (idxPadre * 2 + 1 >= vector_capacidad(heap.vector))
    return NULL;
  void *hijoIzq = vector_leer(heap.vector, idxPadre * 2);
  void *hijoDer = vector_leer(heap.vector, idxPadre * 2 + 1);
  if (hijoDer == NULL || hijoIzq == NULL)
    if (hijoDer == NULL) {
      *idxHijo = idxPadre * 2;
      return hijoIzq;
    } else {
      *idxHijo = idxPadre * 2 + 1;
      return hijoDer;
    }
  else if (heap.compara(hijoDer, hijoIzq) < 0) {
    *idxHijo = idxPadre * 2;
    return hijoIzq;
  } else {
    *idxHijo = idxPadre * 2 + 1;
    return hijoDer;
  }
}

Heap hundir(Heap heap, int idx) {
  void *hundido = vector_leer(heap.vector, idx);
  int idxHijo;
  void *hijo = hijoMayor(heap, idx, &idxHijo);
  while (hijo != NULL && heap.compara(hundido, hijo) < 0) {
    vector_escribir(heap.vector, idx, hijo);
    idx = idxHijo;
    hijo = hijoMayor(heap, idx, &idxHijo);
  }
  heap.vector = vector_escribir(heap.vector, idx, hundido);
  return heap;
}

Heap heap_eliminar(Heap heap, void *elem) {
  int idx = 1;
  for (void *e = vector_leer(heap.vector, idx); idx < vector_largo(heap.vector) && heap.compara(elem, e); idx++, e = vector_leer(heap.vector, idx))
    ;
  if (idx >= vector_largo(heap.vector))
    return heap;
  void *ultimo = vector_ultimo(heap.vector);
  heap.vector = vector_escribir(heap.vector, idx, ultimo);
  heap.vector = vector_eliminar_ultimo(heap.vector);
  return hundir(heap, idx);
}

Heap heap_top(Heap heap) { return heap_eliminar(heap, heap_maximo(heap)); }

void *heap_maximo(Heap heap) {
  if (heap_vacio(heap))
    return NULL;
  return vector_leer(heap.vector, 0);
}

int heap_vacio(Heap heap) { return vector_largo(heap.vector) == 0; }

void heap_destruir(Heap heap) { vector_destruir(heap.vector); }

void heap_recorrer(Heap heap, FuncionVisitante visita) { vector_recorrer(heap.vector, visita); }

void heap_imprimir_in(Heap heap, FuncionImpresora imprime, int indice, int indentacion) {
  if (indice >= vector_largo(heap.vector)) {
    return;
  }

  heap_imprimir_in(heap, imprime, 2 * indice, indentacion + 1);

  for (int i = 0; i < indentacion; i++)
    printf("    ");
  imprime(vector_leer(heap.vector, indice));
  printf("\n");

  heap_imprimir_in(heap, imprime, 2 * indice + 1, indentacion + 1);
}

void heap_imprimir(Heap heap, FuncionImpresora imprime) { heap_imprimir_in(heap, imprime, 1, 0); }