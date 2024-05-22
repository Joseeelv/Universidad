#include "articulo.hpp"
/*-----Implementación de la clase Articulo-----*/
Articulo::Articulo(const Autores& autor, Cadena referencia, Cadena titulo, Fecha f_publi,
double precio):autores_(autor), referencia_(referencia), titulo_(titulo),fpubli_(f_publi),precio_(precio){
    //Lo unico que tenemos que comprobar que dicho articulo tenga como mínimo un autor
    if(autores_.empty())throw Autores_vacios();
}

//Operador de inserción en flujo
std::ostream& operator <<(std::ostream& output, const Articulo& art)noexcept{
    std::locale::global(std::locale(""));
    output<<"["<<art.referencia()<<"] "<<"\""<<art.titulo()<<"\""<<", de ";

    //recorremos el conjunto de autores del articulo
    auto i = art.autores().begin();
    output << (*i)->apellidos();
    for(i++;i!=art.autores().end();i++){
        output<<", "<<(*i)->apellidos();
    }
    output<<". "<<art.f_publi().anno()<<". "
          <<std::fixed<<std::setprecision(2)<<art.precio()<<" €"<<std::endl<<"\t";
    //llamamos al método heredado.
    art.impresion_especifica(output);
    return output;
}

/*-----Implementación del Método virtual-----*/
void Libro::impresion_especifica(std::ostream& output)const{
    output<<n_pag_<<" págs., "<< stock_ <<" unidades.";
}

void Revista::impresion_especifica(std::ostream&output)const{
    output << "Número: "<<numero_<<", Periodicidad: "<<periodicidad_<<" días."
    <<"\n"<<"\t"
    <<"Próximo número a partir de: " <<Fecha(f_publi() + periodicidad_) <<".";
}

void LibroDigital::impresion_especifica(std::ostream& output)const{
    output<<"A la venta hasta el "<<f_expir_<<".";
}