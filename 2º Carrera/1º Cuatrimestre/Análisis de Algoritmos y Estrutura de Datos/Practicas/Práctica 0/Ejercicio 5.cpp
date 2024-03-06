//5. ¿Hay algún problema con el siguiente programa? Si lo hay, explique cuál. Si no, explique
//qué salida produce

#include <iostream>

int main(){
    using namespace std;
    int v[3] = { 1, 2, 3, };
    for (int i = 0; i < 3; ++i)
        cout << v[i] << ' ' ;
    cout << endl;
    
}
/*  Encontramos algunos problemas:
    Vemos que no para de imprimir "0" hasta que llegue al décimo elemento, es decir,
    produce una salida de --> 1, 2, 3, 0, 0, 0, 0, 0, 0, 0.

    Para solucionar esto ponemos que int v[3] es de 3 elementos y por tanto el bucle iteraría
    solo 3 veces, que son los elementos que contiene.
*/
