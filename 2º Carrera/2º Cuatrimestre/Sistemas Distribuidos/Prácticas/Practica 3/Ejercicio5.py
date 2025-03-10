from bottle import request, put, get, post, response
import json

#creamos la Base de Datos vacía
Usuarios ={} #es un diccionario
#si nos pidieran un array --> Usuarios = []

#creamos la clase 
class User:
    def __init__(self,user,contraseña,email,estado,nombre_completo):
        self.User=user
        self.Contraseña = contraseña
        self.Email = email
        self.Estado=estado
        self.NombreCompleto = nombre_completo

#Registrar usuario
@post('/RegistrarUsuario')
def RegistrarUsuario():
    #comprobamos que el Usuario y el Email no están registrados
    datos = request.json
    user = datos.get('Usuario')
    email = datos.get('Email')
    
    if user or email in Usuarios:
        #si nos pide una cadena
        return (f'Ya hay un Usuario {user} o un Email {email} registrados en el sistema')
        #si nos pide un json:
        # response.headers['Content-Type']='application/json'
        # return json.dumps(f'Ya hay un Usuario {user} o un Email {email} registrados en el sistema)
    else:
        password = datos.get('Contraseña') #no cifrada
        #si queremos cifrarla, hacemos una funcion aparte para que nos la cifre "bcrypt"
        Nombrecompleto = datos.get('Nombre_apellidos')
        
        #creamos un usuario auxiliar para introducir los nuevos datos en el diccionario
        usuario_nuevo ={
            'Usuario':user,
            'Contraseña': password,
            'Email':email,
            'Estado': False,
            'Nombre_apellidos':Nombrecompleto
            }
        #guardamos en Usuario el nuevo usuario y mandamos el mensaje de verificacion
        Usuarios.update(usuario_nuevo)
        #si nuestra base de datos fuera una lista/array:
        #Usuarios.append(usuario_nuevo)

        return (f'Usuario{usuario_nuevo["Usuario"]}, Introducido correctamente en la Base de Datos')
        #si nos pide que le devolvamos el diccionario:
        # response.headers['Content-Type']='application/json'
        # return json.dumps(Usuarios,indent=2)

@put('/ActivarCuenta/<parametro>')
def ActivarCuenta(parametro):
    #comprobamos que el parámetro se corresponde al usuario o email
    for user in Usuarios:
        if user['Usuario'] == parametro or user['Email']==parametro:
            #puede que exista el usuario y el email pero ya esté activado, lo comprobamos:
            if user['Estado'] == False:
                user['Estado'] = True
    return ('Usuario o Email no existen en la Base de Datos')

@get('/BuscarUsuario/<cadena>')
def BuscarUsuario(cadena):
    #buscamos los usuarios que tengan esa cadena en el Usuario o Email
    Usuarios_encontrados=[]
    for user in Usuarios:
        if cadena.lower() in user['Usuario'].lower() or cadena.lower() in user['Email'].lower():
            Usuarios_encontrados.append(user)
            
    #devolvemos los usuarios que han sido encontrados
    response.headers['Content-Type']='application/json'
    return json.dumps(Usuarios_encontrados,indent=2)
