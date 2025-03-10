import numpy as np 
from dataclasses import dataclass 
from copy import deepcopy 

cuenta_nodos = 0  # Inicializamos la variable global

@dataclass
class Nodo:
    tablero: np.array
    # Puede añadir más atributos si lo considera oportuno 

    def __init__(self, tablero):
        self.tablero = tablero

    def __str__(self):
        visual = {-1: "🟡", 1: "🔴", 0.0: " "}
        string = ""
        for i in range(self.tablero.shape[0]):
            for j in range(self.tablero.shape[1]):
                if i==0 and j==0:
                    string+="|"
                if self.tablero[i, j] == 0:
                    string += "    |"
                else:
                    string += f" {visual[self.tablero[i, j]]} |"
            if  i < self.tablero.shape[0]-1:
                string += f"\n ----+----+----+----+----+----+----\n|"
            else:
                
                string += f"\n ----+----+----+----+----+----+----\n"
        return f"{string}"

@dataclass
class Jugada:
    # Implementar de acuerdo con lo que necesite o bien, puede eliminarlo y realizar 
    # los cambios en el resto del código que hace referencia a Jugada.
    #Está asociada a la columna que elegimos para introducir la ficha
    columna: int 

    def __init__(self, columna: int):
        self.columna = columna
    

def NodoInicial():
    tablero = np.zeros((6,7))
    return Nodo(tablero)

def NodoInicial_Poda():
    tablero = np.array([
        [1, 0, 0, 0, 0, 0, 0],
        [-1, 0, 0, 0, 0, 0, 1],
        [1, 1, -1, 0, -1, -1, 1],
        [-1, 1, -1, -1, 1, 1, -1],
        [-1, -1, 1, 1, -1, 1, 1],
        [1, -1, -1, -1, 1, 1, -1]
    ])
    return Nodo(tablero)

def esValida(actual: Nodo, jugada: Jugada) -> bool:
    # Comprobamos si la columna está llena (el primer valor de la columna es 0) o que esté dentro del rango
    return 0 <= jugada.columna < actual.tablero.shape[1] and actual.tablero[0, jugada.columna] == 0

def aplicaJugada(actual: Nodo, jugada: Jugada, jugador: int) -> Nodo:
    # Buscamos una fila donde podamos colocar la ficha 
    # Usamos la columna y el jugador de la clase Jugada para aplicar la jugada
    columna = jugada.columna
    for fila in range(actual.tablero.shape[0] - 1, -1, -1):
        if actual.tablero[fila, columna] == 0:  # Si la celda está vacía
            # Colocar la ficha del jugador en esa posición
            nuevo_tablero = deepcopy(actual.tablero)
            nuevo_tablero[fila, columna] = jugador
            # Devolver el nuevo nodo con el tablero actualizado
            return Nodo(nuevo_tablero)
    
    # Si no se puede realizar la jugada (columna llena), devolver el nodo sin cambios
    return actual  

def terminal(actual: Nodo) -> bool:
    #Comprobamos si es un nodo terminal, es decir, que hay un ganador o todas sus columnas están rellenas
    return np.all(actual.tablero != 0) or HayGanador(actual)

def ComprobarFila(actual: Nodo, i: int, j: int) -> bool:
    # Comprobamos que haya espacio suficiente para 4 fichas consecutivas en la fila
    if j + 3 < actual.tablero.shape[1]:
        # Verificamos si las 4 fichas son iguales
        for k in range(4):
            if actual.tablero[i, j + k] != actual.tablero[i, j]:
                return False
        return True
    return False

def ComprobarColumna(actual: Nodo, i: int, j: int) -> bool:
    # Comprobamos que haya espacio suficiente para 4 fichas consecutivas en la columna
    if i + 3 < actual.tablero.shape[0]:
        # Verificamos si las 4 fichas son iguales
        for k in range(4):
            if actual.tablero[i + k, j] != actual.tablero[i, j]:
                return False
        return True
    return False

def ComprobarDiagonal(actual: Nodo, i: int, j: int) -> bool:
    # Comprobamos la diagonal hacia abajo a la derecha
    if i + 3 < actual.tablero.shape[0] and j + 3 < actual.tablero.shape[1]:
        for k in range(4):
            if actual.tablero[i + k, j + k] != actual.tablero[i, j]:
                return False
        return True
    # Comprobamos la diagonal hacia abajo a la izquierda
    if i + 3 < actual.tablero.shape[0] and j - 3 >= 0:
        for k in range(4):
            if actual.tablero[i + k, j - k] != actual.tablero[i, j]:
                return False
        return True
    return False

def HayGanador(actual: Nodo) -> bool:
    # Recorremos todo el tablero
    for i in range(actual.tablero.shape[0]):
        for j in range(actual.tablero.shape[1]):
            if actual.tablero[i, j] != 0:  # Comprobamos solo casillas no vacías
                # Comprobamos si hay 4 fichas consecutivas en fila, columna o diagonal
                if ComprobarFila(actual, i, j) or ComprobarColumna(actual, i, j) or ComprobarDiagonal(actual, i, j):
                    return True
    return False


def utilidad(nodo: Nodo) -> int:
    #Devolvemos el valor de restar el número de fichas de cada jugador
    return np.sum(nodo.tablero == 1) - np.sum(nodo.tablero == -1)

def heuristica(nodo: Nodo) -> int:
    #Devolvemos el valor de la heurística de ese nodo, podríamos devolver la diferencia de fichas de cada jugador, para ver que jugada le renta más
    return utilidad(nodo)

def jugadaAdversario(juego: Nodo) -> Nodo:
    columna = int(input("Elige una columna (0-6): "))
    while not esValida(juego, Jugada(columna)):
        print("Columna no válida, inténtalo de nuevo.")
        columna = int(input("Elige una columna (0-6): "))
    return aplicaJugada(juego, Jugada(columna), -1)  # El jugador humano es el 2, que es -1 en tu código

def opuesto(jugador: int) -> int:
    return -jugador

def minimax(actual: Nodo) -> Nodo:

    global cuenta_nodos
    cuenta_nodos += 1

    if terminal(actual):
        return actual

    jugador = 1
    valor_max = -float('inf')
    for columna in range (actual.tablero.shape[1]):
        if esValida(actual, Jugada(columna)):
            intento = aplicaJugada(actual,Jugada(columna),jugador)
            valor_actual = valorMin(intento)
            if valor_actual > valor_max:
                valor_max = valor_actual
                mejor_jugada = Jugada(columna)

    return aplicaJugada(actual, mejor_jugada, 1)


def valorMin(actual: Nodo) -> int:
    valor_min = float('inf')
    
    if terminal(actual):
        return utilidad(actual)
    
    #Recorremos todas las jugadas posibles
    for columna in range(actual.tablero.shape[1]):
        if esValida(actual, Jugada(columna)):
            intento = aplicaJugada(actual, Jugada(columna), -1)
            valor_min = min(valor_min, valorMax(intento))
    return valor_min
    
def valorMax(actual: Nodo) -> int:
    valor_max = -float('inf')

    if terminal(actual):
        return utilidad(actual)
    
    #Recorremos todas jugadas
    for columna in range(actual.tablero.shape[1]):
        if esValida(actual,Jugada(columna)):
            intento = aplicaJugada(actual,Jugada(columna),1)
            valor_max = max(valor_max,valorMin(intento))
    return valor_max