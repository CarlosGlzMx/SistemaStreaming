#include "Pelicula.h"

// Constructor por defecto, utilizado para la pelicula raiz y las peliculas vacias en casos de error
Pelicula::Pelicula()
{
	siguiente = NULL;
	id = "";
	titulo = "";
	duracion = "";
	genero = "";
	calificacion = 0.0f;
}

// Constructor por argumentos, utilizado al importar nuevas peliculas
Pelicula::Pelicula(string _id, string _titulo, string _duracion, string _genero, float _calificacion)
{
	siguiente = NULL;
	id = _id;
	titulo = _titulo;
	duracion = _duracion;
	genero = _genero;
	calificacion = _calificacion;
}

// Destructor de las peliculas dado que las peliculas importadas utilizan memoria alojada
Pelicula::~Pelicula()
{
	// Va borrando las peliculas de la lista a traves de recursion, termina al encontrarse el apuntador NULL
	if (this->getSiguiente() != NULL) {
		delete this->getSiguiente();
	}
}

// Getter del siguiente nodo Pelicula
Pelicula* Pelicula::getSiguiente()
{
	return this->siguiente;
}

// Setter del siguiente nodo Pelicula
void Pelicula::setSiguiente(Pelicula& siguiente_pelicula)
{
	this->siguiente = &siguiente_pelicula;
}
