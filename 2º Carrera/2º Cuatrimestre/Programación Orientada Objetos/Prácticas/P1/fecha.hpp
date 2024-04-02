#ifndef FECHA_HPP_
#define FECHA_HPP_

//incluimos las librerias
#include <iostream>
#include <ctime> //para la fecha del sistema
#include <utility> //para los operadores lógicos
#include <stdio.h> //sscanf
#include <cstring>
#include <cstdio>
class Fecha{
    public:
        //Ctor de 3 parámetros.
        explicit Fecha(int dia =0, int mes=0, int anno=0);
        //Ctor a partir de cadena de bajo nivel -> dd/mm/aaaa.
        Fecha (const char*);
        //operador de conversion de cadena de bajo nivel a fecha
        const char* cadena() const noexcept;
        //atributos publicos que definen el rango de años.
        static const int AnnoMinimo = 1902;
        static const int AnnoMaximo=2037;

        //observadores de la clase
        inline int dia()const noexcept{return dia_;}
        inline int mes()const noexcept{return mes_;}
        inline int anno()const noexcept{return anno_;}

        //Operadores incremento y decremento de la fecha
        Fecha& operator ++();
        Fecha operator ++(int);
        Fecha& operator --();
        Fecha operator --(int);

        Fecha operator +(int) const;
        Fecha operator -(int) const;
        
        Fecha& operator += (int);
        Fecha& operator -= (int);


        //clase de la excepcion
        class Invalida{
            public:
                Invalida(const char* c):motivo_(c){}
                const char* por_que()const {return motivo_;}
            private:
                const char* motivo_;
        };
    private:
        //atributos de los objetos clase
        int dia_,mes_,anno_;
        mutable char crep[45];
        mutable bool actual;
        //métodos privados comprobadores de fecha
        void comprueba_fecha()const; //comprueba que la fecha sea válida
        int ultimo_dia()const; //devuelve el último dia del mes
        void actualizar()const;
};

//Operadores lógicos
bool operator == (const Fecha& , const Fecha&);
bool operator != (const Fecha&, const Fecha&);
bool operator < (const Fecha&, const Fecha&); //se sobrecarga este
bool operator <= (const Fecha&, const Fecha&);
bool operator > (const Fecha&, const Fecha&);
bool operator >= (const Fecha&, const Fecha&);

//Operadores de inserccion y extracción en flujo
std::ostream& operator <<(std::ostream&, const Fecha& )noexcept;
std::istream& operator >>(std::istream&, Fecha&);
#endif //Fecha.hpp
/*
Hecho por: Jose Luis Venega Sánchez
*/