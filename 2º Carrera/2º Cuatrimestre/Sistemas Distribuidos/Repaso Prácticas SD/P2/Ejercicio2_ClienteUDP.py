import socket
import os

#creamos el socket y la direccion del servidor
clt_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
serv_dir =('localhost',8080)
buffer=1024

print(f'Conexion establecida con el servidor {serv_dir}')

#guardamos el nombre del fichero a enviar y se lo enviamos al servidor
file = input('Introduce el nombre del fichero a enviar al servidor: ')
nombre_fichero = os.path.basename(file)
clt_udp.sendto(nombre_fichero.encode(),serv_dir)

#esperamos la respuesta del servidor de que el fichero existe ya en el directorio del fichero
datos, servidor = clt_udp.recvfrom(buffer)
respuesta =datos.decode()

if respuesta == 'existe':
    print(f'Archivo con nombre {file}, ya existe en el servidor')
    respuesta2 = input("Deseas modificar el nombre del archivo para que se envie de nuevo pero renombrado (s/n)?: ")
    #enviamos la respuesta al servidor
    clt_udp.sendto(respuesta2.encode(),serv_dir)    
    if respuesta2.upper() == 'N':
        print("Cerrando conexion con el servidor..")
        clt_udp.close()
        exit()

#recibimos la respuesta de que se puede enviar el fichero
with open(file, 'rb') as fichero:
    for datos in fichero:
        clt_udp.sendto(datos,serv_dir)
print(f'Archivo con nombre {file} enviado con exito al servidor')

#recibimos la respuesta del servidor 
respuesta3 = clt_udp.recvfrom(buffer).decode()
print(respuesta3)
print('Operacion realizada con exito, Cerrando conexion...')
clt_udp.close()
exit()