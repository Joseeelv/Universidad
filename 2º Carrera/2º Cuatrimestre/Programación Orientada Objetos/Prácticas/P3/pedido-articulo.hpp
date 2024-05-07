#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

//Inclusión de librerias y cabeceras
#include "pedido.hpp"
#include "articulo.hpp"

//declaraciones adelantadas
Pedido;
Articulo;

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

struct OrdenaArticulos{
    bool operator () (const Articulo*, const Articulo* )const;
};

struct OrdenaPedidos{
    bool operator()(const Pedido* , const Pedido* )const;
};

class Pedido_Articulo{
    public:
        //Diccionarios
        //ItemsPedido será un tipo público de la clase Pedido_Articulo definido como un diccionario
        //std::map<Articulo*, LineaPedido, OrdenaArticulos>.
        typedef std::map<Articulo*,LineaPedido,OrdenaArticulos>ItemsPedido;
        typedef std::map<Pedido*,ItemsPedido,OrdenaPedidos> PedidoArticulo;
        //Asociacion en sentido inverso
        //Pedidos será un tipo público de la clase Pedido_Articulo definido como
        //std::map<Pedido*, LineaPedido, OrdenaPedidos>.
        typedef std::map<Pedido*,LineaPedido,OrdenaPedidos>Pedidos;
        typedef std::map<Articulo*,Pedidos,OrdenaArticulos> ArticuloPedido;

        //Se hace uso de cosntructores predeterminados

        //Creacion de enlaces
        void pedir(Pedido&,Articulo&,double,unsigned cantidad = 1); //directa
        void pedir(Articulo&,Pedido&,double,unsigned cantidad = 1); //inversa

        //detalle devolverá la colección de artículos de un pedido (que se le pasa,
        // por referencia) junto a su precio de venta y cantidad comprada; o sea, una referencia
        // constante a ItemsPedido
        const ItemsPedido detalle(Pedido& )const;

        //ventas devolverá todos los pedidos de un artículo (que se le pasa, por referencia) con precio
        //de venta y cantidad; o sea, un Pedidos.
        const Pedidos ventas(Articulo& )const;

        //mostrarDetallePedidos imprimirá en el flujo de salida proporcionado
        //el detalle de todos los pedidos realizados hasta la fecha,
        //así como el importe de todas las ventas.
        std::ostream& mostrarDetallesPedidos(std::ostream&)const noexcept;

        //mostrarVentasArticulos visualizará en el flujo de salida proporcionado todas
        //las ventas agrupadas por artículos
        std::ostream& mostrarVentasArticulos(std::ostream&)const noexcept;


    private:
    //Diccionarios de la clase
    PedidoArticulo pedidoarticulo_; //directa
    ArticuloPedido articulopedido_; //inversa
};

//Sobrecarga de los operadores de inserción en flujo
std::ostream& operator << (std::ostream& , const Pedido_Articulo::ItemsPedido&)noexcept;
std::ostream& operator << (std::ostream& , const Pedido_Articulo::Pedidos&) noexcept;
#endif // !PEDIDO_ARTICULO_HPP
