#include "Serie.h"

// Constructor por defecto, utilizado para la serie raiz del sistema y para series vacias en casos de error
Serie::Serie()
{
	siguiente = NULL;
	temporada_raiz = new Temporada();
	id = "";
	nombre = "";
	genero = "";
}

// Constructor por argumentos, utilizado al importar datos
Serie::Serie(string _id, string _nombre, string _genero)
{
	siguiente = NULL;
	temporada_raiz = new Temporada();
	id = _id;
	nombre = _nombre;
	genero = _genero;
}

// Destructor dado que cada nueva serie se crea alojando memoria
Serie::~Serie()
{
	// Al borrar una serie, tambien se lleva a cabo la limpieza de sus temporadas, inciando con la raiz
	delete this->getRaiz();
	// Va borrando las series de la lista a traves de recursion, termina al encontrarse el apuntador NULL
	if (this->getSiguiente() != NULL) {
		delete this->getSiguiente();
	}
}

// Getters
Serie* Serie::getSiguiente()
{
	return this->siguiente;
}

string Serie::getTitulo()
{
	return this->nombre;
}

string Serie::getID()
{
	return this->id;
}

string Serie::getGenero()
{
	return this->genero;
}

Temporada* Serie::getRaiz()
{
	return temporada_raiz;
}

// Setter para el siguiente nodo Serie
void Serie::setSiguiente(Serie& siguiente_serie)
{
	this->siguiente = &siguiente_serie;
}