#ifndef __ABB_H__
#define __ABB_H__

#include <stdlib.h>
#include <stdio.h>

typedef void* (*FuncionCopiadora)(void*);
typedef void (*FuncionDestructora)(void*);
typedef int (*FuncionComparadora)(void*, void*);
typedef void (*FuncionImpresora)(void*);

typedef struct __abb_nodo {
    void* dato;
    struct __abb_nodo *izq, *der;
} ABBNodo;

typedef struct __abb {
    ABBNodo* raiz;
    FuncionCopiadora copia;
    FuncionComparadora compara;
    FuncionDestructora destruye;
} ABB;


ABB ABB_crear(FuncionComparadora comapara, FuncionCopiadora copia, FuncionDestructora destruye);

ABB ABB_insertar(ABB arbol, void* dato);

ABB ABB_eliminar(ABB arbol, void* dato);

void* ABB_buscar(ABB arbol, void* dato);

void ABB_destruir(ABB arbol);

void ABB_imprimir(ABB arbol, FuncionImpresora imprime);


#endif