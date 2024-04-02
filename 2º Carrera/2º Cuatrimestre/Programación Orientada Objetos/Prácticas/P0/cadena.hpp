#ifndef CADENA_HPP_
#define CADENA_HPP_

//Incluimos las librerías
#include <iostream>
#include <cstring>
#include <stdexcept>
class Cadena{
    public:
        //Por defecto, una cadena vacía = contiene el caracter terminador
        explicit Cadena(size_t tam = 0, char c = ' ');
        //Tenemos que definir el constructor de copia debido a que estamos haciendo uso de mem dinamica
        Cadena(const Cadena& );
        Cadena(const char*);
        //Si hacemos ctor de copia debemos de hacer operador de asignación por copia
        Cadena& operator = (const Cadena& )noexcept;
        Cadena& operator =(const char*)noexcept;
        //conversion a cadena de bajo nivel (observadora y modificadora)
        explicit operator const char*()const noexcept{return s_;}
        
        //método observador -> devuelve el num de caracteres de una cadena
        size_t length() const noexcept{return tam_;}
        //Operadores aritmeticos
        Cadena& operator += (const Cadena& )noexcept; //concatenación de cadenas (misma cadena resultante)
        //operador de indice
        char& operator [](size_t index)noexcept{return s_[index];}
        char& operator[](size_t index)const noexcept{return s_[index];}
        char& at(size_t );
        char& at(size_t )const;

        //Método de subcadena
        Cadena substr(unsigned , size_t)const;
        //declaramos el destructor de la cadena
        ~Cadena();
        
        private:
        static char vacia[1]; //vacia = char [1] = '\0';
        size_t tam_; //tamaño de la cadena de char (num caracteres de la misma)
        char* s_; //puntero a char
        
};
Cadena operator + (const Cadena& , const Cadena& )noexcept; //concatenación de cadenas (nueva cadena resultante)
//Operadores lógicos
bool operator == (const Cadena& , const Cadena& )noexcept;
bool operator != (const Cadena& , const Cadena& )noexcept;
bool operator < (const Cadena& , const Cadena& )noexcept;
bool operator <= (const Cadena& , const Cadena& )noexcept;
bool operator > (const Cadena& , const Cadena& )noexcept;
bool operator >= (const Cadena& , const Cadena& )noexcept;


#endif // !CADENA_HPP
/*
Hecho por: Jose Luis Venega Sánchez*/