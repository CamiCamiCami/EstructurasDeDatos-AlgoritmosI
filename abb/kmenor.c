#include "implementacion/abb.h"
#include "implementacion/abbaux.h"
#include <stdio.h>

int* copiaInt(int* dato) {
    int* nuevo = malloc(sizeof(int));
    *nuevo = *dato;
    return nuevo;
}

void destruyeInt(int* dato) {
    free(dato);
}

int comparaInt(int* dato1, int* dato2) {
    return (*dato1) - (*dato2);
}

void imprimeInt(int* dato) {
    printf("%i", *dato);
}


int main() {
    int numeros[21] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    ABB arbol = ABB_crear((FuncionComparadora)comparaInt, (FuncionCopiadora)copiaInt, (FuncionDestructora)destruyeInt);
    arbol = ABB_insertar(arbol, &numeros[10]);
    arbol = ABB_insertar(arbol, &numeros[5]);
    arbol = ABB_insertar(arbol, &numeros[13]);
    arbol = ABB_insertar(arbol, &numeros[2]);
    arbol = ABB_insertar(arbol, &numeros[6]);
    arbol = ABB_insertar(arbol, &numeros[20]);
    arbol = ABB_insertar(arbol, &numeros[4]);
    arbol = ABB_insertar(arbol, &numeros[18]);
    ABB_imprimir(arbol, (FuncionImpresora)imprimeInt); 
    int k = 9;
    printf("%i\n", *(int*)ABBMenorSuperaK(arbol, &k));
}