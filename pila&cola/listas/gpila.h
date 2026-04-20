#ifndef __GPILA_H__
#define __GPILA_H__

#include "glist.h"

typedef GList GPila;

GPila gpila_crear();

GPila gpila_push(GPila pila, void* dato);


GPila gpila_pop(GPila pila);


void* gpila_top(GPila pila);


int gpila_len(GPila pila);


void gpila_destruir(GPila pila);


int gpila_vacia(GPila pila);

#endif