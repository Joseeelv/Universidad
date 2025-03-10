#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
/*----------Ejercicio 2----------*/
class LineaPedido{};
class Articulo{};
class Pedido{};

class Pedido_Articulo{
    public:
        typedef std::map<Articulo*,LineaPedido*>ALP;
        typedef std::map<Pedido*,LineaPedido*>PLP;
        
        typedef std::map<Articulo*,PLP> Articulos;
        typedef std::map<Pedido*,ALP>Pedidos;

        void set(Articulo&, Pedido&, LineaPedido& )noexcept;
        void set(Pedido&, Articulo&, LineaPedido& )noexcept;

        Articulos getArticulos(Pedido& )const noexcept;
        Pedido getPedidos(Articulo& )const noexcept;
    private:
        Articulos articulos_;
        Pedidos pedidos_;
};

/*No, no es obligatorio hacer uso de una clase de asociación, podemos implementar dicha relación añadiendo los miembros necesarios
en las clases asociadas para que se cumpla la relación.
*/

class Articulo{
    public:
        //Miembros públicos de la clase Articulo
        typedef std::map<Pedido*,LineaPedido*>Pedidos;
        void setPedido(Pedido&, LineaPedido& )noexcept;
        const Pedidos& getPedidos()const noexcept;
    private:
        //Miembros privados de la clase Articulo
        Pedidos pedidos_;
};

class Pedido{
    public:
        //Miembros públicos de la clase Pedido
        typedef std::map<Articulo*,LineaPedido*>Articulos;
        void setArticulo(Articulo&, LineaPedido&)noexcept;
        const Articulos& getArticulos()const noexcept;
    private:
        //Miembros privados de la clase Pedido
        Articulos articulos_;
};

/*----------Ejercicio 3----------*/
//Sabiendo que ListaOrdenada usa una clase genérica list:
template <typename T>
class ListaOrdenada{
public:
  typedef typename list <T>::const_iterator iterator;
  void insertar(const T& e);
  void eliminar(iterator i);
  iterator begin()const;
  iterator end()const;
private:
};

//Explica la relación que se puede establecer entre ListaOrdenada y la clase list. Implemente la clase ListaOrdenada.
//Como list tiene una gran variedad de métodos y ListaOrdenada solamente hace uso de unas cuantas no tiene sentido llevar a cabo
// una relación de especialización, por tanto, vamos a realizar una relación de composición la cual hace que la implementación sea 
//mucho más eficiente y menos compleja pudiendo delegar en varios métodos de la clase list.
template <typename T>
class ListaOrdenada{
    public:
        typedef typename list <T>::const_iterator iterator;
        void insertar(const T& e);
        void eliminar(iterator i);
        size_t contar(const T& e)const;
        inline iterator begin()const{return cbegin();}
        inline iterator end()const{return cend();}
    private:
        list<T>listaordenada_;
};
//Vamos a implementar el metodo contar mediante el uso de una función lambda
template <typename T>
size_t ListaOrdenada::contar(const T& e)const{
    return std::count_if(listaordenada_.begin(),listaordenada_.end(),[e](T& x){return e==x;});
}
/*----------Ejercicio 4----------*/
//Sea el programa:
class Instrumento{
public:
  enum tClase{instrumento, percusión, viento, cuerda};
  Instrumento(string n):nom_(n),clase_(instrumento){}
  void tocar()const{
    cout<<"Soy un "<<nombre()<<" y pertenezco a " <<clase()<<endl;
  }
  string nombre()const {return nom_;}
  string clase() const{
    switch(clase_){
      case percusion: return "percusión"; break;
      case viento: return "viento"; break;
      case cuerda : return "cuerda";break;
      case default: return "instrumento";break;
    }
  }
protected:
  string nom_;
  string clase_;
};

class Percusion : public Instrumento{
public:
  Percusion(string n):Instrumento(n),clase_(percusion){}
};

class Viento: public Instrumento{
public:
  Viento(string n):Instrumento(n),clase_(viento){}
};

class Cuerda:public Instrumento{
public:
  Cuerda(string n):Instrumento(n),clase_(cuerda){}
};

int main(){
  vector<Instrumento*> v;
  v.push_back(new Cuerda("Violin"));
  v.push_back(new Instrumento("Sintetizador"));
  v.push_back(new Cuerda("Arpa"));
  v.push_back(new Percusion("Timbal"));
  v.push_back(new Viento("Tuba"));
  for(auto* i : v){
    i -> tocar();
    delete i;
  }
  return 0;
}

//¿Se puede mejorar la implementación de esta jerarquía de clases usando métodos polimorficos?
// En caso afirmativo reescribe el programa para obtener un resultado idéntico.
//Si, podemos hacer desaparecer ese switch de la clase Instrumento mediante el uso de polimorfismo, donde
//cada clase derivada contendrá los métodos tocar() y nombre().

class Instrumento{
public:
  Instrumento(string n):nom_(n){}
  virtual void tocar()const{
    cout<<"Soy un "<<nombre()<<" y pertenezco a Instrumento"<<endl;
  }
  virtual string nombre()const {return nom_;}
protected:
  string nom_;
};

class Percusion : public Instrumento{
 public:
    Percusion(string n):Instrumento(n){}
    virtual void tocar()const override{
        cout<<"Soy un "<<nombre()<<" y pertenezco a Percusión"<<endl;
    }
    inline virtual string nombre()const override {return nom_;}
};

class Viento : public Instrumento{
public:
    Viento(string n):Instrumento(n){}
    virtual void tocar()const override{
        cout<<"Soy un "<<nombre()<<" y pertenezco a Viento"<<endl;
    }
    inline virtual string nombre()const override {return nom_;}
};

class Cuerda : public Instrumento{
public:
    Cuerda(string n):Instrumento(n){}
    virtual void tocar()const override{
            cout<<"Soy un "<<nombre()<<" y pertenezco a Cuerda"<<endl;
        }
    inline virtual string nombre()const override {return nom_;}
};

#include <set>

typedef Fecha;
class Articulo{
    double precio_;
  public:
    Articulo(double p):precio_(p){}
};

class ArticuloAlmacenable : public Articulo{
    int stock_;
  public:
    ArticuloAlmacenable(int s, double p):Articulo(p),stock_(s){}
};

class LibroDigital : public Articulo{
    Fecha fech_exp;
  public:
    LibroDigital(Fecha f, double p):Articulo(p),fech_exp(f){}
};

class Libro : public ArticuloAlmacenable{};
class Revista: public ArticuloAlmacenable{};
//Clase nueva que nos piede el ejercicio
class LibroDigital : public Articulo{
  Fecha f_expir_;
public:
  LibroDigital(Fecha f, double p, Cancion& c):Articulo(p),f_expir_(f){
    setCanciones(c);
  }
  //Alias del conjunto de canciones del disco
  typedef std::set<Cancion*>Canciones;
  inline void setCanciones(Cancion&c )noexcept{
    canciones_.insert(&c);
  }
  inline const Canciones& getCanciones()const noexcept{
    return canciones_;
  }
private:
  Canciones canciones_;
}

class Cancion{};