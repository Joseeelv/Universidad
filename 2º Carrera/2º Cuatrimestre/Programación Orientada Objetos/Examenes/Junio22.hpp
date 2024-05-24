#include<iostream>
#include <algorithm>
#include <map>
#include <set>
#include <cstring>
/*
Multiplicidad de las relaciones
Cliente - Vehiculo -> * - *
Clinte - Contrato -> 1 - *
Contrato - Vehiculo -> 1..* - 1..*
*/
class Reserva{};
class Detalle{};
class Vehiculo{};

class Cliente_Vehiculo{ //Clase asociación Cliente - Vehiculo
    public:
        //Multiplicidad *-* -> map de map
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
        //Métodos propios de la clase Cliente
        //relacion con la clase contrato
        typedef std::set<Contrato*>Contratos;
        void firma(Contrato& )noexcept;
        const Contratos& firmados()const noexcept;
    private:
       //Atributos propios de la clase Cliente
       //Relacion con contrato
       Contratos contratos_;
};

class Contrato{
    public:
        Contrato(/*Parámetros propios*/ Cliente& c):cliente_(c){}
        inline Cliente tiene()const noexcept{return cliente_;}
    private:
        Cliente cliente_;
};



class Contrato_Vehiculo{
    public:
    //Multiplicidad 1..* - 1..* map de pair
    typedef std::pair<Contrato*,Detalle*>CD;
    typedef std::pair<Vehiculo*,Detalle*>VD;
    
    typedef std::map<Contrato*,VD>CVD;
    typedef std::map<Vehiculo*,CD>VCD;

    //métodos asociadores
    void detalle(Contrato&, Vehiculo&, Detalle&)noexcept;
    void detalle(Vehiculo&, Contrato&, Detalle&)noexcept;
    //observadores
    const VD& vehiculoscontratados(Contrato& )const noexcept;
    const CD& contratosvehiculo(Vehiculo& )const noexcept;
    private:
    //Relaciones entre las clases
    CVD directa_;
    VCD inversa_;
};