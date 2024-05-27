#include "Cliente.h"
#include <iostream>
#include "hasmap_Productos.h"

// Constructor
Cliente::Cliente(std::string rut, std::string discapacidad, std::string tipoDiscapacidad, std::string numero) {
    this->rut = rut;
    this->discapacidad = discapacidad;
    this->tipoDiscapacidad = tipoDiscapacidad;
    Numero = numero;
    producto = nullptr;
}

// Getters
std::string Cliente::getRut() const {
    return rut;
}

std::string Cliente::tieneDiscapacidad() const {
    return discapacidad;
}

std::string Cliente::getTipoDiscapacidad() const {
    return tipoDiscapacidad;
}

std::string Cliente::getNumero() const
{
    return Numero;
}

Producto* Cliente::getProducto()
{
    return producto;
}

// Setters
void Cliente::setRut(std::string rut) {
    this->rut = rut;
}

void Cliente::setDiscapacidad(std::string discapacidad) {
    this->discapacidad = discapacidad;
}

void Cliente::setTipoDiscapacidad(std::string tipoDiscapacidad) {
    this->tipoDiscapacidad = tipoDiscapacidad;
}

void Cliente::setNumero(std::string numero)
{
    Numero = numero;
}

void Cliente::ingresarProducto(std::string nombreP , int valor)
{
    Producto* P = new Producto(nombreP,valor,1);
    Producto* aux = producto;
    
    if (producto == nullptr ) {
        producto = P;
    }
    
    else {

        while (producto != nullptr) {
            if (producto->getNombreProducto() == P->getNombreProducto()) {
                producto->sumarProducto();
                break;
            }
            if (producto->getSiguiente() == nullptr) {
                producto->setSiguiente(P);
                break;
            }
        
            producto = producto->getSiguiente();
        }
        producto = aux;
    }
}

void Cliente::generarBoleta()
{
    int valorT = 0;
    while (producto != nullptr) {
        std::cout << producto->getNombreProducto() << "  -  " << producto->getCantidad() << "X" << producto->getValorProducto()
            << "   -   " << producto->getCantidad() * producto->getValorProducto() << std::endl;
        valorT += producto->getCantidad() * producto->getValorProducto();
        producto = producto->getSiguiente();
    }
    std::cout << std::endl;
    std::cout << "Valor total de la boleta : " << valorT << std::endl;
    std::cout << std::endl;
}

Producto* Cliente::buscarProducto(int lugar)
{
    Producto* current = producto;
    int index = 0;

    while (current != nullptr) {
        if (index == lugar) {
            return current;
        }
        current = current->getSiguiente();
        index++;
    }

    return nullptr;
}

void Cliente::eliminarProducto(int lugar)
{
    Producto* produ = buscarProducto(lugar);
    if (produ == nullptr) {
        std::cout << "Producto no encontrado." << std::endl;
        return;
    }

    produ->setCantidad(produ->getCantidad() - 1);
    int cant = produ->getCantidad();
    if (cant == 0) {
        // Encontrar y eliminar el producto de la lista de productos
        Producto* prev = nullptr;
        Producto* current = producto;

        while (current != nullptr) {
            if (current == produ) {
                if (prev == nullptr) {
                    // El producto a eliminar es el primero de la lista
                    producto = current->getSiguiente();
                }
                else {
                    // El producto a eliminar está en medio o al final de la lista
                    prev->setSiguiente(current->getSiguiente());
                }
                delete current; // Liberar la memoria del producto eliminado
                break;
            }
            prev = current;
            current = current->getSiguiente();
        }
    }
}
