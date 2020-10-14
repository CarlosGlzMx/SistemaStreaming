#pragma once
#include "Video.h"

class Episodio :public Video {
private:
	// Atributos diferentes a Video, iniciando por un episodio siguiente para la funcionalidad de lista ligada
	Episodio* siguiente;
	// Atributo que almacena la temporada donde se almacena el episodio
	int temporada;
	// Atributo que almacena la serie donde se almacena tal temporada
	string id_serie;
public:
	// Constructores
	Episodio();
	Episodio(string _id, string _titulo, string _duracion, string _genero, float _calificacion, int _temporada, string _id_serie);

	// Destructor dado que cada nuevo episodio se almacena alojando memoria
	~Episodio();

	// Getters
	string getIdSerie();
	int getTemporada();
	Episodio* getSiguiente();

	// Setter
	void setSiguiente(Episodio& siguiente_episodio);

	// Sobrecarga del operador << agregando el numero de temporada
	friend ostream& operator<<(ostream& salida, Episodio& _episodio);
};