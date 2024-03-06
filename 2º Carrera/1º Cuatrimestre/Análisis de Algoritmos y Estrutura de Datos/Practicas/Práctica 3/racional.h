#ifndef _RACIONAL_
#define _RACIONAL_

class racional{
    public:
        racional(long num=0, long deno=1);
        long num() const{return n;}
        long den() const{return d;}

        //OPERADORES ARTIMÉTICOS EXTERNOS
            friend racional operator +(const racional& r, const racional& s);
            friend racional operator *(const racional& r, const racional& s);
            friend racional operator -(const racional& r, const racional& s);
            friend racional inv(const racional& r);
    private:
        long n,d;
        static long mcd(long,long);
        static long mcm(long,long);
};