#include "articulo.hpp"

//Operador de inserción en flujo
std::ostream& operator <<(std::ostream& output, const Articulo& art)noexcept{
    std::locale::global(std::locale(""));
    output<<"["<<art.referencia()<<"]"<<"\""<<art.titulo()<<"\""<<", "
          <<art.f_publi().anno()<<". "
          <<std::fixed<<std::setprecision(2)<<art.precio()<<" €";
    return output;
}