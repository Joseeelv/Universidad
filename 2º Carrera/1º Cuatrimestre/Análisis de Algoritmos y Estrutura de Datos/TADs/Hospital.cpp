#include <iostream>
#include "TADHospital.hpp"
int main() {
    // Crear un hospital con capacidad para 3 pacientes en UCI y 4 pacientes en planta
    Hospital miHospital(3, 4); //UCI - PLANTA

    // Añadir pacientes al hospital
    miHospital.setPaciente(1, 3); //id , gravedad
    miHospital.setPaciente(2, 7);
    miHospital.setPaciente(3, 5);
    miHospital.setPaciente(4, 2);
    miHospital.setPaciente(5, 8);

    // Mostrar la cantidad de pacientes en UCI y en planta
    std::cout << "Pacientes en UCI: " << miHospital.getPacientesUCI() << std::endl;
    std::cout << "Pacientes en Planta: " << miHospital.getPacientesPlanta() << std::endl;

    // Dar de alta a un paciente de la planta
    miHospital.Alta(4);

    // Mostrar nuevamente la cantidad de pacientes en UCI y en planta
    std::cout << "Después del alta, pacientes en UCI: " << miHospital.getPacientesUCI() << std::endl;
    std::cout << "Después del alta, pacientes en Planta: " << miHospital.getPacientesPlanta() << std::endl;

    // Simular la muerte de un paciente en UCI
    miHospital.Muerte(1);

    // Mostrar la cantidad de pacientes en UCI y en planta después de la muerte
    std::cout << "Después de la muerte, pacientes en UCI: " << miHospital.getPacientesUCI() << std::endl;
    std::cout << "Después de la muerte, pacientes en Planta: " << miHospital.getPacientesPlanta() << std::endl;

    // Obtener la cantidad de pacientes con gravedad 5 en UCI y en planta
    size_t gravedadBuscada = 5;
    std::cout << "Pacientes con gravedad " << gravedadBuscada << " en UCI: " << miHospital.getPacientesGravedad(gravedadBuscada) << std::endl;

    return 0;
}
