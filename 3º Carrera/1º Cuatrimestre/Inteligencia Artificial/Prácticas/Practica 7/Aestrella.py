import numpy as np
from dataclasses import dataclass
import copy
from NPuzle_Alum import *
from busquedaAlum import *

def Aesrella(estado_inicial: tEstado, estado_objetivo: tEstado, heuristica: int)-> bool:
  raiz = Nodo(estado_inicial, None, 0, 0, None)
  abiertos = [(raiz, heuristica(raiz.estado) + raiz.coste)]
  cerrados = []

  while abiertos:
      # Ordenar por f(n) = g(n) + h(n)
      abiertos.sort(key=lambda x: x[1])
      nodo_actual, _ = abiertos.pop(0)

      # Comprobamos si el estado actual es el objetivo
      if iguales(nodo_actual.estado, estado_objetivo):
          dispSolucion(nodo_actual)
          return True

      # Si no está cerrado, expandimos
      if not any(iguales(nodo_actual.estado, cerrado.estado) for cerrado in cerrados):
          cerrados.append(nodo_actual)
          sucesores = expandir(nodo_actual)
          for sucesor in sucesores:
              f_n = sucesor.coste + heuristica(sucesor.estado)
              abiertos.append((sucesor, f_n))

  print("No se ha encontrado solución")
  return False


## Comparativa
def Comparativa(r):