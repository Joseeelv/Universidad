#ifndef ARTICULO_HPP
#define ARTICULO_HPP

//Inclusión de librerías
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include <iostream>
#include <iomanip>
#include <locale.h>
#include <set>

/*-----Clase Autor de la P4-----*/
class Autor{
    public:
        //No definimos la relación con Articulo aqui ya que no
        //nos hace falta.
        Autor(const Cadena& nombre, const Cadena& apellido, const Cadena& direccion)
            :nom_(nombre),apell_(apellido),dir_(direccion){}
        //Consultores de la clase
        inline const Cadena& nombre() const noexcept {return nom_;}
        inline const Cadena& apellidos() const noexcept {return apell_;}
        inline const Cadena& direccion() const noexcept {return dir_;}
    private:
        Cadena nom_,apell_,dir_;
};

/*-----Clase Aticulo de la P4-----*/
class Articulo{
    public:
    /*-----Relación entre Articulo - Autor-----*/
        //podemos definirlo como una asociación o agregación, que cada Articulo contendrá 
        //un conjunto de Autores.
        typedef std::set<Autor*>Autores;

        //Como un Articulo puede tener como mínimo 1 autor y además sin autor no hay articulo
        Articulo(const Autores& autores, Cadena referencia, Cadena titulo ,
            Fecha f_publi,double precio);

        //Observadores de la clase
        inline const Cadena& referencia() const noexcept{return referencia_;}
        inline const Cadena& titulo()const noexcept{return titulo_;}
        inline const Fecha& f_publi()const noexcept{return fpubli_;}
        inline double precio()const noexcept{return precio_;}
        inline double& precio()noexcept{return precio_;}
        //Desaparece en esta práctica
        // inline unsigned stock()const noexcept{return stock_;}
        // inline unsigned& stock()noexcept{return stock_;}
        inline const Autores& autores()const noexcept{return autores_;}
        //Exepcion de la clase
        class Autores_vacios{};

        //Nuevo operador de inserción en flujo
        virtual void impresion_especifica(std::ostream&)const =0;

        //Como esta clase se va a especializar en otras su destructor debe de ser
        //virtual para que puedan llamarse a los destructores de las clases derivadas
        virtual ~Articulo()=default;
    private:
        Autores autores_;//relación de las clases Articulo - Autor
        const Cadena referencia_,titulo_;
        const Fecha fpubli_;
        double precio_;
        //unsigned stock_; Desaparece en esta práctica
};

//Operador de inserción en flujo
std::ostream& operator <<(std::ostream& , const Articulo&)noexcept;

/*-----Clase Derivada ArticuloAlamacenable-----*/
class ArticuloAlmacenable : public Articulo{
    public:
        ArticuloAlmacenable(const Autores& autores, Cadena referencia, Cadena titulo,
            Fecha f_publi,double precio, unsigned stock=0)
            :Articulo(autores,referencia,titulo,f_publi,precio),stock_(stock){}

        //Observadores de la clase
        inline unsigned stock()const noexcept{return stock_;}
        inline unsigned& stock()noexcept{return stock_;}
    protected: //se pone protected para que las clases derivadas de esta puedan hacer uso del atributo
    //Atributo de la clase Articulo que lo define
        unsigned stock_;
};

/*-----Clase Derivada Libro-----*/
class Libro final: public ArticuloAlmacenable{
    public:
        Libro(const Autores& autores, Cadena referencia, Cadena titulo,
            Fecha f_publi,double precio, unsigned paginas=0, unsigned stock=0):
            ArticuloAlmacenable(autores,referencia,titulo,f_publi,precio,stock),n_pag_(paginas){}
        //Observadores de la clase
        inline const unsigned& n_pag()const noexcept {return n_pag_;}
        //Método virtual heredado
        void impresion_especifica(std::ostream&) const override final;
    private:
    //Atributo de la clase que lo define
     const unsigned n_pag_;    
};

/*-----Clase Derivada Revista-----*/
class Revista final: public ArticuloAlmacenable{
    public:
        Revista(const Autores& autores, Cadena referencia, Cadena titulo,
            Fecha f_publi,double precio,const unsigned numero, const unsigned f,unsigned stock=0):
            ArticuloAlmacenable(autores,referencia,titulo,f_publi,precio,stock),numero_(numero),periodicidad_(f){}
        //Observadores de la clase
        inline unsigned numero()const noexcept{return numero_;}
        inline unsigned periodicidad()const noexcept{return periodicidad_;}
        //Método virtual heredado
        void impresion_especifica(std::ostream&)const override final;
    private:
        const unsigned numero_, periodicidad_;
};

/*-----Clase Derivada LibroDigital-----*/
class LibroDigital final:public Articulo{
    public:
        LibroDigital(const Autores& autores, Cadena referencia, Cadena titulo ,
            Fecha f_publi,double precio,const Fecha& f_expir):
            Articulo(autores,referencia,titulo,f_publi,precio),f_expir_(f_expir){}
        //Observador de la clase
        inline const Fecha& f_expir()const noexcept{return f_expir_;}
        //Método virtual heredado
        void impresion_especifica(std::ostream&)const override final;
    private:
        const Fecha f_expir_;
};

#endif // !ARTICULO_HPP