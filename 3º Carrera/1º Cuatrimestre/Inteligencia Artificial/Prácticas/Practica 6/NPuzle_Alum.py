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

    def __repr__(self) -> str: # Permite representar el objeto como cadena
        return f"{self.tablero}\n Fila: {self.fila}\n Col: {self.col}\n"


# Estados para el 3-puzzlela Parte II
def estadoInicial3() -> tEstado:
    puzle_inicial = np.array(
    [
        [1,2],
        [0,3]
    ])
    return tEstado(puzle_inicial)


def estadoObjetivo3() -> tEstado:
    puzle_final = np.array(
    [
        [0,1],
        [2,3]
    ])
    return tEstado(puzle_final)


def estadoInicial() -> tEstado:
    puzle_inicial = np.array(
    [
        [8, 1, 3], 
        [0, 2, 4], 
        [7, 6, 5]
    ])
    return tEstado(puzle_inicial)


def estadoObjetivo() -> tEstado:
    puzle_final = np.array(
    [
        [1, 2, 3], 
        [8, 0, 4], 
        [7, 6, 5]
    ])
    return tEstado(puzle_final)


def coste(operador: str, estado: tEstado) -> int:
    return 1


def dispOperador(operador: str) -> None:
    print(f"Operador: {operadores[operador]}")


def iguales(actual: tEstado, objetivo: tEstado) -> bool:
    if not isinstance(actual, tEstado) or not isinstance(objetivo, tEstado):
        raise TypeError("Los argumentos deben ser instancias de tEstado.")
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
            valido = estado.fila < estado.N-1
        case "IZQUIERDA":
            valido = estado.col > 0
        case "DERECHA":
            valido = estado.col < estado.N-1
    return valido

def aplicaOperador(operador: str, estado: tEstado) -> tEstado:
    nuevo = copy.deepcopy(estado)  # Se hace la copia completa del estado anterior
    ficha = 0  # ficha vacía
    match operadores[operador]:
        case "ARRIBA":
            nuevo.fila = nuevo.fila - 1
        case "ABAJO":
            nuevo.fila = nuevo.fila + 1
        case "IZQUIERDA":
            nuevo.col = nuevo.col - 1
        case "DERECHA":
            nuevo.col = nuevo.col + 1
    
    # Intercambio del hueco por la posición de la ficha
    ficha = nuevo.tablero[nuevo.fila, nuevo.col]
    nuevo.tablero[nuevo.fila, nuevo.col] = 0
    nuevo.tablero[estado.fila, estado.col] = ficha

    return nuevo
