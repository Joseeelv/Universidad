from __future__ import annotations
from NPuzle_Alum import *


@dataclass
class Nodo:
    estado: tEstado
    operador: str
    costeCamino: int
    profundidad: int
    padre: Nodo


def nodoInicial() -> Nodo:
    return Nodo(estadoInicial(), None, 0, 0, None)


def dispCamino(nodo: Nodo) -> None:
    lista = []
    aux = nodo
    while aux.padre != None:
        lista.append((aux.estado.tablero, aux.operador))
        aux = aux.padre
    for i in lista[::-1]: # Se utiliza ::-1 para recorrer la lista en sentido inverso, desde la raíz hasta el nodo objetivo.
        print("Operador: ", operadores[i[1]], "\n", i[0])
        print()


def dispSolucion(nodo: Nodo) -> None:
    dispCamino(nodo)
    print("Profundidad: ", nodo.profundidad)
    print("Coste: ", nodo.costeCamino)


def expandir(nodo: Nodo) -> list:
  nodos = []
  # Completar el código.
  for operador in operadores:
    if esValido(operador,nodo.estado):
      nuevo_estado = aplicaOperador(operador,nodo.estado)
      # Creamos el nuevo nodo, hijo de "nodo"
      nuevoNodo = Nodo(estado = nuevo_estado,
      operador = operador,
      costeCamino = nodo.costeCamino+coste(operador, nodo), #hacemos uso del métodos coste()
      profundidad = nodo.profundidad+1,
      padre = nodo)
      nodos.append(nuevoNodo) #guardamos el nodo
  return nodos


def busquedaAnchura() -> bool:
  objetivo = False
  raiz = nodoInicial()
  abiertos = [] 
  sucesores = [] # nodos no abiertos
  abiertos.append(raiz)
  # Se ejecuta mientras haya nodos cerrados y no se haya llegado a la solución
  while abiertos and not objetivo:
    nodo_actual = abiertos.pop(0) #sacamos el primer nodo
    # comprobamos que sea el objetivo
    if testObjetivo(nodo_actual.estado):
       objetivo = True
    # Si no es objetivo, expandimos
    sucesores = expandir(nodo_actual)
    abiertos.extend(sucesores)
  
  if objetivo: #Comprobamos si es las solución
    dispSolucion(nodo_actual)
  elif not objetivo:
    print("No se ha encontrado solución")

  return objetivo 


#búsquda en profundida
def busquedaProfundidad() -> bool:
  objetivo = False
  raiz = nodoInicial()
  abiertos = [] 
  abiertos.append(raiz)

  while len(abiertos) > 0 and not objetivo:
     nodo_actual = abiertos.pop() #sacamos el último nodo LIFO
     if testObjetivo(nodo_actual.estado):
        objetivo = True
  sucesores = expandir(nodo_actual)
  abiertos.extend(sucesores)

  if objetivo: #Comprobamos si es las solución
    dispSolucion(nodo_actual)
  elif not objetivo:
    print("No se ha encontrado solución")

  return objetivo 

