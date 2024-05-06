/*--------------------------------------------------------*/
/* colaenla.h                                             */
/*                                                        */
/* clase Cola de elementos del tipo genérico T y          */
/*    capacidad ilimitada.                                */
/*--------------------------------------------------------*/

#ifndef COLA_ENLA_H
#define COLA_ENLA_H
#include <cstddef>   // size_t
#include <cassert>

template <typename T> class Cola {
public:
   Cola();
   bool vacia() const;
   size_t tama() const;
   const T& frente() const;
   void pop();
   void push(const T& x);
   Cola(const Cola& C);             // Ctor. de copia
   Cola& operator =(const Cola& C); // Asignación entre colas
   ~Cola();                         // Destructor
private:
   struct nodo {
     T elto;
     nodo* sig;
     nodo(const T& e, nodo* p = nullptr) : elto(e), sig(p) {}
   };

   nodo *inicio, *fin;   // Extremos de la cola
   size_t n_eltos;       // Tamaño de la cola

   void copiar(const Cola& C);
};

/*--------------------------------------------------------*/
/* clase Cola genérica mediante celdas enlazadas.         */
/*                                                        */
/* Implementación de operaciones                          */
/*--------------------------------------------------------*/

template <typename T>
inline Cola<T>::Cola() :
   inicio(nullptr),
   // fin(nullptr), // Innecesario en esta implementación
   n_eltos(0)
{}

template <typename T>
inline bool Cola<T>::vacia() const
{ return inicio == nullptr; } // Alternativa: return n_eltos == 0;

template <typename T>
inline size_t Cola<T>::tama() const
{ return n_eltos; }

template <typename T>
inline const T& Cola<T>::frente() const
{
   assert(!vacia());
   return inicio->elto;
}

template <typename T>
inline void Cola<T>::pop()
{
   assert(!vacia());
   nodo* p = inicio;
   inicio = p->sig;
   // if (!inicio) fin = nullptr; // Innecesario en esta implementación
   delete p;
   --n_eltos;
}

template <typename T>
inline void Cola<T>::push(const T& x)
{
   if (vacia())
      inicio = fin = new nodo(x);
   else
      fin = fin->sig = new nodo(x);
   ++n_eltos;
}

// Constructor de copia
template <typename T>
inline Cola<T>::Cola(const Cola& C) : Cola()
{
   copiar(C);
}

// Asignación entre colas
template <typename T>
inline Cola<T>& Cola<T>::operator =(const Cola& C)
{
   if (this != &C) {   // Evitar autoasignación
      this->~Cola();   // Vaciar la cola actual
      copiar(C);
   }
   return *this;
}

// Destructor: vacía la cola
template <typename T>
Cola<T>::~Cola()
{
   nodo* p;
   while (inicio) {
      p = inicio->sig;
      delete inicio;
      inicio = p;
   }
   // fin = nullptr; // Innecesario en esta implementación
   n_eltos = 0;
}

// Método privado
template <typename T>
void Cola<T>::copiar(const Cola& C)
// Pre: *this está vacía.
// Post: *this es copia de C.
{
   if (!C.vacia()) {
       // Copiar el primer elto.
      inicio = fin = new nodo(C.inicio->elto);
      n_eltos = 1;
      // Copiar el resto de elementos hasta el final de C.
      for (nodo* p = C.inicio->sig; p; p = p->sig, ++n_eltos)
         fin = fin->sig = new nodo(p->elto);
   }
}

#endif // COLA_ENLA_H
