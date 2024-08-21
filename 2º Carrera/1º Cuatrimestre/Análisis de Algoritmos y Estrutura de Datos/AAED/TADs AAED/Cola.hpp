#ifndef TADCOLADINAMICA_H_INCLUDED
#define TADCOLADINAMICA_H_INCLUDED
#include <cassert>

template <typename T> class Cola {
    public:
        Cola(); // constructor
        Cola(const Cola<T>& C); // ctor. de copia
        Cola<T>& operator =(const Cola<T>& C); // asignación de colas
        bool vacia() const;
        const T& frente() const;
        void pop();
        void push(const T& x);
        ~Cola(); // destructor

    private:
        struct nodo {
            T elto;
            nodo* sig;
            nodo(const T& e, nodo* p = 0): elto(e), sig(p) {}
        };
        nodo *inicio, *fin; // extremos de la cola
        void copiar(const Cola<T>& C);
        };

        // Método privado
template <typename T>
void Cola<T>::copiar(const Cola<T>& C) {
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

template <typename T> inline Cola<T>::Cola() : inicio(0), fin(0) {}

template <typename T> inline Cola<T>::Cola(const Cola<T>& C) : inicio(0), fin(0) {
    copiar(C);
}

template <typename T> inline Cola<T>& Cola<T>::operator =(const Cola<T>& C) {
    if (this != &C) { // evitar autoasignación
        this->~Cola(); // vaciar la cola actual
        copiar(C);
    }
    return *this;
}

template <typename T> inline bool Cola<T>::vacia() const {
    return (inicio == 0);
}

template <typename T> inline const T& Cola<T>::frente() const {
    assert(!vacia());
    return inicio->elto;
}

template <typename T> inline void Cola<T>::pop() {
    assert(!vacia());
    nodo* p = inicio;
    inicio = p->sig;
    if (!inicio) fin = 0;
    delete p;
}

template <typename T> inline void Cola<T>::push(const T& x) {
    nodo* p = new nodo(x);
    if (inicio == 0) // cola vacía
        inicio = fin = p;
    else fin = fin->sig = p;
}

// Destructor: vacía la cola
template <typename T> Cola<T>::~Cola() {
    nodo* p;
    while (inicio) {
        p = inicio->sig;
        delete inicio;
        inicio = p;
    }
    fin = 0;
}

#endif // TADCOLADINAMICA_H_INCLUDED
