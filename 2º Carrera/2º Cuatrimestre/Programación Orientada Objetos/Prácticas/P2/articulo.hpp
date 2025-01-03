#ifndef ARTICULO_HPP
#define ARTICULO_HPP

//Inclusión de librerías
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include <iostream>
#include <iomanip>
#include <locale.h>
class Articulo{
    public:
        Articulo(Cadena referencia, Cadena titulo ,Fecha f_publi
        ,double precio,unsigned ejemplares =0):referencia_(referencia),titulo_(titulo),
        fpubli_(f_publi),precio_(precio),ejemplares_(ejemplares){}

        //Observadores de la clase
        inline const Cadena& referencia() const noexcept{return referencia_;}
        inline const Cadena& titulo()const noexcept{return titulo_;}
        inline const Fecha& f_publi()const noexcept{return fpubli_;}
        inline double precio()const noexcept{return precio_;}
        inline double& precio()noexcept{return precio_;}
        inline unsigned stock()const noexcept{return ejemplares_;}
        inline unsigned& stock()noexcept{return ejemplares_;}

    private:
        const Cadena referencia_,titulo_;
        const Fecha fpubli_;
        double precio_;
        unsigned ejemplares_;
};

//Operador de inserción en flujo
std::ostream& operator <<(std::ostream& , const Articulo&)noexcept;
#endif // !ARTICULO_HPP