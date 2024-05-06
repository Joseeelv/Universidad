#ifndef USUARIO_HPP
#define USUARIO_HPP

//Inclusión de librerías
#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <unistd.h> //crypt()
#include <random>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>

//Declaraciones adelantadas
class Tarjeta;
class Numero;

/*-----Clase Clave-----*/
class Clave{
    public:
        typedef enum {CORTA,ERROR_CRYPT}Razon;
        Clave(const char*);

        //observador de la clase
        inline Cadena clave()const {return password_;}
        bool verifica(const char* )const;
        //Clase de la excepción
        class Incorrecta{
            Razon razon_;
            public:
                Incorrecta(const Razon& r):razon_(r){};
                const Razon& razon()const{return razon_;}
        };
    private:
        Cadena password_;
};

/*-----Clase Usuario-----*/
class Usuario{
    public:
        typedef std::map<Numero,Tarjeta*> Tarjetas;
        typedef std::unordered_map<Articulo*,unsigned int>Articulos;

        Usuario(const Cadena& ,const Cadena& , const Cadena& , const Cadena& , const Clave& );
        //eliminamos el ctor de copia y el operador de asignacion
        Usuario(const Usuario&)=delete;
        Usuario operator = (const Usuario&)=delete;
        //métodos observadores
        inline Cadena id()const noexcept{return identificador_;}
        inline Cadena nombre()const noexcept{return nombre_;}
        inline Cadena apellidos()const noexcept{return apellidos_;}
        inline Cadena direccion()const noexcept{return direccion_;}
        inline const Tarjetas& tarjetas()const noexcept{return tarjetas_;}
        inline const Articulos& compra()const noexcept{return articulos_;}
        
        //metodos de la asociacion con clase Tarjeta
        void es_titular_de(Tarjeta&) noexcept;
        void no_es_titular_de(Tarjeta&) noexcept;
        //métodos de la asociación unidireccional con Articulos
        void compra( Articulo&, size_t cantidad = 1) noexcept;
        inline void vaciar_carro() noexcept {articulos_.clear();}
        inline size_t n_articulos()const noexcept {return articulos_.size();}

        //destructor de la clase usuario
        ~Usuario();
        //Clase de la excepcion
        class Id_duplicado{
            Cadena id_;
            public:
                Id_duplicado(const Cadena& id):id_(id){};
                const Cadena& idd()const{return id_;}
        };
        friend std::ostream& operator <<(std::ostream& , const Usuario&)noexcept;
    private:
        const Cadena identificador_, nombre_,apellidos_,direccion_;
        Clave clave_;
        Tarjetas tarjetas_;
        Articulos articulos_;
        static std::unordered_set<Cadena> usuario_; //conjunto de usuarios no repetidos del programa
};
void mostrar_carro(std::ostream& , const Usuario&);
#endif // !USUARIO_HPP
