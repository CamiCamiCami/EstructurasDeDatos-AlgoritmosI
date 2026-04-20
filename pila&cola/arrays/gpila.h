#ifndef __GPILA_H__
#define __GPILA_H__

#include "arrays.h"

typedef struct __gpila {
    GArreglo arreglo;
    int ultimo;
} *GPila;


GPila gpila_crear();

void gpila_push(GPila pila, void* dato);

void gpila_pop(GPila pila);

void* gpila_top(GPila pila);

int gpila_len(GPila pila);

void gpila_destruir(GPila pila);

int gpila_vacia(GPila pila);

#endif