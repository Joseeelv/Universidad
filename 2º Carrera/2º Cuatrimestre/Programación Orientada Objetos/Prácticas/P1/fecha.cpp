
#include "fecha.hpp"
/*-----Métodos privados de la clase Fecha-----*/
void Fecha::comprueba_fecha ()const{
    //Comprobamos que el día es correcto
    if(dia_>ultimo_dia()||dia_ < 1){
        Fecha::Invalida D_Invalido("ERROR: Dia introducido es incorrecto");
        throw D_Invalido;
    }
    if(anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo){
        Fecha::Invalida A_Invalido("ERROR: Ano introducido es incorrecto");
        throw A_Invalido;
    }
}
int Fecha::ultimo_dia ()const{
    if(mes_==1||mes_==3||mes_==5||mes_==7||mes_==8||mes_==10||mes_==12)return 31;
        else if(mes_==4||mes_==6||mes_==9||mes_==11)return 30;
        else if(mes_ == 2){
            //Comprobamos que sea bisiesto
            if((anno_%4 == 0 && anno_%100 !=0)||anno_%400==0) return 29;
            else return 28;
        }
    else{
        Fecha::Invalida M_Invalido("ERROR: Mes introducido es incorrecto");
        throw M_Invalido;
    } 
}

void Fecha::actualizar()const{
    //Codificación en UTF-8
    std::locale::global(std::locale("es_ES.utf8"));
    //Vamos a pasar la fecha a cadena sin formato
    //Desformateamos la fecha
    std::time_t t_sistema = std::time(nullptr);
    std::tm* t_desformato = std::localtime(&t_sistema);
    t_desformato -> tm_year = anno_-1900;
    t_desformato -> tm_mon = mes_-1;
    t_desformato -> tm_mday = dia_;
    mktime(t_desformato);
    //Ahora guardamos todo en el vector de cadena
    strftime(crep,sizeof(crep),"%A %d de %B de %Y",t_desformato);
}

/*----- Métodos públicos de la clase Fecha*/
//Implementación del constructor
Fecha::Fecha(int dia, int mes, int anno):dia_(dia),mes_(mes),anno_(anno),actual(false){
    /*Si la variable toma el valor 0 --> toma la fecha del sistema.
    Para ello hacemos uso de la libreria ctime.*/
    std::time_t t_sistema = std::time(nullptr);
    std::tm* t_sistemacompuesto = std::localtime(&t_sistema);

    //comprobamos si el valor de la variables es 0
    if(anno_ == 0) anno_ = t_sistemacompuesto-> tm_year + 1900;
    if(mes_ ==0) mes_ = t_sistemacompuesto -> tm_mon +1;
    if(dia_ ==0) dia_ = t_sistemacompuesto -> tm_mday;
    //comprobamos que la fecha es correcta
    comprueba_fecha();
}
Fecha::Fecha(const char* c):actual(false){
    //Introducimos la fecha de la manera dia/mes/año, tenemos que sacar el formato
    // y guardar en cada variable los datos correspondientes
    //Comprobamos el formato
    if(sscanf(c,"%d/%d/%d",&dia_,&mes_,&anno_)!=3){
        Fecha::Invalida F_Invalido("ERROR: Formato de fecha incorrecto");
    }
       *this = Fecha(dia_,mes_,anno_);
}
// //Implementación del operador de conversion a const char*
// Fecha::operator const char*()const noexcept{
//     //Comprobamos que no se haya actualizado la fecha antes
//     if(!actual){//se introduce por primera vez
//         actualizar();
//         actual = true; //actualizada
//     }
//     return crep;
// }

const char* Fecha::cadena() const noexcept{
    if(!actual){
        actualizar();
        actual = true;
    }
    return crep;
}

//Implementación de los operadores de incremento y decremento
Fecha& Fecha::operator +=(int n){
    time_t tiempo_hasta_ahora = time (NULL);
	struct tm* fecha = localtime(&tiempo_hasta_ahora);
    fecha->tm_mday = dia_+n;
    fecha->tm_mon = mes_ -1;
    fecha->tm_year = anno_ -1900;
    mktime(fecha);

    //modificamos los atributos de esa fecha
    dia_ = fecha->tm_mday;
    mes_ = fecha->tm_mon+1;
    anno_ =fecha->tm_year+1900;
    
    //Comprobamos que la fecha sea válida
    comprueba_fecha();
    return *this; //devolvemos la fecha modificada
}
Fecha& Fecha::operator -= (int n){return *this += -n;}
Fecha& Fecha::operator ++(){return *this += 1;}
Fecha Fecha::operator ++(int){
    Fecha fecha = *this;
    *this +=1;
    return fecha;
}
Fecha& Fecha::operator --(){return *this += -1;}
Fecha Fecha::operator --(int){
    Fecha fecha = *this;
    *this += -1;
    return fecha;
}
Fecha Fecha::operator +(int n)const{
    Fecha fecha=*this;
    return fecha += n;
}
Fecha Fecha::operator -(int n)const{
    Fecha fecha=*this;
    return fecha += -n;
}

//Operadores aritméticos
bool operator == (const Fecha& f1, const Fecha&f2){
    return (f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia()==f2.dia());
}
bool operator !=(const Fecha&f1, const Fecha&f2){
    return !(f1==f2);
}
bool operator <(const Fecha& f1, const Fecha& f2){
    return(f1.anno() < f2.anno() || (f1.anno() == f2.anno() && (f1.mes() < f2.mes()
        || (f1.mes() == f2.mes() && f1.dia() < f2.dia()))));
}
bool operator <=(const Fecha&f1, const Fecha& f2){
    return !(f2<f1);
}
bool operator >(const Fecha& f1, const Fecha& f2){
    return f2 < f1;
}
bool operator >=(const Fecha& f1, const Fecha& f2){
    return !(f1<f2);
}

//Operadores de flujo
std::ostream& operator << (std::ostream& output, const Fecha& f)noexcept{
    return output<<f.cadena();
}
std::istream& operator >>(std::istream& input, Fecha& f){
    //reservamos memoria para la nueva cadena introducida
    char nuevafecha[12]=""; 
    //obtenemos lo introducido por teclado+
    input.width(12);
    input >> nuevafecha;
    //comprobamos que la fecha es válida
    try{
        f= nuevafecha;
    }catch(const Fecha::Invalida e){
        input.setstate(std::ios::failbit);
        throw e;
    }
    return input;
}
/*
Hecho por: Jose Luis Venega Sánchez
*/