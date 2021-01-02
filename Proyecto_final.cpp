/*****************************************************************//**
 * \file   proyecto_final.cpp
 * \brief  Práctica final de informática.\n
 *		   1ºGIET Escuela Superior Tecnica de Ingeniería (ETSE-UV). 
 *
 * \author WINSRROW
 * \version   1.0
 * \date   December 2020
 *********************************************************************/


// Inicio include. 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "termcolor.hpp"; //!< Librería para el coloreado de la terminal.
// Fin include.

// Inicio asignaciones "using".
using namespace std;
using namespace termcolor;
// Fin asignaciones "using".

// Inicio declaraciones de structs.

/** 
* Estructura de datos para almacenar la fecha.
*/
struct Fecha
{
	unsigned short dia    = 1;    //!< Día del mes.
	unsigned short mes    = 1;	  //!< Mes del año.
	unsigned int anyo     = 2000; //!< Año.
 
	unsigned short hora   = 10;	  //!< Hora del día.
	unsigned short minuto = 0;	  //!< Minuto del día.
};


/** 
* Información sobre el libro.
*/
struct Libro
{
	string titulo             = "";   //!< Titulo del libro.
	string autor              = "";	  //!< Autor del libro.
	string genero             = "";	  //!< Genero al que pertenece el libro.
	string isbn               = "";	  //!< Codigo de identificación ISBN del libro.
	Fecha fecha;                      //!< Fecha de edicion.
	unsigned int paginas      = 0;	  //!< Cantidad de páginas.
	unsigned int ejemplares   = 0;	  //!< Número de ejemplares de los que dispone la librería
	unsigned int prestados    = 0;	  //!< Número de ejemplares que se están prestados en ese momento.
};

// Fin declaraciones de structs.

// Inicio declaración de tipos de datos propios.

typedef vector<string> Menu; //!< Tipo de dato menú para especificar que los vectores de strigns usados en los menús no se confundan.


// Fin declaración de tipos de datos propios.


// Inicio cabeceras de las funciones incluidas en este archivo.
	
	// Función de presentación.
	void Presentacion(void); //!< \brief Función para mostrar la presentación del programa.
	// Función de presentación.
	
	// Inicio funciones de muestra de datos
	void mostrarLibro(const vector<Libro>&, int);   //!< \brief Función visualización datos libro.
	
	// Fin funciones de muestra de datos
	
	// Inicio funciones recogida de datos del usuario.
	int VisualizarMenu(const string&, const Menu&); //!< \brief Función Visualización Menú.
	
	// Fin funciones recogida de datos del usuario.

	// Inicio funciones de interacción con archivos.
	bool LeerCsv(vector<vector<string>>&, const string&, char);//!< \brief Función para lectura genérica de los csv.

	// Fin funciones de interacción con archivos.

// Fin cabeceras de las funciones incluidas en este archivo.

/*!
 * \brief Función principal del proyecto.
 * 
 * \return 
 */

int main()
{
	Presentacion(); // Presentación del programa.

	// Inicio declaración de variables de programa.
	vector<Libro> biblioteca;

	// Fin declaración de variables de programa.

	// Inicio bucle principal del programa.

	Menu principal =
	{
		"Mostrar Libros",
		"Alta nuevo libro",
		"Baja libro existente",
		"Mostrar informacion de un ejemplar",
		"Prestar libro",
		"Devolver libro",
		"Salir del programa de gestion"
	};

	int seleccion = 0;

	seleccion = VisualizarMenu("Menu principal", principal);

	cout << endl << seleccion << endl << endl;
	// Fin bucle principal del programa.




    system("PAUSE");
    return 0;
}


// Función de presentación.
void Presentacion(void)
{
	system("CLS"); // Borrado del contenido de la terminal.

	// Inicio bloque de información a pantalla.

	// Titulo de la práctica.
	cout << endl;
	cout << green << " * * * * * * * * * *" << red << " PRACTICA Final " << green << " * * * * * * * * * * * * * *" << endl;
	cout << red   << "                 Manejo de una libreria                         " << reset << endl;
	cout << endl;
	// Titulo de la práctica.

	// Explicación de la práctica.
	cout << " Este programa sirve para el manejo de una libreria." << endl;
	cout << endl;

	cout << " Las funciones basicas son: " << endl;
	cout << "    - Dar de alta libros conforme se recepcionan nuevos ejemplares" << reset << endl;
	cout << "    - Permitir eliminar aquellos libros que, por desgaste, estan inutilizables" << reset << endl;
	cout << "    - Llevar el estocaje de todos los libros de que se dispone, "<<endl
		 << "      pudiendo diferenciar los que estan en la biblioteca de los" << endl
		 << "      que estan prestados en cada momento" << reset << endl;
	cout << "    - Prestar libros a alumnos de la ETSE" << reset << endl;
	cout << endl;
	// Explicación de la práctica.

	// Información del programa.
	cout << green << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	cout <<          " *                                                             *" << endl;
	cout <<          " *" << reset << " Programa desarrollado por " << yellow << "Javier Sanchez.                   " << green << "*" << endl;
	cout <<          " *" << reset << " Version " << green  <<"1.0                                                 "  << green << "*" << endl;
	cout << green << " *                                                             *" << endl;
	cout <<          " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << reset << endl;
	cout << endl << endl;
	// Información del programa.

	system("PAUSE"); // Pausa de ejecución del programa. (Para dar tiempo al usuario a leer los datos.)
}
// Función de presentación.

// Inicio funciones de muestra de datos

/*!
 * Función visualizar datos del libro.
 * 
 * \param libreria  Vector conteniente de todos los libros.
 * \param posicion  Posición del libro el cual se desean visualizar los datos. 
 */
void mostrarLibro(const vector<Libro>& libreria, int posicion)
{
	cout << endl;
	cout << " " << red << "Datos del libro" << reset << endl;

	cout << green << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << reset << endl;
	cout << " Titulo     : " << yellow << libreria[posicion].titulo     << reset << endl;
	cout << " Autor      : " << yellow << libreria[posicion].autor      << reset << endl;
	cout << " Genero     : " << yellow << libreria[posicion].genero     << reset << endl;
	cout << " ISBN       : " << yellow << libreria[posicion].isbn       << reset << endl;
	cout << " Anyo       : " << yellow << libreria[posicion].fecha.anyo << reset << endl;
	cout << " Paginas    : " << yellow << libreria[posicion].paginas    << reset << endl;
	cout << " Ejemplares : " << yellow << libreria[posicion].ejemplares << reset << endl;
	cout << " Prestados  : " << yellow << libreria[posicion].prestados  << reset << endl;
	cout << green << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << reset << endl;

	cout << endl;
}

// Fin funciones de muestra de datos

// Inicio funciones recogida de datos del usuario.

/*!
 *
 * Funcion para la visualización de los menús haciendo uso de el tipo de dato Menu con la posibilidad de añadir un título.
 *
 * @param menu     Menu a visualizar.
 * @param titulo   Titulo del menú.
 *
 * \return valor de la posición del menú seleccionado siempre y cuando el valor introducido sea valido.
 *
 */
int VisualizarMenu(const string& titulo, const Menu& menu)
{
	// Variables de la función.
	int seleccion = 0;
	bool repetir = false;
	// Variables de la función.

	system("CLS"); // Borrado de la pantalla.

	// Visualizacion del titulo del menú.
	cout << endl;
	cout << " " << red << titulo << reset << endl;
	// Visualizacion del titulo del menú.

	// Visualización del menú.
	cout << green << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << reset << endl;
	for (unsigned int i = 0; i < menu.size(); i++)
	{
		cout << " " << i << "- " << menu[i] << endl;
	}
	cout << green << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << reset << endl;
	// Visualización del menú.
	cout << endl;

	// Solicitud y comprobación de validez del valor del menú.
	while (!repetir)
	{
		// Solicitud del valor del menú.
		cout << " Introduce el numero del menu que se desee : ";
		cin >> seleccion;
		cin.ignore();
		// Solicitud del valor del menú.

		// Comprobación del valor introducido para confirmar que sea valido.
		if (seleccion < 0 || seleccion >= menu.size())
		{
			cout << red << " El valor introducido no se encuentra en los parametros." << reset << endl;
		}
		else
		{
			repetir = true;
		}
		// Comprobación del valor introducido para confirmar que sea valido.
	}
	// Solicitud y comprobación de validez del valor del menú.

	return seleccion; // Devolución de la posición del menú introducido.
}

/*!
 * .
 * 
 * \param libreria
 */
void anadirLibro(vector<Libro>& libreria)
{
	Libro nuevo_libro;
	system("CLS");

	cout << "Titulo: ";
	cin.ignore();
	getline(cin, nuevo_libro.titulo);

	cout << "Autor: ";
	getline(cin, nuevo_libro.autor);

	cout << "Genero: ";
	getline(cin, nuevo_libro.genero);

	cout << "ISBN: ";
	getline(cin, nuevo_libro.isbn);

	cout << "Numero de paginas: ";
	cin >> nuevo_libro.paginas;

	
	cin >> nuevo_libro.isbn;



	libreria.push_back(nuevo_libro);
}


// Fin funciones recogida de datos del usuario.


// Inicio funciones de interacción con archivos.

/*!
* 
 * Función para la lectura de cualquier csv genérico necesario en el proyecto.
 * 
 * \param parsed_csv      Vector bidimensional del csv leido.
 * \param nombre_archivo  Nombre del archivo a leer.
 * \param delimiter       Delimitador para los campos del CSV (, ; . etc).
 * 
 * \return Booleano apertura del archivo.
 * 
 */
bool LeerCsv(vector<vector<string>>& parsed_csv, const string& nombre_archivo, char delimitador)
{
	// Variables internas de la función.
	vector<string> linea;
	string elemento;
	string lineas;
	bool archivo_abierto = true;
	
	fstream archivo;
	// Variables internas de la función.

	archivo.open(nombre_archivo, ios::in); // Abrir el archivo correspondiente como lectura.

	if (archivo) // Comprobación archivo abierto
	{
		// Lectura del fichero.
		while (!archivo.eof())
		{

			getline(archivo, lineas); // Lectura de la línea.

			istringstream tokenStream(lineas);

			while (getline(tokenStream, elemento, delimitador)) // Iteración de la linea para obtener los elementos independientes.
			{
				linea.push_back(elemento); // Creación de la primera dimensión del array.
			}

			parsed_csv.push_back(linea); // Unión de los vectores para formar el vector bidimensional.

			linea.clear(); // Borrado de los datos del vector para poder reutilizarlo para leer la nueva línea.

		}
		// Lectura del fichero.

		archivo.close(); // Cierre del fichero.
	}
	else
	{
		archivo_abierto = false;
	}

	return archivo_abierto;
}


// Fin funciones de interacción con archivos.











