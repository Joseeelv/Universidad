#ifndef CADENA_HPP_
#define CADENA_HPP_

//Incluimos las librerías
#include <iostream>
#include <cstring>
#include <iterator>

class Cadena{
    public:
        //Por defecto, una cadena vacía = contiene el caracter terminador
        explicit Cadena(size_t tam = 0, char c = ' ');
        //Tenemos que definir el constructor de copia debido a que estamos haciendo uso de mem dinamica
        Cadena(const Cadena& );
        Cadena(const char*);
        Cadena(Cadena&&);
        //Si hacemos ctor de copia debemos de hacer operador de asignación por copia
        Cadena operator = (const Cadena& );
        Cadena operator =(const char*);
        Cadena operator = (Cadena&& );
        //conversion a cadena de bajo nivel (observadora y modificadora)
        explicit operator const char*()const noexcept{return s_;}
        
        //método observador -> devuelve el num de caracteres de una cadena
        size_t length() const noexcept{return tam_;}
        //Operadores aritmeticos
        Cadena& operator += (const Cadena& )noexcept; //concatenación de cadenas (misma cadena resultante)
        //operador de indice
        char& operator [](size_t index){return s_[index];}
        char& operator[](size_t index)const{return s_[index];}
        char& at(size_t );
        char& at(size_t )const;

        //Método de subcadena
        Cadena substr(size_t , size_t)const;

        //Iteradores de la clase

        typedef char* iterator;
        typedef const char* const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin()const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator crbegin()const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;
        const_reverse_iterator crend()const noexcept;
        const_reverse_iterator rend()const noexcept;
        reverse_iterator rend() noexcept;
        //declaramos el destructor de la cadena
        ~Cadena();
        
        private:
        static char vacia[1]; //vacia = char [1] = '\0';
        char* s_; //puntero a char
        size_t tam_; //tamaño de la cadena de char (num caracteres de la misma)
        
};
Cadena operator + (const Cadena& , const Cadena& )noexcept; //concatenación de cadenas (nueva cadena resultante)
//Operadores lógicos
bool operator == (const Cadena& , const Cadena& )noexcept;
bool operator != (const Cadena& , const Cadena& )noexcept;
bool operator < (const Cadena& , const Cadena& )noexcept;
bool operator <= (const Cadena& , const Cadena& )noexcept;
bool operator > (const Cadena& , const Cadena& )noexcept;
bool operator >= (const Cadena& , const Cadena& )noexcept;

//Operadores de inserción y extracción de flujo
std::ostream& operator << (std::ostream& , const Cadena&)noexcept;
std::istream& operator >>(std::istream&, Cadena&)noexcept;

//Inclusión de los iteradores
inline Cadena::iterator Cadena::begin() noexcept { return s_; }
inline Cadena::const_iterator Cadena::begin() const noexcept { return s_; }
inline Cadena::const_iterator Cadena::cbegin() const noexcept { return s_; }
inline Cadena::iterator Cadena::end() noexcept { return s_ + tam_; }
inline Cadena::const_iterator Cadena::end() const noexcept { return s_ + tam_; }
inline Cadena::const_iterator Cadena::cend() const noexcept { return s_ + tam_; }
inline Cadena::reverse_iterator Cadena::rbegin() noexcept { return reverse_iterator(end()); }
inline Cadena::const_reverse_iterator Cadena::rbegin() const noexcept { return const_reverse_iterator(end()); }
inline Cadena::const_reverse_iterator Cadena::crbegin() const noexcept { return const_reverse_iterator(end()); }
inline Cadena::reverse_iterator Cadena::rend() noexcept { return reverse_iterator(begin()); }
inline Cadena::const_reverse_iterator Cadena::rend() const noexcept { return const_reverse_iterator(begin()); }
inline Cadena::const_reverse_iterator Cadena::crend() const noexcept { return const_reverse_iterator(begin()); }

//codigo hash Para P2 y ss .
// Especialización de la plantilla std :: hash<Key> para definir la función hash a usar
// en contenedores desordenados de Cadena, unordered_[set|map|multiset|multimap].
namespace std{ //Estaremos dentro del espacio de nombres std
    template <> // Es una especializaci ón de una plantilla para Cadena.
    struct hash <Cadena>{
        size_t operator() (const Cadena& cad) const //el operador funcion
        {
            hash<string> hs;
            auto p{(const char*)(cad)};
            string s{p};
            size_t res{hs(s)};
            return res;
        }
    };
}
#endif // !CADENA_HPP
/*
Hecho por: Jose Luis Venega Sánchez*/