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
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "termcolor.hpp" //!< Librería para el coloreado de la terminal.
// Fin include.

// Constantes globales
const string archivo_libros = "archivos/libros.csv";
const string archivo_gente  = "archivos/listado_gente.csv";
// Constantes globales

// Inicio asignaciones "using".
using namespace std;
using namespace termcolor;
// Fin asignaciones "using".

// Inicio declaraciones de structs.
/*!
 * Estructura de datos para almacenar la fecha..
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

	// Función de despedida.
	void Creditos(void); //!< \brief Función para presentar los créditos.
    // Función de despedida.

	// Inicio funciones de muestra de datos
	void MostrarLibro(const vector<Libro>&, int);   //!< \brief Función visualización datos libro.
	void MostrarLibros(const vector<Libro>&);  //!< \brief Función visualización contenido biblioteca.
	string Estrellitas(unsigned int);
	// Fin funciones de muestra de datos
	
	// Inicio funciones recogida de datos del usuario.
	int VisualizarMenu(const string&, const Menu&);
	// Fin funciones recogida de datos del usuario.
	void anadirLibro(vector<Libro>& biblioteca);
	// Inicio funciones de interacción con archivos.
	bool LeerCsv(vector<vector<string>>&, const string&, char);
	bool EscribirCsv(vector<vector<string>>& bi_vector, const string& nombre_archivo, char delimitador);
	// Fin funciones de interacción con archivos.

	// Inicio funciones procesado de datos.
	void BVectorToBiblioteca(const vector<vector<string>>&, vector<Libro>&);
	void BibliotecaToBVector(const vector<Libro>&, vector<vector<string>>&);
	bool IsbnExist(const vector<Libro>&, const string&, int);
	// Fin funciones procesado de datos.

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
	vector<vector<string>> data;
	vector<Libro> biblioteca;
	string data_string = "";

	int seleccion_principal = 0;
	int seleccion_auxiliar = 0;

	int aux_var1 = 0; // Variables auxiliares para usos generales.
	int aux_var2 = 0; // Variables auxiliares para usos generales.
	int aux_var3 = 0; // Variables auxiliares para usos generales.
	int aux_var4 = 0; // Variables auxiliares para usos generales.
	unsigned int uns_aux_var1 = 0; // Variables auxiliares para usos generales.
	unsigned int uns_aux_var2 = 0; // Variables auxiliares para usos generales.
	unsigned int uns_aux_var3 = 0; // Variables auxiliares para usos generales.
	unsigned int uns_aux_var4 = 0; // Variables auxiliares para usos generales.

	bool salir = false;

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

	// Fin declaración de variables de programa.

	LeerCsv(data, "archivos/libros.csv", ';');
	BVectorToBiblioteca(data, biblioteca);
	data.clear();

	// Inicio bucle principal del programa.

	while (!salir)
	{

		seleccion_principal = VisualizarMenu("Menu principal", principal);

		if (seleccion_principal == 0)
		{
			MostrarLibros(biblioteca);
		}
		else if (seleccion_principal == 1)
		{
			system("CLS"); // Borrado de pantalla.

			cout << " Introduce el ISBN del libro: "; // Petición del ISBN.
			getline(cin, data_string);

			if (IsbnExist(biblioteca, data_string, aux_var1)) // Comprobación de existencia en la biblioteca.
			{
				cout << " La cantidad de libros de los que se dispone es: " << biblioteca[aux_var1].ejemplares << endl;
				cout << " Introduce la cantidad de libros de los que se dispondra: ";
				cin >> aux_var2;
				cin.ignore();

				while ((aux_var2 <= biblioteca[aux_var1].ejemplares || aux_var2 < 0)&& aux_var2 != -1) // Confirmamos que la cantidad a introducir es mayor a la existente y añadimos una condción de salida como -1.
				{
					cout << " El numero introducido es igual o inferior al numero de ejemplares existentes." << endl;
					cout << " Introduce la cantidad de libros o -1 para salir: ";
					cin >> aux_var2;
					cin.ignore();
				}
				
				if (aux_var2 != -1) // hacemos caso omiso de variar la cantidad de ejemplares en caso de que sea la condición de salida.
				{

					biblioteca[aux_var1].ejemplares = (unsigned int)aux_var2; // Cambiamos la cantidad de ejemplares.
					BibliotecaToBVector(biblioteca, data);         // Guardado de los datos en el fichero.
					EscribirCsv(data, archivo_libros, ';'); // Guardado de los datos en el fichero.
				}
			}
			else
			{
				anadirLibro(biblioteca); // Si no existe llama a la función de introducción de libro.
			}
		}
		else if (seleccion_principal == 2)
		{
			system("CLS"); // Borrado de pantalla.

			cout << " Introduce el ISBN del libro: "; // Petición del ISBN.
			getline(cin, data_string);

			while (!IsbnExist(biblioteca, data_string, aux_var1 && data_string != "-1")) // Comprobación de existencia en la biblioteca.
			{
				system("CLS");
				cout << red << " El libro no existe" << reset << endl;
				cout << " Introduzca de nuevo el ISBN o -1 para salir: ";
				getline(cin, data_string);
			}
			if (data_string != "-1")
			{
				biblioteca.erase(biblioteca.begin() + aux_var1);

				BibliotecaToBVector(biblioteca, data);
				EscribirCsv(data, archivo_libros, ';');

				system("CLS");
				cout << " EL libro con isbn: " << data_string << " ha sido eliminado." << endl;
			}
		}
		else if (seleccion_principal == 3)
		{

		}
		else if (seleccion_principal == 4)
		{

		}
		else if (seleccion_principal == 5)
		{

		}
		else if (seleccion_principal == 6)
		{
			salir = true;
		}
	}

	// Fin bucle principal del programa.

	Creditos();

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

// Función de presentación.
void Creditos(void)
{
	system("CLS"); // Borrado del contenido de la terminal.

	// Inicio bloque de información a pantalla.

	// Titulo de la práctica.
	cout << endl;
	cout << green << " * * * * * * * * * *" << red << " PRACTICA Final " << green << " * * * * * * * * * * * * * *" << endl;
	cout << red << "                 Manejo de una libreria                         " << reset << endl;
	cout << endl;
	// Titulo de la práctica.

	// Despedida.
	cout << " El programa ha finalizado." << endl << endl;
	cout << " Muchas gracias por usar este software." << endl;
	cout << endl;
	// Despedida.

	// Información del programa.
	cout << green << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	cout << " *                                                             *" << endl;
	cout << " *" << reset << " Programa desarrollado por " << yellow << "Javier Sanchez.                   " << green << "*" << endl;
	cout << " *" << reset << " Version " << green << "1.0                                                 " << green << "*" << endl;
	cout << green << " *                                                             *" << endl;
	cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << reset << endl;
	cout << endl << endl;
	// Información del programa.
}
// Función de presentación.

// Inicio funciones de muestra de datos

/*!
 * \param libreria  Vector conteniente de todos los libros.
 * \param posicion  Posición del libro el cual se desean visualizar los datos. 
 */
void MostrarLibro(const vector<Libro>& biblioteca, int posicion)
{
	cout << endl;
	cout << " " << red << "Datos del libro" << reset << endl;

	cout << green << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << reset << endl;
	cout << " Titulo     : " << yellow << biblioteca[posicion].titulo     << reset << endl;
	cout << " Autor      : " << yellow << biblioteca[posicion].autor      << reset << endl;
	cout << " Genero     : " << yellow << biblioteca[posicion].genero     << reset << endl;
	cout << " ISBN       : " << yellow << biblioteca[posicion].isbn       << reset << endl;
	cout << " Anyo       : " << yellow << biblioteca[posicion].fecha.anyo << reset << endl;
	cout << " Paginas    : " << yellow << biblioteca[posicion].paginas    << reset << endl;
	cout << " Ejemplares : " << yellow << biblioteca[posicion].ejemplares << reset << endl;
	cout << " Prestados  : " << yellow << biblioteca[posicion].prestados  << reset << endl;
	cout << green << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << reset << endl;

	cout << endl;
}

/*!
 * \param libreria  Vector conteniente de todos los libros.
 */
void MostrarLibros(const vector<Libro>& biblioteca)
{
	// Declaración de variables de la función.
	unsigned int tamano_biblioteca       = biblioteca.size();            // Variable que contiene el tamaño de la biblioteca para no tener la necesidad de llamar a la función size() más de una vez.
										 							    
	unsigned int espaciado_titulo        = biblioteca[0].titulo.size(); // Variable para el espaciado del texto.
	unsigned int nuevo_espaciado_titulo  = 0;						    // variable auxiliar para el espaciado del texto.
										 							    
	unsigned int espaciado_isbn          = biblioteca[0].isbn.size();   // Variable para el espaciado del isbn.
	unsigned int nuevo_espaciado_isbn    = 0;						    // variable auxiliar para el espaciado del isbn.
																	    
	unsigned int num_estrellas           = 0;                           // Variable para la cantidad de estrellas.
										 							    
	unsigned int libros_verdes           = 0;						    // Contador de libros con ejemplares para prestar.
	unsigned int libros_rojos            = 0;						    // Contador de libros sin unidades disponbles.
	// Declaración de variables de la función.

	for (unsigned int i = 0; i < tamano_biblioteca; i++)  // Bucle que recorre la librería calculando cosas.
	{
		// Calculo del espaciado del título.
		nuevo_espaciado_titulo = biblioteca[i].titulo.size();
		if (nuevo_espaciado_titulo > espaciado_titulo)
		{
			espaciado_titulo = nuevo_espaciado_titulo;
		}
		// Calculo del espaciado del título.

		// Calculo del espaciado del ISBN.
		nuevo_espaciado_isbn = biblioteca[i].isbn.size();
		if (nuevo_espaciado_isbn > espaciado_titulo)
		{
			espaciado_isbn = nuevo_espaciado_isbn;
		}
		// Calculo del espaciado del ISBN.

		// Calculo del numero de libros en verde y en rojo.
		if (biblioteca[i].prestados == biblioteca[i].ejemplares)
		{
			libros_verdes++;
		}
		else
		{
			libros_rojos++;
		}
		// Calculo del numero de libros en verde y en rojo.
	}

	espaciado_titulo += 2;
	espaciado_isbn   += 2;
	num_estrellas = (38 + to_string(libros_verdes).size()+ 45 +to_string(libros_rojos).size()) / 2; // Calculo de las estrellitas que se necesitan.

	system("CLS"); // Borrado de la pantalla.
	cout << left << endl; // Alineación a la izquierda.
	cout << " " << red << "Datos del libro" << reset << endl; // Título

	cout << green << Estrellitas(num_estrellas) << reset << endl;

	cout << " Libros encontrados: "<< tamano_biblioteca << reset << endl; // Libros totales.
	cout << " Libros con ejemplares para prestar: " << libros_verdes << " Libros con todos los ejemplares prestados: " << libros_rojos << endl; // Libros.
	
	cout << green << Estrellitas(num_estrellas) << reset << endl;

	for (unsigned int i = 0; i < tamano_biblioteca; i++) // Bucle para visualizar los títulos e ISBN de los libros que contenga la biblioteca.
	{
		if (biblioteca[i].prestados == biblioteca[i].ejemplares) // Libros en rojo.
		{
			cout << " Titulo :  " << setw(espaciado_titulo) << red << biblioteca[i].titulo << reset;
			cout << " ISBN   :  " << setw(espaciado_isbn) << red << biblioteca[i].isbn << reset << endl;
		}
		else // Libros en verde.
		{
			cout << " Titulo :  " << setw(espaciado_titulo) << green << biblioteca[i].titulo << reset;
			cout << " ISBN   :  " << setw(espaciado_isbn) << green << biblioteca[i].isbn << reset << endl;
		}
	}
	cout << green << Estrellitas(num_estrellas) << reset << endl;

	cout << endl;
	system("PAUSE");
}

/*!
 * 
 * Función que me pareció util para facilitarme la vida a la hora de hacer lineas de estrellitas "dinámicas";
 * 
 * \param	num Número de estrellas a printar.
 * 
 * \return  ESTRELLITAAAAAS (cadena de texto conteniendo " *" las veces que haga falta).
 */
string Estrellitas(unsigned int num)
{
	string estrellas = "";
	for (unsigned int i = 0; i <num; i++)
	{
		 estrellas += " *";
	}
	return estrellas;
}

// Fin funciones de muestra de datos

// Inicio funciones recogida de datos del usuario.

//!< \brief Función Visualización Menú.
/*!
 * 
 * Funcion para la visualización de los menús haciendo uso de el tipo de dato Menu con la posibilidad de añadir un título.
 * 
 * \param titulo   Titulo del menú.
 * \param menu     Menu a visualizar.
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
void anadirLibro(vector<Libro>& biblioteca)
{
	Libro nuevo_libro; // Nuevo libro.
	system("CLS");     // Limpiar la pantalla.

	cout << "Titulo: ";				    // Introducción del título.
	getline(cin, nuevo_libro.titulo);   // Introducción del título.  
									    
	cout << "Autor: ";				    // Introducción de autor.
	getline(cin, nuevo_libro.autor);    // Introducción de autor.
									    
	cout << "Genero: ";				    // Introducción del género del libro.
	getline(cin, nuevo_libro.genero);   // Introducción del género del libro.
									    
	cout << "ISBN: ";				    // Introducción del ISBN.
	getline(cin, nuevo_libro.isbn);     // Introducción del ISBN.
									    
	cout << "Anyo de edicion: ";	    // Introducción del año de edición.
	cin >> nuevo_libro.fecha.anyo;      // Introducción del año de edición.
									    
	cout << "Numero de paginas: ";      // Introducción número de páginas.
	cin >> nuevo_libro.paginas;		    // Introducción número de páginas.
									    
	cout << "Numero de ejemplares: ";   // Introducción numero de ejemplares.
	cin >> nuevo_libro.ejemplares;	    // Introducción numero de ejemplares.
	
	cin.ignore(); // Uso del cin ignore para eliminar el salto de línea y el retorno de carro.

	biblioteca.push_back(nuevo_libro);  
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

/*!
 * 
 * Función para la escritura de vectores bidimensionales en archivos.
 * 
 * \param bi_vector       Vector bidimensional a escribir.
 * \param nombre_archivo  Nombre ( o ruta completa + nombre) del archivo al que se pretende escribir.
 * \param delimitador     Delimitador deseado para la escritura del archivo. (ej: ; , . )
 * \return                Boleando indicando si se ha podido realizar correctamente la apertura del archivo.
 */
bool EscribirCsv(vector<vector<string>>& bi_vector, const string& nombre_archivo, char delimitador)
{
	// Variables internas de la función.
	bool archivo_abierto = true;
	fstream archivo;
	// Variables internas de la función.

	archivo.open(nombre_archivo, ios::out); // Abrir el archivo correspondiente como escritura.

	if(archivo) // Comprobación archivo abierto
	{
		// Escritura del fichero.
		for (unsigned int i = 0; i < bi_vector.size(); i++) // Iteración primera dimensión del vector.
		{
			for (unsigned int j = 0; j < bi_vector[i].size(); j++) // Iteración segunda dimensión del vector.
			{
				archivo << bi_vector[i][j] << delimitador; // Escritura de la posición del vector en el archivo  con la separación especificada en el delimitador.
			}

			archivo << endl;
		}
		// Escritura del fichero.

		archivo.close(); // Cierre del fichero.
	}
	else
	{
		archivo_abierto = false;
	}
	return archivo_abierto;
}


// Fin funciones de interacción con archivos.

// Inicio funciones procesado de datos.

/*!
 * .
 * 
 * \param [IN]bi_vector    Vector bidimensional conteniendo la información del archivo. (leida con la función LeerCsv)
 * \param [OUT]biblioteca  Vector de Libros, destinatario del contenido procesado por la función.
 */
void BVectorToBiblioteca(const vector<vector<string>>& bi_vector, vector<Libro>& biblioteca)
{
	for (unsigned int i = 0; i < bi_vector.size(); i++)
	{
		if (!bi_vector[i].empty())
		{
			Libro nuevo_libro;
			if (!bi_vector[i][1].empty()) nuevo_libro.titulo		=      bi_vector[i][0];
			if (!bi_vector[i][2].empty()) nuevo_libro.autor			=      bi_vector[i][1];
			if (!bi_vector[i][3].empty()) nuevo_libro.genero		=      bi_vector[i][2];
			if (!bi_vector[i][4].empty()) nuevo_libro.isbn			=      bi_vector[i][3];
			if (!bi_vector[i][4].empty()) nuevo_libro.fecha.anyo	= stoi(bi_vector[i][4]);
			if (!bi_vector[i][7].empty()) nuevo_libro.paginas		= stoi(bi_vector[i][5]);
			if (!bi_vector[i][7].empty()) nuevo_libro.ejemplares	= stoi(bi_vector[i][6]);
			if (!bi_vector[i][7].empty()) nuevo_libro.prestados		= stoi(bi_vector[i][7]);
			biblioteca.push_back(nuevo_libro);
		}
	}
}

/*!
 * Función para convertir el vector biblioteca en un vector bidimensional para guardarlo en un archivo.
 * 
 * \param biblioteca Vector conteniendo toda la información de los libros.
 * \param bi_vector  vector bidimensional al que se guardará la información.
 */
void BibliotecaToBVector(const vector<Libro>& biblioteca, vector<vector<string>>& bi_vector)
{
	vector<string> data; // Vector auxiliar.

	for (unsigned int i = 0; i < biblioteca.size(); i++)     // Bucle para iterar todo el vector
	{	
		data.push_back(          biblioteca[i].titulo     ); // construcción de la primera dimensión del vector.
		data.push_back(          biblioteca[i].autor	  ); // construcción de la primera dimensión del vector.
		data.push_back(          biblioteca[i].genero     ); // construcción de la primera dimensión del vector.
		data.push_back(          biblioteca[i].isbn 	  ); // construcción de la primera dimensión del vector.
		data.push_back(to_string(biblioteca[i].fecha.anyo)); // construcción de la primera dimensión del vector.
		data.push_back(to_string(biblioteca[i].paginas   )); // construcción de la primera dimensión del vector.
		data.push_back(to_string(biblioteca[i].ejemplares)); // construcción de la primera dimensión del vector.
		data.push_back(to_string(biblioteca[i].prestados )); // construcción de la primera dimensión del vector.

		bi_vector.push_back(data); // Concatenación del vector en un vector bidimensional.

		data.clear(); // Borrado de los datos de la "linea" para poder reutilizarla.
	}
}


/*!
 * Función para determinar si el libro existe en base al isbn.
 * 
 * \param  biblioteca Biblioteca conteniendo el conjunto de libros.
 * \param  isbn       ISBN del libro a que se desea saber si existe.
 * \return true si el libro existe o false si no.
 */
bool IsbnExist(const vector<Libro>& biblioteca, const string& isbn, int posicion)
{
	bool existe = false; // Boleano que indica si el libro ha sido encontrado.

	for (unsigned int i = 0; i < biblioteca.size() && !existe; i++) // Bucle que recorre el vector biblioteca hasta que encuentra el libro o bien este se acaba.
	{
		if (biblioteca[i].isbn == isbn) // Condición para que el libro exista.
		{
			existe = true;
			posicion = i;
		}
	}
	return existe;
}

// Fin funciones procesado de datos.








