from Conecta4_Alum import *
from time import time

ganador = 0
jugador = int(input("Introduzca el 1er jugador: 1 IA, 2 Tú "))

if jugador != 1:
    jugador = -1

juego = NodoInicial()
print(juego)
while not ganador: # Puede añadir si lo desea alguna condición adicional
    if jugador == 1:
        inicio = time()
        juego = minimax(juego)
        fin = time()
        print(f"Ha tardado un total de {fin-inicio} segundos")
    else:
        juego = jugadaAdversario(juego)
    print(juego)
    if terminal(juego):
        ganador = utilidad(juego)
    jugador = opuesto(jugador)

match ganador:
    case 0:
        print("EMPATE")
    case 100:
        print("GANA MAX (IA)")
    case -100:
        print("GANA MIN (JUGADOR)")
