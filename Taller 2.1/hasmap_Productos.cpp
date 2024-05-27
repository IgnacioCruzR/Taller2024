#include "hasmap_Productos.h"
#include <iostream>
#include "Cliente.h"

hasmap_Productos::hasmap_Productos():
    tamanoTabla(10), cantidadElementos(0) {
    // Inicializar la tabla con el tamaño predeterminado
    
    tabla = new Nodo_Categoria * [tamanoTabla];
    
    for (int i = 0; i < tamanoTabla; ++i) {
        tabla[i] = nullptr;
    }
}

int hasmap_Productos::funcionHash() {
    int actual = cantidadElementos;
    return actual;
}

hasmap_Productos::~hasmap_Productos() {}

void agregarproductos(Nodo_SubCategoria* subCategoria,const std::string nombreMedicamento, int valorMedicamento) {
    Producto* ListProductos = subCategoria->getListaProductos();
    Producto* nuevoProducto = new Producto(nombreMedicamento, valorMedicamento,1);
    if (ListProductos != nullptr) {
        while (ListProductos != nullptr) {

            if (ListProductos->getNombreProducto() == nombreMedicamento) {
                ListProductos->sumarProducto();
                break;
            }
            else if (ListProductos->getSiguiente() == nullptr) {
                ListProductos->setSiguiente(nuevoProducto);
                break;
            }
            ListProductos = ListProductos->getSiguiente();
        }
    }
else if (ListProductos == nullptr) {
        subCategoria->setListaProductos(nuevoProducto);
    }
    
};

void hasmap_Productos::ingresar_categoria(const std::string Categoria, 
    const std::string subcategoria,const std::string nombreMedicamento,int valorMedicamento)
{
    // creamos el nodo para subcategoria
    Nodo_SubCategoria* subcate = new Nodo_SubCategoria(subcategoria);
    int indice = 0;
    for (int i = 0; i < tamanoTabla; i++) {
        indice = i;
        Nodo_Categoria* actual = tabla[indice];
       if (actual != nullptr) {
            if (actual->nombreCategoria == Categoria) {
                Nodo_SubCategoria* actualsub = actual->ListaSubCategoria;
                if (actualsub == nullptr) {
                    actualsub = subcate;
                }
                else {
                    while (actualsub != nullptr) {
                        if (actualsub->nombreSubCategoria == subcate->nombreSubCategoria) {
                            agregarproductos(actualsub, nombreMedicamento, valorMedicamento);
                            break;

                        }
                        else if (actualsub->siguiente == nullptr) {
                            agregarproductos(subcate, nombreMedicamento, valorMedicamento);
                            actualsub->siguiente = subcate;
                            break;
                        }

                        actualsub = actualsub->siguiente;
                    }
                }
                return;
            }
       }
       else {
           break;
       }
    }

    // Si no hay nodos con la misma clave, agregar al principio de la lista
    Nodo_Categoria* nuevoNodo = new Nodo_Categoria(Categoria);
    tabla[indice] = nuevoNodo;
    nuevoNodo->ListaSubCategoria = subcate;
    agregarproductos(subcate, nombreMedicamento, valorMedicamento);
    //std::cout << subcate->nombreSubCategoria <<std::endl;
    cantidadElementos++;

    // Redimensionar la tabla si la carga excede el factor de carga
    if (cantidadElementos > tamanoTabla * 0.75) {
        redimensionarTabla();
    }
}

void hasmap_Productos::redimensionarTabla() {
    int nuevoTamano = tamanoTabla * 2; // se duplica el tamaño
    Nodo_Categoria** nuevaTabla = new Nodo_Categoria * [nuevoTamano];
    for (int i = 0; i < nuevoTamano; ++i) {
        nuevaTabla[i] = nullptr;
    }

    // Reasignar los nodos a la nueva tabla
    for (int i = 0; i < tamanoTabla; ++i) {
        Nodo_Categoria* actual = tabla[i];
        nuevaTabla[i] = actual;
    }

    // Liberar la memoria de la tabla antigua y actualizar el tamaño
    delete[] tabla;
    tabla = nuevaTabla;
    tamanoTabla = nuevoTamano;
}

void hasmap_Productos::printSoloCategorias()
{
    std::cout << "**** Categorias ****" << std::endl;
    for (int i = 0; i < tamanoTabla; i++) {
        if (tabla[i] != nullptr) {
            std::cout << i+1 << ") " << " - " << tabla[i]->nombreCategoria << std::endl;
        }
        else {
            break;
        }
    }
}
int hasmap_Productos::getCantidad() const
{
    return cantidadElementos;
}

void hasmap_Productos::mostrarCategorias() const {
    std::cout << "Contenido de las Categorias :" << std::endl;
    std::cout << "----------------------" << std::endl;
    for (int i = 0; i < tamanoTabla; ++i) {
        Nodo_Categoria* actual = tabla[i];

        if (actual != nullptr) {
            std::cout << "- Categoria: " << actual->nombreCategoria << ":" << std::endl;
            Nodo_SubCategoria* subCate = actual->ListaSubCategoria;
            while (subCate != nullptr ) {
                std::cout << "   -   Subcategoria: " << subCate->nombreSubCategoria << std::endl;
                Producto* ListaP = subCate->ListaProductos;
                while (ListaP != nullptr) {
                    std::cout << "      -      Producto:  " << ListaP->getNombreProducto() << " Cantidad: " << ListaP->getCantidad() << std::endl;
                    ListaP = ListaP->getSiguiente();
                }
                subCate = subCate->siguiente;
            }
            actual = actual->siguiente;
        }
        else {
            break;
        }
    }
}

Nodo_Categoria* hasmap_Productos::buscarCategoria(std::string clave){
    for (int i = 0; i < tamanoTabla; i++) {
        Nodo_Categoria* actual = tabla[i];
        if (actual != nullptr) {
            if (actual->nombreCategoria == clave) {
                return actual;
            }

        }
        else {
            break;
        }
    }
    return nullptr;
}

Nodo_Categoria* hasmap_Productos::obtenerCategoria(int lugar)
{
    return tabla[lugar-1];
}

Nodo_SubCategoria* hasmap_Productos::obtenerSubcategoria(Nodo_Categoria* categoria, int lugar)
{
    Nodo_SubCategoria* subcategoria = categoria->ListaSubCategoria;
    int i = 0;
    while (i > lugar - 1) {
        subcategoria = subcategoria->siguiente;
    }
   
    return subcategoria;
}

void hasmap_Productos::mostrarProductos(Nodo_SubCategoria* subcategoria)
{
    std::cout << " **** Productos **** " << std::endl;
    Producto* produ = subcategoria->getListaProductos();
    int i = 1;
    while (produ != nullptr) {
        std::cout << i << ") " << produ->getNombreProducto() << std::endl;
        produ = produ->getSiguiente();
        i++;
    }
}

Producto* hasmap_Productos::obtenerProducto(Nodo_SubCategoria* subcate, int lugar)
{
    Producto* subcategoria = subcate->getListaProductos();
    int i = 0;
    while (i > lugar - 1) {
        subcategoria = subcategoria->getSiguiente();
    }

    return subcategoria;
}

void hasmap_Productos::generarBoleta(hasmap_Productos boleta) const
{
    std::cout << " ***** Boleta *****" << std::endl;
    
    int valorT;
    for (int i = 0; i < boleta.getCantidad() ; i++) {
        Nodo_Categoria* actual = boleta.obtenerCategoria(i);
        Nodo_SubCategoria* subcate = actual->ListaSubCategoria;
        Producto* produ = subcate->ListaProductos;
        
        
        while (produ != nullptr) {
            int cant = produ->getCantidad();
            int valor = produ->getCantidad();
            int coste = valor * cant;
            std::cout << cant << "X" << valor << "  " << produ->getNombreProducto() << "  " <<
                coste << std::endl;

            produ = produ->getSiguiente();
        }
    }
}

void hasmap_Productos::EliminarProducto(Nodo_Categoria* categoria,Nodo_SubCategoria* subcategoria,Producto* produ)
{   
    produ->setCantidad(produ->getCantidad() - 1);
    int cant = produ->getCantidad();
    if (cant == 0) {
        // Encontrar y eliminar el producto de la lista de productos de la subcategoría
        Producto* prev = nullptr;
        Producto* current = subcategoria->getListaProductos();
        while (current != nullptr) {
            if (current->getNombreProducto() == produ->getNombreProducto()) {
                if (prev == nullptr) {
                    // El producto a eliminar es el primero de la lista
                    subcategoria->setListaProductos(current->getSiguiente());
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

        // Si la subcategoría ya no tiene productos, considerar eliminar la subcategoría
        if (subcategoria->getListaProductos() == nullptr) {
            Nodo_SubCategoria* prevSub = nullptr;
            Nodo_SubCategoria* currentSub = categoria->ListaSubCategoria;
            while (currentSub != nullptr) {
                if (currentSub->nombreSubCategoria == subcategoria->nombreSubCategoria) {
                    if (prevSub == nullptr) {
                        // La subcategoría a eliminar es la primera de la lista
                        categoria->ListaSubCategoria = currentSub->siguiente;
                    }
                    else {
                        // La subcategoría a eliminar está en medio o al final de la lista
                        prevSub->siguiente = currentSub->siguiente;
                    }
                    delete currentSub; // Liberar la memoria de la subcategoría eliminada
                    break;
                }
                prevSub = currentSub;
                currentSub = currentSub->siguiente;
            }
        }
    }
    // Si la subcategoría ya no tiene productos, eliminar la subcategoría
    if (subcategoria->getListaProductos() == nullptr) {
        Nodo_SubCategoria* prevSub = nullptr;
        Nodo_SubCategoria* currentSub = categoria->ListaSubCategoria;
        while (currentSub != nullptr) {
            if (currentSub->nombreSubCategoria == subcategoria->nombreSubCategoria) {
                if (prevSub == nullptr) {
                    // La subcategoría a eliminar es la primera de la lista
                    categoria->ListaSubCategoria = currentSub->siguiente;
                }
                else {
                    // La subcategoría a eliminar está en medio o al final de la lista
                    prevSub->siguiente = currentSub->siguiente;
                }
                delete currentSub; // Liberar la memoria de la subcategoría eliminada
                break;
            }
            prevSub = currentSub;
            currentSub = currentSub->siguiente;
        }

        // Si la categoría ya no tiene subcategorías, eliminar la categoría
        if (categoria->ListaSubCategoria == nullptr) {
            int indice = -1;
            for (int i = 0; i < tamanoTabla; ++i) {
                if (tabla[i] == categoria) {
                    indice = i;
                    break;
                }
            }
            if (indice != -1) {
                delete tabla[indice]; // Liberar la memoria de la categoría eliminada
                tabla[indice] = nullptr;

                // Reajustar el array para llenar el hueco dejado por la categoría eliminada
                for (int i = indice; i < tamanoTabla - 1; ++i) {
                    tabla[i] = tabla[i + 1];
                }
                tabla[tamanoTabla - 1] = nullptr;
                cantidadElementos--;
            }
        }
    }
    
}

void Nodo_SubCategoria::setListaProductos(Producto* producto)
{
    ListaProductos = producto;
}

void hasmap_Productos::printSubCategorias(Nodo_Categoria* categoria) {
    std::cout << " **** Sub Categorias **** " << std::endl;
    Nodo_SubCategoria* subcategoria = categoria->ListaSubCategoria;
    int i = 1;
    while (subcategoria != nullptr) {
        std::cout << i << ") " << subcategoria->nombreSubCategoria << std::endl;
        subcategoria = subcategoria->siguiente;
        i++;
    }

}

Producto* Nodo_SubCategoria::getListaProductos()
{
    return ListaProductos;
}
