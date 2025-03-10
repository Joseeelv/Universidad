// listavec.h
//
// clase Lista genérica cuya capacidad (parámetro de
// entrada del constructor) puede ser distinta para
// cada objeto de la clase.
// Las variables externas de tipo posición, posteriores
// a la posición p en la que se realiza una inserción
// o eliminación, no cambian, pero sí los elementos
// que se encuentran en dichas posiciones.
#ifndef LISTA_VEC_H
#define LISTA_VEC_H
#include <cstddef> // size_t
#include <cassert>
template <typename T>
class Lista
{
public:
    typedef size_t posicion;        // Posición de un elemento
    explicit Lista(size_t tamaMax); // Constructor, req. ctor. T()
    bool vacia() const;
    size_t tama() const;
    size_t tamaMax() const; // Requerida por la implementación
    void insertar(const T &x, posicion p);
    void eliminar(posicion p);
    const T &elemento(posicion p) const; // Lec. elto. en Lista const
    T &elemento(posicion p);             // Lec/Esc elto. en Lista no=const
    posicion siguiente(posicion p) const;
    posicion anterior(posicion p) const;
    posicion primera() const;
    posicion fin() const;             // Posición después del último
    Lista(const Lista &L);            // Ctor. de copia, req. ctor. T()
    Lista &operator=(const Lista &L); // Asig, req. ctor. T()
    ~Lista();                         // Destructor
private:
    T *elementos; // Vector de elementos
    size_t Lmax,  // Tamaño del vector
        n;        // Longitud de la lista
};
// clase Lista genérica: vector pseudoestático.
// Una lista de longitud n se almacena en celdas
// consecutivas del vector, desde 0 hasta n=1.
// La posición de un elemento es el índice de la celda
// en que se almacena.
//
// Implementación de operaciones
template <typename T>
inline Lista<T>::Lista(size_t tamaMax) : elementos(new T[tamaMax]),
                                         Lmax(tamaMax),
                                         n(0)
{
}
template <typename T>
inline bool Lista<T>::vacia() const
{
    return n == 0;
}
template <typename T>
inline size_t Lista<T>::tama() const
{
    return n;
}
template <typename T>
inline size_t Lista<T>::tamaMax() const
{
    return Lmax;
}
template <typename T>
void Lista<T>::insertar(const T &x, posicion p)
{
    assert(p >= primera() && p <= fin());
    assert(tama() < tamaMax());
    // Desplazar los eltos. entre p y n() a la siguiente posición
    for (posicion q = fin(); q > p; --q)
        elementos[q] = elementos[q - 1];
    elementos[p] = x;
    ++n;
}
template <typename T>
void Lista<T>::eliminar(posicion p)
{
    assert(p >= primera() && p < fin());
    --n;
    // Desplazar los eltos. entre p+1 y n() a la posición anterior
    for (posicion q = p; q < fin(); ++q)
        elementos[q] = elementos[q + 1];
}
template <typename T>
inline const T &Lista<T>::elemento(posicion p) const
{
    assert(p >= primera() && p < fin());
    return elementos[p];
}
template <typename T>
inline T &Lista<T>::elemento(posicion p)
{
    assert(p >= primera() && p < fin());
    return elementos[p];
}
template <typename T>
inline typename Lista<T>::posicion Lista<T>::siguiente(posicion p) const
{
    assert(p >= primera() && p < fin());
    return p + 1;
}
template <typename T>
inline typename Lista<T>::posicion Lista<T>::anterior(posicion p) const
{
    assert(p > primera() && p <= fin());
    return p - 1;
}
template <typename T>
inline typename Lista<T>::posicion Lista<T>::primera() const
{
    return 0;
}
template <typename T>
inline typename Lista<T>::posicion Lista<T>::fin() const
{
    return n;
}
// Constructor de copia
template <typename T>
Lista<T>::Lista(const Lista<T> &L) : elementos(new T[L.Lmax]),
                                     Lmax(L.Lmax),
                                     n(L.n)
{ // Copiar elementos
    for (posicion p = primera(); p < fin(); ++p)
        elementos[p] = L.elementos[p];
}
// Asignación de listas
template <typename T>
Lista<T> &Lista<T>::operator=(const Lista<T> &L)
{
    if (this != &L)
    { // Evitar autoasignación
        // Destruir el vector y crear uno nuevo si es necesario
        if (Lmax != L.Lmax)
        {
            T *p = elementos;
            elementos = new T[L.Lmax]; // Si new falla, *this no cambia.
            Lmax = L.Lmax;
            delete[] p;
        }
        n = L.n;
        for (posicion p = primera(); p < fin(); ++p)
            elementos[p] = L.elementos[p];
    }
    return *this;
}
// Destructor
template <typename T>
inline Lista<T>::~Lista()
{
    delete[] elementos;
}
#endif // LISTA_VEC_H