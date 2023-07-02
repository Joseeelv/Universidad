from bottle import request, response, post, delete, get
import json
import random

#creamos la base de datos
#Si nos pide un diccionario:
#reservas ={}

#con una lista
reservas =[]

#creamos la clase
class Reserva:
    def __initi__(self,idreserva,num_pista,HoraIni,HoraFin,jugador):
        self.Idreserva = idreserva
        self.numpista= num_pista
        self.Inicio = HoraIni
        self.Fin = HoraFin
        self.jugador_=jugador
    
#creamos una clase la cual nos generará un id aleatorio para la reserva
def GenerarId():
    return ''.join(random.choices('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890',k=10))
#reservar pista
@post('/Reservar')
def Reservarpista():
    #comprobamos que la pista no esté reservada en esa franja horaria.
    datos = request.json
    Inicio = datos.get('HoraInicio')
    Fin = datos.get('HoraFin')
    for reserva in reservas:
        if reserva['HoraInicio'] <= Fin and reserva['HoraFin'] >=Inicio:
            if reserva['Pista'] in reservas:
                return (f'La pista ya está reservada para la hora {Inicio - Fin}')
            
    #si no está reservado generamos un id aleatorio
    Idreserva = GenerarId()
    
    #creamos un array para almacenar las nuevas reservas
    nueva_reserva={
        'Idreserva':Idreserva,
        'Numero_pista':datos.get('Pista'),
        'HoraInicio':Inicio,
        'HoraFIn':Fin,
        'Jugador_reserva':datos.get('Jugador')
    }
    #guardamos la nueva reserva
    #si fuera un diccionario usamos update --> reservas.update(nueva_reserva)
    #como tenemos un array:
    reserva.append(nueva_reserva)
    
    #enviamos un mensaje de confirmacion con el id de la reserva
    return (f'Reserva realizada con exito.\nNumero de la reserva: {Idreserva}')

#Cancelar la reserva
@delete('/EliminarReserva/<Idreserva')
def CancelarReserva(ID):
    #buscamos la reserva para eliminarla a traves de su idreserva
    pos = -1
    for contador, reserva in enumerate(reservas):
        if reserva['Idreserva']!=ID:
            #seguimos buscando la reserva
            pos = contador 
    if pos != -1: #hemos encontrado el idreserva
        #eliminamos la posicion de la lista
       reservas.pop(pos)
       return (f'Se ha eliminado la reserva {ID} correctamente')       
    else:
        return(f'No existe la reserva con ID {ID}')
    
         
#Mostrar las reservas
@get('/Mostrar')
def Mostrar_reservas(Numpista):
    #comprobamos que la pista debe de estar ocupada --> Tiene un nombre de Jugador_reserva
    pistas_reservadas=[]
    for reserva in reservas:
        if reserva['Pista']!=Numpista:
            return(f'No hay ninguna reserva de esa pista')
        inicio = reserva['HoraInicio']
        fin = reserva['HoraFin']
        jugador = reserva['Jugador_reserva']
        
        #guardamos todos los datos que se corresponde a la reserva de la pista
        
        pistas_reservadas={
            inicio ,'a', fin,': reservada por', jugador
        }
            
    return (f'Estado de la pista numero{Numpista}{pistas_reservadas}')
            
        
    
    