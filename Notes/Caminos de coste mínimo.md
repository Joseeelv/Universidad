# Algoritmo Dijkstra
El algoritmo Dijkstra calcula los caminos de coste mínimo entre ***origen*** y ***todos los vértices*** del grafo **G**.
```
template <typename tCoste> Dijkstra
(const GrafoP<tCoste>& G,typename GrafoP<tCoste>::vertice origen,
         vector<typename GrafoP<tCoste>::vertice>& P);
```
Como salida tenemos:
    - Un *vector de costes mínimos* de tamaño `G.numVert()`.
    - **P**, un *vector de vértices* de tamaño `G.numVert()`, tal que `P[i]` es el vértice anterior a `i` en el camino de coste mínimo desde **origen** hasta `i`.

**<u>NOTA:</u>** *Un grafo no dirigido, es un grafo dirigido pero con flechas en ambas direcciones. Por tanto, si tenemos un algoritmo que es válido para un grado dirigido, también funcionará para uno NO dirigido.*
### Ejemplo del algoritmo
Encontramos un vector de booleanos `bool`, que indica si se ha usado o no ese nodo para mejorar los caminos.
El algoritmo se acaba cuando hemos hecho uso de todos los nodos (*teóricamente*).
En este algoritmo, partimos desde un lugar concreto ‘*origen*’. 

Se inicializan todos los nodos a `false` menos el origen.
Va a devolver 2 resultados:
|Distancia ‘D’|Camino ‘P’|
|---|---|
|Es el **coste mínimo** de ir desde el nodo *origen* hasta cualquier otro nodo del grafo. En este algoritmo siempre partimos desde un origen. Hacemos uso de un vector y este se inicializa con los costes directos entre el origen a los demás nodos del grafo.|Es un **vector de vértices**. Cuando el camino es directo, se inicializa a 0. Nos permite recuperar el camino, que son los vértices por los que se han pasado.|

#### Pasos para mejorar
Primero de todo, tenemos que encontrar el primer nodo para mejorar el algoritmo. A dicho nodo, le ponemos `true`. 
En el ejemplo hacemos que el nodo ‘1’ sea el nodo para mejorar.
Ahora la distancia al nodo 2, en vez de ser ∞ a 60, una clara mejora.
Si el coste del nuevo camino es ≤ que el anterior, podemos hacer uso del nuevo. 
En el vector P, ponemos 1 que significa el nodo por el cual se ha mejorado.
El siguiente va a ser 3, ya que su coste es 30 y hacemos lo mismo.
Vemos cuanto se puede mejorar, como 30 > 10 vemos que los nodos 0 y 1 no se pueden mejorar, por tanto, los únicos que se pueden mejorar son el 2 y 4.
En el nodo 2 pasamos de un coste 60 a un coste 50 (30+20) y en el nodo 4 pasamos de un coste 100 a un coste 90 (30+60).

Ya hemos hecho uso de los nodos 0,1,3 para mejorar, solo nos queda el 2 y 4.
Ahora hacemos uso del 2 para mejorar el 4, de 0 a 2 es coste mínimo es 50, por tanto, a llegar a 4 es 60, por tanto, pasamos de un 90 al ser mejorado con 3 a un coste mínimo de 60 al ser mejorado por 2.
Como solo nos queda un nodo, el 4, no podemos hacer uso de él para poder mejorar los demás nodos, debido a que es el nodo ‘más alejado’ del origen *tiene mayor coste mínimo*. 
Por tanto, tenemos que tener en cuenta que *si el coste mínimo es mayor que el coste del camino anterior, no se puede mejorar el coste mínimo de ningún nodo*. 

### Código del algoritmo Dijkstra
#### Suma de costes
Hacemos uso de un tipo de dato llamado `INFINITO` que nos indica que no es accesible ese nodo desde el origen y por tanto, su coste mínimo es *infinito*. 
```
template <typename tCoste>
tCoste suma(tCoste x, tCoste y){
//Hacemos uso del tipo de dato tCoste INFINITO para decir
//que los nodos no está directamente conectados
  const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
  if (x == INFINITO || y == INFINITO) return INFINITO;
  else return x + y;
}
    
```
#### Método Dijkstra
El vector D se inicializa al origen y es la primera fila de la  ***matriz de costes***
Si tenemos $n$ nodos, partimos del origen y como no nos sirve el último nodo, tenemos que iterar $n-2$ veces.
$w$ tiene la posición del nodo que vamos a usar para mejorar.
```
typedef typename GrafoP<tCoste>::vertice vertice;
    vertice v, w;
    const size_t n = G.numVert();
    vector<bool> S(n, false); // Conjunto de vértices vacío.
    vector<tCoste> D; // Costes mínimos desde origen.
// Iniciar D y P con caminos directos desde el vértice origen.
    D = G[origen];
    D[origen] = 0; // Coste origen-origen es 0.
    P = vector<vertice>(n, origen);
// Calcular caminos de coste mínimo hasta cada vértice.
    S[origen] = true; // Incluir vértice origen en S.
    for (size_t i = 1; i <= n-2; i++)
    {
// Localizar vértice w no incluido en S con menor coste desde origen
        tCoste costeMin = GrafoP<tCoste>::INFINITO;
        for (v = 0; v <= n-1; v++)
            if (!S[v] && D[v] <= costeMin)
            {
                costeMin = D[v];
                w = v; //nos quedamos con la posición del nodo
            }
        S[w] = true; // Incluir vértice w en S.
// Recalcular coste hasta cada v no incluido en S, a través de w.
//Aqui optimizamos de verdad, donde se recálcala los valores del vector D
        for (v = 0; v <= n-1; v++)
            if (!S[v])
            {
                tCoste Owv = suma(D[w], G[w][v]);
                if (Owv < D[v])
                {
                    D[v] = Owv; //Coste de ir del origen a v a través de w
                    P[v] = w;
                }
            }
        }
    return D;
}
```
#### Método Camino
A esta función le llega un origen, vértice y el vértice P.
```
template <typename tCoste> typename GrafoP<tCoste>::tCamino
camino(typename GrafoP<tCoste>::vertice orig,
typename GrafoP<tCoste>::vertice v,
const vector<typename GrafoP<tCoste>::vertice>& P){
    typename GrafoP<tCoste>::tCamino C;
    C.insertar(v, C.primera());
    do {
        C.insertar(P[v], C.primera());
        v = P[v];
    } while (v != orig);
    return C;
}
```
El `origen` es 0, `v` es la posición destino.  

