#include "Producto.h"

// Constructor
Producto::Producto(const std::string& nombre_Producto, int valor_Producto,int cant)
    : nombre_Producto(nombre_Producto), valor_Producto(valor_Producto), siguiente(nullptr), cantidad(cant) {}


std::string Producto::getNombreProducto() const {
    return nombre_Producto;
}

int Producto::getValorProducto() const {
    return valor_Producto;
}

Producto* Producto::getSiguiente()
{
    return siguiente;
}

int Producto::getCantidad()
{
    return cantidad;
}

// Setters

void Producto::setNombreProducto(const std::string& nombreProducto) {
    this->nombre_Producto = nombreProducto;
}

void Producto::setValorProducto(int valorProducto) {
    this->valor_Producto = valorProducto;
}

void Producto::setCantidad(int cant)
{
    cantidad = cant;
}

void Producto::sumarProducto()
{
    cantidad = cantidad + 1;
}

void Producto::setSiguiente(Producto* sig)
{
    siguiente = sig;
}
