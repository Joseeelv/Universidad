import numpy as np
from dataclasses import dataclass
import copy

operadores = {"8": "ARRIBA", "2": "ABAJO", "4": "IZQUIERDA", "6": "DERECHA"}

@dataclass
class tEstado:
    tablero: np.ndarray
    fila: int
    col: int

    def __init__(self, tablero: np.ndarray):
        self.tablero = tablero
        self.N = self.tablero.shape[0]
        self.fila, self.col = np.where(self.tablero == 0)
        self.fila = self.fila[0]
        self.col = self.col[0]

    def __repr__(self) -> str:
        return f"{self.tablero}\n Fila: {self.fila}\n Col: {self.col}\n"

def estadoInicial() -> tEstado:
    puzle_inicial = np.array(
    [
        [0, 2, 3], 
        [1, 4, 5], 
        [8, 7, 6]
    ])
    return tEstado(puzle_inicial)

def estadoObjetivo() -> tEstado:
    puzle_final = np.array(
    [
        [1, 2, 3], 
        [4, 5, 6], 
        [7, 8, 0]
    ])
    return tEstado(puzle_final)

def coste(operador: str, estado: tEstado) -> int:
    return 1

def dispOperador(operador: str) -> None:
    print(f"Operador: {operadores[operador]}")

def iguales(actual: tEstado, objetivo: tEstado) -> bool:
    return np.array_equal(actual.tablero, objetivo.tablero)

def testObjetivo(actual: tEstado) -> bool:
    objetivo = estadoObjetivo()
    return iguales(actual, objetivo)

def esValido(operador: str, estado: tEstado) -> bool:
    valido = False
    match operadores[operador]:
        case "ARRIBA":
            valido = estado.fila > 0
        case "ABAJO":
            valido = estado.fila < estado.N - 1
        case "IZQUIERDA":
            valido = estado.col > 0
        case "DERECHA":
            valido = estado.col < estado.N - 1
    return valido

def aplicaOperador(operador: str, estado: tEstado) -> tEstado:
    nuevo = copy.deepcopy(estado)
    match operadores[operador]:
        case "ARRIBA":
            nuevo.fila -= 1
        case "ABAJO":
            nuevo.fila += 1
        case "IZQUIERDA":
            nuevo.col -= 1
        case "DERECHA":
            nuevo.col += 1
    
    ficha = nuevo.tablero[nuevo.fila, nuevo.col]
    nuevo.tablero[nuevo.fila, nuevo.col] = 0
    nuevo.tablero[estado.fila, estado.col] = ficha

    return nuevo
