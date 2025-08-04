#include <algorithm>
#include <abin.h>
#include <agen.h>
// NODO HOJA BINARIO
template <typename T>
bool EsHoja(const Abin<T> &A, typename Abin<T>::nodo n)
{
  return (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO);
}

// ALTURA BINARIO
template <typename T>
size_t Altura(const Abin<T> &A, typename Abin<T>::nodo n)
{
  if (n == Abin<T>::NODO_NULO)
    return 0;
  return 1 + std::max(Altura(A, A.hijoIzqdo(n)), Altura(A, A.hijoDrcho(n)));
}

// ALTURA GENERAL
template <typename T>
size_t Altura(const Agen<T> &A, typename Agen<T>::nodo n)
{
  if (n == Agen<T>::NODO_NULO)
    return 0;
  size_t AlturaActual = 0;
  typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
  while (hijo != Agen<T>::NODO_NULO)
  {
    AlturaActual = std::max(AlturaActual, Altura(A, hijo));
    hijo = A.hermDrcho(hijo);
  }
  return 1 + AlturaActual;
}

// DESEQUILIBRIO BINARIO
template <typename T>
size_t Desequilibrio(const Abin<T> &A, typename Abin<T>::nodo n)
{
  if (n == Abin<T>::NODO_NULO)
    return 0;
  size_t AlturaI = Altura(A, A.hijoIzqdo(n));
  size_t AlturaD = Altura(A, A.hijoDrcho(n));

  size_t DifAltura = std::abs(AlturaI - AlturaD);
  size_t DesequilibrioT = std::max(Desequilibrio(A, A.hijoIzqdo(n)), Desequilibrio(A, A.hijoDrcho(n)));

  return std::max(DifAltura, DesequilibrioT);
}

// DESEQUILIBRIO GENERAL
template <typename T>
size_t Desequilibrio(const Agen<T> &A, typename Agen<T>::nodo n)
{
  if (n == Agen<T>::NODO_NULO)
    return 0;
  size_t alturaMax = 0;
  size_t alturaMin = SIZE_MAX;

  typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
  while (hijo != Agen<T>::NODO_NULO)
  {
    size_t alturaNodo = Altura(A, hijo);
    alturaMax = std::max(alturaMax, alturaNodo);
    alturaMin = std::min(alturaMin, alturaNodo);
    hijo = A.hermDrcho(hijo);
  }
  size_t DesequilibrioNodo = 0;
  if (alturaMin != SIZE_MAX)
  {
    DesequilibrioNodo = std::abs(alturaMax - alturaMin);
  }

  size_t DesequilibrioHijos = 0;
  hijo = A.hijoIzqdo(n);
  while (hijo != Agen<T>::NODO_NULO)
  {
    DesequilibrioHijos = std::max(DesequilibrioHijos, Desequilibrio(A, hijo));
    hijo = A.hermDrcho(hijo);
  }
  return std::max(DesequilibrioNodo, DesequilibrioHijos);
}

// BUSCAR NODO A PARTIR DE ELEMENTO BINARIO
template <typename T>
bool BuscarNodo(const Abin<T> &A, typename Abin<T>::nodo n, typename Abin<T>::nodo &encontrado, const T &elto)
{
  if (n == Abin<T>::NODO_NULO)
    return false;
  if (A.elemento(n) == elto)
  {
    encontrado = n;
    return true;
  }
  return BuscarNodo(A, A.hijoIzqdo(n), encontrado, elto) || BuscarNodo(A, A.hijoDrcho(n), encontrado, elto);
}

// BUSCAR NODO A PARTIR DE UN ELEMENTO GENERAL
template <typename T>
bool BuscarNodo(const Agen<T> &A, typename Agen<T>::nodo n, typename Agen<T>::nodo &encontrado, const T &elto)
{
  if (n == Agen<T>::NODO_NULO)
    return false;
  if (A.elemento(n) == elto)
  {
    encontrado = n;
    return true;
  }
  typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
  while (n != Agen<T>::NODO_NULO)
  {
    if (BuscarNodo(A, hijo, encontrado, elto))
      return true;
    hijo = A.hermDrcho(hijo);
  }
  return false;
}

// HUNDIR NODO BINARIO
template <typename T>
void HundirNodo(Abin<T> &A, typename Abin<T>::nodo n)
{
  if (n != Abin<T>::NODO_NULO)
  {
    // Hundimos por condición -> valor de nodo actual menor que el de su hijo izq o drcho
    typename Abin<T>::nodo mayor = n;
    if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.elemento(A.hijoIzqdo(n)) > A.elemento(mayor)) // Solo tiene hijo Izquierdo
    {
      mayor = A.hijoIzqdo(n);
    }
    if (A.hijoDrcho(n) != Abin<T>::NODO_NULO && A.elemento(A.hijoDrcho(n)) > A.elemento(mayor)) // Solo tienen hijo Derecho
    {
      mayor = A.hijoDrcho(n);
    }
    if (A.elemento(n) < A.elemento(mayor)) // Si tiene ambos; ya se obtiene previamente el mayor de los dos
    {
      T eltoAux = A.elemento(n);
      A.elemento(n) = A.elemento(mayor);
      A.elemento(mayor) = eltoAux;
      HundirNodo(A, mayor);
    }
  }
}

// HUNDIR NODO GENERAL
template <typename T>
void HundirNodo(Agen<T> &A, typename Agen<T>::nodo n)
{
  if (n != Agen<T>::NODO_NULO)
  {
    if (!EsHoja(A, n))
    {
      typename Agen<T>::nodo mayor = Agen<T>::NODO_NULO;
      typename Agen<T>::nodo hijo = A.hijoIzqdo(n);

      // Comprobamos toda la lista de hijos del nodo n
      while (hijo != Agen<T>::NODO_NULO)
      {
        // nos quedamos con el mayor de los hijos
        if (mayor == Agen<T>::NODO_NULO || A.elemento(hijo) > A.elemento(mayor))
        {
          mayor = hijo;
        }
        hijo = A.hermDrcho(hijo);
      }
      if (mayor != Agen<T>::NODO_NULO && A.elemento(n) < A.elemento(mayor))
      {
        T eltoAux = A.elemento(n);
        A.elemento(n) = A.elemento(mayor);
        A.elemento(mayor) = A.elemento(n);
        HundirNodo(A, mayor);
      }
    }
  }
}

// BINARIO REFLEJADO
template <typename T>
Abin<T> Reflejado(const Abin<T> &A)
{
  // Vamos a ir insertando el contenido del hijo izquiero del árbol A en el hijo derecho del nuevo árbol reflejado y viceversa.
  Abin<T> R;
  if (!A.arbolVacio())
  {
    R.insertarRaiz(A.elemento(A.raiz()));
    Reflejado_rec(A, R, A.raiz(), R.raiz());
  }
  return R;
}

template <typename T>
void Reflejado_rec(const Abin<T> &A, Abin<T> &Reflejado, typename Abin<T>::nodo n, typename Abin<T>::nodo m)
{
  if (n != Abin<T>::NODO_NULO)
  {
    if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
    { // Si tiene hijo izquierdo, lo insertamos como hijo derecho del nuevo arbol
      Reflejado.insertarHijoDrcho(m, A.elemento(A.hijoIzqdo(n)));
      Reflejado_rec(A, Reflejado, A.hijoIzqdo(n), Reflejado.hijoDrcho(m));
    }
    if (A.hijoDrcho(n) != Abin<T>::NODO_NULO)
    {
      Reflejado.insertarHijoIzqdo(m, A.elemento(A.hijoDrcho(n)));
      Reflejado_rec(A, Reflejado, A.hijoDrcho(n), Reflejado.hijoIzqdo(m));
    }
  }
}

// GENERAL REFLEJADO
template <typename T>
Agen<T> Reflejado(const Agen<T> &A)
{
  Agen<T> R;
  if (A.raiz() != Agen<T>::NODO_NULO)
  {
    R.insertarRaiz(A.elemento(A.raiz()));
    Reflejado_rec(A, A.raiz(), R, R.raiz());
  }
  return R;
}

template <typename T>
void Reflejado_rec(const Agen<T> &A, typename Agen<T>::nodo nA, Agen<T> &R, typename Agen<T>::nodo nR)
{
  if (nA != Agen<T>::NODO_NULO)
  {
    if (A.hijoIzqdo(nA) != Agen<T>::NODO_NULO)
    {
      typename Agen<T>::nodo hijo = A.hijoIzqdo(nA);
      typename Agen<T>::nodo nuevo = Agen<T>::NODO_NULO;
      while (hijo != Agen<T>::NODO_NULO)
      {
        nuevo = R.insertarHijoIzqdo(nR, A.elemento(hijo));
        Reflejado_rec(A, hijo, R, nuevo);
        hijo = A.hermDrcho(hijo);
      }
    }
  }
}

// COMPROBAR SI ES AVL A PARTIR DE UN BINARIO
/*
  Para que un árbol binario sea un AVL, este debe de cumplir las siguientes condiciones:
    1. Ser un ABB -> HijoIzqdo < Nodo < HijoDrcho (en todos los niveles).
    2. Estar equilibrado: diferencia de altura entre subárbol izquierdo y derecho <= 1.
*/

template <typename T>
bool esAVL(const Abin<T> &A)
{
  if (A.arbolVacio())
    return true;
  return esABB(A, A.raiz()) && esAVL_rec(A, A.raiz());
}

// Comprobamos si es hoja
template <typename T>
bool EsHoja(const Abin<T> &A, typename Abin<T>::nodo n)
{
  return A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO;
}

template <typename T>
bool esABB(const Abin<T> &A, typename Abin<T>::nodo n, T min, T max)
{
  if (n == Abin<T>::NODO_NULO)
    return true;

  T val = A.elemento(n);
  if (val <= min || val >= max)
    return false;

  return esABB(A, A.hijoIzqdo(n), min, val) && esABB(A, A.hijoDrcho(n), val, max);
}

template <typename T>
bool esAVL_rec(const Abin<T> &A, typename Abin<T>::nodo n)
{
  if (n == Abin<T>::NODO_NULO)
    return true;

  int alturaI = Altura(A, A.hijoIzqdo(n));
  int alturaD = Altura(A, A.hijoDrcho(n));

  if (std::abs(alturaI - alturaD) > 1)
    return false;

  return esAVL_rec(A, A.hijoIzqdo(n)) && esAVL_rec(A, A.hijoDrcho(n));
}

/*
  DADA UNA CADENA DE TEXTO, SE PRETENDE REALIZAR UN ALGORITMO CRIPTOGRÁFICO QUE CIFRE LA CADENA DE TEXTO MEDIANTE EL USO DE ÁRBOLES BINARIOS.
  EL MÉTODO DE CIFRADO SERÁ DISPONER LOS CARACTERES EN ANCHURA Y POSTERIORMENTE LEERLOS EN PREORDEN PARA OBTENER SU CIFRADO.

  ES DECIR, SI TENEMOS LA CADENA "HOLA MUNDO"
*/

size_t Longitud(const char *texto)
{
  size_t longitud = 0;
  while (texto[longitud] != '\0')
  {
    longitud++;
  }
  return longitud;
}

template <typename T = char>
void insertarCaracteres(Abin<T> &A, const T *texto)
{
  size_t tama = Longitud(texto);
  A.insertarRaiz(texto[0]);
  typename Abin<T>::nodo actual = A.raiz();

  // Simulamos una cola con el tamaño de la cadena de texto
  typename Abin<T>::nodo *cola = new typename Abin<T>::nodo[tama];
  size_t inicio, fin = 0;
  cola[fin++] = actual;
  size_t i = 1; // Empezamos por el segundo elemento
  while (i < tama)
  {

    actual = cola[inicio];
    inicio++;

    if (i < tama)
    {
      A.insertarHijoIzqdo(actual, texto[i++]);
      cola[fin++] = A.hijoIzqdo(actual);
    }
    if (i < tama)
    {
      A.insertarHijoDrcho(actual, texto[i++]);
      cola[fin++] = A.hijoDrcho(actual);
    }
  }
  recorridoPreorden(A, A.raiz());
  delete[] cola;
}

template <typename T = char>
void recorridoPreorden(const Abin<T> &A, typename Abin<T>::nodo n)
{
  if (n != Abin<T>::NODO_NULO)
  {
    std::cout << A.elemento(n);
    recorridoPreorden(A, A.hijoIzqdo(n));
    recorridoPreorden(A, A.hijoDrcho(n));
  }
}