import datetime
import requests

URL = 'http://localhost:8080'

#atributos del vuelo aeropuerto
# Avion={
#     'Matricula':'',
#     'FechaS':'',
#     'HoraS':'',
#     'Fechall':'',
#     'Horall':'',
#     'PistaS':'',
#     'Pistall':''    
# }

#creamos el menu
while True:
    print("Menú Aeropuerto\n","--------------------\n",
          '1. Registrar Aterrizaje \n',
          '2. Resgistrar Despegue \n',
          '3. Listado de Aviones del Aeropuerto\n',
          '4. Salir del Programa \n'
          ,"--------------------\n")
    opc = int(input('Introduce una opcion: '))
    if opc !='':
        if opc == 4:
            print('Hasta Pronto')
            break
        elif opc ==1:
            print('Menu Registrar Aterrizaje de un Avion\n',"-----------------")
            idAA =input ('Introduzca la Matricula del Avion: ')
            if idAA !='':
                while True:
                    Fechallegada = input('Introduce la fecha de aterrizaje (dd-mm-aaaa): ')
                    if Fechallegada !='':
                        try:
                            Fechallegada=datetime.datetime.strptime(Fechallegada,'%d-%m-%Y').__str__()
                            break
                        except:
                            print('Formato fecha incorrecto')
                while True:
                    Horall = input('Introduce la Hora de aterrizaje (H:M): ')
                    if Horall !='':
                        try:
                            Horall = datetime.datetime.strptime(Horall,'%H:%M').__str__()
                            break
                        except:
                            print('Formato Hora incorrecto')
                        
            datosAA= {'Matricula':idAA,'Fechall':Fechallegada,'Horall':Horall}
            URL_POST=URL+'/Aterrizaje'
            respuesta = requests.post(URL_POST,json=datosAA)
            print(respuesta.text)

        elif opc == 2:
            print('Menu Registrar Despegue de un Avion\n',"-----------------")
            idAD = input("Introduzca la Matricula del Avion: ")
            if idAD != '':
                while True:
                    Fechasalida = input("Introduce la fecha de despegue (dd-mm-aaaa): ")
                    if Fechasalida !='':
                        try:
                            Fechasalida = datetime.datetime.strptime(Fechasalida,'%d-%m-%Y').__str__()
                            break
                        except:
                            print("Formato de Fecha Despegue incorrecto")
                while True:
                    horasalida = input("Introduzca la hora del despegue(HH:MM): ")
                    if horasalida!='':
                        try:
                            horasalida= datetime.datetime.strptime(horasalida, '%H:%M').__str__()
                            break
                        except:
                            print("Formato Hora Despegue incorrecto")
            
            datosAD = {'Matricula': idAD, 'FechaS':Fechasalida,'HoraS':horasalida}
            URL_POST = URL+'/Despegue'
            respuesta = requests.post(URL_POST,json=datosAD)
            print(respuesta.text)
            
        elif opc == 3:
            print('Menu Listar Aviones\n',"-----------------")
            URL_GET=URL+'/ListaAviones'
            respuesta = requests.get(URL_GET)
            print(respuesta.text)