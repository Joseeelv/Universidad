#ifndef TARJETA_HPP
#define TARJETA_HPP

//Inclusión de librerias
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "usuario.hpp"
#include <iostream>
#include <set>
#include <algorithm> //remove_if
#include <cctype> //isspace
//declaraciones adelantadas
class Usuario;
class Clave;

/*-----Clase Numero-----*/
class Numero{
    public:
        //tipos de excepciones
        typedef enum {LONGITUD,DIGITOS,NO_VALIDO}Razon;
        Numero(const Cadena&);
        
        //operador de conversion a const char*
        inline operator const char*()const{return numero_.operator const char *();}
        //sobrecarga del operador < para comparar numeros
        friend bool operator < (const Numero&, const Numero&);
        //clase de la excepcion
        class Incorrecto{
            Razon razon_;
            public:
                Incorrecto(const Razon& r):razon_(r){};
                const Razon& razon()const{return razon_;}
        };

    private:
        Cadena numero_;
        //metodos extras para el constructor
        Cadena eliminar_espacios(const Cadena&); //devuelve la cadena sin espacios
        Cadena longitud(const Cadena&); //comprueba la longitud de la cadena es correcta o no
};

/*-----Clase Tarjeta-----*/
class Tarjeta{
    public:
        //tipos de tarjetas
        typedef enum {Otro,VISA,Mastercard,Maestro,JCB,AmericanExpress} Tipo;
        Tarjeta(const Numero&, Usuario&, const Fecha&);

        //no se pueden crear tarjetas por copia de otras
        Tarjeta(const Tarjeta&)=delete;
        Tarjeta operator =(const Tarjeta&)=delete;

        //Observadores de la clase
        const Numero& numero()const noexcept{return numero_;}
        const Usuario* titular()const noexcept{return titular_;}
        const Fecha& caducidad()const noexcept{return caducidad_;}
        bool activa()const noexcept{return activa_;}
        bool activa(bool estado) noexcept {activa_=estado;return activa_;}//version modificadora de la anterior
        Tipo tipo()const noexcept;

        //destructor de la clase
        ~Tarjeta();
        //Clase de la excepcion tarjeta caducada
        class Caducada{
            Fecha fecha_;
            public:
                Caducada(const Fecha fecha):fecha_(fecha){};
                const Fecha& cuando()const{return fecha_;}
        };
        //Clase de la excepcion tarjeta duplicada
        class Num_duplicado{
            Numero num_;
            public:
                Num_duplicado(const Numero& num):num_(num){};
                const Numero& que()const{return num_;}
        };
        //Clase de la excepcion tarjeta desactivada
        class Desactivada{};
    private:
        const Numero numero_;
        Usuario* const titular_;
        const Fecha caducidad_;
        bool activa_;

        //método privado de la clase
        //hacemos que la clase usuario sea amiga para poder hacer uso de este método
        friend class Usuario;
        void anula_titular();

        //conjunto de tarjetas
        static std::set<Numero>tarjetas_;
};
std::ostream& operator <<(std::ostream&, const Tarjeta& )noexcept;
std::ostream& operator <<(std::ostream&, const Tarjeta::Tipo& )noexcept;
//sobrecarga del operador <, para ordenar tarjetas
bool operator <(const Tarjeta&,const Tarjeta&);

#endif // !TARJETA_HPP
