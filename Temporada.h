#pragma once
#include "Episodio.h"

class Temporada
{
private:
	// Identificador de la temporada, podria ser tambien un string
	int numero;
	// Atributo apuntando a un siguiente nodo Temporada para continuar la lista
	Temporada* siguiente;
	// Cada temporada, parte de una lista, cuenta con su propia lista de episodios
	Episodio* episodio_raiz;
public:
	// Constructores
	Temporada();
	Temporada(int _numero);

	// Destructor dado que cada nueva temporada se crea alojando memoria
	~Temporada();

	// Getters
	Temporada* getSiguiente();
	int getNumero();
	Episodio* getRaiz();

	// Setter del siguiente nodo Temporada
	void setSiguiente(Temporada& siguiente_temporada);
};