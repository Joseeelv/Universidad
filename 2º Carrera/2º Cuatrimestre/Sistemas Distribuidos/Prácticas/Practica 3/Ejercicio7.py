from bottle import post, delete, run,request,response,get
import json
import random



#creamos la BD de pistas paddle
reserva_pistas=[]

#creamos la clase

class Paddle:
    def __init__(self, idreserva, pista,HoraIni,HoraFin):
        self.idreserva = idreserva
        self.pista = pista
        self.HoraIni=HoraIni
        self.HoraFin=HoraFin
        
#creamos una funcion que nos genere un idreserva random
def generarID():
    return ''.join(random.choices('abcdefghijklmnopqrstuvwxyzABCDEFGHYJKLMNOPQRSTUVWXYZ0123456789',k=10))

# /reservar:deberápermitirañadirunanuevareservaparaunapista concreta. 
# Si la reserva es correcta, el sistema generará un identi cador aleatorio que devolverá al usuario. 
# En caso contrario, se deberá cancelar el proceso 
# e informar al usuario si la pista ya está reservada para esa franja horaria.
@post('/reservar')
def ReservarPista():
    #creamos el codigo de reserva
    idR = generarID()
    datos = request.json
    num_pista = datos.get('numero')
    nombre = datos.get('Nombre')
    HoraIni=datos.get('HoraInicio')
    HoraFIN=datos.get('HoraFin')
    
    #comprobamos si está reservada la pista en la franja horaria
    for pista in reserva_pistas:
        if pista['Numero'] == num_pista and (pista['HoraInicio']< HoraFIN and pista['HoraFin']>HoraIni):
            return json.dumps("No se puede se puede reservar esa pista, ya que tiene un numero de reserva para esa franja horaria")
    
    #comprobamos que no hay ninguna reserva en la pista en ese tramo horario
    reservapista={
        'IDreserva':idR,
        'Numero':num_pista,
        'HoraInicio':HoraIni,
        'HoraFin':HoraFIN,
        'Nombre':nombre
    }
    #almacenamos la reserva
    reserva_pistas.append(reservapista)
    response.headers['Content-Type']='application/json'
    return json.dumps(reserva_pistas,indent=2)
# /cancelar:dadounidenti cadordereserva,seeliminarálareserva asociada al identi cador, 
# quedando la pista liberada para esa franja horaria. 
# En caso de que no exista ninguna reserva para ese identi cador, 
# deberá informarse al usuario del error.
@delete('/cancelar/<Idreserva>')
def CancelarReserva(Idreserva):
    pos = -1 #posicion del vector de las reservas
    #comprobamos que en esa franja horaria no exista un identificador de reserva
    for contador, pistas in enumerate(reserva_pistas):
        if pistas["IDreserva"]!=Idreserva:
            return json.dumps("No hay ninguna reserva en esa franja horaria")
        #si hay reserva, guardamos la posicion del que tiene la misma IDreserva
        pos = contador
    #comprobamos que la posicion existe
    if pos !=-1:
        #eliminamos del vector la posicion que contenga esa IDreserva
        reserva_pistas.pop(pos)
        return json.dumps("Reserva eliminada correctamente",indent=2)
    else:
        return json.dumps("No existe la reserva")
    
# /mostrar: dado un número de pista, el sistema deberá mostrar en qué franjas horarias la pista está ocupada y por quién.
# El formato del JSON de retorno queda a juicio del alumno, 
# pero deberá ser su ciente para que un cliente pudiese parsearlo para mostrar un listado con un aspecto similar al siguiente:
@get('/mostrar/<IDpista>')
def MostrarPista(IDpista):
    #comprobamos que el IDpista es correcto
    reservas_pistas=[]
    for pistas in reserva_pistas:
        if pistas['Numero'] != IDpista:
            return json.dumps("No hay ninguna pista con ese ID")
        inicio = pistas['HoraInicio']
        fin = pistas['HoraFin']
        nombre = pistas['Nombre']
        
        reservas_pistas.append({
            'HoraInicio': inicio,
            'HoraFin':fin,
            'Nombre': nombre,
            'Numero_Pista':IDpista
            })

    return json.dumps(reservas_pistas, indent=2)

if __name__ == '__main__':
    run(host='localhost', port=8080)