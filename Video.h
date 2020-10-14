#pragma once
#include <iostream>

using namespace std;

// Clase abstracta, no se generan instancias pero se usa de base para pelicula y episodio
class Video
{
protected:
	string id;
	string titulo;
	string duracion;
	string genero;
	float calificacion;
public:
	// Constructores
	Video();
	Video(string _id, string _titulo, string _duracion, string _genero, float _calificacion);

	// Getters
	string getTitulo();
	string getId();
	float getCalificacion();
	string getGenero();

	// Setter
	void setCalificacion(float _calificacion);

	// Sobrecarga de operador
	friend ostream& operator<<(ostream& salida, Video& _video);
};

