#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "listas/gpila.h"

// Función auxiliar para crear enteros en el heap
int *crear_entero(int n)
{
    int *res = malloc(sizeof(int));
    *res = n;
    return res;
}

void test_crear_vacia()
{
    printf("Ejecutando: test_crear_vacia... ");
    GPila p = gpila_crear();
    assert(gpila_vacia(p) == 1);
    assert(gpila_len(p) == 0);
    gpila_destruir(p);
    printf("PASÓ\n");
}

void test_push_pop()
{
    printf("Ejecutando: test_push_pop... ");
    GPila p = gpila_crear();
    int *d1 = crear_entero(10);
    int *d2 = crear_entero(20);

    p = gpila_push(p, d1);
    assert(gpila_len(p) == 1);
    assert(*(int *)gpila_top(p) == 10);

    p = gpila_push(p, d2);
    assert(gpila_len(p) == 2);
    assert(*(int *)gpila_top(p) == 20); // LIFO: el último es el top

    // Pop del primer elemento
    p = gpila_pop(p);
    assert(gpila_len(p) == 1);
    assert(*(int *)gpila_top(p) == 10);

    // Pop del último elemento
    p = gpila_pop(p);
    assert(gpila_vacia(p) == 1);

    // Limpieza (los datos fueron extraídos o manejados)
    free(d1);
    free(d2);
    gpila_destruir(p);
    printf("PASÓ\n");
}

void test_orden_lifo()
{
    printf("Ejecutando: test_orden_lifo... ");
    GPila p = gpila_crear();
    int valores[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++)
    {
        p = gpila_push(p, &valores[i]);
    }

    assert(gpila_len(p) == 5);

    // Verificamos que salgan en orden inverso (5, 4, 3, 2, 1)
    for (int i = 4; i >= 0; i--)
    {
        assert(*(int *)gpila_top(p) == valores[i]);
        p = gpila_pop(p);
    }

    assert(gpila_vacia(p));
    gpila_destruir(p);
    printf("PASÓ\n");
}

int main()
{
    printf("=== INICIANDO TESTS DE GPILA ===\n");

    test_crear_vacia();
    test_push_pop();
    test_orden_lifo();

    printf("=== TODOS LOS TESTS PASARON EXITOSAMENTE ===\n");
    return 0;
}