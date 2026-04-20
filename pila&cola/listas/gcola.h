#ifndef __GCOLA_H__
#define __GCOLA_H__

#include "gdlist.h"

typedef GDList GCola;


GCola gcola_crear();

GCola gcola_queue(GCola cola, void *dato);

GCola gcola_dequeue(GCola cola);

void *gcola_first(GCola cola);

int gcola_len(GCola cola);

void gcola_destruir(GCola cola);

int gcola_vacia(GCola cola);

#endif