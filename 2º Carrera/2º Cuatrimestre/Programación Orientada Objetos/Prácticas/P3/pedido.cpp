#include "pedido.hpp"

//Inicializamod la variable static
unsigned n_pedidos_ = 0;

//Constructor
Pedido::Pedido(Usuario_Pedido& up,Pedido_Articulo& pa,Usuario& u,
const Tarjeta& t,const Fecha& f=Fecha()):num_pedido_(n_pedidos_+1),tarjeta_pago_(&t),f_pedido_(f),importe_Total_(0.0){
    //Vamos a comprobar todas la excepciones del constructor de pedido
    //Si el usuario no tiene una compra realizada, el pedido está vacio
    if(u.compra().empty())throw Pedido::Vacio(&u);

    //Si el usuario es otro al que realiza la compra, excepción
    if(t.titular()!=&u)throw Pedido::Impostor(&u);

    //Si la tarjeta está caducada o desactivada, excepción
    if(t.caducidad() < f_pedido_)throw Tarjeta::Caducada(t.caducidad());
    if(!t.activa()) throw Tarjeta::Desactivada();
    //Si no hay stock del articulo, excepción
    for(auto& i : u.compra()){
        if(i.first->stock()<i.second)
        u.vaciar_carro();
        throw Pedido::SinStock(i.first);
    }
}

//Insersión en flujo
std::ostream& operator <<(std::ostream& output , const Pedido& ped)noexcept{
    output<<"Núm. pedido: "<<ped.numero()<<std::endl
          <<"Fecha: "<<ped.fecha()<<std::endl
          <<"Pagado con: "<<ped.tarjeta()<<std::endl
          <<"Importe: "<<std::fixed<<std::setprecision(2)<<ped.total()<<" €";
}
