#Ejercicio 4 de la practica 3 de Bottle

from bottle import put, post, get, request, response,run,HTTPResponse
import json
import random

#creamos la clase del miembro de la UCA
Personal = [] #lista del personal de la UCA

class Persona:
    def __init__(self,dni,nombre,email,dept,categoria,asig):
        self.dni_=dni
        self.nombre_n=nombre
        self.email_=email
        self.dept_=dept
        self.categoria_=categoria
        self.asignatura_=asig        
    
#Dar alta a un nuevo miembro
@post ('/Miembro/NuevoMiembro')
def Añadirmiembro():
    datos = request.json
    Dni=datos.get('DNI')
    #comprobamos que haya un miembro con ese DNI
    for miembro in Personal:
        if miembro['DNI']==Dni:
            return json.dumps('Ya existe un miembro con ese DNI')
    #verificamos la categoria del miembro
    categoria = datos["Categoria"]
    if categoria not in ['PAS','PDI','Becario']:
        return json.dumps('Categoria erronea')
    #introducimos asignaturas si es PDI
    if categoria != 'PDI':
        asignaturas = [] #lista de asignaturas
    else:
        if 'Asignaturas' not in datos:
            return json.dumps('No hay asignaturas asignadas al Nuevo Miembro')
        asignaturas = datos.get("Asignaturas")    
    #Agregamos el nuevo miembro a la lista del personal
    Personal.append({
        'DNI': datos["DNI"],
        'Nombre':datos['nombre'],
        'Email':datos['email'],
        'Departamento':datos['Departamento'],
        'Categoria':categoria,
        'Asignaturas':asignaturas
    })
    response.headers['Content-Type']='application/json'
    return json.dumps(Personal,indent=2)

@put('/Miembro/ModificarMiembro/<DNI>')
def ModificarMiembro(DNI):
    #comprobamos que existe el DNI del usuario para modificarlo
    datos = request.json
    dni=datos.get('DNI')
    for miembro in Personal:
        if miembro['DNI']!=dni:
            return json.dumps("No hay un Miembro con este DNI")
        break            

    #guardamos todos los datos
    nombre = datos.get('Nombre')
    dept = datos.get('departamento')
    categoria = datos.get('categoria')
    asignaturas = datos.get('asignaturas')
    
    #actualizamos los datos del miembro
    for miembro in Personal:
        if miembro["DNI"]==dni:
            miembro['Nombre']==nombre
            miembro['Departamento']==dept
            miembro['Categoria']==categoria
            miembro['Asignaturas']==asignaturas
    response.headers['Content-Type']='application/json'
    return json.dumps("Miembro modificado correctamente", indent=2)
@get('/Miembro/MiembrosUniversidad')
def Consulta():
    response.headers['Conten-Type'] = 'application/json'
    return json.dumps(Personal,indent=2)

@get('/Miembro/BuscarMiembro/<DNI>')
def BuscarMiembro(DNI):
    #comprobamos que el DNI existe
    miembro_encontrado = ''
    for miembro in Personal:
        if miembro['DNI']!=DNI:
            return json.dumps("No existe ningun Miembro con ese DNI")

    miembro_encontrado = miembro
    response.headers['Content-Type']='application/json'
    return json.dumps(miembro_encontrado, indent=2)

@get('/Miembro/MiembroLista/<Categoria>')
def ListaMiembrosCategoria(Categoria):
    #comprobamos que la categoría existe
    if Categoria not in ['PAS','PDI','Becario']:
        return json.dumps('Categoría Incorrecta')
    miembros_cat =''
    for miembro in Personal:
        if miembro['Categoria'] != Categoria:
            return json.dumps("No hay ningun miembro en esa categoria")
        #si existe la categoria guardamos los miembros
        miembros_cat = miembro
        response.headers['Content-Type']='application/json'
        return json.dumps(miembros_cat,indent=2)

    
run(host='127.0.0.1', port=8080)
    
    
    