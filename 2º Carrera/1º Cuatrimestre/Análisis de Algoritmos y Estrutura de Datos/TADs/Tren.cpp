#include <iostream>
#include "TADTren.hpp"

int main() {
    Tren<int> tren;

    // Agregar algunos vagones
    tren.setActivo(1);
    tren.toRight();
    tren.setActivo(2);
    tren.toRight();
    tren.setActivo(3);
    tren.toRight();

    // Mostrar el estado actual del tren
    std::cout << "Estado actual del tren:" << std::endl;
        tren.toleft();
        tren.toleft();
        std::cout << "Activo: "<< tren.getActivo() << " "<<std::endl;
        tren.toleft();
    std::cout << std::endl;

    // Agregar más vagones y probar la funcionalidad de eliminación
    tren.setActivo(4);
    tren.toRight();
    tren.setActivo(5);
    tren.toRight();
    tren.deleteVagonActivo();

    // Mostrar el estado actual del tren después de eliminar un vagon
    std::cout << "Estado del tren después de eliminar un vagon:" << std::endl;
        tren.toleft();
        tren.toleft();
        tren.toleft();
        tren.toleft();
        std::cout << "Activo: "<< tren.getActivo() << " "<<std::endl;
    std::cout << "Estado del tren después de eliminar un vagon:" << std::endl;
    std::cout << "Vagones en la izquierda: ";
    std::cout << "Activo: "<< tren.getActivo() << " ";
    std::cout << std::endl;

    return 0;
}
