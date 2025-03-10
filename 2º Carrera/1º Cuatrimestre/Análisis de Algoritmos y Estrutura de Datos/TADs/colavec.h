#ifndef COLA_VEC_H
#define COLA_VEC_H
#include <cstddef> // size_t
#include <cassert>
template <typename T>
class Cola
{
public:
    explicit Cola(size_t tamaMax); // Constructor, req. ctor. T()
    bool vacia() const;
    size_t tama() const;
    size_t tamaMax() const; // Requerida por la implementación
    const T &frente() const;
    void pop();
    void push(const T &x);
    Cola(const Cola &C);            // Ctor. de copia, req. ctor. T()
    Cola &operator=(const Cola &C); // Asig., req. ctor. T()
    ~Cola();                        // Destructor
private:
    T *elementos; // Vector de elementos
    size_t Lmax,  // Tamaño del vector
        inicio,   // Posición del frente
        n_eltos;  // Tamaño de la cola
};
template <typename T>
inline Cola<T>::Cola(size_t tamaMax) : elementos(new T[tamaMax]),
                                       Lmax(tamaMax),
                                       inicio(0),
                                       n_eltos(0)
{
}
template <typename T>
inline bool Cola<T>::vacia() const
{
    return n_eltos == 0;
}
template <typename T>
inline size_t Cola<T>::tama() const
{
    return n_eltos;
}
template <typename T>
inline size_t Cola<T>::tamaMax() const
{
    return Lmax;
}
template <typename T>
inline const T &Cola<T>::frente() const
{
    assert(!vacia());
    return elementos[inicio];
}
template <typename T>
inline void Cola<T>::pop()
{
    assert(!vacia());
    inicio = (inicio + 1) % Lmax;
    --n_eltos;
}
template <typename T>
inline void Cola<T>::push(const T &x)
{
    assert(n_eltos < Lmax);
    elementos[(inicio + n_eltos) % Lmax] = x;
    ++n_eltos;
}
// Constructor de copia
template <typename T>
Cola<T>::Cola(const Cola &C) : elementos(new T[C.Lmax]),
                               Lmax(C.Lmax),
                               inicio(0),
                               n_eltos(C.n_eltos)
{
    for (size_t i = 0; i < n_eltos; ++i) // Copiar elementos
        elementos[i] = C.elementos[(C.inicio + i) % Lmax];
}
// Asignación entre colas
template <typename T>
Cola<T> &Cola<T>::operator=(const Cola &C)
{
    if (this != &C)
    { // Evitar autoasignación
        // Destruir el vector y crear uno nuevo si es necesario
        if (Lmax != C.Lmax)
        {
            T *p = elementos;
            elementos = new T[C.Lmax]; // Si new falla, *this no cambia.
            Lmax = C.Lmax;
            delete[] p;
        }
        inicio = 0;
        n_eltos = C.n_eltos;
        for (size_t i = 0; i < n_eltos; ++i) // Copiar elementos
            elementos[i] = C.elementos[(C.inicio + i) % Lmax];
    }
    return *this;
}
// Destructor
template <typename T>
inline Cola<T>::~Cola()
{
    delete[] elementos;
}
#endif // COLA_VEC_H