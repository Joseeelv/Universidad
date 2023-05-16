//
//Jose Luis Venega Sánchez P2
//
#include "usuario.hpp"

std::unordered_set<Cadena> Usuario::usuario_;

//##### IMPLEMENTACION CLASE CLAVE #####
Clave::Clave(const char* c){
    //comprobamos que la clave a encriptar sea valida
    if(strlen(c)< 5){
        throw Incorrecta(Razon::CORTA);
    }else{
        //creamos la cadena que nos ayudará a encriptar
        const char* encryp = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
        //realizamos el cifrado de la constraseña
        std::random_device random;
        std::uniform_int_distribution<> distribucion(0,63);
        char cifrado[2]={encryp[distribucion(random)],encryp[distribucion(random)]};
        //comprobamos que el cifrado no sea nulo
        if(crypt(c,cifrado)){
            //guardamos la contraseña cifrada
            password_ = crypt(c,cifrado);
        }else{
             throw Incorrecta(Razon::ERROR_CRYPT);
        }
    }
}

bool Clave::verifica(const char* c) const{
    return !strcmp(crypt(c,password_.operator const char *()), password_.operator const char *());
}

//##### IMPLEMENTACION CLASE USUARIO #####
//ctor
Usuario::Usuario(const Cadena& id,const Cadena& nombre,const Cadena& apellido,const Cadena& dir,const Clave& pass):
identificador_(id),nombre_(nombre),apellidos_(apellido),direccion_(dir),constraseña_(pass){
    //El constructor debe comprobar 
    //que el usuario que se va a construir sea correcto; 
    //es decir, que el identificador de usuario no esté repetido
    if(!usuario_.insert(id).second){
        throw Usuario::Id_duplicado(id);
        }
}

void Usuario::compra(Articulo& art, unsigned cantidad){
    if(cantidad!=0){ //se añade el articulo tantas veces como cantidad
        articulos_[&art] = cantidad;
    }
    else{
        articulos_.erase(&art);
    }
}

void Usuario::es_titular_de(Tarjeta& t){
    //vinculamos la tarjeta al usuario actual
    if(this == t.titular()){
        tarjetas_.insert(std::make_pair(t.numero(),&t));
    }
}

void Usuario::no_es_titular_de(Tarjeta& t){
    //desvinculamos la tarjeta del usuario actual
    t.anula_titular();
    tarjetas_.erase(t.numero()); //eliminamos el numero de la tarjeta
}

std::ostream& operator << (std::ostream& out, const Usuario& user){
    out << user.identificador_ << "[" << user.constraseña_.clave().operator const char *() << "]" << user.nombre_
    << user.apellidos_ << "\n"<<user.direccion_ <<std::endl;
    out <<"Tarjetas:";
    //metemos en el flujo todas las tarjetas del user
    for(auto i =user.tarjetas().begin(); i!=user.tarjetas().end(); i++){
        out<<*i ->second<<std::endl;
    }
    return out; //devolvemos el flujo de salida
}


void mostrar_carro(std::ostream& out, const Usuario& user){
    out << "Carrito de compra de" << user.id() << "[Artículos: " << user.n_articulos() << "]" <<"\n"
    <<"Cant.Articulo"<<std::endl;

    //creamos una linea de iguales "estética"
    out << std::setw(95)<<" = " <<' '<<std::endl;

    //introducimos el nº articulos que hay en el carrito del usuario
    int n_art = user.n_articulos(); 
    //es mejor tener un while y un for que 2 for anidados
    while(n_art > 0){
        for(auto i = user.compra().begin(); i!=user.compra().end(); i++){
            out << std::setw(4)<< i->second <<" ["
            <<(*i ->first).referencia() <<"] \""
            <<(*i->first).titulo()<<"\", "
            <<(*i->first).f_publi().anno()<<". "
            <<std::fixed<<std::setprecision(2) << (*i->first).precio() <<" €" << std::endl;
            n_art --; //decrementamos el numero de articulos a medida que los vamos imprimiendo
        }
    }
}   
//el desctuctor desvincula el titular de la tarjeta y elimina dicho usuario
Usuario::~Usuario(){
    for(auto i = tarjetas_.begin() ; i!=tarjetas_.end();i++){
        i->second -> anula_titular();
    }
    usuario_.erase(identificador_);
}