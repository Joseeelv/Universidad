#ifndef __LISTA_HPP__
#define __LISTA_HPP__

#include <iostream>
#include <cassert>

template<typename T>
class Lista 
{
  struct nodo;
  
  public:
    
    typedef nodo* posicion;

    Lista();
    Lista(const Lista<T>& Lis);
    Lista<T>& operator=(const Lista<T>& Lis);

    const T& elemento(posicion p) const;
    T& elemento(posicion p);
    
    void insertar(const T& x, posicion p);
    void eliminar(posicion p);

    posicion primera() const;
    posicion fin() const;
    posicion anterior(posicion p) const;
    posicion siguiente(posicion p) const;

    ~Lista();


  private: 
    
    struct nodo
    {
      T elto;
      nodo* sig;

      nodo(T e, nodo* p = nullptr): elto(e), sig(p)
      {}
    };
      
    nodo* L;

    void copiar(const Lista<T>& Lis); 
};


template<typename T>
void Lista<T>::copiar(const Lista<T>& Lis)
{
  // llamo al constructor de T para que me cree un objeto de tipo T vacío.
  L = new nodo(T());
  nodo* p = L;
  nodo* aux = Lis.L->sig;

  while(aux)
  {
    p->sig = new nodo (aux->elto);
    p = p->sig;
    aux = aux->sig;
  }

}


template<typename T>
Lista<T>::Lista(): L(new nodo(T()))
{}


template<typename T>
Lista<T>::Lista(const Lista<T>& Lis)
{
  copiar(Lis);
}


template<typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& Lis)
{
  if(this != &Lis)
  {
    this->~Lista();
    copiar(Lis);
  }

  return *this;
}


template<typename T>
void Lista<T>::insertar(const T& x, posicion p)
{
  p->sig = new nodo(x, p->sig);
}


template<typename T>
void Lista<T>::eliminar(posicion p)
{
  assert(p->sig != nullptr);
  
  nodo* q = p->sig;
  p->sig = p->sig->sig;

  delete q;
}


template<typename T>
const T& Lista<T>::elemento(posicion p) const 
{
  assert(p->sig != nullptr);

  return p->sig->elto; 
}

template<typename T>
T& Lista<T>::elemento(posicion p)
{
  assert(p->sig != nullptr);

  return p->sig->elto;
}


template<typename T>
typename Lista<T>::posicion Lista<T>::primera() const 
{
  return L;
}


template<typename T>
typename Lista<T>::posicion Lista<T>::fin() const 
{
  nodo* q = L;

  while(q != nullptr)
    q = q->sig;

  return q;
}

template<typename T>
typename Lista<T>::posicion Lista<T>::anterior(posicion p) const 
{
  assert(p != L);

  nodo* q = L->sig;

  while(q->sig != p)
    q = q->sig;

  return q;
}


template<typename T>
typename Lista<T>::posicion Lista<T>::siguiente(posicion p) const 
{
  assert(p->sig != nullptr);
  
  return p->sig;
}

// Siempre que me pasen p, esa p se refiere al nodo anterior


template<typename T>
Lista<T>::~Lista()
{
  nodo* q = L;
  while(L)
  {
    q = L->sig;
    delete L;
    L = q;
  }
}




#endif
