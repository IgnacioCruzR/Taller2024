#pragma once
#include <string>
#include "Producto.h"
#include "Cliente.h"
#include <queue>


struct Nodo_SubCategoria {
    std::string nombreSubCategoria;
    Nodo_SubCategoria* siguiente;
    Producto* ListaProductos;
    Nodo_SubCategoria(const std::string subCategoria) : nombreSubCategoria(subCategoria), siguiente(nullptr), ListaProductos(nullptr){}
    void setListaProductos(Producto* producto);
    
    Producto* getListaProductos();
};
struct Nodo_Categoria {
    std::string nombreCategoria;
    Nodo_Categoria* siguiente;
    Nodo_SubCategoria* ListaSubCategoria;
    Nodo_Categoria(const std::string& categoria) : nombreCategoria(categoria), siguiente(nullptr), ListaSubCategoria(nullptr){}
};


class hasmap_Productos
{
private:
   
    Nodo_Categoria** tabla;
    int tamanoTabla;
    int cantidadElementos;

public:

    hasmap_Productos();
    ~hasmap_Productos();

    void redimensionarTabla();
    void ingresar_categoria(const std::string categoria, const std::string subCategoria, const std::string nombreMedicamento, int valorMedicamento);
    int funcionHash();
    
    void printSoloCategorias();
    
    int getCantidad() const;
    
    void mostrarCategorias() const;
    
    Nodo_Categoria* obtenerCategoria(int lugar);
    
    Nodo_SubCategoria* obtenerSubcategoria(Nodo_Categoria* categoria, int lugar);
    
    void printSubCategorias(Nodo_Categoria* categoria);
    
    Nodo_Categoria* buscarCategoria(std::string clave);
    
    void mostrarProductos(Nodo_SubCategoria* subcategoria);
    
    Producto* obtenerProducto(Nodo_SubCategoria* subcate, int lugar);
    
    void EliminarProducto(Nodo_Categoria* categoria, Nodo_SubCategoria* subcategoria, Producto* produ);
    
    void generarBoleta(hasmap_Productos boleta) const; 
};

