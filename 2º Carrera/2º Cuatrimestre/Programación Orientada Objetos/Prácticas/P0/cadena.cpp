#include "cadena.hpp"
//Definimos la variable estática
char Cadena::vacia[1]={'\0'};

/*-----Métodos publicos de la clase Cadena-----*/
//Constructores de la clase cadena
Cadena::Cadena(size_t tam, char c):tam_(tam),s_(vacia){
    if(tam_>0){
        s_ = new char[tam_+1];
        for(size_t i=0; i<tam_ ;i++){
            s_[i]=c;
            
        }
        s_[tam_] =vacia[0];
    }
}

Cadena::Cadena(const Cadena& other):tam_(other.tam_),s_(vacia){
    if(tam_>0){
       s_= new char[tam_+1];
       //hacemos uso de strcpy
        strcpy(s_,other.s_);
        s_[tam_] =vacia[0];
    }
}

Cadena::Cadena (const char* c):tam_(strlen(c)), s_(vacia){
    if(tam_>0){
        s_ = new char[tam_+1];
        strcpy(s_,c);
         s_[tam_]=vacia[0];
    }
}

//Operadores de asignación por copia
Cadena& Cadena::operator = (const Cadena& other)noexcept{
    //evitamos autoasignación
    if(this!=&other){
        if(tam_ > 0){
            delete[] s_;
        }
        tam_ = other.tam_;
        if(other.tam_ > 0){
        s_ = new char[tam_+1];
        strcpy(s_,other.s_);
        }else{
            s_ = vacia;}
    }
    return *this;
}


Cadena& Cadena::operator =(const char* c)noexcept{
    if(*this!=c){
        if(tam_ > 0){
            delete [] s_;
        }
        tam_ = strlen(c);
        if(strlen(c)>0){
            s_ = new char [tam_+1];
            strcpy(s_,c);
        }
        else{ s_ = vacia;
        }
    }
    return *this;
}

//Concatenación de cadenas
Cadena& Cadena::operator +=(const Cadena& other)noexcept{
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

Cadena operator +(const Cadena&c1, const Cadena& c2)noexcept{
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
    if(index < tam_){
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
    if(tam_>0){
        delete [] s_;
    }
    
}

//Operadores lógicos
bool operator == (const Cadena& cadena1, const Cadena& cadena2)noexcept{
    return (strcmp(&cadena1[0],&cadena2[0])==0);
}
bool operator !=(const Cadena& cadena1, const Cadena& cadena2)noexcept{
    return !(cadena1==cadena2);
}

bool operator <(const Cadena& cadena1, const Cadena& cadena2)noexcept{
    return (strcmp(&cadena1[0],&cadena2[0])<0);
}
bool operator <=(const Cadena& cadena1, const Cadena& cadena2)noexcept{
    return !(cadena2<cadena1);
}

bool operator > (const Cadena& cadena1, const Cadena& cadena2)noexcept{
    return cadena2<cadena1;
}

bool operator >=(const Cadena& cadena1, const Cadena& cadena2)noexcept{
    return !(cadena1<cadena2);
}