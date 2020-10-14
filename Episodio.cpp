#include "Episodio.h"

// Constructor por defecto, usado para los episodios raiz y episodios vacios en casos de error
Episodio::Episodio()
{
	siguiente = NULL;
	id = "";
	titulo = "";
	duracion = "";
	genero = "";
	calificacion = 0.0f;
	temporada = 0;
	id_serie = "";
}

// Constructor por argumentos, para el almacenamiento de los datos cargados
Episodio::Episodio(string _id, string _titulo, string _duracion, string _genero, float _calificacion, int _temporada, string _id_serie)
{
	siguiente = NULL;
	id = _id;
	titulo = _titulo;
	duracion = _duracion;
	genero = _genero;
	calificacion = _calificacion;
	temporada = _temporada;
	id_serie = _id_serie;
}

// Destructor dado que todos los episodios nuevos alojan memoria
Episodio::~Episodio()
{
	// Va borrando los episodios de la temporada a traves de recursion, termina al encontrarse el apuntador NULL
	if (this->getSiguiente() != NULL) {
		delete this->getSiguiente();
	}
}

// Getters
string Episodio::getIdSerie()
{
	return id_serie;
}

int Episodio::getTemporada()
{
	return this->temporada;
}

Episodio* Episodio::getSiguiente()
{
	return siguiente;
}

// Setter del siguiente nodo Episodio
void Episodio::setSiguiente(Episodio& siguiente_episodio)
{
	this->siguiente = &siguiente_episodio;
}

// Sobrecarga del operador << diferente al de Video, incluye temporada
ostream& operator<<(ostream& salida, Episodio& _episodio)
{
	salida << "(" <<  _episodio.temporada << "): " << _episodio.titulo << " - " << _episodio.genero << " - " << _episodio.calificacion << " - " << _episodio.duracion << " - " << _episodio.id;
	return salida;
}
