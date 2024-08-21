#ifndef TEXTO_H
#define TEXTO_H
#include <iostream>
#include "lista.h"
//VERSION 3.0  02/9/18 TDI
using namespace std;
class Texto{
   public:
       typedef Lista<char> Linea;
       Texto(Lista<Linea> texto): t(texto){}
       void MostrarTexto();
   private:
       Lista<Linea> t;
};
void Texto::MostrarTexto(){
    Lista<Linea>::posicion p= t.primera();
    while(p!=t.fin()){
        bool imprimir= true;
        Linea& lin= t.elemento(p);
        Linea::posicion l= lin.primera();
        while(l!=lin.fin()){
            if(lin.elemento(l)=='#')
               imprimir= false;
            l= lin.siguiente(l);
        }
        if(imprimir=true){
            l= lin.primera();
            while(l!=lin.fin()){
                if(lin.elemento(l)=='@'){
                       while(lin.elemento(l)=='@')
                       lin.eliminar(l);
                lin.eliminar(lin.anterior(l))
                l=lin.anterior(l);
                }
                cout<< lin.elemento(l);
                l= lin.siguiente(l);
                }
            p= t.siguiente(p);
            if(p!=t.fin())
               cout<<endl;
            }else
           t.eliminar(p);

    }

}

#endif // TEXTO_H
