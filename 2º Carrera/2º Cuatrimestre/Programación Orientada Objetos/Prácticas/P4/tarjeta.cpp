#include "tarjeta.hpp"

//inicialización del conjunto estático de tarjetas
std::set<Numero> Tarjeta::tarjetas_;
//Hacemos uso del algoritmo de luhn para ver si el numero de la tarjeta es correcto o no
bool luhn(const Cadena& numero);

/*-----Práctica 3-----*/
// Reimplemente la retirada de espaciado en blanco y la detección de caracteres no numé-
// ricos en el constructor de la clase Numero utilizando los algoritmos de la STL remove_if
// y find_if. Cada uno de estos algoritmos recibe un predicado (clase de objetos función
// cuyo operador () devuelve un valor booleano). Necesitará dos, uno para cada algoritmo:
// • Para remove_if defina uno llamado Numero::EsBlanco para detectar espaciado en
// blanco, o bien use una función anónima (λ) de C++11. Si elige la primera opción,
// defina este predicado como una clase anidada pública de Numero.
// • Para find_if defina otro llamado Numero::EsDigito para detectar dígitos, y combíne-
// lo con el adaptador de negación unaria disponible en <functional> para detectar
// caracteres que no sean dígitos. Defina la clase anidada Numero::EsDigito como
// miembro público. Así se podrá usar en el exterior de Numero, en particular, en los
// programas de prueba de las prácticas.

//Hacemos los dos objetos a función

// class EsBlanco: public std::unary_function<char,bool>
// {
//     public:
//         bool operator ()(char caracter)const {return isspace(caracter);}
// };


/*-----Clase Numero----- -> Se incluye la verificación de si hay espacio en blanco
                            , si es digito y la comprobación de la longitud*/
Numero::Numero(const Cadena& numero){
    Cadena aux(numero);
    //Práctica 2
        // char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ./";
        //Comprobamos que está en el rango de caracteres
        // if(strcspn(numero_.operator const char *(),caracteres)<numero_.length())

    //Práctica 3
    //hacemos uso de los predicados para los algoritmos remove_if, find_if
    //Eliminamos los espacios del numero
    auto quitaespacios = std::remove_if(aux.begin(),aux.end(),[](char c){return isspace(c);});
    //Modificamos el número fisicamente
    aux = aux.substr(0, quitaespacios-aux.begin());
    // auto i = std::remove_if(aux.begin(),aux.end(),EsBlanco());
    // if(i != aux.end()){
    //     *i = '\0'; //el ultimo caracter será el terminador
    //     aux=Cadena(aux.operator const char *()); //devolvemos la cadena de bajo nivel
    // }

    //negamos que sea un digito y buscamos caracteres que no sean digitos
    auto NotDigito = not_fn(EsDigito());
    auto j = std::find_if(aux.begin(),aux.end(),NotDigito);

    if(j!=aux.end()) //si encuentra un caracter no numérico, excepción
        throw Incorrecto(Razon::DIGITOS); 

    if(aux.length()>19 || aux.length() < 13 || aux.length() == 0)
        throw Incorrecto(Razon::LONGITUD);

    //comprobamos que sea correcto
    if(!luhn(aux))
        throw Incorrecto(Razon::NO_VALIDO);

    //actualizamos el numero sin espacios ni caracteres no numéricos
    numero_ = aux;

}
bool operator < (const Numero& a, const Numero& b){
    return strcmp(a,b)<0;
}
/*-----Práctica 2-----*/
//metodos privados de la clase
// Cadena Numero::eliminar_espacios(const Cadena& cadena){
//     //creamos una cadena nueva como copia de la introducida
//     Cadena aux(cadena);
//     //Practica 2
//         // const char* original = cadena.operator const char *();
//         //hacemos uso del método remove_if de la stl
//         //esto lo que hace que elimina si encuentra un espacio, hacemos uso de una funcion lamda
//         // int j =0;
//         // for(size_t i =0; i!=strlen(original); i++){
//         //     if(!isspace(original[i])){
//         //         aux[j++] = original[i];
//         //     }
//         // }
//         // aux[j] = '\0';
// }

// Cadena Numero::longitud(const Cadena& cadena){
//     //creamos una cadena como copia de la introducida para calcular la longitud sin espacios
//     Cadena aux = eliminar_espacios(cadena);
//     if(aux.length()>19 || aux.length() < 13 || aux.length() == 0)
//         throw Incorrecto(Razon::LONGITUD);
//     return aux;
// }

/*-----Clase Tarjeta-----*/
Tarjeta::Tarjeta(const Numero& numero,  Usuario& titular, const Fecha& caducidad):
    numero_(numero),titular_(&titular),caducidad_(caducidad){
    //Tarjeta caducada
    if(caducidad_ < Fecha()) throw Caducada(caducidad_);

    //Comprobamos que la tarjeta no está registrada
    if(!tarjetas_.insert(numero_).second) throw Num_duplicado(numero_);

    //No caducada y numero correcto -> se asigna al usuario
    activa_ = true; //activamos la tarjeta
    titular.es_titular_de(*this);
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
    //Por tanto, convertirmos el usuario constante a no constante
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
    case Tarjeta::Otro: output<<"Tipo indeterminado"<<std::endl; break;
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
