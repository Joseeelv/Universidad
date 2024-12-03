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
    nodo_actual = abiertos.pop(0) #sacamos el primer nodo FIFO
    # comprobamos que sea el objetivo
    if testObjetivo(nodo_actual.estado):
       objetivo = True
       break
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

  while abiertos and not objetivo:
    nodo_actual = abiertos.pop() #sacamos el último nodo LIFO
    if testObjetivo(nodo_actual.estado):
      objetivo = True
      break
    sucesores = expandir(nodo_actual)
    abiertos.extend(sucesores)

  if objetivo: #Comprobamos si es las solución
    dispSolucion(nodo_actual)
  elif not objetivo:
    print("No se ha encontrado solución")

  return objetivo

#búsqueda Profundidad Limitada
def busquedaProfundidadLimitada(limite: int) -> bool:
  raiz = nodoInicial()
  abiertos = [] 
  abiertos.append(raiz)

  while len(abiertos) > 0:
     print(f"Tamaño de la lista: {len(abiertos)}")
     nodo_actual = abiertos.pop()

     if nodo_actual.profundidad > limite:
        #Si hemos llegado al límite, no procesamos ese nodo
        continue
     
     if testObjetivo(nodo_actual.estado):
        dispSolucion(nodo_actual)
        return True
     
     sucesores = expandir(nodo_actual)
     for sucesor in sucesores:
      abiertos.append(sucesor)
  
  print("No se ha encontrado solución")
  return False

#búsqueda Profundidad Limitada Iterativa
def busquedaProfundidadLimitadaIter(limite_max: int) -> bool:
  for limite in range (limite_max + 1):
    print(f"Realizando búsqueda con límite de profundidad {limite_max}")
    if busquedaProfundidadLimitada(limite):
       return True
  print("No se ha encontrado solución")
  return False

# Busqueda en Anchura con control de estados
def BusquedaAnchuraEstados() -> bool:
  raiz = nodoInicial()
  abiertos = [] 
  sucesores = [] # nodos no abiertos
  cerrados = [] # lista de cerrados
  abiertos.append(raiz)
  while len(abiertos) > 0:
    nodo_actual = abiertos.pop(0) #Sacamos el primero

    if testObjetivo(nodo_actual.estado):
      dispSolucion(nodo_actual)
      return True
    
    #Marcamos el nodo actual como visitado y leugo expandimos
    if nodo_actual.estado not in cerrados:
       cerrados.append(nodo_actual.estado)
       
    sucesores = expandir(nodo_actual)
    for sucesor in sucesores:
      abiertos.append(sucesor)
  #No encontramos solución
  print("No se ha encontrado solución")
  return False

# Busqueda en Profundidad con control de estados
def BusquedaProfundidadEstados() -> bool:
  raiz = nodoInicial()
  abiertos = [] 
  sucesores = [] # nodos no abiertos
  cerrados = [] # lista de cerrados
  abiertos.append(raiz)
  while len(abiertos) > 0:
     nodo_actual = abiertos.pop() #Sacamos el último insertado

     if testObjetivo(nodo_actual.estado):
        dispSolucion(nodo_actual)
        return True
     
     #Marcamos el nodo actual como visitado y luego expandimos
     if nodo_actual.estado not in cerrados:
        cerrados.append(nodo_actual.estado)

     sucesores = expandir(nodo_actual)
     for sucesor in sucesores:
      abiertos.append(sucesor)
  #No encontramos solución
  print("No se ha encontrado solución")
  return False