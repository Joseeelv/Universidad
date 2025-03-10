from minimaxAlum import *

def menu():
    """
    Muestra el menú y permite al usuario elegir el modo de juego.
    """
    print("Elige el algoritmo de la IA:")
    print("1. Minimax")
    print("2. Poda Alfa-Beta")
    while True:
        try:
            opcion = int(input("Introduce tu elección (1 o 2): "))
            if opcion in [1, 2]:
                return opcion
            else:
                print("Por favor, selecciona una opción válida (1 o 2).")
        except ValueError:
            print("Entrada inválida. Introduce un número válido.")

# Menú inicial para seleccionar algoritmo y el primer jugador
algoritmo = menu()
ganador = 0
jugador = int(input("Introduzca el 1er jugador: 1 (IA), 2 (Tú): "))

if jugador != 1:
    jugador = -1

# Inicializamos el juego
juego = nodoInicial()

# Bucle principal del juego
while juego.vacias > 0 and not ganador:
    if jugador == 1:  # Turno de la IA
        if algoritmo == 1:  # Minimax
            juego = minimax(juego)
        elif algoritmo == 2:  # Poda Alfa-Beta
            juego = poda_ab(juego)
    else:  # Turno del jugador humano
        juego = jugadaAdversario(juego)

    print(juego)

    # Comprobamos si el juego ha terminado
    if terminal(juego):
        ganador = utilidad(juego)

    # Cambiamos el turno
    jugador = opuesto(jugador)

# Mostramos el resultado del juego
match ganador:
    case 0:
        print("EMPATE")
    case 100:
        print("GANA MAX (IA)")
    case -100:
        print("GANA MIN (JUGADOR)")
