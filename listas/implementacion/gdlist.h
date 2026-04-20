#ifndef __GDLIST_H__
#define __GDLIST_H__

#include <stdlib.h>

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *dato);

typedef struct _GDNode {
    void *data;
    struct _GNode *next, *prev;
} GDNode;


typedef struct _GDList {
    GDNode *primero, *ultimo;
    unsigned int largo;
} GDList;


/**
 * Devuelve una lista vacía.
 */
GDList gdlist_crear();

/**
 * Destrucción de la lista.
 */
void gdlist_destruir(GDList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 */
int gdlist_vacia(GDList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
GDList gdlist_agregar_inicio(GDList lista, void *dato, FuncionCopia copiar);

/**
 * Agrega un elemento al fin de la lista.
 */
GDList gdlist_agregar_final(GDList lista, void *dato, FuncionCopia copiar);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void gdlist_recorrer(GDList lista, FuncionVisitante visitar);

/**
 * Elimina el primer elemento de la lista.
 */
GDList gdlist_eliminar_inicio(GDList lista, FuncionDestructora destruir);

/**
 * Elimina el ultimo elemento de la lista.
 */
GDList gdlist_eliminar_final(GDList lista, FuncionDestructora destruir);

/**
 * Busca el elemento en la lista.
 */
void *gdlist_buscar(GDList lista, void *dato, FuncionComparadora compara);

/**
 * Da el largo de la lista.
 */
int gdlist_largo(GDList lista);

/**
 * Devuelve el primer elemento de la lista.
 */
void* gdlist_primero(GDList lista);

/**
 * Devuelve el ultimo elemento de la lista
 */
void* gdlist_ultimo(GDList lista);

#endif /* __GDLIST_H__ */
