#ifndef TEXTO_HPP
#define TEXTO_HPP

#include <iostream>
#include "listaenla.h" //Lista enlazada
// Suponiendo que ya tienes la implementación de las clases Lista y Linea

typedef Lista<char> Linea;
typedef Lista<Linea>::posicion pos_lin; // Declaración de posición

class Texto {
public:
    Texto() {}
    void MostrarTexto() const;
    void insertarLinea(Linea l);

private:
    Lista<Linea> texto_;
};

void Texto::insertarLinea(Linea l) {
    texto_.insertar(l, texto_.fin());
}

void Texto::MostrarTexto() const {
    for (auto it_linea = texto_.primera(); it_linea != texto_.fin(); it_linea = texto_.siguiente(it_linea)) {
        for (auto it_caracter = texto_.elemento(it_linea).primera(); it_caracter != texto_.elemento(it_linea).fin(); it_caracter = texto_.elemento(it_linea).siguiente(it_caracter)) {
            if (texto_.elemento(it_linea).elemento(it_caracter) == '@') {
                // Si es '@', imprimir el caracter anterior en lugar de borrarlo
                if (it_caracter != texto_.elemento(it_linea).primera()) {
                    auto anterior = texto_.elemento(it_linea).anterior(it_caracter);
                    std::cout << texto_.elemento(it_linea).elemento(anterior);
                }
            } else if (texto_.elemento(it_linea).elemento(it_caracter) == '#') {
                // Si es '#', imprimir un salto de línea en lugar de borrar la línea completa
                std::cout << std::endl;
            } else {
                // Imprimir el caracter normal
                std::cout << texto_.elemento(it_linea).elemento(it_caracter);
            }
        }
    }
}
#endif //texto.hpp

/*
TEXTO -> HOLAA@ MARII@@SOL GUAPA#
Linea 1 -> HOLAA@
Linea 2 -> MARII@@S
Linea 3 -> GUAPA#
RESULTADO -> HOLA
*/