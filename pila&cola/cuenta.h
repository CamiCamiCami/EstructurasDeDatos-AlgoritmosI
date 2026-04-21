#ifndef __CUENTA_H__
#define __CUENTA_H__

#include "stdlib.h"


typedef int (*Operador)(int, int);


typedef struct __cuenta {
    int operandos;
    int opIzq, opDer;
    Operador operacion;
}* Cuenta;


Cuenta cuenta_crear();

void cuenta_agregar_operando(Cuenta cuenta, int operando);

void cuenta_agregar_operador(Cuenta cuenta, Operador operando);

int cuenta_calcular(Cuenta cuenta);

#endif