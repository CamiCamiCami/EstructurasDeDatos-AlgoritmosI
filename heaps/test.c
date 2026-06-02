#include <stdio.h>
#include <stdlib.h>

#include "../Implementaciones/Heap/heap.h"

int int_compara(int *v1, int *v2) { return (*v1) - (*v2); }

int *int_copia(int *v) {
  int *vCopia = malloc(sizeof(int));
  (*vCopia) = (*v);
  return vCopia;
}

void int_destruye(int *v) { free(v); }

void int_imprimir(int *v) { printf("%i", *v); }

int main() {
  Heap heap = heap_crear((FuncionComparadora)int_compara, (FuncionCopia)int_copia, (FuncionDestructora)int_destruye);
  for (int i = 0; i < 50; i++) {
    int j = rand() % 100;
    int i = rand() % 100;
    printf("\nIteracion (+%i) (-%i)\n", i, j);
    heap = heap_insertar(heap, &i);
    printf("insertado: ✓\n");
    heap = heap_eliminar(heap, &j);
    printf("eliminado: ✓\n");
    heap_imprimir(heap, (FuncionImpresora)int_imprimir);
  }
}