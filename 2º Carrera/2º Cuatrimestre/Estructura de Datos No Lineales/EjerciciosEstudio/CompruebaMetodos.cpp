#include <iostream>
#include "abin.h"
#include "agen.h"
#include "abin_E-S.hpp"
#include "agen_E-S.hpp"
#include "MetodosArboles.hpp"
using namespace std;

int main()
{
  // ===================== ÁRBOL BINARIO =====================
  Abin<int> abin;
  auto raizBin = abin.insertarRaiz(10);
  auto izq = abin.insertarHijoIzqdo(raizBin, 15);   // mayor que la raíz -> debería subir
  auto der = abin.insertarHijoDrcho(raizBin, 5);    // menor que la raíz
  abin.insertarHijoIzqdo(izq, 20); // más grande aún -> debería llegar arriba

  cout << "\n--- Árbol binario antes de HundirNodo ---\n";
  imprimirAbin(abin);

  HundirNodo(abin, raizBin);  // Aplica hundimiento

  cout << "\n--- Árbol binario después de HundirNodo ---\n";
  imprimirAbin(abin);

  // ===================== ÁRBOL GENERAL =====================
  Agen<int> agen;
  auto raizGen = agen.insertarRaiz(30);
  auto h1 = agen.insertarHijoIzqdo(raizGen, 40); // mayor que raíz
  auto h2 = agen.insertarHermDrcho(h1, 25);
  auto h3 = agen.insertarHermDrcho(h2, 50); // el mayor
  agen.insertarHijoIzqdo(h1, 60); // aún mayor, probar recursividad

  cout << "\n--- Árbol general antes de HundirNodo ---\n";
  imprimirAgen(agen);

  HundirNodo(agen, raizGen);

  cout << "\n--- Árbol general después de HundirNodo ---\n";
  imprimirAgen(agen);

  return 0;
}
