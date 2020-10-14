#include "Video.h"

// Constructores por defecto de Video, no se utiliza dado que es una clase base
Video::Video()
{
	id = "";
	titulo = "";
	duracion = "";
	genero = "";
	calificacion = 0.0f;
}

// Constructores por argumentos de Video, no se utiliza dado que es una clase base
Video::Video(string _id, string _titulo, string _duracion, string _genero, float _calificacion)
{
	id = _id;
	titulo = _titulo;
	duracion = _duracion;
	genero = _genero;
	calificacion = 0.0f;
}

// Metodos getters, aplicables para peliculas y episodios
string Video::getTitulo()
{
	return titulo;
}

string Video::getId()
{
	return this->id;
}

float Video::getCalificacion()
{
	return this->calificacion;
}

string Video::getGenero()
{
	return this->genero;
}

// Unico metodo setter, sirve para la funcion de reasingnar calificaciones
void Video::setCalificacion(float _calificacion)
{
	this->calificacion = _calificacion;
}

// Sobrecarga del operador << para facilitar la impresion total de peliculas, o parcial de episodios
ostream& operator<<(ostream& salida, Video& _video)
{
	salida << _video.titulo << " - " << _video.genero << " - " << _video.calificacion << " - " << _video.duracion << " - " << _video.id;
	return salida;
}
