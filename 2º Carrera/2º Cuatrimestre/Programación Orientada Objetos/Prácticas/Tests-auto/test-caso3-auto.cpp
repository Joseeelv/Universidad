/* $Id: test-caso3-auto.cpp 344 2016-04-29 20:20:13Z gerardo $
 * ©2014 Antonio G.ª Dguez.
 * ©2015-19 el resto de profesores de POO
 * ©2022-23 José Fidel
 *
 */

#include "test-auto.hpp"

using namespace std;

// Variables para el siguiente conjunto de casos de prueba. ¡No tocar!
namespace {
  const Cadena referencia("1234XYZ");
  const Cadena titulo("Prueba");
  const Fecha  fecha(10, 10, 2000);
  const Cadena sId("pperez");
  const Cadena sNombre("Perico");
  const Cadena sApellidos("Perez Palotes");
  const Cadena sDireccion("13 Rue del Percebe");
  const Clave  clave("pedrofueacomprarpan");
  const Numero nTarjeta("01234 56789 012 8");
  const Numero nTarjeta2("01234567890128");
  const Numero nTarjeta3("11234567890126");
  const Fecha  fHoy;
  const Fecha  fAyer = fHoy - 1;
  const Fecha  fUnaSemana = fHoy + 7;
  const Fecha  fSiguienteAnno(1, 1, fHoy.anno() + 1);
  const unsigned stock1 = 50;
  const unsigned stock2 = 50;
#ifdef P4
  Autor autor("Harry", "Potter", "Hogwarts");
  Articulo::Autores autores { &autor };
  Libro articulo1(autores, "111", "The Standard Template Library",
		  fHoy, 42.10, 200, stock1);
  Revista articulo2(autores, "110", "Programadores de C++",
		     fHoy, 11.95, 136, 30, stock2);
#else
  Articulo articulo1("111", "The Standard Template Library", fHoy, 42.10, stock1),
           articulo2("110", "Fundamentos de C++", fHoy, 35.95, stock2);
#endif
  Usuario         *pU, *pU2;
  Tarjeta         *pTarjetaU;
  const Tarjeta   *pTarjetaU2;
  Usuario_Pedido  *pAsocUsuarioPedido;
  Pedido_Articulo *pAsocPedidoArticulo;
  Pedido    *pPed1, *pPed2;
  const unsigned cantidad_A1_P1 = 1;
  const unsigned cantidad_A1_P2 = 3;
  const unsigned cantidad_A2_P2 = 5;
  int N_pedidos = 0;
  
  bool bPrimera = true;

  using TIPO = Tarjeta::Tipo;

  struct Usu_Ped {
      typedef std::set<Pedido*> Pedidos;
      std::map<Usuario*, Pedidos> pedidos_;
      std::map<Pedido*, Usuario*> cliente_;
  };

  struct Ped_Art {
    typedef std::map<Articulo*, LineaPedido, Pedido_Articulo::OrdenaArticulos> ItemsPedido; 
    typedef std::map<Pedido  *, LineaPedido, Pedido_Articulo::OrdenaPedidos  > Pedidos; 
    std::map<Pedido  *, ItemsPedido, Pedido_Articulo::OrdenaPedidos  > pedidos_articulos_;
    std::map<Articulo*, Pedidos    , Pedido_Articulo::OrdenaArticulos> articulos_pedidos_;
  };
}

FCTMF_FIXTURE_SUITE_BGN(test_p3_clases) {

  if (bPrimera) {
    bPrimera = false;
    cerr << "\n---------- PRÁCTICA 3 ----------\n" << endl;
  }

  // El éxito de las pruebas depende de su orden. ¡No reordenar!
  FCT_SETUP_BGN() {
    pAsocUsuarioPedido  = new Usuario_Pedido ;
    pAsocPedidoArticulo = new Pedido_Articulo;
    pU  = new Usuario(sId, sNombre, sApellidos, sDireccion, clave);
    pU2 = new Usuario("u2", "Mario", "Segali", "Mundo 1-1", "jumpman");
    pTarjetaU  = new Tarjeta(nTarjeta , *pU , fUnaSemana);
    pTarjetaU2 = new Tarjeta(nTarjeta3, *pU2, fUnaSemana);
  }
  FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    delete pTarjetaU2;
    delete pTarjetaU;
    delete pU2;
    delete pU;
    delete pAsocPedidoArticulo;
    delete pAsocUsuarioPedido;
  }
  FCT_TEARDOWN_END();

  // --- Pruebas de la clase LineaPedido

  FCT_TEST_BGN(LineaPedido - valor por defecto en 2do. parametro constructor) {
    const double pVenta  {  10.5  };
    const LineaPedido lp { pVenta /* , 1u */};
    fct_chk_eq_dbl(lp.precio_venta(), pVenta);
    fct_chk_eq_int(lp.cantidad    (),      1);
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(LineaPedido - constructor de 2 parametros) {
    const double      pVenta   { 7.3 };
    const unsigned    cantidad { 5   };
    const LineaPedido lp       { pVenta, cantidad };
    fct_chk_eq_dbl(lp.precio_venta(), pVenta  );
    fct_chk_eq_int(lp.cantidad()    , cantidad);
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(LineaPedido - insercion en flujo) {
    const LineaPedido lp { 9.2, 42 };
    chk_incl_cstr(toString(lp), "9,20 €");
    chk_incl_cstr(toString(lp), "42");
  }
  FCT_TEST_END();

  // --- Pruebas de Pedido

  FCT_TEST_BGN(Pedido - carrito vacio) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    try {
      Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU, fHoy};
      fct_xchk(false, "Se esperaba una excepción Pedido::Vacio");
    }
    catch(const Pedido::Vacio& ex) {
      fct_chk(&ex.usuario() == pU);
      fct_xchk(pU_P->pedidos_.empty(), "En pedido no viable: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "En pedido no viable: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "En pedido no viable: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "En pedido no viable: "
              "enlace Articulo-Pedido incorrecto.");
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido - impostor) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    pU2->compra(articulo1, 3);
    try {
      Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU2, *pTarjetaU, fHoy};
      fct_xchk(false, "Se esperaba una excepción Pedido::Impostor");
    }
    catch(const Pedido::Impostor& ex) {
      fct_chk(&ex.usuario() == pU2);
      fct_xchk(articulo1.stock() == stock1, "En pedido no viable: "
              "articulo1.stock() == %d != %d", articulo1.stock(), stock1);
      fct_xchk(pU_P->pedidos_.empty(), "En pedido no viable: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "En pedido no viable: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "En pedido no viable: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "En pedido no viable: "
              "enlace Articulo-Pedido incorrecto.");
      articulo1.stock() = stock1;
    }
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - sin stock) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    pU->compra(articulo1, 9001);
    pU->compra(articulo2, 5);
    try {
      Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU, fHoy};
      fct_xchk(false, "Se esperaba una excepción Pedido::SinStock");
    }
    catch (const Pedido::SinStock& ex) {
      fct_chk(&ex.articulo() == &articulo1);
      fct_xchk(pU->compra().empty(), "Pedido sin stock: carrito no vaciado.");
      fct_xchk(articulo1.stock() == stock1, "Vendido artículo de un pedido sin stock: "
              "articulo1.stock() == %d != %d", articulo1.stock(), stock1);
      fct_xchk(articulo2.stock() == stock2, "Vendido artículo de un pedido sin stock: "
              "articulo2.stock() == %d != %d", articulo2.stock(), stock2);
      fct_xchk(pU_P->pedidos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Articulo-Pedido incorrecto.");
      articulo1.stock() = stock1;
      articulo2.stock() = stock2;
      pU_P->pedidos_.clear();
      pU_P->cliente_.clear();
      pP_A->pedidos_articulos_.clear();
      pP_A->articulos_pedidos_.clear();
    }
    pU->compra(articulo1, 5);
    pU->compra(articulo2, 9001);
    try {
      Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU, fHoy};
      fct_xchk(false, "Se esperaba una excepción Pedido::SinStock");
    }
    catch (const Pedido::SinStock& ex) {
      fct_chk(&ex.articulo() == &articulo2);
      fct_xchk(pU->compra().empty(), "Pedido sin stock: carrito no vaciado.");
      fct_xchk(articulo1.stock() == stock1, "Vendido artículo de un pedido sin stock: "
              "articulo1.stock() == %d != %d", articulo1.stock(), stock1);
      fct_xchk(articulo2.stock() == stock2, "Vendido artículo de un pedido sin stock: "
              "articulo2.stock() == %d != %d", articulo2.stock(), stock2);
      fct_xchk(pU_P->pedidos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Articulo-Pedido incorrecto.");
    }
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - tarjeta caducada) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    pU->compra(articulo1, 4);
    try {
      Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU, fHoy + 30};
      fct_xchk(false, "Se esperaba una excepción Tarjeta::Caducada");
    }
    catch (const Tarjeta::Caducada& ex) {
      fct_chk(ex.cuando() == fUnaSemana);

      fct_xchk(articulo1.stock() == stock1, "En pedido no viable: "
              "articulo1.stock() == %d != %d", articulo1.stock(), stock1);
      fct_xchk(pU_P->pedidos_.empty(), "En pedido no viable: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "En pedido no viable: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "En pedido no viable: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "En pedido no viable: "
              "enlace Articulo-Pedido incorrecto.");
      articulo1.stock() = stock1;
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido - tarjeta desactivada) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    pU->compra(articulo2, 4);
    pTarjetaU->activa(false);
    try {
      Pedido(*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU, fHoy);
      fct_xchk(false, "Se esperaba una excepción Tarjeta::Caducada");
    }
    catch (const Tarjeta::Desactivada& ex) {
      fct_xchk(articulo2.stock() == stock2, "En pedido no viable: "
              "articulo1.stock() == %d != %d", articulo1.stock(), stock2);
      fct_xchk(pU_P->pedidos_.empty(), "En pedido no viable: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "En pedido no viable: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "En pedido no viable: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "En pedido no viable: "
              "enlace Articulo-Pedido incorrecto.");
      articulo2.stock() = stock2;
    }
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - actualizacion relacionados y asociaciones) {
    const unsigned int cantidad { 1u };
    pU->compra(articulo1, cantidad);
    pU->compra(articulo2, cantidad);
    const unique_ptr<Pedido> pPed {
      new Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU} 
    };
    ++N_pedidos;
    fct_xchk(pPed->n_total_pedidos() == N_pedidos, "Cantidad de pedidos incorrecta: "
             "pPed->n_total_pedidos() == %d != %d", pPed->n_total_pedidos(), N_pedidos);
    fct_xchk(pPed->numero() == N_pedidos, "Número de pedido incorrecto: "
             "pPed->numero() == %d != %d", pPed->numero(), N_pedidos);
    
    // Actualización de carrito y stock
    fct_xchk(pU->compra().empty(), "Carrito no vacío tras realizar pedido.");
    fct_xchk(articulo1.stock() == stock1 - cantidad, "Existencias de articulo no actualizadas: "
            "articulo1.stock() == %d != %d", articulo1.stock(), stock1 - cantidad);
    fct_xchk(articulo2.stock() == stock2 - cantidad, "Existencias de articulo no actualizadas: "
            "articulo2.stock() == %d != %d", articulo2.stock(), stock2 - cantidad);
    
    // Asociación Usuario-Pedido
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    fct_xchk(pU_P->cliente_[pPed.get()] == pU,
             "El usuario asociado al pedido no es el comprador.");
    if (pU_P->pedidos_[pU].size() == 1)
      fct_xchk(*pU_P->pedidos_[pU].begin() == pPed.get(),
               "El pedido asociado no corresponde al comprador.");
    else
      fct_xchk(false, "El número de pedidos asociados al usuario debe ser 1.");
    
    // Asociación Pedido-Artículo
    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    const Pedido_Articulo::ItemsPedido itPed {
      pP_A->pedidos_articulos_[pPed.get()]
	  };
    if (itPed.size() == 2) {
      // Los artículos deben ir ordenados por código de referencia
      auto it = itPed.cbegin();
      fct_xchk(it->first == &articulo2,
               "Artículo inesperado o desordenado en pedido.");
      fct_xchk(it->second.cantidad() == cantidad, "Cantidad incorrecta "
               "en pedido: %d != %d", it->second.cantidad(), cantidad);
      fct_xchk(it->second.precio_venta() == articulo2.precio(),
               "Precio de venta incorrecto en pedido: %f != %f",
               it->second.precio_venta(), articulo2.precio());
      ++it;
      fct_xchk(it->first == &articulo1,
               "Artículo inesperado o desordenado en pedido.");
      fct_xchk(it->second.cantidad() == cantidad, "Cantidad incorrecta "
               "en pedido: %d != %d", it->second.cantidad(), cantidad);
      fct_xchk(it->second.precio_venta() == articulo1.precio(),
               "Precio de venta incorrecto en pedido: %f != %f",
               it->second.precio_venta(), articulo1.precio());
    }
    else
      fct_xchk(false, "El pedido debería tener 2 artículos");
  }
  FCT_TEST_END();
}
FCTMF_FIXTURE_SUITE_END();

FCTMF_FIXTURE_SUITE_BGN(test_p3_asociaciones_e_informes) {
  
  // Batería de pruebas para las clases de asociación.
  // Simula dos pedidos de dos usuarios.  
  FCT_SETUP_BGN() {
    pAsocUsuarioPedido  = new Usuario_Pedido ;
    pAsocPedidoArticulo = new Pedido_Articulo;
    pU  = new Usuario(sId, sNombre, sApellidos, sDireccion, clave);
    pU2 = new Usuario("u2", "Mario", "Segali", "Mundo 1-1", "jumpman");
    pTarjetaU  = new Tarjeta(nTarjeta, *pU, fUnaSemana);
    pTarjetaU2 = new Tarjeta(nTarjeta3,*pU2,fUnaSemana);
    articulo1.stock() = stock1;
    articulo2.stock() = stock2;

    // Primer pedido
    pU->compra(articulo1, cantidad_A1_P1);
    pPed1 = new Pedido(*pAsocUsuarioPedido, *pAsocPedidoArticulo, 
		       *pU, *pTarjetaU, fHoy);
    ++N_pedidos;

    // Segundo pedido, de otro usuario
    pU2->compra(articulo1, cantidad_A1_P2);
    pU2->compra(articulo2, cantidad_A2_P2);
    pPed2 = new Pedido(*pAsocUsuarioPedido, *pAsocPedidoArticulo,
                       *pU2, *pTarjetaU2, fHoy);
    ++N_pedidos;
  };
  FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    delete pPed2;
    delete pPed1;
    delete pTarjetaU2;
    delete pTarjetaU;
    delete pU2;
    delete pU;
    delete pAsocPedidoArticulo;
    delete pAsocUsuarioPedido;
  }
  FCT_TEARDOWN_END();
  
  FCT_TEST_BGN(Pedido - observadores) {
    const Pedido& rPed {*pPed2};
    const double totalEsperado {articulo1.precio() * cantidad_A1_P2 +
                                articulo2.precio() * cantidad_A2_P2};
    fct_xchk(rPed.numero() == N_pedidos, "Número de pedido incorrecto: "
             "%d != %d", rPed.numero(), N_pedidos);
    fct_xchk(rPed.tarjeta() == pTarjetaU2,
             "La tarjeta asociada al pedido no es la del pago.");
    fct_xchk(rPed.fecha() == fHoy, "Fecha del pedido incorrecta.");
    fct_xchk(rPed.total() == totalEsperado, "Importe total de pedido incorrecto: "
             "%f != %f", rPed.total(), totalEsperado);
    fct_xchk(rPed.n_total_pedidos() == N_pedidos, "Cantidad de pedidos incorrecta: "
             "%d != %d", rPed.n_total_pedidos(), N_pedidos);
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - insercion en flujo) {
    const Pedido& rPed {*pPed1};
    const string sPed {toString(rPed)};
    chk_incl_cstr(sPed, "Núm. pedido:");
    chk_incl_cstr(sPed, "Fecha:"      );
    chk_incl_cstr(sPed, "Pagado con:" );
    chk_incl_cstr(sPed, "Tipo indeterminado" );
    chk_incl_cstr(sPed, "Importe:"    );
    chk_incl_str (sPed, toString(rPed.numero()));
    chk_incl_cstr(sPed, rPed.fecha().cadena()  );
    chk_incl_cstr(sPed, rPed.tarjeta()->numero()     );
    chk_incl_str (sPed, toEuros(rPed.total())  );
  }
  FCT_TEST_END();

  // Pruebas de la clase de asociación Pedido_Articulo

  FCT_TEST_BGN(Pedido---Articulo - OrdenaPedidos) {
    const Pedido_Articulo::OrdenaPedidos oP;
    fct_xchk(oP(pPed1, pPed2), "Ordenación incorrecta por número de pedido");
    fct_xchk(!oP(pPed2, pPed1), "Ordenación incorrecta por número de pedido");
    fct_xchk(!oP(pPed1, pPed1), "Ordenación incorrecta por número de pedido");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Articulo - OrdenaArticulos) {
    const Pedido_Articulo::OrdenaArticulos oA;
    fct_xchk(oA(&articulo2, &articulo1), "Ordenación incorrecta por referencia de articulo");
    fct_xchk(!oA(&articulo1, &articulo2), "Ordenación incorrecta por referencia de articulo");
    fct_xchk(!oA(&articulo1, &articulo1), "Ordenación incorrecta por referencia de articulo");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Articulo - pedir(Pedido, Articulo)) {
    double pvp {articulo1.precio()};
    unsigned cant {1u};
    // Añadir artículo2 a pedido1
    pAsocPedidoArticulo->pedir(*pPed1, articulo2, pvp);

    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    fct_xchk(pP_A->pedidos_articulos_[pPed1].find(&articulo2) != pP_A->pedidos_articulos_[pPed1].end(), 
             "Falta enlace pedido ---> articulo");
    fct_xchk(pP_A->articulos_pedidos_[&articulo2].find(pPed1) != pP_A->articulos_pedidos_[&articulo2].end(), 
             "Falta enlace articulo ---> pedido");
    fct_xchk(pP_A->pedidos_articulos_[pPed1][&articulo2].precio_venta() == pvp &&
             pP_A->pedidos_articulos_[pPed1][&articulo2].cantidad()     == cant &&
             pP_A->articulos_pedidos_[&articulo2][pPed1].precio_venta() == pvp &&
             pP_A->articulos_pedidos_[&articulo2][pPed1].cantidad() == cant,
             "Añadida LineaPedido con precio_venta o cantidad incorrectos");
  }
  FCT_TEST_END();
 
  FCT_TEST_BGN(Pedido---Articulo - pedir(Articulo, Pedido)) {
    double pvp {articulo1.precio()};
    unsigned cant {1u};
    // Añadir artículo2 a pedido1
    pAsocPedidoArticulo->pedir(articulo2, *pPed1, pvp);

    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    fct_xchk(pP_A->pedidos_articulos_[pPed1].find(&articulo2) != pP_A->pedidos_articulos_[pPed1].end(), 
             "Falta enlace pedido ---> articulo");
    fct_xchk(pP_A->articulos_pedidos_[&articulo2].find(pPed1) != pP_A->articulos_pedidos_[&articulo2].end(), 
             "Falta enlace articulo ---> pedido");
    fct_xchk(pP_A->pedidos_articulos_[pPed1][&articulo2].precio_venta() == pvp &&
             pP_A->pedidos_articulos_[pPed1][&articulo2].cantidad()     == cant &&
             pP_A->articulos_pedidos_[&articulo2][pPed1].precio_venta() == pvp &&
             pP_A->articulos_pedidos_[&articulo2][pPed1].cantidad() == cant,
             "Añadida LineaPedido con precio_venta o cantidad incorrectos");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Articulo - detalle de un pedido) {
    const Pedido_Articulo& rAsocPedidoArticulo = *pAsocPedidoArticulo;
    const auto& detalle { rAsocPedidoArticulo.detalle(*pPed1) };
    if (detalle.size() == 1) {
      const auto& it = detalle.cbegin();
      const LineaPedido& lp { it->second };
      fct_xchk(it->first == &articulo1, "Pedido 1 no incluye articulo 1");
      fct_xchk(lp.precio_venta() == articulo1.precio(), "Precio de venta en pedido 1 "
               "incorrecto: %f != %f", lp.precio_venta(), articulo1.precio());
      fct_xchk(lp.cantidad() == cantidad_A1_P1, "Cantidad vendida en pedido 1 incorrecta: "
               "%d != %d", lp.cantidad(), cantidad_A1_P1);
    }
    else
      fct_chk(!"El pedido debería tener un solo elemento");
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido---Articulo - ventas de un articulo vendido) {
    const Pedido_Articulo& rAsocPedidoArticulo { *pAsocPedidoArticulo };
    const auto& pedArticulo1 { rAsocPedidoArticulo.ventas(articulo1) };
    if (pedArticulo1.size() == 2) { // 2 pedidos de articulo1
      auto it = pedArticulo1.find(pPed1);
      fct_xchk(it->second.precio_venta() == articulo1.precio(), "Precio de articulo 1 "
               "en pedido 1 incorrecto: %f != %f", it->second.precio_venta(), articulo1.precio());
      fct_xchk(it->second.cantidad() == cantidad_A1_P1, "Cantidad de articulo 1 "
               "en pedido 1 incorrecta: %d != %d", it->second.cantidad(), cantidad_A1_P1);
      ++it;
      fct_xchk(it->second.precio_venta() == articulo1.precio(), "Precio de articulo 1 "
               "en pedido 2 incorrecto: %f != %f", it->second.precio_venta(), articulo1.precio());
      fct_xchk(it->second.cantidad() == cantidad_A1_P2, "Cantidad de articulo 1 "
               "en pedido 2 incorrecta: %d != %d", it->second.cantidad(), cantidad_A1_P2);
    }
    else
      fct_xchk(false, "El artículo 1 debería tener 2 ventas");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Articulo - ventas de un articulo no vendido) {
#ifdef P4
    Autor Hitler("Adolf", "Hitler", "Berlin");
    Articulo::Autores a { &Hitler };
    Libro MeinKampf(a, "666", "Mein Kampf", fHoy, 55.55, 555);
#else
    Articulo MeinKampf { "666", "Mein Kampf", fHoy, 55.55, 555 };
#endif
    const Pedido_Articulo& rAsocPedidoArticulo { *pAsocPedidoArticulo };
    const auto& pedArticulo3 { rAsocPedidoArticulo.ventas(MeinKampf) };
    fct_xchk(pedArticulo3.empty(), "Existen pedidos de articulo no vendido");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Articulo - insercion en flujo de ItemsPedido) {
    const Pedido_Articulo& rAsocPedidoArticulo { *pAsocPedidoArticulo };
    const auto& detalle { rAsocPedidoArticulo.detalle(*pPed2) };
    const string sDetalle { toString(detalle) };
    chk_incl_str(sDetalle, toString(pPed2->total()));
    chk_incl_str(sDetalle, toString(detalle.cbegin()->first->referencia()));
    chk_incl_str(sDetalle, toString(detalle.cbegin()->second.precio_venta()));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Articulo - insercion en flujo de Pedidos) {

    const Pedido_Articulo& rAsocPedidoArticulo { *pAsocPedidoArticulo };
    auto pedArticulo1 { rAsocPedidoArticulo.ventas(articulo1) };
    const string sPedidos { toString(pedArticulo1) };

    chk_incl_str(sPedidos,  toString(articulo1.precio()));
    chk_incl_str(sPedidos,  toString(cantidad_A1_P1));
    chk_incl_cstr(sPedidos, pPed1->fecha().cadena());
    chk_incl_str(sPedidos,  toString(cantidad_A1_P2));
    chk_incl_cstr(sPedidos, pPed2->fecha().cadena());
    
    const double totalEsperado =
      (cantidad_A1_P1 + cantidad_A1_P2) * articulo1.precio();
    chk_incl_str(sPedidos, toEuros(totalEsperado));
    chk_incl_str(sPedidos, toString(cantidad_A1_P1 + cantidad_A1_P2));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Articulo - mostrar detalle pedidos) {
    const Pedido_Articulo& rAsocPedidoArticulo { *pAsocPedidoArticulo };
    ostringstream os;
    rAsocPedidoArticulo.mostrarDetallePedidos(os);
    const string sDetalle { os.str() };
    
    const double totalEsperado =
      (cantidad_A1_P1 + cantidad_A1_P2) * articulo1.precio()
      + cantidad_A2_P2 * articulo2.precio();
    chk_incl_str(sDetalle, toEuros(totalEsperado));
    chk_incl_cstr(sDetalle, (const char*)(articulo1.titulo()));
    chk_incl_cstr(sDetalle, (const char*)(articulo2.titulo()));
    chk_incl_str(sDetalle, toString(cantidad_A1_P1));
    chk_incl_str(sDetalle, toString(cantidad_A1_P2));
    chk_incl_str(sDetalle, toString(cantidad_A2_P2));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Articulo - mostrar ventas agrupadas) {
    const Pedido_Articulo& rAsocPedidoArticulo { *pAsocPedidoArticulo };
    ostringstream os;
    rAsocPedidoArticulo.mostrarVentasArticulos(os);
    const string sDetalle { os.str() };
    /*
      Construimos expresiones regulares que buscan las cantidades
      como palabras separadas del resto por espacios. Es decir, si
      la cantidad es 1, ' 1' a final de línea, '1 ' a principio de
      línea, o ' 1 ' valen, pero no '123', por ejemplo.
    */
    const string sRegexPrefijo { "€[[:space:]]+"   }; // "(€[[:space:]]|^)";  
    const string sRegexSufijo  { "([[:space:]]|$)" };
#ifndef CPP11REGEX
    const string 
      sRegexA1P1(sRegexPrefijo + toString(cantidad_A1_P1) + sRegexSufijo),
      sRegexA1P2(sRegexPrefijo + toString(cantidad_A1_P2) + sRegexSufijo),
      sRegexA2P2(sRegexPrefijo + toString(cantidad_A2_P2) + sRegexSufijo);
    const regoff_t 
      posCantidad_A1_P1 = find_regex(sRegexA1P1.c_str(), sDetalle.c_str()),
      posCantidad_A1_P2 = find_regex(sRegexA1P2.c_str(), sDetalle.c_str()),
      posCantidad_A2_P2 = find_regex(sRegexA2P2.c_str(), sDetalle.c_str());
    // Las tres compras deben estar en la salida
    fct_chk(posCantidad_A1_P1 != -1);
    fct_chk(posCantidad_A1_P2 != -1);
    fct_chk(posCantidad_A2_P2 != -1);
    // Las compras deben estar agrupadas por artículo, y debidamente ordenadas.
    fct_chk(posCantidad_A2_P2 < posCantidad_A1_P1);
    fct_chk(posCantidad_A1_P1 < posCantidad_A1_P2);
#else
    regex  		// La nueva biblioteca regex de C++11
      sRegexA1P1(sRegexPrefijo + toString(cantidad_A1_P1) + sRegexSufijo),
      sRegexA1P2(sRegexPrefijo + toString(cantidad_A1_P2) + sRegexSufijo),
      sRegexA2P2(sRegexPrefijo + toString(cantidad_A2_P2) + sRegexSufijo);
    smatch cantidad_A1_P1, cantidad_A1_P2, cantidad_A2_P2;
    // Las tres compras deben estar en la salida
    fct_chk(regex_search(sDetalle, cantidad_A1_P1, sRegexA1P1));
    fct_chk(regex_search(sDetalle, cantidad_A1_P2, sRegexA1P2));
    fct_chk(regex_search(sDetalle, cantidad_A2_P2, sRegexA2P2));
    // Las compras deben estar agrupadas por artículo, y debidamente ordenadas.
    fct_chk(cantidad_A2_P2.position(0) < cantidad_A1_P1.position(0));
    fct_chk(cantidad_A1_P1.position(0) < cantidad_A1_P2.position(0));
#endif
  }
  FCT_TEST_END();

  // Pruebas de la clase de asociación Usuario_Pedido

  FCT_TEST_BGN(Usuario---Pedido - pedidos de un usuario comprador) {
    const Usuario_Pedido& rAsocUsuarioPedido = *pAsocUsuarioPedido;
    const auto& pedidosU2 = rAsocUsuarioPedido.pedidos(*pU2);
    if (pedidosU2.size() == 1)
      fct_xchk(*pedidosU2.begin() == pPed2, "El usuario 2 tiene un pedido "
               "asociado que no ha realizado.");
    else
      fct_xchk(false, "Debería haber un solo pedido registrado del usuario 2");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario---Pedido - pedidos de un usuario no comprador) {
    Usuario U3("u3", "Aitor", "Tilla", "Caracol 10", "esternocleidomastoideo");
    const Usuario_Pedido& rAsocUsuarioPedido = *pAsocUsuarioPedido;
    const auto& pedidosU3 = rAsocUsuarioPedido.pedidos(U3);
    fct_xchk(pedidosU3.empty(), "Un usuario que no ha comprado "
             "tiene un pedido por lo menos");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario---Pedido - cliente de un pedido) {
    const Usuario_Pedido& rAsocUsuarioPedido = *pAsocUsuarioPedido;
    fct_xchk(rAsocUsuarioPedido.cliente(*pPed1) == pU, 
             "Pedido 1 no asociado al cliente que lo ha realizado");
    fct_xchk(rAsocUsuarioPedido.cliente(*pPed2) == pU2,
             "Pedido 2 no asociado al cliente que lo ha realizado");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario---Pedido - asocia Usuario<---->Pedido) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    // Cambiar pedido2 de usuario2 a usuario1.
    pU_P->pedidos_[pU2].erase(pPed2);
    pU_P->cliente_.erase(pPed2);
    pAsocUsuarioPedido->asocia(*pU, *pPed2);

    fct_xchk(pU_P->pedidos_[pU].find(pPed2) != pU_P->pedidos_[pU].end(),
             "Falta enlace usuario ---> pedido");
    fct_xchk(pU_P->cliente_[pPed2] == pU, "Falta enlace pedido ---> usuario");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario---Pedido - asocia Pedido<--->Usuario) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    // Cambiar pedido2 de usuario2 a usuario1.
    pU_P->pedidos_[pU2].erase(pPed2);
    pU_P->cliente_.erase(pPed2);
    pAsocUsuarioPedido->asocia(*pPed2, *pU);

    fct_xchk(pU_P->pedidos_[pU].find(pPed2) != pU_P->pedidos_[pU].end(),
             "Falta enlace usario ---> pedido");
    fct_xchk(pU_P->cliente_[pPed2] == pU, "Falta enlace pedido ---> usuario");
  }
  FCT_TEST_END();
}
FCTMF_FIXTURE_SUITE_END()
