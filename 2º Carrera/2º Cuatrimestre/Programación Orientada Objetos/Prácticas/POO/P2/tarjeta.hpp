//
//Jose Luis Venega Sánchez P2
//

#ifndef _TARJETA_HPP
#define _TARJETA_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"
#include "ostream"
#include "cstring"
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <set>

//declaracion adelantada de las clases
class Usuario;
class Clave;

//##### CLASE NUMERO #####
class Numero{
public:
enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
//ctor
Numero(const Cadena& num);
friend bool operator < (const Numero& a, const Numero& b); //booleano que nos dice si el numero a es menor que b
operator const char*() const; //operador de conversion a cadena de bajo nivel
    //clase de la excepcion
    class Incorrecto{
        public:
        Incorrecto(const Razon& r):fallo_(r){}
        const Razon& razon() const{return fallo_;}
        private:
        Razon fallo_; 
    };

private:
    Cadena numero_;
    //metodos privados de la clase
    Cadena eliminar_espacios(const Cadena& n); //eliminamos lo espacios inecesarios
    Cadena longitud(const Cadena& n); //obtenemos la longitud de la cadena

};


//##### CLASE TARJETA #####
class Tarjeta{
public:
    enum Tipo{OTRO, VISA, Mastercard,Maestro, JCB, AmericanExpress};

    Tarjeta(const Numero& n, Usuario& user,const Fecha& f);
//Dos tarjetas no se pueden copiar, ni al crearse ni por asignación. 
//Esto sería ilegal, no puede haber dos tarjetas iguales
    Tarjeta(const Tarjeta& t)=delete;
    Tarjeta& operator=(const Tarjeta& t)=delete;

//metodos observadores de los atributos
    inline const Numero& numero() const{return numero_;}
    inline const Usuario* titular() const {return usuario_;}
    inline const Fecha& caducidad() const{return caduc_;}
    inline bool activa(bool valor){activa_ = valor;return activa_;}
    inline bool activa() const {return activa_;}
    Tipo tipo() const;

//destrutor 
    ~Tarjeta();
//clase de la excepcion Caducada
    class Caducada{
        public:
        Caducada(const Fecha& f): fchC_(f){}
        Fecha cuando() const{return fchC_;}
        private:
        Fecha fchC_;
    };

//clase de la excepcion Numero duplicado
    class Num_duplicado{
        public:
        Num_duplicado(const Numero& n):n_(n){}
        const Numero& que() const {return n_;}
        private:
        Numero n_;
    };
//clase desactivada "todo por omision"
    class Desactivada{};
private:
    const Numero numero_;
    Usuario* const usuario_; //nombre del titular
    const Fecha caduc_;
    bool activa_;

    void anula_titular();
    friend class Usuario;
    //Conj de todas las tarjetas existentes
    static std::set<Numero> tarjetas_;
};
//sobrecarga del operando <<
std::ostream& operator << (std::ostream& out, const Tarjeta& t);
std::ostream& operator <<(std::ostream& out, const Tarjeta::Tipo& t);
//Dos Tarjeta podrán ordenarse por sus números. Para ello tendrá que definir el operador menor-que de dos tarjetas.
bool operator < (const Tarjeta& a, const Tarjeta& b);
#endif //Tarjeta.hpp