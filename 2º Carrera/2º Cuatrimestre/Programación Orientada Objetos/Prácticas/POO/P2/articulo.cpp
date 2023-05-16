//
//Jose Luis Venega Sánchez P2
//
#include "articulo.hpp"
//implementamos el operador de extraccion
std::ostream& operator <<(std::ostream& out, const Articulo& Art){
    std::locale::global(std::locale(""));
    out << "[" << Art.referencia() << "] "<< "\"" <<Art.titulo()<<" \", " <<Art.f_publi().anno() << ". " 
    <<std::fixed<<std::setprecision(2)<<Art.precio()<<" €";
    return out; //devolvemos el flujo de salida
}