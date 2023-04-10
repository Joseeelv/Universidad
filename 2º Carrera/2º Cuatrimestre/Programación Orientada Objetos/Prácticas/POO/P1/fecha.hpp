/*
Jose Luis Venega Sánchez
Practica 0 de POO
*/
#ifndef FECHA_HPP
#define FECHA_HPP
#include <iostream>
//especificacion de la clase fecha
class Fecha{
    public:
        //constructores de la clase
        explicit Fecha(int dd=0 ,int mm = 0,int aaaa=0); //constructor que usa conversiones no implicitas
        Fecha(const Fecha& f ) = default ;//constructor de copia "no hay ni punteros ni referencias --> Usamos Predeterminado"
        Fecha& operator =(const Fecha& f) = default; //operador de asignacion "predeterminado"
        Fecha(const char* c);//obtenemos una fecha a partir de una cadena de caracteres
        const char* cadena() const noexcept ; //Conversor a const *char

        //metodos observadores de la clase
        inline int dia() const noexcept{return dd;}
        inline int mes() const noexcept{return mm;}
        inline int anno() const noexcept{return aaaa;}

        //años max y min "nos especifica que debe de ir en la parte pública de la clase"
        static const int AnnoMaximo=2037;
        static const int AnnoMinimo= 1902;

        //Sobrecarga de Operandos
        Fecha& operator ++(); //incremento ++fecha
        Fecha operator ++(int n); //incremento fecha++
        Fecha& operator --();//decremento --fecha
        Fecha operator --(int n);//decremento fecha--
        Fecha& operator +=(int n);
        Fecha& operator -=(int n);

        //Sobrecarga Operando aritmeticos "
        Fecha operator +(int n) const; //suma
        Fecha operator -(int n) const; //resta
        //destructor por defecto
        ~Fecha()=default; //Destructor por defecto por omision "visto en clase"

    //excepciones
        class Invalida{ //clase que contiene la excepciones que puedan ocurrir en el programa
            public:
                //constructores de la clase
                Invalida(const char* cadena):motivo(cadena){};
                inline const char* por_que() const {return motivo;} 
            private:
            const char* motivo; //cadena que contiene el motivo de la excepción
        };
    private:
    int dd,mm,aaaa; //formato dia/mes/año
    int ultimo_dia() const; //observa cual es el ultimo dia de ese mes
    void comprobarfecha(); //funcion que comprueba que la fecha es correcta
};
//Especificacion de los operadores lógicos
bool operator ==(const Fecha& a, const Fecha& b) noexcept; //devuelve verdadero si ambas fechas son iguales
bool operator !=(const Fecha& a, const Fecha& b)noexcept; //devuelve verdadero si las fechas son diferentes
bool operator <(const Fecha& a, const Fecha& b)noexcept; //devuelve verdaderos si la fecha a<b
bool operator > (const Fecha& a, const Fecha& b)noexcept; //devuelve verdaderoa si la fehca a>b
bool operator <=(const Fecha& a, const Fecha& b)noexcept; //devuelve verdaderos si la fecha a<=b
bool operator >=(const Fecha& a, const Fecha& b)noexcept; //devuelve verdaderoa si la fehca a>=b

//Creamos la especificación del operador de extraccion
std::ostream& operator <<(std::ostream& os, const Fecha& f) noexcept; 
//Creamos la especificacion del operador de inserccion
std::istream& operator >>(std::istream& is, Fecha& f);

#endif//fecha.cpp
//ya se realizó todo lo pedido en la P0
/*
----PRÁCTICA 1----
    (✅) Especificar los operadores de extraccion e insercion
*/