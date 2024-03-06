#ifndef AGEN_H
#define AGEN_H
#include <cassert>
template <typename T>
class Agen
{
    struct celda; // Declaración adelantada privada
public:
    typedef celda *nodo;
    static const nodo NODO_NULO;
    Agen(); // Constructor
    void insertarRaiz(const T &e);
    void insertarHijoIzqdo(nodo n, const T &e);
    void insertarHermDrcho(nodo n, const T &e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHermDrcho(nodo n);
    void eliminarRaiz();
    const T &elemento(nodo n) const; // Lectura en Agen const
    T &elemento(nodo n);             // Lectura/escritura en Agen no-const
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hermDrcho(nodo n) const;

    Agen(const Agen<T> &a);               // Ctor. de copia
    Agen<T> &operator=(const Agen<T> &a); // Asignación de árboles
    ~Agen();                              // Destructor
private:
    struct celda
    {
        T elto;
        nodo padre, hizq, heder;
        celda(const T &e, nodo p = NODO_NULO) : elto(e),
                                                padre(p), hizq(NODO_NULO), heder(NODO_NULO) {}
    };
    nodo r; // nodo raíz del árbol
    void destruirNodos(nodo &n);
    nodo copiar(nodo n);
};
/* Definición del nodo nulo */
template <typename T>
const typename Agen<T>::nodo Agen<T>::NODO_NULO(nullptr);
/*--------------------------------------------------------*/ /* Métodos públicos */ /*--------------------------------------------------------*/ template <typename T>
inline Agen<T>::Agen() : r(NODO_NULO) {}
template <typename T>
inline void Agen<T>::insertarRaiz(const T &e)
{
    assert(r == NODO_NULO); // Árbol vacío.
    r = new celda(e);
}

template <typename T>
inline void Agen<T>::insertarHijoIzqdo(nodo n, const T &e)
{
    assert(n != NODO_NULO);
    nodo hizqdo = n->hizq; // Hijo izqdo. actual.
    n->hizq = new celda(e, n);
    n->hizq->heder = hizqdo; // El actual hijo izqdo. se convierte en
                             // hermano drcho. del nuevo hijo.
}
template <typename T>
inline void Agen<T>::insertarHermDrcho(nodo n, const T &e)
{
    assert(n != NODO_NULO);
    assert(n != r);          // n no es la raíz.
    nodo hedrcho = n->heder; // Hermano drcho. actual
    n->heder = new celda(e, n->padre);
    n->heder->heder = hedrcho; // El actual hermano drcho. se convierte
                               // en hermano drcho. del nuevo.
}

template <typename T>
inline void Agen<T>::eliminarHijoIzqdo(nodo n)
{
    nodo hizqdo;
    assert(n != NODO_NULO);
    hizqdo = n->hizq;
    assert(hizqdo != NODO_NULO);       // Existe hijo izqdo.
    assert(hizqdo->hizq == NODO_NULO); // Hijo izqdo. es hoja.
    // El hermano drcho. pasa a ser el nuevo hijo izqdo.
    n->hizq = hizqdo->heder;
    delete hizqdo;
}

template <typename T>
inline void Agen<T>::eliminarHermDrcho(nodo n)
{
    nodo hedrcho;
    assert(n != NODO_NULO);
    hedrcho = n->heder;
    assert(hedrcho != NODO_NULO);       // Existe hermano drcho.
    assert(hedrcho->hizq == NODO_NULO); // Hermano drcho. es hoja.
                                        // El hermano del hermano se convierte en el
                                        // nuevo hermano drcho. de n.
    n->heder = hedrcho->heder;
    delete hedrcho;
}

template <typename T>
inline void Agen<T>::eliminarRaiz()
{
    assert(r != NODO_NULO);       // Árbol no vacío.
    assert(r->hizq == NODO_NULO); // La raíz es hoja.
    delete (r);
    r = NODO_NULO;
}

template <typename T>
inline const T &Agen<T>::elemento(nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}
template <typename T>
inline T &Agen<T>::elemento(nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::raiz() const
{
    return r;
}
template <typename T>
inline
    typename Agen<T>::nodo
    Agen<T>::padre(nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}

template <typename T>
inline
    typename Agen<T>::nodo
    Agen<T>::hijoIzqdo(nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}
template <typename T>
inline
    typename Agen<T>::nodo
    Agen<T>::hermDrcho(nodo n) const
{
    assert(n != NODO_NULO);
    return n->heder;
}

template <typename T>
inline Agen<T>::Agen(const Agen<T> &A)
{
    r = copiar(A.r); // Copiar raíz y descendientes.
}
template <typename T>
Agen<T> &Agen<T>::operator=(const Agen<T> &A)
{
    if (this != &A) // Evitar autoasignación.
    {
        destruirNodos(r); // Vaciar el árbol.
        r = copiar(A.r);  // Copiar raíz y descendientes.
    }
    return *this;
}
template <typename T>
inline Agen<T>::~Agen()
{
    destruirNodos(r); // Vaciar el árbol.
}

/*--------------------------------------------------------*/ /* Métodos privados */ /*--------------------------------------------------------*/ // Destruye un nodo y todos sus descendientes
template <typename T>
void Agen<T>::destruirNodos(nodo &n)
{
    if (n != NODO_NULO)
    {
        if (n->hizq != NODO_NULO)
        { // Destruir hermanos del hijo izqdo.
            nodo hedrcho = n->hizq->heder;
            while (hedrcho != NODO_NULO)
            {
                n->hizq->heder = hedrcho->heder;
                destruirNodos(hedrcho);
                hedrcho = n->hizq->heder;
            }
            destruirNodos(n->hizq); // Destruir el hijo izqdo.
        }
        delete (n);
        n = NODO_NULO;
    }
}

// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Agen<T>::nodo Agen<T>::copiar(nodo n)
{
    nodo m = NODO_NULO;
    if (n != NODO_NULO)
    {
        m = new celda(n->elto); // Copiar n.
        if (n->hizq != NODO_NULO)
        {                              // n tiene descendientes.
            m->hizq = copiar(n->hizq); // Copiar primer subárbol.m->hizq->padre = m;
            // Copiar el resto de subárboles.
            nodo hijo = m->hizq;           // Último subárbol copiado.
            nodo hedrcho = n->hizq->heder; // Siguiente subárbol a copiar
            while (hedrcho != NODO_NULO)
            {
                hijo = hijo->heder = copiar(hedrcho);
                hijo->padre = m;
                hedrcho = hedrcho->heder;
            }
        }
    }
    return m;
}
#endif // AGEN_H