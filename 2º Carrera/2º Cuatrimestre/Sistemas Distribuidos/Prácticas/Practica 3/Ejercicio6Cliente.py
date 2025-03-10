#cliente ejercicio 6
import requests
import json
URL = 'http://127.0.0.1:8080'
#parametros de vehiculo y usuario 
vehiculo={
    "IDvehiculo":'',
    "Marca":'',
    "Modelo":'',
    "Estado_alquiler":'',#libre / ocupado
    "Usuario_alquiler":''
}
usuario={
    "IDuser":'',
    "Veces_alquilado":''
}
#creamos el menu
while True:
    print("Menú Alquileres",
          "\n-----------------\n",
          "1. Registrar Usuario\n",
          "2. Registrar Vehiculo\n",
          "3. Alquilar vechículo libre\n",
          "4. Alquilar vehiculo especifico\n",
          "5. Salir del programa",
          "\n-----------------")
    opc = int(input("Introduce una opcion: "))
    
    #salimos del programa
    if opc == 5:
        print("Hasta pronto")
        break
    
    #añadir un nuevo usuario
    if opc == 1:
        print("Menú Registrar Nuevo Usuario")
        id = int(input("Introduce ID del nuevo usuario: "))
        if id != "":
            URL_POST = URL+'/NuevoUsuario/'+str(id)
            respuesta= requests.post(URL_POST,json=usuario)
            print(respuesta.text)
        
    elif opc==2:
        print("Menú Registrar Nuevo Vehículo ")
        id=int(input("Introduce el ID del vehículo: "))
        if id != "":
            marca=input("Introduce la marca del vechículo: ")
            if marca !="":
             modelo=input("Introduce el modelo del vehículo: ")
             if modelo !="":
                 data ={'IDvehiculo':id,'Marca':marca,'Modelo':modelo}
                 URL_POST = URL+'/NuevoVehiculo/'+str(id)
                 respuesta=requests.post(URL_POST, json=data)
                 print(respuesta.text)
    elif opc == 3:
        print("Menú Alquilar Vehículo libre")
        idU=int(input("Introduce el id de un Usuario para alquilar un vehículo: "))
        URL_PUT = URL+'/AlquilerVehiculo/'+str(id)
        respuesta=requests.put(URL_PUT,json=vehiculo)
        print(respuesta.text)
    elif opc == 4:
        print("Menú Alquilar Vehículo Específico")
        idU=int(input("Introduce el ID del cliente: "))
        if idU!='':
            idV=int(input("Introduce el ID del vehiculo: "))
            if idV !='':
                URL_PUT = URL+'/AlquilerVehiculo/'+str(idV)+'/'+str(idU)
                respuesta = requests.put(URL_PUT, json=vehiculo)
                print(respuesta.text)
                        
        