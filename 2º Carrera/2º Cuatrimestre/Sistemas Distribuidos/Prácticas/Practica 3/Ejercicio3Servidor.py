# Desarrolleunserviciowebdegestióndehabitacionesdeunhotel.El
# serviciodebeposeerunalistadehabitacionesycadahabitaciónposeerá,
# mínimo,lossiguientesatributos:
# ■ Identicador.
# ■ Númerodeplazas.
# ■ Listadeequipamiento(porejemplo:armario,aireacondicionado,
# cajafuerte,escritorio,etc.).
# ■ Ocupada(sí/no).
# Sedebenimplementarlossiguientesendpoints:
# a)Dardealtaunanuevahabitación.
# b)Modicarlosdatosdeunahabitación.
# c)Consultarlalistacompletadehabitaciones.
# d)Consultarunahabitaciónmedianteidenticador.
# e)Consultarlalistadehabitacionesocupadasodesocupadas.
# QuedaajuiciodelestudianteidenticarquétipodeoperacionesHTTP
# debeimplementarcadaendpoint (PUT,POST oGET).
# Paralosendpointsb),d)ye),esobligatorioelusodeparámetrosenel
# path delaURL.

import datetime
from bottle import get, post, request, response, run,delete
import json
import os #uso de la variable path
import random
import atexit #para guarda los datos al salir
#como vamos a trabajar con JSON que será nuestra BD, vamos a iniciar el servidor
#accediendo a la ruta del json "lista de habitaciones"
PATH = os.path.dirname(os.path.realpath(__file__))

#abrimos el archivo json
with open(PATH + '/InfoHotel.json', 'r') as file:
    BaseDatos = json.load(file) #BaseDatos será nuestra base de datos que contiene los elementos del json
    
#Mensajes de errores de la estructura reserva
MENSAJE_ERROR= BaseDatos["mensaje_error"]
MENSAJE_BORRADO = BaseDatos["mensaje_borrado"]
#Creamos las clases del programa
class Room:
    def __init__ (self,identificador,capacidad, equipamiento, estado):
        self.identificador = identificador
        self.capacidad = capacidad
        self.equipamiento = equipamiento
        self.estado = estado
class Usuario:
    def __init__(self,DNI, nombre, contraseña):
        self.DNI = DNI
        self.nombre = nombre
        self.contraseña = contraseña
class Reserva:
    def __init__(self, idreserva, DNIpersona, habitacion, fechaIni, 
                 fechaFin,mensaje_error, mensaje_borrado):
        self.idreserva = idreserva
        self.DNIpersona = DNIpersona
        self.habitacion = habitacion
        self.fechaIni = fechaIni.strftime('%d/%m/%y')
        self.fechaFin = fechaFin.strftime('%d/%m/%y')


#comprobamos las credenciales del usuario
def CompruebaUser(user,password):
    for i in BaseDatos["usuarios"]:
        if user == i["Nombre"] and password == i["contraseña"]:
            return True
    return False


#añadir una habitacion "POST"
@post('/añadirHabitacion')
def añade_habitacion():
    datos = json.loads(request.json) #guardamos los datos del json
    #comprobamos que son correctos
    if not CompruebaUser(datos.get('user'), datos.get('pass')):
        return json.dumps({"No se ha encontrado el usuario"})

    id = [] #id de la habitacion
    #guardamos las habitaciones en un vector
    for i in BaseDatos["habitaciones"]:
        id.append(i["identificador"])
    
    #vemos si tenemos mas capacidad o no para seguir añadiendo habitaciones
    if len(id) == 100:
        return json.dump({"Hemos alcanzado el maximo de habitaciones"})

    #añadimos un id random para la habitacion nueva
    while True:
        identificador = random.randint(1,101)
        if identificador not in id:
            break
    #procedemos a añadir la habitacion al json
    hab = Room(identificador, datos.get("capacidad"), datos.get("equipamiento"), datos.get("estado"))
    
    #guardamos la habitaciones con sus atributos en la base de datos
    BaseDatos["habitaciones"].append(hab.__dict__)
    return json.dumps({"Habitación añadida correctamente"})

    
#Consultar los datos de una habitacion "GET"
@get('/InformacionHotel/<identificador>')
def InfoHabitacion(identificador):
    datos = json.loads(request.json)
    #comprobamos credenciales
    if not CompruebaUser(datos.get('user'), datos.get('pass')):
        return json.dumps({"No se ha encontrado el usuario"})
    #comprobamos que la sala existe, si existe imprime los datos
    for hab in BaseDatos["habitaciones"]:
        if hab["identificador"]== int(identificador):
            return json.dumps(hab)
    return json.dumps('{}')

#Añadir reserva
@post('/reserva')
def reserva():
    datos = json.loads(request.json)
    #comprobamos credenciales
    if not CompruebaUser(datos.get('user'), datos.get('pass')):
        return json.dumps({"No se ha encontrado el usuario"})

    #creamos un vector para las reservas
    idr=[]
    Inicio = (datetime.datetime.strptime(datos.get('FechaIni'), '%Y-%m-%d'))
    Fin = (datetime.datetime.strptime(datos.get('FechaFin'), '%Y-%m_%d'))
    
    #comprobamos que la habitacion no está ocupada
    for i in BaseDatos["reservas"]:
        if i["habitaciones"] == datos.get('identificador'):
            return json.dumps({"La habitacion elegida ya está reservada"})
        #si está libre, se guarda en el vector
        idr.append(i["idreserva"])
    if len(idr) == 100:
        return json.dumps({"Todas las habitaciones están reservadas"})
    
    #asignamos un numero de reserva random a la reserva
    while True:
        idreserva = random.randint(0,101)
        #se hace hasta que encuentra un numero de reserva que no esté asignado
        if idreserva not in idr:
            break
    #asignamos un DNI "cliente" a la reserva 
    dniC = 0
    #buscamos al usuario en cuestion
    for i in BaseDatos["usuarios"]:
        if datos.get('user') == i["nombre"] and datos.get('pass') == i["contraseña"]:
            dniC = i["DNI"]
    
    booking = Reserva(idreserva, dniC, datos.get('identificador'), datos.get('dia'), Inicio, Fin)
    #guardamos en la base de datos y enviamos en formato JSON
    BaseDatos["reservas"].append(reserva.__dict__)
    return json.dumps({"Reserva completada con éxito"})

#Mostrar reservas de un cliente 
@get('/reservas/<DNIusuario>')
def MostrarReservas(DNIusuario):
    datos = json.loads(request.json)
    #comprobamos credenciales
    if not CompruebaUser(datos.get('user'), datos.get('pass')):
        return json.dumps({"No se ha encontrado el usuario"})

    #creamos un vector de las reservas
    reservas_user = []
    
    #guardamos todas las reservas del usuario con el DNI introducido
    for reservas in BaseDatos["reservas"]:
        if reservas["DNI"] == DNIusuario:
            reservas_user.append(reservas)
    return json.dumps(reservas_user)

#Eliminar reserva
@delete('/EliminarReserva/<idReserva>')
def Eliminar(idReserva):
    datos = json.loads(request.json)
    pos = -1 
    #comprobamos credenciales
    if not CompruebaUser(datos.get('user'), datos.get('pass')):
        return json.dumps({"Usuario no encontrado"})
    #buscamos la reseva que tiene ese idReserva y la eliminamos
    for contador, i in enumerate(BaseDatos["reservas"]):
        if i["idreserva"] == int(idReserva):
            pos = contador
            break
    #comprobamos que la posicion es la de la reserva y la sacamos del vector "pop"
    if pos!= -1:
        BaseDatos["reservas"].pop(pos)
        return json.dumps(MENSAJE_BORRADO)
    else:
    #si no existe la reserva, manda el mensaje de error
        return json.dumps(MENSAJE_ERROR)
    
def Guardar_datos():
    with open (PATH + '/InfoHotel.json', 'w') as file:
        json.dump(BaseDatos,file)
    atexit.register(Guardar_datos)
run(host='127.0.0.1',port=8080)