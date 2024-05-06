#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

//Inclusión de librerias y cabeceras
#include "pedido.hpp"
#include "articulo.hpp"

//declaraciones adelantadas
Articulo;
Pedido;

//Contendrá LineaPedido
class LineaPedido{
    public:
        explicit LineaPedido(double precio = 0., unsigned cant=1)
            :precio_venta_(precio),cantidad_venta_(cant){}
        //Métodos observadores de la clase
        double precio_venta()const noexcept{return precio_venta_;}
        unsigned cantidad()const noexcept{return cantidad_venta_;}

    private:
        double precio_venta_;
        unsigned cantidad_venta_;
};



//Operador de inserción en flujo de LineaPedido
std::ostream& operator <<(std::ostream& , const LineaPedido&)noexcept;

// El que representa la asociación desde Pedido a Articulo será del tipo
// std::map<Pedido*, ItemsPedido, OrdenaPedidos>, donde ItemsPedido será un
// tipo público de la clase Pedido_Articulo definido como un diccionario
// std::map<Articulo*, LineaPedido, OrdenaArticulos>.
// OrdenaPedidos y OrdenaArticulos serán también tipos públicos definidos como dos
// clases anidadas en Pedido_Articulo. Se trata de dos clases de objetos función para
// ordenar ascendentemente los pedidos y artículos por número y referencia, respec-
// tivamente, dentro de los diccionarios.
// • La asociación en el sentido inverso (desde Articulo a Pedido) se representará por un
// diccionario del tipo std::map<Articulo*, Pedidos, OrdenaArticulos>, donde
// Pedidos será un tipo público de la clase Pedido_Articulo definido como
// std::map<Pedido*, LineaPedido, OrdenaPedidos>.

struct ItemsPedido{

};

struct OrdenaPedidos{
    bool operator()(const Pedido* p1, cosnt Pedido* p2)const;
};

class Pedido_Articulo{
    public:

   

    private:
};

#endif // !PEDIDO_ARTICULO_HPP
