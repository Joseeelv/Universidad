#ifndef TADCOLADINAMICA_H_INCLUDED
#define TADCOLADINAMICA_H_INCLUDED
#include <cassert>

template <typename T> class ColaD {
    public:
        ColaD(); // constructor
        ColaD(const ColaD<T>& C); // ctor. de copia
        ColaD<T>& operator =(const ColaD<T>& C); // asignación de colas
        bool vacia() const;
        const T& frente() const;
        void pop();
        void push(const T& x);
        ~ColaD(); // destructor

    private:
        struct nodo {
            T elto;
            nodo* sig;
            nodo(const T& e, nodo* p = 0): elto(e), sig(p) {}
        };
        nodo *inicio, *fin; // extremos de la cola
        void copiar(const ColaD<T>& C);
        };

        // Método privado
template <typename T>
void ColaD<T>::copiar(const ColaD<T>& C) {
    if (C.inicio) { // C no está vacía
        // Copiar el primer elto.
        inicio = fin = new nodo(C.inicio->elto);
        // Copiar el resto de elementos hasta el ﬁnal de la cola.
        for (nodo *p = C.inicio->sig; p; p = p->sig) {
            fin->sig = new nodo(p->elto);
            fin = fin->sig;
        }
    }
}

template <typename T> inline ColaD<T>::ColaD() : inicio(0), fin(0) {}

template <typename T> inline ColaD<T>::ColaD(const ColaD<T>& C) : inicio(0), fin(0) {
    copiar(C);
}

template <typename T> inline ColaD<T>& ColaD<T>::operator =(const ColaD<T>& C) {
    if (this != &C) { // evitar autoasignación
        this->~ColaD(); // vaciar la cola actual
        copiar(C);
    }
    return *this;
}

template <typename T> inline bool ColaD<T>::vacia() const {
    return (inicio == 0);
}

template <typename T> inline const T& ColaD<T>::frente() const {
    assert(!vacia());
    return inicio->elto;
}

template <typename T> inline void ColaD<T>::pop() {
    assert(!vacia());
    nodo* p = inicio;
    inicio = p->sig;
    if (!inicio) fin = 0;
    delete p;
}

template <typename T> inline void ColaD<T>::push(const T& x) {
    nodo* p = new nodo(x);
    if (inicio == 0) // cola vacía
        inicio = fin = p;
    else fin = fin->sig = p;
}

// Destructor: vacía la cola
template <typename T> ColaD<T>::~ColaD() {
    nodo* p;
    while (inicio) {
        p = inicio->sig;
        delete inicio;
        inicio = p;
    }
    fin = 0;
}

#endif // TADCOLADINAMICA_H_INCLUDED
