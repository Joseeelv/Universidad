#include "TADHipermercadoVector.hpp"

int main() {
    Hipermercado hipermercado;

    // Set up some initial state
    hipermercado.setCaja(1, 101);
    hipermercado.setCaja(2, 102);
    hipermercado.setCaja(51, 103);

    // Perform some operations
    hipermercado.getDinero(100.0, 1);
    hipermercado.getDinero(150.0, 2);
    hipermercado.getDinero(200.0, 51);

    hipermercado.cambiaCajero(1, 105);
    hipermercado.cambiaCajero(2, 106);

    double turno1 = hipermercado.cambiaTurno();
    std::cout << "Dinero recaudado en el turno 1: " << turno1 << std::endl;

    hipermercado.cierraCaja(1);
    hipermercado.cierraCaja(2);
    hipermercado.cierraCaja(51);

    double totalCerrado = hipermercado.cierraHipermercado();
    std::cout << "Dinero total recaudado al cerrar el hipermercado: " << totalCerrado << std::endl;
    return 0;
}
