# Escriba el código correspondiente a un endpoint de tipo POST con el framework Bottle en Python.
# El nombre del endpoint será /inserta. 
# Como entrada tomará un JSON, en el que se encontrará un número entero cuya clave será elemento. 
# El servidor buscará el número indicado en el JSON de entrada en un array denominado mis_elementos,
# si el elemento no existe en el array lo insertará en la última posición,
# en caso contrario, no modificará el array.
# Por último, devolverá al cliente, también en formato JSON, el array resultante con la clave mis_elementos. 
# Si la clave elemento no se encuentra en el JSON de entrada, el servicio deberá devolver un error al cliente.

from bottle import run, post, response,request, get, HTTPResponse
import json

#creamos el vector vacio de mis_elementos
mis_elementos= []
@post('/inserta')
def inserta_elemento():
    #obtenemos los elementos del json
    datos = request.json
    elemento = datos.get('elemento')
    try:
        #Comprobamos que el hay elementos
        if elemento is None:
            raise ValueError("El JSON no contiene ningun elemento para añadir al vector {{mis_elementos}}")
        else:
            #comprobamos que el vector tiene el elemento
            if elemento in mis_elementos:
                return "Elemento ya en el vector {{mis_elementos}}"
            else:
                mis_elementos.append(elemento)
            response_datos = {'mis_elementos': mis_elementos}
            #devolvemos el array en formato JSON
            return json.dumps(response_datos)
    
    except ValueError as e:
        response = HTTPResponse(status=400,body=str(e))
        return response
        

if __name__ == '__main__':
    run(host='localhost', port=8000, debug = True)