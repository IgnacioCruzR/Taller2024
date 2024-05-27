// Taller 2.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "hasmap_Productos.h"
#include <vector>
#include <queue>
#include "Cliente.h"
using namespace std;

void menu(hasmap_Productos hashmapProductos, queue<Cliente*> ListaClientes) {
	cout << "**** menu ****" << endl;
}

Cliente* ordenarClientes(Cliente* ListaClientes) {
	queue<Cliente*> ListaTerceraEdad, ListaEmbarazadas, ListaDiscapacitados;
	queue<Cliente*> ListaSinDiscapacidad;
	cout << ListaClientes.front() << endl;
	while (ListaClientes.size() > 0) {

		string TieneDiscapacidad = ListaClientes.front()->tieneDiscapacidad();

		if (TieneDiscapacidad == "Si") {
			string tipo = ListaClientes.front()->tieneDiscapacidad();
			// vamos a rellenar las listas para darles distintas
			//  preferencias al moento de volver a rellenar la lista ordenada 
			if (tipo == "Tercera Edad") {
				ListaTerceraEdad.push(ListaClientes.front());
				cout << ListaClientes.front()->tieneDiscapacidad() << endl;
			}
			else if (tipo == "Embarazada") {
				ListaEmbarazadas.push(ListaClientes.front());
			}
			else if (tipo == "Discapacitado") {
				ListaDiscapacitados.push(ListaClientes.front());
			}
		}
		else {
			ListaSinDiscapacidad.push(ListaClientes.front());
		}
		ListaClientes.pop();

	}
	// empezamos a rellenar por orden de preferencia la Lista de los clientes
	while (ListaTerceraEdad.size() > 0) {

		ListaClientes.push(ListaTerceraEdad.front());
		ListaTerceraEdad.pop();

	}
	while (ListaEmbarazadas.size() > 0) {

		ListaClientes.push(ListaEmbarazadas.front());
		ListaEmbarazadas.pop();

	}
	while (ListaDiscapacitados.size() > 0) {

		ListaClientes.push(ListaDiscapacitados.front());
		ListaDiscapacitados.pop();

	}
	while (ListaSinDiscapacidad.size() > 0) {

		ListaClientes.push(ListaSinDiscapacidad.front());
		ListaSinDiscapacidad.pop();

	}
	return ListaClientes;

}

queue<Cliente*> lecturaClientes() {
	queue<Cliente*> ListaCliente;
	ifstream archivo("Clientes.txt");
	if (!archivo.is_open()) {
		cerr << "No se pudo abrir el archivo." << std::endl;
		return ListaCliente;
	}

	string linea;
	while (getline(archivo, linea)) {
		string token; // token para poder obtener el string

		istringstream iss(linea); // llamamos al istingstream para poder separarlo

		vector<string> DatosClientes; // donde vamos a guardar todos los datos del Cliente

		while (getline(iss, token, ',')) { // hacemos todas las separaciones y las guardamos

			DatosClientes.push_back(token);
		}

		string rut = DatosClientes[0];
		string tienediscapacidad = DatosClientes[1];
		string TipoDeDiscapacidad = DatosClientes[2];
		Cliente* clienten = new Cliente(rut,tienediscapacidad,TipoDeDiscapacidad);
		
		ListaCliente.push(clienten);
	}
	archivo.close();
	ListaCliente = ordenarClientes(ListaCliente);
	return ListaCliente;
}

hasmap_Productos lecturaProductos() {
    hasmap_Productos productos;
	ifstream archivo("Productos.txt");
	if (!archivo.is_open()) {
		cerr << "No se pudo abrir el archivo." << std::endl;
		return productos;
	}

	string linea;
	while (getline(archivo, linea)) {
		string token; // token para poder obtener el string

		istringstream iss(linea); // llamamos al istingstream para poder separarlo

		vector<string> DatosProductos; // donde vamos a guardar todos los datos del Cliente

		while (getline(iss, token, ',')) { // hacemos todas las separaciones y las guardamos

			DatosProductos.push_back(token);
		}

		string nombreCategoria = DatosProductos[0];
		string nombre_Sub_Categoria = DatosProductos[1];
		string nombreProducto = DatosProductos[2];
		int valor = stoi(DatosProductos[3]);
		productos.ingresar_categoria(nombreCategoria,nombre_Sub_Categoria
			,nombreProducto,valor);
	}
	archivo.close(); return productos;
}

int main()
{   
    hasmap_Productos hashmapProductos;
    hashmapProductos = lecturaProductos();
	//hashmapProductos.mostrarCategorias();
	queue<Cliente*> ListaClientes = lecturaClientes();
    // empezar el menu
	menu(hashmapProductos, ListaClientes);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
