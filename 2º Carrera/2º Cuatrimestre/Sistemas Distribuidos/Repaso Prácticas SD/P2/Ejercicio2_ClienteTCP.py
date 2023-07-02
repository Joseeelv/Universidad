import socket
import os

#creamos el socket, buffer y conectamos con el servidor
clt_tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #socket de tipo tcp
dir_serv =('localhost',8080)
buffer = 1024 
#nos conectamos al servidor
clt_tcp.connect(dir_serv)

#enviamos el nombre del archivo a subir al servidor "en esta caso sera un pdf con el nombre file"
archivo = os.path.basename('File.pdf')
clt_tcp.send(archivo.encode())

#recibimos la respuesta del servidor del si el archivo que vamos a subir ya está o no..
respuesta = clt_tcp.recv(buffer).decode()

#si el archivo existe podemos subirlo modificando el nombre ó no modificarlo y no subirlo
if respuesta == "existe":
    print(f'Archivo cuyo nombre {archivo} ya existe en el servidor')
    respuesta2 = input('Deseas modificar el nombre del archivo (s/n): ')
    #si no queremos modificarlo, cancelamos operacion y cerramos conexion con el servidor
    clt_tcp.send(respuesta2.encode())
    if respuesta2.upper() == 'N':
        print(f'Operacion canceladad con exito. Cerrando conexion con el servidor {dir_serv}')
        clt_tcp.close()
        exit()
    else:
        nombre_nuevo = input(f'Introduce otro nombre para modificar el nombre del archivo {archivo}: ')
        #enviamos el nombre del archivo que será modificado en el servidor.
        clt_tcp.send(nombre_nuevo.encode())
        
print('Esperando respuesta del servidor...')         
#esperamos la respuesta del servidor de que ha recibido el fichero correctamente
respuesta4 = clt_tcp.recv(buffer).decode()
print(respuesta4)
print('Operacion realizada con exito. Cerrando conexion...')
clt_tcp.close()
