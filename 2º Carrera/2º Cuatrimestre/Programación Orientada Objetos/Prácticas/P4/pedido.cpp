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
    /*-----Práctica 3-----*/
    // //Si no hay stock del articulo, excepción
    // for(auto i : u.compra()){
    //     if(i.first->stock()<i.second){
    //         u.vaciar_carro();
    //         throw Pedido::SinStock(i.first);
    //     }
    // }
    // //Creamos la asociación entre las clases una vez que todo está correcto
    // /*Asociación Usuario-Pedido*/
    // up.asocia(*this,u);
    // //actualizamos el importe del pedido y pedimos el articulo
    // for(auto& i : u.compra()){
    //     //importe_Total_ += precio_articulo * cantidad del mismo.
    //     importe_Total_ += i.first->precio() * i.second;
    //     pa.pedir((*i.first),*this,i.first->precio(),i.second);

    //     //restamos el stock del articulo que se ha pedido
    //     i.first->stock() -= i.second; //sobrecarga del operador -=
    // }
    // //Aumentamos el numero de pedidos y vaciamos el carro del usuario
    // u.vaciar_carro();
    // n_pedidos_++;


    /*----Práctica 4----*/
    // Ahora para poder construir el pedido no podemos comprobar directamente el stock de los articulos
    // que están en el carrito del usuario, ya que la clase artículo no tiene ese atributo.
    // Para ello, tenemos que buscar una manera de convertir un objeto de tipo articulo a uno de tipo
    // ArticuloAlmacenable para poder acceder al stock.
    // Como las conversiones implícitas hacia abajo no están permitidas, haremos uso de una conversión
    // explicita mediante dynamic_cast.

    //Si no hay stock del articulo, excepcion.
    //Hacemos la conversión primero y luego comprobamos
    Usuario::Articulos carrito = u.compra();
    for(auto i : carrito){//carrito del usuario
        if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(i.first)){//hacemos conversion
            //comprobamos el stock
            if(AA->stock() < i.second){
                u.vaciar_carro();
                throw Pedido::SinStock(AA); 
            }  
        }
        //DA UN SEGMENTATION FAULT
        else if(LibroDigital* LD = dynamic_cast<LibroDigital*>(i.first)){
            //Si la fecha de expiración es < a la fecha del pedido, se añade con cantidad 0
            if(LD->f_expir() < Fecha()){ //Ha expirado
                u.compra(*LD,0);//Añadimos al pedido dicho articulo pero con la cantidad a 0
            }
        }
        else{
            throw std::logic_error("Pedido::Pedido - Tipo de articulo no conocido");
        }
    }
    //Comprobamos que no se quede vacio el Pedido
    if(u.compra().empty()) throw Pedido::Vacio(&u);
    //Realizamos la asociación Usuario - Pedido
    up.asocia(*this,u);

    //Vamos a pedir el articulo
    for(auto& i : u.compra()){
        importe_Total_ += i.first->precio() * i.second;
        pa.pedir(*this,*(i.first),i.first->precio(),i.second);

        //Ahora para restar el stock de dicho articulo hacemos lo mismo que arriba
        if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(i.first)){
            AA->stock() -= i.second;
        }
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
