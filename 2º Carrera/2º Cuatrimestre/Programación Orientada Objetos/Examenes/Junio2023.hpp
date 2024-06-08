#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <valarray>
/*----------Ejercicio 1----------*/
// Dado el siguiente diagrama, donde nos encontramos con distintas clases con relaciones entre ellas.

/*Tenemos las siguientes relaciones:
    -> Asociación muchos - muchos Cconsorte - Tramo
    -> Composicion 1 - muchos Carretera - Tramo
    -> Agregación 1 - 2 Carretera - TerMunicipal
    -> Asociación con atrib enlace muchos - muchos TerMunicipal - horas - Tramo */

//Relación Asociación muchos - muchos Cconsorte - Tramo
//Esta asociación la podemos implementar de dos maneras diferentes, una mediante la creación de una clase de asociación o modificando las clases asociadas, lo haremos de la segunda menera:

class Cconsorte{
    public:
    //métodos propios de la clase
        //-----Relación Asociación muchos - muchos Cconsorte - Tramo-----
        //Alias de la asociacion
        typedef std::set<Tramo*>Tramos;
        void setTramo(Tramo&)noexcept;
        const Tramos& getTramos()const noexcept;
    private:
    //atributos propios
        //relacion con tramo
        Tramos tramos_;
};

class Tramo{
    public:
    //..
        //-----Relación Asociación muchos - muchos Cconsorte - Tramo-----
        typedef std::set<Cconsorte*>Cconsortes;
        void setConsorte(Cconsorte&)noexcept;
        const Cconsortes& getConsortes()const noexcept;
    private:    
    //..
        Cconsortes consortes_;
};

class Carretera{
    public:
    //...
        Carretera(Tramo& t,TerMunicipal&ter1, TerMunicipal&ter2);
        typedef std::set<Tramo>Tramos;
        //operador < para ordenar las carreteras
        bool operator <(const Carretera& )const noexcept;

        const TerMunicipal getTermunicipal1()const noexcept;
        const TerMunicipal getTermunicipal2() const noexcept;
    private:  
        Tramos tramos_; //relacion de composición
        TerMunicipal ter1_,ter2_;

};

class TerMunicipal{/*...*/};

//Para la relación con clase de asociación vamos a crear una clase nueva de asociación llamada TerMunicipal_Tramo
class TerMunicipal_Tramo{
    public:
        //Alias de las relaciones de las clases con el atributo de enlace
        typedef std::map<Tramo*,int> Tramos;
        typedef std::map<TerMunicipal*,int>TerMunicipales;
        //Alias de las relaciones
        typedef std::map<Tramo*,TerMunicipales>TramoTerMunipal;
        typedef std::map<TerMunicipal*,Tramos>TerMunicipalTramo;

        //método que liga las clases
        void setTerMunicipalTramo(TerMunicipal&,Tramo&,int)noexcept;
        void setTerMunicipalTramo(Tramo&,TerMunicipal&,int)noexcept;

        //observadores
        Tramos getTramos(TerMunicipal&)const noexcept;
        TerMunicipales getTerMuniciaples(Tramo&)const noexcept;
    private:
        TramoTerMunipal directa_;
        TerMunicipalTramo inversa_;
};


/*----------Ejercicio 2----------*/
//1.Añade otra clase al esquema llamada DiscoDigital que contiene, al igual que LibroDigital, la fecha de expiración del DiscoDigital. Modifique el diagrama de acuerdo a esto.
typedef Fecha;
class Articulo{
    double precio_;
    public:
        Articulo(double p):precio_(p){}
};

class ArticuloAlmacenable:public Articulo{
    int stock_;
};

class Libro: public ArticuloAlmacenable{};

class Revista: public ArticuloAlmacenable{};

class LibroDigital : public Articulo{
    Fecha fech_exp;
};

//Creamos la nueva clase DiscoDigital -> como es digital no va a ser un ArticuloAlmacenable, por tanto quedaría:
class DiscoDigital: public Articulo{
    public:
        typedef std::set<Cancion>Canciones;
        bool operator < (const DiscoDigital)const noexcept;
        DiscoDigital(Fecha f, double p, Cancion& c):Articulo(p),fech_exp(f){}
        const size_t nCancion() const noexcept{return canciones_.size();}
    private:
    Fecha fech_exp;
    Canciones canciones_;
};

//Clase Cancion, donde un DiscoDigital está compuesto de una serie de canciones
class Cancion{
    public:
        DiscoDigital* disco_()const noexcept{return discoD_;}
    private:
    DiscoDigital* discoD_;
};
/*----------Ejercicio 3----------*/
//Implementación del método para conocer el número de articulo que es menor dado un precio mediante un objeto a funcion
typedef Fecha;
class Articulo{
    double precio_;
    public:
        Articulo(double p):precio_(p){}
        //Creamos el objeto a funcion.
        typedef struct EsBarato
        {
            bool operator()(Articulo& art, double precio){
                return art.precio_ < precio;
            }
        };
        inline const double getprecio()const noexcept{return precio_;}
        virtual ~Articulo() = default;
};  

class ArticuloAlmacenable:public Articulo{
    int stock_;
    public:
        ArticuloAlmacenable(int s, double p):stock_(s),Articulo(p){}
        inline const int getstock()const noexcept{return stock_;}
};

class Libro: public ArticuloAlmacenable{
    public:
        Libro(int s, double p):ArticuloAlmacenable(s,p){}
};

class Revista: public ArticuloAlmacenable{
    public:
        Revista(int s, double p):ArticuloAlmacenable(s,p){}
};

class LibroDigital : public Articulo{
    Fecha fech_exp;
    public:
        LibroDigital(Fecha f ,double p):Articulo(p),fech_exp(f){}
};

//Creamos el método nuevo, recibe un conjunto de articulos y el precio

size_t ArticulosBaratos(const std::vector<Articulo*>&articulos, double precioMinimo){
    //Creamos el resultado
    size_t articulosbaratos = 0;
    //Creamos el objeto a funcion
    Articulo::EsBarato esbarato;

    //recorremos el vector de articulos
    for(auto& a : articulos){
        if(esbarato(*a,precioMinimo)){
            articulosbaratos++;
        }
    }
    return articulosbaratos;
}

//La misma función pero con una función lambda

size_t LibrosBaratos(const std::vector<Articulo*>&articulos, double precioMinimo){
    //Creamos el resultado
    size_t librobarato=0;

    //creamos la función lambda
    auto EsBarato = [precioMinimo](Articulo* art){
        //solo libros
        if( Libro* l = dynamic_cast<Libro*>(art)){
            return l!=nullptr && l->getprecio() < precioMinimo;
        }    
    };
    //recorremos la lista de articulos pero solo contamos los libros
    for(const auto& a : articulos){
            if(EsBarato(a)){
                librobarato ++;
            }
        }
        return librobarato;
}

//Devolver el lista de articulos que hay que reponer, dado un lista de punteros a Articulo y un stock minimo

std::vector<Articulo*> ArticulosReponer(const std::vector<Articulo*>&articulos, int stockMinimo){
    //Creamos el vector que contendrán los articulos a reponer
    std::vector<Articulo*>articulosAreponer;

    //recorremos el vector de articulos y comparamos su stock, lo podemos hacer mediante una función lambda
    auto Reponer = [stockMinimo](Articulo* a){
        if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(a)){
            return AA!=nullptr && AA->getstock() < stockMinimo;
        }
    };

    //Recorremos la lista de ArticulosAlmacenables
    for(const auto& AA : articulos){
        if(Reponer(AA))articulosAreponer.push_back(AA);
    }
    return articulosAreponer;
}


/*----------Ejercicio 4----------*/

template <typename T = double>
class Matriz{
    public:
        //Constructor
        Matriz(T F = 10, T C = 10, T y = 0.0):m(F),n(C),x(m*n,y){}

        //Creamos el Constructor por copia y operador de asignación por copia.
        Matriz& (const Matriz& other){
            if(this!= &other){
                //vemos si el tamaño es el mismo
                if(m != other.m || n = other.n){
                    delete [] x;
                    m = other.m;
                    n = other.n;
                }
                //Creamos la nueva matriz
                *this = Matriz(m,n,other.y);
            }
        }

        Matriz<T>& operator = (const Matriz<T>&){
            if(this!=&other){
                if(m != other.m || n = other.n){
                    m = other.m;
                    n = other.n;
                }
                //Creamos la nueva matriz
                x_.resize(m*n);
            }
            return *this;
        }

        friend std::ostream& operator << (std::ostream&, const Matriz<T>&);
    private:
        T m,n;
        std::valarray<T> x;

};
template<typename T>
std::ostream& operator << (std::ostream& os, const Matriz<T>& matriz){
    os<<"Matriz con "<<matriz.m<<" columnas, "<<matriz.n<<" filas, con valores: \n";
    for(T i=0; i<n; i++)
        for(T j=0; j<m ; j++){
            os<<matriz(i,j)<<" ";
        }
    os << std::endl;

    return os;
}

