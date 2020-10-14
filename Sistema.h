#pragma once
#include <iostream>
#include "Serie.h"
#include "Pelicula.h"

using namespace std;

// Clase designada para manejar la aplicacion
class Sistema
{
private:
	// Raices de listas ligadas principales, de peliculas y series
	Pelicula* pelicula_raiz;
	Serie* serie_raiz;
public:
	// Constructor unico y destructor para manejar todos los alojamientos de memoria
	Sistema();
	~Sistema();

	// Funciones escenciales del ciclo en el menú
	void comenzar();
	void importar_peliculas();
	void importar_series();
	void importar_episodios();
	void mostrarPorCondicion();
	void calificarTitulo();

	// Funciones getter de apoyo
	Serie* getSerieByID(string _id_serie);
	Pelicula* getPeliculaByTitulo(string titulo);
	Episodio* getEpisodioByTitulo(string titulo);

	// Metodos push para agregar nuevos elementos a las listas al importar
	void pushPelicula(Pelicula& nueva_pelicula);
	void pushSerie(Serie& nueva_serie);
	void pushEpisodio(Episodio& nuevo_episodio);

	// Metodos de impresion con modificadores
	void imprimirPeliculas(int tipo = 0, float calificacion = 0, string genero = "");
	void imprimirEpisodios(int tipo = 0, float calificacion = 0, string genero = "", string serie = "");
};