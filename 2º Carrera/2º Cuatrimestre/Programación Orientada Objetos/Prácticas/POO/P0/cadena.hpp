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
        //operador de asignacion para el ctr de copia
        Cadena& operator =(const Cadena& cadena );

        //metodos observadores
        inline int length()const noexcept{return tam_;}

        //metodo de conversion a const char*
        explicit operator const char* ()const {return s_;}

        //sobrecarga de operadores
        Cadena& operator +=(const Cadena& cadena);

        //metodos operadores de indice
        inline char& operator[](int i){return s_[i];}//modificadora
        inline const char& operator[](int i) const{return s_[i];} //observadora
        char& at(size_t i);//modificadora
        const char& at(size_t i)const; //observadora

        //Subcadena "substr"
        Cadena substr(size_t i, size_t tam) const; //siendo i una posicion y tam el tamaño
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


#endif //cadena.hpp

/*
    (*) cadena con 1 parametro "tam" --> se rellena con espacios
    (*) cadena sin parametros --> cadena vacia de tam 0
    (*) se puede copiar una cadena en otra
    (*) se puede realizar conversiones desde const char* a una cadena
    (*) funcion observadora --> length que devuelve el nº carac cadena
    (*) se puede realizar conversiones a char*
    (*) las cadenas se pueden concatenar --> Operador suma con asignacion "+="
    (*) las cadenas se pueden concatenar --> Operador suma "+" 
    (*) se pueden comparar cadenas "valor booleano" --> "==", "!=", ">", "<", "<=" y ">="
    (*) comprobar que la cadena no se sale del rango
    (*) Se puede obtener un caracter cualquiera de la cadena --> mediante un indice
    (*) El destructor debe de eliminar la cadena y liberar memoria reservada

*/