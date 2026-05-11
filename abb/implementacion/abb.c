#include "abb.h"

ABB ABB_crear(FuncionComparadora compara, FuncionCopiadora copia, FuncionDestructora destruye) {
    ABB arbol;
    arbol.raiz = NULL;
    arbol.compara = compara;
    arbol.copia = copia;
    arbol.destruye = destruye;
    return arbol;
}

ABBNodo* crear_nodo(void* dato, FuncionCopiadora copia) {
    ABBNodo* nodo = malloc(sizeof(ABBNodo));
    nodo->izq = nodo->der = NULL;
    nodo->dato = copia(dato);
    return nodo;
}

ABBNodo* ABB_insertar_in(ABBNodo* arbol, void* dato, FuncionComparadora compara, FuncionCopiadora copia) {
    if(arbol == NULL) {
        return crear_nodo(dato, copia);
    }
    int dif = compara(dato, arbol->dato);
    if(dif > 0) {
        arbol->der = ABB_insertar_in(arbol->der, dato, compara, copia);
    } else {
        arbol->izq = ABB_insertar_in(arbol->izq, dato, compara, copia);
    }
    return arbol;
}

ABB ABB_insertar(ABB arbol, void* dato) {
    arbol.raiz = ABB_insertar_in(arbol.raiz, dato, arbol.compara, arbol.copia);
    return arbol;
}


ABBNodo* levantar_menor(ABBNodo* arbol, ABBNodo* anterior, int esRaiz) {
    if(arbol->izq == NULL) {
        if(esRaiz) anterior->der = arbol->der;
        else anterior->izq = arbol->der;
        arbol->der = NULL;
        return arbol;
    }
    return levantar_menor(arbol->izq, arbol, 0);
}


ABBNodo* levantar_mayor(ABBNodo* arbol, ABBNodo* anterior, int esRaiz) {
    if(arbol->der == NULL) {
        if(esRaiz) anterior->izq = arbol->izq;
        else anterior->der = arbol->izq;
        arbol->izq = NULL;
        return arbol;
    }
    return levantar_mayor(arbol->der, arbol, 0);
}

ABBNodo* eliminar_raiz(ABBNodo* raiz, FuncionDestructora destruye) {
    ABBNodo* remplazo;
    if (raiz->der != NULL && raiz->izq != NULL) {
        remplazo = levantar_menor(raiz->der, raiz, 1);
        remplazo->izq = raiz->izq;
        remplazo->der = raiz->der;
    } else {
        remplazo = raiz->der != NULL ? raiz->der : raiz->izq;
    }
    destruye(raiz->dato);
    free(raiz);
    return remplazo;
} 

ABBNodo* ABB_eliminar_in(ABBNodo* arbol, void* dato, FuncionComparadora compara, FuncionDestructora destruye) {
    if(arbol == NULL) {
        return NULL;
    }
    int dif = compara(dato, arbol->dato);
    if(dif > 0) {
        arbol->der = ABB_eliminar_in(arbol->der, dato, compara, destruye);
    } else if (dif < 0) {
        arbol->izq = ABB_eliminar_in(arbol->izq, dato, compara, destruye);
    } else {
        arbol = eliminar_raiz(arbol, destruye);
    }
    return arbol;
}

ABB ABB_eliminar(ABB arbol, void* dato) {
    arbol.raiz = ABB_eliminar_in(arbol.raiz, dato, arbol.compara, arbol.destruye);
    return arbol;
}


void* ABB_buscar_in(ABBNodo* arbol, void* dato, FuncionComparadora compara) {
    if (arbol == NULL) {
        return NULL;
    }
    int dif = compara(dato, arbol->dato);
    if (dif > 0) {
        return ABB_buscar_in(arbol->der, dato, compara);
    } else if (dif < 0) {
        return ABB_buscar_in(arbol->izq, dato, compara);
    } else {
        return arbol->dato;
    }
}


void* ABB_buscar(ABB arbol, void* dato) {
    return ABB_buscar_in(arbol.raiz, dato, arbol.compara);
}

void ABB_destruir_in(ABBNodo* arbol, FuncionDestructora destruye) {
    if(arbol == NULL) {
        return;
    }
    ABBNodo *izq = arbol->izq, *der = arbol->der;
    destruye(arbol->dato);
    free(arbol);
    ABB_destruir_in(izq, destruye);
    ABB_destruir_in(der, destruye);
}

void ABB_destruir(ABB arbol) {
    ABB_destruir_in(arbol.raiz, arbol.destruye);
}


void ABB_imprimir_in(ABBNodo* nodo, FuncionImpresora imprime, int indentacion) {
    if(nodo == NULL) {
        return;
    }
    
    ABB_imprimir_in(nodo->der, imprime, indentacion+1);
    
    for(int i = 0; i < indentacion; i++)
        printf("    ");
    imprime(nodo->dato);
    printf("\n");
    
    ABB_imprimir_in(nodo->izq, imprime, indentacion+1);
}

void ABB_imprimir(ABB arbol, FuncionImpresora imprime) {
    ABB_imprimir_in(arbol.raiz, imprime, 0);
}
