#ifndef _PEDIDO_HPP_
#define _PEDIDO_HPP_

//Inclusión de librerias y cabeceras
#include "tarjeta.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

//Declaraciones adelantadas
class Tarjeta;
class Pedido_Articulo;
class Usuario_Pedido;

class Pedido{
    public:
        Pedido(Usuario_Pedido& ,Pedido_Articulo&,Usuario& ,const Tarjeta& ,const Fecha& f=Fecha());
        
        //Observadores de la clase
        unsigned numero()const noexcept {return num_pedido_;}
        const Tarjeta* tarjeta()const noexcept{return tarjeta_pago_;}
        const Fecha& fecha()const noexcept{return f_pedido_;}
        double total()const noexcept{return importe_Total_;}
        static unsigned n_total_pedidos() noexcept{return n_pedidos_;}

        //clase de la excepcion vacio
        class Vacio{
            Usuario* user_;
            public:
                Vacio(Usuario* user):user_(user){}
                const Usuario& usuario()const{return *user_;}
        };

        //clase de la excepción Impostor
        class Impostor{
            Usuario* user_;
            public:
                Impostor(Usuario* user):user_(user){}
                const Usuario& usuario()const{return *user_;}
        };

        //clase de la excepción SinStock
        class SinStock{
            Articulo* articulo_;
            public:
                SinStock(Articulo* articulo):articulo_(articulo){}
                const Articulo& articulo()const{return *articulo_;}
        };

    private:
        unsigned num_pedido_;
        const Tarjeta* tarjeta_pago_;
        Fecha f_pedido_;
        double importe_Total_;
        static unsigned n_pedidos_;
};

//Sobrecarga del operador de flujo
std::ostream& operator <<(std::ostream& ,const Pedido& )noexcept;

#endif //!PEDIDO.HPP