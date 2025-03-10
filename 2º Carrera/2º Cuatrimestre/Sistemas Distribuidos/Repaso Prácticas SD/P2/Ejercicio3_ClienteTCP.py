import socket
import os

#creamos el socket, direccion
clientetcp = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
direccion = ('localhost',8080)
buffer = 1024
#nos conectamos al servidor
clientetcp.connect(direccion)

nombre = input('Introduce el nombre del archivo a enviar al servidor: ')
archivo = os.path.basename(nombre)
#enviamos el archivo al servidor
clientetcp.send(archivo.encode())

with open(archivo,'r') as fichero:
    for datos in fichero:
        clientetcp.send(datos.encode())
print('Archivo enviado')

#esperamos la respuesta del servidor (archivo recibido + tamaño)
respuesta = clientetcp.recv(buffer).decode()
print(respuesta)

