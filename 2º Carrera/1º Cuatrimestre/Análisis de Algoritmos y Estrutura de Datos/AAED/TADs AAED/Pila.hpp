#ifndef TADPILADINAMICA_H
#define TADPILADINAMICA_H
#include <cassert>

template <typename tElemento> class PilaD {
public:
    explicit PilaD();                   /*Constructor*/
    PilaD(const PilaD<tElemento>& P);   /*Constructor de copia*/
    PilaD<tElemento>& operator= (const PilaD<tElemento>& P); //Asignaci�n entre pilas
    bool vacia() const;
    const tElemento& tope() const;
    tElemento pop();
    void push(const tElemento& x);
    ~PilaD(); /*Destructor*/
private:
    struct nodo {
        tElemento elto;
        nodo* sig;
        nodo (const tElemento& e, nodo* p = 0): elto(e), sig(p) {}
    };
    nodo* tope_; //Posici�n del tope
    void copiar(const PilaD<tElemento>& P);
};

template <typename tElemento>
inline PilaD<tElemento>::PilaD() : tope_(0) {}

template <typename tElemento>
PilaD<tElemento>::PilaD(const PilaD<tElemento>& P) : tope_(0)
{
    copiar(P);
}

template <typename tElemento>
PilaD<tElemento>& PilaD<tElemento>::operator= (const PilaD<tElemento>& P)
{
    if(this != &P) {    //Evitar autoasignaci�n
        this->~PilaD();  //Vaciar la pila actual
        copiar(P);
    }
    return *this;
}

template <typename tElemento>
inline bool PilaD<tElemento>::vacia() const
{
    return (!tope_);
}

template <typename tElemento>
inline const tElemento& PilaD<tElemento>::tope() const
{
    assert(!vacia());
    return tope_->elto;
}

template <typename tElemento>
inline tElemento PilaD<tElemento>::pop()
{
    assert(!vacia());
    nodo* p = tope_;
    tope_ = p->sig;
    tElemento eltoAux = p->elto;
    delete p;
    return eltoAux;
}

template <typename tElemento>
inline void PilaD<tElemento>::push(const tElemento& x)
{
    tope_ = new nodo(x, tope_);
}

//Destructor: vac�a la pila
template <typename tElemento>
PilaD<tElemento>::~PilaD()
{
    nodo* p;
    while(tope_) {
        p = tope_->sig;
        delete tope_;
        tope_ = p;
    }
}

template <typename tElemento> void PilaD<tElemento>::copiar(const PilaD<tElemento>& P){
    if (!P.vacia()) {
        tope_ = new nodo(P.tope()); //Copiar el primer elto
        //Copiar el resto de elementos hasta el fondo de la pila
        nodo* p = tope_; //Recorre la pila destino
        nodo* q = P.tope_->sig; //2� nodo, recorre la pila origen
        while(q) {
            p->sig = new nodo (q->elto);
            p = p->sig;
            q = q->sig;
        }
    }
}

#endif // TADPILADINAMICA_H
