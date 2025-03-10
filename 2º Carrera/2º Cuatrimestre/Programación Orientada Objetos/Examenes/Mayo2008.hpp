#include <iostream>
#include <set>

/*----------Ejercio 1----------*/
/*
    Relacion Especializacion A -> B y E
    Relación Agregación B -> D(compuesto)
    Relación asociación muchos - muchos  E -> D. 
    Relación composición de 1 entre D - C(compuesto)
    Relación de especialización E y C -> F
*/

class A{};

class B: public A{}; //rel1

class E:public A{ //rel2
    public:
        typedef std::set<D*>Ds;
        E(D&d){ds_.insert(&d);}
        inline const Ds& rel5()const noexcept{return ds_;}
    private:
        Ds ds_;
};

class D{
    public:
        D(B&b):b_(b){}
        const B& rel3()const noexcept{return b_;}
    private:
        B b_;
};

class C{
    public:
        C(D& d):d_(d){}
        const D& rel4()const noexcept{return d_;}
    private:
    D d_;
};

class F : public C, public E{};

