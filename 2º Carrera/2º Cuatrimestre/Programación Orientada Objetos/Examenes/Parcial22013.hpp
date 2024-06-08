#include <iostream>
#include <set>
#include <map>
/*-----Ejercicio 1-----*/
class A{
    public:
        typedef std::map<C*,int>Cs; //suponemos que int es el tipo del atributo de enlace
        void setC(C&, int)noexcept;
        const Cs& getC()const noexcept;
    private:
        Cs cs_; //rel1, al ser unidireccional, se almacenan los datos en el lado opuesto a la flecha
};

class B{
    public:
        typedef std::set<D*>Ds;
        void setD(D&)noexcept;;
        const Ds& getD()const noexcept;
    private:
        Ds ds_;//rel3 bidireccional
        int d1; //suponemos que el calificador es de tipo int
};

class C{
    public:
        //como la multiplicidad es 0-1, no es necesario que para crear C exista D
        void setD(D& )noexcept;
        D getD()const noexcept;
    private:
        D ds_; //rel4 bidireccional
};

class D:private A{
    public:
        D(A&a):A(a){} 
        typedef std::set<C*>Cs;
        void setC(C&)noexcept;
        const Cs& getC()const noexcept;

        typedef std::map<int, B*>Bs;
        void setB(B&, int)noexcept;
        const Bs& getB() const noexcept;
    private:
        Cs cs_; //rel4 bidireccional
        //A a_; //rel2 unidireccional solo compuesto conoce, tambien podemos implementarla así
        Bs bs_; //rel3 bidireccional
};

/*-----Ejercicio 2-----*/
class C{};
class D{};

class DC{
    public:
        typedef std::set<C*> Cs;
        typedef std::map<C*,D*>CDs;
        typedef std::map<D*,Cs>DCs;

        void asocia(C&,D&)noexcept;
        void asocia(D&,C&)noexcept;

        Cs getCs(D&)const noexcept;
        D* getDs(C&) const noexcept;
    private:
        CDs directa_;
        DCs inversa_;
};

void DC::asocia(C& c, D& d)noexcept{
    //Comprobamos si está asociado
    directa_[&c] = &d;
    inversa_[&d].insert(&c);
}

void DC::asocia(D& d, C& c)noexcept{
    asocia(c,d); //delegamos
}

DC::Cs DC::getCs(D& d)const noexcept{
    //comprobamos si existe D
    auto i = inversa_.find(&d);
    if(i!=inversa_.end()) return i->second;
    else{
        DC::Cs vacia;
        return vacia;
    }
}
D* DC::getDs(C& c)const noexcept{
    auto i = directa_.find(&c);
    if(i!=directa_.end()) return i->second;
    else return nullptr;
}

/*-----Ejercicio 3-----*/

class C1{
    int x,y;
    public:
        C1(int a, int b):x(a),y(b){}
};
class C2{};

class C3:private C2,public C1{ 
    char x;
    public:
        C3(int i, int j, char z):C1(i,j),x(z){}
};

class C4:public C1{
    char x;
    int z;
    public:
        C4(int a, char b):C1(a,a),x(b){}
};