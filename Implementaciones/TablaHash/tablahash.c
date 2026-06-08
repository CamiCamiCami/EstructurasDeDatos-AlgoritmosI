#include "tablahash.h"
#include <stdlib.h>

TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia, FuncionComparadora comp, FuncionDestructora destr, FuncionHash hash,
                          FuncionHash paso, Colisiones tipo) {
  TablaHash tabla;
  tabla.capacidad = capacidad;
  tabla.compara = comp;
  tabla.copia = copia;
  tabla.destruye = destr;
  tabla.elems = malloc(sizeof(CasillaHash) * capacidad);
  tabla.hash = hash;
  tabla.numElems = 0;
  tabla.tipoColision = tipo;
  tabla.paso = paso;
  switch (tipo) {
  case LINEAR_PROBING:
    for (int i = 0; i < capacidad; i++) {
      tabla.elems[i].linear.dato = NULL;
      tabla.elems[i].linear.eliminado = 0;
    }
    break;
  case ARBOL:
    for (int i = 0; i < capacidad; i++) {
      tabla.elems[i].arbol = avl_crear(copia, comp, destr);
    }
    break;
  case LISTA_MEZCLADA:
    for (int i = 0; i < capacidad; i++) {
      tabla.elems[i].mezclada.dato = NULL;
      tabla.elems[i].mezclada.sig = NULL;
    }
    break;
  case DOBLE_HASH:
    for (int i = 0; i < capacidad; i++) {
      tabla.elems[i].dato = NULL;
    }
    break;
  }
  return tabla;
}

int tablahash_nelems(TablaHash tabla) { return tabla.numElems; }

int tablahash_capacidad(TablaHash tabla) { return tabla.capacidad; }

void tablahash_destruir(TablaHash tabla) {
  switch (tabla.tipoColision) {
  case LINEAR_PROBING:
    for (int i = 0; i < tabla.capacidad; i++) {
      void *dato = tabla.elems[i].linear.dato;
      if (dato != NULL)
        destruye(dato);
    }
    break;
  case ARBOL:
    for (int i = 0; i < tabla.capacidad; i++) {
      avl_destruir(tabla.elems[i].arbol);
    }
    break;
  case LISTA_MEZCLADA:
    for (int i = 0; i < tabla.capacidad; i++) {
      void *dato = tabla.elems[i].mezclada.dato;
      if (dato != NULL)
        destruye(dato);
    }
    break;
  case DOBLE_HASH:
    for (int i = 0; i < tabla.capacidad; i++) {
      void *dato = tabla.elems[i].dato;
      if (dato != NULL)
        destruye(dato);
    }
    break;
  }
}


#define LPdato(c) c.linear.dato
#define LPeliminado(c) c.linear.eliminado
void* linearProbing_buscar(CasillaHash *elems, void *buscado, FuncionHash hash, FuncionComparadora compara, unsigned capacidad) {
    for(int i = hash(buscado) % capacidad; (LPdato(elems[i]) != NULL || LPeliminado(elems[i])); i = (i + 1) % capacidad) {
        if(compara(buscado, LPdato(elems[i])) == 0) {
            return LPdato(elems[i]);
        }
    }
    return NULL;
}

void linearProbing_insertar(CasillaHash *elems, void *nuevo, FuncionHash hash, FuncionCopia copia, unsigned capacidad) {
  unsigned idxBusqueda = hash(nuevo) % capacidad;
  int insertado = 0;
  while (!insertado) {
    void *dato = LPdato(elems[idxBusqueda]);
    if (dato == NULL) {
      LPdato(elems[idxBusqueda]) = copia(nuevo);
      insertado = 1;
    }
    idxBusqueda = idxBusqueda + 1 % capacidad;
  }
}

void *tablahash_buscar(TablaHash tabla, void *dato);

void listaMezclada_insertar(CasillaHash *elems, void *nuevo, FuncionHash hash, FuncionCopia copia, unsigned capacidad) {
  unsigned idxInsertado = hash(nuevo) % capacidad;
  CasillaHash *origen = &elems[idxInsertado];
  CasillaHash *ultimo = origen;
  while (ultimo->mezclada.sig != NULL) {
    ultimo = ultimo->mezclada.sig;
  }

  int insertado = 0;
  while (!insertado) {
    if (elems[++idxInsertado].mezclada.dato == NULL) {
      insertado = 1;
      elems[idxInsertado].mezclada.dato = copia(nuevo);
      ultimo->mezclada.sig = &elems[idxInsertado];
    }
  }
}

void dobleHashing_insertar(CasillaHash *elems, void *nuevo, FuncionHash hash, FuncionHash paso, FuncionCopia copia, unsigned capacidad) {
  int insertado = 0;
  unsigned valPaso = paso(nuevo) % capacidad;
  for (int idx = hash(nuevo) % capacidad; !insertado; idx = (idx + valPaso) % capacidad) {
    if (elems[idx].dato != NULL) {
      insertado = 1;
      elems[idx].dato = copia(nuevo);
    }
  }
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *nuevo) {
  if (tablahash_buscar(tabla, nuevo) != NULL)
    return;
  switch (tabla.tipoColision) {
  case LINEAR_PROBING:
    linearProbing_insertar(tabla.elems, nuevo, tabla.hash, tabla.copia, tabla.capacidad);
    break;
  case ARBOL:
    avl_insertar(tabla.elems[tabla.hash(nuevo) % tabla.capacidad].arbol, nuevo);
    break;
  case LISTA_MEZCLADA:
    listaMezclada_insertar(tabla.elems, nuevo, tabla.hash, tabla.copia, tabla.capacidad);
    break;
  case DOBLE_HASH:
    dobleHashing_insertar(tabla.elems, nuevo, tabla.hash, tabla.paso, tabla.copia, tabla.capacidad);
    break;
  }
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato);