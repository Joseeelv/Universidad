#include"Junio22.hpp"

/*Implementación de los métodos de la realcion Cliente - Vehiculo*/
void Cliente_Vehiculo::reserva(Cliente& c,Vehiculo& v,Reserva& r)noexcept{
    directa_[&c].insert(std::make_pair(&v,&r));
    inversa_[&v].insert(std::make_pair(&c,&r));
}

void Cliente_Vehiculo::reserva(Vehiculo& v,Cliente& c, Reserva& r)noexcept{
    //delegamos en la anterior
    reserva(c,v,r);
}
Cliente_Vehiculo::VR Cliente_Vehiculo::reservados(Cliente& c)const noexcept{
    //buscamos si existe el cliente que hace la reserva
    auto i = directa_.find(&c);
    if(i!=directa_.end())return i->second;
    else{
        //Devolvemos una reserva vacía
        Cliente_Vehiculo::VR vacia;
        return vacia;
    }
}
Cliente_Vehiculo::CR Cliente_Vehiculo::reservados_por(Vehiculo& v)const noexcept{
    //Buscamos si existe el vechiculo reservado
    auto i = inversa_.find(&v);
    if(i!=inversa_.end())return i->second;
    else{
        //Creamos una reserva vacia y la devolvemos
        Cliente_Vehiculo::CR vacia;
        return vacia;
    }
}

/*Implementación de los métodos de la realcion Cliente - Contrato*/
void Cliente::firma(Contrato& c)noexcept{
    contratos_.insert(&c);
}
const Cliente::Contratos& Cliente::firmados()const noexcept{
    return contratos_;
}

//Observador implementado en el fichero .hpp


/*Implementación de los métodos de la realcion Contrato - Vehiculo*/

void Contrato_Vehiculo::detalle(Contrato& c, Vehiculo& v, Detalle& d)noexcept{
    //Como son pair, estos no tienen el método insert por lo que se hace asignando
    directa_[&c] = std::make_pair(&v,&d);
    inversa_[&v] = std::make_pair(&c,&d);
}

void Contrato_Vehiculo::detalle(Vehiculo& v, Contrato& c, Detalle& d)noexcept{
    //Delegamos en el método anterior
    detalle(c,v,d);
}

const Contrato_Vehiculo::VD& Contrato_Vehiculo::vehiculoscontratados(Contrato& c)const noexcept{
    //Como siempre va a haber un contrato relacionado con un vehiculo y detalle,
    //no hace falta comprobar si existe o no
    return directa_.find(&c)->second;
}

 const Contrato_Vehiculo::CD& Contrato_Vehiculo::contratosvehiculo(Vehiculo& v)const noexcept{
    //Al igual que la anterior, al ser la multiplicidad 1..* siempre va a haber un
    //vehiculo asociado con un contrato y los detalles
    return inversa_.find(&v)->second;
 }
