import socket
import os

#creamos el socket, la direccion servidor, lo bindeamos para escuchar
serv_udp =socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
dir_serv=('localhost',8080)
buffer = 1024
serv_udp.bind(dir_serv)
print("Esperando clientes")

while True:
    #recibimos el nombre del archivo del cliente
    datos, cliente = serv_udp.recvfrom(buffer)
    nombre = datos.decode()
    print(f'Cliente quiere subir un archivo con nombre {nombre}')
    #comprobamos que el archivo existe en el servidor
    if os.path.exists(nombre):
        response = 'existe'
        serv_udp.sendto(response.encode(),cliente)
        
        #esperamos la respuesta del cliente
        datos, cliente = serv_udp.recvfrom(buffer)
        opcion = datos.decode()
        
        if opcion.upper() == 'N':
            print(f'Cerrando conexion con el cliente {cliente}')
            cliente.close()
            exit()
        else:
            #recibimos el nombre modificado del archivo
            datos, cliente = serv_udp.recvfrom(buffer)
            nombre = datos.decode()
    else:
        #guardamos el archivo en el servidor
        with open(nombre,'wb') as archivo:
            while True:
                datos, cliente = serv_udp.recvfrom(buffer)
                if not datos:
                    break
                archivo.write(datos)
        
        #enviamos mensaje de confirmacion
        print(f'Archivo {nombre} recibido con exito')
        serv_udp.sendto('Archivo recibido correctamente'.endcode(), cliente)
        cliente.close()
        serv_udp.close()
        exit()