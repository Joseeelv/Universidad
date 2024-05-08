#include "tarjeta.hpp"

//inicialización del conjunto estático de tarjetas
std::set<Numero> Tarjeta::tarjetas_;
//Hacemos uso del algoritmo de luhn para ver si el numero de la tarjeta es correcto o no
bool luhn(const Cadena& numero);
/*-----Clase Numero-----*/
Numero::Numero(const Cadena& numero):numero_(longitud(numero)){
    char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ./";
    //Comprobamos que está en el rango de caracteres
    if(strcspn(numero_.operator const char *(),caracteres)<numero_.length())
        throw Incorrecto(Razon::DIGITOS);
    //comprobamos que sea correcto
    if(!luhn(numero_))throw Incorrecto(Razon::NO_VALIDO);
}
bool operator < (const Numero& a, const Numero& b){
    return strcmp(a,b)<0;
}

//metodos privados de la clase
Cadena Numero::eliminar_espacios(const Cadena& cadena){
    //creamos una cadena nueva como copia de la introducida
    Cadena aux(cadena);
    const char* original = cadena.operator const char *();
    int j =0;
    for(size_t i =0; i!=strlen(original); i++){
        if(!isspace(original[i])){
            aux[j++] = original[i];
        }
    }
    aux[j] = '\0';
    return Cadena(aux.operator const char *());
}
Cadena Numero::longitud(const Cadena& cadena){
    //creamos una cadena como copia de la introducida para calcular la longitud sin espacios
    Cadena aux = eliminar_espacios(cadena);
    if(aux.length()> 19 || aux.length() < 13 || aux.length() <= 0)
        throw Incorrecto(Razon::LONGITUD);
    return aux;
}

/*-----Clase Tarjeta-----*/
Tarjeta::Tarjeta(const Numero& numero,  Usuario& titular, const Fecha& caducidad):
    numero_(numero),titular_(&titular),caducidad_(caducidad),activa_(true){
    if(caducidad_ < Fecha())throw Caducada(caducidad_); //caducada¿?
    //Comprobamos que la tarjeta no está registrada
    if(!tarjetas_.insert(numero).second)throw Num_duplicado(numero);
    //No caducada y numero correcto -> se asigna al usuario
    titular_ -> es_titular_de(*this);
}
Tarjeta::Tipo Tarjeta::tipo()const noexcept{
    switch (numero_[0]){
    case '3':
        if(numero_[1]=='4' || numero_[1]=='7') return Tipo::AmericanExpress;
        else return Tipo::JCB;
        break;
    case '4': return Tipo::VISA; break;
    case '5': return Tipo::Mastercard; break;
    case '6': return Tipo::Maestro; break;
    default: return Tipo::Otro; break;
    }
}

Tarjeta::~Tarjeta(){
    //Para poder eliminar una tarjeta, primero debemos de desvincularla de su titular
    if(Usuario* user = const_cast<Usuario*>(titular_)) user->no_es_titular_de(*this);
    tarjetas_.erase(numero_); //eliminamos despues de desvincular
}

bool operator <(const Tarjeta& a,const Tarjeta& b){
    return a.numero() < b.numero();
}

std::ostream& operator <<(std::ostream& output, const Tarjeta& t)noexcept{
    //primero tenemos que concatenar el nombre y el apellido del titular
    Cadena nombre_apell = t.titular()->nombre() + " " + t.titular()->apellidos();
    //las tenemos que imprimir en mayusculas
    int i =0;
    while(nombre_apell[i]!='\0'){
        if(islower(nombre_apell[i]))
            nombre_apell[i]=toupper(nombre_apell[i]);
        i++;
    }
    output<<std::setw(2)<<std::setfill(' ')<<' '<<t.tipo()
    <<std::setw(2)<<std::setfill(' ')<<' '<<t.numero()<<"\n"
    <<std::setw(2)<<std::setfill(' ')<<' '<<nombre_apell<<"\n"
    <<std::setw(2)<<std::setfill(' ')<<' '<<"Caduca: "<<std::setfill('0')<<std::setw(2)<<t.caducidad().mes()
    <<"/"<<std::setw(2)<<(t.caducidad().anno() % 100)<<std::endl;
    return output;
}

std::ostream& operator <<(std::ostream&output, const Tarjeta::Tipo& tipo )noexcept{
    switch (tipo){
    case Tarjeta::Otro: output<<"Otro"<<std::endl; break;
    case Tarjeta::VISA: output<<"VISA"<<std::endl; break;
    case Tarjeta::Mastercard: output<<"Mastercard"<<std::endl;break;
    case Tarjeta::Maestro: output<<"Maestro"<<std::endl; break;
    case Tarjeta::JCB: output<<"JCB"<<std::endl; break;
    case Tarjeta::AmericanExpress: output<<"AmericanExpress"<<std::endl; break;
    default: output<<"Otra"<<std::endl;break;
    }
    return output;
}

void Tarjeta::anula_titular(){
    (Usuario*&) titular_=nullptr;
    activa_=false;
}
