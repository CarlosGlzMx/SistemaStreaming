#pragma once
#include "Video.h"

class Pelicula:public Video{
private:
	// Unico atributo distinto a Video, funcionalidad de lista ligada
	Pelicula* siguiente;
public:
	// Constructores
	Pelicula();
	Pelicula(string _id, string _titulo, string _duracion, string _genero, float _calificacion);

	// Destructor dado que cada pelicula que se agrega es con memoria alojada
	~Pelicula();

	// Getter para manejar la lista de peliculas
	Pelicula* getSiguiente();

	// Setter que permite agregar peliculas a la lista en posiciones de siguiente
	void setSiguiente(Pelicula &siguiente_pelicula);
};