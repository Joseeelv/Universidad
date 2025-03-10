from bottle import post, get, put, run,request,response
import json
import random
#bases de datos del sistema
vehiculos =[]
clientes = []
#clases de vehiculo y usuario
class Vehiculo:
    def __init__(self, idvehiculo,marca,modelo,estado,usuario_Alquiler):
        self.idvehiculo=idvehiculo
        self.marca = marca
        self.modelo = modelo
        self.estado = estado
        self.usuario_A = usuario_Alquiler
        
class Clientes:
    def __init__(self,iduser,veces_Alquilado):
        self.iduser =iduser
        self.veces = veces_Alquilado
        
#clase que nos comprueba el id del cliente
def CompruebaIDC(clientes,id):
    for cliente in clientes:
        if cliente['IDuser']==id:
            return True
    return False

#clase que nos comprueba el id del vehiculo
def CompruebaIDV(vehiculos,idv):
    for vehiculo in vehiculos:
        if vehiculo['IDvehivulo']==idv:
            return True
    return False


@post('/NuevoUsuario/<id>')
def NuevoUser(id):
    #comprobamos que el id del cliente no está registrado
    if CompruebaIDC(clientes,id):
        return json.dumps("Ya hay un cliente con ese ID")
    
    #creamos la variable que nos almacenará los datos nuevos de los clientes
    clienteN={
        'IDuser':id,
        'Veces_alquilado':0
    }
    #guardamos en la lista los clientes nuevos
    clientes.append(clienteN)
    
    response.headers['Content-Type']='application/json'
    return json.dumps(clientes, indent=2)    

@post('/NuevoVehiculo/<idv>')
def NuevoVehiculo(idv):
    datos = request.json
    #comprobamos que no tiene el mismo id
    if CompruebaIDV(vehiculos,idv):
        return json.dumps("ID vehiculo ya esta registrado")
    #creamos una lista aux para guardar los datos
    marca = datos.get('Marca')
    modelo =datos.get('Modelo')
    vehiculoN ={
        'IDvehivulo':idv,
        'Marca':marca,
        'Modelo': modelo,
        'Estado_alquiler':'Libre',
        'Usuario_alquiler':''
    }
    #comprobamos que el id del vehiculo no está registrado
    vehiculos.append(vehiculoN)
    response.headers['Content-Type']='application/json'
    return json.dumps(vehiculos, indent=2)

@put('/AlquilerVehiculo/<idA>')
def AlquilarVehiculo(idA):
    #comprobamos que el usuario está registrado
    datos = request.json
    if not CompruebaIDC(clientes,idA):
        return json.dumps("No existe ningun cliente con ese ID")
    #Mostramos los ID, Marca y modelo de los coches libres
    #buscamos un vehiculo libre
    for vehiculo in vehiculos:
        if vehiculo['Estado_alquiler']=='Ocupado':
            return json.dumps("No se puede alquilar un coche que esta ocupado")
        #asignamos al cliente del id este vehiculo "modificamos datos del vehiculo"
        vehiculo['Estado_alquiler']='Ocupado'
        vehiculo['Usuario_alquiler']=idA
        #modificamos los valores del cliente
        n_alquileres= datos.get('Veces_alquilado')
        n_alquileres=+1
        for cliente in clientes:
            if cliente['IDuser']==idA:
                cliente['Veces_alquilado'] = n_alquileres
            
    response.headers['Content-Type']='application/json'
    return json.dumps("Vehiculo alquilado correctamente")

@put('/AlquilerVehiculo/<idV>/<idC>')
def AlquilarVehiculoEspecifico(idV,idC):
    #comprobamos que el cliente existe
    if not CompruebaIDC(clientes,idC):
        return json.dumps("No existe el ID del Cliente")
      #comprobamos que el vehiculo está registrado
    if not CompruebaIDV(vehiculos,idV):
        return json.dumps("No existe el ID del Vehiculo ")
    datos = request.json
    #comprobamos que el vehiculo está libre
    for vehiculo in vehiculos:
        if vehiculo['IDvehivulo']==idV:
            if vehiculo['Estado_alquiler']=='Ocupado':
                return json.dumps("No se puede alquilar un coche ocupado")
            #modificamos los valores del coche "alquilamos"
            vehiculo['Estado_alquiler']='Ocupado'
            vehiculo['Usuario_alquiler']=idC
            #modificamos los valores del cliente
            n_alquileres= datos.get('Veces_alquilado')
            n_alquileres=+1
            for cliente in clientes:
                if cliente['IDuser']==idC:
                    cliente['Veces_alquilado'] = n_alquileres
                    
    response.headers['Content-Type']='application/json'
    return json.dumps("Vehiculo alquilado correctamente")

run (host='127.0.0.1', port=8080)