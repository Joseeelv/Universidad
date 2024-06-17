#include <iostream>
#include <vector>
#include <set>
#include <map>

class C;
class A{
  public:
    //Alias de la relacioncon C
    typedef std::set<C*>Cs;
    void setC(C&)noexcept;
    const Cs& getC()const noexcept;
  private:
    Cs cs_; //rel1
};

class D;
class B{
  public:
    //Alias de la relacion con D, suponemos que el tipo de dato de d1 es int
    typedef std::map<int,D*>Ds;
    void setD(D& d)noexcept{
      ds_.insert(std::make_pair(d.clave(),&d));
    }
    const Ds& getD()const noexcept;
  private:
    Ds ds_;//rel3
};

class C{  
  public:
  //como la multiplicidad es 0-1, no es necesario que para crear C exista D
    void setD(D&)noexcept;
    D& getD()const noexcept;
  private:
    D* d_;//rel4
};

class D : private A{//rel2 como es es 1-1, herencia privada
  public:
    D(A& a):A(a){} //rel 2
    //Alias de la relacion con B
    typedef std::set<B*>Bs;
    void setB(B&)noexcept;
    const Bs& getB()const noexcept;

    //Alias de la relacion con C
    typedef std::set<C*>Cs;
    void setC(C&)noexcept;
    const Cs& getC()const noexcept;

    int clave() const noexcept{return clave_;}

  private:
    Bs bs_; //rel3
    Cs cs_; //rel4
    int clave_; //calificador
};