#ifndef ABIN_VEC0_H
#define ABIN_VEC0_H
#include <cassert>
#include <iostream>
template <typename T>
class Abin
{
public:
    typedef size_t nodo; // Índice del vector entre 0 y maxNodos-
    static const nodo NODO_NULO;
    explicit Abin(size_t maxNodos); // Ctor., requiere ctor. T()
    void insertarRaiz(const T &e);
    void insertarHijoIzqdo(nodo n, const T &e);
    void insertarHijoDrcho(nodo n, const T &e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHijoDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;
    const T &elemento(nodo n) const; // Lec. en Abin cons
    T &elemento(nodo n);             // Lec/Esc. en Abin no-const
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoDrcho(nodo n) const;
    Abin(const Abin<T> &A);               // Ctor. copia, req ctor T(
    Abin<T> &operator=(const Abin<T> &A); // Asig. de árboles
    ~Abin();                              // Destructor3
    size_t profundidad_nodo(nodo n) const;
    size_t altura_nodo(nodo n) const;

private:
    struct celda
    {
        T elto;
        nodo padre, hizq, hder;
    };
    celda *nodos;    // Vector de nodos
    size_t maxNodos; // Tamaño del vector
    size_t numNodos; // Número de nodos del árbol
};
/* Definición del nodo nulo */
template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(SIZE_MAX);
template <typename T>
inline Abin<T>::Abin(size_t maxNodos) : nodos(new celda[maxNodos]),
                                        maxNodos(maxNodos),
                                        numNodos(0)
{
}
template <typename T>
inline void Abin<T>::insertarRaiz(const T &e)
{
    assert(numNodos == 0); // Árbol vacío
    numNodos = 1;
    nodos[0].elto = e;
    nodos[0].padre = NODO_NULO;
    nodos[0].hizq = NODO_NULO;
    nodos[0].hder = NODO_NULO;
}

template <typename T>
inline void Abin<T>::insertarHijoIzqdo(nodo n, const T &e)
{
    assert(n >= 0 && n < numNodos);     // Nodo válido
    assert(nodos[n].hizq == NODO_NULO); // n no tiene hijo izqdo.assert(numNodos < maxNodos); // Árbol no lleno
    // Añadir el nuevo nodo al final de la secuencia.
    nodos[n].hizq = numNodos;
    nodos[numNodos].elto = e;
    nodos[numNodos].padre = n;
    nodos[numNodos].hizq = NODO_NULO;
    nodos[numNodos].hder = NODO_NULO;
    ++numNodos;
}

template <typename T>
inline void Abin<T>::insertarHijoDrcho(nodo n, const T &e)
{
    assert(n >= 0 && n < numNodos);     // Nodo válido
    assert(nodos[n].hder == NODO_NULO); // n no tiene hijo drcho.assert(numNodos < maxNodos); // Árbol no lleno
    // Añadir el nuevo nodo al final de la secuencia.
    nodos[n].hder = numNodos;
    nodos[numNodos].elto = e;
    nodos[numNodos].padre = n;
    nodos[numNodos].hizq = NODO_NULO;
    nodos[numNodos].hder = NODO_NULO;
    ++numNodos;
}
template <typename T>
void Abin<T>::eliminarHijoIzqdo(nodo n)
{
    nodo hizqdo;
    assert(n >= 0 && n < numNodos); // Nodo válido
    hizqdo = nodos[n].hizq;
    assert(hizqdo != NODO_NULO); // Existe hijo izqdo. de n.assert(nodos[hizqdo].hizq == NODO_NULO && // Hijo izqdo. denodos[hizqdo].hder == NODO_NULO); // n es hoja.if (hizqdo != numNodos-1)
    {
        // Mover el último nodo a la posición del hijo izqdo.nodos[hizqdo] = nodos[numNodos-1];
        // Actualizar la posición del hijo (izquierdo o derecho)// en el padre del nodo movido.
        if (nodos[nodos[hizqdo].padre].hizq == numNodos - 1)
            nodos[nodos[hizqdo].padre].hizq = hizqdo;
        else
            nodos[nodos[hizqdo].padre].hder = hizqdo;
        // Si el nodo movido tiene hijos,
        // actualizar la posición del padre.
        if (nodos[hizqdo].hizq != NODO_NULO)
            nodos[nodos[hizqdo].hizq].padre = hizqdo;
        if (nodos[hizqdo].hder != NODO_NULO)
            nodos[nodos[hizqdo].hder].padre = hizqdo;
    }
    nodos[n].hizq = NODO_NULO;
    --numNodos;
}
template <typename T>
void Abin<T>::eliminarHijoDrcho(nodo n)
{
    nodo hdrcho;
    assert(n >= 0 && n < numNodos); // Nodo válido
    hdrcho = nodos[n].hder;
    assert(hdrcho != NODO_NULO); // Existe hijo drcho. de n.assert(nodos[hdrcho].hizq == NODO_NULO && // Hijo drcho. denodos[hdrcho].hder == NODO_NULO); // n es hoja.if (hdrcho != numNodos-1)
    {
        // Mover el último nodo a la posición del hijo drcho.nodos[hdrcho] = nodos[numNodos-1];
        // Actualizar la posición del hijo (izquierdo o derecho)// en el padre del nodo movido.
        if (nodos[nodos[hdrcho].padre].hizq == numNodos - 1)
            nodos[nodos[hdrcho].padre].hizq = hdrcho;
        else
            nodos[nodos[hdrcho].padre].hder = hdrcho;
        // Si el nodo movido tiene hijos,
        // actualizar la posición del padre.
        if (nodos[hdrcho].hizq != NODO_NULO)
            nodos[nodos[hdrcho].hizq].padre = hdrcho;
        if (nodos[hdrcho].hder != NODO_NULO)
            nodos[nodos[hdrcho].hder].padre = hdrcho;
    }
    nodos[n].hder = NODO_NULO;
    --numNodos;
}
template <typename T>
inline void Abin<T>::eliminarRaiz()
{
    assert(numNodos == 1);
    numNodos = 0;
}
template <typename T>
inline bool Abin<T>::arbolVacio() const
{
    return (numNodos == 0);
}
template <typename T>
inline const T &Abin<T>::elemento(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].elto;
}
template <typename T>
inline T &Abin<T>::elemento(nodo n)
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].elto;
}
template <typename T>
inline typename Abin<T>::nodo Abin<T>::raiz() const
{
    return (numNodos > 0) ? 0 : NODO_NULO;
}
template <typename T>
inline
    typename Abin<T>::nodo
    Abin<T>::padre(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].padre;
}
template <typename T>
inline
    typename Abin<T>::nodo
    Abin<T>::hijoIzqdo(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].hizq;
}
template <typename T>
inline
    typename Abin<T>::nodo
    Abin<T>::hijoDrcho(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].hder;
}
template <typename T>
Abin<T>::Abin(const Abin<T> &A) : nodos(new celda[A.maxNodos]),
                                  maxNodos(A.maxNodos),
                                  numNodos(A.numNodos)
{
    // Copiar el vector.
    for (nodo n = 0; n <= numNodos - 1; n++)
        nodos[n] = a.nodos[n];
}
template <typename T>
inline Abin<T>::~Abin()
{
    delete[] nodos;
}

template <typename T>
Abin<T> &Abin<T>::operator=(const Abin<T> &A)
{
    if (this != &A) // Evitar autoasignación.
    {
        // Destruir el vector y crear uno nuevo si es necesario.if (maxNodos != A.maxNodos)
        {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new celda[maxNodos];
        }
        // Copiar el vector.
        numNodos = A.numNodos;
        for (nodo n = 0; n <= numNodos - 1; n++)
            nodos[n] = A.nodos[n];
    }
    return *this;
}
template <typename T>
size_t Abin<T>::profundidad_nodo(nodo n) const
{
    if (n != 0)
        return 1 + profundidad_nodo(nodos[n].padre);
}
template <typename T>
size_t Abin<T>::altura_nodo(nodo n) const
{
    if (n == NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(altura_nodo(nodos[n].hizq), altura_nodo(nodos[n].hder));
    }
}
#endif // ABIN_VEC0_H