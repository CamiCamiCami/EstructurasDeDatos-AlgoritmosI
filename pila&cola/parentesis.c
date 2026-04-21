#include "arrays/gpila.h"
#include "cuenta.h"


int suma(int s1, int s2) {
    return s1+s2;
}

int resta(int r, int m)
{
    return r - m;
}

int producto(int m1, int m2)
{
    return m1 * m2;
}

int division(int d, int D)
{
    return d / D;
}

int esParentesisApertura(char c){
    return c == '(';
}

int esParentesisCierre(char c)
{
    return c == ')';
}

int esNumero(char c) {
    return '0' <= c && c <= '9';
}

int aNumero(char c) {
    return (int)(c - '0');
}

Operador aOperador(char c) {
    switch (c) {
    case '+':
        return suma;
    case '-':
        return resta;
    case '*':
        return producto;
    case '/':
        return division;
    default:
        return NULL;
    }
}

void analizaChar(GPila pila, char c)
{
    if (esParentesisApertura(c))
    {
        gpila_push(pila, cuenta_crear());
    }
    else if (esParentesisCierre(c))
    {
        int resultado = cuenta_calcular(gpila_top(pila));
        gpila_pop(pila);
        cuenta_agregar_operando(gpila_top(pila), resultado);
    }
    else if (esNumero(c))
    {
        cuenta_agregar_operando(gpila_top(pila), aNumero(c));
    }
    else
    {
        Operador op = aOperador(c);
        if (op == NULL)
        {
            printf("error\n");
            exit(1);
        }
        cuenta_agregar_operador(gpila_top(pila), op);
    }
}

int analizarStr(char string[]) {
    GPila pila = gpila_crear();
    gpila_push(pila, cuenta_crear());
    for (int i = 0; string[i]; i++) {
        analizaChar(pila, string[i]);
    }
    int resultado = cuenta_calcular(gpila_top(pila));
    gpila_destruir(pila);
    return resultado;
}


int main() {
    char expr1[] = "((1+3)/(7-3))";
    char expr2[] = "(((1+(2*3))-5)*(2/2))";
    printf("%s == %i\n", expr1, analizarStr(expr1));
    printf("%s == %i\n", expr2, analizarStr(expr2));
}