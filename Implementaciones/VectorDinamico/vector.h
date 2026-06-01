#ifndef __DINAMICO_H__
#define __DINAMICO_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef void (*FuncionImpresora)(void*);


typedef struct {
    void* *arr;
    int capacidad;
    int posInsertar;
    FuncionDestructora destruir;
    FuncionCopia copiar;
} GVector;

GVector vector_crear(FuncionDestructora, FuncionCopia);

void vector_destruir(GVector);

void* vector_leer(GVector, int);

void* vector_ultimo(GVector);

GVector vector_eliminar(GVector, int);

GVector vector_escribir(GVector, int, void*);

int vector_capacidad(GVector);

int vector_largo(GVector);

void vector_recorrer(GVector, FuncionVisitante);

void vector_imprimir(GVector, FuncionImpresora);

GVector vector_redimensionar(GVector, int);

GVector vector_meter(GVector, void*);

#endif
