#include "TADTexto.hpp"
#include <iostream>
using namespace std;
int main() {
Texto t;
Linea L1, L2, L3;
//Inicializar Lineas L1.insertar('b',L1.fin()); L1.insertar('e',L1.fin()); L1.insertar('a',L1.fin()); L1.insertar('t',L1.fin()); L1.insertar('t',L1.fin()); L1.insertar('@',L1.fin()); L1.insertar('r',L1.fin()); L1.insertar('i',L1.fin()); L1.insertar('z',L1.fin());
L2.insertar('i',L2.fin()); L2.insertar('s',L2.fin()); L2.insertar('a',L2.fin()); L2.insertar('@',L2.fin()); L2.insertar('@',L2.fin()); L2.insertar('b',L2.fin()); L2.insertar('e',L2.fin()); L2.insertar('l',L2.fin()); L2.insertar('@',L2.fin());
L3.insertar('b',L3.fin()); L3.insertar('e',L3.fin()); L3.insertar('a',L3.fin()); L3.insertar('t',L3.fin()); L3.insertar('t',L3.fin()); L3.insertar('r',L3.fin()); L3.insertar('i',L3.fin()); L3.insertar('z',L3.fin()); L3.insertar('#',L3.fin());
//Inicializar texto t.insertarLinea(L1);t.insertarLinea(L2);t.insertarLinea(L3); //Mostrar texto
t.MostrarTexto();
return 0;
}