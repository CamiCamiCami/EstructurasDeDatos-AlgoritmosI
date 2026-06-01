#include "avl.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Funciones de Utilidad */

#define max(a, b) (((a) > (b)) ? (a) : (b))

void* no_copia(void* dato) { return dato; }

void no_destruye(void* dato) { return; }

int altura_izquierda(AVLNodo* raíz) {
  return raíz->izq == NULL ? 0 : raíz->izq->altura;
}

int altura_derecha(AVLNodo* raíz) {
  return raíz->der == NULL ? 0 : raíz->der->altura;
}

void actualizar_altura(AVLNodo* raíz) {
  if (raíz == NULL) return;
  raíz->altura = max(altura_izquierda(raíz), altura_derecha(raíz)) + 1;
}

int diferencia_altura(AVLNodo* raíz) {
  return altura_izquierda(raíz) - altura_derecha(raíz);
}

int esta_balanceado(AVLNodo* raíz) {
  int difAltura = diferencia_altura(raíz);
  return -2 < difAltura && difAltura < 2;
}

int derecha_mas_alto(AVLNodo* raíz) { return diferencia_altura(raíz) < 0; }

int izquierda_mas_alto(AVLNodo* raíz) { return diferencia_altura(raíz) > 0; }

/* Funciones Auxiliares */

AVLNodo* avl_nodo_crear(void* dato, FuncionCopiadora copia) {
  AVLNodo* nuevoNodo = malloc(sizeof(AVLNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = copia(dato);
  nuevoNodo->izq = nuevoNodo->der = NULL;
  nuevoNodo->altura = 1;
  return nuevoNodo;
}

void* menor(AVLNodo* árbol) {
  if (árbol->izq == NULL) {
    return árbol->dato;
  }
  return menor(árbol->izq);
}

void* mayor(AVLNodo* árbol) {
  if (árbol->der == NULL) {
    return árbol->dato;
  }
  return mayor(árbol->dato);
}

AVLNodo* avl_eliminar_in(AVLNodo*, void*, FuncionComparadora,
                         FuncionDestructora);

AVLNodo* eliminar_raiz(AVLNodo* raíz, FuncionDestructora destruye,
                       FuncionComparadora compara) {
  AVLNodo* remplazo;
  if (raíz->der != NULL && raíz->izq != NULL) {
    void* menorMayor = menor(raíz->der);
    remplazo = avl_nodo_crear(menorMayor, no_copia);
    remplazo->der =
        avl_eliminar_in(raíz->der, menorMayor, compara, no_destruye);
    remplazo->izq = raíz->izq;
    remplazo->dato = menorMayor;
  } else {
    remplazo = raíz->der != NULL ? raíz->der : raíz->izq;
  }
  destruye(raíz->dato);
  free(raíz);
  return remplazo;
}

AVLNodo* rotar_derecha(AVLNodo* raíz) {
  AVLNodo* nuevaRaíz = raíz->der;
  raíz->der = nuevaRaíz->izq;
  nuevaRaíz->izq = raíz;
  actualizar_altura(raíz);
  actualizar_altura(nuevaRaíz);
  return nuevaRaíz;
}

AVLNodo* rotar_izquierda(AVLNodo* raíz) {
  AVLNodo* nuevaRaíz = raíz->izq;
  raíz->izq = nuevaRaíz->der;
  nuevaRaíz->der = raíz;
  actualizar_altura(raíz);
  actualizar_altura(nuevaRaíz);
  return nuevaRaíz;
}

AVLNodo* balancear(AVLNodo* raíz) {
  if (raíz == NULL || esta_balanceado(raíz)) return raíz;
  if (izquierda_mas_alto(raíz)) {
    if (derecha_mas_alto(raíz->izq)) {
      raíz->izq = rotar_derecha(raíz->izq);
    }
    return rotar_izquierda(raíz);
  } else {  // Derecha es mas pesada
    if (izquierda_mas_alto(raíz->der)) {
      raíz->der = rotar_izquierda(raíz->der);
    }
    return rotar_derecha(raíz);
  }
}

/* Funciones Internas */

void avl_destruir_in(AVLNodo* raíz, FuncionDestructora destruye) {
  if (raíz == NULL) {
    return;
  }
  destruye(raíz->dato);
  avl_destruir_in(raíz->der, destruye);
  avl_destruir_in(raíz->izq, destruye);
  free(raíz);
}

int avl_buscar_in(AVLNodo* raíz, void* elem, FuncionComparadora compara) {
  if (raíz == NULL) {
    return 0;
  }
  int dif = compara(elem, raíz->dato);
  if (dif < 0) {
    return avl_buscar_in(raíz->izq, elem, compara);
  } else if (dif > 0) {
    return avl_buscar_in(raíz->der, elem, compara);
  } else {
    return 1;
  }
}

AVLNodo* avl_insertar_in(AVLNodo* raíz, void* elem, FuncionComparadora compara,
                         FuncionCopiadora copia) {
  if (raíz == NULL) {
    return avl_nodo_crear(elem, copia);
  }
  int dif = compara(elem, raíz->dato);
  if (dif < 0) {
    raíz->izq = avl_insertar_in(raíz->izq, elem, compara, copia);
    actualizar_altura(raíz);
    return balancear(raíz);
  } else if (dif > 0) {
    raíz->der = avl_insertar_in(raíz->der, elem, compara, copia);
    actualizar_altura(raíz);
    return balancear(raíz);
  } else {
    return raíz;
  }
}

int avl_validar_in(AVLNodo* raíz) {
  if (raíz == NULL) {
    return 1;
  }
  int validoIzq = avl_validar_in(raíz->izq);
  int validoDer = avl_validar_in(raíz->der);
  actualizar_altura(raíz);
  return validoDer && validoIzq && esta_balanceado(raíz);
}

void avl_recorrer_in(AVLNodo* raíz, AVLRecorrido recorrido,
                     FuncionVisitanteExtra visita, void* elemExtra) {
  if (raíz == NULL) {
    return;
  }
  switch (recorrido) {
    case AVL_RECORRIDO_IN:
      avl_recorrer_in(raíz->izq, recorrido, visita, elemExtra);
      visita(raíz->dato, elemExtra);
      avl_recorrer_in(raíz->der, recorrido, visita, elemExtra);
      break;
    case AVL_RECORRIDO_POST:
      avl_recorrer_in(raíz->izq, recorrido, visita, elemExtra);
      avl_recorrer_in(raíz->der, recorrido, visita, elemExtra);
      visita(raíz->dato, elemExtra);
      break;
    case AVL_RECORRIDO_PRE:
      visita(raíz->dato, elemExtra);
      avl_recorrer_in(raíz->izq, recorrido, visita, elemExtra);
      avl_recorrer_in(raíz->der, recorrido, visita, elemExtra);
      break;
    default:
      break;
  }
}

void avl_imprimir_in(AVLNodo* nodo, FuncionImpresora imprime) {
  if (nodo == NULL) {
    return;
  }

  avl_imprimir_in(nodo->izq, imprime);

  for (int i = 0; i < nodo->altura; i++) printf("    ");
  imprime(nodo->dato);
  printf("\n");

  avl_imprimir_in(nodo->der, imprime);
}

AVLNodo* avl_eliminar_in(AVLNodo* raíz, void* dato, FuncionComparadora compara,
                         FuncionDestructora destruye) {
  if (raíz == NULL) {
    return NULL;
  }
  int dif = compara(dato, raíz->dato);
  if (dif > 0) {
    raíz->der = avl_eliminar_in(raíz->der, dato, compara, destruye);

  } else if (dif < 0) {
    raíz->izq = avl_eliminar_in(raíz->izq, dato, compara, destruye);
  } else {
    raíz = eliminar_raiz(raíz, destruye, compara);
  }
  actualizar_altura(raíz);
  raíz = balancear(raíz);
  return raíz;
}

/* Funciones de Librería */

AVL avl_crear(FuncionCopiadora copia, FuncionComparadora compara,
              FuncionDestructora destruye) {
  AVL árbol;
  árbol.compara = compara;
  árbol.copia = copia;
  árbol.destruye = destruye;
  árbol.raíz = NULL;
  return árbol;
}

void avl_destruir(AVL árbol) { avl_destruir_in(árbol.raíz, árbol.destruye); }

int avl_buscar(AVL árbol, void* elem) {
  return avl_buscar_in(árbol.raíz, elem, árbol.compara);
}

AVL avl_insertar(AVL árbol, void* elem) {
  árbol.raíz = avl_insertar_in(árbol.raíz, elem, árbol.compara, árbol.copia);
  return árbol;
}

int avl_validar(AVL árbol) { return avl_validar_in(árbol.raíz); }

void avl_recorrer(AVL árbol, AVLRecorrido recorrido,
                  FuncionVisitanteExtra visita, void* elemExtra) {
  avl_recorrer_in(árbol.raíz, recorrido, visita, elemExtra);
}

void avl_imprimir(AVL árbol, FuncionImpresora imprime) {
  avl_imprimir_in(árbol.raíz, imprime);
}

AVL avl_eliminar(AVL árbol, void* dato) {
  árbol.raíz = avl_eliminar_in(árbol.raíz, dato, árbol.compara, árbol.destruye);
  return árbol;
}