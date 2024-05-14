## Definición de grafo

Un ***grafo*** *G = (V,A)* es un conjunto de *vértices* o *nodos* (V) y un conjunto de *aristas* (dos direcciones) o *arcos* (*u*na dirección) $A ⊆ (VxV)$ que define una relación binaria en V.

Cada arista es un par de vértices $(v,w) ∈ A$. 

Si $(v,w)$ ≠ $(w,v)$, no son equivalentes (no simétrica) → ***grafo dirigido***.

El vértice v es **incidente**  sobre el vértice w y w es **adyacente** a v.
![](https://joseelv.notion.site/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2F7a659d26-47c8-4fe7-b59f-2d570ed8bddf%2F058de6d5-2070-468e-b96d-d151a40c534e%2FUntitled.png?table=block&id=99caa044-2b97-4d6d-bb19-cc50da1bda75&spaceId=7a659d26-47c8-4fe7-b59f-2d570ed8bddf&width=2000&userId=&cache=v2)
Si $(v,w)$ = $(w,v)$, son equivalentes (simétrico) → ***grafo no dirigido***.

En este caso, v y w son **adyacentes** y la arista $(v,w)$ es incidente sobre v y w.
![](https://joseelv.notion.site/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2F7a659d26-47c8-4fe7-b59f-2d570ed8bddf%2F6ecbd23e-ddad-4c0c-a5b7-e3d4127fac70%2FUntitled.png?table=block&id=f26ecad8-adcb-43e0-beff-73c2264ec060&spaceId=7a659d26-47c8-4fe7-b59f-2d570ed8bddf&width=2000&userId=&cache=v2)


Una arista puede tener un valor asociado (peso), que representa un tiempo, distancia, coste, etc. Un grafo cuyas aristas tienen un peso asociado se denomina. → ***grafo ponderado***.
![](https://joseelv.notion.site/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2F7a659d26-47c8-4fe7-b59f-2d570ed8bddf%2F42a17b33-3dc6-4542-8ac2-40520ba8373f%2FUntitled.png?table=block&id=b9ee7ec8-9644-4dba-b128-f385339ffc3c&spaceId=7a659d26-47c8-4fe7-b59f-2d570ed8bddf&width=1440&userId=&cache=v2)
##  Definiciones

***Grado →***  El grado en un grado no dirigido → número de arcos. Si el grado es dirigido se distingue entre numero de entrada (número de arcos incidentes ) y grado de salida ( número de arcos adyacentes).
***Camino →***  Una sucesión de vértices de un grado $n_1, n_2,...,n_k$ tal que $(n_i,\ n_{i+1})$ es una arista para $1 ≤ i < k$. La **longitud** es el número de arcos/aristas que comprende → número de nodos - 1.

***Camino simple →***  Camino cuyo arcos/aristas son todos distintos. Si además todos los vértices son distintos → ***camino elemental***.

***Ciclo →***  Camino en el que coinciden los vértices inicio y final. Si el camino es simple → *ciclo simple* y si el camino es elemental → *ciclo elemental*. 

***Grafo conexo→***  Grafo no dirigido en el que al menos hay un camino por cada par de vértices del mismo.
![](https://joseelv.notion.site/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2F7a659d26-47c8-4fe7-b59f-2d570ed8bddf%2F5bc81c49-79ab-4de4-9900-715e871edf3b%2FUntitled.png?table=block&id=d692a8aa-dc88-462e-8ea3-acffb7bd3f3e&spaceId=7a659d26-47c8-4fe7-b59f-2d570ed8bddf&width=2000&userId=&cache=v2)


