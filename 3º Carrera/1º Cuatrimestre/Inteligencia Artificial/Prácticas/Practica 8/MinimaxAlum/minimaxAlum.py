from tictactoeAlum import *


def PSEUDOminimax(nodo):
    mejorJugada = -1
    puntos = -2
    for jugada in jugadas:
        if esValida(nodo, jugada):
            intento = aplicaJugada(nodo, jugada, 1)
            util = utilidad(intento)
            if util > puntos:
                puntos = util
                mejorJugada = jugada
    nodo = aplicaJugada(nodo, mejorJugada, 1)
    return nodo


def jugadaAdversario(nodo):
    valida = False
    jugada = None
    while not valida:
        fila = int(input("Fila: "))
        col = int(input("Col: "))
        jugada = Jugada(fila, col)
        valida = esValida(nodo, jugada)
        if not valida:
            print("\n Intenta otra posicion del tablero \n")
    nodo = aplicaJugada(nodo, jugada, -1)
    return nodo

def minimax(nodo: Nodo) -> Nodo:
    mejor_jugada = None
    player = 1
    valor_max = -float('inf')
    jugadas = [Jugada(i,j) for i in range(3) for j in range(3)]

    for jugada in jugadas:
        if esValida(nodo, jugada):
            intento = aplicaJugada(nodo, jugada, player)  # Simulamos la jugada.
            valor_actual = valorMin(intento)  # Calculamos el valor mínimo del siguiente turno.
            if valor_actual > valor_max:
                valor_max = valor_actual
                mejor_jugada = jugada  # Actualizamos la mejor jugada.

    nodo = aplicaJugada(nodo, mejor_jugada, player)  # Ejecutamos la mejor jugada.
    return nodo

def valorMin(nodo: Nodo) -> int:
    player = -1
    valor_min = float('inf')
    #Lista de todas las jugadas posibles
    jugadas = [Jugada(i,j) for i in range(3) for j in range(3)]

    if terminal(nodo):
        return utilidad(nodo)
    else:
        for jugada in jugadas:
            if esValida(nodo,jugada):
            #Si la jugada es válida, realizamos una nueva jugada en otro nodo
                intento = aplicaJugada(nodo, jugada, player)
                valor_min = min(valor_min, valorMax(intento))
    return valor_min

def valorMax(nodo: Nodo) -> int:
    player = 1
    valor_max = -float('inf') #valor menos infinito
    jugadas = [Jugada(i,j) for i in range(3) for j in range(3)] # creamos la lista de todas las jugadas posibles
    if terminal(nodo):
        return utilidad(nodo)
    else:
        for jugada in jugadas:
            if esValida(nodo,jugada):
                intento = aplicaJugada(nodo,jugada,player)
                valor_max = max(valor_max,valorMin(intento))
    return valor_max
