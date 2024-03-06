#include "cadena.hpp"
//Definimos la variable estática
char Cadena::vacia[1] = {'\0'};

/*-----Métodos publicos de la clase Cadena-----*/
//Constructores de la clase cadena
Cadena::Cadena(size_t tam, char c):tam_(tam),s_(vacia){
    if(tam_<0){
        //No podemos crear una cadena con valor negativo
        throw std::length_error("Tamaño de la cadena no permitido");
    }
    //Dependiendo del tamaño introducido, se crea de una manera u otra;
    else if(tam_>0){
        char* s_ = new char[tam_];
        for(size_t i=0; i<tam_ ;i++){
            s_[i]=c;
        }
    }
}

Cadena::Cadena(const Cadena& other):s_(new char[other.tam_+1]), tam_(other.tam_){
    //hacemos uso de strcpy
    strcpy(s_,other.s_);
}

Cadena::Cadena (const char* c):tam_(strlen(c)), s_(new char[tam_+1]){
    strcpy(s_,c);
}

//Operadores de asignación por copia
Cadena& Cadena::operator = (const Cadena& other){
    //evitamos autoasignación
    if(this!=&other){
        delete[] s_;
        tam_ = other.tam_;
        s_ = new char[tam_+1];
        strcpy(s_,other.s_);
    }
    return *this;
}
Cadena& Cadena::operator =(const char* c){
    if(*this!=c){
        delete[]s_;
        tam_ = strlen(c);
        s_ = new char [tam_+1];
        strcpy(s_,c);
    }
    return *this;
}
Cadena::operator const char*(){
    const char* c = s_;
    return c;
}

//Concatenación de cadenas
Cadena& Cadena::operator +=(const Cadena& other){
    //Creamos una cadena nueva que contedrá las dos cadenas concatenadas
    char* concatenada = new char [tam_+1];
    //Copiamo una de las cadenas
    strcpy(concatenada,s_);
    //Modificamos el tamaño
    tam_ += other.tam_;
    //destruimos la cadena original y la reemplazamos
    delete [] s_;
    s_ = new char[tam_+1];
    //Concatenamos dos cadenas
    strcpy(s_,concatenada);
    strcat(s_,other.s_);

    //eliminamos la cadena auxiliar
    delete [] concatenada;
    //devolvemos la cadena final concatenada
    return *this;
}

Cadena operator +(const Cadena&c1, const Cadena& c2){
    //Creamos una cadena nueva -> resultante de la concatenación
    Cadena auxiliar(c1);
    //devolvemos la cadena concatenada
    return auxiliar += c2;
}

//Operadores de índice
char& Cadena::at(size_t index){
    if(index<tam_){
        return s_[index];
    }
    else{
        throw std::out_of_range("ERROR at(): El indice supera el tamaño maximo de la cadena");
    }
}
char& Cadena::at(size_t index)const{
    if(index <tam_){
        return s_[index];
    }
    else{
        throw std::out_of_range("ERROR at(): El indice supera el tamaño maximo de la cadena");
    }
}

Cadena Cadena::substr(unsigned index, size_t tama)const{
    if(index + tama > tam_ || tama > tam_ || index > tam_){
        throw std::out_of_range("ERROR substr(): Los valores dados superan el tamaño maximo de la cadena");
    }
    else{
        //Creamos una cadena para imprimir la subcadena
        Cadena subcadena(tama);
        //Guardamos esa subcadena (indice + tam);
        strncpy(subcadena.s_,s_+index, tama);
        subcadena.s_[tama]='\0';
        //devolvemos la subcadena
        return subcadena;
    }
}

//Destructor de cadena
Cadena::~Cadena(){
    delete [] s_;
    tam_ = 0;
}

//Operadores lógicos
bool operator == (const Cadena& cadena1, const Cadena& cadena2) {
    return (std::strcmp(static_cast<const char*>(cadena1), static_cast<const char*>(cadena2)) == 0);
}
bool operator !=(const Cadena& cadena1, const Cadena& cadena2){
    return !(cadena1==cadena2);
}

bool operator <(const Cadena& cadena1, const Cadena& cadena2){
    return (std::strcmp(static_cast<const char*>(cadena1), static_cast<const char*>(cadena2)) < 0);
}
bool operator <=(const Cadena& cadena1, const Cadena& cadena2){
    return !(cadena2<cadena1);
}

bool operator > (const Cadena& cadena1, const Cadena& cadena2){
    return cadena2<cadena1;
}

bool operator >=(const Cadena& cadena1, const Cadena& cadena2){
    return !(cadena1<cadena2);
}