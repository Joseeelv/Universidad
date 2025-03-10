import socket
import os
import argparse


#Creacion del socket con TCP
direccion_servidor=('localhost',9999)   #creamos un socket cuya
                                        #cuya direcion sea host local y puerto 1025  
clt_tcp=socket.socket(socket.AF_INET, socket.SOCK_STREAM) #inet siempre lo usamos y Stream es TCP
#nos conectamos al servidor
clt_tcp.connect(direccion_servidor)
print('Conexión establecida con el servidor')

#enviamos el pdf al servidor
file = "filein.pdf"
clt_tcp.send(file.encode())

#comprobamos la respuesta del servidor
respuesta = clt_tcp.recv(1024).decode()

#comprobamos si existe o no el fichero
if respuesta == "existe":
    #preguntamos si se quiere sobreescribir el archivo
    overwrite = input("El archivo ya se encuentra en el servidor. Desea sobreescribirlo? (s/n): ")
    if overwrite == "n": # si no queremos sobreescribir nada, salimos
        clt_tcp.close()
        exit()
# si no existe 
with open(file, "rb") as archivo:
    #solo se lee si tiene datos el archivo
    while True:
        datos = archivo.read(1024)
        if not datos:
            break
        clt_tcp.send(datos) #enviamos los datos cuando hayamos
                            # terminado de leerlos

#esperamos la respuesta del servidor de que todo ha ido bien
respuesta = clt_tcp.recv(1024).decode()
print(respuesta)
clt_tcp.close() #cerramos la conexion con el servidor