/*****************************************************************//**
 * \file   proyecto_final.cpp
 * \brief  Práctica final de informática.\n
 *		   1ºGIET Escuela Superior Tecnica de Ingeniería (ETSE-UV). 
 *
 * \author WINSRROW
 * \date   December 2020
 *********************************************************************/


// Inicio include. 
#include <iostream>
#include <fstream>
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
void Presentacion(void); //!< Función para mostrar la presentación del programa.




// Fin cabeceras de las funciones incluidas en este archivo.


int main()
{
	Presentacion();

    system("PAUSE");
    return 0;
}

void Presentacion(void)
{
	system("CLS");

	cout << endl;
	cout << green << " * * * * * * * * * *" << red << " PRACTICA Final " << green << " * * * * * * * * * * * * * *" << endl;
	cout << red   << "                 Manejo de una libreria                         " << reset << endl;
	cout << endl;

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

	cout << green << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	cout <<          " *                                                             *" << endl;
	cout <<          " *" << reset << " Programa desarrollado por " << yellow << "Javier Sanchez.                   " << green << "*" << endl;
	cout <<          " *" << reset << " Version " << green  <<"1.0                                                 " << green << "*" << endl;
	cout << green << " *                                                             *" << endl;
	cout <<          " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << reset << endl;
	cout << endl << endl;

	system("PAUSE");
}






