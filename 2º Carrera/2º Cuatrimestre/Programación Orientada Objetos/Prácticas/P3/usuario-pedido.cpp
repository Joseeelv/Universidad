#include "usuario-pedido.hpp"

//Implementación de los métodos de la clase de asociación

void Usuario_Pedido::asocia(Usuario& u, Pedido& p)noexcept{
    usuariopedidos_.insert(std::make_pair(&u,&p));
    pedidousuario_[&p]=&u;
}

void Usuario_Pedido::asocia(Pedido& p, Usuario& u)noexcept{
    //delegamos en el método anterior
    asocia(u,p);
}

const Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& u)const noexcept{
    //comprobamos que existe el usuario
    auto i = usuariopedidos_.find(&u);
    if(i!=usuariopedidos_.end()) return i->second;
    else{
        Usuario_Pedido::Pedidos pedidovacio;
        return pedidovacio;
    }
}

const Usuario_Pedido::PedidoUsuario& Usuario_Pedido::cliente(Pedido& p)const noexcept{
    //devolvemos el usuario de dicho pedido
    return pedidousuario_[&p];
}
