#pragma once
#include <string>


class Producto
{
private:
    int cantidad;
    std::string nombre_Producto;
    int valor_Producto;
    Producto* siguiente;

public:
    // Constructor
    Producto(const std::string& nombre_Producto, int valor_Producto,int cant);

    // Getters
    std::string getNombreProducto() const;
    int getValorProducto() const;
    Producto* getSiguiente();
    int getCantidad();

    // Setters
    void setNombreProducto(const std::string& nombreProducto);
    void setValorProducto(int valorProducto);
    void setCantidad(int cant);

    // sumar mas productos
    void sumarProducto();
    void setSiguiente(Producto* sig);
};
