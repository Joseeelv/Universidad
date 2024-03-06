#ifndef EJERCICIO3_H
#define EJERCICIO3_H

#include <cassert>

template <typename telemento> class bicolaD{
    public:
    bicolaD(); //constructor
    bicolaD(const bicolaD<telemento>& C);
    bicolaD<telemento> & operator =(const bicolaD<telemento>&C); //operador de asignacion de colas
    bool vacia() const;//comprueba que la bicola está vacía
    const telemento& frenteizquierda() const;
    const telemento& frentederecha() const;

    void pushizq(const telemento& x); //meter elementos porla izquierda
    void popizq(); //eliminar elementos de la izq
    void pushdrc(const telemento& x); //meter elementos por la derecha
    void popdrc(); //eliminar elementos de la derecha
    ~bicolaD(); //destructor

    private:
    struct nodo{
        telemento elemento;
        nodo* sig;
        nodo* ant;
        nodo(const telemento& e, nodo* s=0, nodo* a=0): elemento(e), sig(s),ant(a){}
    };
    nodo *izq, *drc; //punteros por la izq y derecha de los nodos
    void copiar(const bicolaD<telemento>& C);
};

//Metodos privados
template <typename telemento>  void bicolaD<telemento>::copiar(const bicolaD<telemento>&C){
    if(C.izq)//cola no vacía

    //copia del primer elemento
    izq=drc=new nodo(C.izq->elemento);

    //copia el resto de elementos hasta el final de la cola
    for(nodo *p = C.izq->sig; p; p=p->sig){
        drc->sig = new nodo(C.drc.elemento);
        drc =drc->sig;
    }
}

//inicializamos constructor
template <typename telemento> inline bicolaD<telemento>::bicolaD() : izq(0),drc(0){}
//inicializamos constructor de copia
template <typename telemento> inline bicolaD<telemento>::bicolaD(const bicolaD<telemento>& C) : izq(0),drc(0){
    copiar(C);
}


template <typename telemento> inline bicolaD<telemento>& bicolaD<telemento>::operator=(const bicolaD<telemento>&C){
    if(this != &C){ //evitamos la autoasignacion
        this->~bicolaD(); //vaciamos la cola actual
        copiar(C);
    }
    return *this; 
}

template <typename telemento> inline bool bicolaD<telemento>::vacia()const{
    return(izq==drc==0);
}

template <typename telemento> inline const telemento& bicolaD<telemento>::frenteizquierda()const{
    assert(!vacia());//comprobamos si la cola no está vacía "precondicion"
    return izq.elemento;
}

template <typename telemento> inline const telemento& bicolaD<telemento>::frentederecha() const{
    assert(!vacia());
    return drc.elemento;
}

template <typename telemento> inline void bicolaD<telemento>::pushizq(const telemento& x){
    nodo *p = new nodo(x);
    if(drc==0){ //bicola vacia
    drc=izq=p;
    }else{
        p->ant=0;
        p->sig=izq;
        izq=izq->ant=p;
    }
}

template <typename telemento> inline void bicolaD<telemento>::popizq(){
    assert(!vacia()); //comprobamos que no está vacia la bicola
    nodo* p= izq;
    izq=izq->sig;

    if(!izq) drc=0;
    delete p;
}

template <typename telemento> inline void bicolaD<telemento>::pushdrc(const telemento& C){
    nodo *p = new nodo(x);
    if(izq==0){//bicola vacia
        izq=drc=0;
    }else{
        p->sig=0;
        p->ant=drc;
        drc=drc->sig=p;
    }

}

template <typename telemento> inline void bicolaD<telemento>::popdrc(){
    assert(!vacia);//comprobamos que no este vacia la bicola
    nodo *p=drc;
    drc=drc->ant;

    if(!drc) izq=0;
    delete p;
}

//Destructor de la bicola "lo hace recorriendo la bicola de izq a drch"
template <typename telemento> bicolaD<telemento>::~bicolaD(){
    nodo *p;
    while(izq){
        p=p->sig;
        delete izq;
        izq=p;
    }
    drc=0;
}

#endif