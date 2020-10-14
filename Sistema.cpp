#include <fstream>
#include <cstdlib>
#include <sstream>
#include "Sistema.h"
#include "utileria.h"

using namespace std;

// El constructor solo genera los nodos de peliculas y series en la raíz, pero están vacíos
Sistema::Sistema()
{
	pelicula_raiz = new Pelicula();
	serie_raiz = new Serie();
}

// Destructor para manejar correctamente la liberacion de la memoria alojada
Sistema::~Sistema()
{
	// Inicia el proceso de limpieza para las peliculas y luego para las series, englobando toda la memoria alojada
	delete pelicula_raiz;
	delete serie_raiz;
}

// Funcion que maneja las funciones del sistema
void Sistema::comenzar()
{
	// Bienvenida y declaracion del texto de menu
	int seleccion = -1;
	cout << "BIENVENIDO A SU BASE DE DATOS DE SERIES Y PELICULAS" << endl;
	string menu = 
		"-----------------------------------------------------\n"
		"MENU PRINCIPAL\n"
		"1) Importar archivo de datos\n"
		"2) Buscar videos por calificacion o genero\n"
		"3) Mostrar episodios de una serie por calificacion\n"
		"4) Mostrar peliculas por calificacion\n"
		"5) Calificar un video\n"
		"0) Salir\n"
		"Seleccione una opcion: ";

	// Ciclo principal de la aplicacion
	while (seleccion != 0) {
		seleccion = inputMyInt(0, 5, menu, "Ingrese una opcion valida: ");
		// Ejecucion de la seleccion, se utilizan llaves en el caso de requerir variables locales en los case
		switch (seleccion) {
			// Importa datos de los 3 archivos escenciales
			case 1:
				importar_peliculas();
				importar_series();
				importar_episodios();
				break;
			// Muestra todo tipo de video, filtrados por calificacion o genero
			case 2:
				mostrarPorCondicion();
				break;
			// Muestra los episodios de una serie con una calificacion
			case 3: {
				string serie;
				cout << "Ingrese la serie buscada: ";
				getline(cin, serie);
				float calificacion = inputMyFloat(0.0f, 10.0f, "Ingrese la calificacion buscada: ", "Ingrese un valor valido: ");
				imprimirEpisodios(3, calificacion, "", serie);
				break;
			}
			// Muestra todas las peliculas con una calificacion
			case 4: {
				float calificacion = inputMyFloat(0.0f, 10.0f, "Ingrese la calificacion buscada: ", "Ingrese un valor valido: ");
				imprimirPeliculas(1, calificacion, "");
				break;
			}
			// Permite reasignar calificacion a un video
			case 5:
				calificarTitulo();
				break;
		}
	}
}

// Lee las peliculas de un archivo csv, y las agrega a una lista ligada
void Sistema::importar_peliculas()
{
	try {
		// Abre el archivo con los datos a importar
		ifstream peliculas("peliculas.csv");

		// Lanza excepcion especifica con mensaje
		if (!peliculas.is_open()) { throw string("No se encontró el archivo peliculas.csv"); }

		// Comienza la lectura de peliculas
		string linea, id, nombre, duracion, genero, temp_cal;
		float calificacion;

		// Lee cada linea del archivo, cada pelicula
		while (getline(peliculas, linea)) {
			// Separa los datos de cada linea por sus comas, considerando el formato predefinido para el csv
			stringstream hilera(linea);
			getline(hilera, id, ',');
			getline(hilera, nombre, ',');
			getline(hilera, duracion, ',');
			getline(hilera, genero, ',');

			// Trabaja diferente la calificacion para almacenarla como float
			getline(hilera, temp_cal, ',');
			stringstream temp_cal_2(temp_cal);
			temp_cal_2 >> calificacion;

			// Crea un apuntador a la nueva pelicula
			Pelicula* nueva_pelicula = new Pelicula(id, nombre, duracion, genero, calificacion);

			// Une la nueva pelicula a la lista de peliculas
			pushPelicula(*nueva_pelicula);
		}

		// Cierra el archivos con los datos
		peliculas.close();
	}
	catch (string excepcion) {
		// Termina la funcion de importar al presentarse errores
		cerr << "Error: " << excepcion << endl;
		return;
	}
}

// Lee las series de un archivo csv, y las agrega a una lista ligada
void Sistema::importar_series()
{
	try {
		// Abre el archivo con los datos a importar
		ifstream series("series.csv");

		// Lanza excepcion especifica con mensaje
		if (!series.is_open()) { throw string("No se encontró el archivo series.csv"); }

		// Comienza la lectura de series
		string linea, id, nombre, genero, temp_temporadas;
		float temporadas;

		// Lee cada linea del archivo, cada serie
		while (getline(series, linea)) {
			// Separa los datos de cada linea por sus comas
			stringstream hilera(linea);
			getline(hilera, id, ',');
			getline(hilera, nombre, ',');
			getline(hilera, genero, ',');

			// Trabaja diferente el numero de temporadas para almacenarlo como float
			getline(hilera, temp_temporadas, ',');
			stringstream temp_temporadas_2(temp_temporadas);
			temp_temporadas_2 >> temporadas;

			// Crea un apuntador a la nueva serie
			Serie* nueva_serie = new Serie(id, nombre, genero);

			// Une la nueva serie a la lista de series
			pushSerie(*nueva_serie);
		}

		// Cierra el archivo con los datos
		series.close();
	}
	catch (string excepcion) {
		// Termina la funcion de importar al presentarse errores
		cerr << "Error: " << excepcion << endl;
		return;
	}
}

// Lee los episodios de un archivo csv, y los agrega a sus series y temporadas
void Sistema::importar_episodios()
{
	try {
		// Abre el archivo con los datos a importar
		ifstream episodios("episodios.csv");

		// Lanza excepcion especifica con mensaje
		if (!episodios.is_open()) { throw string("No se encontró el archivo episodios.csv"); }

		// Comienza la lectura de episodios
		string linea, id, id_serie, nombre, duracion, genero_serie, temp_cal, temp_temporada;
		float calificacion;
		int temporada;

		// Lee cada linea del archivo, cada episodio
		while (getline(episodios, linea)) {
			// Separa los datos de cada linea por sus comas
			stringstream hilera(linea);
			getline(hilera, id_serie, ',');
			getline(hilera, id, ',');
			getline(hilera, nombre, ',');
			getline(hilera, duracion, ',');

			// Trabaja diferente la calificacion y la temporada para almacenarlas como float
			getline(hilera, temp_cal, ',');
			stringstream temp_cal_2(temp_cal);
			temp_cal_2 >> calificacion;
			getline(hilera, temp_temporada, ',');
			stringstream temp_temporada_2(temp_temporada);
			temp_temporada_2 >> temporada;

			// Recupera el genero de la serie, si la serie no existe, deja el genero de una serie vacia
			Serie* serie_del_episodio = getSerieByID(id_serie);
			genero_serie = serie_del_episodio->getGenero();

			// Maneja el caso de una serie vacia, la borra
			if (serie_del_episodio->getTitulo().compare("") == 0) {
				delete serie_del_episodio;
			}

			// Crea un apuntador al nuevo episodio
			Episodio* nuevo_episodio = new Episodio(id, nombre, duracion, genero_serie, calificacion, temporada, id_serie);

			// Une el nuevo episodio a su serie y a su temporada
			pushEpisodio(*nuevo_episodio);
		}

		// Cierra el archivos con los datos
		episodios.close();
	}
	catch (string excepcion) {
		// Termina la funcion de importar al presentarse errores
		cerr << "Error: " << excepcion << endl;
		return;
	}
}

// Permite al usuario ingresar condiciones de filtrado
void Sistema::mostrarPorCondicion()
{
	// Menu con las dos opciones de filtrado
	string menu = "Tipos de busqueda filtrada\n"
		"1) Por calificacion\n"
		"2) Por genero\n"
		"Ingrese su seleccion: ";
	// Ejecucion de las impresiones segun la respuesta del tipo
	int tipo = inputMyInt(1, 2, menu, "Ingrese una opcion valida: ");
	if (tipo == 1) {
		float calificacion = inputMyFloat(0.0f, 10.0f, "Ingrese la calificacion buscada: ", "Ingrese un valor valido: ");
		imprimirPeliculas(tipo, calificacion, "");
		imprimirEpisodios(tipo, calificacion, "", "");
	}
	else {
		string genero;
		cout << "Ingrese el genero deseado: ";
		getline(cin, genero);
		imprimirPeliculas(tipo, -1, genero);
		imprimirEpisodios(tipo, -1, genero, "");
	}
}

// Permite al usuario elegir un titulo y cambiarle su calificacion
void Sistema::calificarTitulo()
{
	// Define las variables de la funcion y obtiene el titulo a accesar
	string titulo;
	float calificacion;
	cout << "Ingrese el titulo que desee calificar: ";
	getline(cin, titulo);

	// Busca el titulo inicialmente en las peliculas
	Pelicula* pelicula_actual = getPeliculaByTitulo(titulo);
	if (pelicula_actual->getTitulo() != "") {
		// Al no ser una pelicula vacia, cambia la calificacion de la pelicula encontrada
		calificacion = inputMyFloat(0.0f, 10.0f, "Ingrese la nueva calificacion: ", "Ingrese un valor valido: ");
		pelicula_actual->setCalificacion(calificacion);
	}
	else {
		// Al ser una pelicula vacia, se borra y se consideran los episodios
		delete pelicula_actual;
		Episodio* episodio_actual = getEpisodioByTitulo(titulo);
		if (episodio_actual->getTitulo() != "") {
			// Al no ser un episodio vacio, cambia la calificacion del episodio encontrado
			calificacion = inputMyFloat(0.0f, 10.0f, "Ingrese la nueva calificacion: ", "Ingrese un valor valido: ");
			episodio_actual->setCalificacion(calificacion);
		}
		else {
			// Al ser un episodio vacio, se borra y se concluye que no hay tal titulo en la aplicacion
			delete episodio_actual;
			cout << "No se encontro un titulo con tal nombre, intente de nuevo o importe mas datos" << endl;
			return;
		}
	}
	// Confirma la modificacion y sale de la funcion
	cout << "Se ha cambiado la calificacion de " << titulo << " a " << calificacion << endl;
}

// Agrega una pelicula al final de la lista ligada
void Sistema::pushPelicula(Pelicula& nueva_pelicula)
{
	// Ingresa a la lista por la raiz
	Pelicula* pelicula_actual = pelicula_raiz;
	// Sigue la lista hasta su final, donde no hay un siguiente (o es NULL)
	while (pelicula_actual->getSiguiente() != NULL) {
		pelicula_actual = pelicula_actual->getSiguiente();
		// Verifica que no sea una pelicula repetida
		if (pelicula_actual->getId().compare(nueva_pelicula.getId()) == 0) {
			// En el caso de ser repetida borra el objeto que se habia creado y termina push
			delete &nueva_pelicula;
			return;
		}
	}
	// Asigna a la nueva pelicula como el nuevo final de la lista
	pelicula_actual->setSiguiente(nueva_pelicula);
}

// Agrega una serie al final de la lista ligada
void Sistema::pushSerie(Serie& nueva_serie)
{
	// Ingresa a la lista por la raiz
	Serie* serie_actual = serie_raiz;
	// Sigue la lista hasta su final, donde no hay un siguiente (o es NULL)
	while (serie_actual->getSiguiente() != NULL) {
		serie_actual = serie_actual->getSiguiente();
		// Verifica que no sea una serie repetida
		if (serie_actual->getID().compare(nueva_serie.getID()) == 0) {
			// En el caso de ser repetida borra el objeto que se habia creado y termina push
			delete& nueva_serie;
			return;
		}
	}
	// Asigna a la nueva serie como el nuevo final de la lista
	serie_actual->setSiguiente(nueva_serie);
}

// Agrega un episodio a su serie y a su temporada, crea una nueva temporada si no existe
void Sistema::pushEpisodio(Episodio& nuevo_episodio)
{
	// Ingresa a la red de series y temporadas por la serie raiz
	Serie* serie_actual = serie_raiz;
	//  Verifica todas las series, buscando la del episodio
	while (serie_actual->getSiguiente() != NULL) {
		serie_actual = serie_actual->getSiguiente();
		// Continua a las temporadas al encontrar la serie
		if (serie_actual->getID().compare(nuevo_episodio.getIdSerie()) == 0) {
			Temporada* temporada_actual = serie_actual->getRaiz();
			// Verifica todas las temporadas
			while (temporada_actual->getSiguiente() != NULL) {
				temporada_actual = temporada_actual->getSiguiente();
				// Continua a los episodios al encontrar la temporada
				if (temporada_actual->getNumero() == nuevo_episodio.getTemporada()) {
					Episodio* episodio_actual = temporada_actual->getRaiz();
					// Recorre todos los episodios y lo une al final de la temporada
					while (episodio_actual->getSiguiente() != NULL) {
						episodio_actual = episodio_actual->getSiguiente();
						// Verifica que no sea un episodio repetido en la temporada
						if (episodio_actual->getId().compare(nuevo_episodio.getId()) == 0) {
							// En el caso de ser repetido, borra el objeto que se habia creado y sale de push
							delete& nuevo_episodio;
							return;
						}
					}
					// Asigna al episodio al final de la temporada existente
					episodio_actual->setSiguiente(nuevo_episodio);
					return;
				}
			}
			// Agrega una nueva temporada al final de las temporadas
			while (temporada_actual->getSiguiente() != NULL) {
				temporada_actual = temporada_actual->getSiguiente();
			}
			Temporada* nueva_temporada = new Temporada(nuevo_episodio.getTemporada());
			temporada_actual->setSiguiente(*nueva_temporada);
			temporada_actual = temporada_actual->getSiguiente();
			// Asigna al episodio al inicio (que tambien es el final) de la temporada creada
			temporada_actual->getRaiz()->setSiguiente(nuevo_episodio);
			return;
		}
	}
	// En el caso de no encontrase la serie, borra el objeto creado y notifica al usuario
	cout << "No se logro agregar el episodio: " << nuevo_episodio.getId() << ", no se ha agregado su serie." << endl;
	delete& nuevo_episodio;
}

// Obtiene una serie por su ID, sirve para manejar los episodios
Serie* Sistema::getSerieByID(string _id_serie)
{
	// Ingresa a la lista por la raiz
	Serie* serie_actual = serie_raiz;
	// Verifica todas las series
	while (serie_actual->getSiguiente() != NULL) {
		serie_actual = serie_actual->getSiguiente();
		// Devuelve la serie con el mismo ID
		if (serie_actual->getID().compare(_id_serie) == 0) {
			return serie_actual;
		}
	}
	// Concluye que no hay ninguna serie con tal ID y se devuelve una serie vacia
	Serie* vacia = new Serie();
	cout << "No se encontro una serie para el ID: " << _id_serie << endl;
	return vacia;
}

// Obtiene una pelicua por su nombre, sirve para accesar rapidamente un titulo
Pelicula* Sistema::getPeliculaByTitulo(string titulo)
{
	// Ingresa a las peliculas por la raiz
	Pelicula* pelicula_actual = pelicula_raiz;
	// Verifica todas las peliculas
	while (pelicula_actual->getSiguiente() != NULL) {
		pelicula_actual = pelicula_actual->getSiguiente();
		// Devuelve la serie con el titulo buscado
		if (pelicula_actual->getTitulo().compare(titulo) == 0) {
			return pelicula_actual;
		}
	}
	// Concluye que no hay una pelicula con tal titulo y se devuelve una pelicula vacia
	Pelicula* vacia = new Pelicula();
	return vacia;
}

// Obtiene un episodio por su nombre, sirve para accesar rapidamente un titulo
Episodio* Sistema::getEpisodioByTitulo(string titulo)
{
	// Ingresa a los episodios desde las series
	Serie* serie_actual = serie_raiz;
	//  Itera por todas las series
	while (serie_actual->getSiguiente() != NULL) {
		serie_actual = serie_actual->getSiguiente();
		Temporada* temporada_actual = serie_actual->getRaiz();
		// Itera por todas las temporadas
		while (temporada_actual->getSiguiente() != NULL) {
			temporada_actual = temporada_actual->getSiguiente();
			Episodio* episodio_actual = temporada_actual->getRaiz();
			// Verfica todos los episodios
			while (episodio_actual->getSiguiente() != NULL) {
				episodio_actual = episodio_actual->getSiguiente();
				// Devuelve el episodio con el titulo buscado
				if (episodio_actual->getTitulo().compare(titulo) == 0) {
					return episodio_actual;
				}
			}
		}
	}
	// Concluye que no hay un episodio con tal titulo y devuelve un episodio vacio
	Episodio* vacio = new Episodio();
	return vacio;
}

// Imprime las peliculas (apoyandose en la sobrecarga de <<) con opciones de filtrado
void Sistema::imprimirPeliculas(int tipo, float calificacion, string genero)
{
	// Tipo 0 no toma criterios, 1 por calificacion, 2 por genero
	Pelicula* pelicula_actual = pelicula_raiz;
	int impresion_exitosa = 0;
	// Itera por todas las peliculas
	while (pelicula_actual->getSiguiente() != NULL) {
		pelicula_actual = pelicula_actual->getSiguiente();
		// Si se quiere buscar por calificacion, ignora las peliculas sin tal calificacion
		if (tipo == 1 && pelicula_actual->getCalificacion() != calificacion) { continue; }
		// Si se quiere buscar por genero, ignora las peliculas sin tal genero
		if (tipo == 2 && pelicula_actual->getGenero().compare(genero) != 0) { continue; }
		// Imprime los contenidos del apuntador, la pelicula
		cout << *pelicula_actual << endl;
		impresion_exitosa = 1;
	}
	// Imprime al menos un mensaje si la funcion no logra imprimir nada
	if (!impresion_exitosa) {
		cout << "No se encontraron peliculas a imprimir" << endl;
	}
}

// Imprime los episodios de una serie (apoyandose en la sobrecarga de <<) con opciones de filtrado
void Sistema::imprimirEpisodios(int tipo, float calificacion, string genero, string serie)
{
	// Tipo 0 no toma criterios, 1 por calificacion, 2 por genero, 3 por serie y calificacion
	Serie* serie_actual = serie_raiz;
	int impresion_exitosa = 0;
	//  Itera por todas las series
	while (serie_actual->getSiguiente() != NULL) {
		serie_actual = serie_actual->getSiguiente();
		// Si se quiere buscar por serie, ignora las demas series
		if (tipo == 3 && serie_actual->getTitulo().compare(serie) != 0) { continue; }
		Temporada* temporada_actual = serie_actual->getRaiz();
		// Itera por todas las temporadas
		while (temporada_actual->getSiguiente() != NULL) {
			temporada_actual = temporada_actual->getSiguiente();
			Episodio* episodio_actual = temporada_actual->getRaiz();
			// Itera por todos los episodios
			while (episodio_actual->getSiguiente() != NULL) {
				episodio_actual = episodio_actual->getSiguiente();
				// Si se quiere buscar por calificacion, ignora los episodios sin tal calificacion
				if ((tipo == 1 || tipo == 3) && episodio_actual->getCalificacion() != calificacion) { continue; }
				// Si se quiere buscar por genero, ignora los episodios sin tal genero
				if (tipo == 2 && episodio_actual->getGenero().compare(genero) != 0) { continue;  }
				// Imprime la serie con los contenidos del apuntador, el episodio
				cout << getSerieByID(episodio_actual->getIdSerie())->getTitulo() << " " << *episodio_actual << endl;
				impresion_exitosa = 1;
			}
		}
	}
	// Imprime al menos un mensaje si la funcion no logra imprimir nada
	if (!impresion_exitosa) {
		cout << "No se encontraron episodios de series a imprimir" << endl;
	}
}
