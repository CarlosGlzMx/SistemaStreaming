#include "utileria.h"

// Obtiene un entero desde getline, sin errores de tipo y con limites de verificación
int inputMyInt(int lim_a, int lim_b, string mensaje_inicial, string mensaje_error)
{
	// Corrige si los limites se proporcionan en orden incorrecto
	if (lim_a > lim_b) {
		swapMyInts(&lim_a, &lim_b);
	}

	// Obtiene el entero como string una primera vez con el mensaje inicial
	string myInput;
	cout << mensaje_inicial;

	// Variable que almacene el entero a devolver, inicializado fuera de rango
	int myInt = lim_a - 1;

	// Ciclo que verifica los limites y que se ingrese especificamente un entero
	do {
		getline(cin, myInput);
		// Marca el error si lo ingresado no es un número
		if (!myStringIsNumeric(myInput)) {
			myInt = lim_a - 1;
			cout << mensaje_error;
		}
		else {
			// Utiliza un stream para insertar el valor en el string a un dato int
			stringstream myStream(myInput);
			myStream >> myInt;
			// Marca el error si no se está en el rango buscado
			if (myInt > lim_b || myInt < lim_a) {
				cout << mensaje_error;
			}
		}
	} while (myInt > lim_b || myInt < lim_a);

	return myInt;
}

// Intercambia los dos valores enteros almacenados en dos variables
void swapMyInts(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// Obtiene un decimal desde getline, sin errores de tipo y con limites de verificación
float inputMyFloat(float lim_a, float lim_b, string mensaje_inicial, string mensaje_error)
{
	// Corrige si los limites se proporcionan en orden incorrecto
	if (lim_a > lim_b) {
		swapMyFloats(&lim_a, &lim_b);
	}

	// Obtiene el decimal como string una primera vez con el mensaje inicial
	string myInput;
	cout << mensaje_inicial;

	// Variable que almacene el decimal a devolver, inicializado fuera de rango
	float myFloat = lim_a - 1;

	// Ciclo que verifica los limites y que se ingrese especificamente un numero
	do {
		getline(cin, myInput);
		// Marca el error si lo ingresado no es un número
		if (!myStringIsNumeric(myInput)) {
			myFloat = lim_a - 1;
			cout << mensaje_error;
		}
		else {
			// Utiliza un stream para insertar el valor en el string a un dato int
			stringstream myStream(myInput);
			myStream >> myFloat;
			// Marca el error si no se está en el rango buscado
			if (myFloat > lim_b || myFloat < lim_a) {
				cout << mensaje_error;
			}
		}
	} while (myFloat > lim_b || myFloat < lim_a);

	return myFloat;
}

// Intercambia los dos valores decimales almacenados en dos variables
void swapMyFloats(float* a, float* b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

// Verifica si una cadena de texto contiene la estructura de un entero (no considera int overflow)
int myStringIsNumeric(string texto)
{
	int posicion = 1;
	// Itera por los caracteres de un string para verificar si cumple con las condiciones de un número
	for (char& c : texto) {
		// Verifica si el caracter está fuera del rango numérico
		if ((int)c > 57 || (int)c < 48) {
			// Verifica la posibilidad de un signo "-" solamente al inicio de la cadena, o de un punto
			if (((int)c != 45 || posicion != 1) && (int)c != 46) {
				return 0;
			}
		}
		posicion++;
	}
	return 1;
}
