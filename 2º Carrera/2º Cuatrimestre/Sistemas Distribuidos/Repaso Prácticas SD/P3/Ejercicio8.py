from bottle import post, get, request,response, run
import json
import datetime
import random
from collections import Counter
# Avion={
#     'Matricula': id,
#     'Fecha_hora_llegada': string (dd/mm/aaaa HH:MM)
#     'Pista_llegada': numero (10 o 30)
#     'Fecha_hora_salida': string (dd/mm/aaaa HH:MM)
#     'Pista_salida': numero (10 o 30)
# }

#creamos la base de datos
AeropuertoD = {} #si fuera un diccionario
AeropuertoL = [] # si fuera una lista

#creamos la clase Aeropuerto
class Aeropuerto_:
    def __init__(self, matricula, fecha_hora_llegada,pistallegada, fecha_hora_salida, pistasalida):
        self.matriucla_=matricula
        self.llegada = fecha_hora_llegada.strftime('%Y-%m-%d %H:%M')
        self.pistallegada_ = pistallegada
        self.salida = fecha_hora_salida.strftime('%Y-%m-%d %H:%M')
        self.pistasalida_=pistasalida
    
#creamos una funcion que nos de la pista que menos frecuencia tiene 
def AsignarPista():
    while (pista != 10 or pista != 30):
        pista = random.randint(10,30)    
    return pista
#creamos el registro del aterrizaje
@post('/RegistroAterrizaje')
def RegistrarAterrizaje():
    datos = request.json
    llegada_= datetime.datetime.strptime(datos.get('Fecha_hora_llegada'), '%Y-%m-%d %H:%M').isoformat()
    matricula_ = datos.get('Matricula')
    #comprobamos que el avion tiene registrado un aterrizaje ya --> tiene asignado una fecha de llegada
    for avion in AeropuertoD:
        if avion['Matricula'] == matricula_ and avion['Fecha_hora_llegada'] == llegada_:
            return (f'El avion con matricula {avion} ya tiene un aterrizaje asignado')
    #si no tiene un aterrizaje asignado, se lo asignamos, creamos un array auxiliar para ingresar los datos
    avion_aterrizaje ={
        'Matricula': matricula_,
        'Fecha_hora_llegada': llegada_,
        'Pista_llegada': AsignarPista(),
        'Fecha_hora_salida':None,
        'Pista_salida':None
    }
    AeropuertoD.update(avion_aterrizaje)
    AeropuertoL.append(avion_aterrizaje)
    
    return(f'Aterrizaje del avion {matricula_} creado correctamente')

@post('/RegistrarDespegue/<matricula>')
def RegistrarDespegue(matricula):
    datos = request.json
    salida_ = datetime.datetime.strptime(datos.get('Fecha_hora_salida'), '%Y-%m-%d %H:%M')
    pista = AsignarPista()
    #comprobamos que el avion se encuentra en tierra, es decir, no tiene una fecha_hora de salida
    for avion in AeropuertoD:
        if avion['Matricula'] == matricula and avion['Fecha_hora_salida'] != None:
            return (f'Avion con matricula {matricula} no se encuentra en tierra')
    #creamos un diccionario axuliar para introducir los datos del depegue
    avion_despegue={
        'Matricula':matricula,
        'Fecha_hora_llegada':None,
        'Pista_llegada':None,
        'Fecha_hora_salida':salida_,
        'Pista_salida':pista
    }
    #guardamos en el diccionario los datos
    AeropuertoD.update(avion_despegue)
    AeropuertoL.append(avion_despegue)
    
    return(f'Registro del de despegue del avion {matricula} realizado correctamente')

#obtener el listado de los avuones del aeropuerto
@get('/Aviones')
def AvioneAeropuerto():
    response.headers['Content-Type']='application/json'
    return json.dumps (AeropuertoD,AeropuertoL, indent=2)

    
run (host = 'localhost', port=8080)