%LocalAppData%\Microsoft\WindowsApps\wt.exe
#include"polinomio_racional.h"
#include <cstdlib>
#include <cassert>

//METODOS PRIVADOS

long racional::mcd(long x, long y){
    long aux;

    //ALGORITMO EUCLIDES
    if(x<y){
        aux=x;
        x=y;
        y=aux;
    }

    while((aux=x%y)){
        x=y;
        y=aux;
    }
    return y;
}

inline long racional::mcm(long x , long y){
    return x/mcd(x,y)*y;
}

//CONSTRUCTOR
racional::racional(long num,long deno)::n(num), d(deno){
    assert(d!=0); //verificar precondicion
    if(n==0) d=1;
    else{
        if(d<0){
            n=-n;
            d=-d;
        }
    //REDUCIR FRACCION
        long m= mcd(abs(n),d);
        if(m!=1){
            n/=m;
            d/=m;
        }
    }
}

//OPERADORES ARITMETICOS EXTERNOS

racional operator+(const racional& r, const racional& s){
    long m= racional::mcd(r.d,s.d);
    return racional(s.d/ m*r.n+r.d / m*s.n, racional::mcm(r.d,s.d));
}

racional operator*(const racional& r, const racional& s){
    racional t; //racional 0/1

    if(r.n && s.n){
        long a= racional::mcd(abs(r.n),s.d);
        long b=racional::mcd(r.d,abs(s.n));
        t.n= (r.n/a) * (s.n/b);
        t.d= (r.d/b) * (s.d/a);
    }
    return t;
}

racional operator-(const racional& r){
    racional s; //racional 0/1
    
    if(r.n!=0){
        s.n=-r.n;
        s.d=r.d;
    }

    return s;
}

racional inv(const racional& r){
    racional s;

    assert(r.n!=0); //verificar precondicion
    if(r.n>0){
        s.n=r.d;
        s.d=r.n;
    }
    else{ //ponemos signo en el numerador
        s.n=-r.d;
        s.d=-r.n;
    }

    return s;
}