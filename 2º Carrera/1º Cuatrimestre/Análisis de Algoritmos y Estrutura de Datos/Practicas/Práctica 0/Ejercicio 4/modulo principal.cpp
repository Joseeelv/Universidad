//MODULO PRINCIPAL

#include "visita.h"

int main(int argc, const char* argv[]){
    using namespace std;
    Visitas = 0;
    while (*++argv){
        visita (*argv);
        std::cout << "Visitas: " << Visitas << endl;
    }
}