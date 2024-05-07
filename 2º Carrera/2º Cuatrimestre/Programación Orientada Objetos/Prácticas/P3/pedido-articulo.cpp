#include "pedido-articulo.hpp"

//Implementación de la clase LineaPedido
std::ostream& operator <<(std::ostream& output , const LineaPedido& lp)noexcept{
    return output << std::fixed<<std::setprecision(2)<<lp.precio_venta()<<" €\t"
            <<lp.cantidad();
}

//Implementación de la clase Pedido_Articulo
bool OrdenaArticulos::operator()(const Articulo* a1, const Articulo* a2) const{
    return (a1->referencia() < a2->referencia());
}

bool OrdenaPedidos::operator()(const Pedido* p1, const Pedido* p2)const{
    return (p1->numero() < p2->numero());
}

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio, unsigned cant){
    //Creamos una LineaPedido nueva
    LineaPedido lp(precio,cant);
    //creamos los enlaces
    pedidoarticulo_[&p].insert(std::make_pair(&a,lp));
    //creamos el enlace inverso
    articulopedido_[&a].insert(std::make_pair(&p,lp));
}

void Pedido_Articulo::pedir(Articulo& a,Pedido& p,double precio,unsigned cant){
    //Delegamos en el método anterior
    pedir(p,a,precio,cant);
}

const Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(Pedido& p)const{
    //buscamos si existe dicho pedido para devolver su contenido
    auto i = pedidoarticulo_.find(&p);
    if(i!=pedidoarticulo_.end())return i->second;
    else{
        Pedido_Articulo::ItemsPedido ItemsPedidoVacio; //creamos un ItemsPedido vacio si no se encuentra
        return ItemsPedidoVacio;
    }
}

const Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a)const{
    //buscamos el articulo
    auto i = articulopedido_.find(&a);
    if(i!=articulopedido_.end())return i->second;
    else{
        Pedido_Articulo::Pedidos PedidoVacio; //Si no existe, creamos un pedido vacío
        return PedidoVacio;
    }
}

//Implementación de los métodos de inserción en flujo

std::ostream& operator << (std::ostream& output,const Pedido_Articulo::ItemsPedido& IP)noexcept{
    //nos creamos una variable local para obtener el precio total
    double total = 0.;
    output << "PVP\t Cantidad\t Artículo"<<std::endl
    << std::setw(30)<<std::setfill('=')<<' '; //formato
    //insertamos el pedido
    for(auto& i :IP){
        total += i.second.precio_venta()*i.second.cantidad();
        output<<std::fixed<<std::setprecision(2)<<i.second.precio_venta()<<" € "
        <<i.second.cantidad()<<"\t"
        <<"["<<i.first->referencia()<<"] \""<<i.first->titulo()<<"\""<<std::endl;
    }
    output <<  std::setw(30)<<std::setfill('=')<<' ' <<std::endl
    <<"Total "<<std::fixed<<std::setprecision(2)<<total<<" €";
    //devolvemos el flujo de salida
    return output;
}

std::ostream& operator <<(std::ostream& output,const Pedido_Articulo::Pedidos& Ped)noexcept{
    //Nos creamos una variable local para obtener el precio total y el numero de pedidos
    double total = 0.;
    unsigned npedido =1;
    output<<"[Pedidos: "<<npedido<<"]"<<std::endl
          <<std::setw(30)<<std::setfill('=')<<"' '"<<std::endl//formato
          <<std::setw(1)<<"PVP\t Cantidad\t Fecha de venta"<<std::endl
          <<std::setw(30)<<std::setfill('=')<<"' '"<<std::endl;//formato
    for(auto& i : Ped){
        //actualizamos el numero de pedido y el total
        total+=i.second.precio_venta()*i.second.cantidad();
        npedido++;
        output<<std::fixed<<std::setprecision(2)<<i.second.precio_venta()<<" € "<<i.second.cantidad()<<" \t "
              <<i.first->fecha()<<std::endl;
    }
    output<<std::setw(30)<<std::setfill('=')<<"' '"<<std::endl//formato
          <<std::fixed<<std::setprecision(2)<<total<<" €\t "<<npedido<<std::endl;
    return output;
}

std::ostream& Pedido_Articulo::mostrarDetallesPedidos(std::ostream& output)const noexcept{
    //Creamos variables locales para alamecenar el numero de pedido y el total de ventas
    double total=0.;
    unsigned npedido=0;
    for(auto& i : pedidoarticulo_){
        npedido++;
        output<<"Pedido núm. "<<npedido<<std::endl
              <<"Cliente: "<< i.first->tarjeta()->titular()<<"\t"
              <<"Fecha: "<<i.first->fecha()<<std::endl
              <<detalle(*i.first)<<std::endl;
    }
    output<<"TOTAL VENTAS\t "<<std::fixed<<std::setprecision(2)<<total<<std::endl;
    return output;
}
std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& output)const noexcept{
    for(auto& i : articulopedido_){
        output<<"Ventas de ["<<i.first->referencia()<<"] "<<"\""<<i.first->titulo()<<"\"\n"
              <<ventas(*i.first)<<std::endl;
    }
    return output;
}