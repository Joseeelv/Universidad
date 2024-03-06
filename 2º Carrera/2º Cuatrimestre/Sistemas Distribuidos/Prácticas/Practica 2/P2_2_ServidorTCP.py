import argparse
import socket

#creamos socket tcp
ser_tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ser_dir = ("localhost",9999) #hemos creado una direccion 

#creamos el listener y lo bindeamos a una conexion
ser_tcp.bind(ser_dir)
ser_tcp.listen() #hacemos que escuche

#Esperamos la conexion con un cliente
print("Esperando clientes..")
cliente, cliente_dir=ser_tcp.accept() #cliente aceptado
print("Conexion establecida con el cliente: ", cliente_dir)

#se recibe el archivo enviado por el cliente
archivo = cliente.recv(1024).decode()

try:
    #abrimos el archivo para ver su contenido
    with open (archivo,"rb") as f:
        #comprobamos que el archivo existe
        cliente.send("existe".encode())
        #vemos si se quiere sobreescribir el archivo
        respuesta = cliente.recv(1024).decode
        if respuesta == "n":
            cliente.close() #si no se quiere sobreescribir se cierra conexion con el cliente
            exit() #salimos
            
except FileNotFoundError: #comprobamos que le archivo puede ser enviado porque no existe
    cliente.send("OK".encode())
    
#Creamos el archivo que almacenará el contenido
with open(archivo,"wb") as f:
    while True:
        #recibimos el archivo
        datos = cliente.recv(1024)
        if not datos: #si no contiene datos el archivo
            break
        f.write(datos) #escribimos los datos

#enviamos la confirmacion al cliente de que todo ha ido bien
cliente.send("Archivo recibido correctamente".encode())
#cerramos conexcion con el cliente
cliente.close()
ser_tcp.close()


    