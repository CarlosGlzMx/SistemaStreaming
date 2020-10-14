#include "Temporada.h"

// Constructor por defecto, utilizado para las temporadas raiz
Temporada::Temporada()
{
	siguiente = NULL;
	episodio_raiz = new Episodio();
	numero = 0;
}

// Constructor por argumentos utilizado al importar nuevos episodios
Temporada::Temporada(int _numero)
{
	siguiente = NULL;
	episodio_raiz = new Episodio();
	numero = _numero;
}

// Destructor de temporada dado que cada temporada se crea alojando memoria
Temporada::~Temporada()
{
	// Al borrar una temporada, tambien se lleva a cabo la limpieza de sus episodios, inciando con la raiz
	delete this->getRaiz();
	// Va borrando las temporadas de la serie a traves de recursion, termina al encontrarse el apuntador NULL
	if (this->getSiguiente() != NULL) {
		delete this->getSiguiente();
	}
}

// Getters
Temporada* Temporada::getSiguiente()
{
	return siguiente;
}

int Temporada::getNumero()
{
	return this->numero;
}

Episodio* Temporada::getRaiz()
{
	return episodio_raiz;
}

// Setter del siguiente nodo Temporada
void Temporada::setSiguiente(Temporada& siguiente_temporada)
{
	this->siguiente = &siguiente_temporada;
}


