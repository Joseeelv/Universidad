//
//Jose Luis Venega Sánchez P2
//
#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_

//incluimos las cabeceras de las clases
#include "../P1/cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <ostream>
#include <random>
#include <unistd.h>
#include <cstring>
#include <iomanip>


class Numero;
class Tarjeta; //declaracion adelantada

//#####CLASE CLAVE#####
class Clave{
    public:
    typedef enum {CORTA,ERROR_CRYPT}Razon;
    //ctor
    Clave(const char* c);

    //metodo observador y verificar
    Cadena clave() const;
    bool verifica(const char* c) const;
        //clase Incorrecta
        class Incorrecta{
            public:
                Incorrecta(const Razon& r): fallo_(r){};
                Razon razon() const{return fallo_;}
            private:
            Razon fallo_;
        };

    private:
    Cadena password_;
};

//implementamos los metodos inline
inline Cadena Clave::clave() const{return password_;}

//#####CLASE USUARIO#####
class Usuario{
public:
    typedef std::unordered_set<Cadena> Usuarios;
    //Un diccionario ordenado de números de tarjeta y punteros a tarjetas
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    //El contenido del carrito, representado por un diccionario desordenado de punte- ros a artículos
    typedef std::unordered_map<Articulo *, unsigned int > Articulos;

    //ctor
    Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellido, 
            const Cadena& dir, const Clave& pass);

    //Un Usuario no podrá crearse por copia de otro, no podrá pues copiarse ni asignarse a otro
    Usuario& operator = (const Usuario& u) = delete;
    Usuario(const Usuario& u)=delete;

    //metodos observadores
    inline Cadena id() const{return identificador_;}
    inline Cadena nombre() const{return nombre_;}
    inline Cadena apellidos() const{return apellidos_;}
    inline Cadena direccion() const{return direccion_;}
    inline const Tarjetas& tarjetas() const{return tarjetas_;}
    inline const Articulos& compra() const{return articulos_;}

    //Con el método compra() se podrá vaciar el carrito sacando los artículos uno por uno
    void compra(Articulo& art, unsigned cantidad =1);

    void vaciar_carro() {articulos_.clear();}
    //De la asociación con la clase Tarjeta se encargarán los métodos:
    //es_titular_de () y no_es_titular_de()
    void es_titular_de(Tarjeta& tarj);
    void no_es_titular_de(Tarjeta& tarj);

    //El número de artículos diferentes que hay en el carrito 
    //será devuelto por un método llamado n_articulos()
    size_t n_articulos()const{return articulos_.size();}

    //Se sobrecargará el operador de inserción en flujo (<<) para mostrar o imprimir un Usuario
    friend std::ostream& operator << (std::ostream& out, const Usuario& user);

    ~Usuario(); //destructor

    //clase de la excepcion
    class Id_duplicado{
        public:
        //Ctor
        Id_duplicado(const Cadena& c):id_(c){};
        //observador
        const Cadena idd() const{return id_;}
        private:
        Cadena id_;
    };
private:
    const Cadena identificador_, nombre_, apellidos_, direccion_;
    Clave constraseña_;
    Tarjetas tarjetas_;
    Articulos articulos_;

    static std::unordered_set<Cadena> usuario_;
};
//se definirá una función externa mostrar_carro(), que deberá mostrar o 
//imprimir en un flujo de salida dado como primer parámetro el contenido del carro de la compra de un usuario
void mostrar_carro(std::ostream& out, const Usuario& user);

#endif //usuario.hpp


//me dice que no existe un miembro tarjetas en usuario . 