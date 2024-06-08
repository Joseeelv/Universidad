#include <iostream>
#include <set>
#include <vector>
/*----------Ejercicio 3----------*/
class FiguraPlana{
    public:
        virtual void escala(size_t factorescalado)=0;
        virtual void dibujo()const =0;
        virtual ~FiguraPlana() = default; //polimorfica, virtual
};

class Elipse: public FiguraPlana{
    public:
        Elipse(double x, double y):x_(x),y_(y){}

        inline double radio_x()const noexcept{return x_;}
        inline double radio_y()const noexcept{return y_;}
        //Como lo hará uso Circunferencia, lo hacemos virtual, redefinimos
        inline virtual void escala(size_t factorescala) override{
            x_ *= factorescala;
            y_ *=factorescala;
        }
        inline void escala(size_t factorescalax , size_t factorescalay){
           x_ *= factorescalax;
           y_ *= factorescalay;
        }

        void dibujo()const override{
            std::cout<<"Elipse con radio_x = "<<x_<<" y radio_y = "<<y_<<std::endl;
        }
        virtual ~Elipse() = default; //al ser polimorifica, virtual
    private:
        double x_,y_;
};

class Circunferencia: private Elipse{
    public:
        Circunferencia(double radio):Elipse(radio,radio){}
        inline double radio()const noexcept{return Elipse::radio_x();}
        //delegamos en el método escala de Elipse, debido a la herencia
        inline void escala(size_t factorescala)override
        {Elipse::escala(factorescala);}
        void dibujo()const override{
            std::cout<<"Circunferencia con radio = "<<Elipse::radio_x()<<std::endl;
        }
};

class Escena{
    public:
        typedef std::set<FiguraPlana*>Figuras;
        Escena(FiguraPlana* figura){
           figuras_.insert(figura);
        }
        
        void dibuja()const{
           for(const auto& f : figuras_){
               f -> dibujo();
           }
        }
        void escala(size_t factor){
            for(auto f : figuras_){
                f->escala(factor);//aplicamos la escala a cada figura.
            }
        }
         void setFigura(FiguraPlana* f){
            figuras_.insert(f);
        }
    private:
        Figuras figuras_;
};

/*----------Ejercicio 4----------*/
template <typename Iter>
bool ordenado(Iter inicio, Iter fin)
{
    if(inicio == fin) return true; //vacio = ordenado
    Iter siguiente = inicio;
    siguiente ++;

    while(siguiente != fin)
    {
        if(*siguiente <*inicio) return false; // no ordenado
        else
        inicio++;
        siguiente++;
        
    }
    return true; //ordenado
}

template <typename Iter, typename Comparador>
bool ordenado(Iter inicio, Iter fin, Comparador comparador)
{
    if(inicio == fin)return true; //vacio=ordenado
    Iter siguiente = inicio;
    siguiente++;

    while(siguiente!=fin)
    {
        if(!comparador(*inicio,*siguiente))
            return false;
        inicio++;
        siguiente++;
    }
    return true;
}

typedef struct ValoresABS{
    bool operator()(int a, int b){
        return abs(a) < abs(b);
    }
};

int main()
{
    //Creamos el vector de enteros
    std::vector<int>valores = {1, 4, -45, 3};

    bool ascendente = ordenado(valores.begin(),valores.end(),ValoresABS());

    if(ascendente){
        std::cout<<"Ordenado ascendentemente";
    }
    else{
        std::cout<<"No ordenado ascendentemente";
    }
    return 0;
}