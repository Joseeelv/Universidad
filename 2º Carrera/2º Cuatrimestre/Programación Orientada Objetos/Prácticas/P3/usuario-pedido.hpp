#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

//Incluimos cabeceras
#include "usuario.hpp"
#include "pedido.hpp"

//declaraciones adelantadas
class Pedido;
class Usuario;

class Usuario_Pedido{
    public:
        //asociacion uno-a-varios entre Usuario y Pedido,
        //es decir para 1 usuario hay muchos pedidos y
        //un pedido tiene a un único usuario
        typedef std::set<Pedido*>Pedidos;
        typedef std::map<Usuario*,Pedidos>UsuarioPedidos;
        typedef std::map<Pedido*,Usuario*>PedidoUsuario;

        //el método asocia, tiene dos parámetros de tipo Usuario y Pedido, 
        //que se ocupa de enlazar los objetos en ambos sentidos
        void asocia(Usuario&,Pedido&)noexcept;
        void asocia(Pedido&,Usuario&)noexcept;

        //pedidos recibe un Usuario y devuelve los pedidos que éste ha realizado.
        Pedidos& pedidos(Usuario& )noexcept;
        //cliente recibe un Pedido y devuelve la dirección de memoria del usuario que ha hecho el pedido.
        Usuario* cliente(Pedido& )noexcept;
    private:
        UsuarioPedidos usuariopedidos_;
        PedidoUsuario  pedidousuario_;
};


#endif //!USUARIO_PEDIDO.HPP