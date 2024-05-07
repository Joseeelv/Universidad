#include "usuario-pedido.hpp"

//Implementación de los métodos de la clase de asociación

void Usuario_Pedido::asocia(Usuario& u, Pedido& p)noexcept{
    usuariopedidos_[&u].insert(&p);
    pedidousuario_[&p]=&u;
}

void Usuario_Pedido::asocia(Pedido& p, Usuario& u)noexcept{
    //delegamos en el método anterior
    asocia(u,p);
}

Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& u) noexcept{
    //comprobamos que existe el usuario
    return usuariopedidos_.find(&u)->second;
}

Usuario* Usuario_Pedido::cliente(Pedido& p)noexcept{
    //devolvemos el usuario de dicho pedido
    auto i = pedidousuario_.find(&p);
    if(i!=pedidousuario_.end())return i->second;
    else return nullptr;
}
