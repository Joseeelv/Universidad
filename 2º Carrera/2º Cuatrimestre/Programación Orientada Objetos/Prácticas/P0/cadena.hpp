#ifndef CADENA_HPP_
#define CADENA_HPP_

//Incluimos las librerías
#include <iostream>

class Cadena{
    public:
        //Por defecto, una cadena vacía = contiene el caracter terminador
        explicit Cadena(size_t tam = 0, char = ' ');
        
        //Tenemos que definir el constructor de copia debido a que estamos haciendo uso de mem dinamica
        Cadena(const Cadena& );
        Cadena (const char*);
        //Si hacemos ctor de copia debemos de hacer operador de asignación por copia
        Cadena& operator = (const Cadena& );
        Cadena& operator =(const char*);
        //conversion a cadena de bajo nivel (observadora y modificadora)
        explicit operator const char*()const{return s_;}
        explicit operator const char*();
        
        //método observador -> devuelve el num de caracteres de una cadena
        size_t length() const{return tam_;}
        //Operadores aritmeticos
        Cadena& operator += (const Cadena& ); //concatenación de cadenas (misma cadena resultante)
        //operador de indice
        char& operator [](size_t index){return s_[index];}
        char& operator[](size_t index)const{return s_[index];}
        char& at(size_t );
        char& at(size_t )const;

        //Método de subcadena
        Cadena& substr(unsigned , size_t);
        //declaramos el destructor de la cadena
        ~Cadena();
        private:
        const char vacia[1]; //vacia = char [1] = \0;
        size_t tam_; //tamaño de la cadena de char (num caracteres de la misma)
        char* s_; //puntero a char
        
};
Cadena operator + (const Cadena& , const Cadena& ); //concatenación de cadenas (nueva cadena resultante)
//Operadores lógicos
bool operator == (const Cadena& , const Cadena& );
bool operator != (const Cadena& , const Cadena& );
bool operator < (const Cadena& , const Cadena& );
bool operator <= (const Cadena& , const Cadena& );
bool operator > (const Cadena& , const Cadena& );
bool operator >= (const Cadena& , const Cadena& );


#endif // !CADENA_HPP
/*
Hecho por: Jose Luis Venega Sánchez*/