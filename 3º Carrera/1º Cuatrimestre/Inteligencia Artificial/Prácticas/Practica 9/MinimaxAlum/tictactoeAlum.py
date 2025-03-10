from __future__ import annotations
from copy import deepcopy
from dataclasses import dataclass
import numpy as np

visual = {1: "❌", -1: "⭕", 0.0: " "}




@dataclass
class Nodo:
    tablero: np.array
    vacias: int
    N: int

    def __init__(self, tablero):
        self.tablero = tablero
        self.N = self.tablero.shape[0]
        self.vacias = len(np.where(tablero == 0)[0])

    def __str__(self):
        string = f"{' ----+----+----'}\n|"
        for i in range(self.tablero.shape[0]):
            for j in range(self.tablero.shape[1]):
                if self.tablero[i, j] == 0:
                    string += "    |"
                else:
                    string += f" {visual[self.tablero[i, j]]} |"
            if i == 2 and j == 2:
                string += f"\n ----+----+----\n"
            else:
                string += f"\n ----+----+----\n|"
        return f"{string}"


@dataclass
class Jugada:
    x: int
    y: int

    def __str__(self):
        return f"\nFila: ({self.x}, Col: {self.y})"


######
# Se crean todas las posibles jugadas para el for de rango (for jugada in jugadas)
jugadas = []
for i in range(0, 3):
    for j in range(0, 3):
        jugadas.append(Jugada(i, j))
######

""" Funciones complementarias
    * crearNodo
    * nodoInicial
    * opuesto
"""


def crearNodo(tablero):
    return Nodo(tablero)


def nodoInicial():
    tablero_inicial = np.zeros((3, 3))
    return Nodo(tablero_inicial)


def opuesto(jugador):
    return jugador * -1


""" Funciones Búsqueda MiniMax
    * aplicaJugada
    * esValida
    * terminal
    * utilidad
"""


def aplicaJugada(actual: Nodo, jugada: Jugada, jugador: int) -> Nodo:
    """Realiza una copia del nodo recibido como parámetro y aplica la jugada indicada,
    modificando para ello los atributos necesarios. Para esto, se tiene en cuenta qué
    jugador realiza la jugada.

    Args:
        actual (Nodo)
        jugada (Jugada)
        jugador (int)

    Raises:
        NotImplementedError: Mientras que no termine de implementar esta función, puede mantener
        esta excepción.

    Returns:
        Nodo: Contiene la información del nuevo estado del juego.
    """

    nuevo_tablero = deepcopy(actual.tablero)
    if nuevo_tablero[jugada.x,jugada.y] == 0: #if esValida(Nodo,jugada):
        nuevo_tablero[jugada.x, jugada.y] = jugador
        return Nodo(nuevo_tablero)
    else:
        raise NotImplementedError


def esValida(actual: Nodo, jugada: Jugada) -> bool:
    """Comprueba si dada una Jugada, es posible aplicarla o no.

    Args:
        actual (Nodo)
        jugada (Jugada)

    Raises:
        NotImplementedError: Mientras que no termine de implementar esta función, puede mantener
        esta excepción.

    Returns:
        bool: Devuelve True en caso de que pueda realizarse la Jugada, False en caso contrario
    """
    return actual.tablero[jugada.x,jugada.y] == 0
    raise NotImplementedError


def terminal(actual: Nodo) -> bool:
    """Comprueba si el juego se ha acabado, ya sea porque alguno de los jugadores ha ganado o bien
    porque no sea posible realizar ningún movimiento más.

    Args:
        actual (Nodo)

    Raises:
        NotImplementedError: Mientras que no termine de implementar esta función, puede mantener
        esta excepción.

    Returns:
        bool: Devuelve True en caso de Terminal, False en caso contrario
    """

    ###                                 Importante:
    #   Si considera más sencillo trabajar con una representación en vector en lugar de matriz puede
    #   hacer uso de la función reshape o la función flatten que contiene la biblioteca numpy. 
    #   Puede comprobar un ejemplo si ejecuta este código mediante python tictactoeAlum.py
    ###
    ##Comprobamo que estén alineados vertical u horizontalmente
    for i in range(3):
        if abs(np.sum(actual.tablero[i,:])) == 3 or abs(np.sum(actual.tablero[:,i])) == 3:
            return True
    #Comprobamos que están alineados diagonalmente
    #Invertimos su eje diagonal con fliplr.
    if abs(np.sum(np.diagonal(actual.tablero))) == 3 or abs(np.sum(np.diagonal(np.fliplr(actual.tablero)))) == 3:
        return True
    # Si no hay casillas vacías, ni ganador, entonces será empate
    if actual.vacias == 0:
        return True
    
    return False #No se ha terminado el juego

    ################Versión con flatten()################
    #Convertimos el tablero 3x3 en un vector de 9 elementos con flatten
    # tablero_vector = actual.tablero.flatten()
    
    # # Comprobamos si algún jugador ha ganado en las filas
    # for i in range(3):
    #     if abs(np.sum(tablero_vector[i*3:(i+1)*3])) == 3:
    #         return True
    
    # # Comprobamos si algún jugador ha ganado en las columnas
    # for i in range(3):
    #     if abs(np.sum(tablero_vector[i::3])) == 3:
    #         return True
    
    # #Comprobamos si algún jugador ha ganado en las diagonales
    # if abs(np.sum(tablero_vector[::4])) == 3: 
    #     return True
    # if abs(np.sum(tablero_vector[2:8:2])) == 3:
    #     return True
    
    # # Si no hay casillas vacías, ni ganador, entonces es empate
    # if actual.vacias == 0:
    #     return True
    
    # # El juego no ha terminado
    # return False


def utilidad(nodo: Nodo) -> int:
    """La función de utilidad, también llamada objetivo, asigna un valor numérico al nodo recibido como parámetro.
    Por ejemplo, en un juego de 'Suma cero', se puede establecer que devuelve -100, 0, 100 en función de qué jugador
    gana o bien si hay un empate.

    Args:
        nodo (Nodo)

    Raises:
        NotImplementedError: Mientras que no termine de implementar esta función, puede mantener
        esta excepción.

    Returns:
        int: Valor de utilidad
    """
    for i in range(3):
        #Comprobamos filas y columnas
        if abs(np.sum(nodo.tablero[i,:])) == 3:
            return int(np.sign(np.sum(nodo.tablero[i,:])))
        if abs(np.sum(nodo.tablero[:,i])) == 3:
            return int(np.sign(np.sum(nodo.tablero[:,i])))
    # Ahora revisamos las diagonales
    if abs(np.sum(np.diagonal(nodo.tablero))) == 3:
        return int(np.sign(np.sum(np.diagonal(nodo.tablero))))
    if abs(np.sum(np.diagonal(np.fliplr(nodo.tablero)))) == 3:
        return int(np.sign(np.sum(np.diagonal(np.fliplr(nodo.tablero)))))

    # Si no hay ganador, entonces hay un empate
    return 0


if __name__ == "__main__":
    M = np.array([
        [1,2],
        [3,4]
    ])
    print(M)
    M_vector = M.reshape(4)
    print(M_vector)
    M_vector = M.flatten()
    print(M_vector)
    M_de_nuevo = M_vector.reshape(2,2)
    print(M_de_nuevo)


    