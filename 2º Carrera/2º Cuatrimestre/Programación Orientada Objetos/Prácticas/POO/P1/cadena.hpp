/*
Jose Luis Venega Sánchez
Practica 0 de POO
*/
#ifndef CADENA_HPP
#define CADENA_HPP
#include <iostream>
//especificacion de la clase cadenaç
class Cadena{
    public:
        explicit Cadena(size_t t=0, char caracter=' ');//constructor de cadena
                                                       //con tamaño = 0 y vacía.
        Cadena(const Cadena& cadena); //constructor de copia, debemos de usar
                                      //uno que no sea predeterminado ya que vamos
                                      //a trabajar con punteros y referencias.
        Cadena(const char* cadena);
        Cadena(Cadena&& cadena);//constructor de movimiento
        //operador de asignacion para el ctr de copia
        Cadena& operator =(const Cadena& cadena);
        Cadena& operator =(Cadena&& cadena);
        //metodos observadores
        inline int length()const noexcept{return tam_;}

        //metodo de conversion a const char*
        explicit operator const char* () const noexcept;

        //sobrecarga de operadores
        Cadena& operator +=(const Cadena& cadena);

        //metodos operadores de indice
        inline char& operator[](int i){return s_[i];}//modificadora
        inline const char& operator[](int i) const{return s_[i];} //observadora
        char& at(size_t i);//modificadora
        const char& at(size_t i)const; //observadora

        //Subcadena "substr"
        Cadena substr(size_t i, size_t tam) const; //siendo i una posicion y tam el tamaño

        //iteradores nos lo especifica el guión de la práctica
        typedef char* iterator;
        typedef const char* const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        //funciones de los iteradores
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        const_iterator cbegin() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator crend() const noexcept;
        const_reverse_iterator rend() const noexcept;

        //destructor que elimina la cadena y libera memoria
        ~Cadena(); //no es el predeterminado
    private:
    char* s_; //cadena de caracteres
    size_t tam_; //tamaño de la cadena
};
//Especificion operadores lógicos
bool operator ==(const Cadena& a, const Cadena& b); //devuelve verdadero si ambas cadena son iguales
bool operator !=(const Cadena& a, const Cadena& b); //devuelve verdadero si las cadena son diferentes
bool operator <(const Cadena& a, const Cadena& b); //devuelve verdaderos si la cadena a<b
bool operator > (const Cadena& a, const Cadena& b); //devuelve verdaderoa si la cadena a>b
bool operator <=(const Cadena& a, const Cadena& b); //devuelve verdaderos si la cadena a<=b
bool operator >=(const Cadena& a, const Cadena& b); //devuelve verdaderoa si la cadena a>=b
Cadena operator +(const Cadena& a, const Cadena& b); //devuelve una cadena resultante de la suma de otras 2

//operadores de inserccion y extraccion
std::ostream& operator <<(std::ostream& os, const Cadena& cadena) noexcept; //no lanza excepcion
std::istream& operator >> (std::istream& is, Cadena& cadena);

//metodos de los iteradores
inline Cadena::iterator Cadena::begin()noexcept{
    return s_;
}
inline Cadena::const_iterator Cadena::begin() const noexcept{
    return s_;
}
inline Cadena::reverse_iterator Cadena::rbegin() noexcept{
    return reverse_iterator(end());
}
inline Cadena::const_reverse_iterator Cadena::rbegin() const noexcept{
    return const_reverse_iterator(end());
}
inline Cadena::const_iterator Cadena::cbegin() const noexcept{
    return s_;
}
inline Cadena::const_reverse_iterator Cadena::crbegin() const noexcept{
    return const_reverse_iterator(end());
}
inline Cadena::iterator Cadena::end() noexcept{
    return s_+tam_;
}
inline Cadena::const_iterator Cadena::end() const noexcept{
    return s_+tam_;
}
inline Cadena::const_iterator Cadena::cend() const noexcept{
    return s_+tam_;
}
inline Cadena::reverse_iterator Cadena::rend() noexcept{
    return reverse_iterator(begin());
}
inline Cadena::const_reverse_iterator Cadena::crend() const noexcept{
    return const_reverse_iterator(begin());
}
inline Cadena::const_reverse_iterator Cadena::rend() const noexcept{
    return const_reverse_iterator(begin());
}

#endif //cadena.hpp

/*
----PRÁCTICA 0----
    (✅) cadena con 1 parametro "tam" --> se rellena con espacios
    (✅) cadena sin parametros --> cadena vacia de tam 0
    (✅) se puede copiar una cadena en otra
    (✅) se puede realizar conversiones desde const char* a una cadena
    (✅) funcion observadora --> length que devuelve el nº carac cadena
    (✅) se puede realizar conversiones a char*
    (✅) las cadenas se pueden concatenar --> Operador suma con asignacion "+="
    (✅) las cadenas se pueden concatenar --> Operador suma "+" 
    (✅) se pueden comparar cadenas "valor booleano" --> "==", "!=", ">", "<", "<=" y ">="
    (✅) comprobar que la cadena no se sale del rango
    (✅) Se puede obtener un caracter cualquiera de la cadena --> mediante un indice
    (✅) El destructor debe de eliminar la cadena y liberar memoria reservada

----PRÁCTICA 1----
    (✅) Especificar los operadores de extraccion e insercion ""
    (✅) Especificar los iteradores y metodos de los iteradores
    (✅) Especificar constructores de movimiento
*/