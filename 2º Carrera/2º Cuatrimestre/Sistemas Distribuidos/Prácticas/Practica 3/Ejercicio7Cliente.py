#cliente ejercicio 7
import requests
import datetime
URL = 'http://localhost:8080'

#atributos de las clases
pistas={
    "IDreserva":'',
    "Numero":'',
    "HoraInicio":'',
    "HoraFin":'',
    "Nombre":''
}
while True:
    print("Menú PADDLE",
        "\n-----------------\n",
        "1. Reservar Pista\n",
        "2. Cancelar Reserva\n",
        "3. Mostrar Datos Pista\n",
        "4. Salir del programa",
        "\n-----------------")
    opc = int(input("Introduce una opcion: "))
    
    if opc == 4:
        print("Hasta pronto")
        break
    
    elif opc==1:
        print("Menú Reservar Pista","\n-----------------\n")
        while True:
            numeropista=int(input("Introduce el numero de la pista a reservar: "))
            nombre = input("Introduce el nombre de la persona que reserva: ")
            if numeropista !='' and nombre!='':
                break
        while True:
            HoraI= int(input("Introduce la Hora Inicio (HH): "))
            if HoraI =='' or HoraI < 9 or HoraI > 22:
                print("Hora introducida Incorrecta, Formato -> H")
            else:
                break
        while True:
            HoraF =int(input("Introduce la Hora Fin (HH): "))
            if HoraF =='' or HoraF  < 9 or HoraF > 22 or HoraI > HoraF:
                print("Hora introducida Incorrecta")
            else:
                break
        datos ={'numero':numeropista, 'HoraInicio':HoraI, 'HoraFin':HoraF, 'Nombre':nombre}
        URL_POST = URL+'/reservar'
        respuesta = requests.post(URL_POST,json=datos)
        print(respuesta.text)
    
    elif opc==2:
        print("Menú Cancelar reserva","\n-----------------\n")
        
        while True:
            idP = input("Introduzca el ID de la reserva: ")
            if idP !='':
                break
        URL_DELETE = URL+'/cancelar/'+idP 
        respuesta = requests.delete(URL_DELETE,json=pistas)
        print(respuesta.text)
    
    elif opc == 3:
        print("Menú Mostrar Datos Pista","\n-----------------\n")
        while True:
            idpista= input("Introduce el Numero de la pista: ")
            if idpista !='':
                break
        URL_GET = URL+'/mostrar/'+idpista
        respuesta = requests.get(URL_GET,json=pistas)
        print(respuesta.text)
                