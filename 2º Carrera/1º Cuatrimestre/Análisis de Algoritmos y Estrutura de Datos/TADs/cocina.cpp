#include "TADCocina.hpp"

int main() {
    unsigned l;
    std::cout<<"Introduce la longitud de la cocina: ";
    std::cin >> l;
    Cocina miCocina(l); // Crear una cocina con longitud 10

    // Crear y colocar algunos muebles en la cocina
    Mueble mueble1(2, 1);
    Mueble mueble2(300, 6);
    Mueble mueble3(1, 0);

    // Colocar los muebles en la cocina
    if (miCocina.colocarse(2,1)) {
        miCocina.setMueble(2,1);
        std::cout << "Mueble 1 colocado orrectamente." << std::endl;
    } else {
        std::cout << "No se puede colocar el Mueble 1." << std::endl;
    }

    if (miCocina.colocarse(300,6)) {
        miCocina.setMueble(300,6);
        std::cout << "Mueble 2 colocado correctamente." << std::endl;
    } else {
        std::cout << "No se puede colocar el Mueble 2." << std::endl;
    }

    if (miCocina.colocarse(1,0)) {
        miCocina.setMueble(1,0);
        std::cout << "Mueble 3 colocado correctamente." << std::endl;
    } else {
        std::cout << "No se puede colocar el Mueble 3." << std::endl;
    }
    // Mover el Mueble 2
    miCocina.MovMueble(2);
    // Eliminar el Mueble 1
    miCocina.eliminaMueble(1);
    return 0;
}
