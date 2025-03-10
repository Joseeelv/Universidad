import numpy as np
from dataclasses import dataclass
import copy
from NPuzle_Alum import *


#Heurística de Manhattan
def HeuristicaManhattan(estado: tEstado) -> int:
  objetivo = estadoObjetivo.tablero()
  actual = estado.tablero
  distancia = 0
  for i in range (len(actual)):
    for j in range(len(actual[i])):
      valor = actual[i][j]
      if valor != 0:
        objetivo_i, objetivo_j = divmod(np.where(objetivo == valor)[0][0], estado.N)
        distancia += abs(i - objetivo_i) + abs(j - objetivo_j)
  return distancia

