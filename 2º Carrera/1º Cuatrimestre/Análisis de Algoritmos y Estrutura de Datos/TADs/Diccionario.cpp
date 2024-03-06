#include <iostream>
#include "TADDiccionario.hpp"

int main() {
    // Crear un diccionario
    Diccionario miDiccionario;
    // Agregar traducciones al diccionario
    miDiccionario.setTraduccion("apple", "manzana");
    miDiccionario.setTraduccion("banana", "plátano");
    miDiccionario.setTraduccion("orange", "naranja");
    miDiccionario.setTraduccion("apple", "manzana verde"); // Agregar otra traducción para 'apple'

    // Obtener traducciones y mostrarlas
    Lista<string> traduccionesApple = miDiccionario.getTraducciones("apple");
    std::cout << "Traducciones de 'apple': ";
    for (auto it = traduccionesApple.primera(); it != traduccionesApple.fin(); it = traduccionesApple.siguiente(it)) {
        std::cout << traduccionesApple.elemento(it) << " ";
    }
    std::cout << std::endl;

    // Comprobar si una traducción es correcta
    std::cout << "¿'manzana' es correcta para 'apple'? " << (miDiccionario.esCorrecta("apple", "manzana") ? "Sí" : "No") << std::endl;

    // Eliminar una traducción
    miDiccionario.deleTraduccion("apple", "manzana verde");

    // Mostrar traducciones después de eliminar
    traduccionesApple = miDiccionario.getTraducciones("apple");
    std::cout << "Traducciones de 'apple' después de eliminar 'manzana verde': ";
    for (auto it = traduccionesApple.primera(); it != traduccionesApple.fin(); it = traduccionesApple.siguiente(it)) {
        std::cout << traduccionesApple.elemento(it) << " ";
    }
    std::cout << std::endl;

    return 0;
}
