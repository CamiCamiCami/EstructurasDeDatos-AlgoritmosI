#ifndef __AVL_H__
#define __AVL_H__

typedef void* (*FuncionCopiadora)(void* dato);
typedef int (*FuncionComparadora)(void*, void*);
typedef void (*FuncionDestructora)(void* dato);
typedef void (*FuncionVisitanteExtra)(void* dato, void* extra);
typedef void (*FuncionImpresora)(void*);

typedef enum {
  AVL_RECORRIDO_IN,  /** Inorden */
  AVL_RECORRIDO_PRE, /** Preorden */
  AVL_RECORRIDO_POST /** Postorden */
} AVLRecorrido;

typedef struct _AVLNodo {
  void* dato;
  struct _AVLNodo *izq, *der;
  int altura;
} AVLNodo;

typedef struct _AVL {
  AVLNodo* raíz;
  FuncionCopiadora copia;
  FuncionComparadora compara;
  FuncionDestructora destruye;
} AVL;

/**
 * Retorna un árbol AVL vació
 */
AVL avl_crear(FuncionCopiadora, FuncionComparadora, FuncionDestructora);

/**
 * Destruye el arbol y sus datos.
 */
void avl_destruir(AVL);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario
 */
int avl_buscar(AVL, void*);

/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad de los
 * arboles AVL.
 */
AVL avl_insertar(AVL, void*);

/**
 * Retorna 1 si el arbol cumple la propiedad de los arboles AVL, y 0 en caso
 * contrario.
 */
int avl_validar(AVL);

/**
 * Recorrido DSF del arbol
 */
void avl_recorrer(AVL, AVLRecorrido, FuncionVisitanteExtra, void*);

/*
 * Imprime la estructura del árbol junto a sus elementos
 */
void avl_imprimir(AVL, FuncionImpresora);

/*
 * Elimina un elemento del arbol
 */
AVL avl_eliminar(AVL, void*);

#endif /* __AVL_H__ */