#include "vector.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define LARGOINICIAL 50
GVector vector_crear(FuncionDestructora destruir, FuncionCopia copiar) {
  GVector vector;
  vector.arr = malloc(sizeof(void *) * LARGOINICIAL);
  assert(vector.arr);
  vector.destruir = destruir;
  vector.copiar = copiar;
  vector.posInsertar = 0;
  vector.capacidad = LARGOINICIAL;
  for (int i = 0; i < vector.capacidad; i++)
    vector.arr[i] = NULL;
  return vector;
}

void vector_destruir(GVector vector) {
  for (int i = 0; i < vector.capacidad; i++)
    if (vector.arr[i])
      free(vector.arr[i]);
  free(vector.arr);
}

void *vector_leer(GVector vector, int pos) { return vector.arr[pos]; }

GVector vector_escribir(GVector vector, int pos, void *dato) {
  if (dato == NULL) {
    if (vector.arr[pos])
      vector.destruir(vector.arr[pos]);
    vector.arr[pos] = NULL;
  } else {
    vector.posInsertar = vector.posInsertar <= pos ? pos + 1 : vector.posInsertar;
    if (vector.arr[pos] && dato != vector.arr[pos])
      vector.destruir(vector.arr[pos]);
    vector.arr[pos] = vector.copiar(dato);
  }
  return vector;
}

int vector_capacidad(GVector vector) { return vector.capacidad; }

void vector_recorrer(GVector vector, FuncionVisitante visitar) {
  for (int i = 0; i < vector.capacidad; i++)
    if (vector.arr[i])
      visitar(vector.arr[i]);
}

void vector_imprimir(GVector vector, FuncionImpresora imprimir) { vector_recorrer(vector, imprimir); }

GVector vector_redimensionar(GVector vector, int capacidad) {
  if (vector.capacidad >= capacidad)
    return vector;
  vector.arr = realloc(vector.arr, sizeof(void *) * capacidad);
  for (int i = vector.capacidad; i < capacidad; i++)
    vector.arr[i] = NULL;
  vector.capacidad = capacidad;
  return vector;
}

GVector vector_meter(GVector vector, void *elem) {
  if (vector.capacidad <= vector.posInsertar)
    vector = vector_redimensionar(vector, vector.capacidad * 2);
  return vector_escribir(vector, vector.posInsertar, elem);
}

GVector vector_eliminar(GVector vector, int idx) {
  vector = vector_escribir(vector, idx, NULL);
  vector.posInsertar = vector.posInsertar - 1 == idx ? idx : vector.posInsertar;
  return vector;
}

int vector_largo(GVector vector) { return vector.posInsertar; }

void *vector_ultimo(GVector vector) { return vector_largo(vector) == 0 ? NULL : vector_leer(vector, vector_largo(vector) - 1); }

GVector vector_eliminar_ultimo(GVector vector) {
  if (vector_ultimo(vector) == NULL)
    return vector;
  return vector_eliminar(vector, vector_largo(vector) - 1);
}