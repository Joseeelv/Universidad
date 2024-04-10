#include "usuario.hpp"

//Inicialización del conjunto global de usuarios
std::unordered_set<Cadena>Usuario::usuario_;
/*---Clase Clave----*/
Clave:: Clave(const char* c):password_(c){
    //Comprobamos tamaño de la clave
    if(strlen(c)<5){
        throw Incorrecta(Razon::CORTA);
    }
    else{
        //Encriptamos la clave nueva
        const char* valores ="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
        std::random_device random;
        std::uniform_int_distribution<>distribucion(0,63);
        char cifrado[2]={valores[distribucion(random)],valores[distribucion(random)]};
        //comprabamos que el cifrado sea correcto, si no excepción
        if(crypt(c,cifrado)){
            password_ = crypt(c,cifrado);
        }else{
            throw Incorrecta(Razon::ERROR_CRYPT);
        }
    }
}
bool Clave::verifica(const char* clave)const{
    //compara la encriptación de la clave que hemos metido concuerda con una de las claves
    return !strcmp(crypt(clave,password_.operator const char *()),password_.operator const char *());
}

/*-----Clase Usuario-----*/
Usuario::Usuario(const Cadena& id ,const Cadena& nom, const Cadena& apell ,const Cadena& dir ,const Clave& clave):
    identificador_(id),nombre_(nom),apellidos_(apell),direccion_(dir),clave_(clave){
    //Vamos a compromar si el usuario no existe en la lista de usuarios del programa
    if(!usuario_.insert(id).second)throw Usuario::Id_duplicado(id);
}
void Usuario::es_titular_de(Tarjeta& t) noexcept{
    //asosicamos el usuario con la tarjeta
    if(this==t.titular()){
        tarjetas_.insert(std::make_pair(t.numero(),&t));
    }
}

void Usuario::no_es_titular_de(Tarjeta& t) noexcept{
    //desvinculamos el usuario con la tarjeta
    t.anula_titular();
    tarjetas_.erase(t.numero());
}

void Usuario::compra(Articulo& art, size_t cantidad) noexcept{
    //si la cantidad del articulo es > 0 -> se añade; si no se elimina
    if(cantidad > 0)articulos_[&art]=cantidad;
    else articulos_.erase(&art);
}

Usuario::~Usuario(){
    //Para eliminar al usuario tenemos que desligar todas sus tarjetas y luego
    //eliminarlo
    for(auto i = tarjetas_.begin(); i!=tarjetas_.end();i++){
        i->second->anula_titular();
    }
    usuario_.erase(identificador_);
}
 
void mostrar_carro(std::ostream& output , const Usuario& user){
    output << "Carrito de compra de "<<user.id()<<"[Artículos: "<<user.n_articulos()<<"]"<<std::endl
           << "Cant. Artículo"<<std::endl
           <<std::setw(95)<<" = " <<' '<<std::endl; //estética del formato
    //creamos una variable para tener control del numero de articulos del carro
    size_t n_art = user.n_articulos();
    while(n_art > 0){
        for(auto i=user.compra().begin();i!=user.compra().end();i++){
            output<<std::setw(4)<< i->second
              <<"["<<(*i->first).referencia()<<"] "<<"\""
              <<(*i->first).titulo()<<"\""<<", "
              <<(*i->first).f_publi().anno()<<". "
              <<std::fixed<<std::setprecision(2)<<(*i->first).precio()<<" €"<<std::endl;
            n_art--;
        }
    }
}
std::ostream& operator <<(std::ostream& output , const Usuario& user)noexcept{
    output << user.id() <<"["<<user.clave_.clave().operator const char *()<<"]"<<user.nombre()
    <<user.apellidos()<<std::endl <<user.direccion()<<std::endl;
    output<<"Tarjetas:";
    for(auto i = user.tarjetas().begin(); i!=user.tarjetas().end(); i++)
        output<< *i->second << std::endl;
    return output;
}
