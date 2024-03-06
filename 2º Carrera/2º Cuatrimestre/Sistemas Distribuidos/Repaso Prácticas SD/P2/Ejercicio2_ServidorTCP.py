import socket
import os

#creamos el socket del servidor, la direccion,lo  y escuchamos
serv_tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
dir_ser = ('localhost', 8080)
serv_tcp.bind(dir_ser)
serv_tcp.listen(1) #solo a un host
buffer = 1024
print('Esperando clientes')
#establecemos conexion con el cliente
cliente, cliente_dir = serv_tcp.accept()
print('Conexion establecida con el cliente', '\nEsperando archivos...')

#recibimos el nombre del fichero
nom_archivo = cliente.recv(buffer).decode()

if os.path.exists(nom_archivo): #si existe el archivo, dejamos que el cliente decida si quiere sobreescribirlo o no
    cliente.send('existe'.encode())
    #esperamos la respuesta del cliente de si se quiere sobreescribir o no
    response2 = cliente.recv(buffer).decode()
    if response2.upper() == "N":
        #cerramos conexion con el cliente
        print(f'No se ha querido modificar el nombre del archivo {nom_archivo}, Abortando operacion..')
        cliente.close()
        serv_tcp.close()
        exit()
    else:
        #recibimos el nombre de modificación
        nombre_modif = cliente.recv(buffer).decode()
#mandamos el mensaje de confirmacion de que se puede enviar el fichero
cliente.send('OK'.encode())

#subimos el fichero al servidor
with open (nombre_modif,'wb') as fichero:
    while True:
        datos = cliente.recv(buffer).decode()
        if not datos:
            break
        fichero.write(datos)
print(f'Fichero con nombre {nombre_modif} subido correctamente al servidor.','\nCerrando conexcion con el cliente...' )
cliente.close()
serv_tcp.close()
exit()