#ifndef DICCIONARIO_HPP
#define DICCIONARIO_HPP
#include <iostream>
#include "listaenla.hpp"
#include <string.h>
using namespace std;
class Diccionario{
    public:
        Diccionario(){}
        void setTraduccion(string,string);
        void deleTraduccion(string,string);
        bool esCorrecta(string, string)const;
        Lista<string> getTraducciones(string)const;
        ~Diccionario();
    private:
        struct Inglesa{
            string nombre_;
            Lista<string>Spanish;
            Inglesa(const string n = " "):nombre_(n){}
        };
        Lista<Inglesa>diccionario;
        typedef Lista<Inglesa>::posicion posicion;
        typedef Lista<string>::posicion posicionesp;
        posicion buscarInglesa(string)const;
};
Diccionario::posicion Diccionario::buscarInglesa(string palabra)const{
    //vamos a buscar la palabra inglesa en el diccionario
    posicion p = diccionario.primera();
    while(p!=diccionario.fin()&&diccionario.elemento(p).nombre_!=palabra){
        p = diccionario.siguiente(p);
    }
    return p;
}

void Diccionario::setTraduccion(string pI,string pE){
    //comprobamos que la palabra inglesa existe
    posicion p = buscarInglesa(pI);
    bool insertado = false;
    if(p == diccionario.fin()){ //NO existe
        //Hay que insertar ordenamente
        posicion q = diccionario.primera();
        while(q!=diccionario.fin()){
            if(diccionario.elemento(q).nombre_ < pI){ //arroz - agua 
                diccionario.insertar(pI,q);
                insertado = true;
            }
            p = diccionario.siguiente(p);
        }
        if(!insertado){
            diccionario.insertar(pI,diccionario.fin());
        }
        diccionario.elemento(q).Spanish.insertar(pE, diccionario.elemento(q).Spanish.fin());
    }else{//Existe
        diccionario.elemento(p).Spanish.insertar(pE,diccionario.elemento(p).Spanish.fin());
    }
}

void Diccionario::deleTraduccion(string pI, string pE){
    //buscamos la palabra inglesa
    posicion p = buscarInglesa(pI);
    if(p!=diccionario.fin()){ //Existe la palabra inglesa en el diccionario
        //buscamos la traduccion a eliminar
        posicionesp q = diccionario.elemento(p).Spanish.primera();
        while(q!=diccionario.elemento(p).Spanish.fin()){
            if(diccionario.elemento(p).Spanish.elemento(q) == pE){
                diccionario.elemento(p).Spanish.eliminar(q);
            }
            q = diccionario.elemento(p).Spanish.siguiente(q);
        }
    }
}
bool Diccionario::esCorrecta(string pI, string pE)const{
    //Vamos a comprobar si la traduccion es correcta
    //buscamos la palabra inglesa
    posicion p = buscarInglesa(pI);
    bool correcta = false;
    if(p!=diccionario.fin()){ //Hemos encontrado la palabra inglesa
        //vamos a consultar si la traduccion es correcta
        posicionesp q = diccionario.elemento(p).Spanish.primera();
        while(q!=diccionario.elemento(p).Spanish.fin()){
            if(diccionario.elemento(p).Spanish.elemento(q) == pE){
                correcta = true;
            }
            q = diccionario.elemento(p).Spanish.siguiente(q);
        }
        return correcta;  
    } else return correcta;//devuelve false si no se encuentra la palabra inglesa.
}

Lista<string> Diccionario::getTraducciones(string palabra)const{
    //Buscamos la palabra inglesa
    posicion p = buscarInglesa(palabra);
    if(p!=diccionario.fin()){ //Existe, devuelvo todas las traducciones
       Lista<string>copia(diccionario.elemento(p).Spanish);
       return copia;
    }else{
        Lista<string>lista;//Si no se encuentra nada devuelve vacío 
        return lista;
    }
}

Diccionario::~Diccionario(){
    posicion p = diccionario.primera();
    while(p!=diccionario.fin()){
        diccionario.elemento(p).Spanish.~Lista();
        p = diccionario.siguiente(p);
    }
    diccionario.~Lista();
}

#endif // !DICCIONARIO_HPP
