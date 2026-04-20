#include "arrays/gpila.h"

int esParentesisApertura(char c) {
    return c == '(' || c == '{' || c == '[';
}

int esParentesisCierre(char c) {
    return c == ')' || c == '}' || c == ']';
}


int analizaStr(GPila pila, char* str, int indice, int largo) {
    
}