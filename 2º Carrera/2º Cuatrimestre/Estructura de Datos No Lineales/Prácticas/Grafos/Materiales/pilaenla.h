/*--------------------------------------------------------*/
/* pilaenla.h                                             */
/*                                                        */
/* clase Pila de elementos del tipo genérico T y          */
/*    capacidad ilimitada.                                */
/*--------------------------------------------------------*/

#ifndef PILA_ENLA_H
#define PILA_ENLA_H
#include <cstddef>   // size_t
#include <cassert>

template <typename T> class Pila {
public:
   Pila();
   bool vacia() const;
   size_t tama() const;
   const T& tope() const;
   void pop();
   void push(const T& x);
   Pila(const Pila& P);             // Ctor. de copia
   Pila& operator =(const Pila& P); // Asignación entre pilas
   ~Pila();                         // Destructor
private:
   struct nodo {
      T elto;
      nodo* sig;
      nodo(const T& e, nodo* p = nullptr) : elto(e), sig(p) {}
   };

   nodo* tope_;
   size_t n_eltos;

   void copiar(const Pila& P);
};

/*--------------------------------------------------------*/
/* clase Pila genérica mediante celdas enlazadas.         */
/*                                                        */
/* Implementación de operaciones                          */
/*--------------------------------------------------------*/

template <typename T>
inline Pila<T>::Pila() :
   tope_(nullptr),
   n_eltos(0)
{}

template <typename T>
inline bool Pila<T>::vacia() const
{
   return (n_eltos == 0); // Alternativa: return tope_ == nullptr;
}

template <typename T>
inline size_t Pila<T>::tama() const
{
   return n_eltos;
}

template <typename T>
inline const T& Pila<T>::tope() const
{
   assert(!vacia());
   return tope_->elto;
}

template <typename T>
inline void Pila<T>::pop()
{
   assert(!vacia());
   nodo* p = tope_;
   tope_ = p->sig;
   delete p;
   --n_eltos;
}

template <typename T>
inline void Pila<T>::push(const T& x)
{
   tope_ = new nodo(x, tope_);
   ++n_eltos;
}

// Constructor de copia
template <typename T>
inline Pila<T>::Pila(const Pila& P) : Pila()
{
   copiar(P);
}

// Asignación entre pilas
template <typename T>
Pila<T>& Pila<T>::operator =(const Pila& P)
{
   if (this != &P) {   // Evitar autoasignación
      this->~Pila();   // Vaciar la pila actual
      copiar(P);
   }
   return *this;
}

// Destructor: vací­a la pila
template <typename T>
Pila<T>::~Pila()
{
   nodo* p;
   while (tope_) {
      p = tope_->sig;
      delete tope_;
      tope_ = p;
   }
   n_eltos = 0;
}

// Método privado
template <typename T>
void Pila<T>::copiar(const Pila& P)
// Pre: *this está vacía.
// Post: *this es copia de P.
{
   if (!P.vacia()) {
      tope_ = new nodo(P.tope_->elto); // Copiar el primer elemento.
      n_eltos = 1;
      // Copiar el resto de elementos hasta el fondo de la pila.
      nodo* p = tope_;         // p recorre la pila destino (*this).
      nodo* q = P.tope_->sig;  // q recorre la pila origen (P) desde 2º nodo.
      while (q) {
         p->sig = new nodo(q->elto);
         ++n_eltos;
         p = p->sig;
         q = q->sig;
      }
   }
}

#endif // PILA_ENLA_H
/*
// Alternativa para copiar
#include <utility> // swap()

// Constructor de copia
template <typename T>
inline Pila<T>::Pila(const Pila<T>& P) :
   tope_(nullptr),
   n_eltos(P.n_eltos)
{
   if (n_eltos > 0) {
      tope_ = new nodo(P.tope()); // Copiar el primer elemento.
      // Copiar el resto de elementos hasta el fondo de la pila.
      nodo* p = tope_;         // p recorre la pila destino (*this).
      nodo* q = P.tope_->sig;  // q recorre la pila origen (P) desde 2º nodo.
      while (q) {
         p->sig = new nodo(q->elto);
         p = p->sig;
         q = q->sig;
      }
   }
}

// Asignación entre pilas
template <typename T>
Pila<T>& Pila<T>::operator =(Pila<T> P)
{
   std::swap(*this, P);
   return *this;
}

#endif // PILA_ENLA_H
*/
