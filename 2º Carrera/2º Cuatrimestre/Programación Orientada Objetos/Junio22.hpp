#include<iostream>
#include <algorithm>
#include <map>
#include <set>

/*
Multiplicidad de las relaciones
Cliente - Vehiculo -> * - *
Clinte - Contrato -> 1 - *
Contrato - Vehiculo -> 1..* - 1..*
*/
class Reserva{};
class Detalle{};
class Vehiculo; //declaración adelantada


class CV{ //Clase asociación Cliente - Vehiculo
    public:
        typedef std::map<Cliente*,Reserva*>CR;
        typedef std::map<Vehiculo*,Reserva*>VR;

        typedef std::map<Cliente*,VR>CVR;
        typedef std::map<Vehiculo*,CR>VCR;
        //métodos asociadores
        void reserva(Cliente&,Vehiculo&,Reserva&)noexcept;
        void reserva(Vehiculo&,Cliente&,Reserva&)noexcept;
        //Métodos observadores
        CR reservados_por(Vehiculo&)const noexcept;
        VR reservados(Cliente&) const noexcept;
    private:
        CVR directa_;
        VCR inversa_;
};

class Cliente{
    public:

    private:

};

class Contrato{
    public:

    private:

};

class Vehiculo{};

