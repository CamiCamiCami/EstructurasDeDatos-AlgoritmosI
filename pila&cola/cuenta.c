#include "cuenta.h"

Cuenta cuenta_crear() {
    Cuenta nueva = malloc(sizeof(struct __cuenta));
    nueva->operandos = 0;
    return nueva;
}

void cuenta_agregar_operando(Cuenta cuenta, int operando) {
    if (cuenta->operandos == 0) {
        cuenta->opIzq = operando;
    } else {
        cuenta->opDer = operando;
    }
    cuenta->operandos++;
}

void cuenta_op_der(Cuenta cuenta, int operando) {
    cuenta->opDer = operando;
}

void cuenta_agregar_operador(Cuenta cuenta, Operador operador) {
    cuenta->operacion = operador;
}

int cuenta_calcular(Cuenta cuenta) {
    int resultado;
    if (cuenta->operandos == 1) {
        resultado = cuenta->opIzq;
    } else {
        resultado = cuenta->operacion(cuenta->opIzq, cuenta->opDer);
    }
    free(cuenta);
    return resultado;
}