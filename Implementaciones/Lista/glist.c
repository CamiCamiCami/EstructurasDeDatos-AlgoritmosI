#include "glist.h"
#include <assert.h>
#include <stdlib.h>



GList glist_crear() { return NULL; }


void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}


int glist_vacia(GList list) { return (list == NULL); }


GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

GList glist_agregar_final(GList list, void *data, FuncionCopia copy) {
  if(list == NULL) {
    GNode *newNode = malloc(sizeof(GNode));
    assert(newNode != NULL);
    newNode->next = list;
    newNode->data = copy(data);
    return newNode;
  }

  list->next = glist_agregar_final(list->next, data, copy);
  return list;
}

void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

GList glist_eliminar_inicio(GList lista, FuncionDestructora destruir) {
  if (lista == NULL) return NULL;
  GList sig = lista->next;
  destruir(lista->data);
  free(lista);
  return sig;
}

GList glist_eliminar_final(GList lista, FuncionDestructora destruir) {
  if (lista == NULL) return lista;
  if (lista->next == NULL) {
    destruir(lista->data);
    free(lista);
    return NULL;
  }
  lista->next = glist_eliminar(lista->next, destruir);
  return lista;
}

void *glist_buscar(GList lista, int pos) {
  if(pos == 0) {
    return lista->data;
  }
  return glist_buscar(lista->next, pos-1);
}


int glist_largo(GList lista) {
  if (lista == NULL) {
    return 0;
  }

  return glist_largo(lista->next) + 1;
}