//
//Jose Luis Venega Sánchez P2
//
#include "tarjeta.hpp"


//declaracion adelantada
std::set<Numero> Tarjeta::tarjetas_;
bool luhn(const Cadena& n); //funcion bool que nos hará falta para calcular si

//##### CLASE NUMERO #####
// es valido o no el numero de la tarjeta 
Numero::Numero(const Cadena& num):numero_(longitud(num)){
    //comprobamos que el numero digitos sea valido
    if(std::count_if(numero_.begin(), numero_.end(), static_cast<int(*)(int)>(std::isdigit)) != numero_.length()){
        throw Incorrecto (Razon::DIGITOS);
    }
    //comprobamos que el numero sea valido "algoritmo Luhn"
    if(!luhn(numero_)){
        throw Incorrecto (Razon::NO_VALIDO);
    }
}
bool operator < (const Numero& a, const Numero& b){
   return strcmp(a,b)<0;
}

Numero::operator const char*() const{
    return numero_.operator const char *();
}

Cadena Numero::eliminar_espacios(const Cadena& n){
    Cadena aux(n); //creamos una cadena auxiliar

    std::remove_if(aux.begin(),aux.end()+1, [](char c){return isspace(c);});
    return Cadena(aux.operator const char *());
}

Cadena Numero::longitud(const Cadena& n){
    //Creamos una cadena auxilar para calcular su long sin espacios
    Cadena aux = eliminar_espacios(n);
    //Un número de tarjeta de pago válido debe contener solo dígitos, 
    //y esta cadena de solo dígitos debe tener una longitud comprendida entre 13 y 19,
    if(aux.length() > 19 || aux.length() <13 || aux.length()==0) throw Incorrecto(Razon::LONGITUD);

    return aux; //devolvemos la long de la tarjeta sin espacos.
}
//##### CLASE TARJETA #####
Tarjeta::Tarjeta(const Numero& n, Usuario& user,const Fecha& f):numero_(n), usuario_(&user), caduc_(f), activa_(true){
    //comprobamos que la fecha es válida
    if(caduc_ < Fecha()){
        throw Caducada(caduc_);
    }
    if(!tarjetas_.insert(n).second){ //comprobamos si la tarjeta está duplicada
        throw Num_duplicado(n);
    }
    //creamos una cadena auxiliar la cual contendrá el numero de la tarjeta
    //asignamos la tarjeta a su ususario
    usuario_->es_titular_de(*this);
}
void Tarjeta::anula_titular(){
    //anulamos la tarjeta desvinculandola del usuario
    activa_= false;
    (Usuario*&)usuario_ = nullptr;
}
std::ostream& operator << (std::ostream& out, const Tarjeta& t){
    //obtenemos el nombre y apellidos del titular
    Cadena nom_titular = t.titular()->nombre()+ " " + t.titular()->apellidos();
    int i =0;
    //rellenamos las cadenas "mayusculas --> toupper"
    while (nom_titular[i]!='\0') //hacer hasta que se acabe la cadena nombre del titular
    {
        if(islower(nom_titular[i])) 
            nom_titular[i] = toupper(nom_titular[i]);
        i++;
    }
    //como la fecha es MM/AA usamos setfill para introducir caracteres y 
    //setw(2) para decir cual es el rango en este caso 2 para mes y año
    out << t.tipo()<<"\n"
    <<t.numero()<<"\n"
    <<nom_titular<<"\n"
    <<"Caduca:"
    <<std::setfill('0')<<std::setw(2)<<t.caducidad().mes()
    <<"/"
    <<std::setw(2)<<(t.caducidad().anno() % 100)<<std::endl;
    return out; //devolvemos por el flujo de salida
}
Tarjeta::Tipo Tarjeta::tipo()const {
     //vemos a que "compañía" pertenece la tarjeta
    switch (numero_[0])
    {
    case '3':
            if(numero_[1]=='4'||numero_[1]=='7'){return Tipo::AmericanExpress;}
            else{return Tipo::JCB;} 
            break;
    case '4': return Tipo::VISA;
            break;
    case '5': return Tipo::Mastercard;
            break;
    case '6': return Tipo::Maestro;
            break;
    default:return Tipo::OTRO;
            break;
    }
}
std::ostream& operator <<(std::ostream& out, const Tarjeta::Tipo& t){
    switch (t)
    {
    case Tarjeta::OTRO: out << "OTRO" <<std::endl;
        break;
    case Tarjeta::VISA: out << "VISA" <<std::endl;
        break;
    case Tarjeta::Mastercard: out << "Mastercard" <<std::endl;
        break;
    case Tarjeta::Maestro: out << "Maestro" <<std::endl;
        break;
    case Tarjeta::JCB: out << "JCB" <<std::endl;
        break;
    case Tarjeta::AmericanExpress: out << "AmericanExpress" <<std::endl;
    default: out<< "Otra" <<std::endl;
        break;
    }
    return out; //devolvemos por el flujo de salida
}

bool operator < (const Tarjeta& a, const Tarjeta& b){
    return a.numero() < b.numero();
}

Tarjeta::~Tarjeta(){
    //para elmininar la tarjeta, la desvinculamos del usuario "no_es_titular()"
    if(Usuario* user = const_cast<Usuario*>(usuario_)){
        user->no_es_titular_de(*this);
    }
    tarjetas_.erase(numero_);
}
