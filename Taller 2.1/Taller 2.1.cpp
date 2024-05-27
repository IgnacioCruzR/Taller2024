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

void escribirArchivosDesdeHashMap(hasmap_Productos map, const string& nombreArchivoProductos) {
	// Abrir el archivo de productos en modo escritura
	ofstream archivoProductos(nombreArchivoProductos);

	if (!archivoProductos) {
		cerr << "Error al abrir el archivo de productos." << endl;
		return;
	}

	// Escribir el contenido en los archivos de productos y clientes(archivoProductos<< lo que quieras <<","<< lo que quieras << endl;
	//Productos
	for (int i = 0; i < map.getCantidad(); i++) {
		Nodo_Categoria* catN = map.obtenerCategoria(i);
		Nodo_SubCategoria* actual = catN->ListaSubCategoria;
		while (actual->siguiente != nullptr) {
			Producto* actualP = actual->getListaProductos();
			while (actualP->getSiguiente() != nullptr) {
				archivoProductos << catN->nombreCategoria << "," << actual->nombreSubCategoria << "," << actualP->getNombreProducto() << "," << actualP->getValorProducto() << endl;
			}


		}

	}


	// Cerrar los archivos
	archivoProductos.close();

	cout << "Se ha escrito el contenido en los archivos de productos y clientes." << endl;
}

Cliente* agergarProductoCarrito(Cliente* actual , hasmap_Productos hashmapProductos) {
	
	hashmapProductos.printSoloCategorias();
	int opcion;
	cout << "Opcion: "; cin >> opcion;
	Nodo_Categoria* categoria = hashmapProductos.obtenerCategoria(opcion);
	hashmapProductos.printSubCategorias(categoria);
	int opcionS;
	cout << "Opcion: "; cin >> opcionS;
	Nodo_SubCategoria* subcategoria = hashmapProductos.obtenerSubcategoria(categoria, opcionS);
	hashmapProductos.mostrarProductos(subcategoria);
	int opcionP;
	cout << "Opcion: "; cin >> opcionP;
	Producto* produ = hashmapProductos.obtenerProducto(subcategoria, opcionP);
	cout << "---- agregando al carrito ----" << endl;
	actual->ingresarProducto(produ->getNombreProducto(), produ->getValorProducto());
	cout << "------------------------------" << endl;
	cout << "---- Agregado al carrito ----" << endl;
	hashmapProductos.EliminarProducto(categoria, subcategoria, produ);
	return actual;
}

hasmap_Productos agergarProducto(hasmap_Productos hashmapProductos) {
	cout << "**** Agregar Producto ****" << endl;
	string categria, subcate, producto;
	int valor;
	cout << "Categoria: "; cin >> categria;
	cout << "Sub Categoria: "; cin >> subcate;
	cout << "Producto: "; cin >> producto;
	cout << "Valor: "; cin >> valor;
	cout << "---- Agregando Producto ----" << endl;
	cout << "----------------------------" << endl;
	hashmapProductos.ingresar_categoria(categria,subcate,producto,valor);
	cout << "---- Producto Agregado ----" << endl;
	return hashmapProductos;
}

hasmap_Productos EliminarProductos(hasmap_Productos hashmapProductos) {
	hashmapProductos.printSoloCategorias();
	int opcion;
	cout << "Opcion: "; cin >> opcion;
	Nodo_Categoria* categoria = hashmapProductos.obtenerCategoria(opcion);
	hashmapProductos.printSubCategorias(categoria);
	int opcionS;
	cout << "Opcion: "; cin >> opcionS;
	Nodo_SubCategoria* subcategoria = hashmapProductos.obtenerSubcategoria(categoria,opcionS);
	hashmapProductos.mostrarProductos(subcategoria);
	int opcionP;
	cout << "Opcion: "; cin >> opcionP;
	Producto* produ = hashmapProductos.obtenerProducto(subcategoria,opcionP);
	cout << "---Eliminando Producto---" << endl;
	cout << "-------------------------" << endl;
	hashmapProductos.EliminarProducto(categoria,subcategoria,produ);
	cout << "---Producto Eliminado---" << endl;
	return hashmapProductos;
}

hasmap_Productos menubodega(hasmap_Productos hashmapProductos) {
	while (true) {
		cout << " **** Menu Bodega ****" << endl;
		cout << "1) Agregar Producto" << endl;
		cout << "2) Eliminar producto" << endl;
		cout << "3) ver inventario" << endl;
		cout << "4) salir menu bodega" << endl;
		int opcion;
		cout << "Opcion: "; cin >> opcion;
		
		switch (opcion)
		{
		case 1:
			hashmapProductos = agergarProducto(hashmapProductos);
			break;
		case 2:
			hashmapProductos = EliminarProductos(hashmapProductos);
			break;
		case 3:
			hashmapProductos.mostrarCategorias();
			break;
		case 4:
			return hashmapProductos;
			break;
		}
	}
	
}

queue<Cliente*> ordenarClientes(queue<Cliente*> ListaClientes) {
	queue<Cliente*> ListaTerceraEdad, ListaEmbarazadas, ListaDiscapacitados;
	queue<Cliente*> ListaSinDiscapacidad;
	while (ListaClientes.size() > 0) {

		string TieneDiscapacidad = ListaClientes.front()->tieneDiscapacidad();

		if (TieneDiscapacidad == "Si") {
			string tipo = ListaClientes.front()->getTipoDiscapacidad();
			// vamos a rellenar las listas para darles distintas
			//  preferencias al moento de volver a rellenar la lista ordenada 
			if (tipo == "Tercera Edad") {
				ListaTerceraEdad.push(ListaClientes.front());
				//cout << ListaClientes.front()->getTipoDiscapacidad() << endl;
			}
			else if (tipo == "Embarazada") {
				ListaEmbarazadas.push(ListaClientes.front());
				//cout << ListaClientes.front()->getTipoDiscapacidad() << endl;

			}
			else if (tipo == "Discapacitado") {
				ListaDiscapacitados.push(ListaClientes.front());
				//cout << ListaClientes.front()->getTipoDiscapacidad() << endl;
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
	// ver si esta ordenada la nueva lisa de los clientes
	/*
	queue<Cliente*> Lista_Clientes = ListaClientes;
	while (Lista_Clientes.size() > 0) {
		cout << Lista_Clientes.size() << ") " << endl;
		cout << Lista_Clientes.front()->getRut() << " -> ";
		cout << Lista_Clientes.front()->getTipoDiscapacidad() << " Lugar: ";
		cout << Lista_Clientes.front()->getNumero() <<  endl;


		Lista_Clientes.pop();

	}
	*/
	return ListaClientes;

}

string obtenerNumero(queue<Cliente*>ListaClientes, string tipoD) {
	int numeros = 1;
	queue<Cliente*> Lista_Cliente = ListaClientes;
	while (Lista_Cliente.size() > 0) {
		if (Lista_Cliente.front()->getTipoDiscapacidad() == tipoD) {
			numeros++;
		}

		Lista_Cliente.pop();
	}
	string numero, lugar;
	if (tipoD == "Tercera Edad") {
		lugar = to_string(numeros % 100);
		numero = " A - " + lugar;
	}
	else if (tipoD == "Embarazada") {
		lugar = to_string(numeros % 100);
		numero = " E - " + lugar;
	}
	else if (tipoD == "Discapacitado") {
		lugar = to_string(numeros % 100);
		numero = " D - " + lugar;
	}
	return numero;
}

queue<Cliente*> ingresarC(queue<Cliente*> ListaClientes) {
	cout << " **** Ingresando Cliente ****" << endl;
	cout << endl;
	string rut , tieneD , tipoD; // D = Discapacidad
	cout << "rut : "; cin >> rut;
	cout << "Tiene discapacidad: "; cin >> tieneD;
	
	if (tieneD == "Si") {
		string lista[] = {"Tercera Edad", "Embarazada", "Discapacitado"};
		int opcion;
		cout << "1) Tercera Edad" << endl << "2) Embarazada" << endl << "3) discapacitado" << endl;
		cout << "opcion: ";  cin >> opcion;
		tipoD = lista[opcion - 1];
		
	}
	else {
		tipoD = "No tiene discapacidad";
	}
	string numero = obtenerNumero(ListaClientes , tipoD);
	Cliente* c = new Cliente(rut,tieneD,tipoD,numero);
	ListaClientes.push(c);
	ListaClientes = ordenarClientes(ListaClientes);
	return ListaClientes;
}

void generarventa(Cliente* clienteActual) {
	clienteActual->generarBoleta();
}

Cliente* EliminarProductoCarrito(Cliente* ClienteActual) {
	Producto* produ = ClienteActual->getProducto();
	int i = 1;
	while (produ != nullptr) {
		cout << i << ") " << produ->getNombreProducto() << endl;

		produ = produ->getSiguiente();
	}
	return ClienteActual;
}

void vercarro(Cliente* clienteActual) {
	Producto* produ = clienteActual->getProducto();
	cout << "**** Carrito ****" << endl;
	while (produ != nullptr) {
		cout << produ->getNombreProducto() << "  -  " << produ->getCantidad() << "X" << produ->getValorProducto() 
			<< "   -   " << produ->getCantidad()*produ->getValorProducto() << endl;
		produ = produ->getSiguiente();
	}
}

void menu(hasmap_Productos hashmapProductos, queue<Cliente*> ListaClientes) {
	Cliente* clienteActual = nullptr; string linea_;

	while (true) {
		cout << "**** menu ****" << endl;
		// opciones
		int opcion;

		cout << "1) Ingresar cliente" << endl;
		cout << "2) Llamar siguinte cliente" << endl;
		cout << "3) carrito del cliente (agregar, cancelar, ver productos)" << endl;
		cout << "4) cancelar venta cliente actual" << endl;
		cout << "5) generar boleta" << endl;
		cout << "6) ingresar bodega" << endl;
		cout << "7) salir" << endl;
		cout << "opcion: "; cin >> opcion;
		cout << "-----------------------------------" << endl;

		switch (opcion)
		{
		case 1:
			ListaClientes = ingresarC(ListaClientes);
			break;
		case 2:
			if (clienteActual == nullptr) {
				clienteActual = ListaClientes.front();
				cout << "Numero: " << clienteActual->getNumero() << endl;
			}
			else {
				cout << "Ya se esta atendiendo a un cliente." << endl;
				cout << "En caso de que no llego o cancelo oprimir 4 en menu" << endl;
			}
			break;
		case 3:
			cout << " **** Carrito ****" << endl;
			cout << "1) Agregar" << endl;
			cout << "2) Eliminar" << endl;
			cout << "3) ver carrito" << endl;
			int opcion2;
			cout << "Opcion: "; cin >> opcion2;
			if (opcion2 == 1) {
				cout << "**** Agregando producto al carrito ****" << endl;
				agergarProductoCarrito(clienteActual, hashmapProductos);
			}
			else if (opcion2 == 2) {
				EliminarProductoCarrito(clienteActual);
			}
			else if (opcion2 == 3) {
				vercarro(clienteActual);
			}
			else {
				cout << "Por favor ingresar una opcion valida" << endl;
			}
			break;
		case 4:
			if (clienteActual == nullptr) {
				cout << "No se encuentra a ningun cliente actual" << endl;
				cout << "Por favor llamar al siguiente cliente con oprimir 2 en el menu." << endl;
			}
			else {
				cout << "Cancelando venta actual." << endl;
				ListaClientes.pop();
				clienteActual = nullptr;
			}
			break;
		case 5:
			if (clienteActual != nullptr) {
				generarventa(clienteActual);
				ListaClientes.pop();
				clienteActual = nullptr;
			}
			break;
		case 6:
			hashmapProductos = menubodega(hashmapProductos);
			break;
		case 7:
			// guardar y salir
			escribirArchivosDesdeHashMap(hashmapProductos,"Productos.txt");
			exit(0);
			break;

		default:
			break;
			}
			cout << "-----------------------------------" << endl;
		}
	}

queue<Cliente*> lecturaClientes() {
	queue<Cliente*> ListaCliente;
	ifstream archivo("Clientes.txt");
	if (!archivo.is_open()) {
		cerr << "No se pudo abrir el archivo." << std::endl;
		return ListaCliente;
	}
	int clienteN = 1,clienteA = 1, clienteE = 1, clienteD = 1;
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
		string numero , lugar;
		if (tienediscapacidad == "Si") {
			
			if (TipoDeDiscapacidad == "Tercera Edad") {
				lugar = to_string(clienteA%100);
				numero = " A - " + lugar;
				clienteA++;
			}
			else if(TipoDeDiscapacidad == "Embarazada"){
				lugar = to_string(clienteE % 100);
				numero = " E - " + lugar;
				clienteE++;
			}
			else if (TipoDeDiscapacidad == "Discapacitado") {
				lugar = to_string(clienteD % 100);
				numero = " D - " + lugar;
				clienteD++;
			}
		}
		else {
			lugar = to_string(clienteN % 100);
			numero = " C - " + lugar;
			clienteN++;
		}
		Cliente* cliente = new Cliente(rut, tienediscapacidad, TipoDeDiscapacidad,numero);
		
		
		ListaCliente.push(cliente);
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
		productos.ingresar_categoria(nombreCategoria, nombre_Sub_Categoria
			, nombreProducto, valor);
	}
	archivo.close(); 
	return productos;
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
