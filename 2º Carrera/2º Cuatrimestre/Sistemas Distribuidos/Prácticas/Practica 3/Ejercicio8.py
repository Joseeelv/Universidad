from bottle import get, post,put, response,request,run
import json
import datetime
import random

#diccioanario de Aeropuerto
aeropuerto = []

#creamos la clase aeropuerto
class Aeropuerto:
    def __init__(self,matricula,FechaLL,FechaS,pista_ll, pista_s):
        self.matricula_=matricula
        self.Fechall_=FechaLL.strftime('%Y-%m-%d %H:%M')
        self.FechaS_=FechaS.strftime('%Y-%m-%d %H:%M')
        self.Pistall_=pista_ll
        self.PistaS_=pista_s
        
#creamos una funcion que nos asigna una pista aleatoria
def AsignarPista():
    return random.randint(10,30)
@post('/Aterrizaje')
def RegistrarAterrizaje():
    #asignamos una pista
    num_pista = AsignarPista()
    avionll=[]
    datos = request.json
    idA = datos.get('Matricula')
    Fechall_ = datetime.datetime.strptime(datos.get('Fechall'), '%Y-%m-%d %H:%M:%S').isoformat()
    Horall_ = datetime.datetime.strptime(datos.get('Horall'),'%Y-%m-%d %H:%M:%S').isoformat()
    #comprobamos que el id del avion no está registrado
    for avion in aeropuerto:
        if avion['Matricula_Avion'] == idA:
            if avion['Pista_Aterrizaje']=='':
                return json.dumps('Avion ya registrado. Registro Fallido')
    avionll={
        'Matricula_Avion':idA,
        'Fecha_Aterrizaje':Fechall_,
        'Hora_Aterrizaje':Horall_,
        'Pista_Aterrizaje':num_pista,
        'Fecha_Despegue':None,
        'Hora_Despegue':None,
        'Pista_Despegue':None
    }
    aeropuerto.append(avionll)
    response.headers['Content-Type']='application/json'
    return json.dumps('Registro completado con exito')
    
@post('/Despegue')
def RegistrarDespegue():
    datos = request.json
    num_pista = AsignarPista()
    idA = datos.get('Matricula')
    FechaS_ = datetime.datetime.strptime(datos.get('FechaS'),'%Y-%m-%d %H:%M:%S').isoformat()
    HoraS_ = datetime.datetime.strptime(datos.get('HoraS'),'%Y-%m-%d %H:%M:%S').isoformat()
    
    #comprobamos que el avion está en tierra --> No tiene fecha de despegue ni de aterrizaje
    for avion in aeropuerto:
        if avion['Matricula_Avion']==idA:
            if avion['Fecha_Aterrizaje'] >=FechaS_: #si esta volando tiene fecha aterrizaje
                if avion['Hora_Aterrizaje'] >= HoraS_: #por ende tiene hora de aterrizaje
                    return json.dumps('El Avion esta volando, ya que tiene Fecha-Hora de aterrizaje')
   
        avionD ={
            'Matricula_Avion':idA,
            'Fecha_Aterrizaje':None,
            'Hora_Aterrizaje':None,
            'Pista_Aterrizaje':None,
            'Fecha_Despegue':FechaS_,
            'Hora_Despegue':HoraS_,
            'Pista_Despegue':num_pista
        }
    aeropuerto.append(avionD)
    response.headers['Content-Type']='application/json'
    return json.dumps('Despegue registrado con exito')

@get('/ListaAviones')
def ListarAvionesAeropuerto():
    response.headers['Content-Type']='application/json'
    return json.dumps(aeropuerto,indent=2)

run (host='localhost', port=8080)