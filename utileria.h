#pragma once
/* 
Funciones o secuencias de comandos requeridas frecuentemente cuyas implementaciones toman tiempo y espacio en
los archivos, como lo son: validación de valores ingresados, manejo básico de números, "parsing" y demás.
*/

#include <iostream>
#include <sstream>

using namespace std;

// Manejo de enteros
int inputMyInt(int lim_a, int lim_b, string mensaje_inicial, string mensaje_error);
void swapMyInts(int* a, int* b);

// Manejo de decimales
float inputMyFloat(float lim_a, float lim_b, string mensaje_inicial, string mensaje_error);
void swapMyFloats(float* a, float* b);

// Manejo de cadenas
int myStringIsNumeric(string texto);