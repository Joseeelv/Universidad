#Pograma cliente perteneciente al servidor

import json
import requests
import datetime 
#creamos la URL para acceder al servidor
HOST = "127.0.0.1"
PUERTO = 8080
URL = "http://" + HOST + ":" + PUERTO

#imprimimos un mensaje de bienvenida
print("Bienvenido de nuevo")

#Funcion para logearse
while True:
    user = input("Introduzca un nombre de ususario:")
    password = input("Introduzca una contraseña:")
    if user != "" and password != "":
        break

#Funcion menu para elegir que opcion realizar
while True:
    print("Elige una opcion")
    print("\n 1. Dar de alta una habitación\n2. Consultar los datos de una habitacion\n3. Reservar una habitacion\n4.Mostrar tus reservas\n5. Eliminar Reserva\n6.Salir del programa")
    opc = input(int("Seleccione una de estas opciones: "))
    
    #hacemos un "switch"
    if opc == 1: #alta habitacion
        print("Menú Dar de Alta una Habitacion")
        #creamos un vector para guardar el equipamiento de la habitacion
        equipamiento = []
        #introducimos capacidad
        while True:
            capacidad_hab = input("Introduzca la capacidad de la habitacion: ")
            if capacidad_hab is not None or capacidad_hab != 0:
                try:
                    capacidad_hab = int(capacidad_hab)
                    break
                except:
                    print("La capacidad de la habitacion tiene que ser como mínimo 1")
        #introducimos lista de equipamiento
        while True:
            print("Introduce el equipamiento que quieres que tenga la habitacion")
            equip = input("Cuando no quieras introducir más equipamiento indique FIN: ")
            if equip == "":
                print("La habitacion no puede estar vacía")
            elif equip != "FIN" or equip != "fin":
                equipamiento.append(equip)
                estado = "ocupado"
            else:
                break
        datos = json.dumps({"user":user,"pass":password,"capacidad":capacidad_hab, "equipamiento":equipamiento, "estado":estado})
        response = requests.get(URL+'/añadirHabitacion', json=datos)  

    elif opc == 2: #Consultar datos habitacion
        print("Menú Consultar Atributos Habitación")
        ID = input("Introduzca el Id de la habitacion a modificar: ")
        response = requests.get(URL+'//InformacionHotel/'+ ID, json=json.dumps(user,password))
        
        try:
            hab = json.loads(response.text)
            print("ID de la habitacion: " +str(hab["identificador"])+
                  "\nCapacidad de la habitacion: "+str(hab["capacidad"])+
                  "\nEquipamiento de la habitacion: "+str(hab["equipamiento"])+
                  "\nEstado de la habitacion: "+str(hab["estado"]+"\n"))
        except:
            print("La habitacion no existe")
                                
    elif opc == 3: #Reservar una habitacion
        print("Menú Reservar Habitacion")
        while True:
            #mostramos las habitaciones que no están ocupadas
            hab_reservar = input(int("Introduzca el id de la habitacion a reservar"))
            if hab_reservar == "":
                print ("Introduce un id de habitacion")
        #comprobamos que la habitacion está disponible para ser reservada  
            else:
                if hab_reservar["estado"] != "ocupado" or hab_reservar["estado"] != "Ocupado":
                    break
                else:
                    print("No se puede reservar una habitacion ya ocupada")
        #introducimos la fecha de la reserva
        while True:
            fechaI = input("Introduce la fecha de inicio de la reserva (dd/mm/aaaa): ")
            if fechaI != "":
                try:
                    fechaI = datetime.datetime.strptime(fechaI, '%d/%m/%Y').__str__()
                    break
                except:
                    print("Formato de fecha introducido mal")
            
            fechaF = input("Introduce la fecha de fin de la reserva (dd/mm/aaaa): ")
            if fechaF != "":
                try:
                    fechaF = datetime.datetime.strptime(fechaF, '%d/%m/%Y').__str__()
                    break
                except:
                    print("Formato de fecha introducido mal")
            estado = "ocupado"
        datos = json.dumps({"usuer":user,"contraseña":password,"identificador":hab_reservar,"FechaIni":fechaI,"FechaFin":fechaF,"estado":estado})
        response = requests.post(url=URL+"/reserva",json=datos)
    
    elif opc ==4: #Mostrar reservas de un usuario
        print("Mwnú Ver Datos Reservas Usuario")
        DNI = input("Introduce el DNI del usuario")
        response = requests.get(URL+"//reservas/"+DNI, json=json.dumps({"user":user, "pass":password}))
        
        try:
            reservas = json.load(response.text)
            if len(reservas) != 0:
                for reserva in reserva:
                    print("Id de la reserva: "+str(reserva["idreserva"])+
                          "\nDNI de la persona: "+str(reserva["DNIpersona"])+
                          "\nHabitacion reservada: "+str(reserva["habitacion"])+
                          "\nFecha de Inicio reserva: "+str(reserva["FechaIni"])+
                          "\nFecha finalizacion reserva: "+str(reserva["FechaFin"]+"\n"))
            else:
                print("No tienes reservas")
        except:
            print("Este usuario no tiene ninguna reserva")
            
    elif opc == 5: #Eliminar Reserva
        print("Menú Eliminar Reserva")
        while True:
            reserva = input(int("Introduce el id de la reserva a eliminar: "))
            if reserva == "":
                print("Introduce un id de reserva por favor")
            else:
                break
        response = requests.delete(URL+"/EliminarReserva/"+str(reserva), json=json.dumps(user,password))
    
    elif opc == 6: #salir del programa
        print("Hasta pronto")
        break
    
    else:
        print("Introduce una opcion del menú porfavor..")
        
        
            