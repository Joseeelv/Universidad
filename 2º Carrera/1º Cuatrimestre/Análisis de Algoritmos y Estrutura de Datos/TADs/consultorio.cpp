#include "TADConsultorio.hpp"

int main() {
    Consultorio consultorio;

    // Agregar médicos
    consultorio.setMedico(1);
    consultorio.setMedico(2);
    consultorio.setMedico(3);

    // Agregar pacientes
    consultorio.setPaciente(1, 1);
    consultorio.setPaciente(1, 2);
    consultorio.setPaciente(2, 3);

    // Verificar información
    std::cout << "Lista de espera del médico 1: " << (consultorio.getListaespera(1) ? "Hay pacientes" : "No hay pacientes") << std::endl;
    std::cout << "Paciente en frente de la cola del médico 1: " << consultorio.getPaciente(1) << std::endl;
    
    std::cout << "Lista de espera del médico 2: " << (consultorio.getListaespera(2) ? "Hay pacientes" : "No hay pacientes") << std::endl;
    std::cout << "Paciente en frente de la cola del médico 2: " << consultorio.getPaciente(2)<< std::endl;

    std::cout << "Lista de espera del médico 3: " << (consultorio.getListaespera(3) ? "Hay pacientes" : "No hay pacientes") << std::endl;

    // Eliminar pacientes
    consultorio.deletPaciente(1);
    consultorio.deletPaciente(2);
    consultorio.deletPaciente(3);

    // Verificar si hay pacientes después de eliminar
    std::cout << "Lista de espera del médico 1 después de eliminar pacientes: " << (consultorio.getListaespera(1) ? "Hay pacientes" : "No hay pacientes") << std::endl;

    // Eliminar médicos
    consultorio.deletMedico(1);
    consultorio.deletMedico(2);
    return 0;
}
