#include <iostream>
#include <algorithm> //pair
#include <map>
#include <string>
#include <vector>
#include <list>
#include <iterator>
/*----------Ejercicio 2----------*/
class Articulo
{
  public:
    //Alias del contenedor
    typedef std::map<Pedido*,LineaPedido*>Pedidos;
    void setPedido(Pedido&, LineaPedido&)noexcept;
    //Un articulo puede que no esté en ese pedido
    Pedidos getPedidos()const noexcept;

  private:
    std::string referencia;
    std::string titulo;
    double precio;
    Pedidos pedidos_;
};
class Pedido
{
  public:
    //Relacion con Articulo y LineaPedido
    typedef std::map<Articulo*,LineaPedido*>Articulos;
    void setArticulo(Articulo&,LineaPedido&)noexcept;
    const Articulos& getArticulos()const noexcept;
  private:
    double total;
    unsigned int num;
    Articulos articulos_;
};
class LineaPedido
{
  public:
    double precio_venta()const {return precio_venta_;}
    unsigned cantidad()const{return cantidad_;}
  private:
    double precio_venta_;
    unsigned cantidad_;
};

class Articulo_Pedido
{
  public:
    //Alias de los conjuntos de objetos
    typedef std::map<Articulo*,LineaPedido*>ArtLP;
    typedef std::pair<Pedido*,LineaPedido*>PedLP;
    //Diccionarios
    typedef std::map<Articulo*,PedLP>Articulos;
    typedef std::map<Pedido*,ArtLP>Pedidos;

    void setLineaPedido(Articulo&, Pedido& LineaPedido&)noexcept;
    void setLineaPedido(Pedido&, Articulo&,LineaPedido&)noexcept;

    //observadores
    //Siempre va a haber un artículo en un Pedido
    const PedLP& getPedidos(Articulo& )const noexcept;
    //No sabemos si en ese Pedido está ese articulo, puede que en ningún Pedido
    ArtLP getArticulos(Pedido& )const noexcept;
  private:
    Articulos directa_;
    Pedidos inversa_;
};
/*----------Ejercicio 3----------*/
template<typename T>
class ListaOrdenada
{
  public:
    typedef typename list<T>::const_iterator iterator;
    void insertar(const T& e);
    void eliminar(iterator p);

   inline iterator begin() const{return cbegin();}
   inline iterator end() const{return cend();}

    size_t contar(const T& e);
  private:
    std::list<T> listaordenada_; //compsición
};
template<typename T>
void ListaOrdenada<T>::insertar(const T& e)
{
  //vamos a insertar pero ordenadamente, para ello buscamos el primer elemento que sea menor al que vamos a introducir
 iterator posicion = std::lower_bound(listaordenada_.begin(), listaordenada_.end(),e);
 listaordenada_.insert(posicion,e);
}

template <typename T>
void ListaOrdenada<T>::eliminar(iterator p)
{
  //Vamos a eliminar el elemento de la posicion p.
  listaordenada_.erase(p);
}

template <typename T>
size_t ListaOrdenada<T>::contar(const T& e)
{
  //Vamos a devolver el número de veces que se encuentra el elemento en la lista
  return std::count_if(listaordenada_.begin(),listaordenada_.end(),[&e](const T& eltolista){return eltolista == e});
}

/*----------Ejercicio 4----------*/
using namespace std;
class Instrumento
{
  public:
    Instrumento(string nom):nombre_(nom){}
    virtual void tocar()const
    {
      cout<<"Soy un "<<nombre()<<" y pertenezco a instrumento"<<endl;
    }

    inline virtual string nombre() const{return nombre_;}
  protected:
    string nombre_;
};

class Percusion:public Instrumento
{
  public:
    Percusion(string n):Instrumento(n){}
    void tocar()const override{
            cout<<"Soy un "<<nombre()<<" y pertenezco a percusión"<<endl;
    }
    inline virtual string nombre()const override{return nombre_;}
};  

class Cuerda: public Instrumento
{
  public:
    Cuerda(string n):Instrumento(n){}
    void tocar()const override{
            cout<<"Soy un "<<nombre()<<" y pertenezco a cuerda"<<endl;
    }
    inline virtual string nombre()const override{return nombre_;}

};

class Viento: public Instrumento
{
  public:
    Viento(string n):Instrumento(n){}
    void tocar()const override{
            cout<<"Soy un "<<nombre()<<" y pertenezco a viento"<<endl;
    }
    inline virtual string nombre()const override{return nombre_;}
};

// int main() {
//     Instrumento instrumento("Instrumento");
//     Percusion percusion("Tambor");
//     Cuerda cuerda("Violín");
//     Viento viento("Flauta");

//     instrumento.tocar();  // Output: Soy un Instrumento y pertenezco a instrumento
//     percusion.tocar();    // Output: Soy un Tambor y pertenezco a percusión
//     cuerda.tocar();       // Output: Soy un Violín y pertenezco a cuerda
//     viento.tocar();       // Output: Soy un Flauta y pertenezco a viento

//     return 0;
// }
void clasificainstrumentos(const vector<unique_ptr<Instrumento>>&instrumento, vector<Percusion*>&percusiones,vector<Cuerda*>& cuerdas, vector<Viento*>& vientos)
{
  for(const auto& i : instrumento){
    if(Percusion* pp = dynamic_cast<Percusion*>(i.get()))
    {
      percusiones.push_back(pp);
    }
    else if(Viento* v = dynamic_cast<Viento*>(i.get()))
    {
      vientos.push_back(v);
    }
    else if(Cuerda* c = dynamic_cast<Cuerda*>(i.get()))
    {
      cuerdas.push_back(c);
    }
  }
}

int main()
{
  vector<unique_ptr<Instrumento>>instrumentos;
  instrumentos.push_back(make_unique<Percusion>("Tambor"));
  instrumentos.push_back(make_unique<Cuerda>("Violín"));
  instrumentos.push_back(make_unique<Viento>("Flauta"));
  instrumentos.push_back(make_unique<Instrumento>("Instrumento"));

  vector<Percusion*> percusiones;
  vector<Cuerda*> cuerdas;
  vector<Viento*> vientos;

  //llamamos al método que nos clasifica los instrumentos
  clasificainstrumentos(instrumentos,percusiones,cuerdas,vientos);
  //devolvemos los vectores por pantalla
  cout<<"INSTRUMENTOS DE PERCUSION:"<<endl;
  for(const auto& i : percusiones){
    i->tocar();
  }
  cout<<"\nINSTRUMENTOS DE VIENTO:"<<endl;
  for(const auto& i : vientos)
  {
    i->tocar();
  }

  cout<<"\nINSTRUMENTOS DE CUERDA:"<<endl;
  for(const auto& i : cuerdas)
  {
    i->tocar();
  }

  return 0;
}
