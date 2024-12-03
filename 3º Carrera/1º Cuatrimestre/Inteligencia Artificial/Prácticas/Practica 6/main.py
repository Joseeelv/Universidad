from busquedaAlum import *


## Vamos a crear un menú para seleccionar que tipo puzzle vamos a usar

def Selector(tipo: str, estrategia: str, limite=None) -> None:

    if tipo == '8-puzzle':
        estado_inicial = estadoInicial()
        estado_objetivo = estadoObjetivo()
    elif tipo == '3-puzzle':
        estado_inicial = estadoInicial3()
        estado_objetivo = estadoObjetivo3()
    else:
        print('Elige o "8-puzzle" o "3-puzzle", porfavor')
        return   

    print(f"\nSeleccionaste el tipo: {tipo} y la estrategia: {estrategia}\n")

    if estrategia == "profundidad":
        BusquedaProdundidadGeneral(estado_inicial,estado_objetivo)
    elif estrategia == "anchura":
        BusquedaGeneralAnchura(estado_inicial,estado_objetivo)
    elif estrategia == "profundidadLimitada":
         if limite is not None:
            busquedaProfundidadLimitadaGeneral(estado_inicial, estado_objetivo, limite)
         else:
            print("Por favor, proporciona un límite para la búsqueda limitada.")
    elif estrategia == "profundidadLimitadaIter":
         if limite is not None:
            busquedaProfundidadLimitadaIterGeneral(estado_inicial, estado_objetivo, limite)
         else:
            print("Por favor, proporciona un límite para la búsqueda limitada.")
    elif estrategia == "anchuraEstados":
        BusquedaAnchuraEstadosGeneral(estado_inicial,estado_objetivo)
    elif estrategia == "anchuraEstados":
        BusquedaAnchuraEstadosGeneral(estado_inicial,estado_objetivo)
    elif estrategia == "profundidadEstados":
        BusquedaProfundidadEstadosGeneral(estado_inicial,estado_objetivo)
    elif estrategia == "voraz":
        VorazGeneral(estado_inicial,estado_objetivo)
    else:
        print("Estrategia no reconocida o parámetros faltantes")

print("Seleccione el tipo del puzzle y la estrategia: ")
# Función para interactuar con el usuario
def menu():
    print("Seleccione el tipo de puzzle (8-puzzle o 3-puzzle):")
    tipo = input("Tipo: ").strip()
    print("\nSeleccione la estrategia de búsqueda:")
    estrategias = [
        "profundidad", "anchura", "profundidadLimitada", 
        "profundidadLimitadaIter", "anchuraEstados", 
        "profundidadEstados", "voraz"
    ]
    print(f"Estrategias disponibles: {', '.join(estrategias)}")
    estrategia = input("Estrategia: ").strip()

    limite = None
    heuristica = None

    if estrategia in ["profundidadLimitada", "profundidadLimitadaIter"]:
        limite = int(input("Proporcione el límite de profundidad: ").strip())

    # Llama al selector con los parámetros elegidos
    Selector(tipo, estrategia, limite)

# Ejecuta el menú
if __name__ == "__main__":
    menu()