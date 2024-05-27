#ifndef CLIENTE_H
#define CLIENTE_H
#include <string>
#include "Producto.h"

class Cliente {
private:
    std::string rut;
    std::string discapacidad;
    std::string tipoDiscapacidad;
    std::string Numero;
    Producto* producto;
    

public:
    // Constructor
    Cliente(std::string rut, std::string discapacidad, std::string tipoDiscapacidad, std::string numero);

    // Getters
    std::string getRut() const;
    std::string tieneDiscapacidad() const;
    std::string getTipoDiscapacidad() const;
    std::string getNumero() const;
    Producto* getProducto();

    // Setters
    void setRut(std::string rut);
    void setDiscapacidad(std::string discapacidad);
    void setTipoDiscapacidad(std::string tipoDiscapacidad);
    void setNumero(std::string numero );

    void ingresarProducto(std::string nombreP, int valor);
    void generarBoleta();
    void eliminarProducto(int lugar);
    Producto* buscarProducto(int lugar);
};

#endif