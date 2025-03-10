#include "pedido.hpp"

//Inicializamod la variable static
int Pedido::n_pedidos_ = 0;

//Constructor
Pedido::Pedido(Usuario_Pedido& up,Pedido_Articulo& pa,Usuario& u,
const Tarjeta& t,const Fecha& f):num_(n_pedidos_+1),tarjeta_(&t),f_pedido_(f),importe_Total_(0.0){
    //Vamos a comprobar todas la excepciones del constructor de pedido
    //Si el usuario no tiene una compra realizada, el pedido está vacio
    if(u.compra().empty())
        throw Pedido::Vacio(&u);

    //Si el usuario es otro al que realiza la compra, excepción
    if(t.titular()!=&u)
        throw Pedido::Impostor(&u);

    //Si la tarjeta está caducada o desactivada, excepción
    if(t.caducidad() < f_pedido_)
        throw Tarjeta::Caducada(t.caducidad());

    if(!t.activa()) throw Tarjeta::Desactivada();
    //Si no hay stock del articulo, excepción
    for(auto i : u.compra()){
        if(i.first->stock()<i.second){
            u.vaciar_carro();
            throw Pedido::SinStock(i.first);
        }
    }
    //Creamos la asociación entre las clases una vez que todo está correcto
    /*Asociación Usuario-Pedido*/
    up.asocia(*this,u);
    //actualizamos el importe del pedido y pedimos el articulo
    for(auto& i : u.compra()){
        //importe_Total_ += precio_articulo * cantidad del mismo.
        importe_Total_ += i.first->precio() * i.second;
        pa.pedir((*i.first),*this,i.first->precio(),i.second);

        //restamos el stock del articulo que se ha pedido
        i.first->stock() -= i.second; //sobrecarga del operador -=
    }
    //Aumentamos el numero de pedidos y vaciamos el carro del usuario
    u.vaciar_carro();
    n_pedidos_++;
}

//Insersión en flujo
std::ostream& operator <<(std::ostream& output , const Pedido& ped)noexcept{
    output<<"Núm. pedido: "<<ped.numero()<<std::endl
          <<"Fecha:\t"<<ped.fecha()<<std::endl
          <<"Pagado con: "<<ped.tarjeta()->tipo()<<" n.º: "<<ped.tarjeta()->numero()<<std::endl
          <<"Importe: "<<std::fixed<<std::setprecision(2)<<ped.total()<<" €"<<std::endl;
    return output;
}
