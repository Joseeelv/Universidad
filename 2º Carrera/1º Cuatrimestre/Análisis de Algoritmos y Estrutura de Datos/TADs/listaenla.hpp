// clase Lista genérica de capacidad ilimitada.
// Después de una inserción o eliminación en una
// posición p, las variables externas de tipo posición
// posteriores a p continúan representado las
// posiciones de los mismos elementos.
#ifndef LISTA_ENLA_H
#define LISTA_ENLA_H
#include <cstddef> // size_t
#include <cassert>
template <typename T>
class Lista
{
    struct nodo; // Declaración adelantada privada
public:
    typedef nodo *posicion; // Posición de un elemento
    Lista();                // Constructor, req. ctor. T()
    bool vacia() const;
    size_t tama() const;
    void insertar(const T &x, posicion p);
    void eliminar(posicion p);
    const T &elemento(posicion p) const; // Lec. elto. en Lista const
    T &elemento(posicion p);             // Lec/Esc elto. en Lista no=const
    posicion siguiente(posicion p) const;
    posicion anterior(posicion p) const;
    posicion primera() const;
    posicion fin() const;               // Posición después del último
    Lista(const Lista &Lis);            // Ctor. de copia, req. ctor. T()
    Lista &operator=(const Lista &Lis); // Asig. de listas
    ~Lista();                           // Destructor
private:
    struct nodo
    {
        T elto;
        nodo *sig;
        nodo(const T &e = T(), nodo *p = nullptr) : elto(e), sig(p) {}
    };
    nodo *L;  // Lista enlazada circular con cabecera, ptro. al último
    size_t n; // Longitud de la lista
    void copiar(const Lista &Lis);
};
template <typename T>
inline Lista<T>::Lista() : L(new nodo), // Crear cabecera
                           n(0)
{
    L->sig = L; // Estructura circular
}
template <typename T>
inline bool Lista<T>::vacia() const
{
    return n == 0; // Alternativa: return primera() == n();
}
template <typename T>
inline size_t Lista<T>::tama() const
{
    return n;
}
template <typename T>
inline void Lista<T>::insertar(const T &x, posicion p)
{
    p->sig = new nodo(x, p->sig);
    if (p == fin())
        L = p->sig; // Nuevo último
    ++n;
}
template <typename T>
inline void Lista<T>::eliminar(posicion p)
{
    assert(p != fin());
    posicion q = p->sig;
    if (q == fin())
        L = p; // El nuevo último es el penúltimo
    p->sig = q->sig;
    delete q;
    --n;
}
template <typename T>
inline const T &Lista<T>::elemento(posicion p) const
{
    assert(p != fin());
    return p->sig->elto;
}
template <typename T>
inline T &Lista<T>::elemento(posicion p)
{
    assert(p != fin());
    return p->sig->elto;
}
template <typename T>
inline typename Lista<T>::posicion Lista<T>::siguiente(posicion p) const
{
    assert(p != fin());
    return p->sig;
}
template <typename T>
typename Lista<T>::posicion Lista<T>::anterior(posicion p) const
{
    assert(p != primera());
    posicion q = primera();
    while (q->sig != p)
        q = q->sig;
    return q;
}
template <typename T>
inline typename Lista<T>::posicion Lista<T>::primera() const
{
    return L->sig;
}
template <typename T>
inline typename Lista<T>::posicion Lista<T>::fin() const
{
    return L;
}
// Constructor de copia
template <typename T>
Lista<T>::Lista(const Lista &Lis){
    copiar(Lis);
}
// Asignación de listas
template <typename T>
Lista<T> &Lista<T>::operator=(const Lista &Lis)
{
    if (this != &Lis)
    { // Evitar autoasignación
        while (!vacia())
            eliminar(primera());
        copiar(Lis);
    }
    return *this;
}
// Destructor: vacía la lista y destruye el nodo cabecera
template <typename T>
Lista<T>::~Lista()
{
    nodo *p;
    while (L != L->sig)
    {
        p = L->sig;
        L->sig = p->sig;
        delete p;
    }
    delete L;
}
// Método privado
template <typename T>
void Lista<T>::copiar(const Lista &Lis)
// Pre: *this está vacía.
// Post: *this es copia de Lis.
{
    for (nodo *p = Lis.L->sig; p != Lis.L; p = p->sig, ++n)
        L = L->sig = new nodo(p->sig->elto, L->sig);
}
#endif // LISTA_ENLA_H