import socket
import os 
#creamos la direcciom, socket, lo bindeamos
direccion = ('localhost', 8080)
buffer = 1024
serv_udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
serv_udp_sock.bind(direccion)

#vamos a obtener el directorio actual de servidor
directorio = os.gtcwd()


#vamos a crear el menu que realizará las operaciones que nos indique el cliente
data, cliente =serv_udp_sock.recvfrom(buffer)
respuesta = data.decode()
print(f'Comando {respuesta} recibido con exito del cliente')
while True:
    if respuesta == 'ls': #listar los ficheros de un directorio
        archivos = os.listdir(directorio)
        print('\n'.join(archivos))


    elif respuesta.starwith('rm'): #eliminar el fichero
        nombre_fichero = respuesta.split(' ')[1]
        ruta = os.path.join(directorio,nombre_fichero)
        if os.path.exists(ruta): #si existe lo eliminamos
            os.remove(ruta)
            serv_udp_sock.sendto(f'Archivo con nombre {nombre_fichero} eliminado correctamente'.encode(),direccion)

    elif respuesta.startwith('write'):
        #vamos a crear un nuevo fichero que contendrá el nombre que le pasemos
        nombre_fichero = respuesta.split(' ')[1] #en la posicion 1 esta el nombre del fichero
        mensaje = respuesta.split(' ')[2] #en la posicion 2 esta el mensaje del fichero
        ruta = os.path.join(directorio,nombre_fichero)
        #vamos a proceder a escribir en el fichero el mensaje
        with open(ruta, 'w') as archivo:
            archivo.write(mensaje)
            
        serv_udp_sock.sendto(f'Archivo con nombre{nombre_fichero} y mensaje {mensaje} creado correctamente en el directorio {directorio}'.encode(),direccion)
        
    elif respuesta.starwith('cd'):
        #vamos a cambiar de directorio
        nombre_directorio = respuesta.split(' ')[1]
        ruta = os.path.join(directorio,nombre_directorio)
        #vamos a comprobar que existe dicha ruta
        if not os.path.exists(ruta) and not os.path.isdir(ruta):
            serv_udp_sock.sento(f'No existe el directorio {nombre_directorio} en el servidor'.encode(),direccion)
            
        directorio = ruta #cambiamos de ruta si exisre la ruta que hemos metido en el directorio acutal
        
    elif respuesta.startwith('mv'):
        origen_fichero = respuesta.split(' ')[1]
        destino_fichero = respuesta.split(' ')[2]
        ruta_origen = os.path.join(directorio, origen_fichero)
        ruta_destino = os.path.join(directorio, destino_fichero)
        
        #los directorios origen y destino no pueden ser el mismo
        if os.path.exists(ruta_origen) and os.path.exists(ruta_destino) and os.path.isfile(ruta_origen)and os.path.isdir(ruta_destino):
            os.rename(ruta_origen, os.path.join(ruta_destino,origen_fichero))
            serv_udp_sock.sento(f'Archivo con nombre {origen_fichero} movido correctamente al directorio {ruta_destino}'.encode(),direccion)
        else:
            serv_udp_sock.sendto('Error al mover el archivo'.encode(),direccion)
    elif respuesta == 'exit':
        #salimos del programa, cerramos la conexcion
        serv_udp_sock.close()
        break
    else:
        serv_udp_sock.sento('Comando no valido, Introduzca uno nuevo'.encode(),direccion)
        