#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__


#include "../Lista/glist.h"
#include "../ArbolAdelsonVelskyLandis/avl.h"

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef unsigned (*FuncionHash)(void *dato);


typedef enum {
    LINEAR_PROBING,
    ARBOL,
    LISTA_MEZCLADA,
    DOBLE_HASH
} Colisiones;

typedef struct {
    void* dato;
    int eliminado;
} CasillaLinearProbing;

typedef struct {
    void* dato;
    void* sig;
} CasillaListaMezclada;

typedef union {
  CasillaLinearProbing linear;
  AVL arbol;
  CasillaListaMezclada mezclada;
  void* dato;
} CasillaHash;

typedef struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  Colisiones tipoColision;
  FuncionCopiadora copia;
  FuncionComparadora compara;
  FuncionDestructora destruye;
  FuncionHash hash;
  FuncionHash paso;
} TablaHash;

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash, FuncionHash paso, Colisiones tipo);

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla);

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla);

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato);

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato);

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato);

#endif /* __TABLAHASH_H__ */