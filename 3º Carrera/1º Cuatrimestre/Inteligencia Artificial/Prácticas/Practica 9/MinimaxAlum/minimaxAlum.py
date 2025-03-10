from tictactoeAlum import *

## Indicamos el límite de la proundidad con límite
LIMITE = 5


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


######################Código de la P8######################
# def minimax(nodo: Nodo) -> Nodo:
#     mejor_jugada = None
#     player = 1
#     valor_max = -float('inf')
#     jugadas = [Jugada(i,j) for i in range(3) for j in range(3)]

#     for jugada in jugadas:
#         if esValida(nodo, jugada):
#             intento = aplicaJugada(nodo, jugada, player)  # Simulamos la jugada.
#             valor_actual = valorMin(intento)  # Calculamos el valor mínimo del siguiente turno.
#             if valor_actual > valor_max:
#                 valor_max = valor_actual
#                 mejor_jugada = jugada  # Actualizamos la mejor jugada.

#     nodo = aplicaJugada(nodo, mejor_jugada, player)  # Ejecutamos la mejor jugada.
#     return nodo

# def valorMin(nodo: Nodo) -> int:
#     player = -1
#     valor_min = float('inf')
#     #Lista de todas las jugadas posibles
#     jugadas = [Jugada(i,j) for i in range(3) for j in range(3)]

#     if terminal(nodo):
#         return utilidad(nodo)
#     else:
#         for jugada in jugadas:
#             if esValida(nodo,jugada):
#             #Si la jugada es válida, realizamos una nueva jugada en otro nodo
#                 intento = aplicaJugada(nodo, jugada, player)
#                 valor_min = min(valor_min, valorMax(intento))
#     return valor_min

# def valorMax(nodo: Nodo) -> int:
#     player = 1
#     valor_max = -float('inf') #valor menos infinito
#     jugadas = [Jugada(i,j) for i in range(3) for j in range(3)] # creamos la lista de todas las jugadas posibles
#     if terminal(nodo):
#         return utilidad(nodo)
#     else:
#         for jugada in jugadas:
#             if esValida(nodo,jugada):
#                 intento = aplicaJugada(nodo,jugada,player)
#                 valor_max = max(valor_max,valorMin(intento))
#     return valor_max

##############################################Práctica 9##############################################
def heuristica(nodo: Nodo, player: int) -> int:
    valor_heuristica = 0

    # Evaluamos filas y columnas
    for i in range(3):
        fila_actual = nodo.tablero[i, :]
        col_actual = nodo.tablero[:, i]
        valor_fila = evalua_linea(fila_actual, player)
        valor_col = evalua_linea(col_actual, player)
        valor_heuristica += valor_fila + valor_col

    # Evaluamos las diagonales
    diagonal_principal = np.diagonal(nodo.tablero)
    diagonal_inversa = np.diagonal(np.fliplr(nodo.tablero))
    valor_diag_principal = evalua_linea(diagonal_principal, player)
    valor_diag_inversa = evalua_linea(diagonal_inversa, player)
    valor_heuristica += valor_diag_principal + valor_diag_inversa

    return valor_heuristica


def evalua_linea(linea: np.array, player: int) -> int:
    oponente = opuesto(player)

    # Contamos celdas ocupadas por el jugador y el oponente
    cuenta_player = np.count_nonzero(linea == player)
    cuenta_oponente = np.count_nonzero(linea == oponente)
    celdas_vacias = np.count_nonzero(linea == 0)

    # Línea completamente del jugador
    if cuenta_player == 3:
        return 100

    # Línea completamente del oponente
    if cuenta_oponente == 3:
        return -100

    # Línea con ventaja para el jugador
    if cuenta_oponente == 0:
        return 10 * cuenta_player

    # Línea con ventaja para el oponente
    if cuenta_player == 0:
        return -10 * cuenta_oponente

    # Línea neutral
    return 0
#Modificamos un poco el código de minimax para que la expansión tenga un límite.
def minimax(nodo: Nodo) -> Nodo:
    mejor_jugada = None
    player = 1
    valor_max = -float('inf')
    jugadas = [Jugada(i,j) for i in range(3) for j in range(3)]

    for jugada in jugadas:
        if esValida(nodo, jugada):
            intento = aplicaJugada(nodo, jugada, player)  # Simulamos la jugada.
            valor_actual = valorMin(intento,1)  # Calculamos el valor mínimo del siguiente turno.
            if valor_actual > valor_max:
                valor_max = valor_actual
                mejor_jugada = jugada  # Actualizamos la mejor jugada.

    nodo = aplicaJugada(nodo, mejor_jugada, player)  # Ejecutamos la mejor jugada.
    return nodo

def valorMin(nodo: Nodo, profundidad: int) -> int:
    player = -1
    valor_min = float('inf')

    if terminal(nodo):
        return utilidad(nodo)
    if profundidad >= LIMITE:
        return heuristica(nodo,player)
    else:
        #Lista de todas las jugadas posibles
        jugadas = [Jugada(i,j) for i in range(3) for j in range(3)]
        for jugada in jugadas:
            if esValida(nodo,jugada):
            #Si la jugada es válida, realizamos una nueva jugada en otro nodo
                intento = aplicaJugada(nodo, jugada, player)
                valor_min = min(valor_min, valorMax(intento,profundidad+1))
    return valor_min

def valorMax(nodo: Nodo, profundidad: int) -> int:
    player = 1
    valor_max = -float('inf') #valor menos infinito
    if terminal(nodo):
        return utilidad(nodo)
    if profundidad >= LIMITE:
        return heuristica(nodo,player)
    else:
        jugadas = [Jugada(i,j) for i in range(3) for j in range(3)] # creamos la lista de todas las jugadas posibles
        for jugada in jugadas:
            if esValida(nodo,jugada):
                intento = aplicaJugada(nodo,jugada,player)
                valor_max = max(valor_max,valorMin(intento,profundidad+1))
    return valor_max

def poda_ab(nodo: Nodo) -> Nodo:
    #Función qu decide la mejor jugada
    player = 1
    prof = 0 #profundidad inicial
    alfa =  -float('inf')
    beta = float('inf')
    jugadas = [Jugada(i,j) for i in range(3) for j in range(3)]

    for jugada in jugadas:
        if esValida(nodo,jugada):
            intento = aplicaJugada(nodo,jugada,player)
            valor_actual = valorMin_ab(intento,prof+1,alfa,beta)
            if valor_actual > alfa:
                alfa = valor_actual
                mejor_jugada = jugada
    
    nodo = aplicaJugada(nodo,mejor_jugada,player)
    return nodo


def valorMin_ab(nodo: Nodo, profundidad: int, alfa: float, beta: float) -> int:
    if terminal(nodo):
        return utilidad(nodo)
    if profundidad >= LIMITE:
        return heuristica(nodo,-1)
    else:
        jugadas = [Jugada(i,j) for i in range(3) for j in range(3)]
        for jugada in jugadas:
            if alfa < beta:
                if esValida(nodo, jugada):
                    intento = aplicaJugada(nodo,jugada,-1)
                    beta = min(beta,valorMax_ab(intento,profundidad+1,alfa,beta))
    return beta

def valorMax_ab(nodo: Nodo, profundidad: int, alfa: float, beta: float) -> int:
    if terminal(nodo):
        return utilidad(nodo)
    if profundidad >= LIMITE:
        return heuristica(nodo,1)
    else:
        jugadas = [Jugada(i,j) for i in range(3) for j in range(3)]
        for jugada in jugadas:
            if alfa < beta:
                if esValida(nodo,jugada):
                    intento = aplicaJugada(nodo, jugada, 1)
                    alfa = max(alfa,valorMin_ab(intento,profundidad+1,alfa,beta))
    return alfa



def heuristicaTICTACTOE(nodo: Nodo) -> int:
    lineas = [
        nodo.tablero[0,:],
        nodo.tablero[1,:],
        nodo.tablero[2,:],
        nodo.tablero[:,0],
        nodo.tablero[:,1],
        nodo.tablero[:,2],
        np.diagonal(nodo.tablero),
        np.fliplr(nodo.tablero).diagonal()
    ]
    puntuacion = 0
    for linea in lineas:
        if np.all(linea == 1): #Gana Max
            puntuacion += 100
        elif np.all(linea == -1): #Gana Min
            puntuacion -= 100
        elif np.sum(linea == 1) > np.sum(linea == -1): #Más fichas a Max
            puntuacion += 10
        elif np.sum(linea == 1) < np.sum(linea == -1): #Más fichas a min
            puntuacion -= 10

    return puntuacion