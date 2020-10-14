#pragma once
#include <iostream>
#include "Temporada.h"

using namespace std;

// No hereda de Video, sino que almacena temporadas que almacenan episodios que si heredan de Video
class Serie
{
private:
	// Siguiente serie de la lista ligada
	Serie* siguiente;
	// Temporada que inicia la lista de temporadas para esta serie especificamente
	Temporada* temporada_raiz;
	string id;
	string nombre;
	string genero;
public:
	// Constructores
	Serie();
	Serie(string _id, string _nombre, string _genero);
	
	// Destructor dado que cada nueva serie se crea alojando memoria
	~Serie();

	// Getters
	Serie* getSiguiente();
	string getTitulo();
	string getID();
	string getGenero();
	Temporada* getRaiz();

	// Setter del siguiente nodo Serie
	void setSiguiente(Serie& siguiente_serie);
};