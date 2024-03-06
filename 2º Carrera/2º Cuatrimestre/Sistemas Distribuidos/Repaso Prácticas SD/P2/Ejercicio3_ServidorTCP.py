import socket
import os

#creamos el socket, la direccion, lo bindeamos y escuchamos
servidortcp = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
direccion = ('localhost',8080)
buffer = 1024
servidortcp.bind(direccion)
servidortcp.listen()

print('Esperando clientes')
#aceptamos la conexion con el cliente
cliente, cliente_dir = servidortcp.accept()
print(f'Conexion establecida con el cliente {cliente}')

#recibimos el nombre del archivo
nombre_archivo= cliente.recv(buffer).decode()

#recibimos el contenido del fichero, lo invertirmos y calculamos el tamaño
contenido = cliente.recv(buffer).decode()

#vamos a invertir la cadena 
with open(contenido, 'w') as fichero:
    fichero.read()[::-1] #invertimos la carrera