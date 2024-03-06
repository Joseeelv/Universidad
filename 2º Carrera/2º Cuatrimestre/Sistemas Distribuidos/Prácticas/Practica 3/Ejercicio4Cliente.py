#cliente del ejercicio 4

import requests
import json
URL = 'http://localhost:8080/Miembro'

Persona ={
    'DNI': '1',
    'nombre':'Pedro',
    'email':'pedro@gmail.com',
    'Categoria':'Becario',
    'Departamento':'Ciencias',
    'Asignaturas':['Mates','Quimica']
    }

Persona2 ={
    'DNI': '1',
    'nombre':'Juan',
    'email':'Juan@gmail.com',
    'Categoria':'PAS',
    'Departamento':'Ciencias',
    'Asignaturas':[]
}



#menu
print("Menú ejercicio 4\n","---------------------\n",
          "1. Dar Alta\n","2. Modificar datos usuario\n","3. Consultar datos de un usuario\n",
          "4. Hacer busqueda por DNI\n","5. Obtener lista de miembros de una categoría\n","6. Salir\n","---------------------\n")
while True:
    opc = int(input("Introduzca una opción: "))
    if opc == 1:
        respuesta = requests.post(URL+'/NuevoMiembro', json=Persona)
        print (respuesta.text)
    elif opc == 2:
        #funcion iniciar sesion
        while True:
            dni=input("Introduzca un DNI: ")
            if dni != "":
                break
        URL_PUT = URL+'/ModificarMiembro/'+dni
        respuesta= requests.put(URL_PUT,json=Persona2)
        print (respuesta.text)
    elif opc == 3:
        respuesta = requests.get(URL+'/MiembrosUniversidad', json=Persona)
        print(respuesta.text)
    elif opc == 4:
        while True:
            dni=input("Introduzca un DNI: ")
            if dni != "":
                break
        URL_GET = URL+'/BuscarMiembro/'+dni
        respuesta= requests.get(URL_GET,json=Persona)
        print(respuesta.text)
    elif opc == 5:
        while True:
            cat=input("Introduzca una Categoria: ")
            if cat != "":
                break
        URL_GET = URL+'/MiembroLista/'+cat
        respuesta = requests.get(URL_GET,json=Persona)
        print(respuesta.text)
    elif opc == 6:
        print("Hasta pronto")
        break