#include "PostFijo.hpp"
int main() {
        //((A+B) * (C+D)) = 15
        //std::string expresion = "AB+CD+*"; 
        //((A+B) * (C+D)) * A-E = -60 
        //::string expresion = "AB+CD+*AE-*"; 
        //((A+B) * (C+D)) * B-E = -45 
        std::string expresion = "AB+CD+*BE-*";
        Variable variables[] = {
        Variable('A', 2),
        Variable('C', 1),
        Variable('B', 3),
        Variable('D', 2),
        Variable('E', 6),
    };
    std::cout<< "El valor del postfijo es: "<<getResultadoExpresion(expresion,variables) <<std::endl;
    return 0;

}