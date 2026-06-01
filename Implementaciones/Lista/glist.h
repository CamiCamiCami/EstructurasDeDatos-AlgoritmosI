#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionVisitante)(void* dato);
typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destrucción de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void* dato, FuncionCopia copiar);

/**
 * Agrega un elemento al fin de la lista.
 */
GList glist_agregar_final(GList lista, void* dato, FuncionCopia copiar);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

/**
 * Elimina el primer elemento de la lista.
 */
GList glist_eliminar_inicio(GList lista, FuncionDestructora destruir);

/**
 * Elimina el ultimo elemento de la lista.
 */
GList glist_eliminar_final(GList lista, FuncionDestructora destruir);

/**
 * Busca el elemento en el indice indicado.
 */
void* glist_buscar(GList lista, int pos);

/**
 * Da el largo de la lista.
 */
int glist_largo(GList lista);


#endif /* __GLIST_H__ */
