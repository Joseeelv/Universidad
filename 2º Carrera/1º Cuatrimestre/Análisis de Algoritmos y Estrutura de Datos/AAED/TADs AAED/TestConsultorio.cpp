#include <iostream>
#include "TADConsultorio.hpp"

// Definición de las clases Paciente, Medico y Consultorio
// ...

int main() {
    Consultorio consultorio;

    // Alta de médicos
    consultorio.AltaMedico(1);
    consultorio.AltaMedico(2);
    consultorio.AltaMedico(3);

    // Crear pacientes
    Paciente paciente1(1);
    Paciente paciente2(2);
    Paciente paciente3(3);

    // Pacientes en espera
    consultorio.PacienteEspera(paciente1, 1);
    consultorio.PacienteEspera(paciente2, 1);
    consultorio.PacienteEspera(paciente3, 2);

    // Atender pacientes
    consultorio.Atender(1);
    consultorio.Atender(2);

    // Consulta paciente en espera
    Paciente pacienteEnEspera = consultorio.ConsultaPaciente(1);
    std::cout << "Paciente en espera para médico 1: Turno " << pacienteEnEspera.numero << std::endl;

    // Verificar si hay pacientes en espera para médico 2
    bool hayPacientes = consultorio.Pacientes(2);
    if (hayPacientes) {
        std::cout << "Hay pacientes en espera para médico 2." << std::endl;
    } else {
        std::cout << "No hay pacientes en espera para médico 2." << std::endl;
    }

    // Baja de médico
    consultorio.BajaMedico(1);

    // Verificar si el médico 1 existe después de dar de baja
    bool existeMedico1 = consultorio.ExisteMedico(1);
    if (existeMedico1) {
        std::cout << "El médico 1 todavía existe." << std::endl;
    } else {
        std::cout << "El médico 1 ya no existe." << std::endl;
    }

    return 0;
}
