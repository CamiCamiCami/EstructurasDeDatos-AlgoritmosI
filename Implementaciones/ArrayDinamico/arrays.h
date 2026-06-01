#ifndef __ARRAYS_H__
#define __ARRAYS_H__

#include <stdlib.h>
#include <stdio.h>

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

typedef struct {
    void* *direccion;
    int capacidad;
} GArreglo;

GArreglo arreglo_crear(int capacidad);

void arreglo_destruir(GArreglo arreglo, FuncionDestructora destruir);

void* arreglo_leer(GArreglo arreglo, int pos);

void arreglo_escribir(GArreglo arreglo, int pos, void* dato, FuncionCopia copiar);

int arreglo_capacidad(GArreglo arreglo);

void arreglo_recorrer(GArreglo arreglo, FuncionVisitante visitar);

void arreglo_imprimir(GArreglo arreglo);

GArreglo arreglo_redimensionar(GArreglo arreglo, int capacidad);

#endif
