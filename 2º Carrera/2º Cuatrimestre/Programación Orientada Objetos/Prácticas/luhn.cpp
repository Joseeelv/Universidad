// $Id: luhn.cpp 404 2018-02-27 10:50:37Z gerardo $
// Verifica un número de tarjeta empleando el algoritmo de Luhn
// Referencias: 
//              http://en.wikipedia.org/wiki/Luhn_algorithm
//
#include "cadena.hpp"
#include <cstddef>

bool luhn(const Cadena& numero)
{
  size_t n = numero.length();
  size_t suma = 0;
  bool alt = false;
  for (int i = n - 1; i > -1; --i) {
    n = numero[size_t(i)] - '0';
    if (alt) {
      n *= 2;
      if (n > 9)
	n = (n % 10) + 1;
    }
    alt = !alt;
    suma += n;
  }
  return !(suma % 10);
}
