#ifndef ABIN_VEC1_H
#define ABIN_VEC1_H
#include <cassert>
template <typename T>
class Abin
{
public:
    typedef size_t nodo; // Índice del vector,
    // entre 0 y maxNodos-1
    static const nodo NODO_NULO;
    explicit Abin(size_t maxNodos, const T &e_nulo = T());
    void insertarRaiz(const T &e);
    void insertarHijoIzqdo(nodo n, const T &e);
    void insertarHijoDrcho(nodo n, const T &e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHijoDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;

    const T &elemento(nodo n) const; // Lec. en Abin const
    T &elemento(nodo n);             // Lec/Esc. en Abin no-const
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoDrcho(nodo n) const;
    Abin(const Abin<T> &a);               // Ctor. de copia
    Abin<T> &operator=(const Abin<T> &a); // Asig. de árboles
    ~Abin();                              // Destructorprivate:
    T *nodos;                             // Vector de nodos
    size_t maxNodos;                      // Tamaño del vector
    T ELTO_NULO;                          // Marca celdas vacías
};
/* Definición del nodo nulo */
template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(SIZE_MAX);
template <typename T>
Abin<T>::Abin(size_t maxNodos, const T &e_nulo) : nodos(new T[maxNodos]),
                                                  maxNodos(maxNodos),
                                                  ELTO_NULO(e_nulo)
{
    // Marcar todas las celdas libres.
    for (nodo n = 0; n <= maxNodos - 1; n++)
        nodos[n] = ELTO_NULO;
}
template <typename T>
inline void Abin<T>::insertarRaiz(const T &e)
{
    assert(nodos[0] == ELTO_NULO); // Árbol vacío.nodos[0] = e;
}

template <typename T>
inline void Abin<T>::insertarHijoIzqdo(nodo n, const T &e)
{
    assert(n >= 0 && n <= maxNodos - 1); // Nodo válido.assert(nodos[n] != ELTO_NULO); // Nodo del árbol.assert(2*n+1 < maxNodos); // Hijo izqdo. cabe en el árbol.assert(nodos[2*n+1] == ELTO_NULO); // n no tiene hijo izqdo.nodos[2*n+1] = e;
}
template <typename T>
inline void Abin<T>::insertarHijoDrcho(nodo n, const T &e)
{
    assert(n >= 0 && n < maxNodos - 1); // Nodo válidoassert(nodos[n] != ELTO_NULO); // Nodo del árbolassert(2*n+2 < maxNodos); // Hijo drcho. cabe en el árbol.assert(nodos[2*n+2] == ELTO_NULO); // n no tiene hijo drcho.nodos[2*n+2] = e;
}

template <typename T>
inline void Abin<T>::eliminarHijoIzqdo(nodo n)
{
    assert(n >= 0 && n <= maxNodos - 1); // Nodo válido.assert(nodos[n] != ELTO_NULO); // Nodo del árbol.assert(2*n+1 < maxNodos); // Hijo izqdo. cabe en el árbol.assert(nodos[2*n+1] != ELTO_NULO); // n tiene hijo izqdo.if (4*n+4 < maxNodos) // Caben los hijos del hijo izqdo. de nassert(nodos[4*n+3] == ELTO_NULO && // Hijo izqdo. denodos[4*n+4] == ELTO_NULO); // n es hojaelse if (4*n+3 < maxNodos) //Sólo cabe h. izq. de h. izq. de nassert(nodos[4*n+3] == ELTO_NULO); //Hijo izq. de n es hojanodos[2*n+1] = ELTO_NULO;
}

template <typename T>
inline void Abin<T>::eliminarHijoDrcho(nodo n)
{
    assert(n >= 0 && n <= maxNodos - 1); // Nodo válido.assert(nodos[n] != ELTO_NULO); // Nodo del árbol.assert(2*n+2 < maxNodos); // Hijo drcho. cabe en el árbol.assert(nodos[2*n+2] != ELTO_NULO); // n tiene hijo drcho.if (4*n+6 < maxNodos) // Caben los hijos del hijo drcho. de nassert(nodos[4*n+5] == ELTO_NULO && // Hijo drcho. denodos[4*n+6] == ELTO_NULO); // n es hojaelse if (4*n+5 < maxNodos) //Sólo cabe h. izq. de h. drch de nassert(nodos[4*n+5] == ELTO_NULO); //Hijo drch de n es hojanodos[2*n+2] = ELTO_NULO;
}
template <typename T>
inline void Abin<T>::eliminarRaiz()
{
    assert(nodos[0] != ELTO_NULO); // Árbol no vacíoassert(nodos[1] == ELTO_NULO &&
nodos[2] == ELTO_NULO); // La raíz es hojanodos[0] = ELTO_NULO;
}
template <typename T>
inline bool Abin<T>::arbolVacio() const
{
    return (nodos[0] == ELTO_NULO);
}
template <typename T>
inline const T &Abin<T>::elemento(nodo n) const
{
    assert(n >= 0 && n <= maxNodos - 1); // Nodo válido.assert(nodos[n] != ELTO_NULO); // Nodo del árbol.return nodos[n];
}
template <typename T>
inline T &Abin<T>::elemento(nodo n)
{
    assert(n >= 0 && n <= maxNodos - 1); // Nodo válido.assert(nodos[n] != ELTO_NULO); // Nodo del árbol.return nodos[n];
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::raiz() const
{
    return (nodos[0] == ELTO_NULO) ? NODO_NULO : 0;
}
template <typename T>
inline
    typename Abin<T>::nodo
    Abin<T>::padre(nodo n) const
{
    assert(n >= 0 && n <= maxNodos - 1); // Nodo válido.assert(nodos[n] != ELTO_NULO); // Nodo del árbol.return (n == 0) ? NODO_NULO : (n-1)/2;
}

template <typename T>
inline
    typename Abin<T>::nodo
    Abin<T>::hijoIzqdo(nodo n) const
{
    assert(n >= 0 && n <= maxNodos - 1); // Nodo válido.assert(nodos[n] != ELTO_NULO); // Nodo del árbol.return (2*n+1 >= maxNodos || nodos[2*n+1] == ELTO_NULO) ?NODO_NULO : 2*n+1;
}
template <typename T>
inline
    typename Abin<T>::nodo
    Abin<T>::hijoDrcho(nodo n) const
{
    assert(n >= 0 && n <= maxNodos - 1); // Nodo válido.assert(nodos[n] != ELTO_NULO); // Nodo del árbol.return (2*n+2 >= maxNodos || nodos[2*n+2] == ELTO_NULO) ? NODO_NULO : 2*n+2;
}

template <typename T>
Abin<T>::Abin(const Abin<T> &A) : nodos(new T[A.maxNodos]),
                                  maxNodos(A.maxNodos),
                                  ELTO_NULO(A.ELTO_NULO)
{
    // Copiar el vector
    for (nodo n = 0; n <= maxNodos - 1; n++)
        nodos[n] = A.nodos[n];
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
        // Destruir el vector y crear uno nuevo si es necesarioif (maxNodos != A.maxNodos)
        {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new T[maxNodos];
        }
        ELTO_NULO = A.ELTO_NULO;
        // Copiar el vector.
        for (nodo n = 0; n <= maxNodos - 1; n++)
            nodos[n] = A.nodos[n];
    }
    return *this;
}
#endif // ABIN_VEC1_H