#include "gdlist.h"

/**
 * Devuelve una lista vacía.
 */
GDList gdlist_crear() {
    GDList lista;
    lista.primero = lista.ultimo = NULL;
    lista.largo = 0;
    return lista;
}

/**
 * Destrucción de la lista.
 */
void gdlist_destruir(GDList lista, FuncionDestructora destruir) {
    for (GDNode *it = lista.primero, *sig; it; it = sig) {
        sig = it->next;
        destruir(it->data);
        free(it);
    }
}

/**
 * Determina si la lista es vacía.
 */
int gdlist_vacia(GDList lista) {
    return lista.largo == 0;
}

GDNode *crear_nodo(GDNode *sig, GDNode *ant, void *dato, FuncionCopia copia)
{
    GDNode* new = malloc(sizeof(GDNode));
    new->data = copia(dato);
    new->next = sig;
    new->prev = ant;
    return new;
}

/**
 * Agrega un elemento al inicio de la lista.
 */
GDList gdlist_agregar_inicio(GDList lista, void *dato, FuncionCopia copiar) {
    GDNode *nuevoNodo = crear_nodo(lista.primero, NULL, dato, copiar);
    if (gdlist_vacia(lista))
        lista.ultimo = nuevoNodo;
    else
        lista.primero->prev = nuevoNodo;
    lista.primero = nuevoNodo;
    lista.largo++;
    return lista;
}

/**
 * Agrega un elemento al fin de la lista.
 */
GDList gdlist_agregar_final(GDList lista, void *dato, FuncionCopia copiar) {
    GDNode *nuevoNodo = crear_nodo(NULL, lista.ultimo, dato, copiar);
    if (gdlist_vacia(lista))
        lista.primero = nuevoNodo;
    else
        lista.ultimo->next = nuevoNodo;
    lista.ultimo = nuevoNodo;
    lista.largo++;
    return lista;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void gdlist_recorrer(GDList lista, FuncionVisitante visitar) {
    for (GDNode *it = lista.primero; it; it = it->next)
        visitar(it->data);
}


void eliminar_nodo(GDNode* nodo, FuncionDestructora destruir) {
    destruir(nodo->data);
    free(nodo);
}


/**
 * Elimina el primer elemento de la lista.
 */
GDList gdlist_eliminar_inicio(GDList lista, FuncionDestructora destruir) {
    if (gdlist_vacia(lista)) 
        return lista;
    GDNode *nodo_destruir = lista.primero;
    lista.primero = lista.primero->next;
    if (lista.primero == NULL) 
        lista.ultimo = NULL;
    else
        lista.primero->prev = NULL;
    eliminar_nodo(nodo_destruir, destruir);
    lista.largo--;
    return lista;
}

/**
 * Elimina el ultimo elemento de la lista.
 */
GDList gdlist_eliminar_final(GDList lista, FuncionDestructora destruir) {
    if (gdlist_vacia(lista))
        return lista;
    GDNode *nodo_destruir = lista.ultimo;
    lista.ultimo = lista.ultimo->prev;
    if (lista.ultimo == NULL)
        lista.primero = NULL;
    else
        lista.ultimo->next = NULL;
    eliminar_nodo(nodo_destruir, destruir);
    lista.largo--;
    return lista;
}

/**
 * Busca el elemento en la lista.
 */
void *gdlist_buscar(GDList lista, void* dato, FuncionComparadora compara) {
    GDNode *it = lista.primero;
    for (;it && compara(it->data, dato) != 0; it = it->next);
    return it;
}

/**
 * Da el largo de la lista.
 */
int gdlist_largo(GDList lista) {
    return lista.largo;
}

/**
 * Devuelve el primer elemento de la lista.
 */
void *gdlist_primero(GDList lista) {
    return lista.primero->data;
}

/**
 * Devuelve el ultimo elemento de la lista
 */
void *gdlist_ultimo(GDList lista) {
    return lista.ultimo->data;
}