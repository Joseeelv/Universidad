/*
Jose Luis Venega Sánchez
Practica 0 de POO
*/
#include "fecha.hpp"
#include <iostream>
#include <ctime>
#include <cstdio>
#include <locale>

//-----Implementacion de los métodos privados de la clase Fecha-----
void Fecha::comprobarfecha(){ //DIA ERRONEO¿?
    if(dd > ultimo_dia() || dd < 1){
        Fecha::Invalida D_invalido("ERROR: Dia mal introducido");
        //excepcion
        throw D_invalido;
    }
    if(aaaa < Fecha::AnnoMinimo || aaaa>Fecha::AnnoMaximo){
        Fecha::Invalida A_invalido("ERROR: Año mal introducido");
        //excepcion
        throw A_invalido;
    }
}

int Fecha::ultimo_dia()const{
    //meses que tienen 31 dias
    if(mm==1||mm==3||mm==5||mm==7||mm==8||mm==10||mm==12) return 31;
    //meses que tiene 30 dias
    else if(mm==4||mm==6||mm==9||mm==11) return 30; 
    //comprobamos que febrero tiene 28 o 29 dias
    else if(mm==2){
        if(aaaa%4 ==0 && (aaaa %400 ==0 || aaaa %100 !=0)){
            return 29;
        } //bisiesto
        else return 28;
    }
    else{//MES ERRONEO¿?
        Fecha::Invalida M_invalido("ERROR: Mes masl introducido");
        //falta la excepcion
        throw M_invalido;
        return 0;
    }
}
//----IMPLEMENTACION DE LOS CONSTRUCTORES----
Fecha::Fecha(int dia, int mes, int anno):dd{dia},mm{mes},aaaa{anno}{
    //dependiendo de los parámetros que introduzcamos debemos introducir
    //la fecha local del sistema, para ello utilizamos la biblioteca estandar <ctime>
    std::time_t t_calendario = std::time(nullptr); //tiempo nulo
    std::tm* t_descompuesto = std::localtime(&t_calendario); //descomponemos el tiempo local

    //Descomponemos la fecha
    if(aaaa == 0) aaaa= t_descompuesto->tm_year +1900;
    if(mm == 0) mm = t_descompuesto->tm_mon +1; //ya que Enero seria el mes 0 no el 1
    if(dd == 0) dd = t_descompuesto->tm_mday;
    comprobarfecha(); //comprobamos que la fecha es correcta
}

Fecha::Fecha(const char* c){ //poder obtner la fecha a partir de una cadena de caracteres
    if(sscanf(c,"%d/%d/%d",&dd,&mm,&aaaa) !=3){ //la fecha no tiene 3 parámetros --> Fecha incorrecta
        Fecha::Invalida formato("ERROR: Formato de fecha incorrecto");
        throw formato;
    }
    //Si la fecha es correcta procedemos a descomponerla
    std::time_t t_calendario = std::time(nullptr);
    std::tm* t_descompuesto = std::localtime(&t_calendario);
    //descomponemos la fecha
    if(aaaa == 0) aaaa= t_descompuesto->tm_year +1900;
    if(mm == 0) mm = t_descompuesto->tm_mon +1; //ya que Enero seria el mes 0 no el 1
    if(dd == 0) dd = t_descompuesto->tm_mday;
    comprobarfecha(); //comprobamos que la fecha es correcta
}

Fecha::operator const char*()const noexcept{
    //Usamos la codificación española "utf-8"
    std::locale::global(std::locale("es_ES.utf8"));
    static char *auxiliar= new char[45]; //creamos con memoria dinamica un vector auxiliar que contendrá la fecha

    //descomponemos la fecha
    std::time_t t_calendario = std::time(nullptr);
    std::tm* tiempo = std::localtime(&t_calendario);
    tiempo->tm_mday = dd;
    tiempo->tm_mon  = mm-1;
    tiempo->tm_year = aaaa-1900;
    mktime(tiempo); //creamos la fecha
    //guardamos la fecha en el vector auxiliar
    strftime(auxiliar,45,"%A %d de %B de %Y",tiempo);
    return auxiliar; //devolvemos la fecha
}

//----IMPLEMENTACION DE LOS OPERADORES DE INCREMENTO Y DECREMENTO----
Fecha& Fecha::operator++(){
    *this +=1;
    return *this;
}
Fecha Fecha::operator++(int){ //la variable no se usa es para especificar que es "++fecha"
    //Fecha *fecha = new Fecha(*this); //tenemos que la nueva fecha = *this
    Fecha fecha(*this); //Ctor copia
    *this+=1;
    return fecha;
}
Fecha& Fecha::operator--(){
    *this-=1;
    return *this;
}
Fecha Fecha::operator--(int){ //la variable no se usa es para especificar que es "--fecha"
    Fecha fecha(*this);
    *this-=1;
    return fecha;
}
Fecha& Fecha::operator+=(int n){
    //Creamos una estructura con la fecha ya operada y formateada
    std::tm fecha{};
    fecha.tm_mday = dd + n;
    fecha.tm_mon = mm - 1;
    fecha.tm_year = aaaa - 1900;
    std::mktime(&fecha);

    //pasamos la fecha formateada
    dd = fecha.tm_mday;
    mm = fecha.tm_mon +1;
    aaaa= fecha.tm_year +1900;
    comprobarfecha(); //comprobamos que la fecha sea correcta
    return *this; //devolvemos la fecha modificada
}
Fecha& Fecha::operator-=(int n){
    *this += -n;
    return *this;
}
//----IMPLEMENTACION DE LOS OPERADORES SUMA Y RESTA----
Fecha Fecha::operator+(int n)const{ 
    Fecha fecha(*this);
    return fecha +=n;
}
Fecha Fecha::operator -(int n)const {
    Fecha fecha(*this);
    return fecha -=n;
}

//----IMPLEMENTACION OPERADORES LOGICOS----
bool operator == (const Fecha& a, const Fecha& b) noexcept{ //comprobamos que ambas fechas son iguales
    return(a.dia() == b.dia() && a.mes() == b.mes() && a.anno() == b.anno());
}
bool operator !=(const Fecha& a, const Fecha& b) noexcept{
    //return(a.dia() != b.dia() && a.mes() != b.mes() && a.anno() != b.anno());
    return !(a==b); //mas eficiente así
}
bool operator <(const Fecha& a, const Fecha& b) noexcept{
    return (a.anno() < b.anno() ||((a.anno() == b.anno() && a.mes() < b.mes())||
        (a.anno() == b.anno() && a.mes() == b.mes() && a.dia() < b.dia())));
}
bool operator >(const Fecha& a, const Fecha& b) noexcept{ 
    // fecha a > fechb <--> b<a
    return (b<a);
}
bool operator <=(const Fecha& a, const Fecha& b)noexcept{
    //fecha a <= fecha b <--> !(b<a)
    return !(b<a);
}
bool operator >=(const Fecha& a, const Fecha& b)noexcept{
    //fecha a >= fecha b <--> !(a<b)
    return !(a<b);
}
//Lo hacemos así ya que el operador que hemos sobrecargado es " < " y por
//tanto nos basamos en él para la comprobación de que las fechas son. ">, <= y >="

//La implementacion del constructor de la clase
//Invalida está hecho en el .hpp
